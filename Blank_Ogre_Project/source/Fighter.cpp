#include "Fighter.h"

Fighter::Fighter(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
		m_pNode = newShip;
	

	hasExploded = false;
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);
	numMaterials - 2;
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
	move();
}

void Fighter::collide(){
	
}

void Fighter::move(void)
{
	
	
}

