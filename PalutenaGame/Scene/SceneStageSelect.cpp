#include "SceneStageSelect.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

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

	// Aボタンが押されたらメイン画面へ遷移する
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
		//	// // 効果音鳴らす
		//	// PlaySoundFile("data/sound/TitleDecide.mp3", DX_PLAYTYPE_BACK);
		//	PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK, true);
		//}
		// タイトル画面を終了してSceneMainに移動する処理を書きたい!
	}
}

void SceneStageSelect::Draw()
{
	DrawString(kChirPosX + 25, kChirPosY, "ステージ1", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval, "ステージ2", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval * 2, "タイトルに戻る", 0xffffff);

	// 選択中の部分を四角で描画
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

