#pragma once
#include "Matrix4x4f.h"
#include "Vector3f.h"
using MyNamespace::Matrix4x4f;

class Camera
{
public:
	const float kWindowWidth = 1280;
	const float kWindowHeight = 720;

	float aspectRatio = kWindowWidth / kWindowHeight;

	Matrix4x4 GetCameraMatrix() { return cameraMatrix_; }
	Matrix4x4 GetViewMatrix() { return viewMatrix_; }
	Matrix4x4 GetViewProjectionMatrix() { return viewProjectionMatrix_; }
	Matrix4x4 GetViewPortMatrix() { return viewportMatrix_; }
	Matrix4x4 GetViewWorldProjectionMatrix() { return viewWorldProjectionMatrix_; }

	Vector3 GetRotate() { return rotate_; }
	Vector3 GetPosition() { return position_; }

	void SetPositon(Vector3& vector) { position_ = vector; }
	void SetRotate(Vector3& rotateVector) { rotate_ = rotateVector; }
	
	void DebugText();
private:
	//CameraRotate
	Vector3 rotate_{ 1.86f, 0.0f, 3.2f };
	//CameraPosition
	Vector3 position_{ -0.3f,7.84f,-2.67f };
	Matrix4x4 worldMatrix_{};

	Matrix4x4 cameraMatrix_{};
	Matrix4x4 viewMatrix_{};
	Matrix4x4 viewProjectionMatrix_{};
	Matrix4x4 viewportMatrix_{};
	Matrix4x4 viewWorldProjectionMatrix_{};
protected:
	//Matrix4x4を計算するための変数
	Matrix4x4f func{};
	//Vector3を計算するための変数
	Vector3f operation{};
};

