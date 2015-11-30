#include "Carrier.h"


Carrier::Carrier(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
		m_pNode = newShip;
		
	hasExploded = false;
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);
	numMaterials = 3;
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
}

void Carrier::collide(){
	
}

void Carrier::move(void)
{
	
	
}
