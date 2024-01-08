#pragma once
#include <vector>
#include "Vec2.h"

class Player;
class EnemyBase;
class Back;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	//// �G�L�����N�^�[�̐���
	//void CreateEnemyLeft();
	//void CreateEnemyRight();
	//void CreateEnemyToPlayer();

	// �O���t�B�b�N�̃n���h��
	int m_gameScreenHandle;	// �Q�[�����

	int m_playerHandle;		// �v���C���[
	int m_enemyHandle;		// �G
	int m_backHandle;		// �w�i

	// �v���C���[
	Player* m_pPlayer;
	// �w�i
	Back* m_pBack;
	// �G
	std::vector<EnemyBase*> m_pEnemy;

};

