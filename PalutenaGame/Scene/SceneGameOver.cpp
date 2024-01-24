#include "SceneGameOver.h"
#include "SceneManager.h"
#include "SceneMain.h"
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
	isStage1(false),
	isStage2(false),
	m_select(kScelectRestart),
	m_fadeAlpha(255),
	m_selectPos(kSelectPosX, kSelectPosY)
{

}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
	Graph = LoadGraph("data/Map/GameOverGraph.jpg");

	m_select=kScelectRestart;
	m_isSceneEnd = false;
	isStage1 = false;
	isStage2 = false;
	m_fadeAlpha = 255;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;
}

void SceneGameOver::Update()
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
			if(pSceneMain->JustFinishStage1())
			{
				m_isSceneEnd = true;
				isStage1 = true;
			}
			//if(m_pSceneTwo->JustStage2())
			//{
			// m_isSceneEnd = true;
			// isStage2=true;
			//}
			break;
		case kScelectReturnHome:
			m_isSceneEnd = true;
			break;
		case kScelectEnd:
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




		m_isSceneEnd = true;

		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}
}

void SceneGameOver::Draw()
{
	DrawGraph(0, 0, Graph, false);
	DrawString(120, 120, "�Q�[���I�[�o�[���", GetColor(255, 255, 255));
	DrawString(120, 120 + 64, "A�L�[�������Ă�������", GetColor(255, 255, 255));

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���

	SetFontSize(64);

	DrawString(kChirPosX, kChirPosY, "������x�ŏ�����V��", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval, "�^�C�g����ʂɖ߂�", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval * 2, "�Q�[�����I���", 0xffffff);

	// �I�𒆂̕������l�p�ŕ`��
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX,
		m_selectPos.y + kSelectSizeY, 0x00bfff, false);
}

void SceneGameOver::End()
{
	// �w�i������������폜
	DeleteGraph(Graph);
}

bool SceneGameOver::IsSceneEnd() const
{
	return m_isSceneEnd;
}
