#include "Framework_Parameters.h"
#include "B_Poly.h"

#include <fstream>

typedef K::Point_3 P3;
typedef Polyhedron::Vertex_iterator vertex_iterator;
typedef Polyhedron::Halfedge_iterator halfedge_iterator;
typedef Polyhedron::Face_iterator face_iterator;
typedef Polyhedron::Facet::Halfedge_around_facet_circulator face_he_circulator;

void Write_Poly_VTK_File ( Framework_Parameters const& f_p, vector<B_Poly>const& polys )
{
    int num_polys_written = 0;
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        if (polys[counter].zone <= 10)
        {
            Polyhedron poly = polys[counter].poly;
            
            ofstream ofs( f_p.output_file + to_string( polys[counter].zone ) + "_" + to_string( num_polys_written ) + ".vtk" );
            
            ofs << "# vtk DataFile Version 3.0" << endl;
            ofs << "vtk output" << endl;
            ofs << "ASCII" << endl;
            ofs << "DATASET POLYDATA" << endl;
            ofs << "Points " << poly.size_of_vertices() << " double" << endl;
            
            for (vertex_iterator v = poly.vertices_begin(); v != poly.vertices_end(); ++v)
            {
                ofs << v->point().x() << " " << v->point().y() << " " << v->point().z() << endl;
            }
            
            int list_size = 0;
            
            for (face_iterator f = poly.facets_begin(); f != poly.facets_end(); ++f)
            {
                list_size += f->size() + 1;
            }
            
            ofs << "Polygons " << poly.size_of_facets() << " " << list_size;
            
            for (face_iterator f = poly.facets_begin(); f != poly.facets_end(); ++f)
            {
                ofs << endl;
                ofs << f->size();
                
                face_he_circulator h = f->facet_begin(), i = f->facet_begin();
                
                do
                {
                    ofs << " " << distance( poly.vertices_begin(), h->vertex() );
                } while( ++h != i);
            }
            
            ofs.close();
            
            ++num_polys_written;
        }
    }
}
