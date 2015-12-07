#include "Carrier.h"
#include "GameObjectFactory.h"
#include "ObjectManager.h"

Carrier::Carrier(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
	this->type = largeEnemy_cmd;
		m_pNode = newShip;
	

	hasExploded = false;
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);
	numMaterials = 3;
	health = 1500;
	personalTimer = 0;

	reloading = 0.0f;
}


Carrier::~Carrier(void)
{
}

Ogre::SceneNode& Carrier::getNode()
{
	return *m_pNode;
}

void Carrier::update(float timer_, ObjectManager* manager)
{

	Ogre::MaterialPtr mat;


	for(int i = 1; i<=numMaterials; i++){
		mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(m_pNode->getName()+"_Thruster_FireMaterial_"+ Ogre::StringConverter::toString(i)));
		mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("timer", timer_);
	}

	for(int i = 4; i<=29; i++){
	
		mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(m_pNode->getName()+"_SField_SplineParticleMaterial_"+ Ogre::StringConverter::toString(i)));
		mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("timer", timer_ - i);
	}


		move();
		return;
}

void Carrier::collide(){
	
}

void Carrier::collide(int damage){
	health-=damage;
	if(health <= 0){
		m_pNode->setVisible(false);
		dead = true;
	}
}

void Carrier::shoot(GameObjectFactory* factory ,ObjectManager* manager, GameObject* player){

	
	GameObject* temp;
	std::srand(std::time(0));

	if(reloading <= 0.0){
	  temp = factory->createGameScatterShot(m_pNode->getOrientation(),m_pNode->getPosition(),true);
	  temp->setTeam(1);
	  manager->addObject(temp);
	  reloading = 10.0f;
	}else{
	  reloading -= 0.1f;
	}
	
		
}

void Carrier::turn_right(Ogre::Degree _degree)
{
	m_pNode->roll(-1 * _degree);
}

void Carrier::turn_left(Ogre::Degree _degree)
{
	m_pNode->roll(1 * _degree);
}

void Carrier::move(void)
{
	turn_left(Ogre::Degree(0.5f));
	m_pNode->translate(m_pNode->getOrientation() * Ogre::Vector3::UNIT_X);
	m_pNode->needUpdate();
}

