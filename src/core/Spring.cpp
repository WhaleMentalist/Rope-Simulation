#include<iostream>

#include "../../include/core/Spring.h"

Spring::Spring(float stiffness, float dampening, float restLength, PNode* p1, PNode* p2)
{
    _k = stiffness;
    _kd = dampening;
    _restLength = restLength;
    _endPoints[0] = p1;
    _endPoints[1] = p2;
}

void Spring::simulate(float deltaTime)
{
    solve();
    _endPoints[0]->simulate(deltaTime);
    _endPoints[1]->simulate(deltaTime);
}

void Spring::solve()
{
    // Get distance between two end points and the magnitude squared
    Vector3D endPointDistVector = _endPoints[0]->getPosition() - _endPoints[1]->getPosition();
    float endPointDistMag = endPointDistVector.magnitude(); // TODO: Could do first order taylor series approx of 'sqrt'
    Vector3D endPointDistNorm = endPointDistVector / endPointDistMag;

    Vector3D force;

    if(endPointDistMag != 0.0f)
    {
        force += -(endPointDistNorm * (endPointDistMag - _restLength)) * _k; // Spring force
        force +=  endPointDistNorm *
                (endPointDistNorm * (_endPoints[0]->getVelocity() - _endPoints[1]->getVelocity())) * -_kd; // Dampening
    }

    _endPoints[0]->applyForce(force);
    _endPoints[1]->applyForce(-force);
}
