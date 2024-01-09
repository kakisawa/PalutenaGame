#include "SceneMapEdit.h"
#include "DxLib.h"
#include <cassert>
#include "Pad.h"

// ファイルの出力に使用する
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>	// 文字の出力
using namespace std;

namespace
{
	// カーソル移動リピートフレーム
	constexpr int kCursorRepeatFrame = 5;
}

SceneMapEdit::SceneMapEdit() :
	m_cursorX(0),
	m_cursorY(0),
	m_upRepeatFrame(0),
	m_downRepeatFrame(0),
	m_leftRepeatFrame(0),
	m_rightRepeatFrame(0)
{
	// グラフィックのロード
	m_bgHandle = LoadGraph("data/image/bg.png");
	assert(m_bgHandle != -1);

	// マップチップの数を数える
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_bgHandle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;


	// チップの配置情報の生成
	for (int x = 0; x < kChipNumX; x++)
	{
		for (int y = 0; y < kChipNumY; y++)
		{
			m_chipData[y][x] = 0;
		}
	}
}

SceneMapEdit::~SceneMapEdit()
{
	// グラフィックの解放
	DeleteGraph(m_bgHandle);
}

void SceneMapEdit::Init()
{
}

void SceneMapEdit::End()
{
}

void SceneMapEdit::Update()
{
	// カーソルの移動
	if (Pad::IsPress(PAD_INPUT_UP))
	{
		m_upRepeatFrame++;
		if ((m_upRepeatFrame >= kCursorRepeatFrame) ||
			Pad::IsTrigger(PAD_INPUT_UP))
		{
			m_upRepeatFrame = 0;
			// カーソルの移動処理
			CursorUp(Pad::IsTrigger(PAD_INPUT_UP));
		}
	}
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		m_downRepeatFrame++;
		if ((m_downRepeatFrame >= kCursorRepeatFrame) ||
			Pad::IsTrigger(PAD_INPUT_DOWN))
		{
			m_downRepeatFrame = 0;
			CursorDown(Pad::IsTrigger(PAD_INPUT_DOWN));
		}
	}
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		m_leftRepeatFrame++;
		if ((m_leftRepeatFrame >= kCursorRepeatFrame) ||
			Pad::IsTrigger(PAD_INPUT_LEFT))
		{
			m_leftRepeatFrame = 0;
			CursorLeft(Pad::IsTrigger(PAD_INPUT_LEFT));
		}
	}
	// 右方向へのカーソル移動
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_rightRepeatFrame++;
		if ((m_rightRepeatFrame >= kCursorRepeatFrame) ||
			Pad::IsTrigger(PAD_INPUT_RIGHT))
		{
			m_rightRepeatFrame = 0;
			// カーソルの移動処理
			CursorRight(Pad::IsTrigger(PAD_INPUT_RIGHT));
		}
	}

	if (Pad::IsPress(PAD_INPUT_1))
	{
		// 配列の範囲外アクセスを検知するためのassert
		assert(m_cursorX >= 0 && m_cursorX < kChipNumX);
		assert(m_cursorY >= 0 && m_cursorY < kChipNumY);

		// m_cursorX	←この中にカーソルの座標が入っている

		// 選択しているマップチップの番号を+1
		m_chipData[m_cursorY][m_cursorX]++;

		// グラフィック内に存在するマップチップの数
		int chipNum = GetGraphChipNum();
		
		// chipの番号は0番からの通し番号で管理している
		// chipが10個だと、通し番号は0~9
		// ループ処理
		if (m_chipData[m_cursorY][m_cursorX] > chipNum-1)
		{
			m_chipData[m_cursorY][m_cursorX] = 0;
		}
	}

	if (Pad::IsPress(PAD_INPUT_2))
	{
		// 配列の範囲外アクセスを検知するためのassert
		assert(m_cursorX >= 0 && m_cursorX < kChipNumX);
		assert(m_cursorY >= 0 && m_cursorY < kChipNumY);

		// 選択しているマップチップの番号を+2
		m_chipData[m_cursorY][m_cursorX]--;

		// グラフィック内に存在するマップチップの数
		int chipNum = GetGraphChipNum();

		// ループ処理
		if (m_chipData[m_cursorY][m_cursorX] < 0)
		{
			m_chipData[m_cursorY][m_cursorX] = chipNum - 1;
		}
	}

	// ファイル出力テスト
	if (Pad::IsTrigger(PAD_INPUT_3))	// コントローラーだとX キーボードだと"C"
	{
		OutputBainary();
	}

	// ファイル読み込みテスト
	if (Pad::IsTrigger(PAD_INPUT_4))	// コントローラーだとY キーボードだと"V"
	{
		InputBainary();
	}
#if false
	// test
	if (false)
	{
		fstream file;
		file.open("test.txt", ios::in | ios::out);	// 複数のフラグを同時指定可能
	}
#endif
}

void SceneMapEdit::Draw()
{
	for (int y = 0; y < kChipNumY;y++)
	{
		for(int x=0;x<kChipNumX;x++)
		{
			// マップ情報から置くチップを取ってくる
			int chipNo = m_chipData[y][x];

			// マップチップの切り出し座標
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumX);

			DrawRectGraph(x * kChipHeight, y * kChipWidth,
				srcX, srcY, kChipWidth, kChipHeight,
				m_bgHandle, true);
		}
	}

	// グリッドの表示

	// 縦線
	for (int x = 0; x < kChipNumX; x++) 
	{
		DrawLine(x * kChipWidth, 0, x * kChipWidth, 
			Game::kScreenHeight, GetColor(255, 255, 255));
	}
	// 横線
	for (int y = 0; y < kChipNumY; y++)
	{
		DrawLine(0, y * kChipHeight, Game::kScreenWidth,
			y * kChipHeight, GetColor(255, 255, 255));
	}

	// 現在選択しているチップにカーソルを表示
	int cursorPosX = m_cursorX * kChipWidth;
	int cursorPosY = m_cursorY * kChipHeight;

	DrawBox(cursorPosX, cursorPosY,		// 左上座標
		cursorPosX + kChipWidth, cursorPosY + kChipHeight,	// 右下座標
		GetColor(255, 0, 0), false);
	// 一回り小さい資格を描画して線の太い四角にする
	DrawBox(cursorPosX + 1, cursorPosY + 1,
		cursorPosX + kChipWidth - 1, cursorPosY + kChipHeight - 1,
		GetColor(255, 0, 0), false);	
}

void SceneMapEdit::CursorUp(bool isLoop)
{
	m_cursorY--;
	if (m_cursorY < 0)
	{
		if (isLoop)
		{
			// トリガーの時はカーソルをループする
			m_cursorY = kChipNumY - 1;
		}
		else
		{
			// リピートの場合は端で止まる
			m_cursorY = 0;
		}
	}
}

void SceneMapEdit::CursorDown(bool isLoop)
{
	m_cursorY++;
	if (m_cursorY > kChipNumY - 1)
	{
		if (isLoop)
		{
			m_cursorY = 0;
		}
		else
		{
			m_cursorY = kChipNumY - 1;
		}
	}
}

void SceneMapEdit::CursorLeft(bool isLoop)
{
	m_cursorX--;
	if (m_cursorX < 0)
	{
		if (isLoop) 
		{
			m_cursorX = kChipNumX - 1;
		}
		else
		{
			m_cursorX = 0;
		}
	}
}

void SceneMapEdit::CursorRight(bool isLoop)
{
	m_cursorX++;
	if (m_cursorX > kChipNumX - 1)
	{
		if (isLoop)
		{
			m_cursorX = 0;
		}
		else
		{
			m_cursorX = kChipNumX - 1;
		}
	}
}

int SceneMapEdit::GetGraphChipNum()
{
	return m_graphChipNumX * m_graphChipNumY;
}

void SceneMapEdit::OutputText()
{
	fstream file;
	file.open("test.txt", ios::out);	// ファイルを開く 出力したいのでios::out
	// ファイルの内容を見たい場合はios::inで開く

// ファイルを開くのに失敗した場合の処理
	if (!file.is_open()) {
		// ファイルを開けなかった場合の処理
		// return EXIT_FAILURE;	// 教科書は開けなかったらその時点でプログラム終了
		printfDx("ファイルを開くのに失敗しました\n");	// ファイルは開けなかったと文章を表示する
	}
	else
	{
		//// ファイルが開けた場合の処理
		// 作成したマップのデータをテキストで出力する

		// testでマップの一番上の行のみ出力する
		// m_chipData[kChipNumY][kChipNumX];
		// m_chipData[0][~kChipNumX-1]	// これを出力する
		for (int y = 0; y < kChipNumY; y++)
		{
			file << "{";
			for (int x = 0; x < kChipNumX; x++)
			{
				if (x == kChipNumX - 1)	// 最後のみ","は出力しない
				{
					file << m_chipData[y][x];
				}
				else
				{
					file << m_chipData[y][x] << ",";
				}

			}
			file << "}," << endl;
		}
		file.close();	// 開いたら閉じる 

		printfDx("ファイルに書き込みを行いました\n");
	}
}

void SceneMapEdit::InputText()
{
	fstream file;
	file.open("test.txt", ios::in);	// 読み込むときはios::inで開く

	// ファイルを開くのに失敗した場合の処理
	if (!file.is_open())
	{
		// ファイルを開けなかった場合の処理
		// return EXIT_FAILURE;	// 教科書は開けなかったらその時点でプログラム終了
		printfDx("ファイルを開くのに失敗しました\n");	// ファイルは開けなかったと文章を表示する
	}
	else
	{
		// ファイルのオープンに成功したので読み込みを行う
		string str;			// 内部にcharの配列を持っている(ようなもの)
		getline(file, str);
		file.close();

		printfDx(str.c_str());
	}
}

void SceneMapEdit::OutputBainary()
{
	fstream file;
	// バイナリモードで開く
	// 拡張子は何でもよい バイナリデータを表すbin,データを表すdat等がメジャー
	file.open("map.bin", ios::out|ios::binary);	

	// ファイルを開くのに失敗した場合の処理
	if (!file.is_open())
	{
		// ファイルを開けなかった場合の処理
		// return EXIT_FAILURE;	// 教科書は開けなかったらその時点でプログラム終了
		printfDx("ファイルを開くのに失敗しました\n");	// ファイルは開けなかったと文章を表示する
	}
	else
	{
		// ファイルオープンに成功した
		// マップチップの配置データをバイナリで出力

		// fstreamのwrite関数を使用して出力する
		// メモリ上のどこに置かれているか(アドレス)と
		// そこから何バイト出力するか、を指定する

		file.write((const char*)&(m_chipData[0][0]), sizeof(int) * kChipNumX * kChipNumY);
		file.close();

		printfDx("バイナリデータとしてマップデータを出力しました\n");
	}
}

void SceneMapEdit::InputBainary()
{
	fstream file;
	// バイナリモードで開く
	file.open("map.bin", ios::in | ios::binary);


	// ファイルを開くのに失敗した場合の処理
	if (!file.is_open())
	{
		// ファイルを開けなかった場合の処理
		// return EXIT_FAILURE;	// 教科書は開けなかったらその時点でプログラム終了
		printfDx("ファイルを開くのに失敗しました\n");	// ファイルは開けなかったと文章を表示する
	}
	else
	{
		// ファイルオープンに成功した
		// 読み込んだバイナリの内容をメモリ上のマップチップ情報に上書きする
		file.read((char*)&(m_chipData[0][0]), sizeof(int) * kChipNumX * kChipNumY);
		file.close();

		printfDx("バイナリデータを読み込んでマップデータにしました\n");
	}
}
