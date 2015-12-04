#pragma once

#include "GameObject.h"
#include "SmallShip.h"
#include "Rocket.h"
#include "Carrier.h"
#include "Fighter.h"
#include "Bomber.h"
#include "Laser.h"
#include "Scattershot.h"

#include <OGRE\OgreSceneNode.h>
#include <OGRE\OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include "ParticleFactory.h"



class GameObjectFactory
{
public:


	GameObjectFactory(Ogre::SceneManager*);
	~GameObjectFactory(void);

	GameObject* createGameObject(GameObject::objectType);
	GameObject* createGameRocket(Ogre::Quaternion ,Ogre::Vector3 , Ogre::Vector3 );
	GameObject* createGameLaser(Ogre::Quaternion ,Ogre::Vector3, bool );
	GameObject* createGameScatterShot(Ogre::Quaternion ,Ogre::Vector3, bool );

private:
	int SAF_id; // small ally fighter
	int SEF_id; // small enemy fighter
	int SAB_id; // small ally bomber
	int SEB_id; // small enemy bomber
	int LAC_id; // large ally cmd
	int LEC_id; // large enemy cmd
	int RCKT_id;// rocket
	int LSR_id; //lasers
	int SCTR_id; //lasers

	Ogre::SceneManager* scene_manager;

	ParticleFactory* factory;

	Ogre::SceneNode* create_SAF();
	Ogre::SceneNode* create_SEF();
	Ogre::SceneNode* create_SAB();
	Ogre::SceneNode* create_SEB();
	Ogre::SceneNode* create_LAC();
	Ogre::SceneNode* create_LEC();
	Ogre::SceneNode* create_AP();
	Ogre::SceneNode* create_EP();
	Ogre::SceneNode* create_RCKT(Ogre::Quaternion,Ogre::Vector3 );
	Ogre::SceneNode* create_LSR(Ogre::Quaternion,Ogre::Vector3 );
	Ogre::SceneNode* create_SCTR(Ogre::Quaternion,Ogre::Vector3 );
	
};

