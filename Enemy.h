#pragma once
class Enemy
{
public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private: //メンバ変数
	struct Vector2
	{
		float x;
		float y;
	};

	Vector2 pos;
	Vector2 speed;
	int radius;
};

