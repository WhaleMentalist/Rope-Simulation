#include "../../include/core/Spring.h"

Spring::Spring(float stiffness, float dampening, float restLength, Particle p1, Particle p2)
{
    _k = stiffness;
    _kd = dampening;
    _restLength = restLength;
    _endPointOne = new Particle(p1);
    _endPointTwo = new Particle(p2);
}

void Spring::simulate(float deltaTime)
{
    solve();
    _endPointOne->simulate(deltaTime);
    _endPointTwo->simulate(deltaTime);
}

void Spring::applyForce(Vector3D force)
{

}

void Spring::print()
{
    std::cout << "First mass: " << "\n";
    _endPointOne->print();
    std::cout << "Second mass: " << "\n";
    _endPointTwo->print();
}

void Spring::solve()
{
    /*
     * Need to check if particles are locked or have infinite mass...
     */

    Vector3D displacement = _endPointOne->getPosition() - _endPointTwo->getPosition();
    float displacementMag = displacement.magnitude(); // Get magnitude via 'sqrt' of sum of components squared

    Vector3D force;

    if(displacementMag != 0.0f) // Need better way to compare 'float'
    {
        force += -(displacement / displacementMag) * (displacementMag - _restLength) * _k;
        force += -(_endPointOne->getVelocity() - _endPointTwo->getVelocity()) * _kd;
        _endPointOne->applyForce(force);
        _endPointTwo->applyForce(-force);
    }
}
