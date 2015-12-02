#include "PlayerInput.h"




	float camera_near_clip_distance_g = 0.001f;
	float camera_far_clip_distance_g = 10000.0;
	Ogre::Vector3 camera_position_g(0.0, 0.0, 0.0);
	Ogre::Vector3 camera_look_at_g(0.0, 0.0, 0.0);
	Ogre::Vector3 camera_up_g(0.0, 1.0, 0.0);
	bool space_down_ = false;
	bool camState = true;
	bool relativeMotion = true;
	bool keyUp = true;
	bool ckeyUp = true;
	bool xkeyUp = true;
	bool mouseLeft = true;
	bool lasrLR = true;
	GameObject* temp;

	PlayerInput::PlayerInput(  Ogre::SceneManager* manager,OIS::Keyboard* _keyboard, OIS::Mouse* _mouse, GameObjectFactory* oFactory, ObjectManager* oManager)
{

		currentDir = (0,0,0);
		rightDir = (0,0,0);
		upDir = (0,0,0);
		forwDir = (0,0,0);
		
		scene_manager = manager;
		root_scene_node = scene_manager->getRootSceneNode();

		playerMouse_ = _mouse;
		playerMouse_->setBuffered(true);
		playerKeyboard_ = _keyboard;

		factory = oFactory;
		objectManager = oManager;



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
		camera_first_person_node->setPosition(0,1,0);
		camera_first_person_node->setFixedYawAxis(false);

		
		camera_chase_node = camera_first_person_node->createChildSceneNode("MyChaseCameraNode");
		camera_chase_node->setPosition(0.0, 2.0, 15.0);
		camera_chase_node->setInheritOrientation(false);
		camera_chase_node->setFixedYawAxis(false);
}


PlayerInput::~PlayerInput(void)
{
	playerShip = 0;
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

	}

}

void PlayerInput::handleInput(void){
	/* This event is called after a frame is queued for rendering */
	/* Do stuff in this event since the GPU is rendering and the CPU is idle */	
	upDir = Ogre::Vector3(0.0f);
	rightDir = Ogre::Vector3(0.0f);
	forwDir = Ogre::Vector3(0.0f);

	if(playerMouse_->getMouseState().buttonDown(OIS::MB_Right)){
		

		Ogre::Quaternion pitchQuat(Ogre::Radian(playerMouse_->getMouseState().Y.rel * -0.01f),Ogre::Vector3::UNIT_X);
		Ogre::Quaternion yawQuat(Ogre::Radian(playerMouse_->getMouseState().X.rel * -0.01f),Ogre::Vector3::UNIT_Y);
		Ogre::Quaternion rotQuat =  pitchQuat * yawQuat;
		//camera_first_person_node->rotate(pitchQuat,Ogre::Node::TS_LOCAL); //this allows us to have no roll when pitch and yaw are combined
		//camera_first_person_node->rotate(yawQuat,Ogre::Node::TS_WORLD); //  this will also cause a forced lock

		playerShip->pitch(Ogre::Radian(playerMouse_->getMouseState().Y.rel * -0.01f));
		playerShip->yaw(Ogre::Radian(playerMouse_->getMouseState().X.rel * -0.01f));
		
		//camera_first_person_node->rotate(rotQuat); // quaternion camera with rotations embedded from pitch and yaws

		//camera_first_person_node->pitch(Ogre::Radian(playerMouse_->getMouseState().Y.rel * -0.01f));
		///camera_first_person_node->yaw(Ogre::Radian(playerMouse_->getMouseState().X.rel * -0.01f));
	
	}

	if(playerMouse_->getMouseState().buttonDown(OIS::MB_Left)){
		if(mouseLeft == true){
//<<<<<<< HEAD
			temp = factory->createGameLaser(playerShip->getOrientation(),playerShip->getPosition(),lasrLR);
			//temp = factory->createGameScatterShot(playerShip->getOrientation(),playerShip->getPosition(),lasrLR);
//=======
			//temp = factory->createGameLaser(playerShip->getOrientation(),playerShip->getPosition(),lasrLR);
			temp->setTeam(0);
//>>>>>>> 6ef87d019f27df578792ee5af98c1f0cd7b4db1e
			objectManager->addObject(temp);
			mouseLeft = false;
			lasrLR = !lasrLR;
		}
	}else{
		mouseLeft = true;
	}

	if(playerKeyboard_->isKeyDown(OIS::KC_C)){
		if(ckeyUp == true){
			temp = factory->createGameRocket(playerShip->getOrientation(),playerShip->getPosition(),playerShip->getMotionDirection());
			temp->setTeam(0);
			objectManager->addObject(temp);
			ckeyUp = false;
			
		}
	}else{
		ckeyUp = true;
	}

		if(playerKeyboard_->isKeyDown(OIS::KC_X)){
		if(xkeyUp == true){
			temp = factory->createGameScatterShot(playerShip->getOrientation(),playerShip->getPosition(),lasrLR);
			temp->setTeam(0);
			objectManager->addObject(temp);
			xkeyUp = false;
			
		}
	}else{
		xkeyUp = true;
	}
	

	

	Ogre::Radian rot_factor(Ogre::Math::PI / 180); // Camera rotation with directional thrusters

	if(playerKeyboard_->isKeyDown(OIS::KC_P)){
		playerShip->fullStop();
	}


	if(playerKeyboard_->isKeyDown(OIS::KC_Q)){

		playerShip->roll(Ogre::Quaternion(rot_factor,Ogre::Vector3::UNIT_Z));
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_E)){
		
		playerShip->roll(Ogre::Quaternion(-1*rot_factor,Ogre::Vector3::UNIT_Z));
	}

	
	if(playerKeyboard_->isKeyDown(OIS::KC_A)){
		rightDir = player_camera->getDerivedRight();
		playerShip->translate(Ogre::Vector3(0.0f), -rightDir, Ogre::Vector3(0.0f));
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_D)){
		rightDir = player_camera->getDerivedRight();
		playerShip->translate(Ogre::Vector3(0.0f), rightDir, Ogre::Vector3(0.0f));
		
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_W)){
		forwDir = player_camera->getDerivedDirection();
		playerShip->translate(Ogre::Vector3(0.0f), Ogre::Vector3(0.0f), forwDir);
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_S)){
		forwDir = player_camera->getDerivedDirection();
		playerShip->translate(Ogre::Vector3(0.0f), Ogre::Vector3(0.0f), -forwDir);
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_R)){
		upDir = player_camera->getDerivedUp();
		playerShip->translate(upDir, Ogre::Vector3(0.0f), Ogre::Vector3(0.0f));
	}
	if(playerKeyboard_->isKeyDown(OIS::KC_F)){
		upDir = player_camera->getDerivedUp();
		playerShip->translate(-upDir, Ogre::Vector3(0.0f), Ogre::Vector3(0.0f));
	}

	if(playerKeyboard_->isKeyDown(OIS::KC_M)){
		if(keyUp){
			relativeMotion = !relativeMotion;
			keyUp = false;
		}
	}
	else{
		keyUp = true;
	}


	if (playerKeyboard_->isKeyDown(OIS::KC_SPACE)){
		space_down_ = true;
	}
	if ((!playerKeyboard_->isKeyDown(OIS::KC_SPACE)) && space_down_){
		camState = !camState;
		space_down_ = false;
	}

	
	camera_first_person_node->needUpdate();
	camera_chase_node->needUpdate();
}

void PlayerInput::bindCamera(SmallShip* _ship, Ogre::Node* _node)
{
	playerShip = _ship;

	Ogre::Node* temp = root_scene_node->removeChild("MyCameraNode");
	
	_node->addChild(temp);
}