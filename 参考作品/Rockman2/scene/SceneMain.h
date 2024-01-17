#pragma once
#include <vector>
#include "Vec2.h"

class Bg;
class ScenePause;
class Player;
class ShotBase;
class EnemyBase;
class RecoveryBase;

/// <summary>
/// �Q�[����ʂ̃N���X
/// </summary>
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

	// �V���b�g�̒ǉ�
	bool AddShot(ShotBase* pShot);

	// �A�C�e���h���b�v
	void DropHpSmallRecovery(int enemyIndex);	// HP����
	void DropHpGreatRecovery(int enemyIndex);	// HP���
	void DropShotSmallRecovery(int enemyIndex);	// �e����
	void DropShotGreatRecovery(int enemyIndex);	// �e���
	void DropLifeRecovery(int enemyIndex);		// �c�@��
	void DropFullHpRecovery();					// HP�S��

	// �A�C�e��2���̕\����Ԃ��擾
	bool GetIsExistLineMove() const {return m_isExistLineMove; }

	// �V�[���ړ��̎擾
	bool IsSceneGameOver() const { return m_isSceneGameOver; }	// �Q�[���I�[�o�[���
	bool IsSceneClear() const { return m_isSceneClear; }		// �N���A���

private:
	// �G�L�����N�^�[�̐���
	void CreateMatasaburo(); // �܂����Ԃ낤�̐���

private:
	// �O���t�B�b�N�̃n���h��
	int m_bgHandle;			// �w�i
	int m_mapHandle;		// �}�b�v�`�b�v
	int m_playerHandle;		// �v���C���[
	int m_enemyHandle;		// �G
	// HP�̉񕜃o�[�̒���
	int m_drawValue;

	// �v���C���[��E�ʂ��擾������ true:�擾����
	bool m_isGetFullHpRecovery;
	// �A�C�e��2������ʏ�ɑ��݂��邩
	bool m_isExistLineMove;

	// �V�[���ړ����邩 true:�V�[���ړ�����
	bool m_isSceneGameOver;	// �Q�[���I�[�o�[��ʂɈړ�
	bool m_isSceneClear;	// �N���A��ʂɈړ�

	// �w�i
	Bg* m_pBg;
	// �|�[�Y���
	ScenePause* m_pPause;
	// �v���C���[
	Player* m_pPlayer;
	// �V���b�g
	std::vector<ShotBase*> m_pShot;
	// �G
	std::vector<EnemyBase*> m_pEnemy;
	// �񕜃A�C�e��
	std::vector<RecoveryBase*> m_pRecovery;

	// �v���C���[�̌��ݒn
	Vec2 m_playerPos;
};

