#include "Framework_Parameters.h"
#include "Input.h"
#include "Dividing_Space.h"
#include "Triangulate_Zones.h"
#include "Write_Poly_VTK_File.h"

void Compute_Voronoi_Zones ( Framework_Parameters const& f_p, Input const& input, P3 const& base_pt, multimap<double, P3>const cloud, vector<double>& zone_volume, vector<double>& max_radii, vector<vector<Tetrahedron>>& tetras )
{
    vector<B_Poly> polys;
    polys.reserve( 3000 );
    
    Dividing_Space( cloud, base_pt, input.k, polys, max_radii, f_p.use_threads );
    
    Triangulate_Zones( polys, input.k, tetras, zone_volume );
    
    if (f_p.write_vtk) Write_Poly_VTK_File( f_p, polys );
}
