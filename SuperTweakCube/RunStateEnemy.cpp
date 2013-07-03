#include"RunStateEnemy.h"

RunStateEnemy::RunStateEnemy(Ogre::SceneManager* SceneMgr,Ogre::Camera* camera,Ogre::Vector3 Postion)
{
	m_pSceneMgr=SceneMgr;
	m_pCamera = camera;
	EnemyAction = WAIT;
	Translate = Ogre::Vector3(0,0,0);
	ActionTime = 0;
	this->Postion = Postion;
	math = new Ogre::Math();
	health=100;
}

void RunStateEnemy::Create(Player *player)
{
	//����ģ��
	_EnemyEnt = m_pSceneMgr->createEntity("Elemental.MESH");
	_EnemyNode = m_pSceneMgr->createSceneNode();
	m_pSceneMgr->getRootSceneNode()->addChild(_EnemyNode);
	_EnemyNode->setScale(8.0f,8.0f,8.0f);
	_EnemyNode->setPosition(Postion);
	_EnemyNode->attachObject(_EnemyEnt);
	this->player = player;

	_aniStateWalk =_EnemyEnt->getAnimationState("Run");
	_aniStateWalk->setEnabled(false);
	_aniStateWalk->setLoop(false);

	_aniStateIdle =_EnemyEnt->getAnimationState("Idle");
	_aniStateIdle->setEnabled(false);
	_aniStateIdle->setLoop(false);

	_aniStateAttack =_EnemyEnt->getAnimationState("Attack2");
	_aniStateAttack->setEnabled(false);
	_aniStateAttack->setLoop(false);

	_aniStateDie =_EnemyEnt->getAnimationState("Die");
	_aniStateDie->setEnabled(false);
	_aniStateDie->setLoop(false);
}

void RunStateEnemy::addTime(double time)
{
	if(EnemyAction!=DEAD)			//������û�������������
	{
		if(ActionTime>0)
		{
			ActionTime-=time;
			if(EnemyAction==MOVE)
			{
				Move(time);
			}
			else if(EnemyAction==ATTACK)
				Attack(time);
			else if(EnemyAction==MOVETOPLAYER)
				MovetoPlayer(time);
			else if(EnemyAction==WAIT)
			{
				_aniStateWalk->setTimePosition(0.0f);
				_aniStateWalk->setEnabled(false);
				_aniStateAttack->setTimePosition(0.0f);
				_aniStateAttack->setEnabled(false);
				_aniStateDie->setTimePosition(0.0f);
				_aniStateDie->setEnabled(false);
				_aniStateIdle->setEnabled(true);
				if(_aniStateIdle->hasEnded())
					_aniStateIdle->setTimePosition(0.0f);
				_aniStateIdle->addTime(time/1000);
			}
		}
		else					//�����ж����
		{
			ActionTime=0;
			getNextAction();
		}
		ishurted();
	}
	else if(ActionTime>0)
		die(time);
}

void RunStateEnemy::getNextAction()
{
	Ogre::Real random = math->SymmetricRandom();		//����-1��1�������
	Ogre::Real distance;
	distance = _EnemyNode->getPosition().distance(m_pSceneMgr->getSceneNode("PNode")->getPosition());
	if(distance<70.0f&&distance>20.0f)			//������Ҿ���С��100ʱ������ƶ�
	{
		ActionTime = 1000;
		EnemyAction = MOVETOPLAYER;
	}
	else if(distance<20.0f)
	{
		ActionTime = 300;
		EnemyAction = ATTACK;
	}
	else if(EnemyAction == MOVE||EnemyAction == MOVETOPLAYER)
	{
		ActionTime = (random+1)*1000;
		EnemyAction = WAIT;
	}
	else if(EnemyAction == WAIT)		//��״̬Ϊ�ȴ�
	{
		ActionTime = (random+1)*1000;
		Translate = Ogre::Vector3(math->SymmetricRandom(),0,math->SymmetricRandom());		//�����������
		Translate = Translate/Translate.length();
		_EnemyNode->resetOrientation();
		_EnemyNode->setDirection(-Translate);				//ת���������ƶ�����һ��
		EnemyAction = MOVE;
	}
}

void RunStateEnemy::ishurted()
{
	Ogre::Real distance;
	distance = _EnemyNode->getPosition().distance(m_pSceneMgr->getSceneNode("CubeNode")->getPosition());
	if(distance<10.0f)			//��Cube�����С��һ������
	{
		health-=100;
		m_pSceneMgr->getSceneNode("CubeNode")->setPosition(Ogre::Vector3(0.0f,-1000.0f,0.0f));		//��Cube�ŵ���Զ�ĵط�......
	}
	if(player->PlayerAction==1)
	{
		distance = _EnemyNode->getPosition().distance(m_pSceneMgr->getSceneNode("PNode")->getPosition());
		if(distance<12.0f)			//���û������С��һ������
		{
			health-=40;
		}
	}
	if(health<=0)
	{
		ActionTime = 2000;
		EnemyAction = DEAD;
	}
}

void RunStateEnemy::Move(double time)
{
	_EnemyNode->translate(Translate * time/40);
	_aniStateIdle->setTimePosition(0.0f);
	_aniStateIdle->setEnabled(false);
	_aniStateAttack->setTimePosition(0.0f);
	_aniStateAttack->setEnabled(false);
	_aniStateDie->setTimePosition(0.0f);
	_aniStateDie->setEnabled(false);
	_aniStateWalk->setEnabled(true);
	if(_aniStateWalk->hasEnded())
		_aniStateWalk->setTimePosition(0.0f);
	_aniStateWalk->addTime(time/1000);
}

void RunStateEnemy::Attack(double time)			//�����ж�
{
	static bool attackmark = false;
	Ogre::Real distance;
	distance = _EnemyNode->getPosition().distance(m_pSceneMgr->getSceneNode("PNode")->getPosition());
	if(ActionTime<100&&attackmark==false)
		if(distance<30.0f)			//�Ƿ�Χ��
		{
			attackmark = true;
			if(player->Health>0)
				player->Health-=10;
		}
	if(ActionTime<=0)
		attackmark = false;
	_aniStateWalk->setTimePosition(0.0f);
	_aniStateWalk->setEnabled(false);
	_aniStateIdle->setTimePosition(0.0f);
	_aniStateIdle->setEnabled(false);
	_aniStateDie->setTimePosition(0.0f);
	_aniStateDie->setEnabled(false);
	_aniStateAttack->setEnabled(true);
	if(_aniStateAttack->hasEnded())
		_aniStateAttack->setTimePosition(0.0f);
	_aniStateAttack->addTime(time/1000);
}

void RunStateEnemy::MovetoPlayer(double time)
{
	Ogre::Real distance;
	Ogre::Vector3 PlayerPos;
	PlayerPos = m_pSceneMgr->getSceneNode("PNode")->getPosition();		//������λ��
	distance = _EnemyNode->getPosition().distance(PlayerPos);
	if(distance<20.0f)				//��������20��ʱ��������
	{
		ActionTime = 300;
		EnemyAction = ATTACK;
	}
	Translate = _EnemyNode->getPosition()-PlayerPos;
	Translate = Translate/Translate.length();
	_EnemyNode->resetOrientation();
	_EnemyNode->setDirection(Translate);
	_EnemyNode->translate(-Translate * time/40);
	_aniStateWalk->setEnabled(true);
	if(_aniStateWalk->hasEnded())
		_aniStateWalk->setTimePosition(0.0f);
	_aniStateWalk->addTime(time/1000);
}

void RunStateEnemy::die(double time)
{
	_aniStateWalk->setTimePosition(0.0f);
	_aniStateWalk->setEnabled(false);
	_aniStateIdle->setTimePosition(0.0f);
	_aniStateIdle->setEnabled(false);
	_aniStateAttack->setTimePosition(0.0f);
	_aniStateAttack->setEnabled(false);
	_aniStateDie->setEnabled(true);
	if(_aniStateDie->hasEnded())
	{
		ActionTime = 0;
	}
	_aniStateDie->addTime(time/1000);
}