#pragma once

class FontManager;

class Time
{
public:
	Time();
	~Time();

	void Init();
	void Update();
	void Draw();

	// �������Ԃ̃t���O��Ԃ�
	bool TimeUp() const { return isTimeUp; }

private:
	float Second;		// �c��̃Q�[���b��(��������)*60
	float Count;		// �J�E���g�b��*60

	bool isTimeUp;		// �������Ԃ��I��������

	FontManager* m_pFontManager;
};

