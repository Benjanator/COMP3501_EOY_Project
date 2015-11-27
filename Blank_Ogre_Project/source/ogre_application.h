#ifndef OGRE_APPLICATION_H_
#define OGRE_APPLICATION_H_

#include <exception>
#include <string>

#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"
#include "OIS/OIS.h"

#include "SmallShip.h"
#include "PlayerInput.h"
#include "ObjectManager.h"
#include "PhysicsManager.h"
#include "GameObjectFactory.h"

namespace ogre_application {


	/* A useful type to define */
	typedef std::vector<Ogre::String> Strings;

	/* Our exception type */
	class OgreAppException: public std::exception
    {
		private:
		    std::string message_;
	    public:
			OgreAppException(std::string message) : message_(message) {};
			virtual const char* what() const throw() { return message_.c_str(); };
	};

	/* Our Ogre application */
	class OgreApplication :
	    public Ogre::FrameListener, // Derive from FrameListener to be able to have render event callbacks
        public Ogre::WindowEventListener // Derive from FrameListener to be able to have window event callbacks
		{

        public:
            OgreApplication(void);
            void Init(void); // Call Init() before running the main loop
			void CreateTorus(Ogre::String object_name, Ogre::String material_name, float loop_radius = 0.6, float circle_radius = 0.2, int num_loop_samples = 90, int num_circle_samples = 30); // Create an object to show on the screen
			void SetupAnimation(Ogre::String object_name); // Setup animation for an object
            void MainLoop(void); // Keep application active
			void createLoadedEntity(Ogre::String _objectName);
			void test(void);

	

        private:
			// Create root that allows us to access Ogre commands
            std::auto_ptr<Ogre::Root> ogre_root_;
            // Main Ogre window
            Ogre::RenderWindow* ogre_window_;

			//Game Objects
			ObjectManager *objectManager;
			PhysicsManager* physicsManager;
			GameObjectFactory *factory;

			// For animating an object
			Ogre::AnimationState *animation_state_; // Keep state of the animation
			bool animating_; // Whether animation is on or off
			bool space_down_; // Whether space key was pressed

			// For particles
			float timer_;

			// Input managers
			OIS::InputManager *input_manager_;
			OIS::Mouse *mouse_;
			OIS::Keyboard *keyboard_;


			/* Methods to initialize the application */
			void InitRootNode(void);
			void InitPlugins(void);
			void InitRenderSystem(void);
			void InitWindow(void);
			void InitViewport(void);
			void InitEvents(void);
			void InitOIS(void);
			void LoadMaterials(void);
			void LoadModels(void);
			void LoadSkybox(void);
			
			/* Methods to handle events */
			bool frameRenderingQueued(const Ogre::FrameEvent& fe);
			void windowResized(Ogre::RenderWindow* rw);

			//

			

    }; // class OgreApplication

} // namespace ogre_application;

#endif // OGRE_APPLICATION_H_
