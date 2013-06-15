/********************************************************************
	created:	2012/02/27
	created:	27:2:2012   15:23
	filename: 	E:\Ogre\Project\Ogre_Project\Game_Demo\Main.cpp
	file path:	E:\Ogre\Project\Ogre_Project\Game_Demo
	file base:	Main
	file ext:	cpp
	author:		Star
	
	purpose:	Main function
*********************************************************************/

#include "DemoApp.h"

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char** argv)
#endif
{
	CDemoApp demo;
	try
	{
		demo.StartDemo();
	}
	catch (std::exception& e)
	{
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBoxA(NULL, e.what(), "An exception has occurred", MB_OK
			 | MB_ICONERROR |MB_TASKMODAL);
#else
		fprintf(stderr, "An excption has occurred: %s\n", e.what());
#endif
	}

	return 0;
}