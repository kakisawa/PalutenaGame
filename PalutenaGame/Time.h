#pragma once

class Time
{
public:
	Time();
	~Time();

	void Init();
	void Update();
	void Draw();

	bool TimeUp() const { return isTimeUp; }

private:
	float Second;		// �c��̃Q�[���b��(��������)*60
	float Count;		// �J�E���g�b��*60

	bool isTimeUp;		// �������Ԃ��I��������
};

