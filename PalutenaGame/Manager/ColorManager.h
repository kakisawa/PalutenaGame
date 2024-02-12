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
	int GetColorBlack() { return m_colorHandle; }
	int GetColorWhite() { return m_colorHandle2; }
	int GetColorRed() { return m_colorHandle3; }
	int GetColorYellow() { return m_colorHandle4; }

private:
	int m_colorHandle;
	int m_colorHandle2;
	int m_colorHandle3;
	int m_colorHandle4;
};