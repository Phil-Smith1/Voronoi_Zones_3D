#include <string>
#include <vector>
#include <cmath>

using namespace std;

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

double Cell_Volume ( vector<pair<string, double>>const& cell_shape )
{
    double volume = cell_shape[0].second * cell_shape[1].second * cell_shape[2].second * sqrt( 1 - pow( cos( PI * cell_shape[3].second / (double)180 ), 2 ) - pow( cos( PI * cell_shape[4].second / (double)180 ), 2 ) - pow( cos( PI * cell_shape[5].second / (double)180 ), 2 ) + 2 * cos( PI * cell_shape[3].second / (double)180 ) * cos( PI * cell_shape[4].second / (double)180 ) * cos( PI * cell_shape[5].second / (double)180 ) );
    
    return volume;
}
