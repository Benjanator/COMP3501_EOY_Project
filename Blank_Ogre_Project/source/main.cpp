#include <iostream>
#include <exception>
#include "ogre_application.h"

/* Macro for printing exceptions */
#define PrintException(exception_object)\
	std::cerr << exception_object.what() << std::endl

/* Main function that builds and runs the application */
int main(void){
    ogre_application::OgreApplication application;

	try {
		application.Init();
		//application.createLoadedEntity("MAN");
		//application.createLoadedEntity("SAF");
		application.createLoadedEntity("SAF");
		//application.createLoadedEntity("LEC");
		application.test();
		application.MainLoop();
	}
	catch (std::exception &e){
		PrintException(e);
	}

    return 0;
}
