#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"


SceneTitle::SceneTitle():
	m_isSceneEnd(false)
{
	// ”wŒi‚Ìƒ[ƒh
	Graph = LoadGraph("data/Map/TitleGraph2.png");
}

SceneTitle::~SceneTitle()
{
	
}

void SceneTitle::Init()
{
	
}

void SceneTitle::Update()
{

}

void SceneTitle::Draw()
{
	DrawGraph(0, 0, Graph, false);
	DrawString(120, 120, "ƒ^ƒCƒgƒ‹‰æ–Ê", GetColor(255, 255, 255));
}

void SceneTitle::End()
{
	// ”wŒi‚ğƒƒ‚ƒŠ‚©‚çíœ
	DeleteGraph(Graph);
}

bool SceneTitle::IsSceneEnd() const
{
	
}
