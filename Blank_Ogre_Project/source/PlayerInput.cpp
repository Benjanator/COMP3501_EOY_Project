#include "PlayerInput.h"




	float camera_near_clip_distance_g = 0.001f;
	float camera_far_clip_distance_g = 10000.0;
	Ogre::Vector3 camera_position_g(0.0, 0.0, 0.0);
	Ogre::Vector3 camera_look_at_g(0.0, 0.0, 0.0);
	Ogre::Vector3 camera_up_g(0.0, 1.0, 0.0);
	bool space_down_ = false;
	bool camState = true;

PlayerInput::PlayerInput(  Ogre::SceneManager* manager,OIS::Keyboard* _keyboard, OIS::Mouse* _mouse)
{

		
		scene_manager = manager;
		root_scene_node = scene_manager->getRootSceneNode();

		playerMouse_ = _mouse;
		playerKeyboard_ = _keyboard;


		player_camera = scene_manager->createCamera("MyCamera");
        camera_scene_node = root_scene_node->createChildSceneNode("MyCameraNode");
        camera_scene_node->attachObject(player_camera);
		camera_scene_node->setPosition(0.0, 0.0, 0.0);

		camera_scene_node->resetOrientation();

        player_camera->setNearClipDistance(camera_near_clip_distance_g);
        player_camera->setFarClipDistance(camera_far_clip_distance_g); 

		player_camera->setPosition(camera_position_g);
		player_camera->lookAt(camera_look_at_g);
		//camera->setFixedYawAxis(true, camera_up_g);
		player_camera->setFixedYawAxis(false);
		camera_scene_node->setFixedYawAxis(false);


		camera_first_person_node = root_scene_node->createChildSceneNode("MyFirstPersonCameraNode");
		camera_first_person_node->setPosition(0,0,0);
		camera_first_person_node->setFixedYawAxis(false);

		
		camera_chase_node = camera_first_person_node->createChildSceneNode("MyChaseCameraNode");
		camera_chase_node->setPosition(0.0, 2.0, 10.0);
		camera_chase_node->setInheritOrientation(false);
		camera_chase_node->setFixedYawAxis(false);
}


PlayerInput::~PlayerInput(void)
{
}


void PlayerInput::updateCamera(void){

	/* Capture input */
	playerKeyboard_->capture();
	playerMouse_->capture();

	handleInput();
	if(camState){
		camera_scene_node->setPosition(camera_first_person_node->getPosition());
		camera_scene_node->setOrientation(camera_first_person_node->getOrientation());
	}else{
		camera_scene_node->setPosition(camera_chase_node->_getDerivedPosition());
		camera_scene_node->setOrientation(camera_first_person_node->getOrientation());
		//camera_scene_node->setOrientation(camera_chase_node->_getDerivedOrientation());

	}

}

void PlayerInput::handleInput(void){
	/* This event is called after a frame is queued for rendering */
	/* Do stuff in this event since the GPU is rendering and the CPU is idle */	

	if(playerMouse_->getMouseState().buttonDown(OIS::MB_Right)){
		camera_first_person_node->pitch(Ogre::Radian(playerMouse_->getMouseState().Y.rel * -0.01f),Ogre::Node::TS_LOCAL);
		camera_first_person_node->yaw(Ogre::Radian(playerMouse_->getMouseState().X.rel * -0.01f),Ogre::Node::TS_WORLD);
	
	}
	

	Ogre::Radian rot_factor(Ogre::Math::PI / 180); // Camera rotation with directional thrusters
	

	
	if(playerKeyboard_->isKeyDown(OIS::KC_Q)){
		camera_first_person_node->roll(rot_factor);
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_E)){
		camera_first_person_node->roll(rot_factor*-1);
	}

	
	if(playerKeyboard_->isKeyDown(OIS::KC_A)){
		camera_first_person_node->translate(player_camera->getDerivedRight() * -0.1);
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_D)){
		camera_first_person_node->translate(player_camera->getDerivedRight() * 0.1);
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_W)){
		camera_first_person_node->translate(player_camera->getDerivedDirection() * 0.5);
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_S)){
		camera_first_person_node->translate(player_camera->getDerivedDirection() * -0.5);
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_R)){
		camera_first_person_node->translate(player_camera->getDerivedUp() * 0.1);
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_F)){
		camera_first_person_node->translate(player_camera->getDerivedUp() * -0.1);
	}

	

	if (playerKeyboard_->isKeyDown(OIS::KC_SPACE)){
		space_down_ = true;
	}
	if ((!playerKeyboard_->isKeyDown(OIS::KC_SPACE)) && space_down_){
		camState = !camState;
		space_down_ = false;
	}


}