#pragma once
#include <memory>

class Map;
class Player
{
public:
	Player();
	virtual ~Player();

	// �}�b�v�̃|�C���^��ݒ肷��
	void SetMap(std::shared_ptr<Map> pMap) { m_pMap = pMap; }

	void Update();
	void Draw();

	// �v���C���[�̈ʒu���擾		// �v���C�x�[�g�̂܂܂��Ƒ��̃N���X�Ŏg�p�ł��Ȃ���
	float GetX() const { return m_x; }
	float GetY() const { return m_y; }

	// �v���C���[�̏㉺���E���W���擾
	float GetLeft();
	float GetRight(); 
	float GetTop();
	float GetBottom();

private:
	// Map�Ō��肵���X�N���[���ʂ��擾���邽�߂�Map�N���X�̏�񂪕K�v
	std::shared_ptr<Map>	m_pMap;

	// �W�����v���Ă��邩�ǂ����̃t���O������
	// �󒆂ɂ���ꍇ��true,�n�ʂɗ����Ă���ꍇ��false
	bool m_isJump;

	// �v���C���[�̑�����������Ƃ������W
	float m_x;
	float m_y;

	// �v���C���[�̉����x	1�t���[��������̈ړ���
	float m_moveX;
	float m_moveY;

};

