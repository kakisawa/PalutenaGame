#pragma once
class FontManager;
class ColorManager;
class Time
{
public:
	Time();
	~Time();

	void Init();
	void Update();
	void Draw();
	
	bool TimeUp() const { return m_isTimeUp; }// �������Ԃ̃t���O��Ԃ�

private:
	float m_second;		// �c��̃Q�[���b��(��������)*60
	float m_count;		// �J�E���g�b��*60

	bool m_isTimeUp;		// �������Ԃ��I��������

	// �t�H���g
	FontManager* m_pFontManager;
	// �F
	ColorManager* m_pColorManager;
};

