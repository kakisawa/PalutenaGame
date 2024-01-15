#pragma once
#include <vector>
#include "Vec2.h"

// �N���X�錾
class Player;
class Back;
class MozueyeEnemy;
class DeathYourEnemy;
class PumpkinEnemy;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void Update();
	void Draw();

	void End();

	// �V�[�����I������������
	bool IsSceneEnd() const;

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

	// �G�l�~�[
	int m_mozueyeEnemy;			// ���Y�A�C
	int m_deathYourEnemyGraph;	// ���O�����̎�
	int m_pumpkinEnemyGraph;	// �p���v�L���N

	// �V�[������
	bool m_isSceneEnd;		// �V�[�����I�����鎞true�ɂ���


	// �v���C���[
	Player* m_pPlayer;
	// �w�i
	Back* m_pBack;

	// �G�l�~�[
	std::vector<EnemyBase>* m_pEnemy;

	/*std::vector<MozueyeEnemy> m_pMozueyeEnemy;
	std::vector<DeathYourEnemy> m_pDeathYourEnemy;
	std::vector<PumpkinEnemy> m_pPumpkinEnemy;*/
};

