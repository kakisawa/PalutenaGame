#include "ScenePause.h"
#include "Player.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// ポーズ画面のサイズ
	constexpr int kWidth = 280;
	constexpr int kHeight = 480;

	// ポーズ画面の位置
	constexpr int kPosX = (Game::kScreenWidth - kWidth) / 2;
	constexpr int kPosY = Game::kScreenHeight / 6;

	// 選択中の四角のY座標の初期位置
	constexpr int kInitSelectPosY = 195;
	// 四角の描画の間隔
	constexpr int kSelectPosY = 60;
}

ScenePause::ScenePause(Player* pPlayer):
	m_select(kBuster),
	m_pPlayer(pPlayer),
	m_isExist(false)
{
}

ScenePause::~ScenePause()
{
}

void ScenePause::Init()
{
	m_isExist = false;
	m_select = kBuster;
	m_selectPos.x = 0;
	m_selectPos.y = kInitSelectPosY;
}

void ScenePause::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*Aキーを押したらメニューを表示、非表示*/
	if (Pad::IsTrigger(pad & PAD_INPUT_4))
	{
		if (!m_isExist)
		{
			m_isExist = true; // 表示する
		}
		else
		{
			m_isExist = false;
		}
	}

	// 表示中
	if (m_isExist)
	{
		// ↓キーを押したら選択状態を1つ下げる
		if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
		{
			m_select = (m_select + 1) % kSelectNum;
			m_selectPos.y += kSelectPosY; // 選択中の四角を下に移動

			// 選択中の四角が一番下にだったら四角を一番上に戻す
			if (m_selectPos.y > kInitSelectPosY + kSelectPosY * 4)
			{
				m_selectPos.y = kInitSelectPosY;
			}
		}
		// ↑キーを押したら選択状態を1つ上げる
		if (Pad::IsTrigger(pad & PAD_INPUT_UP))
		{
			m_select = (m_select + (kSelectNum - 1)) % kSelectNum;
			m_selectPos.y -= kSelectPosY;	// 選択中の四角を上に移動

			if (m_selectPos.y < kInitSelectPosY)
			{
				m_selectPos.y = kInitSelectPosY + kSelectPosY * 4;
			}
		}

		// Xキーを押したら現在選択中の武器に変更する
		if (Pad::IsTrigger(pad & PAD_INPUT_2))
		{
			// 選択中の武器を取得
			bool isBuster = false;
			bool isMetal = false;
			bool isFire = false;
			bool isLineMove = false;
			// ポーズ画面を閉じるかどうか	true:閉じる
			bool isClosePause = true; 

			switch (m_select)
			{
			case kBuster:
				// バスターに切り替える
				isBuster = true;
				break;
			case kMetal:
				// メタルに切り替える
				isMetal = true;
				break;
			case kFire:
				// ファイアに切り替える
				isFire = true;
				break;
			case kLine:
				// 2号に切り替える
				isLineMove = true;
				break;
			case kFullRecovery:
				// E缶を1つでも持っていたらHP全回復
				if (m_pPlayer->GetFullHpRecovery() > 0)
				{
					m_pPlayer->HpFullRecovery();
				}
				isClosePause = false; // ポーズ画面を閉じないようにする
				break;
			default:
				break;
			}

			// プレイヤーの武器を変更する
			if (m_select != kFullRecovery)
			{
				m_pPlayer->ChangeShot(isBuster, isMetal, isFire, isLineMove);
			}
			// ポーズ画面を閉じる
			if (isClosePause)
			{
				m_isExist = false;
			}
		}
	}
}

void ScenePause::Draw()
{
	if (m_isExist)
	{
		// ポーズ画面の四角を表示
		SetDrawBlendMode(DX_BLENDMODE_MULA, 200);
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);// 表示モードを元に戻す
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0xffffff, false); // 枠を描画
		DrawString(kPosX ,150, "ポーズ画面", 0xffffff);

		// 選択中の部分を四角で描画
		DrawBox(505, m_selectPos.y, 770, m_selectPos.y + 30, 0x00bfff, false);
	}
}
