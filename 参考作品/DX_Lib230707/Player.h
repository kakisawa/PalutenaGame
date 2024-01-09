#pragma once
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();
	// �O���t�B�b�N�̐ݒ�A���ƍ����̎擾���s��
	void SetGraphHandle(int handle);

	// ��`�̓����蔻����Ƃ�̂ɕK�v�ȏ����擾����֐�
	float GetLeft() const;	// ����X���W
	float GetTop() const;	// ���Y���W
	float GetRight() const;	// �E��X���W
	float GetBottom() const;// ����Y���W

private:
	int m_handle;
	// �O���t�B�b�N�̃T�C�Y
	int m_width;
	int m_height;

	float m_posX;
	float m_posY;

	// ���E���]�\��
	bool m_isTurn;
};

