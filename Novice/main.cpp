#include <Novice.h>
#include "imgui.h"
#include "Matrix4x4f.h"
#include "Grid.h"
using MyNamespace::Matrix4x4f;

const char kWindowTitle[] = "GC2B_05_コーテスジャレッドアレン";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Grid *grid = new Grid();
	Camera* camera = new Camera();

	Matrix4x4f func{};

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
		
		Matrix4x4 cameraMatrix = func.MakeAffineMatrix({ 1,1,1 }, camera->GetRotate(), camera->GetPosition());
		Matrix4x4 viewMatrix = func.Inverse(cameraMatrix);

		grid->Update();
		Matrix4x4 viewProjectionMatrix = func.MakePerspectiveFovMatrix(0.45f, camera->aspectRatio, 0.1f, 100);

		Matrix4x4 viewWorldProjectionMatrix = func.Multiply(grid->GetWorldMatrix(), func.Multiply(viewMatrix, viewProjectionMatrix));
		Matrix4x4 viewportMatrix = func.MakeViewportMatrix(0, 0, camera->kWindowWidth, camera->kWindowHeight, 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///
		
		///
		/// ↓描画処理ここから
		///

		grid->Draw(viewWorldProjectionMatrix, viewportMatrix);

#ifdef _DEBUG
		ImGui::Begin("Debug Window");
		camera->DebugText();
		ImGui::End();

#endif // DEBUG

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
