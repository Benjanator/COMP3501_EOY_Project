#pragma once
#include "GameObject.h"
#include <OGRE\OgreSceneNode.h>
#include <OGRE\OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include "SmallShip.h"

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

	Ogre::SceneManager* scene_manager;

	Ogre::SceneNode* create_SAF();
};

