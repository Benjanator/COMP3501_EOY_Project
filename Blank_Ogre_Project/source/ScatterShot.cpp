#include "ScatterShot.h"


ScatterShot::ScatterShot(Ogre::SceneNode * newScatterShot,Ogre::Quaternion shipOrientation,Ogre::Vector3 shipPosition, bool lr):GameObject(GameObject::empty)
{
	
	m_pNode = newScatterShot;
	this->type = scattershot;
	m_pNode->setOrientation(shipOrientation);
	forward_Direction = shipOrientation *  Ogre::Vector3::NEGATIVE_UNIT_Z;
	left_Direction = shipOrientation *  Ogre::Vector3::NEGATIVE_UNIT_X;
	right_Direction = shipOrientation *  Ogre::Vector3::UNIT_X;
	down_Direction = shipOrientation *  Ogre::Vector3::NEGATIVE_UNIT_Y;


	m_pNode->setPosition(shipPosition + (forward_Direction *15) + (down_Direction*0.6));
	
	hasExploded = false;
	accel_Rate = 0.15;
	drift_Direction = Ogre::Vector3(0.0f);
	aabbCenter = Ogre::Vector3(0.0f, 0.230201f, -1.85835f);
	aabbSize = Ogre::Vector3(7.82431f, 2.87618f, 11.2258f);
	numMaterials = 1;


	generateCP(1000);

}


ScatterShot::~ScatterShot(void)
{
}

void ScatterShot::update(float _timer)
{
	splinetraj(_timer);
}

void ScatterShot::generateCP(int num_control_points){


	// Control points for the spline
		Ogre::Vector3 cp;
		float u,v,w;
		std::srand(std::time(0));
		/* Allocate memory for control points */
		//control_point = new Ogre::Vector3[num_control_points];

		/* Create control points of a piecewise spline */
		/* We store the control points in groups of 4 */
		/* Each group represents the control points (p0, p1, p2, p3) of a cubic Bezier curve */
		/* To ensure C1 continuity, we constrain the first and second point of each curve according to the previous curve */
    
		cp = m_pNode->getPosition()+ (forward_Direction *16) + (right_Direction * 1.2) + (down_Direction*0.6);
		controlPoints.push_back(cp);
		

		cp = m_pNode->getPosition()  + (forward_Direction *22) + (left_Direction * 1.2) + (down_Direction*-0.6);
		controlPoints.push_back(cp); 

	

		// Create remaining points
		for (int i = 2; i < num_control_points; i++){
			// Check if we have the first or second point of a curve
			// Then we need to constrain the points
			if (i % 4 == 0){
				// Constrain the first point of the curve
				// p3 = q0, where the previous curve is (p0, p1, p2, p3) and the current curve is (q0, q1, q2, q3)
				// p3 is at position -1 from the current point q0
				controlPoints.push_back(controlPoints.at(i-1));

				
			} else if (i % 4 == 1){
				// Constrain the second point of the curve
				// q1 = 2*p3 – p2
				// p3 is at position -1 and we add another -1 since we are at i%4 == 1 (not i%4 == 0)
				// p2 is at position -2 and we add another -1 since we are at i%4 == 1 (not i%4 == 0)
				controlPoints.push_back( 2.0*controlPoints.at(i-2) - controlPoints.at(i-3));
			} else {

				u= Ogre::Math::RangeRandom(-0.5,3.5);
				v= Ogre::Math::RangeRandom(-5,5);
				w= Ogre::Math::RangeRandom(-5,5);

				controlPoints.push_back(controlPoints.at(i-1) + (forward_Direction *u) + (left_Direction * v) + (down_Direction*w));

			}
		}

		/*for(int x=0; x<= controlPoints.size()-1;x++){
			std::cout << "Control Point:: " << controlPoints.at(x) << std::endl;
		}*/

}

void ScatterShot::move(){

	//look at set of control points, move to next pos
	m_pNode->translate(drift_Direction);
	m_pNode->needUpdate();
}

void ScatterShot::splinetraj(float _timer){

	// The phase of the particle repeats in a cyclic manner and is dependent of the particle id
	
	//float phase = two_pi*particle_id;
	float circtime = (static_cast<int>(_timer / 1.5 )% 56); // A cycle lasts 16 seconds
	//std::cout << "Time:: " << circtime << std::endl;
	// Change position of the particle based on a spline
	
	float t = circtime - floor(circtime); // Fractional part, 0-1
	
	// Spline evaluation
	
    float p1w = (1 - t)*(1 - t)*(1 - t);
    float p2w = 3 * t*(1 - t)*(1 - t);
    float p3w = 3 * t*t*(1 - t);
    float p4w = t*t*t; 
    int wsec = int(floor(circtime))*4; // Picks which set of control points are used           
	Ogre::Vector3 Bt = p1w*controlPoints.at(0+wsec) + p2w*controlPoints.at(1+wsec) + p3w*controlPoints.at(2+wsec) + p4w*controlPoints.at(3+wsec);
	//std::cout << "BT:: " << Bt << std::endl;
	//m_pNode->setPosition(Bt);

	//m_pNode->lookAt(m_pNode->getPosition() + Bt, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_Z);
	m_pNode->lookAt( Bt, Ogre::Node::TS_WORLD,   Ogre::Vector3::UNIT_Z);
	
	m_pNode->translate(0.25 * (m_pNode->getOrientation() *  Ogre::Vector3::UNIT_Z));

	//forward_Direction = m_pNode->getOrientation() *  Ogre::Vector3::NEGATIVE_UNIT_Z;
	m_pNode->needUpdate();
}

void ScatterShot::collide(){
	
	m_pNode->setVisible(false);
	dead = true;
}

void ScatterShot::collide(int damage){
	collide();
}


void ScatterShot::particle(){
	//add these for anything that could collide
}


Ogre::SceneNode& ScatterShot::getNode()
{
	return *m_pNode;
}
