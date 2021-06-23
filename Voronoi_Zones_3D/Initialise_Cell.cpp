#include "Input.h"
#include "Transformation_Matrix.h"
#include "Frac_To_Cart_Coords.h"

void Initialise_Cell ( Input& input )
{
    vector<pair<string, double>> cell_shape;
    cell_shape.reserve( 6 );

    cell_shape.push_back( pair<string, double>( "_cell_length_a", input.cell_param_a ) );
    cell_shape.push_back( pair<string, double>( "_cell_length_b", input.cell_param_b ) );
    cell_shape.push_back( pair<string, double>( "_cell_length_c", input.cell_param_c ) );
    cell_shape.push_back( pair<string, double>( "_cell_angle_alpha", input.cell_param_alpha ) );
    cell_shape.push_back( pair<string, double>( "_cell_angle_beta", input.cell_param_beta ) );
    cell_shape.push_back( pair<string, double>( "_cell_angle_gamma", input.cell_param_gamma ) );
    
    input.matrix = new double *[3];
    input.matrix[0] = new double [3];
    input.matrix[1] = new double [3];
    input.matrix[2] = new double [3];

    Transformation_Matrix( cell_shape, input.matrix );
    
    P3 p1 = P3( 1, 0, 0 );
    P3 p2 = P3( 0, 1, 0 );
    P3 p3 = P3( 0, 0, 1 );
    
    Frac_To_Cart_Coords( input.matrix, p1 );
    Frac_To_Cart_Coords( input.matrix, p2 );
    Frac_To_Cart_Coords( input.matrix, p3 );
    
    input.lattice_vectors.push_back( p1 );
    input.lattice_vectors.push_back( p2 );
    input.lattice_vectors.push_back( p3 );
    
    input.base_pts.clear();
    
    for (int counter = 0; counter < input.frac_base_pts.size(); ++counter)
    {
        input.base_pts.push_back( input.frac_base_pts[counter] );
    }
    
    for (int counter = 0; counter < input.base_pts.size(); ++counter)
    {
        Frac_To_Cart_Coords( input.matrix, input.base_pts[counter] );
    }
}
