#include "Test.h"
#include "Pad.h"
#include "DxLib.h"

namespace {

	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;

	// 文字の表示位置
	constexpr int kSelectChirPosX = kScreenWidth * 0.08f;
	constexpr int kSelectChirPosY = kScreenHeight * 0.15f;

	constexpr int kSelectBackChirPosX = kScreenWidth * 0.43f;
	constexpr int kSelectBackChirPosY = kScreenHeight * 0.85f;

	// 文字の表示幅
	constexpr int kCharInterval = 180;

	// 文字を囲む四角の初期位置
	constexpr int kSelectPosX = kSelectChirPosX - 2;
	constexpr int kSelectPosY = kSelectChirPosY - 2;

	// 文字を囲む四角の移動量
	constexpr int kSelectMoveY = 180;

	// 文字を囲む四角のサイズ
	constexpr int kSelectSizeX = kScreenWidth * 0.245;
	constexpr int kSelectSizeY = 75;
}

Test::Test():
	m_select(kStage1),
	m_selectPos(kSelectPosX, kSelectPosY)
{
}

Test::~Test()
{
}

void Test::Init()
{
	m_fadeLetter = 0;
	m_select = kStage1;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;
}

void Test::Update()
{
	// ↓キーを押したら選択状態を一つ下げる
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		DrawString(1000, 500, "あいうえお", 0xFFFFFF);

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

	// 文字の点滅
	m_fadeLetter++;
	if (m_fadeLetter == 80)
	{
		m_fadeLetter = 0;
	}
}

void Test::Draw()
{
	// ステージセレクトBox
	for (int i = 0; i < 2; i++)
	{
		DrawBox(m_selectPos.x, kSelectPosY + (kCharInterval * i), m_selectPos.x + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0xF4EADE, true);

		DrawBox(m_selectPos.x, kSelectPosY + (kCharInterval * i), m_selectPos.x + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0x99e6ff, false);
	}
	// タイトルに戻るBox
	DrawBox(kSelectBackChirPosX, kSelectBackChirPosY,
		kSelectBackChirPosX + kSelectSizeX, kSelectBackChirPosY + 75,
		0xF4EADE, true);

	// 選択中の部分を四角で描画
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX,
		m_selectPos.y + kSelectSizeY, 0x00bfff, true);


	DrawString(kSelectChirPosX, kSelectChirPosY,
		"　ステージ1", 0x000000);
	DrawString(kSelectChirPosX, kSelectChirPosY + kCharInterval,
		"　ステージ2", 0x000000);
	DrawString(kSelectBackChirPosX, kSelectBackChirPosY,
		"タイトルに戻る", 0x000000);

	// 文字の点滅描画
	if (m_fadeLetter < 60) {
		DrawString(kSelectChirPosX, kSelectChirPosY + kCharInterval * 2.8f,
			" Aキーで決定",0xFFFFFF);
	}
}
