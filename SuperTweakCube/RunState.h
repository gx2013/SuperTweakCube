/********************************************************************
	created:	2012/02/27
	created:	27:2:2012   15:44
	filename: 	E:\Ogre\Project\Ogre_Project\Game_Demo\RunState.h
	file path:	E:\Ogre\Project\Ogre_Project\Game_Demo
	file base:	RunState
	file ext:	h
	author:		Star
	
	purpose:	run state of game
*********************************************************************/

#include "GameState.h"

class CRunState : public CGameState
{
public:
	CRunState();

	DECLARE_GAMESTATE_CLASS(CRunState)

	void Enter();
	void CreateScene();
	void Exit();
	bool Pause();
	void Resume();

	bool keyPressed(const OIS::KeyEvent &evt);
	bool keyReleased(const OIS::KeyEvent &evt);

	bool mouseMoved( const OIS::MouseEvent &evt);
	bool mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id );
	bool mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id );

	void mouseEvent();

	void Update(double timeSinceLastFrame);

private:
	bool m_bQuit;
	Ogre::Entity* _SinbadEnt;
	Ogre::SceneNode* _SinbadNode;
	Ogre::Entity* _CubeEnt;
	Ogre::SceneNode* _CubeNode;
	Ogre::AnimationState* _aniState;
	Ogre::AnimationState* _aniStateTop;
	Ogre::Vector3 translate;
	Ogre::Vector3 SinbadTranslate;
	float _rotation;
	bool Cubeattack;
	int walkedud;
	int walkedlr;
	int Cubetime;
	Ogre::Vector3 Cubedirect;
};