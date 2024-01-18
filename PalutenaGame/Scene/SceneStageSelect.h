#include "SceneBase.h"
#include "Vec2.h"

class SceneStageSelect :
    public SceneBase
{
public:
    SceneStageSelect();
    ~SceneStageSelect() {}

    void Init();
    void Update();
    void Draw();
    void End();

    // シーンを終了させたいか
    bool IsSceneEnd() const;
    bool IsSceneEnd2() const;
    bool IsSceneEnd3() const;

    void SetHandle(int handle) { Graph = handle; }
private:
    enum Select
    {
        kStage1,        // ステージ1
        kStage2,        // ステージ2
        kSclectBack,    // 戻る

        kSclectNum,         // 項目数
    };

    int m_select;    // 選択中のメニュー

private:
    bool m_isSceneEnd;	// シーン終了フラグ
    bool m_isSceneEnd2; // シーン終了フラグ2
    bool m_isSceneEnd3; // シーン終了フラグ3

    // 選択中メニュー四角表示位置
    Vec2 m_selectPos;
};

