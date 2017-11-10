#include "../../include/core/Particle.h"

Particle::Particle(float mass)
{
    _inverseMass = 1.0f / mass;
    _position =  Vector3D(0.0f, 0.0f, 0.0f);
    _previousPosition = _position;
    _velocity =  Vector3D(0.0f, 0.0f, 0.0f);
    _force =  Vector3D(0.0f, 0.0f, 0.0f);
    _isLocked = false;
}

Particle::Particle(float mass, Vector3D position, Vector3D velocity, Vector3D force)
{
    _inverseMass = 1.0f / mass;
    _position =  position;
    _previousPosition = _position;
    _velocity =  velocity;
    _force =  force;
    _isLocked = false;
}

Particle::Particle(const Particle& p)
{
    _inverseMass = p._inverseMass;
    _position = Vector3D(p._position);
    _velocity = Vector3D(p._velocity);
    _force = Vector3D(p._force);
    _isLocked = false;
}

Particle::~Particle()
{
    ;
}

void Particle::applyForce(const Vector3D force)
{
    if(!_isLocked)
    {
        _force += force; // Simply add to the current force
    }
}

void Particle::simulate(float deltaTime)
{
    if(!_isLocked)
    {
        Vector3D acceleration = _force * _inverseMass; // Acceleration = Force / Mass
        _velocity = _position - _previousPosition;
        _previousPosition = _position;
        _position = _position + _velocity * 0.995f + (acceleration * deltaTime * deltaTime);

        /*
         * Zero the force after simulation step
         */
        _force._x = 0.0f;
        _force._y = 0.0f;
        _force._z = 0.0f;
    }
}