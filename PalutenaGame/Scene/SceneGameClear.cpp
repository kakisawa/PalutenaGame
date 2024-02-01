#include "SceneGameClear.h"
#include "SceneManager.h"
#include "SceneMain.h"
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

SceneGameClear::SceneGameClear():
	m_isSceneEnd(false),
	isStage1(false),
	isStage2(false),
	m_select(kScelectReturnHome),
	m_fadeAlpha(255),
	m_fadeLetter(0),
	m_selectPos(kSelectPosX, kSelectPosY+ kSelectMoveY)
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
	Graph = LoadGraph("data/Map/gg.jpg");
	Cursor = LoadGraph("data/Cursor.png");	// �J�[�\�����S�ǂݍ���

	m_select = kScelectReturnHome;
	m_isSceneEnd = false;
	isStage1 = false;
	isStage2 = false;
	m_fadeAlpha = 255;
	m_fadeLetter = 0;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY + kSelectMoveY;

	//�T�E���h�}�l�[�W���[�̏�����
	m_pSoundManager->Init();
}

void SceneGameClear::Update()
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

	// �G���^�[�L�[�������ꂽ��^�C�g����ʂ֑J�ڂ���
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		SceneMain* pSceneMain = new SceneMain;

		switch (m_select)
		{
		case kScelectRestart:
			if (pSceneMain->JustFinishStage1())
			{
				m_isSceneEnd = true;
				isStage1 = true;
				isStage2 = false;
			}
			//if(m_pSceneTwo->JustStage2())
			//{
			// m_isSceneEnd = true;
			// isStage1=true;
			// isStage2=true;
			//}
			break;
		case kScelectReturnHome:
			isStage1 = false;
			isStage2 = false;
			m_isSceneEnd = true;
			break;
		case kScelectEnd:
			DxLib_End();
			break;
		}

		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}

		delete pSceneMain;
		pSceneMain = nullptr;
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

void SceneGameClear::Draw()
{
	SetFontSize(32);

	DrawGraph(0, 0, Graph, false);
	DrawString(120, 120, "�Q�[���N���A���", GetColor(255, 255, 255));

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���

	for (int i = 0; i < 3; i++)
	{
		DrawBox(m_selectPos.x, kSelectPosY + (kCharInterval * i), m_selectPos.x + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0x99e6ff, false);
	}

	// �I�𒆂̕������l�p�ŕ`��
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX,
		m_selectPos.y + kSelectSizeY, 0x00bfff, true);
	DrawExtendGraph(m_selectPos.x - 20, m_selectPos.y - 20,
		m_selectPos.x + kSelectSizeX + 20, m_selectPos.y + kSelectSizeY + 20,
		Cursor, true);

	SetFontSize(64);

	DrawString(kChirPosX, kChirPosY, "������x�ŏ�����V��", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval, "�^�C�g����ʂɖ߂�", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval * 2, "�Q�[�����I���", 0xffffff);

	// �����̓_�ŕ`��
	if (m_fadeLetter < 60)
	{
		SetFontSize(32);
		DrawString(kChirPosX + 123, kChirPosY + kCharInterval * 3.6, "A�L�[�Ō���", 0xffffff);
	}
}

void SceneGameClear::End()
{
	// �w�i������������폜
	DeleteGraph(Graph);

	m_pSoundManager->End();
}

bool SceneGameClear::IsSceneEnd() const
{
	return m_isSceneEnd;
}
