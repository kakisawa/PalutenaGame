#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "Game.h"

class Player;
/// <summary>
/// �w�i�N���X
/// </summary>
class Bg
{
public:
	Bg();
	~Bg();

	void Init();
	void Update();
	void Draw();

	// �v���C���[�̈ʒu����X�N���[���ʂ����肷��
	int GetScrollX();
	int GetScrollY();

	// �v���C���[�̃|�C���^��ݒ�
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	// �O���t�B�b�N�̐ݒ�
	void SetHandle(int bgHandle) { m_bgHandle = bgHandle; }
	void SetMapHandle(int mapHandle) { m_mapHandle = mapHandle; }

	// �v���C���[�Ɠ������Ă��邩���肷��
	bool IsColPlayer();
	// �w�肵����`�Ɠ������Ă��邩���肷��
	bool IsCollision(Rect rect, Rect& chipRect);

private:
	// �V�[�����C���̃|�C���^
	Player* m_pPlayer;

	// �w�i�̃O���t�B�b�N
	int m_bgHandle;
	// �}�b�v�`�b�v�̃O���t�B�b�N
	int m_mapHandle;

	// �w�i�̕\���ʒu
	Vec2 m_bgPos;

	// �O���t�B�b�N�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_graphChipNumX;
	int m_graphChipNumY;
};