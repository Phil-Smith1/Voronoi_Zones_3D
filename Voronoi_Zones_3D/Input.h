#pragma once

#include <string>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;

class Input
{
    public:
    
    int k, perim, num_input;
    double cell_param_a, cell_param_b, cell_param_c, cell_param_alpha, cell_param_beta, cell_param_gamma, max_radius;
    double ** matrix;
    vector<P3> frac_base_pts, lattice_vectors, base_pts;
    
    Input();
    ~Input();
};
