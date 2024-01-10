#pragma once
#include <memory>

class Map;
class Enemy
{
public:
	Enemy();
	virtual ~Enemy(){}

	// �}�b�v�̃|�C���^��ݒ肷��
	void SetMap(std::shared_ptr<Map> pMap) { m_pMap = pMap; }

	void Update();
	void Draw();

private:
	// Map�Ō��肵���X�N���[���ʂ��擾���邽�߂�Map�N���X�̏�񂪕K�v
	std::shared_ptr<Map>	m_pMap;

	// �v���C���[�̑�����������Ƃ������W
	float m_x;
	float m_y;

};

