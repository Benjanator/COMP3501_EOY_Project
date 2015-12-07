#include "Fighter.h"
#include "GameObjectFactory.h"
#include "ObjectManager.h"

Fighter::Fighter(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
	this->type = smallEnemy_fighter;
		m_pNode = newShip;
	

	hasExploded = false;
	personalTimer = 0;
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);
	numMaterials = 2;
	health = 5;

	
	reloading = 50.0f;
}


Fighter::~Fighter(void)
{
}

Ogre::SceneNode& Fighter::getNode()
{
	return *m_pNode;
}

void Fighter::update(float timer_)
{
	
	Ogre::MaterialPtr mat;
	for(int i = 1; i<=numMaterials; i++){
		mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(m_pNode->getName()+"_Thruster_FireMaterial_"+ Ogre::StringConverter::toString(i)));
		mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("timer", timer_);
	}

	if(hasExploded){
		personalTimer += 1;
		mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(m_pNode->getName()+"_Explosion_ParticleMaterial_"+ Ogre::StringConverter::toString(3)));
		mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("timer", personalTimer);

		if(personalTimer >= 50){
			m_pNode->setVisible(false);
			dead = true;
		}
	}

	
	move();
}

void Fighter::collide(){
	
}

void Fighter::collide(int damage){
	health-=damage;
	if(health <= 0){
	
		hasExploded = true;
	}
}

void Fighter::shoot(GameObjectFactory* factory ,ObjectManager* manager,GameObject* player){

	
	GameObject* temp;
	

	Ogre::Vector3 playerPos = (player->getNode()).getPosition();
	m_pNode->lookAt((player->getNode()).getPosition(),Ogre::Node::TS_WORLD,Ogre::Vector3::UNIT_Y);	

	if(reloading <= 0.0){
	  temp = factory->createGameRocket(m_pNode->getOrientation() * (Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::NEGATIVE_UNIT_X)),m_pNode->getPosition(),this->getMotionDirection());
      temp->setTeam(1);
      manager->addObject(temp);
	  reloading = 50.0f;
	}else{
	  reloading -=  Ogre::Math::RangeRandom(0.2f,0.1f);
	  
	}
	

}

void Fighter::move(void)
{
	
	
}

