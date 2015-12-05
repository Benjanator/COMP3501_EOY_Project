#include "Carrier.h"


Carrier::Carrier(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
	this->type = largeEnemy_cmd;
		m_pNode = newShip;


	degree = 0.0f;
	hasExploded = false;
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);
	numMaterials = 3;
	velocity = Ogre::Vector3(0.0f, 0.0f, 0.0f);
	health = 10;
	personalTimer = 0;
}


Carrier::~Carrier(void)
{
}

Ogre::SceneNode& Carrier::getNode()
{
	return *m_pNode;
}

void Carrier::update(float timer_)
{

	Ogre::MaterialPtr mat;
	//Ogre::Entity* mEntity =(Ogre::Entity*) m_pNode->getChild("");
	
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
	GameObjectFactory* tmpfctry = factory;
	ObjectManager* tmpmngr = manager;
	//GameObject* temp;

	m_pNode->lookAt((player->getNode()).getPosition(),Ogre::Node::TS_PARENT,Ogre::Vector3::UNIT_Y);		
}

void Carrier::turn_right(Ogre::Degree _degree)
{
	m_pNode->roll(-1 * _degree);
	m_pNode->needUpdate();
}

void Carrier::turn_left(Ogre::Degree _degree)
{
	m_pNode->roll(1 * _degree);
	m_pNode->needUpdate();
}

void Carrier::move(void)
{
	velocity.x = cos(degree);
	velocity.z = sin(degree);
	turn_right(Ogre::Degree(0.3f));
	degree = degree + 0.005f;
	m_pNode->translate(velocity);
	m_pNode->needUpdate();
}

