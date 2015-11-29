#pragma once
#include <OGRE\OgreSceneNode.h>
#include <OGRE\OgreSceneManager.h>
#include "OGRE/OgreRoot.h"
#include <OGRE/OgreEntity.h>
#include "OGRE/OgreManualObject.h"
#include <exception>
#include <string>
#include <vector>


class ParticleFactory
{
public:
	ParticleFactory(Ogre::SceneManager*);
	~ParticleFactory(void);

	Ogre::SceneNode* CreateParticleEntity(Ogre::String , Ogre::String ,Ogre::SceneNode*, Ogre::Vector3 ); // Create an entity of an object
	void CreateThrusterParticleGeometry(Ogre::String , int ,float loop_radius = 0.6, float circle_radius = 0.2); // Create Thruster Fire (torus) particles
	void CreateExplosionParticleGeometry(Ogre::String object_name, int num_particles);
	void resetCounter();
private:

	
	Ogre::SceneManager* scene_manager;
	int materialCounter;
	std::vector<Ogre::String> materialArray;

	void incrementCounter();
	
	//need to make a partcile instance counter methods so we can count the number of particles generated for a particular object type, perhaps assign the numparticle counter to the object.h and loop through it in update

	
	


};

