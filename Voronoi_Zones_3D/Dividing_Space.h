#pragma once

#include "Generate_Cube.h"
#include "Divide_Polyhedron.h"

#include <thread>

void Dividing_Space ( multimap<double, P3>const& cloud, P3 const& base_pt, int zone_limit, vector<B_Poly>& final_polys, vector<double>& max_radii, bool use_threads );
