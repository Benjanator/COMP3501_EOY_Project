#include "Fighter.h"

Fighter::Fighter(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
		m_pNode = newShip;
		
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);
}


Fighter::~Fighter(void)
{
}

Ogre::SceneNode& Fighter::getNode()
{
	return *m_pNode;
}

void Fighter::update(void)
{
	move();
}

void Fighter::move(void)
{
	
	
}
