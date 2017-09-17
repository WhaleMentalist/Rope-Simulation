#include "../../include/core/Particle.h"

Particle::Particle(float mass)
{
    _inverseMass = 1.0f / mass;
    _position = new Vector3D(0.0f, 0.0f, 0.0f);
    _velocity = new Vector3D(0.0f, 0.0f, 0.0f);
    _force = new Vector3D(0.0f, 0.0f, 0.0f);
    _isLocked = false;
}

Particle::Particle(float mass, Vector3D position, Vector3D velocity, Vector3D force)
{
    _inverseMass = 1.0f / mass;
    _position = new Vector3D(position);
    _velocity = new Vector3D(velocity);
    _force = new Vector3D(force);
    _isLocked = false;
}

Particle::Particle(const Particle& p)
{
    _inverseMass = p._inverseMass;
    _position = new Vector3D(*(p._position));
    _velocity = new Vector3D(*(p._velocity));
    _force = new Vector3D(*(p._force));
    _isLocked = false;
}

Particle::~Particle()
{
    delete _velocity;
    delete _force;
    delete _position;
}

Vector3D Particle::getVelocity()
{
    return *(_velocity);
}

void Particle::applyForce(const Vector3D force)
{
    if(!_isLocked)
    {
        *(_force) += force; // Simply add to the current force
    }
}

void Particle::simulate(float deltaTime)
{
    if(!_isLocked)
    {
        Vector3D acceleration = *(_force) * _inverseMass; // Acceleration = Force / Mass
        *(_velocity) += acceleration * deltaTime; // Add the affects of acceleration during time step
        *(_position) += *(_velocity) * deltaTime; // Add the affects of the velocity during time step

        /*
         * Zero the force after simulation step
         */
        _force->_x = 0.0f;
        _force->_y = 0.0f;
        _force->_z = 0.0f;
    }
}

void Particle::print()
{
    std::cout << "Position: " << _position->_x <<  ", " << _position->_y << ", " << _position->_z << "\n";
    std::cout << "Velocity: " << _velocity->_x << ", " << _velocity->_y << ", " << _velocity->_z << "\n";
}