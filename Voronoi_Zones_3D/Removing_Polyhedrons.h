#pragma once

#include "B_Poly.h"

using namespace std;

typedef K::Point_3 P3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Removing_Polyhedrons ( P3 const& base_pt, double plane_distance, vector<B_Poly>& polys, vector<B_Poly>& final_polys, int zone_limit );
