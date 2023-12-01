#pragma once

// パッドの状態を取得する
class KeyProcess
{
public:
	// パッドの更新処理 1フレームに1回行う
	void Update();

	// 押されているかを取得
	static bool IsPress(int key);
	// 押された瞬間を取得
	static bool IsTrigger(int key);
	// 離した瞬間を取得
	bool IsRelase(int key);
};