#include<math.h>
#include<vector>

using namespace std;

struct Vector3D {
    double x, y, z;

    // Basic vector operators
    Vector3D(){x = 0; y = 0; z = 0;}
    Vector3D(double x_n, double y_n, double z_n) {x = x_n; y = y_n; z = z_n;}
    void set(Vector3D v){x = v.x; y = v.y; z = v.z;}
    Vector3D operator/ (double n) {return Vector3D(x / n, y / n, z / n);}
    void operator/= (double n) {x /= n; y /= n; z /= n;}
    Vector3D operator* (double n) {return Vector3D(x * n, y * n, z * n);}
    void operator*= (double n) {x *= n; y *= n; z *= n;}
    Vector3D operator+ (Vector3D v) {return Vector3D(x + v.x, y + v.y, z + v.z);}
    void operator+= (Vector3D v) {x += v.x; y += v.y; z += v.z;}
    Vector3D operator- (Vector3D v) {return Vector3D(x - v.x, y - v.y, z - v.z);}
    void operator-=(Vector3D v) {x -= v.x; y -= v.y; z -= v.z;}

    // Vector length
    double length() {return sqrt(x * x + y * y + z * z);}

    // Vector normalization
    Vector3D normalized () {return *this / length();}
    void normalize() {x /= length(); y /= length(); z /= length();}

    // DOT&CROSS vector product
    double operator* (Vector3D v) {return (x * v.x + y * v.y + z * v.z);}
    Vector3D operator^ (Vector3D v) {return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);}

    // Grow&Shrink the vector
    Vector3D operator+ (double n) {return *this + normalized() * n;}
    void operator+= (double n) {this->set(*this + normalized() * n);}
    Vector3D operator- (double n) {return *this - normalized() * n;}
    void operator-= (double n) {this->set(*this - normalized() * n);}

    vector<double> as_vector() {return vector<double>{x, y, z};}
};