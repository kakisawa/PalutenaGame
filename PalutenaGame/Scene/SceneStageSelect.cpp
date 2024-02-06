#include "SceneStageSelect.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

namespace
{
	// �����̕\���ʒu
	constexpr int kSelectChirPosX = kScreenWidth * 0.08f;
	constexpr int kSelectChirPosY = kScreenHeight * 0.15f;

	constexpr int kSelectBackChirPosX = kScreenWidth * 0.43f;
	constexpr int kSelectBackChirPosY = kScreenHeight * 0.85f;

	// �����̕\����
	constexpr int kCharInterval = 180;

	// �������͂ގl�p�̏����ʒu
	constexpr int kSelectPosX = kSelectChirPosX - 2;
	constexpr int kSelectPosY = kSelectChirPosY - 2;

	// �������͂ގl�p�̈ړ���
	constexpr int kSelectMoveY = 180;

	// �������͂ގl�p�̃T�C�Y
	constexpr int kSelectSizeX = kScreenWidth*0.245;
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
	// SE/BGM�������m��
	m_pSoundManager = new SoundManager;
	// �t�H���g�������m��
	m_pFontManager = new FontManager;
}

SceneStageSelect::~SceneStageSelect()
{
	// ���������
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	delete m_pFontManager;
	m_pFontManager = nullptr;
}

void SceneStageSelect::Init()
{
	Graph = LoadGraph("data/Map/patter.png");	// �w�i�ǂݍ���
	Cursor = LoadGraph("data/Cursor.png");		// �J�[�\�����S�ǂݍ���
	PushA = LoadGraph("data/PushA.png");				// �uA�{�^���Ō���v�O���t�ǂݍ���

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

	//�T�E���h�}�l�[�W���[�̏�����
	m_pSoundManager->Init();

	m_pSoundManager->BGMDefo();
}

void SceneStageSelect::Update()
{
	// ���L�[����������I����Ԃ��������
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		m_pSoundManager->SoundSelect();

		m_select = (m_select + 1) % kSclectNum;

		// �I�𒆂̎l�p����ԉ���������l�p����ԏ�ɖ߂�
		if (m_selectPos.y >= 918){
			m_selectPos.x = kSelectPosX;
			m_selectPos.y = kSelectPosY;
			return;
		}
		if (m_selectPos.y == kSelectPosY) {
			m_selectPos.y += kSelectMoveY;
		}
		else if(m_selectPos.y == 340){
			m_selectPos.x = 825;
			m_selectPos.y = 918;
		}
	}
	// ��L�[����������I����Ԃ���グ��
	else if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		m_pSoundManager->SoundSelect();

		m_select = (m_select - 1) % kSclectNum;

		// �I�𒆂̎l�p����ԏゾ������l�p����ԉ��ɖ߂�
		if (m_selectPos.y == kSelectPosY)
		{
			m_selectPos.x = 825;
			m_selectPos.y = 918;
			m_select = kBackTitle;
			return;
		}

		if (m_selectPos.y == 340) {
			m_selectPos.y -= kSelectMoveY;
		}
		else if (m_selectPos.y == 918)
		{
			m_selectPos.x = kSelectPosX;
			m_selectPos.y = 340;
			return;
		}
	}

	// A�{�^���������ꂽ�烁�C����ʂ֑J�ڂ���
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		// SE
		m_pSoundManager->SoundButton();
		
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
		default:
			break;
		}
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

void SceneStageSelect::Draw()
{
	// �w�i�̕`��
	BackDraw();	
	// �I�������̕����̕`��p
	StringDraw();
}

void SceneStageSelect::End()
{
	// �摜������������폜
	DeleteGraph(Graph);
	DeleteGraph(Cursor);

	m_pSoundManager->End();
}

void SceneStageSelect::StringDraw()
{
	// �X�e�[�W�Z���N�gBox
	for (int i = 0; i < 2; i++)
	{
		DrawBox(kSelectPosX, kSelectPosY + (kCharInterval * i), kSelectPosX + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0xF4EADE, true);

		DrawBox(kSelectPosX, kSelectPosY + (kCharInterval * i), kSelectPosX + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0x99e6ff, false);
	}
	// �^�C�g���ɖ߂�Box
	DrawBox(kSelectBackChirPosX, kSelectBackChirPosY,
		kSelectBackChirPosX + kSelectSizeX, kSelectBackChirPosY+75,
		0xF4EADE, true);

	// �I�𒆂̕������l�p�ŕ`��
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX,
		m_selectPos.y + kSelectSizeY, 0x00bfff, true);
	DrawExtendGraph(m_selectPos.x - 20, m_selectPos.y - 20,
		m_selectPos.x + kSelectSizeX + 20,
		m_selectPos.y + kSelectSizeY + 20,
		Cursor, true);

	DrawStringToHandle(kSelectChirPosX, kSelectChirPosY,
		"�@�X�e�[�W1", 0x000000, m_pFontManager->GetFont());
	DrawStringToHandle(kSelectChirPosX, kSelectChirPosY + kCharInterval,
		"�@�X�e�[�W2", 0x000000, m_pFontManager->GetFont());
	DrawStringToHandle(kSelectBackChirPosX, kSelectBackChirPosY, 
		"�^�C�g���ɖ߂�", 0x000000, m_pFontManager->GetFont());

	// �����̓_�ŕ`��
	if (m_fadeLetter < 60){
		DrawGraph(kSelectChirPosX, kSelectChirPosY + kCharInterval * 2.8f, PushA, true);
	}

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
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
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}