#include "Framework_Parameters.h"

#include <fstream>
#include <sstream>
#include <iostream>

bool Read_Framework_Parameters ( Framework_Parameters& f_p )
{
    ifstream ifs( "/Users/philsmith/Documents/Work/Xcode Projects/Voronoi_Zones/Voronoi_Zones_3D/Input/Framework_Parameters.csv" );
    
    if (!ifs.is_open())
    {
        cout << "Framework parameters file not found!" << endl;
        return false;
    }
    
    string line_data, val;
    
    getline( ifs, line_data );
    
    stringstream stream;
    
    stream << line_data;
    
    getline( stream, val, ',' );
    getline( stream, val, ',' );
    
    f_p.input_dir = val;
    
    getline( ifs, line_data );
    
    stream.clear();
    stream << line_data;
    
    getline( stream, val, ',' );
    getline( stream, val, ',' );
    
    f_p.output_dir = val;
    
    getline( ifs, line_data );
    
    stream.clear();
    stream << line_data;
    
    getline( stream, val, ',' );
    getline( stream, val, ',' );
    
    f_p.input_file = val;
    
    getline( ifs, line_data );
    
    stream.clear();
    stream << line_data;
    
    getline( stream, val, ',' );
    getline( stream, val, ',' );
    
    f_p.use_threads = stoi( val );
    
    getline( ifs, line_data );
    
    stream.clear();
    stream << line_data;
    
    getline( stream, val, ',' );
    getline( stream, val, ',' );
    
    f_p.k = stoi( val );
    
    getline( ifs, line_data );
    
    stream.clear();
    stream << line_data;
    
    getline( stream, val, ',' );
    getline( stream, val, ',' );
    
    f_p.write_vtk = stoi( val );
    
    getline( ifs, line_data );
    
    stream.clear();
    stream << line_data;
    
    getline( stream, val, ',' );
    getline( stream, val, ',' );
    
    f_p.output_file = val;
    
    ifs.close();
    
    return true;
}

