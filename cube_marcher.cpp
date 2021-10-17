#include<vector>
#include"marching_table.cpp"
#include"v3d.cpp"

using namespace std;

vector<pair<int, int>> edge_codes = {
{0, 1}, {1, 2}, {2, 3}, {3, 0}, 
{4, 5}, {5, 6}, {6, 7}, {7, 4},
{0, 4}, {1, 5}, {2, 6}, {3, 7}};
vector<vector<int>> cube_vertices = {
{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}, 
{0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}};


vector<int> cube2edges(vector<vector<vector<double>>> &field, int x, int y, int z) {
    int cube_id = 0;
    for (int i = 0 ; i < cube_vertices.size(); i++) {
        vector<int> shift = cube_vertices[i];
        if (field[x + shift[0]][y + shift[1]][z + shift[2]] > 0) cube_id += (1 << i);
    }
    return marching_table[cube_id];
}

Vector3D interpolate(Vector3D a, Vector3D b, double alpha, double beta) {
    //cout << a.x << ' ' << a.y << ' ' << a.z << endl;
    if (alpha == beta) return a;
    return a + (b - a) * (alpha / (alpha - beta));
}

void field2mesh(vector<vector<vector<double>>> &field, vector<vector<double>> &vertices, vector<vector<int>> &faces) {
    for (int i = 0; i < field.size() - 1; i++) {
        for (int j = 0; j < field[i].size() - 1; j++) {
            for (int h = 0; h < field[i][j].size() - 1; h++) {
                //cout << i << ' ' << j << ' ' << h << endl;
                vector<int> used_edges = cube2edges(field, i, j, h);
                //cout << used_edges.size() << endl
                vector<int> united_faces;
                for (int code : used_edges) {
                    if (code == -1) break;
                    Vector3D a(
                        i + cube_vertices[edge_codes[code].first][0], 
                        j + cube_vertices[edge_codes[code].first][1], 
                        h + cube_vertices[edge_codes[code].first][2]);
                    Vector3D b(
                        i + cube_vertices[edge_codes[code].second][0], 
                        j + cube_vertices[edge_codes[code].second][1], 
                        h + cube_vertices[edge_codes[code].second][2]);
                    double alpha = field[round(a.x)][round(a.y)][round(a.z)];
                    double beta = field[round(b.x)][round(b.y)][round(b.z)];
                    united_faces.push_back(vertices.size());
                    vertices.push_back(interpolate(a, b, alpha, beta).as_vector());
                    //cout << "Pushed" << endl;
                }
                for (int i = 0; i < united_faces.size(); i += 3) {
                    faces.push_back({united_faces[i + 0], united_faces[i + 1], united_faces[i + 2]});
                }
            }
        }
    }
}