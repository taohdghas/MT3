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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
	Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };
	Quaternion identity = IdentityQuaternion();
	Quaternion conj = Conjugate(q1);
	Quaternion inv = Inverse(q1);
	Quaternion normal = Normalize(q1);
	Quaternion mul1 = Multiply(q1, q2);
	Quaternion mul2 = Multiply(q2, q1);
	float norm = Norm(q1);
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
		QuaternionScreenPrintf(0, kRowHeight * 0, "Identity", identity);
		QuaternionScreenPrintf(0, kRowHeight * 1, "Conjugate",conj);
		QuaternionScreenPrintf(0, kRowHeight * 2, "Inverse",inv);
		QuaternionScreenPrintf(0, kRowHeight * 3, "Normalize", normal);
		QuaternionScreenPrintf(0, kRowHeight * 4, "Multiply(a1,a2)", mul1);
		QuaternionScreenPrintf(0, kRowHeight * 5, "Multiply(a2,a1)", mul2);
		Novice::ScreenPrintf(0, kRowHeight * 6, "%.2f", norm);
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
