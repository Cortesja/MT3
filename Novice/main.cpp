#include <Novice.h>
#include "Matrix4x4f.h"
#include "Vector3f.h"
using MyNamespace::Matrix4x4f;

const char kWindowTitle[] = "GC1B_05_コーテスジャレッドアレン";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3f temp = {};
	Matrix4x4f tempMatrix = {};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Vector3 translate{ 4.1f, 2.6f, 0.8f };
		Vector3 scale{ 1.5f, 5.2f, 7.3f };
		Matrix4x4 translateMatrix = tempMatrix.MakeTranslateMatrix(translate);
		Matrix4x4 scaleMatrix = tempMatrix.MakeScaleMatrix(scale);
		Vector3 point{ 2.3f, 3.8f, 1.4f };
		Matrix4x4 transformMatrix = {
			1.0f, 2.0f, 3.0f, 4.0f,
			3.0f, 1.0f, 1.0f, 2.0f,
			1.0f, 4.0f, 2.0f, 3.0f,
			2.0f, 2.0f, 1.0f, 3.0f
		};
		Vector3 transformed = tempMatrix.Transform(point, transformMatrix);

		///
		/// ↑更新処理ここまで
		///

		temp.VectorScreenPrintf(0, 0, transformed, "transformed");
		tempMatrix.MatrixScreenPrintf(0, 0, translateMatrix, "translateMatrix");
		tempMatrix.MatrixScreenPrintf(0, kRowHeight * 5, scaleMatrix, "scaleMatrix");

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}