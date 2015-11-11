#include "Rocket.h"


Rocket::Rocket(Ogre::SceneNode * newRocket):GameObject(GameObject::empty)
{
	
	m_pNode = newRocket;


}


Rocket::~Rocket(void)
{
}

void Rocket::fly(){

}

void Rocket::collide(){

}

void Rocket::explode(){

}

Ogre::SceneNode& Rocket::getNode()
{
	return *m_pNode;
}

void Rocket::update(void)
{

}