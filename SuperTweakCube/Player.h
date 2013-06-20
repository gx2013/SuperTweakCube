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
	Ogre::Vector3 PlayerTranslate;		//���ģ��λ�Ʒ���
	float _rotation;					//ģ�ͷ���
	bool attacking;						//�Ƿ񹥻�״̬
	int walkedud;
	int walkedlr;
	Ogre::AnimationState* _aniState;	//����ģ�͵Ķ���1
	Ogre::AnimationState* _aniStateTop; //����ģ�͵Ķ���2

	Ogre::Entity* _CubeEnt;
	Ogre::SceneNode* _CubeNode;
	bool Cubeattack;
	int Cubetime;
	Ogre::Vector3 Cubedirect;
};