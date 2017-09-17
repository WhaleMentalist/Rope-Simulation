#include "../../include/core/PNode.h"

Vector3D PNode::getPosition()
{
    return *(_position);
}

void PNode::lock()
{
    _isLocked = true;
}

void PNode::unlock()
{
    _isLocked = false;
}