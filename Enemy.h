#pragma once
class Enemy
{
public: // �����o�֐�

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Enemy();

	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

private: //�����o�ϐ�
	struct Vector2
	{
		float x;
		float y;
	};

	Vector2 pos;
	Vector2 speed;
	int radius;
};

