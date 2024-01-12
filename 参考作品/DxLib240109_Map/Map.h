#pragma once
#include <memory>
#include "Rect.h"

class Player;
class Map
{
public:
	Map(){}
	virtual ~Map(){}

	// �v���C���[�̃|�C���^��ݒ肷��
	void setPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	void Update();
	void Draw();

	// �v���C���[�̈ʒu����X�N���[���ʂ��擾����
	int GetScrollX();
	int GetScrollY();

	// �v���C���[�Ɠ������Ă��邩����
	bool IsColPlayer();		// bool�^��Ԃ��ϐ�������擪��Is��t����

	// �w�肵����`�Ɠ������Ă��邩����
	// �Q�Ƃ��g�p���ĂԂ������}�b�v�`�b�v�̋�`�����擾����
	bool IsCol(Rect rect, Rect& chipRect);
	

private:
	// �X�N���[���ʂ����肷�邽�߂Ƀv���C���[�̈ʒu��񂪕K�v
	std::shared_ptr<Player> m_pPlayer;
};