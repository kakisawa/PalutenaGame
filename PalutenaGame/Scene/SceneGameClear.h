#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SceneGameClear :
    public SceneBase
{
public:

	SceneGameClear();
	~SceneGameClear();

	void Init();
	void Update();
	void Draw();
    void End();


	// シーンを終了させたいか
	bool IsSceneEnd() const;
	void SetHandle(int handle) { Graph = handle; }

    // 直前に遊んでいたステージを返す
    bool AgainStage1() const { return isStage1; }
    bool AgainStage2() const { return isStage2; }

    // 直前にどのステージを遊んでいたかのフラグを受け取る
    bool JustStage1(int justStage1) { isStage1 = justStage1; }
    bool JustStage2(int justStage2) { isStage2 = justStage2; }

private:
    enum Select
    {
        kScelectRestart,    // もう一度最初から
        kScelectReturnHome, // ホーム画面に戻る
        kScelectEnd,        // ゲームを終わる

        kSclectNum,         // 項目数
    };

    int m_select;    // 選択中のメニュー

    int m_fadeLetter;   // 文字の点滅用カウンタ
    int m_fadeAlpha;    // フェードイン、アウト
    bool m_isSceneEnd;	// シーン終了フラグ


    bool isStage1;  // 直前に遊んでいたステージ1
    bool isStage2;  // 直前に遊んでいたステージ2


    // 選択中メニュー四角表示位置
    Vec2 m_selectPos;
};

