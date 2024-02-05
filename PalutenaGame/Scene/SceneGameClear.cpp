#include "SceneGameClear.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneSecond.h"
#include "SceneSecond.h"
#include "SoundManager.h"
#include "Pad.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �^�C�g�������\���ʒu
	constexpr int kTitleChirPosX = kScreenWidth * 0.03f;
	constexpr int kTitleChirPosY = kScreenHeight * 0.05f;

	// �X�R�A�����\���ʒu
	constexpr int kScoreChirPosX = kScreenWidth * 0.43f;
	constexpr int kScoreChirPosY = kScreenHeight * 0.15f;

	// �����̕\���ʒu
	constexpr int kSelectChirPosX = kScreenWidth * 0.15;
	constexpr int kSelectChirPosY = kScreenHeight * 0.85;

	// �����̕\����
	constexpr int kCharInterval = 770;

	// �������͂ގl�p�̏����ʒu
	constexpr int kSelectPosX = kSelectChirPosX - 2;
	constexpr int kSelectPosY = kSelectChirPosY - 2;

	// �������͂ގl�p�̈ړ���
	constexpr int kSelectMoveX = 770;

	// �������͂ގl�p�̃T�C�Y
	constexpr int kSelectSizeX = kScreenWidth * 0.31;
	constexpr int kSelectSizeY = 75;

	// �X�N���[���ړ���
	constexpr float backGround_scale = 1.2f;
	// �w�i�̊g�嗦
	constexpr int kBgScale = 1;
}

SceneGameClear::SceneGameClear():
	m_isSceneEnd(false),
	m_select(kScelectBackTitle),
	m_scrollX(0),
	m_fadeAlpha(255),
	m_fadeLetter(0),
	m_selectPos(kSelectPosX, kSelectPosY)
{
	// SE/BGM�������m��
	m_pSoundManager = new SoundManager;
}

SceneGameClear::~SceneGameClear()
{
	// ���������
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
}

void SceneGameClear::Init()
{
	Graph = LoadGraph("data/Map/patter4.png");
	Cursor = LoadGraph("data/Cursor.png");	// �J�[�\�����S�ǂݍ���

	m_select = kScelectBackTitle;
	m_isSceneEnd = false;
	m_scrollX = 0;
	m_fadeAlpha = 255;
	m_fadeLetter = 0;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;

	//�T�E���h�}�l�[�W���[�̏�����
	m_pSoundManager->Init();
}

void SceneGameClear::Update()
{
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
	// �I�������̕����̕`��p
	StringDraw();

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void SceneGameClear::End()
{
	// �w�i������������폜
	DeleteGraph(Graph);

	m_pSoundManager->End();
}

void SceneGameClear::StringDraw()
{
	for (int i = 0; i < 2; i++)
	{
		DrawBox(kSelectPosX + (kCharInterval * i), kSelectPosY,
			kSelectPosX + (kSelectSizeX + (kCharInterval * i)),kSelectPosY + kSelectSizeY,
			0xF4EADE, true);

		DrawBox(kSelectPosX + (kCharInterval * i), kSelectPosY,
			kSelectPosX +( kSelectSizeX+(kCharInterval * i)),kSelectPosY + kSelectSizeY,
			0x99e6ff, false);
	}

	// �I�𒆂̕������l�p�ŕ`��
	DrawBox(m_selectPos.x, m_selectPos.y,
		m_selectPos.x + kSelectSizeX, m_selectPos.y + kSelectSizeY,
		0x00bfff, true);
	DrawExtendGraph(m_selectPos.x - 20, m_selectPos.y - 20,
		m_selectPos.x + kSelectSizeX + 20, m_selectPos.y + kSelectSizeY + 20,
		Cursor, true);

	SetFontSize(96);
	DrawString(kScoreChirPosX, kScoreChirPosY, "�X�R�A", 0x000000);

	SetFontSize(64);

	DrawString(kTitleChirPosX, kTitleChirPosY, "�Q�[���N���A���", 0x000000);
	DrawString(kSelectChirPosX, kSelectChirPosY, "�^�C�g����ʂɖ߂�", 0x000000);
	DrawString(kSelectChirPosX + kCharInterval, kSelectChirPosY, "�Q�[�����I���", 0x000000);

	// �����̓_�ŕ`��
	if (m_fadeLetter < 60)
	{
		SetFontSize(32);
		DrawString(kSelectChirPosX + 123, kSelectChirPosY + kCharInterval * 3.6, "A�L�[�Ō���", 0xffffff);
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

bool SceneGameClear::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}