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

	void CreateParticleType(Ogre::SceneNode* );

private:

	
	Ogre::SceneManager* scene_manager;



	void CreateParticleEntity(Ogre::String entity_name, Ogre::String object_name, Ogre::String material_name,Ogre::SceneNode*, Ogre::Vector3 ); // Create an entity of an object

	void CreateThrusterParticleGeometry(Ogre::String object_name, int num_particles, float loop_radius = 0.6, float circle_radius = 0.2); // Create Thruster Fire (torus) particles
	


};

