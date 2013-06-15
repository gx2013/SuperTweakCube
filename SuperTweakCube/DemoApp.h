/********************************************************************
	created:	2012/02/27
	created:	27:2:2012   14:24
	filename: 	E:\Ogre\Project\Ogre_Project\Game_Demo\DemoApp.h
	file path:	E:\Ogre\Project\Ogre_Project\Game_Demo
	file base:	DemoApp
	file ext:	h
	author:		Star
	
	purpose:	for the demo
*********************************************************************/

#ifndef _ZH_DEMOAPP_H_
#define _ZH_DEMOAPP_H_

#pragma once

#include "OgreFramework.h"
#include "GameStateManager.h"

class CDemoApp
{
public:
	CDemoApp();
	~CDemoApp();

	void StartDemo();

private:
	CGameStateManager*	m_pGameStateMgr;
};

#endif //_ZH_DEMOAPP_H_