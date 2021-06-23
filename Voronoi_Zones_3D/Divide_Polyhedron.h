#pragma once

#include "Max_Distance_To_Polyhedron.h"
#include "Removing_Polyhedrons.h"
#include "Plane_Intersect_Polyhedron.h"
#include "Max_Radius_Of_Space.h"

#include <mutex>

#include <CGAL/convex_hull_3.h>

typedef K::Segment_3 S3;
typedef K::Intersect_3 I3;
typedef Polyhedron::Halfedge_iterator halfedge_iterator;

void Divide_Polyhedron ( multimap<double, P3>const cloud, P3 const base_pt, int zone_limit, Polyhedron poly, int starting_zone, vector<B_Poly>& final_polys );
