#pragma once
namespace
{
	// 画面幅(横)
	constexpr int kScreenWidth = 1920;	// 1280	// 1920
	// 画面幅(縦)
	constexpr int kScreenHeight = 1080;	//  720	// 1080
	// カラービット数
	constexpr int kColorDepth = 32;

	// 地面の高さ
	constexpr float Ground = kScreenHeight * 0.815f - 72;	// 地面とプレイヤーのサイズを
														// 引いた結果が地面の高さ
}