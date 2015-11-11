#include "Fighter.h"

Fighter::Fighter(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
		m_pNode = newShip;
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
