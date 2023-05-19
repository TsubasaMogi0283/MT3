#include <Novice.h>
#include <Function.h>
#include <Vector3.h>
#include <cstdint>


const char kWindowTitle[] = "LE2B_26_モギ_ツバサ_MT3_-_-_確認課題";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};



	Vector3 rotate = { 1.0f,1.0f,1.0f };
	Vector3 translate = { 1.0f,1.0f,1.0f };

	Vector3 cameraPosition = { 1.0f,1.0f,1.0f };

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };

	//時計回りで
	Vector3 kLocalVertics[3] = {};
	kLocalVertics[0] = {15.0f,200.0f,1.0f};
	kLocalVertics[1] = {20.0f,100.0f,1.0f};
	kLocalVertics[2] = {10.0f,100.0f,1.0f};
	
	Vector3 screenVertices[3] = {};

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

		//左
		if (keys[DIK_A] != 0) {
			translate.x -= 1.0f;
		}
		//右
		if (keys[DIK_D] != 0) {
			translate.x += 1.0f;
		}

		//前
		if (keys[DIK_W] != 0) {
			translate.y += 1.0f;
		}
		//後ろ
		if (keys[DIK_S] != 0) {
			translate.y -= 1.0f;
		}

		

		//レンダリングパイプライン(グラフィックスパイプライン)の流れ
		//      
		//ローカル座標系
		//      ↓
		//ワールド座標系
		//      ↓
		//ビュー座標系
		//      ↓
		//正規化デバイス座標系
		//      ↓
		//スクリーン座標系

		Vector3 cross = Cross(v1, v2);


		//計算
		//ワールドへ
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0,1.0f,1.0f }, {0.0f,0.0f,0.0f}, cameraPosition);
		
		//ビュー
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		//
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(WINDOW_SIZE_WIDTH) / float(WINDOW_SIZE_HEIGHT), 0.1f, 100.0f);

		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		//ビューポート
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0,float(WINDOW_SIZE_WIDTH), float(WINDOW_SIZE_HEIGHT), 0.0f, 1.0f);

		
		for (uint32_t i = 0; i < 3; i++) {
			Vector3 ndcVertices = Transform(kLocalVertics[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertices, viewportMatrix);
		}


		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		VectorScreenPrintf(0, 0, cross, "Cross");


		Novice::DrawTriangle(
			int(screenVertices[0].x),
			int(screenVertices[0].y),
			int(screenVertices[1].x),
			int(screenVertices[1].y),
			int(screenVertices[2].x),
			int(screenVertices[2].y), RED, kFillModeSolid);

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
