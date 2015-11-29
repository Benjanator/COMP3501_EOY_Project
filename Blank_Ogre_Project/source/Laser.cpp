#include "Laser.h"


Laser::Laser(Ogre::SceneNode * newLaser,Ogre::Quaternion shipOrientation,Ogre::Vector3 shipPosition, bool lr):GameObject(GameObject::empty)
{
	
	m_pNode = newLaser;
	//m_pNode->setPosition(shipPosition + Ogre::Vector3(0,0,-2));
	m_pNode->setOrientation(shipOrientation);
	forward_Direction = shipOrientation *  Ogre::Vector3::NEGATIVE_UNIT_Z;
	Ogre::Vector3 left_Direction = shipOrientation *  Ogre::Vector3::NEGATIVE_UNIT_X;
	Ogre::Vector3 right_Direction = shipOrientation *  Ogre::Vector3::UNIT_X;
	Ogre::Vector3 down_Direction = shipOrientation *  Ogre::Vector3::NEGATIVE_UNIT_Y;

	if(lr){
		m_pNode->setPosition(shipPosition + (forward_Direction *12) + (left_Direction * 1.2) + (down_Direction*0.6));
	}else{
		m_pNode->setPosition(shipPosition + (forward_Direction *12) + (right_Direction * 1.2) + (down_Direction*0.6));
	}
	hasExploded = false;
	accel_Rate = 0.15;
	drift_Direction = Ogre::Vector3(0.0f);
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);
	numMaterials = 1;
}


Laser::~Laser(void)
{
}

void Laser::update(float _timer)
{
	move();
}

void Laser::move(){

	drift_Direction = drift_Direction += forward_Direction * accel_Rate;
	m_pNode->translate(drift_Direction);
	m_pNode->needUpdate();
}

void Laser::collide(){
	//add these for anything that could collide
	m_pNode->setVisible(false);
	//std::cout << "HIT " << std::endl;
}

void Laser::particle(){
	//add these for anything that could collide
}


Ogre::SceneNode& Laser::getNode()
{
	return *m_pNode;
}