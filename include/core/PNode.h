#ifndef PHYSICS_ENGINE_PNODE_H
#define PHYSICS_ENGINE_PNODE_H

#include "../../include/core/Vector3D.h"

class PNode
{
    public:

        virtual void applyForce(const Vector3D force) = 0;

        virtual void simulate(float deltaTime) = 0;

        Vector3D getPosition();

        Vector3D getVelocity();

        void lock();

        void unlock();

    protected:

        float _inverseMass;

        Vector3D _position;

        Vector3D _previousPosition;

        Vector3D _velocity;

        Vector3D _force;

        bool _isLocked;
};

#endif //PHYSICS_ENGINE_PNODE_H
