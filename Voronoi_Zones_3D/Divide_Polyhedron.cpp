#include "Max_Distance_To_Polyhedron.h"
#include "Removing_Polyhedrons.h"
#include "Plane_Intersect_Polyhedron.h"
#include "Max_Radius_Of_Space.h"

#include <mutex>

#include <CGAL/convex_hull_3.h>

typedef K::Segment_3 S3;
typedef K::Intersect_3 I3;
typedef Polyhedron::Halfedge_iterator halfedge_iterator;

void Divide_Polyhedron ( multimap<double, P3>const cloud, P3 const base_pt, int zone_limit, Polyhedron poly, int starting_zone, vector<B_Poly>& final_polys )
{
    vector<B_Poly> polys;
    polys.push_back( B_Poly( poly, Max_Distance_To_Polyhedron( base_pt, poly ), starting_zone ) );
    
    double max_radius = 1e10;
    double plane_distance = 0;
    
    vector<Pl3> planes;
    planes.reserve( (int)cloud.size() );
    
    double precision = 1e12;
    
    bool remove_polys = false;
    
    for (auto iter = cloud.begin(); iter != cloud.end(); ++iter)
    {
        Pl3 plane = bisector( base_pt, (*iter).second );
        
        long double a = (long long int)(plane.a() * precision + 0.5);
        long double b = (long long int)(plane.b() * precision + 0.5);
        long double c = (long long int)(plane.c() * precision + 0.5);
        long double d = (long long int)(plane.d() * precision + 0.5);
        
        a = a / (long double)precision;
        b = b / (long double)precision;
        c = c / (long double)precision;
        d = d / (long double)precision;
        
        plane = Pl3( a, b, c, d );
        
        plane_distance = sqrt( squared_distance( base_pt, plane ) );
        
        if (max_radius < plane_distance + tiny_num) break;
        
        {
            mutex m1;
            
            lock_guard<mutex> lock_guard( m1 );
            
            if (remove_polys) Removing_Polyhedrons( base_pt, plane_distance, polys, final_polys, zone_limit );
        }
        
        if (plane.oriented_side( base_pt ) == ON_NEGATIVE_SIDE) plane = plane.opposite();
        
        planes.push_back( plane );
        
        if ((int)polys.size() == 0) break;
        
        int intersect = Plane_Intersect_Polyhedron( poly, plane );
        
        if (intersect == -1)
        {
            for (int counter = 0; counter < polys.size(); ++counter)
            {
                polys[counter].zone += 1;
            }
            
            remove_polys = true;
            
            continue;
        }
        
        else if (intersect == 1)
        {
            remove_polys = false;
            continue;
        }
        
        else
        {
            remove_polys = true;
            
            vector<B_Poly> new_polys;
            new_polys.reserve( (int)polys.size() );
            
            for (int counter_1 = 0; counter_1 < polys.size(); ++counter_1)
            {
                vector<P3> pos_pts;
                vector<P3> neg_pts;
                vector<P3> bdry_pts;
                
                for (vertex_iterator v = polys[counter_1].poly.vertices_begin(); v != polys[counter_1].poly.vertices_end(); ++v)
                {
                    P3 p = v->point();
                    
                    if (squared_distance( p, plane ) < tiny_num) bdry_pts.push_back( p );
                    
                    else if (plane.oriented_side( p ) == ON_POSITIVE_SIDE) pos_pts.push_back( p );
                    
                    else neg_pts.push_back( p );
                }
                
                if ((int)neg_pts.size() == 1 && squared_distance( neg_pts[0], plane ) < 1e-3) continue;
                
                else if ((int)pos_pts.size() == 1 && squared_distance( pos_pts[0], plane ) < 1e-3)
                {
                    ++polys[counter_1].zone;
                    continue;
                }
                
                else if ((int)neg_pts.size() == 0 || (int)pos_pts.size() == 0)
                {
                    if ((int)pos_pts.size() == 0) ++polys[counter_1].zone;
                    continue;
                }
                
                else
                {
                    vector<S3> segs;
                    
                    for (halfedge_iterator h = polys[counter_1].poly.halfedges_begin(); h != polys[counter_1].poly.halfedges_end(); ++h)
                    {
                        P3 p1 = (h->vertex())->point();
                        P3 p2 = (h->prev()->vertex())->point();
                        
                        long double x = (long long int)(p1.x() * precision + 0.5);
                        long double y = (long long int)(p1.y() * precision + 0.5);
                        long double z = (long long int)(p1.z() * precision + 0.5);
                        
                        x = x / (long double)precision;
                        y = y / (long double)precision;
                        z = z / (long double)precision;
                        
                        p1 = P3( x, y, z );
                        
                        x = (long long int)(p2.x() * precision + 0.5);
                        y = (long long int)(p2.y() * precision + 0.5);
                        z = (long long int)(p2.z() * precision + 0.5);
                        
                        x = x / (long double)precision;
                        y = y / (long double)precision;
                        z = z / (long double)precision;
                        
                        p2 = P3( x, y, z );
                        
                        segs.push_back( S3( p1, p2 ) );
                        
                        ++h;
                    }
                    
                    vector<P3> pts;
                    
                    for (int counter_2 = 0; counter_2 < segs.size(); ++counter_2)
                    {
                        cpp11::result_of<I3(Pl3, S3)>::type result = intersection( plane, segs[counter_2] );
                        
                        if (result)
                        {
                            if (const P3 * p = boost::get<P3>( &*result ))
                            {
                                if (squared_distance( *p, segs[counter_2].source() ) > tiny_num && squared_distance( *p, segs[counter_2].target() ) > tiny_num)
                                {
                                    P3 pt = *p;
                                    
                                    long double x = (long long int)(pt.x() * precision + 0.5);
                                    long double y = (long long int)(pt.y() * precision + 0.5);
                                    long double z = (long long int)(pt.z() * precision + 0.5);
                                    
                                    x = x / (long double)precision;
                                    y = y / (long double)precision;
                                    z = z / (long double)precision;
                                    
                                    pt = P3( x, y, z );
                                    
                                    pts.push_back( pt );
                                }
                            }
                        }
                    }
                    
                    pos_pts.insert( pos_pts.end(), pts.begin(), pts.end() );
                    pos_pts.insert( pos_pts.end(), bdry_pts.begin(), bdry_pts.end() );
                    neg_pts.insert( neg_pts.end(), pts.begin(), pts.end() );
                    neg_pts.insert( neg_pts.end(), bdry_pts.begin(), bdry_pts.end() );
                    
                    Polyhedron pos_poly, neg_poly;
                    
                    convex_hull_3( pos_pts.begin(), pos_pts.end(), pos_poly );
                    
                    double dist_pos_poly = Max_Distance_To_Polyhedron( base_pt, pos_poly );
                    
                    polys[counter_1].poly = pos_poly;
                    polys[counter_1].dist = dist_pos_poly;
                    
                    if (polys[counter_1].zone + 1 <= zone_limit)
                    {
                        convex_hull_3( neg_pts.begin(), neg_pts.end(), neg_poly );
                        
                        double dist_neg_poly = Max_Distance_To_Polyhedron( base_pt, neg_poly );
                        
                        new_polys.push_back( B_Poly( neg_poly, dist_neg_poly, polys[counter_1].zone + 1 ) );
                    }
                }
            }
            
            polys.insert( polys.end(), new_polys.begin(), new_polys.end() );
        }
        
        max_radius = Max_Radius_Of_Space( polys );
    }
    
    {
        mutex m1;
        
        lock_guard<mutex> lock_guard( m1 );
        
        Removing_Polyhedrons( base_pt, plane_distance, polys, final_polys, zone_limit );
        
        final_polys.insert( final_polys.end(), polys.begin(), polys.end() );
    }
}
