#include "SceneStageSelect.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// �����\���ʒu
	constexpr int kCharPosX = Game::kScreenWidth / 2 - 20;
	constexpr int kCharPosY = Game::kScreenHeight / 2 + 70;
	// �����Ԋu
	constexpr int kCharInterval = 50;

	// �I�𒆎l�p�̏����ʒu
	constexpr int kInitSelectPosX = kCharPosX - 20;
	constexpr int kInitSelectPosY = kCharPosY - 10;
	// �I�𒆎l�p�̈ړ���
	constexpr int kSelectmoveY = 50;
	// �l�p�̑傫��
	constexpr int kSelectSizeX = 90;
	constexpr int kSelectSizeY = 30;
}

SceneStageSelect::SceneStageSelect() :
	m_select(kStage1),
	m_isSceneEnd(false),
	m_logoHandle(-1),
	m_selectPos(kInitSelectPosX, kInitSelectPosY)
{
	m_logoHandle = LoadGraph("data/image/Logo/TitleLogo.png");
}

SceneStageSelect::~SceneStageSelect()
{
}

void SceneStageSelect::Init()
{
	m_isSceneEnd = false;
	m_select = kStage1;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
}

void SceneStageSelect::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ���L�[����������I����Ԃ�1������
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		m_select = (m_select + 1) % kSelectNum;
		m_selectPos.y += kSelectmoveY; // �I�𒆂̎l�p�����Ɉړ�

		// �I�𒆂̎l�p����ԉ��ɂ�������l�p����ԏ�ɖ߂�
		if (m_selectPos.y > kInitSelectPosY + kSelectmoveY * (kSelectNum - 1))
		{
			m_selectPos.y = kInitSelectPosY;
		}
	}
	// ���L�[����������I����Ԃ�1�グ��
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;
		m_selectPos.y -= kSelectmoveY;	// �I�𒆂̎l�p����Ɉړ�

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSelectmoveY * (kSelectNum - 1);
		}
	}

	// Z�L�[���������Ƃ�
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// TODO:�I����Ԃɂ���Ĉړ����ς���
		switch (m_select)
		{
		case kStage1:
			m_isSceneEnd = true;
			break;
		case kStage2:
			break;
		case kStage3:
			break;
		case kBackTitle:
			break;
		default:
			break;
		}
	}
}

void SceneStageSelect::Draw()
{
	// ���S�\��
	DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 4, 0.8f, 0.0f, m_logoHandle, true);

	// TODO:�����T�C�Y�A�t�H���g�ύX
	DrawString(8, 16, "�X�e�[�W�I�����", 0xffffff, false);
	DrawString(kCharPosX, kCharPosY, "STAGE1", 0xffffff);
	DrawString(kCharPosX, kCharPosY + kCharInterval, "STAGE2", 0xffffff);
	DrawString(kCharPosX, kCharPosY + kCharInterval * 2, "STAGE3", 0xffffff);
	DrawString(kCharPosX - 15, kCharPosY + kCharInterval * 3, "BACKTITLE", 0xffffff);

	// �I�𒆂̕������l�p�ŕ`��
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX, m_selectPos.y + kSelectSizeY, 0x00bfff, false);
}

void SceneStageSelect::End()
{
}
