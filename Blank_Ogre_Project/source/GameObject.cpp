#include "GameObject.h"


GameObject::GameObject(objectType _type)
{
	type = _type;
}


GameObject::~GameObject(void)
{
}

Ogre::Vector3 GameObject::getMotionDirection()
{
	return drift_Direction;
}

bool GameObject::isIndestructable()
{
	return indestructable;
}

int GameObject::getTeam()
{
	return team;
}

void GameObject::setTeam(int _team)
{
	team = _team;
}

Ogre::Vector3 GameObject::getAABBCenter()
{
	return m_pNode->_getDerivedPosition() + aabbCenter;
}

Ogre::Vector3 GameObject::getAABBSize()
{
	return aabbSize;
}