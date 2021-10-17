#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include "cube_marcher.cpp"

using namespace std;

const int FIELD_SIZE = 100;
vector<vector<vector<double>>> field(FIELD_SIZE, vector<vector<double>>(FIELD_SIZE, vector<double>(FIELD_SIZE, -1)));

int main() {
    ios::sync_with_stdio(false);
    cout.tie(0);

    freopen("out.obj", "w", stdout);

    Vector3D centre = *new Vector3D(FIELD_SIZE, FIELD_SIZE, FIELD_SIZE) / 2;
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            for (int h = 0; h < FIELD_SIZE; h++) {
                field[i][j][h] = 2.5 * (Vector3D(i, j, h) - centre).length() / FIELD_SIZE - 1;
            }
        }
    }

    vector<vector<double>> vertices;
    vector<vector<int>> faces;
    field2mesh(field, vertices, faces);
    cout << fixed << setprecision(10);
    
    for (int i = 0; i < vertices.size(); i++) {
        cout << "v " << vertices[i][0] << ' ' << vertices[i][1] << ' ' << vertices[i][2] << '\n';
    }
    for (int i = 0; i < faces.size(); i++) {
        cout << "f " << faces[i][0] + 1 << ' ' << faces[i][1] + 1 << ' ' << faces[i][2] + 1 << '\n';
    }
}