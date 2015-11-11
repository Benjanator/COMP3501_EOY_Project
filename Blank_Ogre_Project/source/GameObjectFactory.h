#pragma once
#include "GameObject.h"
#include <OGRE\OgreSceneNode.h>
#include <OGRE\OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include "SmallShip.h"
#include "Rocket.h"
#include "Carrier.h"
#include "Fighter.h"
#include "Bomber.h"

class GameObjectFactory
{
public:
	GameObjectFactory(Ogre::SceneManager*);
	~GameObjectFactory(void);

	GameObject* createGameObject(GameObject::objectType);

private:
	int SAF_id; // small ally fighter
	int SEF_id; // small enemy fighter
	int SAB_id; // small ally bomber
	int SEB_id; // small enemy bomber
	int LAC_id; // large ally cmd
	int LEC_id; // large enemy cmd
	int RCKT_id; // rocket

	Ogre::SceneManager* scene_manager;

	Ogre::SceneNode* create_SAF();
	Ogre::SceneNode* create_SEF();
	Ogre::SceneNode* create_SAB();
	Ogre::SceneNode* create_SEB();
	Ogre::SceneNode* create_LAC();
	Ogre::SceneNode* create_LEC();
	Ogre::SceneNode* create_AP();
	Ogre::SceneNode* create_EP();
	Ogre::SceneNode* create_RCKT();
};

