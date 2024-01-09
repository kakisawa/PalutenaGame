#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw() const;
	// �O���t�B�b�N�̎w��
	void SetGrahpHandle(int handle);

	// �G�L�����N�^�[�J�n����
	// ��ʏォ�痎���n�߂�
	void Start();

	// ���݂��邩�`�F�b�N
	bool isExist() const { return m_isExist; }

	// �G�L�����N�^�[�̏����ʒu�ݒ�(�O���t�B�b�N��ݒ肵�Ă���s��)
	void SetStartPos();

	// ��`�̓����蔻����Ƃ�̂ɕK�v�ȏ����擾����֐�
	float GetLeft() const;	// ����X���W
	float GetTop() const;	// ���Y���W
	float GetRight() const;	// �E��X���W
	float GetBottom()const;	// ����Y���W

private:
	// �c���p�ɕۑ�����ʒu���̐�
	static constexpr int kPosLogFrame = 8;

private:
	int m_handle;
	// �O���t�B�b�N�̃T�C�Y
	int m_width;
	int m_height;

	// ���݂��邩�t���O
	bool m_isExist;
	
	// �ʒu���
	float m_posX[kPosLogFrame];
	float m_posY[kPosLogFrame];

	// �ړ���
	float m_moveY;

};