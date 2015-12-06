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
const Ogre::ColourValue viewport_background_color_g(0.3f, 0.7f, 0.05f);
float camera_near_clip_distance_g = 0.001f;
float camera_far_clip_distance_g = 9000.0;
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
int Score = 0;

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
	timer_ = 0.0f;
	/* Run all initialization steps */
    InitRootNode();
    InitPlugins();
    InitRenderSystem();
    InitWindow();
	InitEvents();
	InitOIS();
	InitViewport();
	InitOverlay();
	LoadMaterials();
	LoadModels();
	LoadSkybox();

	

	
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


		objectManager = new ObjectManager(ogre_root_->getSceneManager("MySceneManager"));
		factory = new GameObjectFactory(ogre_root_->getSceneManager("MySceneManager"));
		physicsManager = new PhysicsManager(objectManager);

		player = new PlayerInput( scene_manager,keyboard_,mouse_,factory,objectManager);

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


void OgreApplication::InitOverlay(void){

    // Create and initialize the overlay system
    Ogre::OverlaySystem *os = new Ogre::OverlaySystem();
    Ogre::SceneManager* scene_manager =   ogre_root_->getSceneManager("MySceneManager");
    scene_manager->addRenderQueueListener(os);

    // Initialize a font: assumes a standard Windows system
    Ogre::ResourceGroupManager& resource_group_manager = Ogre::ResourceGroupManager::getSingleton();
    resource_group_manager.addResourceLocation("C:\\Windows\\Fonts", "FileSystem");
    Ogre::FontManager& font_manager = Ogre::FontManager::getSingleton();
    Ogre::ResourcePtr font = font_manager.create("MyFont", "General");
    font->setParameter("type", "truetype");
    font->setParameter("source", "arial.ttf");
    font->setParameter("size", "26");
    font->setParameter("resolution", "96");
    font->load();

    // Create a panel for the overlay
    Ogre::OverlayManager& overlay_manager = Ogre::OverlayManager::getSingleton();
    Ogre::OverlayContainer* panel = (Ogre::OverlayContainer*) overlay_manager.createOverlayElement("Panel", "MyPanel");
    panel->setMetricsMode(Ogre::GMM_PIXELS);
    panel->setPosition(0, 0);
    panel->setDimensions(200, 100);
        
    // Create a text area and add it to the panel
	
    Ogre::TextAreaOverlayElement* text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlay_manager.createOverlayElement("TextArea", "MyTextArea_Score"));
    text_area->setMetricsMode(Ogre::GMM_PIXELS);
    text_area->setPosition(0, 0);
    text_area->setDimensions(200, 100);
    text_area->setFontName("MyFont");
	text_area->setCaption("Score: ");
    text_area->setCharHeight(26);
    text_area->setColour(Ogre::ColourValue(0.8, 0.0, 0.0));
    panel->addChild(text_area);

	text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlay_manager.createOverlayElement("TextArea", "MyTextArea_Health"));
    text_area->setMetricsMode(Ogre::GMM_PIXELS);
    text_area->setPosition(0, 26);
    text_area->setDimensions(200, 100);
    text_area->setFontName("MyFont");
	text_area->setCaption("Health: ");
    text_area->setCharHeight(26);
    text_area->setColour(Ogre::ColourValue(0.8, 0.0, 0.0));
    panel->addChild(text_area);

	text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlay_manager.createOverlayElement("TextArea", "MyTextArea_Reticule"));
    text_area->setMetricsMode(Ogre::GMM_PIXELS);
	text_area->setPosition(window_width_g/2-7, window_height_g/2);
    text_area->setDimensions(50,50);
    text_area->setFontName("MyFont");
	text_area->setCaption("X");
    text_area->setCharHeight(26);
    text_area->setColour(Ogre::ColourValue(0.8, 0.0, 0.0));
    panel->addChild(text_area);

	text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlay_manager.createOverlayElement("TextArea", "MyTextArea_GAMEOVER"));
    text_area->setMetricsMode(Ogre::GMM_PIXELS);
	text_area->setPosition(window_width_g/2-7, window_height_g/2 + 52);
    text_area->setDimensions(50,50);
    text_area->setFontName("MyFont");
	text_area->setCaption(" ");
    text_area->setCharHeight(52);
    text_area->setColour(Ogre::ColourValue(0.8, 0.0, 0.0));
    panel->addChild(text_area);

	text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlay_manager.createOverlayElement("TextArea", "MyTextArea_Rocket_CD"));
    text_area->setMetricsMode(Ogre::GMM_PIXELS);
	text_area->setPosition(0, 52);
    text_area->setDimensions(200, 100);
    text_area->setFontName("MyFont");
	text_area->setCaption("Rocket Cooldown: ");
    text_area->setCharHeight(26);
    text_area->setColour(Ogre::ColourValue(0.8, 0.0, 0.0));
    panel->addChild(text_area);

	text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlay_manager.createOverlayElement("TextArea", "MyTextArea_Laser_CD"));
    text_area->setMetricsMode(Ogre::GMM_PIXELS);
	text_area->setPosition(0, 78);
    text_area->setDimensions(200, 100);
    text_area->setFontName("MyFont");
	text_area->setCaption("Laser Cooldown: ");
    text_area->setCharHeight(26);
    text_area->setColour(Ogre::ColourValue(0.8, 0.0, 0.0));
    panel->addChild(text_area);

	text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlay_manager.createOverlayElement("TextArea", "MyTextArea_Scatter_CD"));
    text_area->setMetricsMode(Ogre::GMM_PIXELS);
	text_area->setPosition(0, 104);
    text_area->setDimensions(200, 100);
    text_area->setFontName("MyFont");
	text_area->setCaption("ScatterShot Cooldown: ");
    text_area->setCharHeight(26);
    text_area->setColour(Ogre::ColourValue(0.8, 0.0, 0.0));
    panel->addChild(text_area);

    // Create an overlay using the panel
    Ogre::Overlay* overlay = overlay_manager.create("MyOverlay");
    overlay->add2D(panel);
    overlay->show();
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

	scene_manager->setSkyBox(true, "Skybox", 3000.0f, true);

	//distance fog
	//Ogre::ColourValue fadeColour(81.0/255.0, 22.0/255.0, 70.0/255.0);
	//ogre_window_->getViewport(0)->setBackgroundColour(fadeColour);

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

			objectManager->cleanDestroyedObjects();

			if(physicsManager->spawnNextWave()){
				loadNextWave();
			}
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


	timer_ += fe.timeSinceLastFrame;

	physicsManager->pollTotalEvents(timer_);
	physicsManager->pollAiShots(factory,objectManager);

	Ogre::OverlayManager& overlay_manager = Ogre::OverlayManager::getSingleton();

	if(objectManager->getPlayerHealth() > 0 ){
	  player->updateCamera();
	  	
	  overlay_manager.getOverlayElement( "MyTextArea_Score")->setCaption("Score: " + Ogre::StringConverter::toString(objectManager->getScore()));
	  overlay_manager.getOverlayElement( "MyTextArea_Health")->setCaption("Health: " + Ogre::StringConverter::toString(objectManager->getPlayerHealth()));
	  overlay_manager.getOverlayElement("MyTextArea_Rocket_CD")->setCaption("Rocket Cooldown: " + Ogre::StringConverter::toString(player->getRocketCD()));
	  overlay_manager.getOverlayElement("MyTextArea_Laser_CD")->setCaption("Laser Cooldown: "  + Ogre::StringConverter::toString(player->getLaserCD()));
	  overlay_manager.getOverlayElement("MyTextArea_Scatter_CD")->setCaption("ScatterShot Cooldown: "  + Ogre::StringConverter::toString(player->getScatterCD()));
	}else{

	  overlay_manager.getOverlayElement("MyTextArea_GAMEOVER")->setCaption("GAME OVER");
	  overlay_manager.getOverlayElement( "MyTextArea_Health")->setCaption("Health: 0");
	}

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



void OgreApplication::createLoadedEntity(Ogre::String _objectName, Vector3 _spawnPoint)
{
	GameObject* temp;

	if(_objectName.compare("empty") == 0 || _objectName.compare("") == 0 ){
		return;
	}

	if(_objectName.compare("SAF") == 0 || _objectName.compare("smallAlly_fighter") == 0){
		temp = factory->createGameObject(GameObject::objectType::smallAlly_fighter, _spawnPoint);
	}
	else if(_objectName.compare("SEF") == 0 || _objectName.compare("smallEnemy_fighter") == 0){
		temp = factory->createGameObject(GameObject::objectType::smallEnemy_fighter, _spawnPoint);
	}
	else if(_objectName.compare("SAB") == 0 || _objectName.compare("smallAlly_bomber") == 0){
		temp = factory->createGameObject(GameObject::objectType::smallAlly_bomber, _spawnPoint);
	}
	else if(_objectName.compare("SEB") == 0 || _objectName.compare("smallEnemy_bomber") == 0){
		temp = factory->createGameObject(GameObject::objectType::smallEnemy_bomber, _spawnPoint);
	}
	else if(_objectName.compare("LAC") == 0 || _objectName.compare("largeAlly_cmd") == 0){
		temp = factory->createGameObject(GameObject::objectType::largeAlly_cmd, _spawnPoint);
	}
	else if(_objectName.compare("LEC") == 0 || _objectName.compare("largeEnemy_cmd") == 0){
		temp = factory->createGameObject(GameObject::objectType::largeEnemy_cmd, _spawnPoint);
	}
	
	
	if(objectManager->getListSize() == 0){
		player->bindCamera((SmallShip*)temp, ogre_root_->getSceneManager("MySceneManager")->getRootSceneNode()->getChild("SAF_0"));//ogre_root_->getSceneManager("MySceneManager")->getRootSceneNode()->removeChild("SAF_0"));
	}
	
	objectManager->addObject(temp);

}

void OgreApplication::loadFirstWave()
{
	/*Load MainPlayer*/
	createLoadedEntity("SAF", Vector3(0.0f, 0.0f, 100.0f));

	Ogre::Vector3 enemyPos = Ogre::Vector3(0.0f, 5.0f, -800.0f);

	/*Load Enemy Carrier*/
	createLoadedEntity("LEC", enemyPos);

	int fighterAmount = rand() % 5 + 1;
	float posX = -150.0f;

	/*Load Enemy Fighters*/
	for(int i = 0; i < fighterAmount; i++){
		posX = (posX + 50.0f != 0.0f)? posX + 50.0f: posX + 100.0f;
		createLoadedEntity("SEF", enemyPos + Vector3(posX, 0.0f, 0.0f));
	}

	int bomberAmount = rand() % 3 + 1;

	/*Load Enemy Bomber/Platforms*/
	for(int i = 0; i < bomberAmount; i++){
		createLoadedEntity("SEB", enemyPos + Vector3(0.0f, 0.0f, 75.0f * i));
	}
}

void OgreApplication::loadNextWave()
{
	cout << "Next Wave Has Appeared!" << endl;

	Vector3 enemyPos = objectManager->getObjectList().at(1)->getNode().getPosition();

	int fighterAmount = rand() % 5 + 1;
	float posX = -150.0f;

	/*Load Enemy Fighters*/
	for(int i = 0; i < fighterAmount; i++){
		posX = (posX + 50.0f != 0.0f)? posX + 50.0f: posX + 100.0f;
		createLoadedEntity("SEF", enemyPos + Vector3(posX, 0.0f, 0.0f));
	}

	int bomberAmount = rand() % 3 + 1;

	/*Load Enemy Bomber/Platforms*/
	for(int i = 0; i < bomberAmount; i++){
		createLoadedEntity("SEB", enemyPos + Vector3(0.0f, 0.0f, 75.0f * i));
	}
}

void OgreApplication::test(){
	

	/* GameObject* temp;
	 for(int i=0;i<3;i++){
		temp = factory->createGameObject(GameObject::objectType::smallEnemy_fighter);
		objectManager->addObject(temp);
	 }

	  for(int j=0;j<3;j++){
		temp = factory->createGameObject(GameObject::objectType::smallEnemy_bomber);
		objectManager->addObject(temp);
	 }

	  	temp = factory->createGameObject(GameObject::objectType::largeEnemy_cmd);
		objectManager->addObject(temp);
		
*/	
}


} // namespace ogre_application;