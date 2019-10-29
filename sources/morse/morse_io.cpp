#include "formangradientvector.h"


void FormanGradientVector::writeVTK_1cells(char* file_name, set<int> const& vertici, set<pair<int,int> > const& edges){

    int vertex_number = vertici.size();
    int edge_number = edges.size();

    vector<int> new_vertex_index = vector<int>(mesh->get_vertices_num(), -1);
    vector<int> critical_index = vector<int>(mesh->get_vertices_num(), -1);

    FILE* file;
    file = fopen(file_name, "w");


    int i=0;
    for(set<int>::iterator it = vertici.begin(); it!=vertici.end(); it++){
            new_vertex_index[*it] = i++;
    }


    fprintf(file, "# vtk DataFile Version 2.0\n\n");
    fprintf(file, "ASCII \n");
    fprintf(file, "DATASET UNSTRUCTURED_GRID\n\n");
    fprintf(file, "POINTS %d float\n", vertex_number);

    for(int i=0; i<mesh->get_vertices_num(); i++){
        if(new_vertex_index[i] != -1){
            fprintf(file, "%f %f %f\n", mesh->get_vertex(i).get_c(0), mesh->get_vertex(i).get_c(1), mesh->get_vertex(i).get_c(2));
        }

    }
    fprintf(file, "\n\n");

    fprintf(file, "CELLS %d %d\n", edge_number, edge_number*3);

    for(set<pair<int,int> >::iterator it = edges.begin(); it != edges.end(); it++){
        fprintf(file, "2 %d %d \n", new_vertex_index[it->first], new_vertex_index[it->second]);
    }
    fprintf(file, "\n");

    fprintf(file, "CELL_TYPES %d\n", edge_number);

    for(int i=0; i<edge_number; i++)
        fprintf(file, "%d ", 3);
    fprintf(file, "\n\n");


    fprintf(file, "POINT_DATA %d \n", vertex_number);
    fprintf(file, "FIELD FieldData 1\n");
    fprintf(file, "originalField 1 %d float\n", vertex_number);

    int j=0;
    for(int i=0; i<mesh->get_vertices_num(); i++){
        if(new_vertex_index[i] != -1){
            fprintf(file, "%f ", mesh->get_vertex(i).get_c(2));
         j++;
        }
    }

    fprintf(file, "\n\n");

    fclose(file);

}

void FormanGradientVector::writeVTK_1cells(char* file_name, set<pair<Vertex,Vertex> > const& edges){

    int count=0;
    map<Vertex, int> vertices;

    for(auto s : edges ){
        if(vertices.find(s.first) == vertices.end()){
            vertices[s.first]=count++;
        }

        if(vertices.find(s.second) == vertices.end()){
            vertices[s.second]=count++;
        }
    }

    vector<Vertex> sortedVertices(vertices.size());
    for(auto s : vertices){
        sortedVertices[s.second]=s.first;
    }


    int vertex_number = vertices.size();
    int edge_number = edges.size();

    FILE* file;
    file = fopen(file_name, "w");

    fprintf(file, "# vtk DataFile Version 2.0\n\n");
    fprintf(file, "ASCII \n");
    fprintf(file, "DATASET UNSTRUCTURED_GRID\n\n");
    fprintf(file, "POINTS %d float\n", vertex_number);

    for(auto s : sortedVertices){
        fprintf(file, "%f %f %f\n", s.get_c(0), s.get_c(1), s.get_c(2));
    }
    fprintf(file, "\n\n");

    fprintf(file, "CELLS %d %d\n", edge_number, edge_number*3);

    for(auto s : edges){
        fprintf(file, "2 %d %d \n", vertices[s.first], vertices[s.second]);
    }
    fprintf(file, "\n");

    fprintf(file, "CELL_TYPES %d\n", edge_number);

    for(int i=0; i<edge_number; i++)
        fprintf(file, "%d ", 3);
    fprintf(file, "\n\n");


    fclose(file);

}


void FormanGradientVector::writeVTK_2cells(char* nome_file_output, vector<int> triangles){

    FILE* file;
    file = fopen(nome_file_output, "w");

    fprintf(file, "# vtk DataFile Version 2.0\n\n");
    fprintf(file, "ASCII \n\n");
    fprintf(file, "DATASET UNSTRUCTURED_GRID\n\n");
    fprintf(file, "POINTS %d float\n", mesh->get_vertices_num());

    for(int i=0; i<mesh->get_vertices_num(); i++)
        fprintf(file, "%f %f %f\n", mesh->get_vertex(i).get_c(0), mesh->get_vertex(i).get_c(1), mesh->get_vertex(i).get_c(2));
    fprintf(file, "\n\n");

    fprintf(file, "CELLS %d %d\n", mesh->get_triangles_num(), mesh->get_triangles_num()*4);

    for(int i=0; i<mesh->get_triangles_num(); i++)
        fprintf(file, "3 %d %d %d\n", mesh->get_triangle(i).TV(0), mesh->get_triangle(i).TV(1), mesh->get_triangle(i).TV(2));
    fprintf(file, "\n");

    fprintf(file, "CELL_TYPES %d\n", mesh->get_triangles_num());

    for(int i=0; i<mesh->get_triangles_num(); i++)
        fprintf(file, "%d ", 5);
    fprintf(file, "\n\n");


    fprintf(file, "POINT_DATA %d \n", mesh->get_vertices_num());
    fprintf(file, "FIELD FieldData 1\n");
    fprintf(file, "originalfield 1 %d float\n", mesh->get_vertices_num());

    for(int i=0; i<mesh->get_vertices_num(); i++)
        fprintf(file, "%f ", mesh->get_vertex(i).get_c(2));

    fprintf(file, "\n\n");


    fprintf(file, "CELL_DATA %d \n", mesh->get_triangles_num());
    fprintf(file, "FIELD FieldData 1\n");
    fprintf(file, "descending3cells 1 %d float\n", mesh->get_triangles_num());

    for(int i=0; i<mesh->get_triangles_num(); i++){
        fprintf(file, "%d ", triangles[i]);
    }
    fprintf(file, "\n");


    fclose(file);
}

void FormanGradientVector::writeVTK_2cells_on_vert(char* nome_file_output, vector<int> const& labels){


    FILE* file;
    file = fopen(nome_file_output, "w");

    fprintf(file, "# vtk DataFile Version 2.0\n\n");
    fprintf(file, "ASCII \n\n");
    fprintf(file, "DATASET UNSTRUCTURED_GRID\n\n");
    fprintf(file, "POINTS %d float\n", mesh->get_vertices_num());

    for(int i=0; i<mesh->get_vertices_num(); i++)
        fprintf(file, "%f %f %f\n", mesh->get_vertex(i).get_c(0), mesh->get_vertex(i).get_c(1), mesh->get_vertex(i).get_c(2));
    fprintf(file, "\n\n");

    fprintf(file, "CELLS %d %d\n", mesh->get_triangles_num(), mesh->get_triangles_num()*4);

    for(int i=0; i<mesh->get_triangles_num(); i++)
        fprintf(file, "3 %d %d %d\n", mesh->get_triangle(i).TV(0), mesh->get_triangle(i).TV(1), mesh->get_triangle(i).TV(2));
    fprintf(file, "\n");

    fprintf(file, "CELL_TYPES %d\n", mesh->get_triangles_num());

    for(int i=0; i<mesh->get_triangles_num(); i++)
        fprintf(file, "%d ", 5);
    fprintf(file, "\n\n");


    fprintf(file, "POINT_DATA %d \n", mesh->get_vertices_num());
    fprintf(file, "FIELD FieldData 2\n");
    fprintf(file, "originalfield 1 %d float\n", mesh->get_vertices_num());

    for(int i=0; i<mesh->get_vertices_num(); i++)
        fprintf(file, "%f ", mesh->get_vertex(i).get_c(2));

    fprintf(file, "\n");

    fprintf(file, "ascending 1 %d float\n", mesh->get_vertices_num());

    for(int i=0; i<mesh->get_vertices_num(); i++)
        fprintf(file, "%d ", labels[i]);

    fprintf(file, "\n");

    fclose(file);
}


void FormanGradientVector::writeVTK_gradient(char* nomeFile){

    vector<int> critical_vertexes = vector<int>(mesh->get_vertices_num(),-1);

    vector<vector<float> > new_vertexes_triangles;

    map<pair<int,int>, vector<float> > edges;

    for(int i=0; i<mesh->get_triangles_num(); i++){
        if(edges.find(pair<int,int>(mesh->get_triangle(i).TV(0), mesh->get_triangle(i).TV(1))) == edges.end() && edges.find(pair<int,int>(mesh->get_triangle(i).TV(1), mesh->get_triangle(i).TV(0))) == edges.end())
            edges[pair<int,int>(mesh->get_triangle(i).TV(0), mesh->get_triangle(i).TV(1))] = vector<float>();
        if(edges.find(pair<int,int>(mesh->get_triangle(i).TV(1), mesh->get_triangle(i).TV(2))) == edges.end() && edges.find(pair<int,int>(mesh->get_triangle(i).TV(2), mesh->get_triangle(i).TV(1))) == edges.end())
            edges[pair<int,int>(mesh->get_triangle(i).TV(1), mesh->get_triangle(i).TV(2))] = vector<float>();
        if(edges.find(pair<int,int>(mesh->get_triangle(i).TV(2), mesh->get_triangle(i).TV(0))) == edges.end() && edges.find(pair<int,int>(mesh->get_triangle(i).TV(0), mesh->get_triangle(i).TV(2))) == edges.end())
            edges[pair<int,int>(mesh->get_triangle(i).TV(2), mesh->get_triangle(i).TV(0))] = vector<float>();
    }

    for(map<pair<int,int>, vector<float> >::iterator it = edges.begin(); it != edges.end(); it++){

        float x = (mesh->get_vertex(it->first.first).get_c(0) + mesh->get_vertex(it->first.second).get_c(0))/2.0;
        float y = (mesh->get_vertex(it->first.first).get_c(1) + mesh->get_vertex(it->first.second).get_c(1))/2.0;
        float z = (mesh->get_vertex(it->first.first).get_c(2) + mesh->get_vertex(it->first.second).get_c(2))/2.0;

        vector<float> bar;
        bar.push_back(x);
        bar.push_back(y);
        bar.push_back(z);

        edges[it->first] = bar;
    }


    vector<vector<float> > tri_baricenter;

    for(int i=0; i<mesh->get_triangles_num(); i++){

        float x = (mesh->get_vertex(mesh->get_triangle(i).TV(0)).get_c(0) + mesh->get_vertex(mesh->get_triangle(i).TV(1)).get_c(0)+ mesh->get_vertex(mesh->get_triangle(i).TV(2)).get_c(0))/3.0;
        float y = (mesh->get_vertex(mesh->get_triangle(i).TV(0)).get_c(1) + mesh->get_vertex(mesh->get_triangle(i).TV(1)).get_c(1)+ mesh->get_vertex(mesh->get_triangle(i).TV(2)).get_c(1))/3.0;
        float z = (mesh->get_vertex(mesh->get_triangle(i).TV(0)).get_c(2) + mesh->get_vertex(mesh->get_triangle(i).TV(1)).get_c(2)+ mesh->get_vertex(mesh->get_triangle(i).TV(2)).get_c(2))/3.0;

        vector<float> bar;
        bar.push_back(x);
        bar.push_back(y);
        bar.push_back(z);

        tri_baricenter.push_back(bar);


        if(is_face_critical(i))
            new_vertexes_triangles.push_back(tri_baricenter[i]);
    }


    vector<vector<float> > vectors_gradient;
    for(int i=0; i<mesh->get_vertices_num(); i++ ){

        if(is_vertex_critical(i)){
            critical_vertexes[i] = 0;
        }

        vector<int> vert;
        vert.push_back(i);

        vector<float> vect;
        Edge* e = getVE(i);
        if(e != NULL){

            vector<int> edge;
            edge.push_back(e->EV(0));
            edge.push_back(e->EV(1));

            if(edges.find(pair<int,int>(edge[0], edge[1])) != edges.end()){

                vector<float> bar_edge = edges.find(pair<int,int>(edge[0], edge[1]))->second;
                vector<float> bar_point;
                bar_point.push_back(mesh->get_vertex(i).get_c(0));
                bar_point.push_back(mesh->get_vertex(i).get_c(1));
                bar_point.push_back(mesh->get_vertex(i).get_c(2));

                vect.push_back(bar_edge[0] - bar_point[0]);
                vect.push_back(bar_edge[1] - bar_point[1]);
                vect.push_back(bar_edge[2] - bar_point[2]);
            }
            else{

                vector<float> bar_edge = edges.find(pair<int,int>(edge[1], edge[0]))->second;
                vector<float> bar_point;
                bar_point.push_back(mesh->get_vertex(i).get_c(0));
                bar_point.push_back(mesh->get_vertex(i).get_c(1));
                bar_point.push_back(mesh->get_vertex(i).get_c(2));

                vect.push_back(bar_edge[0] - bar_point[0]);
                vect.push_back(bar_edge[1] - bar_point[1]);
                vect.push_back(bar_edge[2] - bar_point[2]);
            }

        }
        else{

            vect.push_back(0.0);
            vect.push_back(0.0);
            vect.push_back(0.0);
        }

        vectors_gradient.push_back(vect);
    }


    vector<vector<float> > new_vertexes;
    vector<vector<float> > new_vectors;
    vector<int> from_edges;
    for(map<pair<int,int>, vector<float> >::iterator it = edges.begin(); it != edges.end(); it++){

        vector<int> edge;
        edge.push_back(it->first.first);
        edge.push_back(it->first.second);

        edge = sort_simplex(&edge);
        int tri = getEF(new Edge(edge[0],edge[1]));
        if(tri != -1){
            vector<float> new_vert = it->second;

            int t_ind = tri;
            vector<float> vert_vector;

            new_vertexes.push_back(new_vert);

            vert_vector.push_back(tri_baricenter[t_ind][0] -new_vert[0]);
            vert_vector.push_back(tri_baricenter[t_ind][1] -new_vert[1]);
            vert_vector.push_back(tri_baricenter[t_ind][2] -new_vert[2]);

            new_vectors.push_back(vert_vector);

            from_edges.push_back(-1);
        }
        else{

            if(is_edge_critical(edge[0], edge[1])){

                vector<float> new_vert = it->second;
                new_vertexes.push_back(new_vert);

                from_edges.push_back(1);
                vector<float> vert_vector;

                vert_vector.push_back(0);
                vert_vector.push_back(0);
                vert_vector.push_back(0);

                new_vectors.push_back(vert_vector);
            }
        }
    }

    FILE* file;
    file = fopen(nomeFile, "w");

    int vertex_number = mesh->get_vertices_num()+new_vertexes.size()+new_vertexes_triangles.size();
    int triangles = mesh->get_triangles_num();

    fprintf(file, "# vtk DataFile Version 2.0\n\n");
    fprintf(file, "ASCII \n");
    fprintf(file, "DATASET UNSTRUCTURED_GRID\n\n");
    fprintf(file, "POINTS %d float\n", vertex_number);

    for(int i=0; i<mesh->get_vertices_num(); i++){
            fprintf(file, "%f %f %f\n", mesh->get_vertex(i).get_c(0), mesh->get_vertex(i).get_c(1), mesh->get_vertex(i).get_c(2));
    }
    for(int i=0; i<new_vertexes.size(); i++){
        fprintf(file, "%f %f %f\n", new_vertexes[i][0], new_vertexes[i][1], new_vertexes[i][2]);
    }
    for(int i=0; i<new_vertexes_triangles.size(); i++){
        fprintf(file, "%f %f %f\n", new_vertexes_triangles[i][0], new_vertexes_triangles[i][1], new_vertexes_triangles[i][2]);
    }
    fprintf(file, "\n\n");

    fprintf(file, "CELLS %d %d\n", triangles, triangles*4);

    for(int i=0; i<mesh->get_triangles_num(); i++){
        fprintf(file, "3 %d %d %d \n", mesh->get_triangle(i).TV(0), mesh->get_triangle(i).TV(1), mesh->get_triangle(i).TV(2));
    }
    fprintf(file, "\n");

    fprintf(file, "CELL_TYPES %d\n", triangles);

    for(int i=0; i<triangles; i++)
        fprintf(file, "%d ", 5);
    fprintf(file, "\n\n");


    fprintf(file, "POINT_DATA %d \n", vertex_number);
    fprintf(file, "VECTORS vector float\n");

    for(int i=0; i<mesh->get_vertices_num(); i++){
        fprintf(file, "%f %f %f   ", vectors_gradient[i][0], vectors_gradient[i][1], vectors_gradient[i][2]);
    }
    for(int i=0; i<new_vectors.size(); i++){
        fprintf(file, "%f %f %f   ", new_vectors[i][0], new_vectors[i][1], new_vectors[i][2]);
    }
    for(int i=0; i<new_vertexes_triangles.size(); i++){
        fprintf(file, "%f %f %f   ", 0, 0, 0);
    }
    fprintf(file, "\n\n");

    fprintf(file, "FIELD FieldData 1\n");
    fprintf(file, "critical 1 %d int\n", vertex_number);

    for(int i=0; i<mesh->get_vertices_num(); i++){
        fprintf(file, "%d ", critical_vertexes[i]);
    }
    for(int i=0; i<from_edges.size(); i++){
        fprintf(file, "%d ", from_edges[i]);
    }
    for(int i=0; i<new_vertexes_triangles.size(); i++){
        fprintf(file, "%d ", 2);
    }
    fprintf(file, "\n\n");


    fclose(file);

}


void FormanGradientVector::writeVTK_criticalPoints(char* nomeFile){

    FILE* file;
    file = fopen(nomeFile, "w");

    vector<int> cp = count_critical_simplexes();
    int numC = cp[0] + cp[1] + cp[2];

    vector<int> types(numC);

    fprintf(file, "# vtk DataFile Version 2.0\n\n");
    fprintf(file, "ASCII \n");
    fprintf(file, "DATASET UNSTRUCTURED_GRID\n\n");
    fprintf(file, "POINTS %d float\n", numC);

    int critCheck=0;
    for(int i=0; i<mesh->get_triangles_num(); i++){
        if(is_face_critical(i)){
            Vertex v1 = mesh->get_vertex(mesh->get_triangle(i).TV(0));
            Vertex v2 = mesh->get_vertex(mesh->get_triangle(i).TV(1));
            Vertex v3 = mesh->get_vertex(mesh->get_triangle(i).TV(2));
            fprintf(file, "%f %f %f \n", (v1.get_c(0)+v2.get_c(0)+v3.get_c(0))/3.0, (v1.get_c(1)+v2.get_c(1)+v3.get_c(1))/3.0, (v1.get_c(2)+v2.get_c(2)+v3.get_c(2))/3.0);
            types[critCheck++]=2;
        }
    }

    for(int i=0; i<mesh->get_vertices_num(); i++){
        if(is_vertex_critical(i)){
            fprintf(file, "%f %f %f \n", mesh->get_vertex(i).get_c(0), mesh->get_vertex(i).get_c(1), mesh->get_vertex(i).get_c(2));
            types[critCheck++]=0;
        }

        vector<int> vv = mesh->VV(i);
        for(auto v : vv){
            if(v < i){
                if(is_edge_critical(v,i)){
                    Vertex v1 = mesh->get_vertex(i);
                    Vertex v2 = mesh->get_vertex(v);
                    fprintf(file, "%f %f %f \n", (v1.get_c(0)+v2.get_c(0))/2.0, (v1.get_c(1)+v2.get_c(1))/2.0, (v1.get_c(2)+v2.get_c(2))/2.0);
                    types[critCheck++]=1;
                }
            }
        }
    }

    fprintf(file, "POINT_DATA %d \n", numC);
    fprintf(file, "FIELD FieldData 1\n");
    fprintf(file, "critical 1 %d int\n", numC);

    for(int i=0; i<critCheck; i++){
        fprintf(file, "%d ", types[i]);
    }

    fprintf(file, "\n\n");


    fclose(file);
}
