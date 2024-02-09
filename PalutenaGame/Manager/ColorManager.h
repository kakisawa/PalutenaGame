#pragma once
class ColorManager
{
public:
	ColorManager();
	~ColorManager(){}

	void Init(){}
	void Update(){}
	void Draw(){}

public:
	int GetColor() { return m_colorHandle; }
	int GetColor2() { return m_colorHandle2; }
	int GetColor3() { return m_colorHandle3; }
	int GetColor4() { return m_colorHandle4; }

private:
	int m_colorHandle;
	int m_colorHandle2;
	int m_colorHandle3;
	int m_colorHandle4;
};