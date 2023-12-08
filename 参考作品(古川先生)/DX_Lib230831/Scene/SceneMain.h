#pragma once
#include <vector>
#include "Vec2.h"

class Player;
class Bg;
class EnemyBase;
class ShotBase;
class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

	// ����̍��W�����ԋ߂��ɂ���G�̍��W��Ԃ��֐�
	Vec2 GetNearEnemyPos(Vec2 pos) const;
	// �V���b�g��ǉ�����
	// �o�^�ł��Ȃ������ꍇ��false��Ԃ�
	// �o�^�ł��Ȃ������ꍇ�͓�����pShot�������
	bool AddShot(ShotBase* pShot);

private:
	// �G�L�����N�^�[�̐���
	void CreateEnemyLeft();
	void CreateEnemyRight();
	void CreateEnemyToPlayer();

private:
	// �O���t�B�b�N�̃n���h��
	int m_gameScreenHandle;	// �Q�[�����

	int m_playerHandle;
	int m_enemyHandle;
	int m_bgHandle;

	// �v���C���[
	Player* m_pPlayer;
	// �w�i
	Bg* m_pBg;
	// �G
	std::vector<EnemyBase*> m_pEnemy;	// �z��̃T�C�Y�͎��s���Ɍ��߂�(����̓R���X�g���N�^)
	// EnemyBase* m_pEnemy[16];	

	// �V���b�g
	std::vector<ShotBase*> m_pShot;

	// 
	int m_wipeFrame;

	// �G�̓o��Ԋu
	int m_enemyInterval;

	// �_���[�W���󂯂����̉�ʗh�ꉉ�o
	int m_shakeFrame;
};