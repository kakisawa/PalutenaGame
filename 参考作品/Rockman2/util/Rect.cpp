#include "Rect.h"
#include "DxLib.h"
#include <cassert>

Rect::Rect() :
	m_left(0.0f),
	m_top(0.0f),
	m_right(0.0f),
	m_bottom(0.0f)
{
}

Rect::~Rect()
{
}

void Rect::Draw(unsigned int color, bool isFill)
{
	DrawBox(static_cast<int>(m_left), static_cast<int>(m_top), static_cast<int>(m_right), static_cast<int>(m_bottom), color, isFill);
}

void Rect::SetLT(float left, float top, float width, float height)
{
	m_left = left;
	m_top = top;
	m_right = left + width;
	m_bottom = top + height;
}

void Rect::SetCenter(float x, float y, float width, float height)
{
	m_left = x - width / 2;
	m_top = y - height / 2;
	m_right = x + width / 2;
	m_bottom = y + height / 2;
}

float Rect::GetWidth() const
{
	assert(m_right >= m_left);	// ���E�̍��W����ւ��`�F�b�N
	return m_right - m_left;
}

float Rect::GetHeight() const
{
	assert(m_bottom >= m_top);	// �㉺�̍��W����ւ��`�F�b�N
	return m_bottom - m_top;
}

Vec2 Rect::GetCenter() const
{
	// ���S���W
	float x = (m_left + m_right) / 2;
	float y = (m_top + m_bottom) / 2;
	return Vec2{ x,y };
}

bool Rect::IsCollision(const Rect& rect)
{
	// ��΂ɓ�����Ȃ��p�^�[�����͂����Ă���
	if (m_left > rect.m_right) return false;
	if (m_top > rect.m_bottom) return false;
	if (m_right < rect.m_left) return false;
	if (m_bottom < rect.m_top) return false;

	// ������Ȃ��p�^�[���ȊO�͓������Ă���
	return true;
}
