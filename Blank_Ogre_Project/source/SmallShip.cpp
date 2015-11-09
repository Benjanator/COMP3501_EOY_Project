#include "SmallShip.h"


SmallShip::SmallShip(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
	this->type = smallAlly_fighter;
	velocity = Ogre::Vector3(0.0f, 0.0f, 0.1f);//Ogre::Vector3::ZERO;
	
	direction = newShip->_getDerivedOrientation() * Ogre::Vector3(0.0f, 0.0f, -1.0f);
	up = newShip->_getDerivedOrientation() * Ogre::Vector3(0.0f, 1.0f, 0.0f);
	right = direction.crossProduct(up);
	
	m_pNode = newShip;

	accel_Rate = 0.01;

}


SmallShip::~SmallShip(void)
{
}

void SmallShip::setTeam(int _team)
{
	team = _team;
}

int SmallShip::getTeam()
{
	return team;
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
	velocity = Ogre::Vector3(0.0f);
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
	}
	if(!_right.isZeroLength()){
		right = _right;
	}
	if(!_forward.isZeroLength()){
		direction = _forward;
	}

	m_pNode->needUpdate();
}

void SmallShip::update(void)
{
	move();
}

void SmallShip::move(void)
{
	//m_pNode->translate(direction * velocity.z);
	//m_pNode->translate(up*velocity.y);
	//m_pNode->translate(right * velocity.x);

	m_pNode->translate((direction * velocity.z)+(up*velocity.y)+(right * velocity.x)); //combining translations seems to remove inconsistnecies
	//multiple translate calls can give us controls that dont move the way we would expect due to order motion
	m_pNode->needUpdate();
	
}
