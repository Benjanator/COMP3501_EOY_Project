#include "Carrier.h"


Carrier::Carrier(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
		m_pNode = newShip;
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
