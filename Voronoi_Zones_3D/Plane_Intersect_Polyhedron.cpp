#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Polyhedron_3<K> Polyhedron;
typedef K::Point_3 P3;
typedef K::Plane_3 Pl3;
typedef Polyhedron::Vertex_iterator vertex_iterator;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

int Plane_Intersect_Polyhedron ( Polyhedron& poly, Pl3 const& plane )
{
    bool pos = false, neg = false;
    
    for (vertex_iterator v = poly.vertices_begin(); v != poly.vertices_end(); ++v)
    {
        P3 p = v->point();
        
        if (squared_distance( p, plane ) < tiny_num) continue;
        
        else if (plane.oriented_side( p ) == ON_POSITIVE_SIDE) pos = true;
        
        else neg = true;
        
        if (pos && neg) break;
    }
    
    if (!pos || !neg)
    {
        if (!pos) return -1;
        
        else return 1;
    }
    
    else return 0;
}
