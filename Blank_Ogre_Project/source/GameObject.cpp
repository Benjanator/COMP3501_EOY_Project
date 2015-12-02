#include "GameObject.h"


GameObject::GameObject(objectType _type)
{
	type = _type;
	dead = false;
}


GameObject::~GameObject(void)
{
	m_pNode = 0;
}

Ogre::SceneNode& GameObject::getNode()
{
	return *m_pNode;
}

Ogre::Vector3 GameObject::getMotionDirection()
{
	return drift_Direction;
}

bool GameObject::isIndestructable()
{
	return indestructable;
}

bool GameObject::isDead()
{
	return dead;
}

int GameObject::getTeam()
{
	return team;
}

void GameObject::setTeam(int _team)
{
	team = _team;
}

GameObject::objectType GameObject::getType()
{
	return type;
}

Ogre::Vector3 GameObject::getAABBCenter()
{
	if(type == objectType::smallAlly_fighter){
		return m_pNode->_getDerivedPosition() + aabbCenter;
	}
	else{
		return m_pNode->_getWorldAABB().getCenter();
	}
}

Ogre::Vector3 GameObject::getAABBSize()
{
	if(type == objectType::smallAlly_fighter){
		return aabbSize;
	}
	else{
		return m_pNode->_getWorldAABB().getSize();
	}
}