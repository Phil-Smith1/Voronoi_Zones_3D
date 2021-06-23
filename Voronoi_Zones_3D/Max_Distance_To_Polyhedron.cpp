#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Polyhedron_3<K> Polyhedron;
typedef K::Point_3 P3;

typedef Polyhedron::Vertex_iterator vertex_iterator;

double Max_Distance_To_Polyhedron ( P3 const& base_pt, Polyhedron& poly )
{
    double max_radius = 0;
    
    for (vertex_iterator v = poly.vertices_begin(); v != poly.vertices_end(); ++v)
    {
        P3 p = v->point();
        
        double dist = squared_distance( p, base_pt );
        
        if (dist > max_radius) max_radius = dist;
    }
    
    return sqrt( max_radius );
}
