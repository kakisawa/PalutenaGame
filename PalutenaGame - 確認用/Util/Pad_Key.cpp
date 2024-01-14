#include "Pad_Key.h"
#include "Dxlib.h"

namespace
{
	// 前のフレームのパッド押し下げ状態
	int lastPad = 0;
	// このフレームのパッド押し下げ状態
	int nowPad = 0;

	// 前のフレームのキーボード押し下げ状態
	int lastKey = 0;
	// このフレームのキーボード押し下げ状態
	int nowKey = 0;
}

namespace Pad
{
	void Update()
	{
		// 前のフレームに取得したパッド情報を一つ古い情報にする
		lastPad = nowPad;
		// 現在のパッドの情報を取得する
		nowPad = GetJoypadInputState(DX_CHECKINPUT_PAD);

		// ジョイパッドの入力状態を取得する
		// CheckHitKeyAllで調べる入力タイプ// パッド入力を調べる
	}

	bool IsPress(int pad)
	{
		return (nowPad & pad);
	}
	bool IsTrigger(int pad)
	{
		bool isNow = (nowPad & pad);	// このフレーム
		bool isLast = (lastPad & pad);	// 前のフレーム
		// return !isLast && isNow;	// これでいいけど理解しにくいので↓に分かりやすく

		if (isNow &&	// このフレームに押されていて
			!isLast)	// 前回のフレームに押されていない
		{
			return true;
		}
		return false;
	}
	bool IsRelase(int pad)
	{
		bool isNow = (nowPad & pad);	// このフレーム
		bool isLast = (lastPad & pad);	// 前のフレーム
		// return !isLast && isNow;	// これでいいけど理解しにくいので↓に分かりやすく

		if (!isNow &&	// このフレームは押されていなくて
			isLast)		// 前回のフレームは押されていた
		{
			return true;
		}
		return false;
	}

	namespace Key
	{
		void Update()
		{
			// 前のフレームに取得したキーボード情報を一つ古い情報にする
			lastKey = nowKey;
			// 現在のキーボードキーボードの情報を取得する
			nowKey = CheckHitKey(DX_CHECKINPUT_KEY);

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
}