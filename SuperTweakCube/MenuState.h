/********************************************************************
	created:	2012/02/27
	created:	27:2:2012   11:40
	filename: 	E:\Ogre\Project\Ogre_Project\Game_Demo\MenuState.h
	file path:	E:\Ogre\Project\Ogre_Project\Game_Demo
	file base:	MenuState
	file ext:	h
	author:		Star
	
	purpose:	the menu of the game
*********************************************************************/

#ifndef _ZH_MENUSTATE_H_
#define _ZH_MENUSTATE_H_

#pragma once

#include "GameState.h"

class CMenuState : public CGameState
{
public:
	CMenuState();

	DECLARE_GAMESTATE_CLASS(CMenuState)

	void Enter();
	void CreateScene();
	void Exit();

	bool keyPressed(const OIS::KeyEvent &evt);
	bool keyReleased(const OIS::KeyEvent &evt);

	bool mouseMoved( const OIS::MouseEvent &evt);
	bool mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id );
	bool mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id );

	void buttonHit(OgreBites::Button* button);

	void Update(double timeSinceLastFrame);

private:
	bool m_bQuit;
	
};

#endif //_ZH_MENUSTATE_H_