#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

namespace
{
	// �����̕\���ʒu
	constexpr int kChirPosX = kScreenWidth * 0.38;
	constexpr int kChirPosY = kScreenHeight * 0.58;

	// �����̕\����
	constexpr int kCharInterval = 90;

	// �������͂ގl�p�̏����ʒu
	constexpr int kSelectPosX = kChirPosX-2;
	constexpr int kSelectPosY = kChirPosY-2;

	// �������͂ގl�p�̈ړ���
	constexpr int kSelectMoveY = 90;

	// �������͂ގl�p�̃T�C�Y
	constexpr int kSelectSizeX =460;
	constexpr int kSelectSizeY = 75;

	// �^�C�g�����S�\���ʒu
	constexpr int kLogoPosX = kScreenWidth * 0.13;
	constexpr int kLogoPosY = -220;

	// �^�C�g�����S�T�C�Y
	constexpr int kLogoSizeX = 1450;
	constexpr int kLogoSizeY = 1100;
}

SceneTitle::SceneTitle() :
	x(kLogoPosX),
	y(kLogoPosY),
	m_isSceneEnd(false),
	isToExplanation(false),
	isToSelect(false),
	m_select(kSelectGameStart),
	m_selectPos(kSelectPosX, kSelectPosY+ kSelectMoveY),
	m_fadeAlpha(255)
{
}

void SceneTitle::Init()
{
	Graph = LoadGraph("data/Map/TitleGraph.jpg");	// �w�i�ǂݍ���
	TitleGraph = LoadGraph("data/TitleGraph.png");		// �^�C�g�����S�ǂݍ���

	m_select= kSelectGameStart;
	m_isSceneEnd = false;
	isToExplanation = false;
	isToSelect = false;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY+ kSelectMoveY;
}

void SceneTitle::Update()
{
	// ���L�[����������I����Ԃ��������
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
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

	// A�{�^���������ꂽ�烁�C����ʂ֑J�ڂ���
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		switch (m_select)
		{
		case kSclectOperation:
			m_isSceneEnd = true;
			isToExplanation = true;
			break;
		case kSelectGameStart:
			m_isSceneEnd = true;
			isToSelect = true;
			break;
		case kSclectEnd:
			DxLib_End();
			break;
		default:
			break;
		}

		//if (!m_isSceneEnd)
		//{
		//	// // ���ʉ��炷
		//	// PlaySoundFile("data/sound/TitleDecide.mp3", DX_PLAYTYPE_BACK);
		//	PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK, true);
		//}
		// �^�C�g����ʂ��I������SceneMain�Ɉړ����鏈������������!
	}

	if (m_isSceneEnd)
	{
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else
	{
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
}

void SceneTitle::Draw()
{
	DrawExtendGraph(x, y, x+kLogoSizeX, y+kLogoSizeY, TitleGraph, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���

	SetFontSize(64);

	DrawString(kChirPosX + 100, kChirPosY, "�������", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval, "�Q�[�����n�߂�", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval * 2, "�Q�[�����I���", 0xffffff);

	SetFontSize(32);
	DrawString(kChirPosX + 123, kChirPosY + kCharInterval * 3.6, "A�L�[�Ō���", 0xffffff);

	// �I�𒆂̕������l�p�ŕ`��
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX,
		m_selectPos.y + kSelectSizeY, 0x00bfff, false);
}

void SceneTitle::End()
{
	// �摜������������폜
	DeleteGraph(Graph);
	DeleteGraph(TitleGraph);
}

bool SceneTitle::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
