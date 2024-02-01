#include "SceneGameOver.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SoundManager.h"
#include "Pad.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// 文字の表示位置
	constexpr int kChirPosX = kScreenWidth * 0.4;
	constexpr int kChirPosY = kScreenHeight * 0.3;

	// 文字の表示幅
	constexpr int kCharInterval = 120;

	// 文字を囲む四角の初期位置
	constexpr int kSelectPosX = kChirPosX - 2;
	constexpr int kSelectPosY = kChirPosY - 2;

	// 文字を囲む四角の移動量
	constexpr int kSelectMoveY = 120;

	// 文字を囲む四角のサイズ
	constexpr int kSelectSizeX = 700;
	constexpr int kSelectSizeY = 75;
}

SceneGameOver::SceneGameOver() :
	m_isSceneEnd(false),
	isStage1(false),
	isStage2(false),
	m_select(kScelectReturnHome),
	m_fadeAlpha(255),
	m_fadeLetter(0),
	m_selectPos(kSelectPosX, kSelectPosY + kSelectMoveY)
{
	// SE/BGMメモリ確保
	m_pSoundManager = new SoundManager;
}

SceneGameOver::~SceneGameOver()
{
	// メモリ解放
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
}

void SceneGameOver::Init()
{
	Graph = LoadGraph("data/Map/GameOverGraph.jpg");
	Cursor = LoadGraph("data/Cursor.png");				// カーソルロゴ読み込み

	m_select= kScelectReturnHome;
	m_isSceneEnd = false;
	isStage1 = false;
	isStage2 = false;
	m_fadeAlpha = 255;
	m_fadeLetter = 0;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY + kSelectMoveY;

	//サウンドマネージャーの初期化
	m_pSoundManager->Init();
}

void SceneGameOver::Update()
{
	// ↓キーを押したら選択状態を一つ下げる
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		m_select = (m_select + 1) % kSclectNum;
		m_selectPos.y += kSelectMoveY;

		// 選択中の四角が一番下にだったら四角を一番上に戻す
		if (m_selectPos.y > kSelectPosY + kSelectMoveY * (kSclectNum - 1))
		{
			m_selectPos.y = kSelectPosY;
		}
	}
	// 上キーを押したら選択状態を一つ上げる
	else if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		m_select = (m_select - 1) % kSclectNum;
		m_selectPos.y -= kSelectMoveY;

		// 選択中の四角が一番下にだったら四角を一番上に戻す
		if (m_selectPos.y < kSelectPosY)
		{
			m_selectPos.y = kSelectPosY + kSelectMoveY * (kSclectNum - 1);
		}
	}

	// エンターキーが押されたらタイトル画面へ遷移する
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
				isStage2 = false;
			}
			//if(m_pSceneTwo->JustFinishStage2())
			//{
			// m_isSceneEnd = true;
			// isStage2=true;
			// isStage1 = false;
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
		default:
			break;
		}
		//if (!m_isSceneEnd)
		//{
		//	// // 効果音鳴らす
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

	// 文字の点滅
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
	DrawString(120, 120, "ゲームオーバー画面", GetColor(255, 255, 255));
	
	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく

	// 選択中の部分を四角で描画
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX,
		m_selectPos.y + kSelectSizeY, 0x00bfff, false);
	DrawExtendGraph(m_selectPos.x - 20, m_selectPos.y - 20,
		m_selectPos.x + kSelectSizeX + 20, m_selectPos.y + kSelectSizeY + 20,
		Cursor, true);

	SetFontSize(64);

	DrawString(kChirPosX, kChirPosY, "もう一度最初から遊ぶ", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval, "タイトル画面に戻る", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval * 2, "ゲームを終わる", 0xffffff);

	// 文字の点滅描画
	if (m_fadeLetter < 60)
	{
		SetFontSize(32);
		DrawString(kChirPosX + 123, kChirPosY + kCharInterval * 3.6, "Aキーで決定", 0xffffff);
	}
}

void SceneGameOver::End()
{
	// 背景をメモリから削除
	DeleteGraph(Graph);

	m_pSoundManager->End();

}

bool SceneGameOver::IsSceneEnd() const
{
	return m_isSceneEnd;
}