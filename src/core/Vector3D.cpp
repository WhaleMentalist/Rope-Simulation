#include "../../include/core/Vector3D.h"

Vector3D::Vector3D()
{
    _x = 0.0f;
    _y = 0.0f;
    _z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z)
{
    _x = x;
    _y = y;
    _z = z;
}

Vector3D::Vector3D(const Vector3D &v)
{
    _x = v._x;
    _y = v._y;
    _z = v._z;
}

Vector3D &Vector3D::operator+=(const Vector3D &v)
{
    _x += v._x;
    _y += v._y;
    _z += v._z;
    return *this;
}

Vector3D &Vector3D::operator-=(const Vector3D &v)
{
    _x -= v._x;
    _y -= v._y;
    _z -= v._z;
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D &v)
{
    return Vector3D(_x + v._x, _y + v._y, _z + v._z);
}

Vector3D Vector3D::operator-(const Vector3D &v)
{
    return Vector3D(_x - v._x, _y - v._y, _z - v._z);
}

Vector3D Vector3D::operator-()
{
    return Vector3D(-_x, -_y, -_z);
}

float Vector3D::operator*(const Vector3D &v)
{
    return _x * v._x + _y *v._y + _z * v._z;
}

Vector3D Vector3D::operator*(const float scalar)
{
    return Vector3D(scalar * _x, scalar * _y, scalar * _z);
}

Vector3D &Vector3D::operator*=(const float scalar)
{
    _x *= scalar;
    _y *= scalar;
    _z *= scalar;
    return *this;
}

Vector3D Vector3D::operator/(const float scalar)
{
    return Vector3D(_x / scalar, _y / scalar, _z / scalar);
}

Vector3D Vector3D::operator/=(const float scalar)
{
    _x /= scalar;
    _y /= scalar;
    _z /= scalar;
}

Vector3D Vector3D::cross(const Vector3D &v)
{
    return Vector3D(_y * v._z - _z * v._y,
                    _z * v._x - _x * v._z,
                    _x * v._y - _y * v._x);
}

float Vector3D::magnitude()
{
    return sqrtf(_x * _x + _y * _y + _z * _z);
}

float Vector3D::magnitudeSquared()
{
    return _x * _x + _y * _y + _z * _z;
}
