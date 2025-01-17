#include <Novice.h>
#include "Mymath.h"
#include "Vector3.h"
#include "imgui.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
const char kWindowTitle[] = "LE2C_13_サノ_ハヤテ_タイトル";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void QuaternionScreenPrintf(int x, int y, const char* Name, const Quaternion&quaternion) {

	Novice::ScreenPrintf(x, y, "%.2f", quaternion.x);
	Novice::ScreenPrintf(x + kColumnWidth * 1, y, "%.2f", quaternion.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.2f", quaternion.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%.2f", quaternion.w);
	Novice::ScreenPrintf(x + kColumnWidth * 5 - kRowHeight, y, "%s", ":");
	Novice::ScreenPrintf(x + kColumnWidth * 5, y, "%s",Name);
}

void Vector3ScreenPrintf(int x, int y, const char* Name, const Vector3& vector) {
	Novice::ScreenPrintf(x, y, "%.2f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth * 1, y, "%.2f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.2f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 4 - kRowHeight, y, "%s", ":");
	Novice::ScreenPrintf(x + kColumnWidth * 4, y, "%s", Name);
}


void MatrixScreenPrintf(int x, int y, const char* Name, const Matrix4x4& matrix) {
	Novice::ScreenPrintf(x, y, "%s\n", Name);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%.3f", matrix.m[row][column]
			);
		}
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Quaternion rotation = MakeRotateAxisAngleQuaternion(
		Normalize(Vector3{ 1.0f,0.4f,-0.2f }), 0.45f);
	Vector3 pointY = { 2.1f,-0.9f,1.3f };
	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotation);
	Vector3 rotateByQuaternion = RotateVector(pointY, rotation);
	Vector3 rotateByMatrix = Transform(pointY, rotateMatrix);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();
		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		/// ↓更新処理ここから
	
		/// ↑更新処理ここまで
		/// ↓描画処理ここから
		QuaternionScreenPrintf(0, kRowHeight * 0, " rotation", rotation);
		MatrixScreenPrintf(0, kRowHeight * 1, "rotateMatrix", rotateMatrix);
		Vector3ScreenPrintf(0, kRowHeight * 6, " rotateByQuaternion", rotateByQuaternion);
		Vector3ScreenPrintf(0, kRowHeight * 7, " rotateByMatrix", rotateByMatrix);
		/// ↑描画処理ここまで
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
