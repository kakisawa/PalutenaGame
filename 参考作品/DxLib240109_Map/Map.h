#pragma once
#include <memory>

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

private:
	// �X�N���[���ʂ����肷�邽�߂Ƀv���C���[�̈ʒu��񂪕K�v
	std::shared_ptr<Player> m_pPlayer;
};