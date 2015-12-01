#include "Bomber.h"


Bomber::Bomber(Ogre::SceneNode* newShip):GameObject(GameObject::empty)
{
		m_pNode = newShip;
		
	hasExploded = false;
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);

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
	move();
}

void Bomber::collide(){
	
}

void Bomber::move(void)
{

	
}

