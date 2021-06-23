#include "Read_Framework_Parameters.h"
#include "Read_Input.h"
#include "Initialise_Cell.h"
#include "Voronoi_Zone_Algorithm.h"
#include "Print_Info.h"

int main( int, char*[] )
{
    clock_t start_code_runtime = clock(); // Starts the clock measuring the runtime of the code.
    
    chrono::time_point<chrono::steady_clock> start_absolute_time = chrono::steady_clock::now(); // Starts the clock measuring the absolute time to complete the code.
    
    Framework_Parameters f_p; // Class containing details of what functions to run etc.
    
    if (!Read_Framework_Parameters( f_p )) return 1; // Reading the framework parameters.
    
    ifstream ifs_1( f_p.input_dir + f_p.input_file ); // Opening the input file.
    
    if (!ifs_1.is_open())
    {
        cout << "Input file not found!" << endl;
        return 1;
    }
    
    int num_inputs = 0; // Counter for the number of inputs.
    string line_data; // Generic string.
    
    while (getline( ifs_1, line_data )) // Looping over the inputs.
    {
        ++num_inputs; // Increase number of inputs counter.
        
        Input input; // Class containing all the information about the input.
        input.num_input = num_inputs;
        input.k = input.perim = f_p.k;
        
        if (!Read_Input( f_p, line_data, input )) return 1; // Reading the input.
        
        Initialise_Cell( input ); // Computing the transformation matrix, the lattice vectors and the motif.
        
        Voronoi_Zone_Algorithm( f_p, input ); // Main Voronoi zone computations occur here.
    }
    
    Print_Info( start_code_runtime, start_absolute_time ); // Prints runtimes.
    
    return 0;
}
