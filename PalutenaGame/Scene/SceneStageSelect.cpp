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
}

SceneStageSelect::SceneStageSelect() :
	m_isSceneEnd(false),
	m_isSceneEnd2(false),
	m_isSceneEnd3(false),
	m_select(kStage1),
	m_selectPos(kSelectPosX, kSelectPosY)
{

}

void SceneStageSelect::Init()
{
	m_select = kStage1;
	m_isSceneEnd = false;
	m_isSceneEnd2 = false;
	m_isSceneEnd3 = false;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;
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
			break;
		case kStage2:
			break;
		case kSclectBack:
			m_isSceneEnd3 = true;
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
}

void SceneStageSelect::Draw()
{
	SetFontSize(64);

	DrawString(kChirPosX + 25, kChirPosY, "�X�e�[�W1", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval, "�X�e�[�W2", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval * 2, "�^�C�g���ɖ߂�", 0xffffff);

	SetFontSize(32);
	DrawString(kChirPosX, kChirPosY + kCharInterval * 3, "A�L�[�Ō���", 0xffffff);

	// �I�𒆂̕������l�p�ŕ`��
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX,
		m_selectPos.y + kSelectSizeY, 0x00bfff, false);
}

void SceneStageSelect::End()
{
}

bool SceneStageSelect::IsSceneEnd() const
{
	return m_isSceneEnd;
}

bool SceneStageSelect::IsSceneEnd2() const
{
	return m_isSceneEnd2;
}

bool SceneStageSelect::IsSceneEnd3() const
{
	return m_isSceneEnd3;
}

