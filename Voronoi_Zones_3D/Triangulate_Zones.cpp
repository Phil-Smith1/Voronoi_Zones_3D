#include "B_Poly.h"

#include <CGAL/Triangulation_3.h>

using namespace std;

typedef Tetrahedron_3<K> Tetrahedron;
typedef Triangulation_3<K> Triangulation;
typedef K::Point_3 P3;
typedef Polyhedron::Vertex_iterator vertex_iterator;
typedef Triangulation::Finite_cells_iterator cells_iterator;

void Triangulate_Zones ( vector<B_Poly>& polys, int zone_limit, vector<vector<Tetrahedron>>& tetras, vector<double>& cell_volume )
{
    tetras.resize( zone_limit );
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        vector<P3> vertices;
        
        for (vertex_iterator v = polys[counter].poly.vertices_begin(); v != polys[counter].poly.vertices_end(); ++v)
        {
            P3 p = v->point();
            
            vertices.push_back( p );
        }
        
        Triangulation T( vertices.begin(), vertices.end() );
        
        for (cells_iterator c = T.Triangulation::finite_cells_begin(); c != T.Triangulation::finite_cells_end(); ++c)
        {
            Tetrahedron tetra = T.Triangulation::tetrahedron( c );
            
            tetras[polys[counter].zone - 1].push_back( tetra );
            
            cell_volume[polys[counter].zone - 1] += tetra.volume();
        }
    }
}
