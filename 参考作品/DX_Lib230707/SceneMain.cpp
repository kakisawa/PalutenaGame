#include "SceneMain.h"
#include "DxLib.h"
#include <cassert>
#include "Game.h"

namespace
{
	// ゲームオーバー時に表示する文字列
	const char* const kGameOverString = "ゲイムオーーバーー";	// 文字の定義

	// 敵の初期生成間隔(フレーム数)
	constexpr int kEnemyWaitFrameDefault = 60;
	// 敵の最短生成間隔
	constexpr int kEnemyWaitFrameMin = 3;
	// 敵の生成間隔を敵何体生成するたびに短くするか
	constexpr int kEnemyWaitFrameChangeNum = 5;
	// 一度生成間隔を短くするときに何フレーム短くするか
	constexpr int kEnemyWaitFrameChangeFrame = 2;
}

SceneMain::SceneMain():
m_playerHandle(-1),
m_enemyHandle(-1),
m_bgmHandle(-1),
m_enemyStartSe(-1),
m_playerDath(-1),
m_player(),	// クラスを初期化するとき、()の中にはコンストラクタの引数を入れる
			// Playerクラスに関してはコンストラクタに引数がないので()でok
	m_enemy(),
	m_isGameOver(false),
	m_isSceneEnd(false),
	m_playFrameCount(0),
	m_enemyWaitFrame(0),
	m_enemyCreateNum(0),
	m_fadeAlpha(255)		// 不透明で初期化
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_hk = LoadGraph("data/image/HK.jpg");
	ChangeFont("HGS明朝B");
	SetFontSize(48);

	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);	// グラフィックのロードに失敗していたら止める
	m_enemyHandle = LoadGraph("data/image/enemy.png");
	assert(m_enemyHandle != -1);	// グラフィックのロードに失敗していたら止める

	// サウンドのロード
	m_enemyStartSe = LoadSoundMem("data/sound/EnemyFall.mp3");
	m_bgmHandle = LoadSoundMem("data/sound/bgmMain.wav");
	m_playerDath = LoadSoundMem("data/sound/playerDath.mp3");

	// BGMの再生
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	// フェードインさせるため音量0から始める
	ChangeVolumeSoundMem(0, m_bgmHandle);

	// プレイヤーの初期化
	m_player.Init();
	m_player.SetGraphHandle(m_playerHandle);

	// 敵の初期化
	for (int i = 0; i < kEnemyMax; i++)
	{
		m_enemy[i].Init();
		m_enemy[i].SetGrahpHandle(m_enemyHandle);
		m_enemy[i].SetStartPos();	// グラフィックを設定した後初期化
	}

	// 各種変数の初期化
	m_isGameOver = false;
	m_isSceneEnd = false;
	m_playFrameCount = 0;
	m_enemyCreateNum = 0;
	m_enemyWaitFrame = 0;

	m_fadeAlpha = 255;
}

void SceneMain::Update()
{
	// 画面のフェード値を利用してサウンドの音量を決定する
	int volume = 255 - m_fadeAlpha;
	ChangeVolumeSoundMem(volume, m_bgmHandle);

	// ゲームオーバーなら各処理を行わず、即Update()を終了させる
	if (m_isGameOver)
	{
		StopSoundMem(m_bgmHandle);
		PlaySoundMem(m_playerDath, DX_PLAYTYPE_LOOP);	//死亡音を出したいけど、困難


		if (m_isSceneEnd)
		{
			// フェードアウト
			m_fadeAlpha += 8;
			if (m_fadeAlpha < 255)
			{
				m_fadeAlpha = 255;
			}

		}
		// 1ボタンorZキーが押されたらゲームオーバー画面へ
		int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (pad & PAD_INPUT_1)	  // 1ボタンが押された or Zが押されたとき
		{
			m_isSceneEnd = true;
		}
		return;
	}
	
	// フェードイン
	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	// 生き残り時間(フレーム数)を増やす
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

	// 一定間隔で敵を生成
	m_enemyWaitFrame++;

	// 敵を一定数生成するたびに敵の生成間隔が短くなる
	int waitFrame = kEnemyWaitFrameDefault;
	waitFrame -= (m_enemyCreateNum / kEnemyWaitFrameChangeNum) * kEnemyWaitFrameChangeFrame;
	// 一番短い生成間隔のチェック
	if (waitFrame < kEnemyWaitFrameMin)	waitFrame = kEnemyWaitFrameMin;

	if (m_enemyWaitFrame >= kEnemyWaitFrameDefault)
	{
		// 現在使われていない敵キャラクターを探して
		// そいつをStartさせる
		for (int i = 0; i < kEnemyMax; i++)
		{
			// m_enemy[i].isExist() がfalseの場合存在していない
			// のでそいつを使う
			if (!m_enemy[i].isExist())
			{
				m_enemyCreateNum++; 
				m_enemyWaitFrame = 0;
				m_enemy[i].Start();
				
			//	// 効果音鳴らす
			//	PlaySoundFile("data/sound/EnemyFall.mp3", DX_PLAYTYPE_BACK);
				PlaySoundMem(m_enemyStartSe, DX_PLAYTYPE_BACK);
				break;	// 一体生産したら終了
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
	
	// 生存時間を表示
	// 分:秒.ミリ秒	1:05.0004
//	int sec = m_playerFrameCount / 60;
	int milliSec= m_playFrameCount * 1000 / 60;
	int sec = (milliSec / 1000) % 60;
	int min = (milliSec / 1000) / 60;
	milliSec %= 1000;	// ミリ秒の部分のみ残す
	
	// 文字列の横幅取得
	int strWidth = GetDrawFormatStringWidth("%d:%d.%d", min, sec, milliSec);
	
	DrawFormatString(Game::kScreenWidth / 2 - strWidth / 2,	// X座標 
		Game::kScreenHeight - 48,							// Y座標
		GetColor(255, 255, 255),
		"%3d:%02d.%03d", min, sec, milliSec);

	if (m_isGameOver)
	{
		// 画面中央にゲームオーバー表示

		// 表示する文字の横幅を取得する
		// GetDrawStringWidth(char* String, int StrLen);
		int len = strlen(kGameOverString);
		int width = GetDrawStringWidth(kGameOverString, len);
		int height = GetFontSize();

		DrawString(Game::kScreenWidth / 2 - width / 2,
			Game::kScreenHeight / 2 - height / 2,
			kGameOverString, GetColor(255, 32, 32));
	}

	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneMain::End()
{
	// BGMの停止
	StopSoundMem(m_playerDath);

	// メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);

	// メモリからサウンドを削除
	DeleteSoundMem(m_enemyStartSe);
	DeleteSoundMem(m_bgmHandle);
	DeleteSoundMem(m_playerDath);
}

bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

// プレイヤーと敵の当たり判定
bool SceneMain::IsCollision(const Player& player, const Enemy& enemy)
{
	// 存在しない敵とは当たらない
	if (!enemy.isExist())	return false;

	// 当たり判定
	// プレイヤーよりも完全に左にいる場合は当たっていない
	// プレイヤー左端よりも左に敵の右端がある場合は当たっていない
	if (player.GetLeft() > enemy.GetRight())
	{
		// 完全に左にいるので当たっていないこと確定
		return false;	// 確実に当たっていないのでfalseを返す
	}
	// プレイヤーよりも完全に下にいる場合は当たっていない
	// プレイヤー下端よりも下に敵の上端がある場合は当たっていない
	if (player.GetBottom() < enemy.GetTop())
	{
		// 完全に左にいるので当たっていないこと確定
		return false;	// 確実に当たっていないのでfalseを返す
	}
	// 同様に完全に右にいるパターンを取り除く
	if (player.GetRight() < enemy.GetLeft())
	{
		return false;	// 確実に当たっていないのでfalseを返す

	}
	// 同様に完全に上にいるパターンを取り除く
	if (player.GetTop() > enemy.GetBottom())
	{
		return false;	// 確実に当たっていないのでfalseを返す
	}

	return true;
}

