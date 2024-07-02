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

	Vector3 rotate{ 0.4f, 1.43f, -0.8f };
	Matrix4x4f temp = {};

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

		Matrix4x4 rotateXMatrix = temp.RotateX(rotate.x);
		Matrix4x4 rotateYMatrix = temp.RotateY(rotate.y);
		Matrix4x4 rotateZMatrix = temp.RotateZ(rotate.z);

		Matrix4x4 rotateXYZMatrix = temp.MakeRotateXYZ(rotate);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		temp.MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		temp.MatrixScreenPrintf(0, kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		temp.MatrixScreenPrintf(0, kRowHeight * 5 * 2, rotateZMatrix, "rotateZMatrix");
		temp.MatrixScreenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");


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