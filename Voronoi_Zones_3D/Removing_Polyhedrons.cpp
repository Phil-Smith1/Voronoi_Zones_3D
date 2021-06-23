#include "B_Poly.h"

using namespace std;

typedef K::Point_3 P3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Removing_Polyhedrons ( P3 const& base_pt, double plane_distance, vector<B_Poly>& polys, vector<B_Poly>& final_polys, int zone_limit )
{
    vector<B_Poly> remaining_polys;
    remaining_polys.reserve( polys.size() );
    vector<B_Poly> inside_polys;
    inside_polys.reserve( polys.size() );
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        if (polys[counter].zone <= zone_limit)
        {
            if (polys[counter].dist < plane_distance + tiny_num) inside_polys.push_back( polys[counter] );
            
            else remaining_polys.push_back( polys[counter] );
        }
    }
    
    polys = remaining_polys;
    final_polys.insert( final_polys.end(), inside_polys.begin(), inside_polys.end() );
}
