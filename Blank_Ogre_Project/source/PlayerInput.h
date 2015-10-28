#ifndef PLAYER_INPUT_H_
#define PLAYER_INPUT_H_


#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include "OIS/OIS.h"

class PlayerInput
{
public:
	PlayerInput(Ogre::SceneManager*,OIS::Keyboard*, OIS::Mouse*);
	~PlayerInput(void);

	Ogre::SceneManager* scene_manager;

	Ogre::Camera* player_camera;
	Ogre::SceneNode* root_scene_node;
	Ogre::SceneNode* camera_scene_node;
	Ogre::SceneNode* camera_chase_node;
	Ogre::SceneNode* camera_first_person_node;


	OIS::Mouse *playerMouse_;
	OIS::Keyboard *playerKeyboard_;


	void updateCamera(void);
	void handleInput(void);

	Ogre::SceneNode* getFirstNode(){
		return camera_first_person_node;
	}

};

#endif 
