#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Polyhedron_3<K> Polyhedron;
typedef K::Point_3 P3;

typedef Polyhedron::Vertex_iterator vertex_iterator;

double Max_Distance_To_Polyhedron ( P3 const& base_pt, Polyhedron& poly );
