#include "Triangle.h"
#include "Novice.h"

void Triangle::Initialize(int windowHeight, int windowWidth)
{
	windowHeight_ = windowHeight;
	windowWidth_ = windowWidth;
	v1_ = { 1.2f, -3.9f, 2.5 };
	v2_ = { 2.8f, 0.4f, -1.3f };
	cameraPosition_ = { 0.0f,0.0f,-15.0f };

	scale_ = { 1.0f,1.0f,1.0f };
	translate_ = { 0.0f,0.5f,0.5f };
	radian_.y = 5.0f / 60.0f;

	kLocalVertices_[left] = { -1.0f,-1.0f,0.0f };
	kLocalVertices_[top] = { 0.0f,1.0f,0.0f };
	kLocalVertices_[right] = { 1.0f,-1.0f,0.0f };
}

void Triangle::Update(char *keys, char *preKeys)
{
	cross_ = operation.Cross(v1_, v2_);
	Scale(keys, preKeys);
	Rotate();
	Translate(keys, preKeys);
	Render();
}

void Triangle::Draw()
{
	Novice::DrawTriangle(
		int(screenVertices_[left].x), int(screenVertices_[left].y), int(screenVertices_[top].x), int(screenVertices_[top].y),
		int(screenVertices_[right].x), int(screenVertices_[right].y), RED, kFillModeSolid
	);

	operation.VectorScreenPrintf(0, 0, cross_, "Cross");
}

void Triangle::Scale(char *keys, char *preKeys)
{
	scale_ = operation.Add(scale_, velocity_);

	if (keys[DIK_W] && preKeys[DIK_W] && scale_.x < 2.0f) {
		velocity_.z = 10.0f / 60.0f;
	}
	else if (keys[DIK_S] && preKeys[DIK_S] && scale_.x > 0.7f) {
		velocity_.z = -10.0f / 60.0f;
	}
	else { velocity_.z = 0.0f; }
}

void Triangle::Rotate()
{
	rotate_ = operation.Add(rotate_, radian_);
}

void Triangle::Translate(char* keys, char* preKeys)
{
	translate_ = operation.Add(translate_, velocity_);
	if (keys[DIK_A] && preKeys[DIK_A]) {
		velocity_.x = -5.0f / 60.0f;
	}
	else if (keys[DIK_D] && preKeys[DIK_D]) {
		velocity_.x = 5.0f / 60.0f;
	}
	else { velocity_.x = 0.0f; }
}

void Triangle::Render()
{
	Matrix4x4 worldMatrix = func.MakeAffineMatrix({ 1.0f, 1.0f,1.0f }, rotate_, translate_);
	Matrix4x4 cameraMatrix = func.MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition_);
	Matrix4x4 viewMatrix = func.Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = func.MakePerspectiveFovMatrix(0.45f, float(windowWidth_) / float(windowHeight_), 0.1f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = func.Multiply(worldMatrix, func.Multiply(viewMatrix, projectionMatrix));
	Matrix4x4 viewportMatrix = func.MakeViewportMatrix(0, 0, float(windowWidth_), float(windowHeight_), 0.0f, 1.0f);
	for (int i = 0; i < 3; ++i) {
		Vector3 ndcVertex = func.Transform(kLocalVertices_[i], worldViewProjectionMatrix);
		screenVertices_[i] = func.Transform(ndcVertex, viewportMatrix);
	}
}
