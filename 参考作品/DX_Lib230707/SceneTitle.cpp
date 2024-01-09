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
	// BGMの読み込み
	m_bgmHandle = LoadSoundMem("data/sound/BgmResult.wav");
	// 効果音の読み込み
	m_decideSe = LoadSoundMem("data/sound/TitleDecide.mp3");

	// BGMの再生
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	// フェードインさせるため音量0から始める
	ChangeVolumeSoundMem(0, m_bgmHandle);

	m_isSceneEnd = false;
}

void SceneTitle::Update()
{
	// 画面のフェード値を利用してサウンドの音量を決定する
	int volume = 255 - m_fadeAlpha;
	ChangeVolumeSoundMem(volume, m_bgmHandle);

	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_1)	// パッドの1ボタン or キーボードのZキー
	{
		if (!m_isSceneEnd)
		{
			// // 効果音鳴らす
			// PlaySoundFile("data/sound/TitleDecide.mp3", DX_PLAYTYPE_BACK);
			PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK, true);
		}

		// タイトル画面を終了してSceneMainに移動する処理を書きたい!
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
	DrawString(120, 120, "タイトル画面", GetColor(255, 255, 255));
	DrawString(120, 120 + 16, "1ボタンを押してください", GetColor(255, 255, 255));

	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneTitle::End()
{
	// BGMを止める
	StopSoundMem(m_bgmHandle);

	// BGMをメモリから削除
	DeleteSoundMem(m_bgmHandle);

	// 効果音をメモリから削除
	DeleteSoundMem(m_decideSe);
}

bool SceneTitle::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
