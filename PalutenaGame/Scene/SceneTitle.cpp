#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "FontManager.h"
#include "SoundManager.h"
#include "ColorManager.h"

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

	// PushA�L�[�\���ʒu
	constexpr int kPushAX = kScreenWidth * 0.354f;
	constexpr int kPushAY = kScreenHeight * 0.895;

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
	m_selectPos(kSelectPosX, kSelectPosY),
	m_bgPos(0, 0),
	m_fadeAlpha(255),
	m_fadeLetter(0)
{
	// �t�H���g�̃������m��
	m_pFontManager = new FontManager;
	// SE/BGM�������m��
	m_pSoundManager = new SoundManager;
	// �F�������m��
	m_pColorManager = new ColorManager;
}

SceneTitle::~SceneTitle()
{
	// �t�H���g�������̉��
	delete m_pFontManager;
	m_pFontManager = nullptr;
	// �T�E���h���������
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	// �F���������
	delete m_pColorManager;
	m_pColorManager = nullptr;
}

void SceneTitle::Init()
{
	Graph = LoadGraph("data/Map/patter.png");			// �w�i�ǂݍ���
	TitleGraph = LoadGraph("data/TitleGraph3.png");		// �^�C�g�����S�ǂݍ���
	Cursor = LoadGraph("data/Cursor.png");				// �J�[�\�����S�ǂݍ���
	PushA= LoadGraph("data/PushA.png");				// �uA�{�^���Ō���v�O���t�ǂݍ���
	SelectUI= LoadGraph("data/SelectUI.png");
	SelectUI2 = LoadGraph("data/SelectUI2.png");

	m_select = kSelectGameStart;

	m_isSceneEnd = false;
	isToExplanation = false;
	isToSelect = false;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;
	m_scrollX = 0;
	m_bgPos.x = 0;
	m_bgPos.y = 0;
	m_fadeAlpha = 255;
	m_fadeLetter = 0;

	//�T�E���h�}�l�[�W���[�̏�����
	m_pSoundManager->Init();
	m_pSoundManager->BGMDefo();
}

void SceneTitle::Update()
{
	m_pSoundManager->SetBgmVolume();
	m_pSoundManager->SetSeVolume();

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
	DeleteGraph(Cursor);
	DeleteGraph(PushA);

	StopSoundMem(m_pSoundManager->m_bgmDefo);
	m_pSoundManager->End();
}

void SceneTitle::StringDraw()
{
	for (int i = 0; i < 3; i++){
		DrawGraph(m_selectPos.x, kSelectPosY + (kCharInterval * i),
			SelectUI, false);
	}

	DrawGraph(m_selectPos.x, m_selectPos.y, SelectUI2, true);

	DrawExtendGraph(m_selectPos.x - 20, m_selectPos.y - 20,
		m_selectPos.x + kSelectSizeX + 30, m_selectPos.y + kSelectSizeY + 20, 
		Cursor, true);

	DrawStringToHandle(kSelectChirPosX+31, kSelectChirPosY,
		"�Q�[�����n�߂�", m_pColorManager->GetColorBlack(),
		m_pFontManager->GetFont());
	DrawStringToHandle(kSelectChirPosX + 100, kSelectChirPosY + kCharInterval,
		"�I�v�V����", m_pColorManager->GetColorBlack(), 
		m_pFontManager->GetFont());
	DrawStringToHandle(kSelectChirPosX + 31, kSelectChirPosY + kCharInterval * 2,
		"�Q�[�����I���", m_pColorManager->GetColorBlack(), 
		m_pFontManager->GetFont());

	// �����̓_�ŕ`��
	if (m_fadeLetter < 60)
	{
		DrawExtendGraph(kPushAX, kPushAY,
			kPushAX + 560, kPushAY + 80,
			PushA, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, 
		m_pColorManager->GetColorBlack(), true);
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
