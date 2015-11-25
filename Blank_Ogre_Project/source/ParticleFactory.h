#pragma once
#include <OGRE\OgreSceneNode.h>
#include <OGRE\OgreSceneManager.h>
#include "OGRE/OgreRoot.h"
#include <OGRE/OgreEntity.h>
#include "OGRE/OgreManualObject.h"
#include <exception>
#include <string>


class ParticleFactory
{
public:
	ParticleFactory(Ogre::SceneManager*);
	~ParticleFactory(void);

	Ogre::SceneNode* CreateParticleEntity(Ogre::String , Ogre::String ,Ogre::SceneNode*, Ogre::Vector3 ); // Create an entity of an object
	void CreateThrusterParticleGeometry(Ogre::String , int ,float loop_radius = 0.6, float circle_radius = 0.2); // Create Thruster Fire (torus) particles

private:

	
	Ogre::SceneManager* scene_manager;
	int numMaterials;
	Ogre::String materialArray[5000];


	

	
	


};

