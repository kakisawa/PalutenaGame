#include "SceneGameClear.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneSecond.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "ColorManager.h"
#include "Player.h"
#include "Pad.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �^�C�g���摜�\���ʒu
	constexpr int kTitleGraphPosX = kScreenWidth * 0.27;
	constexpr int kTitleGraphPosY = kScreenHeight * 0.08f;
	// �X�R�A�摜�\���ʒu
	constexpr int kScoreGraphPosX = kScreenWidth * 0.25f;
	constexpr int kScoreGraphPosY = kScreenHeight * 0.58f;
	// PushA�L�[�摜�\���ʒu
	constexpr int kPushAX = kScreenWidth * 0.398f;
	constexpr int kPushAY = kScreenHeight * 0.901f;

	// �X�R�A���l�\���ʒu
	constexpr int kScorePosX = kScoreGraphPosX * 2.2f;
	constexpr int kScorePosY = kScoreGraphPosY;

	// �I�����l�p���̕����\���ʒu
	constexpr int kSelectChirPosX = kScreenWidth * 0.2;
	constexpr int kSelectChirPosY = kScreenHeight * 0.8f;
	// �I�����l�p���̕����\����
	constexpr int kCharInterval = 770;
	// �I�����l�p�̏����ʒu
	constexpr int kSelectPosX = kSelectChirPosX - 2;
	constexpr int kSelectPosY = kSelectChirPosY - 2;
	// �I�����l�p�̈ړ���
	constexpr int kSelectMoveX = kCharInterval;
	// �I�����l�p�̃T�C�Y
	constexpr int kSelectSizeX = 470;
	constexpr int kSelectSizeY = 75;


	// �X�N���[���ړ���
	constexpr float backGround_scale = 1.2f;
	// �w�i�̊g�嗦
	constexpr int kBgScale = 1;
}

SceneGameClear::SceneGameClear() :
	m_isSceneEnd(false),
	m_select(kScelectBackTitle),
	m_scrollX(0),
	m_fadeAlpha(255),
	m_fadeLetter(0),
	ResultScore(0),
	m_selectPos(kSelectPosX, kSelectPosY)
{
	// SE�EBGM�������m��
	m_pSoundManager = new SoundManager;
	// �t�H���g������
	m_pFontManager = new FontManager;
	// �F�������m��
	m_pColorManager = new ColorManager;
}

SceneGameClear::~SceneGameClear()
{
	// ���������
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	delete m_pFontManager;
	m_pFontManager = nullptr;
	delete m_pColorManager;
	m_pColorManager = nullptr;
}

void SceneGameClear::Init()
{
	Graph = LoadGraph("data/Map/patter4.png");
	TitleGraph = LoadGraph("data/GameClear.png");
	ScoreGraph = LoadGraph("data/Score.png");
	Cursor = LoadGraph("data/Cursor.png");
	SelectUI = LoadGraph("data/SelectUI.png");
	SelectUI2 = LoadGraph("data/SelectUI2.png");
	PushA= LoadGraph("data/PushA.png");				// �uA�{�^���Ō���v�O���t�ǂݍ���

	m_select = kScelectBackTitle;
	m_isSceneEnd = false;
	m_scrollX = 0;
	m_fadeAlpha = 255;
	m_fadeLetter = 0;
	ResultScore = 0;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;

	//�T�E���h�}�l�[�W���[�̏�����
	m_pSoundManager->Init();

	m_pSoundManager->BGMGameClear();
}

void SceneGameClear::Update()
{
	m_pSoundManager->SetBgmVolume();
	m_pSoundManager->SetSeVolume();

	// �E�L�[����������I����Ԃ��E�Ɉڂ�
	if (Pad::IsTrigger(PAD_INPUT_RIGHT))
	{
		// SE
		m_pSoundManager->SoundSelect();

		m_select = (m_select + 1) % kSclectNum;
		m_selectPos.x += kSelectMoveX;

		// �I�𒆂̎l�p����ԉ��ɂ�������l�p����ԏ�ɖ߂�
		if (m_selectPos.x > kSelectPosX + kSelectMoveX * (kSclectNum - 1))
		{
			m_selectPos.x = kSelectPosX;
		}
	}
	// ���L�[����������I����Ԃ����Ɉڂ�
	else if (Pad::IsTrigger(PAD_INPUT_LEFT))
	{
		// SE
		m_pSoundManager->SoundSelect();

		m_select = (m_select - 1) % kSclectNum;
		m_selectPos.x -= kSelectMoveX;

		// �I�𒆂̎l�p����ԉ��ɂ�������l�p����ԏ�ɖ߂�
		if (m_selectPos.x < kSelectPosX)
		{
			m_selectPos.x = kSelectPosX + kSelectMoveX * (kSclectNum - 1);
		}
	}

	// �G���^�[�L�[�������ꂽ��^�C�g����ʂ֑J�ڂ���
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		switch (m_select)
		{
		case kScelectBackTitle:
			m_isSceneEnd = true;
			break;
		case kScelectEnd:
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

	// �t�F�[�h�C���E�A�E�g
	if (m_isSceneEnd)
	{
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else {
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
}

void SceneGameClear::Draw()
{
	// �w�i�̕`��
	BackDraw();
	// �摜�`��
	UIDraw();
	// �I�������̕����̕`��p
	StringDraw();

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, m_pColorManager->GetColorBlack(), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void SceneGameClear::End()
{
	DeleteGraph(Graph);		// �w�i������������폜
	m_pSoundManager->End();
}

void SceneGameClear::StringDraw()
{
	DrawStringToHandle(kSelectChirPosX, kSelectChirPosY, "  �^�C�g���ɖ߂�",
		m_pColorManager->GetColorBlack(), m_pFontManager->GetFont());
	DrawStringToHandle(kSelectChirPosX + kCharInterval, kSelectChirPosY, "  �Q�[�����I���",
		m_pColorManager->GetColorBlack(), m_pFontManager->GetFont());

	ResultScore = SceneManager::s_ResultScore;
	DrawFormatStringToHandle(kScorePosX+2, kScorePosY+2,
		m_pColorManager->GetColorWhite(), m_pFontManager->GetFont3(),
		"%4d", ResultScore);
	DrawFormatStringToHandle(kScorePosX, kScorePosY,
		m_pColorManager->GetColorBlack(), m_pFontManager->GetFont3(),
		"%4d", ResultScore);

	// �����̓_�ŕ`��
	if (m_fadeLetter < 60)
	{
		DrawExtendGraph(kPushAX, kPushAY,
			kPushAX + 560, kPushAY + 80,
			PushA, true);
	}
}

void SceneGameClear::BackDraw()
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

void SceneGameClear::UIDraw()
{
	DrawGraph(kTitleGraphPosX, kTitleGraphPosY, TitleGraph, true);
	DrawGraph(kScoreGraphPosX, kScoreGraphPosY, ScoreGraph, true);

	// �^�C�g���ɖ߂�E�Q�[�����I������BOX
	for (int i = 0; i < 2; i++) {
		DrawGraph(kSelectPosX + (kCharInterval * i), kSelectPosY,
			SelectUI, false);
	}

	// �I�𒆂̕������l�p�ŕ`��
	DrawGraph(m_selectPos.x, m_selectPos.y,
		SelectUI2, false);
	DrawExtendGraph(m_selectPos.x - 20, m_selectPos.y - 20,
		m_selectPos.x + kSelectSizeX + 20,
		m_selectPos.y + kSelectSizeY + 20,
		Cursor, true);
}

bool SceneGameClear::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}