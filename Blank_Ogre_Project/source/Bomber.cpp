#include "Bomber.h"


Bomber::Bomber(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
		m_pNode = newShip;
		this->type = smallEnemy_bomber;
		
	hasExploded = false;
	personalTimer = 0;
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);
	health = 5;
}


Bomber::~Bomber(void)
{
}

Ogre::SceneNode& Bomber::getNode()
{
	return *m_pNode;
}

void Bomber::update(float timer_)
{
	Ogre::MaterialPtr mat;
	for(int i = 1; i<=26; i++){
		mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(m_pNode->getName()+"_SField_SplineParticleMaterial_"+ Ogre::StringConverter::toString(i)));
		mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("timer", timer_ - i);
	}

	if(hasExploded){
		personalTimer += 1;
		mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(m_pNode->getName()+"_Explosion_ParticleMaterial_"+ Ogre::StringConverter::toString(27)));
		mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("timer", personalTimer);

		if(personalTimer >= 50){
			m_pNode->setVisible(false);
			dead = true;
		}
	}
	move();
}

void Bomber::collide(){
	
}

void Bomber::collide(int damage){
	health-=damage;
	if(health <= 0){
		//dead = true;
		hasExploded = true;
	}
}

void Bomber::shoot(GameObjectFactory*){
	
}




void Bomber::move(void)
{

	
}

