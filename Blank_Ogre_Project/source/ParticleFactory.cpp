#include "ParticleFactory.h"


ParticleFactory::ParticleFactory(Ogre::SceneManager* _sm)
{
	scene_manager = _sm;
	materialCounter = 1;
}


ParticleFactory::~ParticleFactory(void)
{
}


void ParticleFactory::incrementCounter(){
	 materialCounter++;
}

void ParticleFactory::resetCounter(){
	materialCounter = 1;
}

Ogre::SceneNode* ParticleFactory::CreateParticleEntity(Ogre::String object_name, Ogre::String material_name,Ogre::SceneNode* parent, Ogre::Vector3 size){

		/* Create one instance of the torus (one entity) */
		/* The same object can have multiple instances or entities */

		/* Create entity */
		Ogre::String name = parent->getName() + object_name;
        //Ogre::Entity* entity = scene_manager->createEntity(object_name);
		Ogre::Entity* entity = scene_manager->createEntity(object_name);

		Ogre::MaterialPtr mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(material_name));
		//mat = mat->clone(object_name.append("_" +material_name.append("_" + Ogre::StringConverter::toString(materialCounter))));
		mat = mat->clone(name.append("_" +material_name.append("_" + Ogre::StringConverter::toString(materialCounter))));

		std::cout << "NAME: " << name << std::endl;
		//mat = mat->clone(object_name.append(material_name));
		/* Apply a material to the entity */
		entity->setMaterialName(mat->getName());
		//materialArray[numMaterials] = mat->getName();
		materialArray.push_back(mat->getName());
		

		/* Create a scene node for the entity */
		/* The scene node keeps track of the entity's position */
        Ogre::SceneNode* scene_node = parent->createChildSceneNode(mat->getName());
        scene_node->attachObject(entity);
		//scene_node->translate(0.5,0.5,-1);
		incrementCounter();
		/* Scale the entity */
		scene_node->scale(size);
		return scene_node;
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

		object->position(Ogre::Vector3(0.0f, 0.0f, -30.0f));
		object->colour(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
		object->textureCoord(Ogre::Vector2(0.0f, 0.0f));
		object->normal(Ogre::Vector3(0.0f, 0.0f, -30.0f));

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

void ParticleFactory::CreateExplosionParticleGeometry(Ogre::String object_name, int num_particles){

		/* Retrieve scene manager and root scene node */
        //Ogre::SceneManager* scene_manager = ogre_root_->getSceneManager("MySceneManager");
        Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

        /* Create the 3D object */
        Ogre::ManualObject* object = NULL;
        object = scene_manager->createManualObject(object_name);
        object->setDynamic(false);

        /* Create point list for the object */
		object->begin("", Ogre::RenderOperation::OT_POINT_LIST);

		/* Initialize random numbers */
		std::srand(std::time(0));

		/* Create a set of points which will be the particles */
		/* This is similar to drawing a sphere: we will sample points on a sphere, but will allow them to also
		   deviate a bit from the sphere along the normal (change of radius) */
		float trad = 0.04; // Defines the starting point of the particles
        float maxspray = 0.01; // This is how much we allow the points to deviate from the sphere
		float u, v, w, theta, phi, spray; // Work variables
		for (int i = 0; i < num_particles; i++){
			
			// Randomly select three numbers to define a point in spherical coordinates
			u = ((double) rand() / (RAND_MAX));
            v = ((double) rand() / (RAND_MAX));
            w = ((double) rand() / (RAND_MAX));

			// Use u to define the angle theta along one direction of a sphere
            theta = u * 2.0 * 3.1416;
			// Use v to define the angle phi along the other direction of the sphere
			phi = acos(2.0*v - 1.0);
			// Use we to define how much we can deviate from the surface of the sphere (change of radius)
            spray = maxspray*pow((float) w, (float) (1.0/3.0)); // Cubic root of w

			// Define the normal and point based on theta, phi and the spray
            Ogre::Vector3 normal = Ogre::Vector3(spray*cos(theta)*sin(phi), spray*sin(theta)*sin(phi), spray*cos(phi));
			object->position(normal.x*trad, normal.y*trad, normal.z*trad);
			object->normal(normal);
			object->colour(Ogre::ColourValue(i/(float) num_particles, 0.0, 1.0 - (i/(float) num_particles))); // We can use the color for debug, if needed
		}
		
		/* We finished the object */
        object->end();
		
        /* Convert triangle list to a mesh */
        object->convertToMesh(object_name);

}





