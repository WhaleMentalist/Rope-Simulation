#include "../../include/core/PNode.h"

Vector3D PNode::getPosition()
{
    return _position;
}

Vector3D PNode::getVelocity()
{
    return _velocity;
}

void PNode::lock()
{
    _isLocked = true;
}

void PNode::unlock()
{
    _isLocked = false;
}