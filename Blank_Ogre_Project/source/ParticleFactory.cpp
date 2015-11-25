#include "ParticleFactory.h"


ParticleFactory::ParticleFactory(Ogre::SceneManager* _sm)
{
	scene_manager = _sm;
}


ParticleFactory::~ParticleFactory(void)
{
}

void ParticleFactory::CreateParticleType(Ogre::SceneNode* ){

}


void ParticleFactory::CreateThrusterParticleGeometry(Ogre::String object_name, int num_particles, float loop_radius, float circle_radius){

	//try {
		/* Retrieve scene manager and root scene node */
       // Ogre::SceneManager* scene_manager = ogre_root_->getSceneManager("MySceneManager");
        Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

        /* Create the 3D object */
        Ogre::ManualObject* object = NULL;
        object = scene_manager->createManualObject(object_name);
        object->setDynamic(false);
/*
        /* Create point list for the object */
		object->begin("", Ogre::RenderOperation::OT_POINT_LIST);

		/* Initialize random numbers */
		std::srand(std::time(0));

		/* Create a set of points which will be the particles */
		/* This is similar to drawing a torus: we will sample points on the surface of the torus */

		
		float maxspray = 1.5; // This is how much we allow the points to wander around
		float u, v, w, theta, phi, spray; // Work variables
		for (int i = 0; i < num_particles; i++){
			
			// Randomly select two numbers to define a point on the torus
			u = ((double) rand() / (RAND_MAX));
            v = ((double) rand() / (RAND_MAX));
            
			// Use u and v to define the point on the torus
            theta = u * Ogre::Math::TWO_PI;
			phi = v * Ogre::Math::TWO_PI;
			Ogre::Vector3 center = Ogre::Vector3(loop_radius*cos(theta), loop_radius*sin(theta), 0.0);
            Ogre::Vector3 normal = Ogre::Vector3(cos(theta)*cos(phi), sin(theta)*cos(phi), sin(phi));
			object->position(center + normal*circle_radius); // Position of the point
			object->colour(Ogre::ColourValue(((float) i)/((float) num_particles), 0.0, 1.0 - (((float) i)/((float) num_particles))));
			object->textureCoord(Ogre::Vector2(0.0, 0.0));

			// Now sample a point on a sphere to define a direction for points to wander around
			u = ((double) rand() / (RAND_MAX));
            v = ((double) rand() / (RAND_MAX));
			w = ((double) rand() / (RAND_MAX));
			
			theta = u * Ogre::Math::TWO_PI;
			phi = acos(2.0*v * -1.0);
			spray = maxspray*pow((float) w, (float) (1.0/4.0)); // Cubic root
			Ogre::Vector3 wander = Ogre::Vector3(spray*cos(theta)*cos(phi), spray*cos(theta)*sin(phi), sin(phi)*-2);

			object->normal(wander);
		}


        object->end();
		
		
		
        /* Convert triangle list to a mesh */
        object->convertToMesh(object_name);
  /*  }
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }*/
}


void ParticleFactory::CreateParticleEntity(Ogre::String entity_name, Ogre::String object_name, Ogre::String material_name,Ogre::SceneNode* parent, Ogre::Vector3 size){

	//try {
		/* Create one instance of the torus (one entity) */
		/* The same object can have multiple instances or entities */

		/* Retrieve scene manager and root scene node */
        //Ogre::SceneManager* scene_manager = ogre_root_->getSceneManager("MySceneManager");
        Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

		/* Create entity */
        Ogre::Entity* entity = scene_manager->createEntity(object_name);

		/* Apply a material to the entity */
		entity->setMaterialName(material_name);
		//particle_material_name_ = material_name;
		
		/* Create a scene node for the entity */
		/* The scene node keeps track of the entity's position */
        Ogre::SceneNode* scene_node = parent->createChildSceneNode(entity_name);
        scene_node->attachObject(entity);

		/* Scale the entity */
		scene_node->scale(size);
	/*}
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }*/
}
