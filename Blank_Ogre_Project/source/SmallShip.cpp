#include "SmallShip.h"


SmallShip::SmallShip(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
	this->type = smallAlly_fighter;
	velocity = Ogre::Vector3(0.0f, 0.0f, 0.1f);//Ogre::Vector3::ZERO;
	
	direction = newShip->_getDerivedOrientation() * Ogre::Vector3(0.0f, 0.0f, -1.0f);
	drift_Direction = direction;
	up = newShip->_getDerivedOrientation() * Ogre::Vector3(0.0f, 1.0f, 0.0f);
	right = direction.crossProduct(up);

	m_pNode = newShip;

	accel_Rate = 0.01;


	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);

}


SmallShip::~SmallShip(void)
{
}

Ogre::SceneNode& SmallShip::getNode()
{
	return *m_pNode;
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

void SmallShip::fullStop()
{
	drift_Direction = Ogre::Vector3(0.0f);
}

void SmallShip::verticalThrust(int _abs)
{
	if(_abs > 0){
		velocity.y += accel_Rate;
	}
	else if(_abs < 0){
		velocity.y -= accel_Rate;
	}
}

void SmallShip::horizontalThrust(int _abs)
{
	if(_abs > 0){
		velocity.x += accel_Rate;
	}
	else if(_abs < 0){
		velocity.x -= accel_Rate;
	}
}

void SmallShip::pitch(Ogre::Radian _pitch)
{
	m_pNode->pitch(_pitch);
	m_pNode->needUpdate();
}

void SmallShip::yaw(Ogre::Radian _yaw)
{
	m_pNode->yaw(_yaw);
	m_pNode->needUpdate();
}

void SmallShip::roll(Ogre::Quaternion _rot)
{
	m_pNode->rotate(_rot);
	m_pNode->needUpdate();
}

void SmallShip::translate(Ogre::Vector3 _up, Ogre::Vector3 _right, Ogre::Vector3 _forward)
{
	if(!_up.isZeroLength()){
		up = _up;
		drift_Direction += _up * accel_Rate;
	}
	if(!_right.isZeroLength()){
		right = _right;
		drift_Direction += _right * accel_Rate;
	}
	if(!_forward.isZeroLength()){
		direction = _forward;
		drift_Direction += _forward * accel_Rate;
	}
	
	m_pNode->needUpdate();
}

void SmallShip::update(void)
{
	move();
}

void SmallShip::move(void)
{
	m_pNode->translate(drift_Direction);
	
	m_pNode->needUpdate();
	
}

