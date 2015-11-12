#include "Carrier.h"


Carrier::Carrier(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
		m_pNode = newShip;
		
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);
}


Carrier::~Carrier(void)
{
}

Ogre::SceneNode& Carrier::getNode()
{
	return *m_pNode;
}

void Carrier::update(void)
{
	move();
}

void Carrier::move(void)
{
	
	
}
