#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"

SceneTitle::SceneTitle():
	m_isSceneEnd(false),
	m_bgmHandle(-1),
	m_decideSe(-1),
	m_fadeAlpha(255)
	
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	// BGM�̓ǂݍ���
	m_bgmHandle = LoadSoundMem("data/sound/BgmResult.wav");
	// ���ʉ��̓ǂݍ���
	m_decideSe = LoadSoundMem("data/sound/TitleDecide.mp3");

	// BGM�̍Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	// �t�F�[�h�C�������邽�߉���0����n�߂�
	ChangeVolumeSoundMem(0, m_bgmHandle);

	m_isSceneEnd = false;
}

void SceneTitle::Update()
{
	// ��ʂ̃t�F�[�h�l�𗘗p���ăT�E���h�̉��ʂ����肷��
	int volume = 255 - m_fadeAlpha;
	ChangeVolumeSoundMem(volume, m_bgmHandle);

	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_1)	// �p�b�h��1�{�^�� or �L�[�{�[�h��Z�L�[
	{
		if (!m_isSceneEnd)
		{
			// // ���ʉ��炷
			// PlaySoundFile("data/sound/TitleDecide.mp3", DX_PLAYTYPE_BACK);
			PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK, true);
		}

		// �^�C�g����ʂ��I������SceneMain�Ɉړ����鏈������������!
		m_isSceneEnd = true;
	}

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
	DrawString(120, 120, "�^�C�g�����", GetColor(255, 255, 255));
	DrawString(120, 120 + 16, "1�{�^���������Ă�������", GetColor(255, 255, 255));

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void SceneTitle::End()
{
	// BGM���~�߂�
	StopSoundMem(m_bgmHandle);

	// BGM������������폜
	DeleteSoundMem(m_bgmHandle);

	// ���ʉ�������������폜
	DeleteSoundMem(m_decideSe);
}

bool SceneTitle::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
