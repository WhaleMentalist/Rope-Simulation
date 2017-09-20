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

        void applyForce(const Vector3D force) override;

        void simulate(float deltaTime) override;

    protected:

};

#endif //PHYSICS_ENGINE_PARTICLE_H
