#include "Bomber.h"
#include "GameObjectFactory.h"
#include "ObjectManager.h"

Bomber::Bomber(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
		m_pNode = newShip;
		this->type = smallEnemy_bomber;
		
	hasExploded = false;
	personalTimer = 0;
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);
	health = 5;
	warpTimer = 80.0f;

    reloading = 5.0f;
}


Bomber::~Bomber(void)
{
}

Ogre::SceneNode& Bomber::getNode()
{
	return *m_pNode;
}

void Bomber::update(float timer_,ObjectManager* manager)
{
	std::vector<GameObject*> tempList = manager->getObjectList();
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
	Ogre::Vector3 temp = m_pNode->getPosition() - tempList.at(0)->getNode().getPosition();
	move(temp);
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

void Bomber::shoot(GameObjectFactory* factory ,ObjectManager* manager, GameObject* player){
	

	GameObject* temp;
	std::srand(std::time(0));
	m_pNode->lookAt((player->getNode()).getPosition(),Ogre::Node::TS_PARENT,Ogre::Vector3::UNIT_X);	

	if(reloading <= 0.0){
	  temp = factory->createGameLaser(m_pNode->getOrientation() * (Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_Y)),m_pNode->getPosition(),true);
	  temp->setTeam(1);
	  manager->addObject(temp);
	  reloading = 30.0f;
	}else{
	  reloading -= Ogre::Math::RangeRandom(0.5f,0.1f);
	}

	
}



void Bomber::move(Ogre::Vector3 distance)
{
	if(warpTimer <= 0.0){
		m_pNode->translate((-2 * (distance) + Ogre::Vector3(Ogre::Math::RangeRandom(-20.5f,20.5f), Ogre::Math::RangeRandom(-20.5f,20.5f), Ogre::Math::RangeRandom(-20.5f,20.5f))));
		m_pNode->needUpdate();
		warpTimer = 80.0f;
	}else{
		warpTimer -= 0.1f;
	}
	
}

