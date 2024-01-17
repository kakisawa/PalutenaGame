#include "SceneClear.h"
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
	constexpr int kInitSelectPosX = kCharPosX - 15;
	constexpr int kInitSelectPosY = kCharPosY - 10;
	// �I�𒆎l�p�̈ړ���
	constexpr int kSelectmoveY = 50;
	// �l�p�̑傫��
	constexpr int kSelectSizeX = 80;
	constexpr int kSelectSizeY = 30;
}


SceneClear::SceneClear():
	m_select(kSelectStage),
	m_isSceneSelectStage(false)
{
}

SceneClear::~SceneClear()
{
}

void SceneClear::Init()
{
	m_isSceneSelectStage = false;
	m_select = kSelectStage;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
}

void SceneClear::End()
{
}

void SceneClear::Update()
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
		case kSelectStage:
			m_isSceneSelectStage = true;
			break;
		default:
			break;
		}
	}
}

void SceneClear::Draw()
{
	DrawString(8, 16, "�N���A���", 0xffffff, false);
	//DrawString(Game::kScreenWidth * 0.5f, Game::kScreenHeight * 0.5f, "C�L�[�ŃX�e�[�W�I��", 0xffffff, false);
}
