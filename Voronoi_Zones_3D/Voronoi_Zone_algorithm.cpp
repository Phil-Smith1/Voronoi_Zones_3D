#include "Surrounding_Cloud.h"
#include "Compute_Voronoi_Zones.h"

void Voronoi_Zone_Algorithm ( Framework_Parameters const& f_p, Input& input )
{
    cout << "Computing Voronoi zones for " << input.base_pts.size() << " point(s):" << endl;

    vector<double> zone_volume( input.k, 0 ); // Records the area of the zone for each k.
    
    for (int counter = 0; counter < input.base_pts.size(); ++counter) // Looping over base points.
    {
        vector<double> max_radii; // Contains the maximum radius of each zone from the base point.
        vector<vector<Tetrahedron>> tetras; // Contains the Voronoi zones, stored as a vector of tetrahedrons for each zone.
        multimap<double, P3> cloud; // The cloud surrounding the base point.
        
        Surrounding_Cloud( input, counter, cloud ); // Computing the surrounding cloud.
        
        Compute_Voronoi_Zones( f_p, input, input.base_pts[counter], cloud, zone_volume, max_radii, tetras ); // Computing the Voronoi zones.
    }
}
