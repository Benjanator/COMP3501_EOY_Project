#include "Fighter.h"

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
		//m_pNode->setVisible(false);
		//dead = true;
		hasExploded = true;
	}
}


void Fighter::move(void)
{
	
	
}

