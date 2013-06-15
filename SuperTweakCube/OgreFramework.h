/********************************************************************
	created:	2012/02/25
	created:	25:2:2012   11:31
	filename: 	E:\Ogre\Project\Ogre_Project\Game_Demo\OgreFramework.h
	file path:	E:\Ogre\Project\Ogre_Project\Game_Demo
	file base:	OgreFramework
	file ext:	h
	author:		Star
	
	purpose:	ogre framework
*********************************************************************/

#ifndef _ZH_OGREFRAMEWORK_H_
#define _ZH_OGREFRAMEWORK_H_

#pragma once

#include <Ogre.h>
#include <ois/OIS.h>
#include <SdkTrays.h>

class COgreFramework: public Ogre::Singleton<COgreFramework>, OIS::KeyListener, OIS::MouseListener
{
public:
	COgreFramework();
	~COgreFramework();

	bool InitOgre(Ogre::String wndTitle, OIS::KeyListener* pKeyListener = 0, OIS::MouseListener* pMouseListener = 0);
	void UpdateOgre(double timeSinceLastFrame);

	// for key event
	bool keyPressed(const OIS::KeyEvent& evt);
	bool keyReleased(const OIS::KeyEvent& evt);

	// for mouse event
	bool mouseMoved(const OIS::MouseEvent& evt);
	bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);

public:
	Ogre::Root*				m_pRoot;
	Ogre::RenderWindow*		m_pRenderWnd;
	Ogre::Viewport*			m_pViewport;
	Ogre::Log*				m_pLog;
	Ogre::Timer*			m_pTimer;

	OIS::InputManager*		m_pInputMgr;
	OIS::Keyboard*			m_pKeyboard;
	OIS::Mouse*				m_pMouse;

	OgreBites::SdkTrayManager*	m_pTrayMgr;

private:
	COgreFramework(const COgreFramework&);
	COgreFramework& operator= (const COgreFramework&);

};

#endif //_ZH_OGREFRAMEWORK_H_