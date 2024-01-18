#pragma once
#include "Player.h"
#include "Enemy.h"

// �Q�[���V�[�����N���X������
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw();
	void End();		// �V�[���̏I������
	
	// �V�[�����I�������邩�ǂ���
	bool IsSceneEnd() const;

	bool IsCollision(const Player& player, const Enemy& enemy);

private:
	// ��ʓ��ɓ����ɑ��݂ł���G�̍ő吔
	static constexpr int kEnemyMax = 16;

private:

	int m_hk;		// �w�i
	int m_playerHandle;	// �v���C���[�̃O���t�B�b�N
	int m_enemyHandle;	// �G�̃O���t�B�b�N

	int m_bgmHandle;	// BGM�̃n���h��
	int m_enemyStartSe;	// �G���o�ꂷ�鎞�̌��ʉ�
	int m_playerDath;

	Player m_player;
	Enemy m_enemy[kEnemyMax];

	bool m_isGameOver;		// �Q�[���I�[�o�[���ǂ����̃t���O
	bool m_isSceneEnd;		// �V�[�����I�����鎞true�ɂ���
	int m_playFrameCount;	// �����c���Ă��鎞��

	// Enemy�̐�������
	int m_enemyCreateNum;	// ���܂łɐ��Y�����G�̐�
	int m_enemyWaitFrame;	// �G�����܂ł̑҂�����

	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;
};

