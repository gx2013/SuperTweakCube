/*
  ======================================================================
   SimpleListener.h --- protoype to show off the simple ogre listener.
  ----------------------------------------------------------------------
   Author : Zhu Xiaoyang (xiaoyang.zhu@ia.ac.cn)
   Creation Date : Apr 14 2011
   Description:
   This is a mini Ogre Listener, including SimpleFrameListener,
   SimpleKeyListener and SimpleMouseListener. 
  =======================================================================
*/
#ifndef __SimpleListener_H__
#define __SimpleListener_H__
#include "Ogre.h"
#include "OgreFrameListener.h"
#include <OIS/OIS.h>
using namespace Ogre;
/**
----------------------------------------------------------------------
    class SimpleFrameListener
----------------------------------------------------------------------
*/
class SimpleFrameListener : public FrameListener
{
public:
	SimpleFrameListener(OIS::Keyboard* keyboard, OIS::Mouse* mouse)
	{
		mKeyboard = keyboard;
		mMouse    = mouse;
	}
	//This gets called before the next frame is being rendered.
	bool frameStarted(const FrameEvent& evt)
	{
		//update the input devices
		mKeyboard->capture();
		mMouse->capture();
		//exit if key KC_ESCAPE pressed
		if( mKeyboard->isKeyDown( OIS::KC_ESCAPE ) )
			return false;
		else 
			return true;
	}
	//This gets called at the end of a frame
	bool frameEnded(const FrameEvent& evt)
	{
		return true;
	}
private:
	OIS::Keyboard* mKeyboard;
	OIS::Mouse*    mMouse;
};
/**
----------------------------------------------------------------------
    class SimpleKeyListener
----------------------------------------------------------------------
*/
class SimpleKeyListener : public OIS::KeyListener
{
public:
	bool keyPressed    (const OIS::KeyEvent& e)   { return true; }
	bool keyReleased   (const OIS::KeyEvent& e)   { return true; }
};
/**
----------------------------------------------------------------------
    class SimpleMouseListener
----------------------------------------------------------------------
*/
class SimpleMouseListener : public OIS::MouseListener
{
public:
	bool mouseMoved    (const OIS::MouseEvent& e) { return true; }
	bool mousePressed  (const OIS::MouseEvent& e, OIS::MouseButtonID id) { return true; }
	bool mouseReleased (const OIS::MouseEvent& e, OIS::MouseButtonID id) { return true; }
};
#endif //__SimpleListener_H__ 