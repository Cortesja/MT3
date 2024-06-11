#pragma once
#include "Vector3f.h"
#include "Matrix4x4f.h"
using MyNamespace::Matrix4x4f;

class Triangle
{
public:
	Triangle() {}
	~Triangle() {}
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(int windowHeight, int windowWidth);
	/// <summary>
	/// 更新
	/// </summary>
	void Update(char *keys, char *preKeys);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 
	/// </summary>
	void Scale(char* keys, char* preKeys);
	/// <summary>
	/// 
	/// </summary>
	void Rotate();
	/// <summary>
	/// 
	/// </summary>
	void Translate(char* keys, char* preKeys);

	void Render();
private:
	enum Verticies {
		left,
		top,
		right
	};

	Vector3f operation{};
	Matrix4x4f func{};

	Vector3 radian_{};
	Vector3 velocity_{};

	Vector3 scale_{};
	Vector3 rotate_{};
	Vector3 translate_{};
	Vector3 cameraPosition_ = { 1.0f,1.0f,1.0f };

	Vector3 v1_{};
	Vector3 v2_{};
	Vector3 cross_{};

	Vector3 kLocalVertices_[3]{};
	Vector3 screenVertices_[3]{};

	Matrix4x4 worldMatrix_{};
	Matrix4x4 worldViewProjectionMatrix_{};

	int windowHeight_;
	int windowWidth_;
};

