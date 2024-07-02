#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include <numbers>
#include "Matrix4x4f.h"
using MyNamespace::Matrix4x4f;

class Sphere
{
public:
	Sphere(){}
	~Sphere() { delete this; }
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
private:
	Vector3 center;
	float radius;
};

