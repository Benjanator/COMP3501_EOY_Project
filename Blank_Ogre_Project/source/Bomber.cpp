#include "Bomber.h"


Bomber::Bomber(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
		m_pNode = newShip;

}


Bomber::~Bomber(void)
{
}

Ogre::SceneNode& Bomber::getNode()
{
	return *m_pNode;
}

void Bomber::update(void)
{
	move();
}

void Bomber::move(void)
{

	
}
