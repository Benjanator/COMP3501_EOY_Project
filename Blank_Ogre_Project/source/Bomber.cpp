#include "Bomber.h"


Bomber::Bomber(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
		m_pNode = newShip;
		
	hasExploded = false;
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);

}


Bomber::~Bomber(void)
{
}

Ogre::SceneNode& Bomber::getNode()
{
	return *m_pNode;
}

void Bomber::update(float _timer)
{
	move();
}

void Bomber::collide(){
	
}

void Bomber::move(void)
{

	
}

