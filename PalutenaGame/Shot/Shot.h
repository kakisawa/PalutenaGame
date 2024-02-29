#pragma once
#include "Rect.h"
#include "Vec2.h"
#include <vector>

class Player;
class SceneMain;
class SceneSecond;

namespace
{
	// �v���C���[�̃T�C�Y
	constexpr int kPlayerWidth = 72;
	constexpr int kPlayerHeight = 72;

	// �e�̃T�C�Y
	constexpr int kShotWidth = 30;
	constexpr int kShotHeight = 30;

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
	void SetSecond(SceneSecond* pSecond) { m_pSecond = pSecond; }
	// �v���C���[�̌����Ă���������擾�����
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
private:
	int m_x;	// �e�̍��W
	int m_y;

	int m_dir;	// �e�̕���

	bool m_isExist;	// ���݂��邩�t���O(�g�p�����ǂ���)

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;
	// �ړ���	1�t���[��������̈ړ��ʂ�����
	Vec2 m_vec;
private:
	std::vector<Vec2> m_posLog;

public:
	// �V���b�g��ł����v���C���[�̃|�C���^���o���Ă���
	Player* m_pPlayer;
	// SceneMain�̊֐����Ăяo�����߂Ƀ|�C���^���o���Ă���
	SceneMain* m_pMain;
	SceneSecond* m_pSecond;
};