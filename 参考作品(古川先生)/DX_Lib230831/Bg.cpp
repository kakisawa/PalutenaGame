#include "Bg.h"
#include "DxLib.h"
#include "Game.h"

// �t�@�C���̏o�͂Ɏg�p����
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>	// �����̏o��
using namespace std;

namespace
{
	// �}�b�v�`�b�v�̏��
	constexpr int kChipWidth = 32;
	constexpr int kChipHeight = 32;

	// �`�b�v��u����
	constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;

	// �}�b�v�`�b�v�̔z�u���
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
}


Bg::Bg():
	m_handle(-1),
	m_graphChipNumX(0),
	m_graphChipNumY(0)
{
	for (int x = 0; x < kChipNumX; x++)
	{
		for (int y = 0; y < kChipNumY; y++)
		{
			m_chipData[y][x] = kChipData[y][x];
		}
	}

	// m_chipData[kChipNumY][kChipNumX]
}

Bg::~Bg()
{
}

void Bg::Init()
{
	// �}�b�v�`�b�v�̐��𐔂���
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_handle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;

	// �f�o�b�O�\��
	//m_graphChipNumX = graphW / kChipWidth;
	//m_graphChipNumY = graphH / kChipHeight;

	// �}�b�v�`�b�v�z�u�f�[�^�̓ǂݍ���
	fstream file;
	file.open("data/map/map.bin", ios::in | ios::binary);
	
	// �t�@�C�����J���̂Ɏ��s�����ꍇ�̏���
	if (!file.is_open())
	{
		// �t�@�C�����J���̂Ɏ��s�����ꍇ�̏���
		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");
	}
	else
	{
		// �t�@�C���̃I�[�v���ɐ�������
		// �t�@�C���̒��g����������ɃR�s�[����
		file.read(reinterpret_cast<char*>(&(m_chipData[0][0])), sizeof(int) * kChipNumX * kChipNumY);
		file.close();
	}
}

void Bg::Update()
{
}

void Bg::Draw()
{
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// �}�b�v��񂩂�u���`�b�v������Ă���
			int chipNo = m_chipData[y][x];

			// �}�b�v�`�b�v�̐؂�o�����W
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumX);

			DrawRectGraph(x * kChipHeight, y * kChipWidth,
				srcX, srcY, kChipWidth, kChipHeight,
				m_handle, true);
		}
	}
}
