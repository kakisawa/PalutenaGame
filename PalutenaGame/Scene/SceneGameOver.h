#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SceneGameOver :
    public SceneBase
{
public:
    SceneGameOver();
    ~SceneGameOver();

    void Init();
    void Update();
    void Draw();

    void End();

    // シーンを終了させたいか
    bool IsSceneEnd() const;

    // シーンを最初から
    bool IsSceneRestart() const;

    // 直前にどのステージを遊んでいたかのフラグを受け取る
    void JustStage1(int justStage1) { isStage1 = justStage1; }
    void JustStage2(int justStage2) { isStage2 = justStage2; }

    void SetHandle(int handle) { Graph = handle; }

private:
    enum Select
    {
        kScelectRestart,    // もう一度最初から
        kScelectReturnHome, // ホーム画面に戻る
        kScelectEnd,        // ゲームを終わる

        kSclectNum,         // 項目数
    };

    int m_select;    // 選択中のメニュー

    int m_fadeAlpha;    // フェードイン、アウト
    bool m_isSceneEnd;	// シーン終了フラグ

    bool isStage1;  // 直前に遊んでいたステージ1
    bool isStage2;  // 直前に遊んでいたステージ2


    // 選択中メニュー四角表示位置
    Vec2 m_selectPos;
};