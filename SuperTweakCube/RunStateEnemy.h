#include"OgreFramework.h"
#include"Player.h"

class RunStateEnemy {
public:
	RunStateEnemy(Ogre::SceneManager* SceneMgr,Ogre::Camera* camera,Ogre::Vector3 Postion);
	void Create(Player *player);
	void addTime(double time);
	void Move(double time);
	void MovetoPlayer(double time);
	void Attack(double time);
	void getNextAction();
	void ishurted();
	void die(double time);
private:
	enum Action {WAIT,MOVE,MOVETOPLAYER,ATTACK,DEAD};			//״̬
	Ogre::Math *math;
	Ogre::Vector3 Postion;				//λ��
	Ogre::Entity* _EnemyEnt;
	Ogre::SceneNode* _EnemyNode;
	Ogre::SceneManager* m_pSceneMgr;
	Ogre::Camera* m_pCamera;
	Ogre::Vector3 Translate;		//ģ��λ�Ʒ���
	float _rotation;					//ģ�ͷ���
	int walkedud;
	int walkedlr;
	Ogre::AnimationState* _aniStateIdle;	//����ģ�͵Ķ���
	Ogre::AnimationState* _aniStateWalk;	//����ģ�͵Ķ���
	Ogre::AnimationState* _aniStateAttack;	//����ģ�͵Ķ���
	Ogre::AnimationState* _aniStateDie;	//����ģ�͵Ķ���
	Action EnemyAction;					//�������Ķ���
	float ActionTime;						//����ʣ��ʱ��

	Player *player;
	int health;
};
