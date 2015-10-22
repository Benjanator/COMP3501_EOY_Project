#include "SmallShip.h"


SmallShip::SmallShip(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
	this->type = smallAlly_fighter;
	velocity = Ogre::Vector3::ZERO;
	m_pNode = newShip;

}


SmallShip::~SmallShip(void)
{
}

void SmallShip::accelerate(int _abs)
{
	if(_abs > 0){
		velocity.z += accel_Rate;
	}
	else if(_abs < 0){
		velocity.z -= accel_Rate;
	}
}

void SmallShip::verticalThrust(int _abs)
{

}

void SmallShip::horizontalThrust(int _abs)
{
}

void SmallShip::pitch(int _abs)
{
}

void SmallShip::yaw(int _abs)
{
}

void SmallShip::roll(int _abs)
{
}

void SmallShip::update(void)
{
	move();
}

void SmallShip::move(void)
{
	m_pNode->translate(m_pNode->_getDerivedOrientation()*Ogre::Vector3::NEGATIVE_UNIT_Z * velocity.z);
	m_pNode->translate(up*velocity.y);
	m_pNode->translate(direction.crossProduct(up) * velocity.z);
}
