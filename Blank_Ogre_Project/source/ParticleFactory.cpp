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



void  ParticleFactory::CreateImplosionParticleGeometry(Ogre::String object_name, int num_particles){

	
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
		float trad = 1.4; // Defines the starting point of the particles
        float maxspray = 1.5; // This is how much we allow the points to deviate from the sphere
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


void  ParticleFactory::CreateSplineParticleGeometry(Ogre::String object_name, int num_particles, float loop_radius, float circle_radius){

		/* Retrieve scene manager and root scene node */
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
		/* This is similar to drawing a torus: we will sample points on a torus, but will allow the points to also
		   deviate a bit from the torus along the direction of a random vector */
        float maxspray = 0.5; // This is how much we allow the points to deviate along a normalized vector
		float u, v, w, theta, phi, spray; // Work variables
		for (int i = 0; i < num_particles; i++){
			
			// Get two random numbers
			u = ((double) rand() / (RAND_MAX));
            v = ((double) rand() / (RAND_MAX));
            
			// Use u and v to define a point on the torus with angles theta and phi
            theta = u * Ogre::Math::TWO_PI;
			phi = v * Ogre::Math::TWO_PI;

			// Get center of loop and point's normal on the torus
			Ogre::Vector3 center = Ogre::Vector3(loop_radius*cos(theta), loop_radius*sin(theta), 0.0);
            Ogre::Vector3 normal = Ogre::Vector3(cos(theta)*cos(phi), sin(theta)*cos(phi), sin(phi));

			// Next, we want to let the points deviate along the direction of a random vector
			// To obtain a random vector, we sample a point on the sphere
			// The point on the sphere minus the origin (0, 0) is the random vector

			// Randomly select two numbers to define a point in spherical coordinates
			u = ((double) rand() / (RAND_MAX));
            v = ((double) rand() / (RAND_MAX));
			
			// Use u to define the angle theta along one direction of a sphere
			theta = u * Ogre::Math::TWO_PI;
			// Use v to define the angle phi along the other direction of the sphere
			phi = acos(2.0*v - 1.0);
			// Get the point on the sphere (equivalent to a normalized direction vector since the origin is zero)
			Ogre::Vector3 direct = Ogre::Vector3(cos(theta)*sin(phi), sin(theta)*sin(phi), -cos(phi));
			// We need z = -cos(phi) to make sure that the z coordinate runs from -1 to 1 as phi runs from 0 to pi

			// Now, multiply a random amount of deviation by this vector, which is the deviation we will add to the point on the torus
			w = ((double) rand() / (RAND_MAX));
			spray = maxspray*pow((float) w, (float) (1.0/3.0)); // cbrt(w);
			Ogre::Vector3 wander = Ogre::Vector3(spray*direct.x, spray*direct.y, direct.z);
				
			// Add computed quantities to the object
			object->position(center + normal*circle_radius);
			object->normal(wander);
			object->colour(Ogre::ColourValue(((float) i)/((float) num_particles), 0.0, 0.0)); // Store particle id in the red channel as a float
			object->textureCoord(Ogre::Vector2(0.0, 0.0));
		}
		
		/* We finished the object */
        object->end();
		
        /* Convert triangle list to a mesh */
        object->convertToMesh(object_name);
   
}


void  ParticleFactory::CreateSplineControlPoints(Ogre::String control_points_name, int num_control_points, Ogre::String material_name){

		// Control points for the spline
		Ogre::Vector3 *control_point;

		/* Allocate memory for control points */
		control_point = new Ogre::Vector3[num_control_points];

		/* Create control points of a piecewise spline */
		/* We store the control points in groups of 4 */
		/* Each group represents the control points (p0, p1, p2, p3) of a cubic Bezier curve */
		/* To ensure C1 continuity, we constrain the first and second point of each curve according to the previous curve */
        
		// Initialize the first two control points to fixed values */
		control_point[0] = Ogre::Vector3(-20.0, 0.0, 0.0);
		control_point[1] = Ogre::Vector3(20.0, 0.0, 0.0);

		// Create remaining points
		for (int i = 2; i < num_control_points; i++){
			// Check if we have the first or second point of a curve
			// Then we need to constrain the points
			if (i % 4 == 0){
				// Constrain the first point of the curve
				// p3 = q0, where the previous curve is (p0, p1, p2, p3) and the current curve is (q0, q1, q2, q3)
				// p3 is at position -1 from the current point q0
				control_point[i] = control_point[i - 1];
			} else if (i % 4 == 1){
				// Constrain the second point of the curve
				// q1 = 2*p3 – p2
				// p3 is at position -1 and we add another -1 since we are at i%4 == 1 (not i%4 == 0)
				// p2 is at position -2 and we add another -1 since we are at i%4 == 1 (not i%4 == 0)
				control_point[i] = 2.0*control_point[i -2] - control_point[i - 3];
			} else {
				// Other points: we can freely assign random values to them
				// Get 3 random numbers
				float u, v, w;
				//u = ((double) rand() / (RAND_MAX));
				//v = ((double) rand() / (RAND_MAX));
				//w = ((double) rand() / (RAND_MAX));
				// Define control points based on u, v, and w and scale by the control point index
				//control_point[i] = Ogre::Vector3(u*3.0*(i/4 + 1), v*3.0*(i/4+1), w*3.0*(i/4+1));
				//control_point[i] = Ogre::Vector3(u*3.0*(i/4 + 1), v*3.0*(i/4+1), 0.0); // Easier to visualize with the control points on the screen

				//x = cx + r * cos(a)
				//y = cy + r * sin(a)
			
				u = 20 * cos(Ogre::Math::RangeRandom(-25,25));
				v = 20 * sin(Ogre::Math::RangeRandom(-50,50));
				w = (Ogre::Math::RangeRandom(-15,15));
				control_point[i] = Ogre::Vector3(u, w, v);

			}
		}

		/* Add control points to the material's shader */
		/* Translate the array of Ogre::Vector3 to an accepted format */
		float *shader_data;
		shader_data = new float[num_control_points*4];
		for (int i = 0; i < num_control_points; i++){
			shader_data[i*4] = control_point[i].x;
			shader_data[i*4 + 1] = control_point[i].y;
			shader_data[i*4 + 2] = control_point[i].z;
			shader_data[i*4 + 3] = 0.0;
		}

		/* Add array as a parameter to the shader of the specified material */
		Ogre::MaterialPtr mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(material_name));
		mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("control_point", shader_data, num_control_points, 4);

		/* Also create a mesh out of the control points, so that we can render them, if needed */
		
        Ogre::ManualObject* object = NULL;
        object = scene_manager->createManualObject(control_points_name);
        object->setDynamic(false);
		object->begin("", Ogre::RenderOperation::OT_POINT_LIST);
		for (int i = 0; i < num_control_points; i++){
			object->position(control_point[i]);
			// Color allows us to keep track of control point ordering
			object->colour(1.0 - ((float) i)/((float)num_control_points), 0.0, ((float) i)/((float)num_control_points));
		}
		object->end();
        object->convertToMesh(control_points_name);

		/* Free memory we used to store control points temporarily */
		delete [] control_point;
		
}





