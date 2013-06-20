#include"OgreFramework.h"

class Player {
public:
	Player(Ogre::SceneManager* SceneMgr,Ogre::Camera* camera);
	void Create();
	void addTime(double time);
	void keyPressed(const OIS::KeyEvent &evt);
	void keyReleased(const OIS::KeyEvent &evt);
	void remoteAttack();
	void mousePressed(OIS::MouseButtonID id);
private:
	Ogre::Entity* _PlayerEnt;
	Ogre::SceneNode* _PlayerNode;
	Ogre::SceneManager* m_pSceneMgr;
	Ogre::Camera* m_pCamera;
	Ogre::Vector3 PlayerTranslate;		//玩家模型位移方向
	float _rotation;					//模型方向
	bool attacking;						//是否攻击状态
	int walkedud;
	int walkedlr;
	Ogre::AnimationState* _aniState;	//定义模型的动作1
	Ogre::AnimationState* _aniStateTop; //定义模型的动作2

	Ogre::Entity* _CubeEnt;
	Ogre::SceneNode* _CubeNode;
	bool Cubeattack;
	int Cubetime;
	Ogre::Vector3 Cubedirect;
};