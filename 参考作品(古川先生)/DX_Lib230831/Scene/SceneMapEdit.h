#pragma once
#include "Game.h"
class SceneMapEdit
{
public:
	SceneMapEdit();
	~SceneMapEdit();

	void Init();
	void End();

	void Update();
	void Draw();

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
	// �J�[�\���̈ړ�
	void CursorUp(bool isLoop);
	void CursorDown(bool isLoop);
	void CursorLeft(bool isLoop);
	void CursorRight(bool isLoop);

	// �O���t�B�b�N�ɑ��݂���}�b�v�`�b�v�̐�
	int GetGraphChipNum();

	// �e�L�X�g�t�@�C���Ƃ��ă}�b�v�`�b�v�̃f�[�^���o��
	void OutputText();
	// �e�L�X�g�t�@�C���ǂݍ��݂̃e�X�g
	void InputText();

	// �o�C�i���f�[�^�Ƃ��ă}�b�v�f�[�^���o��
	void OutputBainary();
	// �o�C�i���f�[�^��ǂݍ���Ń}�b�v�Ƃ��Ďg�p����
	void InputBainary();

private:
	// �O���t�B�b�N�̃n���h��
	int m_bgHandle;
	// �O���t�B�b�N�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_graphChipNumX;
	int m_graphChipNumY;

	// �}�b�v�`�b�v�̔z�u���
	int m_chipData[kChipNumY][kChipNumX];

	// �J�[�\���ʒu �񎟌��z��̃C���f�b�N�X���f�[�^�Ƃ��Ď���
	int m_cursorX;
	int m_cursorY;

	// �J�[�\���ړ��̃��s�[�g����
	int m_upRepeatFrame;
	int m_downRepeatFrame;
	int m_leftRepeatFrame;
	int m_rightRepeatFrame;
};

