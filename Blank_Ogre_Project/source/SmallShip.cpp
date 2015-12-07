#include "SmallShip.h"


SmallShip::SmallShip(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
	this->type = smallAlly_fighter;

	velocity = Ogre::Vector3(0.0f, 0.0f, 0.1f);//Ogre::Vector3::ZERO;
	
	direction = newShip->_getDerivedOrientation() * Ogre::Vector3(0.0f, 0.0f, -1.0f);

	drift_Direction = Ogre::Vector3(0.0f);
	up = newShip->_getDerivedOrientation() * Ogre::Vector3(0.0f, 1.0f, 0.0f);
	right = direction.crossProduct(up);

	m_pNode = newShip;
	accel_Rate = 0.01;
	hasExploded = false;
	personalTimer = 0;

	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);
	numMaterials = 4;
	health = 50;
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

void SmallShip::update(float timer_,ObjectManager* manager)
{
	Ogre::MaterialPtr mat;
	
	Ogre::Node* radar = m_pNode->getChild(m_pNode->getName() + "_Radar");
	radar->rotate((Ogre::Quaternion(Ogre::Degree(-0.5),Ogre::Vector3::UNIT_Y)));

	for(int i = 1; i<=numMaterials; i++){
		mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(m_pNode->getName()+"_Thruster_FireMaterial_"+ Ogre::StringConverter::toString(i)));
		mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("timer", timer_);
	}


	if(hasExploded){
		personalTimer += 1;
		mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(m_pNode->getName()+"_Explosion_ParticleMaterial_"+ Ogre::StringConverter::toString(5)));
		mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("timer", personalTimer);

		if(personalTimer >= 15){
			m_pNode->setVisible(false);
			dead = true;
		}
	}

	move();
}

void SmallShip::collide(){
	
}

void SmallShip::collide(int damage){
	health-=damage;
	if(health <= 0){

		hasExploded = true;

	}
}

void SmallShip::shoot(GameObjectFactory* factory ,ObjectManager* manager, GameObject* player){
	
}


void SmallShip::move(void)
{
	m_pNode->translate(drift_Direction);
	m_pNode->needUpdate();
	
}

Ogre::Quaternion SmallShip::getOrientation(){
	return m_pNode->getOrientation();
}

Ogre::Vector3 SmallShip::getPosition(){
	return m_pNode->getPosition();
}


