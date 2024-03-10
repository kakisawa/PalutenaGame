#include "Test.h"
#include "Pad.h"
#include "DxLib.h"

namespace {

	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;

	// �����̕\���ʒu
	constexpr int kSelectChirPosX = kScreenWidth * 0.08f;
	constexpr int kSelectChirPosY = kScreenHeight * 0.15f;

	constexpr int kSelectBackChirPosX = kScreenWidth * 0.43f;
	constexpr int kSelectBackChirPosY = kScreenHeight * 0.85f;

	// �����̕\����
	constexpr int kCharInterval = 180;

	// �������͂ގl�p�̏����ʒu
	constexpr int kSelectPosX = kSelectChirPosX - 2;
	constexpr int kSelectPosY = kSelectChirPosY - 2;

	// �������͂ގl�p�̈ړ���
	constexpr int kSelectMoveY = 180;

	// �������͂ގl�p�̃T�C�Y
	constexpr int kSelectSizeX = kScreenWidth * 0.245;
	constexpr int kSelectSizeY = 75;
}

Test::Test():
	m_select(kStage1),
	m_selectPos(kSelectPosX, kSelectPosY)
{
}

Test::~Test()
{
}

void Test::Init()
{
	m_fadeLetter = 0;
	m_select = kStage1;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;
}

void Test::Update()
{
	// ���L�[����������I����Ԃ��������
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		DrawString(1000, 500, "����������", 0xFFFFFF);

		m_select = (m_select + 1) % kSclectNum;

		m_selectPos.y += kSelectMoveY;

		// �I�𒆂̎l�p����ԉ��ɂ�������l�p����ԏ�ɖ߂�
		if (m_selectPos.y > kSelectPosY + kSelectMoveY * (kSclectNum - 1))
		{
			m_selectPos.y = kSelectPosY;
		}

	}
	// ��L�[����������I����Ԃ���グ��
	else if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		m_select = (m_select - 1) % kSclectNum;
		m_selectPos.y -= kSelectMoveY;

		// �I�𒆂̎l�p����ԉ��ɂ�������l�p����ԏ�ɖ߂�
		if (m_selectPos.y < kSelectPosY)
		{
			m_selectPos.y = kSelectPosY + kSelectMoveY * (kSclectNum - 1);
		}
	}

	// �����̓_��
	m_fadeLetter++;
	if (m_fadeLetter == 80)
	{
		m_fadeLetter = 0;
	}
}

void Test::Draw()
{
	// �X�e�[�W�Z���N�gBox
	for (int i = 0; i < 2; i++)
	{
		DrawBox(m_selectPos.x, kSelectPosY + (kCharInterval * i), m_selectPos.x + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0xF4EADE, true);

		DrawBox(m_selectPos.x, kSelectPosY + (kCharInterval * i), m_selectPos.x + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0x99e6ff, false);
	}
	// �^�C�g���ɖ߂�Box
	DrawBox(kSelectBackChirPosX, kSelectBackChirPosY,
		kSelectBackChirPosX + kSelectSizeX, kSelectBackChirPosY + 75,
		0xF4EADE, true);

	// �I�𒆂̕������l�p�ŕ`��
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX,
		m_selectPos.y + kSelectSizeY, 0x00bfff, true);


	DrawString(kSelectChirPosX, kSelectChirPosY,
		"�@�X�e�[�W1", 0x000000);
	DrawString(kSelectChirPosX, kSelectChirPosY + kCharInterval,
		"�@�X�e�[�W2", 0x000000);
	DrawString(kSelectBackChirPosX, kSelectBackChirPosY,
		"�^�C�g���ɖ߂�", 0x000000);

	// �����̓_�ŕ`��
	if (m_fadeLetter < 60) {
		DrawString(kSelectChirPosX, kSelectChirPosY + kCharInterval * 2.8f,
			" A�L�[�Ō���",0xFFFFFF);
	}
}
