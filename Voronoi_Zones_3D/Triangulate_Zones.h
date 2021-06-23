#pragma once

#include "B_Poly.h"

#include <CGAL/Triangulation_3.h>

using namespace std;

typedef Tetrahedron_3<K> Tetrahedron;
typedef Triangulation_3<K> Triangulation;
typedef K::Point_3 P3;
typedef Polyhedron::Vertex_iterator vertex_iterator;
typedef Triangulation::Finite_cells_iterator cells_iterator;

void Triangulate_Zones ( vector<B_Poly>& polys, int zone_limit, vector<vector<Tetrahedron>>& tetras, vector<double>& cell_volume );
