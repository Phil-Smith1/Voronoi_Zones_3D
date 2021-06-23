#pragma once

#include "Framework_Parameters.h"
#include "B_Poly.h"

#include <fstream>

typedef K::Point_3 P3;
typedef Polyhedron::Vertex_iterator vertex_iterator;
typedef Polyhedron::Halfedge_iterator halfedge_iterator;
typedef Polyhedron::Face_iterator face_iterator;
typedef Polyhedron::Facet::Halfedge_around_facet_circulator face_he_circulator;

void Write_Poly_VTK_File ( Framework_Parameters const& f_p, vector<B_Poly>const& polys );
