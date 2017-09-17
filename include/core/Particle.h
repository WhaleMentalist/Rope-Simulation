#ifndef PHYSICS_ENGINE_PARTICLE_H
#define PHYSICS_ENGINE_PARTICLE_H

#include<iostream>

#include "PNode.h"

class Particle : public PNode
{
    public:

        Particle(float mass);

        Particle(float mass, Vector3D position, Vector3D velocity, Vector3D force);

        Particle(const Particle& p);

        ~Particle();

        Vector3D getVelocity() override;

        void applyForce(const Vector3D force) override;

        void simulate(float deltaTime) override;

        void print();

    protected:

        Vector3D* _velocity;

        Vector3D* _force;

};

#endif //PHYSICS_ENGINE_PARTICLE_H
