#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "Util/Font.h"
#include "SoundManager.h"

namespace
{
	// �����̕\���ʒu
	constexpr int kSelectChirPosX = kScreenWidth * 0.38f;
	constexpr int kSelectChirPosY = kScreenHeight * 0.61f;

	// �����̕\����
	constexpr int kCharInterval = 110;

	// �������͂ގl�p�̏����ʒu
	constexpr int kSelectPosX = kSelectChirPosX - 2;
	constexpr int kSelectPosY = kSelectChirPosY - 2;

	// �������͂ގl�p�̈ړ���
	constexpr int kSelectMoveY = 110;

	// �������͂ގl�p�̃T�C�Y
	constexpr int kSelectSizeX = 460;
	constexpr int kSelectSizeY = 80;

	// �^�C�g�����S�\���ʒu
	constexpr int kLogoPosX = kScreenWidth * 0.08;
	constexpr int kLogoPosY = kScreenHeight * (-0.17f);

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
	// SE/BGM�������m��
	m_pSoundManager = new SoundManager;
}

SceneTitle::~SceneTitle()
{
	// �t�H���g�������̉��
	delete m_pFont;
	m_pFont = nullptr;
	// ���������
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
}

void SceneTitle::Init()
{
	Graph = LoadGraph("data/Map/patter.png");			// �w�i�ǂݍ���
	TitleGraph = LoadGraph("data/TitleGraph3.png");		// �^�C�g�����S�ǂݍ���
	Cursor = LoadGraph("data/Cursor.png");				// �J�[�\�����S�ǂݍ���

	m_select = kSelectGameStart;

	m_isSceneEnd = false;
	isToExplanation = false;
	isToSelect = false;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY + kSelectMoveY;
	m_scrollX = 0;
	m_bgPos.x = 0;
	m_bgPos.y = 0;
	m_fadeAlpha = 255;
	m_fadeLetter = 0;

	//�T�E���h�}�l�[�W���[�̏�����
	m_pSoundManager->Init();
}

void SceneTitle::Update()
{
	// ���L�[����������I����Ԃ��������
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		// SE
		m_pSoundManager->SoundSelect();

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
		// SE
		m_pSoundManager->SoundSelect();

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

		// SE
		m_pSoundManager->SoundButton();
	}

	// �w�i�X�N���[��
	m_scrollX += backGround_scale;

	// �����̓_��
	m_fadeLetter++;
	if (m_fadeLetter == 80)
	{
		m_fadeLetter = 0;
	}
	// �t�F�[�h�C��
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
	DrawExtendGraph(kLogoPosX, kLogoPosY, 
		kLogoPosX + kLogoSizeX, kLogoPosY + kLogoSizeY,
		TitleGraph, true);

	// �I�������̕����̕`��p
	StringDraw();
}

void SceneTitle::End()
{
	// �摜������������폜
	DeleteGraph(Graph);
	DeleteGraph(TitleGraph);

	m_pSoundManager->End();
}

void SceneTitle::StringDraw()
{
	for (int i = 0; i < 3; i++)
	{
		DrawBox(m_selectPos.x, kSelectPosY + (kCharInterval * i), m_selectPos.x + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0xF4EADE, true);

		DrawBox(m_selectPos.x, kSelectPosY + (kCharInterval * i), m_selectPos.x + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0x99e6ff, false);
	}

	// �I�𒆂̕������l�p�ŕ`��
	DrawBox(m_selectPos.x, m_selectPos.y,
		m_selectPos.x + kSelectSizeX, m_selectPos.y + kSelectSizeY, 
		0x00bfff, true);
	DrawExtendGraph(m_selectPos.x - 20, m_selectPos.y - 20,
		m_selectPos.x + kSelectSizeX + 20, m_selectPos.y + kSelectSizeY + 20, 
		Cursor, true);


	SetFontSize(64);

	DrawString(kSelectChirPosX + 100, kSelectChirPosY, "�������", 0x000000);

	//DrawStringToHandle(kChirPosX + 100, kChirPosY, "�������", 0x000000, m_pFont->m_TitleFont);
	DrawString(kSelectChirPosX, kSelectChirPosY + kCharInterval, "�Q�[�����n�߂�", 0x000000);
	DrawString(kSelectChirPosX, kSelectChirPosY + kCharInterval * 2, "�Q�[�����I���", 0x000000);

	// �����̓_�ŕ`��
	if (m_fadeLetter < 60)
	{
		SetFontSize(32);
		DrawString(kSelectChirPosX + 123, kSelectChirPosY + kCharInterval * 3.0f, "A�L�[�Ō���", 0xffffff);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
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
