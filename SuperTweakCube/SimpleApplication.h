/*
  ==========================================================================
   SimpleApplication.h --- protoype to show off the simple ogre application.
  --------------------------------------------------------------------------
   Author : Zhu Xiaoyang (xiaoyang.zhu@ia.ac.cn)
   Creation Date : Apr 14 2011
   Description:
   This is a mini Ogre Application.  It does noting.
  ==========================================================================
*/
#ifndef __SimpleApplication_H__
#define __SimpleApplication_H__
#include "Ogre.h"
#include "SimpleListener.h"
using namespace Ogre;
/**
----------------------------------------------------------------------
    class SimpleApplication
----------------------------------------------------------------------
*/
class SimpleApplication
{
public:
	SimpleApplication()
	{
        mRoot = 0;
	}
	~SimpleApplication()
	{
		if(mRoot)
			OGRE_DELETE mRoot;
	}
	//start example
	void go() 
	{
		if( !setup() )
			return;
		/**
		----------------------------------------------------------------------
        8 start rendering
		@ blocks until a frame listener returns false. 
		  eg. from pressing escape in this example.
        ----------------------------------------------------------------------
		*/
		mRoot->startRendering();
		/**
		----------------------------------------------------------------------
        9 clean up
        ----------------------------------------------------------------------
		*/
		destroyScene();
	}
	//setup Ogre
	bool setup()
	{
		/**
		----------------------------------------------------------------------
        1 Enter ogre
        ----------------------------------------------------------------------
		*/
		mRoot = new Root;
		/**
		----------------------------------------------------------------------
        2 Configure resource paths
		@ Load resource paths from config file
		  File format is:
		  [ResourceGroupName]
		  ArchiveType=Path
		  .. repeat
		  For example:
		  [General]
		  FileSystem=media/
		  zip=packages/level1.zip
        ----------------------------------------------------------------------
		*/
		ConfigFile cf;
		cf.load("resources.cfg");
		//Go through all sections & settings in the file
		ConfigFile::SectionIterator seci = cf.getSectionIterator();
		String secName, typeName, archName;
		while ( seci.hasMoreElements() )
		{
			secName = seci.peekNextKey();
			ConfigFile::SettingsMultiMap  *settings = seci.getNext();
			ConfigFile::SettingsMultiMap::iterator i;
			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;
				ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, secName);
			}
		}
		/**
		----------------------------------------------------------------------
        3 Configures the application and creates the window
        ----------------------------------------------------------------------
		*/
		if ( !mRoot->showConfigDialog() )
		{
			//Ogre
			delete mRoot;
			return false; //Exit the application on cancel
		}
		mWindow = mRoot->initialise(true, "Simple Ogre App");
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
		/**
		----------------------------------------------------------------------
        4 Create the SceneManager
		@ SceneManager Type
		  ST_GENERIC = octree
          ST_EXTERIOR_CLOSE = simple terrain
          ST_EXTERIOR_FAR = nature terrain (depreciated)
          ST_EXTERIOR_REAL_FAR = paging landscape
          ST_INTERIOR = Quake3 BSP
        ----------------------------------------------------------------------
		*/
		mSceneMgr = mRoot->createSceneManager(ST_GENERIC);
		/**
		----------------------------------------------------------------------
        5 Create the camera
        ----------------------------------------------------------------------
		*/
		mCamera = mSceneMgr->createCamera("SimpleCamera");
		/**
		----------------------------------------------------------------------
        6 Create one viewport, entire window
        ----------------------------------------------------------------------
		*/
		Viewport* viewport = mWindow->addViewport(mCamera);
		/**
		----------------------------------------------------------------------
        7 Add OIS input handling
        ----------------------------------------------------------------------
		*/
		OIS::ParamList pl;
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;
		//tell OIS about the Ogre window
		mWindow->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr<<windowHnd;
		pl.insert( std::make_pair( std::string("WINDOW"), windowHndStr.str() ) );
		//setup the manager, keyboard and mouse to handle input
		inputManager = OIS::InputManager::createInputSystem( pl );
		keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject( OIS::OISKeyboard, true ) );
		mouse    = static_cast<OIS::Mouse*>(inputManager->createInputObject( OIS::OISMouse,    true ) );
		//tell OIS about the window's dimensions
		unsigned int width, height, depth;
		int top, left;
		mWindow->getMetrics(width, height, depth, left, top);
		const OIS::MouseState &ms = mouse->getMouseState();
		ms.width  = width;
		ms.height = height;
		//everything is set up, now we listen for input and frames (replaces while loops)
		//key events
		keyListener = new SimpleKeyListener();
		keyboard->setEventCallback(keyListener);
		//mouse events
		mouseListener = new SimpleMouseListener();
		mouse->setEventCallback(mouseListener);
		//render events
		mFrameListener = new SimpleFrameListener(keyboard, mouse);
		mRoot->addFrameListener(mFrameListener);
        return true;
	}
	//clean Ogre
	void destroyScene()
	{
		//OIS
		inputManager->destroyInputObject(mouse);             mouse = 0;
		inputManager->destroyInputObject(keyboard);          keyboard = 0;
		OIS::InputManager::destroyInputSystem(inputManager); inputManager = 0;
		//listeners
		delete mFrameListener;
		delete mouseListener;
		delete keyListener;
	}
private:
	Root* mRoot;
	Camera* mCamera;
	SceneManager* mSceneMgr;
	RenderWindow* mWindow;
	//OIS 
	OIS::InputManager* inputManager;
	OIS::Keyboard* keyboard;
	OIS::Mouse* mouse;
	//Listener
	SimpleKeyListener* keyListener;
	SimpleMouseListener* mouseListener;
	SimpleFrameListener* mFrameListener;
};
#endif //__SimpleApplication_H__