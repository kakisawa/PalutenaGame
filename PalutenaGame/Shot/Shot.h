#pragma once
#include "Rect.h"
#include "Vec2.h"

class Player;
class SceneMain;

namespace
{
	// �v���C���[�̃T�C�Y
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 32;

	// ���������̃v���C���[�T�C�Y��Rect�N���X�Ƃ����p������������
	// �v���P

	// �e�̃T�C�Y
	constexpr int kShotWidth = 20;
	constexpr int kShotHeight = 20;

	// �e�̈ړ����x
	constexpr float kShotSpeed = 8.0f;
}

class Shot
{
public:
	Shot();
	virtual ~Shot();

	virtual void init();
	virtual void Update();
	virtual void Draw();

	void Start(Vec2 pos);

	void colShot();		// �e���G�ƂԂ������Ƃ��̏���

	Rect GetColRect() const { return m_colRect; }	// �����蔻��̋�`���擾����
	bool IsExist() const { return m_isExist; }
	
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }
	// �v���C���[�̌����Ă���������擾�����
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

private:
	int Se;

	int x;	// �e�̍��W
	int y;

	int dir;	// �e�̕���

	bool m_isExist;	// ���݂��邩�t���O(�g�p�����ǂ���)

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;

public:
	// �V���b�g��ł����v���C���[�̃|�C���^���o���Ă���
	Player* m_pPlayer;
	// SceneMain�̊֐����Ăяo�����߂Ƀ|�C���^���o���Ă���
	SceneMain* m_pMain;
};