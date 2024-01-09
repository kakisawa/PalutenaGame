#pragma once
#include "Game.h"

class Bg
{public:
	Bg();
	~Bg();

	void Init();
	void Update();
	void Draw();

	// �O���t�B�b�N�̐ݒ�
	void SetHandle(int handle) { m_handle = handle; }

private:
	// �萔
	// 
	// �}�b�v�`�b�v�̏��
	static constexpr int kChipWidth = 32;
	static constexpr int kChipHeight = 32;

	// �`�b�v��u����
	static constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	static constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;


private:
	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// �O���t�B�b�N�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_graphChipNumX;
	int m_graphChipNumY;

	// �}�b�v�`�b�v�̔z�u���
	int m_chipData[kChipNumY][kChipNumX];
};

