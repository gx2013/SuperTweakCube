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
	enum Action {WAIT,MOVE,MOVETOPLAYER,ATTACK,DEAD};			//状态
	Ogre::Math *math;
	Ogre::Vector3 Postion;				//位置
	Ogre::Entity* _EnemyEnt;
	Ogre::SceneNode* _EnemyNode;
	Ogre::SceneManager* m_pSceneMgr;
	Ogre::Camera* m_pCamera;
	Ogre::Vector3 Translate;		//模型位移方向
	float _rotation;					//模型方向
	int walkedud;
	int walkedlr;
	Ogre::AnimationState* _aniStateIdle;	//定义模型的动作
	Ogre::AnimationState* _aniStateWalk;	//定义模型的动作
	Ogre::AnimationState* _aniStateAttack;	//定义模型的动作
	Ogre::AnimationState* _aniStateDie;	//定义模型的动作
	Action EnemyAction;					//正在做的动作
	float ActionTime;						//动作剩余时间

	Player *player;
	int health;
};
