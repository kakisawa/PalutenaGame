#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <vector>

class SoundManager;
class Player;
class Shot;
class DeathYourEnemy;

namespace {
    // ���ő�o����
    constexpr int DeathMax = 1;
    // ��ʓ��ɓ����ɏo����e�̐�
    constexpr int kShotMax = 30;
}

class SceneExplanation :
    public SceneBase
{
public:
    SceneExplanation();
    ~SceneExplanation();

    void Init();
    void Update();
    void Draw();
    void End();

    void BackDraw();

    // �V�[�����I������������
    bool IsSceneEnd() const;
    void SetHandle(int handle) { Graph = handle; }

private:
    int BgGraph;
    float m_scrollX;    // �X�N���[���ړ���

    // �O���t�B�b�N�̃n���h��
    int m_gameScreenHandle;
    int m_playerHandle;		// �v���C���[
    int m_enemyHandle;		// �G





    int m_fadeAlpha;    // �t�F�[�h�C���A�A�E�g
    bool m_isSceneEnd;	// �V�[���I���t���O

    struct Size         // �w�i�̃T�C�Y
    {
        int width;
        int height;
    };

    // �v���C���[
    Player* m_pPlayer;
    // �e
    Shot* m_pShot[kShotMax];
    // �G�l�~�[
    std::vector<DeathYourEnemy*> m_pDeathYourEnemy;
    SoundManager* m_pSoundManager;
};

