/********************************************************************
	created:	2012/02/25
	created:	25:2:2012   16:05
	filename: 	E:\Ogre\Project\Ogre_Project\Game_Demo\GameStateManager.h
	file path:	E:\Ogre\Project\Ogre_Project\Game_Demo
	file base:	GameStateManager
	file ext:	h
	author:		Star
	
	purpose:	Manage all the game states
*********************************************************************/

#ifndef _ZH_GAMESTATEMANAGER_H_
#define _ZH_GAMESTATEMANAGER_H_

#pragma once
#include "GameState.h"

class CGameStateManager : public CGameStateListener
{
public:
	typedef struct 
	{
		Ogre::String name;
		CGameState* state;
	} SState_info;

	CGameStateManager();
	~CGameStateManager();

	void ManageGameState(Ogre::String stateName, CGameState* state);

	CGameState* FindByName(Ogre::String stateName);

	void Start(CGameState* state);
	void ChangeGameState(CGameState* state);
	bool PushGameState(CGameState* state);
	void PopGameState();
	void PauseCurGameState();
	void Shutdown();
	void PopAllAndPushGameState(CGameState* state);

protected:
	void Init(CGameState* state);

	std::vector<CGameState*>		m_ActiveStateStack;
	std::vector<SState_info>	m_States;
	bool						m_bShutdown;
};

#endif //_ZH_GAMESTATEMANAGER_H_