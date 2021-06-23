#include "Input.h"

typedef K::Vector_3 V3;

void Surrounding_Cloud ( Input const& input, int index, multimap<double, P3>& cloud )
{
    V3 v1 = input.lattice_vectors[0] - ORIGIN;
    V3 v2 = input.lattice_vectors[1] - ORIGIN;
    V3 v3 = input.lattice_vectors[2] - ORIGIN;
    
    for (int counter_1 = -input.perim; counter_1 < input.perim + 1; ++counter_1)
    {
        for (int counter_2 = -input.perim; counter_2 < input.perim + 1; ++counter_2)
        {
            for (int counter_3 = -input.perim; counter_3 < input.perim + 1; ++counter_3)
            {
                V3 v = counter_1 * v1 + counter_2 * v2 + counter_3 * v3;
                
                for (int counter_4 = 0; counter_4 < input.base_pts.size(); ++counter_4)
                {
                    if (counter_1 == 0 && counter_2 == 0 && counter_3 == 0 && counter_4 == index) continue;
                    
                    P3 p = input.base_pts[counter_4] + v;
                    
                    double dist = squared_distance( input.base_pts[index], p );
                    
                    cloud.insert( pair<double, P3>( dist, p ) );
                }
            }
        }
    }
}
