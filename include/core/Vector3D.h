#ifndef PHYSICS_ENGINE_VECTOR3D_H
#define PHYSICS_ENGINE_VECTOR3D_H

#include <math.h>

class Vector3D
{
    public:

        float _x;

        float _y;

        float _z;

        Vector3D();

        Vector3D(float x, float y, float z);

        Vector3D(const Vector3D &v);

        Vector3D operator+(const Vector3D& v);

        Vector3D&operator+=(const Vector3D &v);

        Vector3D operator-(const Vector3D &v);

        Vector3D&operator-=(const Vector3D &v);

        Vector3D operator-();

        float operator*(const Vector3D &v);

        Vector3D operator*(const float scalar);

        Vector3D&operator*=(const float scalar);

        Vector3D operator/(const float scalar);

        Vector3D operator/=(const float scalar);

        Vector3D cross(const Vector3D& v);

        float magnitude();

        float magnitudeSquared();
};

#endif //PHYSICS_ENGINE_VECTOR3D_H
