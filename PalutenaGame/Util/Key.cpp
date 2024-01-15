#include "Key.h"
#include"DxLib.h"

namespace
{
	// 前のフレームのキーボード押し下げ状態
	int lastKey = 0;
	// このフレームのキーボード押し下げ状態
	int nowKey = 0;
}

namespace Key
{
	int keyState[256];

	void Update()
	{
		// 前のフレームに取得したキーボード情報を一つ古い情報にする
		lastKey = nowKey;
		// 現在のキーボードキーボードの情報を取得する
		nowKey = GetHitKeyStateAllEx(keyState);

		// キーボードの押下状態を取得する
		// CheckHitKeyAll で調べる入力タイプ	// キー入力を調べる
	}

	bool IsPress(int key)
	{
		return (nowKey & key);
	}
	bool IsTrigger(int key)
	{
		bool isNow = (nowKey & key);	// このフレーム
		bool isLast = (lastKey & key);	// 前のフレーム
		// return !isLast && isNow;	// これでいいけど理解しにくいので↓に分かりやすく

		if (isNow &&	// このフレームに押されていて
			!isLast)	// 前回のフレームに押されていない
		{
			return true;
		}
		return false;
	}
	bool IsRelase(int key)
	{
		bool isNow = (nowKey & key);	// このフレーム
		bool isLast = (lastKey & key);	// 前のフレーム
		// return !isLast && isNow;	// これでいいけど理解しにくいので↓に分かりやすく

		if (!isNow &&	// このフレームは押されていなくて
			isLast)		// 前回のフレームは押されていた
		{
			return true;
		}
		return false;
	}
}