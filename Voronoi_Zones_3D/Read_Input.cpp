#include "Framework_Parameters.h"
#include "Input.h"

#include <fstream>

bool Read_Input ( Framework_Parameters const& f_p, string const& input_file, Input& input )
{
    ifstream ifs( f_p.input_dir + input_file );
    
    if (!ifs.is_open())
    {
        cout << "Periodic set file not found!" << endl;
        return false;
    }
    
    string line_data, val;
    
    getline( ifs, line_data );
    
    stringstream stream;
    
    stream << line_data;
    
    getline( stream, val, ',' );
    
    input.cell_param_a = stod( val );
    
    getline( stream, val, ',' );
    
    input.cell_param_b = stod( val );
    
    getline( stream, val, ',' );
    
    input.cell_param_c = stod( val );
    
    getline( stream, val, ',' );
    
    input.cell_param_alpha = stod( val );
    
    getline( stream, val, ',' );
    
    input.cell_param_beta = stod( val );
    
    getline( stream, val, ',' );
    
    input.cell_param_gamma = stod( val );
    
    while(getline( ifs, line_data ))
    {
        stream.clear();
        stream << line_data;
        
        getline( stream, val, ',' );
        
        double x = stod( val );
        
        getline( stream, val, ',' );
        
        double y = stod( val );
        
        getline( stream, val, ',' );
        
        double z = stod( val );
        
        input.frac_base_pts.push_back( P3( x, y, z ) );
    }
    
    ifs.close();
    
    return true;
}
