/********************************************************************
	created:	2012/02/25
	created:	25:2:2012   15:05
	filename: 	E:\Ogre\Project\Ogre_Project\Game_Demo\GameState.h
	file path:	E:\Ogre\Project\Ogre_Project\Game_Demo
	file base:	GameState
	file ext:	h
	author:		Star
	
	purpose:	the parent of all the game state
*********************************************************************/

#ifndef _ZH_GAMESTATE_H_
#define _ZH_GAMESTATE_H_

#pragma once

#include "OgreFramework.h"

class CGameState;

class CGameStateListener
{
public:
	CGameStateListener(){};
	virtual ~CGameStateListener(){};

	virtual void ManageGameState(Ogre::String stateName, CGameState* state) = 0;

	virtual CGameState*	FindByName(Ogre::String stateName) = 0;
	virtual void		ChangeGameState(CGameState* state) = 0;
	virtual bool		PushGameState(CGameState* state) = 0;
	virtual void		PopGameState() = 0;
	virtual void		PauseCurGameState() = 0;
	virtual void		Shutdown() = 0;
	virtual void		PopAllAndPushGameState(CGameState* state) = 0;
};

class CGameState : public OIS::KeyListener,public OIS::MouseListener, public OgreBites::SdkTrayListener
{
public:
	static void Create(CGameStateListener* parent, const Ogre::String name) {};

	void destroy() { delete this; }

	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual bool Pause() { return true;}
	virtual void Resume() {};
	virtual void Update(double timeSinceLastFrame) = 0;

protected:
	CGameState(){};
	
	CGameState*		FindByName(Ogre::String stateName) {return m_pListener->FindByName(stateName); }
	void			ChangeGameState(CGameState* state) { m_pListener->ChangeGameState(state); }
	bool			PushGameState(CGameState* state) { return m_pListener->PushGameState(state);}
	void			PopGameState() {m_pListener->PopGameState(); }
	void			Shutdown() { m_pListener->Shutdown(); }
	void			PopAllAndPushGameState(CGameState* state) { m_pListener->PopAllAndPushGameState(state); }

	CGameStateListener*		m_pListener;

	Ogre::Camera*			m_pCamera;
	Ogre::SceneManager*		m_pSceneMgr;
	Ogre::FrameEvent		m_FrameEvent;
};

// macro define
#define  DECLARE_GAMESTATE_CLASS(T)											\
static void Create(CGameStateListener* pListener, const Ogre::String name)	\
{																			\
	T* newState = new T();													\
	newState->m_pListener = pListener;										\
	pListener->ManageGameState(name, newState);								\
}																			\

#endif //_ZH_GAMESTATE_H_