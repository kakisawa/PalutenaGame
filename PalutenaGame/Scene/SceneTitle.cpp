#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"


SceneTitle::SceneTitle():
	m_isSceneEnd(false)
{
	// �w�i�̃��[�h
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
	DrawString(120, 120, "�^�C�g�����", GetColor(255, 255, 255));
}

void SceneTitle::End()
{
	// �w�i������������폜
	DeleteGraph(Graph);
}

bool SceneTitle::IsSceneEnd() const
{
	
}
