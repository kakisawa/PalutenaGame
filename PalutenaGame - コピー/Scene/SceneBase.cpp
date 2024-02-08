#include "SceneBase.h"

SceneBase::SceneBase() :
    Graph(-1),
    Bgm(-1),
    Se(-1),
    x(-1),
    y(-1)
{
}

bool SceneBase::IsSceneEnd() const
{
    return false;
}
