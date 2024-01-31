#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "Util/Font.h"

namespace
{
	// �����̕\���ʒu
	constexpr int kChirPosX = kScreenWidth * 0.38;
	constexpr int kChirPosY = kScreenHeight * 0.65;

	// �����̕\����
	constexpr int kCharInterval = 90;

	// �������͂ގl�p�̏����ʒu
	constexpr int kSelectPosX = kChirPosX - 2;
	constexpr int kSelectPosY = kChirPosY - 2;

	// �������͂ގl�p�̈ړ���
	constexpr int kSelectMoveY = 90;

	// �������͂ގl�p�̃T�C�Y
	constexpr int kSelectSizeX = 460;
	constexpr int kSelectSizeY = 75;

	// �^�C�g�����S�\���ʒu
	constexpr int kLogoPosX = kScreenWidth * 0.08;
	constexpr int kLogoPosY = -150;

	// �^�C�g�����S�T�C�Y
	constexpr int kLogoSizeX = 1637;
	constexpr int kLogoSizeY = 1089;

	// �X�N���[���ړ���
	constexpr float backGround_scale = 1.2f;
	// �w�i�̊g�嗦
	constexpr int kBgScale = 1;
}

SceneTitle::SceneTitle() :
	x(0),
	y(0),
	m_isSceneEnd(false),
	isToExplanation(false),
	isToSelect(false),
	m_scrollX(0),
	m_select(kSelectGameStart),
	m_selectPos(kSelectPosX, kSelectPosY + kSelectMoveY),
	m_bgPos(0, 0),
	m_fadeAlpha(255),
	m_fadeLetter(0)
{
	// �t�H���g�̃������m��
	m_pFont = new Font;
}

SceneTitle::~SceneTitle()
{
	// �t�H���g�������̉��
	delete m_pFont;
	m_pFont = nullptr;
}

void SceneTitle::Init()
{
	Graph = LoadGraph("data/Map/patter.png");	// �w�i�ǂݍ���
	TitleGraph = LoadGraph("data/TitleGraph3.png");		// �^�C�g�����S�ǂݍ���

	m_select = kSelectGameStart;

	m_isSceneEnd = false;
	isToExplanation = false;
	isToSelect = false;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY + kSelectMoveY;
	m_scrollX = 0;
	m_bgPos.x = 0;
	m_bgPos.y = 0;
	m_fadeLetter = 0;
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

	// �w�i�X�N���[��
	m_scrollX += backGround_scale;

	// �����̓_��
	m_fadeLetter++;
	if (m_fadeLetter == 80)
	{
		m_fadeLetter = 0;
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
	// �w�i�E�^�C�g���̕`��
	BackDraw();
	DrawExtendGraph(kLogoPosX, kLogoPosY, kLogoPosX + kLogoSizeX, kLogoPosY + kLogoSizeY, TitleGraph, true);

	// �I�������̕����̕`��p
	StringDraw();
}

void SceneTitle::End()
{
	// �摜������������폜
	DeleteGraph(Graph);
	DeleteGraph(TitleGraph);
}

void SceneTitle::StringDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���

	for (int i = 0; i < 3; i++)
	{
		DrawBox(m_selectPos.x, kSelectPosY + (kCharInterval * i), m_selectPos.x + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0xF4EADE, true);

		DrawBox(m_selectPos.x, kSelectPosY + (kCharInterval * i), m_selectPos.x + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0x99e6ff, false);
	}

	// �I�𒆂̕������l�p�ŕ`��
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX,
		m_selectPos.y + kSelectSizeY, 0x00bfff, true);

	SetFontSize(64);

	DrawString(kChirPosX + 100, kChirPosY, "�������", 0x000000);

	//DrawStringToHandle(kChirPosX + 100, kChirPosY, "�������", 0x000000, m_pFont->m_TitleFont);
	DrawString(kChirPosX, kChirPosY + kCharInterval, "�Q�[�����n�߂�", 0x000000);
	DrawString(kChirPosX, kChirPosY + kCharInterval * 2, "�Q�[�����I���", 0x000000);

	// �����̓_�ŕ`��
	if (m_fadeLetter < 60)
	{
		SetFontSize(32);
		DrawString(kChirPosX + 123, kChirPosY + kCharInterval * 3.6, "A�L�[�Ō���", 0xffffff);
	}
}

void SceneTitle::BackDraw()
{
	Size bg1Size;
	GetGraphSize(Graph, &bg1Size.width, &bg1Size.height);

	// �X�N���[���ʂ��v�Z
	int scrollBg = static_cast<int>(m_scrollX) % static_cast<int>(bg1Size.width * kBgScale);

	for (int index = 0; index < 4; index++)
	{
		DrawRotaGraph2(-scrollBg + index * bg1Size.width * kBgScale,
			kScreenHeight - bg1Size.height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			Graph, true);
	}
}

bool SceneTitle::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

bool SceneTitle::ToStage() const
{
	return isToSelect;
}

bool SceneTitle::ToExplanation() const
{
	return isToExplanation;
}
