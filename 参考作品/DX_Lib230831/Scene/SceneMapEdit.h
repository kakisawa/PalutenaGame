#pragma once
#include "Game.h"
class SceneMapEdit
{
public:
	SceneMapEdit();
	~SceneMapEdit();

	void Init();
	void End();

	void Update();
	void Draw();

private:
	// 定数
	// 
	// マップチップの情報
	static constexpr int kChipWidth = 32;
	static constexpr int kChipHeight = 32;

	// チップを置く数
	static constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	static constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;

private:
	// カーソルの移動
	void CursorUp(bool isLoop);
	void CursorDown(bool isLoop);
	void CursorLeft(bool isLoop);
	void CursorRight(bool isLoop);

	// グラフィックに存在するマップチップの数
	int GetGraphChipNum();

	// テキストファイルとしてマップチップのデータを出力
	void OutputText();
	// テキストファイル読み込みのテスト
	void InputText();

	// バイナリデータとしてマップデータを出力
	void OutputBainary();
	// バイナリデータを読み込んでマップとして使用する
	void InputBainary();

private:
	// グラフィックのハンドル
	int m_bgHandle;
	// グラフィックに含まれるマップチップの数
	int m_graphChipNumX;
	int m_graphChipNumY;

	// マップチップの配置情報
	int m_chipData[kChipNumY][kChipNumX];

	// カーソル位置 二次元配列のインデックスをデータとして持つ
	int m_cursorX;
	int m_cursorY;

	// カーソル移動のリピート処理
	int m_upRepeatFrame;
	int m_downRepeatFrame;
	int m_leftRepeatFrame;
	int m_rightRepeatFrame;
};

