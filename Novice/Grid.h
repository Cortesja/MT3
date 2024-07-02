#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include <numbers>

#include "Camera.h"

class Camera;

class Grid:public Camera
{
public:
	Grid(){}
	~Grid() { delete this; }
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
	void Draw(const Matrix4x4& viewWorldProjectionMatrix, const Matrix4x4& viewportMatrix);
	/// <summary>
	/// 
	/// </summary>
	void Render();
	/// <summary>
	/// デバッグウインドウ
	/// </summary>
	void DebugWindow();

	//ゲッター
	Vector3 GetPosition() { return position_; }
	Vector3 GetRotate() { return rotate_; }
	Matrix4x4 GetWorldMatrix() { return worldMatrix_; }
private:
	static inline const uint32_t kElementCount = 11;

	Vector3 localStart_[kElementCount]{};
	Vector3 ndcVertexStart_[kElementCount]{};
	Vector3 screenStart_[kElementCount]{};

	Vector3 localEnd_[kElementCount]{};
	Vector3 ndcVertexEnd_[kElementCount]{};
	Vector3 screenEnd_[kElementCount]{};

	Vector3 position_{};
	Vector3 rotate_{};

	uint32_t color = 0xFFFFFFFF;

	Matrix4x4 worldMatrix_{};

	Camera* camera_;
};

