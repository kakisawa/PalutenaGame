#pragma once

class Player;

namespace
{
	// �v���C���[�̃T�C�Y
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 32;

	// ���������̃v���C���[�T�C�Y��Rect�N���X�Ƃ����p������������
	// �v���P

	// �e�̃T�C�Y
	constexpr int kShotWidth = 16;
	constexpr int kShotHeight = 16;

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

	void RightShot();
	void LeftShot();
	void UpShot();

	bool IsExist() const { return m_isExist; }

	// �v���C���[�̌����Ă���������擾�����
//	void SetPlayer(Player* pPlayer) { m_Player = pPlayer; }

protected:
	int Se;

	int x;
	int y;

	bool m_isExist;	// ���݂��邩�t���O(�g�p�����ǂ���)

public:
	// �v���C���[
	Player* m_Player;
};

