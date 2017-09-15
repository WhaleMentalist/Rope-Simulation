#ifndef PHYSICS_ENGINE_SPRING_H
#define PHYSICS_ENGINE_SPRING_H

#include "PNode.h"
#include "Particle.h"

class Spring : public PNode
{
    public:

        Spring(float stiffness, float dampening, float restLength,
                Particle p1, Particle p2);

        virtual void simulate(float deltaTime) override;

        virtual void applyForce(Vector3D force) override;

        void print();

    private:

        virtual void solve();

        float _k;

        float _kd;

        float _restLength;

        Particle* _endPointOne;

        Particle* _endPointTwo;
};

#endif //PHYSICS_ENGINE_SPRING_H
