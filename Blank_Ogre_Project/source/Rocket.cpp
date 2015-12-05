#include "Rocket.h"


Rocket::Rocket(Ogre::SceneNode * newRocket,Ogre::Quaternion shipOrientation,Ogre::Vector3 shipPosition, Ogre::Vector3 shipDirection):GameObject(GameObject::empty)
{
	
	m_pNode = newRocket;
	
	this->type = rocket ;
	m_pNode->setOrientation(shipOrientation*(Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_Y)));
	drift_Direction = shipDirection;
	forward_Direction = shipOrientation *  Ogre::Vector3::NEGATIVE_UNIT_Z;
	Ogre::Vector3 down_Direction = shipOrientation *  Ogre::Vector3::NEGATIVE_UNIT_Y;

	m_pNode->setPosition(shipPosition + (forward_Direction *10) + (down_Direction*2));
	
	accel_Rate = 0.02;
	personalTimer = 0;
	hasExploded = false;
	flyTime = 1000.0f;
	aabbCenter = Ogre::Vector3(0.0f, 0.0f, 0.0f);
	aabbSize = Ogre::Vector3(0.1f, 0.1f, 0.1f);
	numMaterials = 1;
}


Rocket::~Rocket(void)
{
}

void Rocket::update(float timer_)
{
	Ogre::MaterialPtr mat;
	mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(m_pNode->getName()+"_Thruster_FireMaterial_"+ Ogre::StringConverter::toString(1)));
	mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("timer", timer_);

	if(hasExploded){
		personalTimer += 1;
		mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(m_pNode->getName()+"_Explosion_ParticleMaterial_"+ Ogre::StringConverter::toString(2)));
		mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("timer", personalTimer);

		if(personalTimer >= 15){
			m_pNode->setVisible(false);
			dead = true;
		}
		return;
	}
	move();

	flyTime -= 0.75f;
	if(flyTime < 0.0f){
		dead = true;
	}
}

void Rocket::move(){

	  drift_Direction += forward_Direction * accel_Rate;
	  m_pNode->translate(drift_Direction);
	  m_pNode->needUpdate();
	
}

void Rocket::collide(){
	hasExploded = true;
	
}

void Rocket::collide(int damage){
	collide();
}

void Rocket::shoot(GameObjectFactory* factory ,ObjectManager* manager, GameObject* player){
	
}

void Rocket::explode(){
	//run explosion particle effect
}

Ogre::SceneNode& Rocket::getNode()
{
	return *m_pNode;
}

