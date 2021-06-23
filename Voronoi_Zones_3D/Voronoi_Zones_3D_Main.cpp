#include "Print_Info.h"

int main( int, char*[] )
{
    clock_t start_code_runtime = clock(); // Starts the clock measuring the runtime of the code.
    
    chrono::time_point<chrono::steady_clock> start_absolute_time = chrono::steady_clock::now(); // Starts the clock measuring the absolute time to complete the code.
    
    Print_Info( start_code_runtime, start_absolute_time ); // Prints runtimes.
    
    return 0;
}
