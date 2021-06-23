#include "Generate_Cube.h"
#include "Divide_Polyhedron.h"

#include <thread>

void Dividing_Space ( multimap<double, P3>const& cloud, P3 const& base_pt, int zone_limit, vector<B_Poly>& final_polys, vector<double>& max_radii, bool use_threads )
{
    Polyhedron cube;
    
    double cube_size = sqrt( cloud.rbegin()->first ) * 0.5;
    
    Generate_Cube( cube_size, base_pt, cube );
    
    multimap<double, P3> reduced_pts;
    multimap<double, P3> remaining_pts;
    
    for (auto iter = cloud.begin(); iter != cloud.end(); ++iter)
    {
        if ((int)reduced_pts.size() <= 5) reduced_pts.insert( pair<double, P3>( iter->first, iter->second ) );
        
        else remaining_pts.insert( pair<double, P3>( iter->first, iter->second ) );
    }
    
    vector<B_Poly> starting_polys;
    
    Divide_Polyhedron( reduced_pts, base_pt, zone_limit, cube, 1, starting_polys );
    
    vector<vector<B_Poly>> fin_polys( (int)starting_polys.size() );
    vector<thread> thr;
    
    thr.reserve( starting_polys.size() );
    
    for (int counter = 0; counter < fin_polys.size(); ++counter)
    {
        fin_polys[counter].reserve( 1000 );
    }
    
    if (use_threads)
    {
        for (int counter = 0; counter < starting_polys.size(); ++counter)
        {
            thr.push_back( thread( Divide_Polyhedron, remaining_pts, base_pt, zone_limit, starting_polys[counter].poly, starting_polys[counter].zone, ref( fin_polys[counter] ) ) );
        }
        
        for (int counter = 0; counter < starting_polys.size(); ++counter)
        {
            thr[counter].join();
        }
    }
    
    else
    {
        for (int counter = 0; counter < starting_polys.size(); ++counter)
        {
            Divide_Polyhedron( remaining_pts, base_pt, zone_limit, starting_polys[counter].poly, starting_polys[counter].zone, fin_polys[counter] );
        }
    }
    
    for (int counter_1 = 0; counter_1 < starting_polys.size(); ++counter_1)
    {
        final_polys.insert( final_polys.end(), fin_polys[counter_1].begin(), fin_polys[counter_1].end() );
    }
    
    vector<double> vec( zone_limit, 0 );
    max_radii = vec;
    
    for (int counter = 0; counter < final_polys.size(); ++counter)
    {
        double max_radius = final_polys[counter].dist;
        
        if (max_radii[final_polys[counter].zone - 1] < max_radius) max_radii[final_polys[counter].zone - 1] = max_radius;
    }
}
