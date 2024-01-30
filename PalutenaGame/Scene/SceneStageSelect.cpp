#include "SceneStageSelect.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

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
	constexpr int kSelectSizeX = 460;
	constexpr int kSelectSizeY = 75;

	// �X�N���[���ړ���
	constexpr float backGround_scale = 1.2f;
	// �w�i�̊g�嗦
	constexpr int kBgScale = 1;
}

SceneStageSelect::SceneStageSelect() :
	m_select(kStage1),
	isStage1(false),
	isStage2(false),
	isBackTitle(false),
	m_scrollX(0),
	m_selectPos(kSelectPosX, kSelectPosY),
	m_bgPos(0, 0),
	m_fadeLetter(0),
	m_fadeAlpha(255)
{
}

SceneStageSelect::~SceneStageSelect()
{
}

void SceneStageSelect::Init()
{
	Graph = LoadGraph("data/Map/patter.png");	// �w�i�ǂݍ���

	m_select = kStage1;
	m_isSceneEnd = false;
	isStage1 = false;
	isStage2 = false;
	isBackTitle = false;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;
	m_scrollX = 0;
	m_bgPos.x = 0;
	m_bgPos.y = 0;
	m_fadeAlpha = 255;
	m_fadeLetter = 0;
}

void SceneStageSelect::Update()
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
		case kStage1:
 			m_isSceneEnd = true;
			isStage1 = true;
			break;
		case kStage2:
			m_isSceneEnd = true;
			isStage2 = true;
			break;
		case kBackTitle:
			isBackTitle = true;
			m_isSceneEnd = true;
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
	// �t�F�[�h�C��
	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}
}

void SceneStageSelect::Draw()
{
	BackDraw();
	StringDraw();
}

void SceneStageSelect::End()
{
}

void SceneStageSelect::StringDraw()
{
	SetFontSize(64);

	// �t�F�[�h�̕`��
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

	DrawString(kChirPosX + 25, kChirPosY, "�X�e�[�W1", 0x000000);
	DrawString(kChirPosX, kChirPosY + kCharInterval, "�X�e�[�W2", 0x000000);
	DrawString(kChirPosX, kChirPosY + kCharInterval * 2, "�^�C�g���ɖ߂�", 0x000000);

	// �����̓_�ŕ`��
	if (m_fadeLetter < 60)
	{
		//SetFontSize(32);
		DrawString(kChirPosX, kChirPosY + kCharInterval * 3, "A�L�[�Ō���", 0xffffff);
	}
}

void SceneStageSelect::BackDraw()
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

bool SceneStageSelect::IsSceneEnd() const
{
	return m_isSceneEnd;
}
