#include "SceneMain.h"
#include "DxLib.h"
#include <cassert>
#include "Game.h"

namespace
{
	// �Q�[���I�[�o�[���ɕ\�����镶����
	const char* const kGameOverString = "�Q�C���I�[�[�o�[�[";	// �����̒�`

	// �G�̏��������Ԋu(�t���[����)
	constexpr int kEnemyWaitFrameDefault = 60;
	// �G�̍ŒZ�����Ԋu
	constexpr int kEnemyWaitFrameMin = 3;
	// �G�̐����Ԋu��G���̐������邽�тɒZ�����邩
	constexpr int kEnemyWaitFrameChangeNum = 5;
	// ��x�����Ԋu��Z������Ƃ��ɉ��t���[���Z�����邩
	constexpr int kEnemyWaitFrameChangeFrame = 2;
}

SceneMain::SceneMain():
m_playerHandle(-1),
m_enemyHandle(-1),
m_bgmHandle(-1),
m_enemyStartSe(-1),
m_playerDath(-1),
m_player(),	// �N���X������������Ƃ��A()�̒��ɂ̓R���X�g���N�^�̈���������
			// Player�N���X�Ɋւ��Ă̓R���X�g���N�^�Ɉ������Ȃ��̂�()��ok
	m_enemy(),
	m_isGameOver(false),
	m_isSceneEnd(false),
	m_playFrameCount(0),
	m_enemyWaitFrame(0),
	m_enemyCreateNum(0),
	m_fadeAlpha(255)		// �s�����ŏ�����
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_hk = LoadGraph("data/image/HK.jpg");
	ChangeFont("HGS����B");
	SetFontSize(48);

	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);	// �O���t�B�b�N�̃��[�h�Ɏ��s���Ă�����~�߂�
	m_enemyHandle = LoadGraph("data/image/enemy.png");
	assert(m_enemyHandle != -1);	// �O���t�B�b�N�̃��[�h�Ɏ��s���Ă�����~�߂�

	// �T�E���h�̃��[�h
	m_enemyStartSe = LoadSoundMem("data/sound/EnemyFall.mp3");
	m_bgmHandle = LoadSoundMem("data/sound/bgmMain.wav");
	m_playerDath = LoadSoundMem("data/sound/playerDath.mp3");

	// BGM�̍Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	// �t�F�[�h�C�������邽�߉���0����n�߂�
	ChangeVolumeSoundMem(0, m_bgmHandle);

	// �v���C���[�̏�����
	m_player.Init();
	m_player.SetGraphHandle(m_playerHandle);

	// �G�̏�����
	for (int i = 0; i < kEnemyMax; i++)
	{
		m_enemy[i].Init();
		m_enemy[i].SetGrahpHandle(m_enemyHandle);
		m_enemy[i].SetStartPos();	// �O���t�B�b�N��ݒ肵���㏉����
	}

	// �e��ϐ��̏�����
	m_isGameOver = false;
	m_isSceneEnd = false;
	m_playFrameCount = 0;
	m_enemyCreateNum = 0;
	m_enemyWaitFrame = 0;

	m_fadeAlpha = 255;
}

void SceneMain::Update()
{
	// ��ʂ̃t�F�[�h�l�𗘗p���ăT�E���h�̉��ʂ����肷��
	int volume = 255 - m_fadeAlpha;
	ChangeVolumeSoundMem(volume, m_bgmHandle);

	// �Q�[���I�[�o�[�Ȃ�e�������s�킸�A��Update()���I��������
	if (m_isGameOver)
	{
		StopSoundMem(m_bgmHandle);
		PlaySoundMem(m_playerDath, DX_PLAYTYPE_LOOP);	//���S�����o���������ǁA����


		if (m_isSceneEnd)
		{
			// �t�F�[�h�A�E�g
			m_fadeAlpha += 8;
			if (m_fadeAlpha < 255)
			{
				m_fadeAlpha = 255;
			}

		}
		// 1�{�^��orZ�L�[�������ꂽ��Q�[���I�[�o�[��ʂ�
		int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (pad & PAD_INPUT_1)	  // 1�{�^���������ꂽ or Z�������ꂽ�Ƃ�
		{
			m_isSceneEnd = true;
		}
		return;
	}
	
	// �t�F�[�h�C��
	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	// �����c�莞��(�t���[����)�𑝂₷
	m_playFrameCount++;

	m_player.Update();
	for (int i = 0; i < kEnemyMax; i++)
	{
		m_enemy[i].Update();
		if (IsCollision(m_player, m_enemy[i]))
		{
			m_isGameOver = true;
		}
	}

	// ���Ԋu�œG�𐶐�
	m_enemyWaitFrame++;

	// �G����萔�������邽�тɓG�̐����Ԋu���Z���Ȃ�
	int waitFrame = kEnemyWaitFrameDefault;
	waitFrame -= (m_enemyCreateNum / kEnemyWaitFrameChangeNum) * kEnemyWaitFrameChangeFrame;
	// ��ԒZ�������Ԋu�̃`�F�b�N
	if (waitFrame < kEnemyWaitFrameMin)	waitFrame = kEnemyWaitFrameMin;

	if (m_enemyWaitFrame >= kEnemyWaitFrameDefault)
	{
		// ���ݎg���Ă��Ȃ��G�L�����N�^�[��T����
		// ������Start������
		for (int i = 0; i < kEnemyMax; i++)
		{
			// m_enemy[i].isExist() ��false�̏ꍇ���݂��Ă��Ȃ�
			// �̂ł������g��
			if (!m_enemy[i].isExist())
			{
				m_enemyCreateNum++; 
				m_enemyWaitFrame = 0;
				m_enemy[i].Start();
				
			//	// ���ʉ��炷
			//	PlaySoundFile("data/sound/EnemyFall.mp3", DX_PLAYTYPE_BACK);
				PlaySoundMem(m_enemyStartSe, DX_PLAYTYPE_BACK);
				break;	// ��̐��Y������I��
			}
		}
	}
}

void SceneMain::Draw()
{
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_hk, false);
	m_player.Draw();
	for (int i = 0; i < kEnemyMax; i++)
	{
		m_enemy[i].Draw();
	}
	
	// �������Ԃ�\��
	// ��:�b.�~���b	1:05.0004
//	int sec = m_playerFrameCount / 60;
	int milliSec= m_playFrameCount * 1000 / 60;
	int sec = (milliSec / 1000) % 60;
	int min = (milliSec / 1000) / 60;
	milliSec %= 1000;	// �~���b�̕����̂ݎc��
	
	// ������̉����擾
	int strWidth = GetDrawFormatStringWidth("%d:%d.%d", min, sec, milliSec);
	
	DrawFormatString(Game::kScreenWidth / 2 - strWidth / 2,	// X���W 
		Game::kScreenHeight - 48,							// Y���W
		GetColor(255, 255, 255),
		"%3d:%02d.%03d", min, sec, milliSec);

	if (m_isGameOver)
	{
		// ��ʒ����ɃQ�[���I�[�o�[�\��

		// �\�����镶���̉������擾����
		// GetDrawStringWidth(char* String, int StrLen);
		int len = strlen(kGameOverString);
		int width = GetDrawStringWidth(kGameOverString, len);
		int height = GetFontSize();

		DrawString(Game::kScreenWidth / 2 - width / 2,
			Game::kScreenHeight / 2 - height / 2,
			kGameOverString, GetColor(255, 32, 32));
	}

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void SceneMain::End()
{
	// BGM�̒�~
	StopSoundMem(m_playerDath);

	// ����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);

	// ����������T�E���h���폜
	DeleteSoundMem(m_enemyStartSe);
	DeleteSoundMem(m_bgmHandle);
	DeleteSoundMem(m_playerDath);
}

bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

// �v���C���[�ƓG�̓����蔻��
bool SceneMain::IsCollision(const Player& player, const Enemy& enemy)
{
	// ���݂��Ȃ��G�Ƃ͓�����Ȃ�
	if (!enemy.isExist())	return false;

	// �����蔻��
	// �v���C���[�������S�ɍ��ɂ���ꍇ�͓������Ă��Ȃ�
	// �v���C���[���[�������ɓG�̉E�[������ꍇ�͓������Ă��Ȃ�
	if (player.GetLeft() > enemy.GetRight())
	{
		// ���S�ɍ��ɂ���̂œ������Ă��Ȃ����Ɗm��
		return false;	// �m���ɓ������Ă��Ȃ��̂�false��Ԃ�
	}
	// �v���C���[�������S�ɉ��ɂ���ꍇ�͓������Ă��Ȃ�
	// �v���C���[���[�������ɓG�̏�[������ꍇ�͓������Ă��Ȃ�
	if (player.GetBottom() < enemy.GetTop())
	{
		// ���S�ɍ��ɂ���̂œ������Ă��Ȃ����Ɗm��
		return false;	// �m���ɓ������Ă��Ȃ��̂�false��Ԃ�
	}
	// ���l�Ɋ��S�ɉE�ɂ���p�^�[������菜��
	if (player.GetRight() < enemy.GetLeft())
	{
		return false;	// �m���ɓ������Ă��Ȃ��̂�false��Ԃ�

	}
	// ���l�Ɋ��S�ɏ�ɂ���p�^�[������菜��
	if (player.GetTop() > enemy.GetBottom())
	{
		return false;	// �m���ɓ������Ă��Ȃ��̂�false��Ԃ�
	}

	return true;
}

