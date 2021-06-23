#pragma once

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

int Plane_Intersect_Polyhedron ( Polyhedron& poly, Pl3 const& plane );
