#include "ogre_application.h"
#include "../bin/path_config.h"
#include <OgreMeshManager.h>

namespace ogre_application {

/* Some configuration constants */
/* They are written here as global variables, but ideally they should be loaded from a configuration file */

/* Initialization */
const Ogre::String config_filename_g = "";
const Ogre::String plugins_filename_g = "";
const Ogre::String log_filename_g = "Ogre.log";

/* Main window settings */
const Ogre::String window_title_g = "Demo";
const Ogre::String custom_window_capacities_g = "";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const bool window_full_screen_g = false;

/* Viewport and camera settings */
float viewport_width_g = 1.0f;
float viewport_height_g = 1.0f;
float viewport_left_g = (1.0f - viewport_width_g) * 0.5f;
float viewport_top_g = (1.0f - viewport_height_g) * 0.5f;
unsigned short viewport_z_order_g = 300;
const Ogre::ColourValue viewport_background_color_g(0.3, 0.7, 0.05);
float camera_near_clip_distance_g = 0.001f;
float camera_far_clip_distance_g = 10000.0;
Ogre::Vector3 camera_position_g(0.0, 0.0, 0.0);
Ogre::Vector3 camera_look_at_g(0.0, 0.0, 0.0);
Ogre::Vector3 camera_up_g(0.0, 1.0, 0.0);

/* Materials */
const Ogre::String material_directory_g = MATERIAL_DIRECTORY;

//
bool camState = 0;

//
float change = 0.0f;

//
PlayerInput *player;


OgreApplication::OgreApplication(void){

    /* Don't do work in the constructor, leave it for the Init() function */
}


void OgreApplication::Init(void){

	/* Set default values for the variables */
	animating_ = false;
	space_down_ = false;
	animation_state_ = NULL;
	input_manager_ = NULL;
	keyboard_ = NULL;
	mouse_ = NULL;

	/* Run all initialization steps */
    InitRootNode();
    InitPlugins();
    InitRenderSystem();
    InitWindow();
	InitEvents();
	InitOIS();
	InitViewport();
	LoadMaterials();
	LoadModels();
	LoadSkybox();

	objectManager = new ObjectManager();
	factory = new GameObjectFactory(ogre_root_->getSceneManager("MySceneManager"));
	physicsManager = new PhysicsManager(objectManager);
}


void OgreApplication::InitRootNode(void){

    try {
		
		/* We need to have an Ogre root to be able to access all Ogre functions */
        ogre_root_ = std::auto_ptr<Ogre::Root>(new Ogre::Root(config_filename_g, plugins_filename_g, log_filename_g));
		//ogre_root_->showConfigDialog();

    }
    catch (Ogre::Exception &e){
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
		throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}


void OgreApplication::InitPlugins(void){

    try {

		/* Load plugin responsible for OpenGL render system */
        Strings plugin_names;
        plugin_names.push_back("RenderSystem_GL");
		
        Strings::iterator iter = plugin_names.begin();
        Strings::iterator iter_end = plugin_names.end();
        for (; iter != iter_end; iter++){
            Ogre::String& plugin_name = (*iter);
            if (OGRE_DEBUG_MODE){
                plugin_name.append("_d");
            }
            ogre_root_->loadPlugin(plugin_name);
        }

    }
    catch (Ogre::Exception &e){
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}


void OgreApplication::InitRenderSystem(void){

    try {

        const Ogre::RenderSystemList& render_system_list = ogre_root_->getAvailableRenderers();
        if (render_system_list.size() == 0)
        {
			throw(OgreAppException(std::string("OgreApp::Exception: Sorry, no rendersystem was found.")));
        }

        Ogre::RenderSystem *render_system = render_system_list.at(0);
        ogre_root_->setRenderSystem(render_system);

    }
    catch (Ogre::Exception &e){
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

        
void OgreApplication::InitWindow(void){

    try {

        /* Create main window for the application */
		bool create_window_automatically = false;
        ogre_root_->initialise(create_window_automatically, window_title_g, custom_window_capacities_g);

        Ogre::NameValuePairList params;
        params["FSAA"] = "0";
        params["vsync"] = "true";
        ogre_window_ = ogre_root_->createRenderWindow(window_title_g, window_width_g, window_height_g, window_full_screen_g, &params);

        ogre_window_->setActive(true);
        ogre_window_->setAutoUpdated(false);
    }
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}


void OgreApplication::InitViewport(void){

    try {

        /* Retrieve scene manager and root scene node */
        Ogre::SceneManager* scene_manager = ogre_root_->createSceneManager(Ogre::ST_GENERIC, "MySceneManager");
        Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();


		player = new PlayerInput( scene_manager,keyboard_,mouse_);

        /* Create viewport */
       // Ogre::Viewport *viewport = ogre_window_->addViewport(camera, viewport_z_order_g, viewport_left_g, viewport_top_g, viewport_width_g, viewport_height_g);
		Ogre::Viewport *viewport = ogre_window_->addViewport(player->player_camera, viewport_z_order_g, viewport_left_g, viewport_top_g, viewport_width_g, viewport_height_g);
        viewport->setAutoUpdated(true);
        viewport->setBackgroundColour(viewport_background_color_g);

		/* Set aspect ratio */
		float ratio = float(viewport->getActualWidth()) / float(viewport->getActualHeight());
		player->player_camera->setAspectRatio(ratio);

    }
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}


void OgreApplication::InitEvents(void){

	try {

		/* Add this object as a FrameListener for render events (see frameRenderingQueued event) */
		ogre_root_->addFrameListener(this);

		/* Add this object as a WindowEventListener to handle the window resize event */
		Ogre::WindowEventUtilities::addWindowEventListener(ogre_window_, this);

	}
    catch (Ogre::Exception &e){
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
		throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}


void OgreApplication::InitOIS(void){

	/* Initialize the Object Oriented Input System (OIS) */
	try {

		/* Initialize input manager */
		OIS::ParamList pl; // Parameter list passed to the input manager initialization
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;
		ogre_window_->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		pl.insert(std::make_pair(std::string("w32_mouse"), 
		std::string("DISCL_FOREGROUND" )));
		pl.insert(std::make_pair(std::string("w32_mouse"), 
		std::string("DISCL_NONEXCLUSIVE")));
		input_manager_ = OIS::InputManager::createInputSystem(pl);

		/*size_t hWnd = 0;
		ogre_window_->getCustomAttribute("WINDOW", &hWnd);
		input_manager_ = OIS::InputManager::createInputSystem(hWnd);*/

		/* Initialize keyboard and mouse */
		keyboard_ = static_cast<OIS::Keyboard*>(input_manager_->createInputObject(OIS::OISKeyboard, false));

		mouse_ = static_cast<OIS::Mouse*>(input_manager_->createInputObject(OIS::OISMouse, false));
		unsigned int width, height, depth;
		int top, left;
		ogre_window_->getMetrics(width, height, depth, left, top);
		const OIS::MouseState &ms = mouse_->getMouseState();
		ms.width = width;
		ms.height = height;

	}
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}


void OgreApplication::LoadMaterials(void){

    try {
		
		/* Load materials that can then be assigned to objects in the scene */
		Ogre::String resource_group_name = "MyGame";
		Ogre::ResourceGroupManager& resource_group_manager = Ogre::ResourceGroupManager::getSingleton();
		resource_group_manager.createResourceGroup(resource_group_name);
		bool is_recursive = false;
		resource_group_manager.addResourceLocation(material_directory_g + "/media/material", "FileSystem", resource_group_name, is_recursive);
		resource_group_manager.initialiseResourceGroup(resource_group_name);
		resource_group_manager.loadResourceGroup(resource_group_name);

	}
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

void OgreApplication::LoadModels(void){
	try{
		Ogre::String resource_group_name = "MyGame";
		Ogre::ResourceGroupManager& resource_group_manager = Ogre::ResourceGroupManager::getSingleton();
		//resource_group_manager.createResourceGroup(resource_group_name);
		bool is_recursive = false;
		resource_group_manager.addResourceLocation(MATERIAL_DIRECTORY + std::string("/media/mesh"), "FileSystem", resource_group_name, is_recursive);
		resource_group_manager.initialiseResourceGroup(resource_group_name);
		resource_group_manager.loadResourceGroup(resource_group_name);

	}
	catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

void OgreApplication::LoadSkybox(void){
	//skybox
	Ogre::SceneManager* scene_manager = ogre_root_->getSceneManager("MySceneManager");

	scene_manager->setSkyBox(true, "Skybox", 400.0f, false);

	//distance fog
	Ogre::ColourValue fadeColour(81.0/255.0, 22.0/255.0, 70.0/255.0);
	ogre_window_->getViewport(0)->setBackgroundColour(fadeColour);

	//scene_manager->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 50, 100);
	//scene_manager->setFog(Ogre::FOG_EXP, fadeColour, 0.0003);
}

void OgreApplication::MainLoop(void){

    try {

        /* Main loop to keep the application going */

        ogre_root_->clearEventTimes();

        while(!ogre_window_->isClosed()){
            ogre_window_->update(false);

            ogre_window_->swapBuffers();

            ogre_root_->renderOneFrame();

            Ogre::WindowEventUtilities::messagePump();
        }
    }
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

bool OgreApplication::frameRenderingQueued(const Ogre::FrameEvent& fe){
	
	physicsManager->pollTotalEvents();

	player->updateCamera();

	if (keyboard_->isKeyDown(OIS::KC_ESCAPE)){
		ogre_root_->shutdown();
		ogre_window_->destroy();
	}

    return true;
}


void OgreApplication::windowResized(Ogre::RenderWindow* rw){

	/* Update the window and aspect ratio when the window is resized */
	int width = rw->getWidth(); 
    int height = rw->getHeight();
      
    Ogre::SceneManager* scene_manager = ogre_root_->getSceneManager("MySceneManager");
    Ogre::Camera* camera = scene_manager->getCamera("MyCamera");

	if (camera != NULL){
		//std::cout << "1 " << (double)width/height << std::endl;
		camera->setAspectRatio((float)((double)width/height));
    }

	const OIS::MouseState &ms = mouse_->getMouseState();
    ms.width = width;
    ms.height = height;

	ogre_window_->resize(width, height);
	ogre_window_->windowMovedOrResized();
	ogre_window_->update();
}

void OgreApplication::loadEntity(Ogre::String _fileName, Ogre::String _objectName){
	/*//ObjectImporter modeler;

	//vector<ObjectImporter::Face> faceList;
	vector<Ogre::Vector3> verticeList;
	vector<Ogre::Vector3> normalList;
	vector<Ogre::Vector2> uvList;

	modeler.loadJSONModel(_fileName, faceList, verticeList, normalList, uvList);

	if(verticeList.size() != normalList.size() && faceList.size() == 0){
		cout << "ERROR: Problem in Format" << endl;
		return;
	}


	try{
		Ogre::ManualObject* object = NULL;

		object = ogre_root_->getSceneManager("MySceneManager")->createManualObject(_objectName);
		object->setDynamic(false);

		object->begin("ObjectMaterial", Ogre::RenderOperation::OT_TRIANGLE_LIST);

		for(int i = 0; i < verticeList.size(); i++){
			object->position(verticeList[i]);
			//object->normal(normalList[i]);
			//object->textureCoord((uvList.size() == 0)? (0,0): (uvList[i].x, uvList[i].y));
			object->colour(Ogre::ColourValue(0.0,1.0,0.0));
		}

		for(int i = 0; i < faceList.size(); i++){
			object->triangle(faceList[i].vertex[0], faceList[i].vertex[1], faceList[i].vertex[2]);
		}

		object->end();
		object->convertToMesh(_objectName);
	}
	catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }*/
}

void OgreApplication::createLoadedEntity(Ogre::String _objectName)
{
	GameObject* temp;

	if(_objectName.compare("empty") == 0 || _objectName.compare("") == 0 ){
		return;
	}

	if(_objectName.compare("SAF") == 0 || _objectName.compare("smallAlly_fighter") == 0){
		temp = factory->createGameObject(GameObject::objectType::smallAlly_fighter);
	}
	else if(_objectName.compare("SEF") == 0 || _objectName.compare("smallEnemy_fighter") == 0){
		temp = factory->createGameObject(GameObject::objectType::smallEnemy_fighter);
	}
	else if(_objectName.compare("SAB") == 0 || _objectName.compare("smallAlly_bomber") == 0){
		temp = factory->createGameObject(GameObject::objectType::smallAlly_bomber);
	}
	else if(_objectName.compare("SEB") == 0 || _objectName.compare("smallEnemy_bomber") == 0){
		temp = factory->createGameObject(GameObject::objectType::smallEnemy_bomber);
	}
	else if(_objectName.compare("LAC") == 0 || _objectName.compare("largeAlly_cmd") == 0){
		temp = factory->createGameObject(GameObject::objectType::largeAlly_cmd);
	}
	else if(_objectName.compare("LEC") == 0 || _objectName.compare("largeEnemy_cmd") == 0){
		temp = factory->createGameObject(GameObject::objectType::largeEnemy_cmd);
	}
	
	
	if(objectManager->getListSize() == 0){
		player->bindCamera((SmallShip*)temp, ogre_root_->getSceneManager("MySceneManager")->getRootSceneNode()->getChild("SAF_0"));//ogre_root_->getSceneManager("MySceneManager")->getRootSceneNode()->removeChild("SAF_0"));
	}
	
	objectManager->addObject(temp);

}

void OgreApplication::test(){
	
	Ogre::SceneManager* scene_manager = ogre_root_->getSceneManager("MySceneManager");
     Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

	 
	 //Ogre::Entity* entity = scene_manager->createEntity("Reference", "Carrier.mesh");
	 Ogre::Entity* entity = scene_manager->createEntity("Reference", "Platform.mesh");
	 
	 Ogre::SceneNode* node =root_scene_node->createChildSceneNode("Reference");
	 entity->setMaterialName("ShinyMaterial");
	 node->attachObject(entity);

	 node->setPosition(0.0,0.0,2.0);
	 node->setScale(5.0,5.0,5.0);
}


} // namespace ogre_application;