#pragma once
#include <vector>
#include "Vec2.h"

namespace
{
	// ���Y�A�C�o����
	constexpr int MozuMax = 1;	// 17
	// ���o����
	constexpr int DeathMax = 1;	// 3
	// ���ڂ���o����
	constexpr int PumpMax = 1;	// 10���A�o���ĂȂ�
}

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

	int m_fadeAlpha;		// �t�F�[�h�C���A�A�E�g

	// �V�[������
	bool m_isSceneEnd;		// �V�[�����I�����鎞true�ɂ���


	// �v���C���[
	Player* m_pPlayer;
	// �w�i
	Back* m_pBack;

	// �G�l�~�[
	MozueyeEnemy* m_pMozueyeEnemy[MozuMax];
	DeathYourEnemy* m_pDeathYourEnemy[DeathMax];
	PumpkinEnemy* m_pPumpkinEnemy[PumpMax];
};