#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"OgreFramework.h"
#include"GameState.h"

class Player {
public:
	enum Action {FREE,ATTACK,REMOTEATTACK,JUMP};			//������ж���
	Player(Ogre::SceneManager* SceneMgr,Ogre::Camera* camera);
	void Create();
	void addTime(double time);
	void keyPressed(const OIS::KeyEvent &evt);
	void keyReleased(const OIS::KeyEvent &evt);
	void remoteAttack();
	void Attack(double time);
	void mousePressed(OIS::MouseButtonID id);
	bool AABBQuery();
	int Health;
	Action PlayerAction;		//�û����ж���
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
	Ogre::AnimationState* _aniStateSlice; //������
	Ogre::AnimationState* _aniStateJump;
	Ogre::Entity* _CubeEnt;
	Ogre::SceneNode* _CubeNode;
	bool Cubeattack;
	float Cubetime;
	Ogre::Vector3 Cubedirect;
	float ActionTime;
	Ogre::AxisAlignedBox pbox;				//AABB��Χ��
	Ogre::AxisAlignedBox hbox;
	Ogre::SceneNode* _PartNode;
	Ogre::ParticleSystem* partSystem;		//����ϵͳ ����
	Ogre::ParticleSystem* partSystem2;		//����ϵͳ ����2
	bool WindWalk;				//����һ�����粽����
	float WindWalktime;
	float SpeedUp;
};

#endif