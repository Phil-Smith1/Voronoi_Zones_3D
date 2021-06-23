#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Polyhedron_3<K> Polyhedron;

class B_Poly
{
    public:
    
    int zone;
    double dist;
    Polyhedron poly;
    
    B_Poly ( Polyhedron const& p, double d, int z );
    
    B_Poly();
    ~B_Poly();
};
