#ifndef PHYSICS_ENGINE_PNODE_H
#define PHYSICS_ENGINE_PNODE_H

#include "../../include/core/Vector3D.h"

class PNode
{
    public:

        virtual void applyForce(const Vector3D force) = 0;

        virtual void simulate(float deltaTime) = 0;

    protected:

        float _inverseMass;

        Vector3D* _position;
};

#endif //PHYSICS_ENGINE_PNODE_H
