#include "SceneGameOver.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneSecond.h"
#include "SoundManager.h"
#include "Pad.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �����̕\���ʒu
	constexpr int kChirPosX = kScreenWidth * 0.4;
	constexpr int kChirPosY = kScreenHeight * 0.3;

	// �����̕\����
	constexpr int kCharInterval = 120;

	// �������͂ގl�p�̏����ʒu
	constexpr int kSelectPosX = kChirPosX - 2;
	constexpr int kSelectPosY = kChirPosY - 2;

	// �������͂ގl�p�̈ړ���
	constexpr int kSelectMoveY = 120;

	// �������͂ގl�p�̃T�C�Y
	constexpr int kSelectSizeX = 700;
	constexpr int kSelectSizeY = 75;
}

SceneGameOver::SceneGameOver() :
	m_isSceneEnd(false),
	m_select(kScelectBackTitle),
	m_fadeAlpha(255),
	m_fadeLetter(0),
	m_selectPos(kSelectPosX, kSelectPosY)
{
	// SE/BGM�������m��
	m_pSoundManager = new SoundManager;
}

SceneGameOver::~SceneGameOver()
{
	// ���������
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
}

void SceneGameOver::Init()
{
	Graph = LoadGraph("data/Map/GameOverGraph.jpg");
	Cursor = LoadGraph("data/Cursor.png");				// �J�[�\�����S�ǂݍ���

	m_select= kScelectBackTitle;
	m_isSceneEnd = false;
	m_fadeAlpha = 255;
	m_fadeLetter = 0;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;

	//�T�E���h�}�l�[�W���[�̏�����
	m_pSoundManager->Init();
}

void SceneGameOver::Update()
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
		}

		// SE
		m_pSoundManager->SoundButton();

		m_isSceneEnd = true;

		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}

	// �����̓_��
	m_fadeLetter++;
	if (m_fadeLetter == 80)
	{
		m_fadeLetter = 0;
	}

	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}
}

void SceneGameOver::Draw()
{
	SetFontSize(32);

	DrawGraph(0, 0, Graph, false);
	DrawString(120, 120, "�Q�[���I�[�o�[���", GetColor(255, 255, 255));
	
	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���

	// �I�𒆂̕������l�p�ŕ`��
	DrawBox(m_selectPos.x, m_selectPos.y, 
		m_selectPos.x + kSelectSizeX, m_selectPos.y + kSelectSizeY, 
		0x00bfff, false);
	DrawExtendGraph(m_selectPos.x - 20, m_selectPos.y - 20,
		m_selectPos.x + kSelectSizeX + 20, m_selectPos.y + kSelectSizeY + 20,
		Cursor, true);

	SetFontSize(64);

	DrawString(kChirPosX, kChirPosY, "�^�C�g����ʂɖ߂�", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval, "�Q�[�����I���", 0xffffff);

	// �����̓_�ŕ`��
	if (m_fadeLetter < 60)
	{
		SetFontSize(32);
		DrawString(kChirPosX + 123, kChirPosY + kCharInterval * 3.6, "A�L�[�Ō���", 0xffffff);
	}
}

void SceneGameOver::End()
{
	// �w�i������������폜
	DeleteGraph(Graph);

	m_pSoundManager->End();
}

bool SceneGameOver::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}