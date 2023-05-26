#include <Novice.h>
#include <Function.h>
#include <Vector3.h>
#include <cstdint>
#include <imgui.h>

const char kWindowTitle[] = "LE2B_26_モギ_ツバサ_MT3_01_02_確認課題";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};



	//Affine
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 translate = { 0.0f,0.0f,0.0f };

	//カメラ
	//Vector3 cameraPosition = { 0.0f,0.0f,-1.0f };
	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };


	//ローカル
	Vector3 LocalVertics[2] = {};
	LocalVertics[0] = {-0.2f,0.0f,0.0f};
	LocalVertics[1] = {0.2f,0.0f,0.0f};
	

	Vector3 localCoodinate = { 0.0f,0.0f,0.0f };



	Sphere sphere = { localCoodinate,1.0f };



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

		

		

		///
		/// ↑更新処理ここまで
		///


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



		//計算
		Matrix4x4 cameraMatrix = MakeAffineMatrix(scale, cameraRotate, cameraTranslate);
		////ビュー(カメラ)
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		
		//射影
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(WINDOW_SIZE_WIDTH) / float(WINDOW_SIZE_HEIGHT), 0.1f, 100.0f);


		//ビューポート
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0,float(WINDOW_SIZE_WIDTH), float(WINDOW_SIZE_HEIGHT), 0.0f, 1.0f);


		///
		/// ↓描画処理ここから
		///
		

		//DrawGrid(const Matrix4x4 & viewProjectionMatrix, const Matrix4x4 & viewportMatrix);
		DrawGrid(viewMatrix,projectionMatrix, viewportMatrix);

		DrawSphre(sphere, viewMatrix, projectionMatrix, viewportMatrix, BLUE);



		////計算
		////ワールドへ
		//Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, localCoodinate);
		//
		//Matrix4x4 cameraMatrix = MakeAffineMatrix(scale, cameraRotate, cameraTranslate);
		//
		////ビュー(カメラ)
		//Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		//
		////射影
		//Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(WINDOW_SIZE_WIDTH) / float(WINDOW_SIZE_HEIGHT), 0.1f, 100.0f);
		//
		////ワールドへ
		//Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		////ビューポート
		//Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0,float(WINDOW_SIZE_WIDTH), float(WINDOW_SIZE_HEIGHT), 0.0f, 1.0f);


		
		//Vector3 screenVertices[3] = {};
		//for (uint32_t i = 0; i < 3; i++) {
		//	Vector3 ndcVertices = Transform(LocalVertics[i], worldViewProjectionMatrix);
		//	screenVertices[i] = Transform(ndcVertices, viewportMatrix);
		//}

		ImGui::Begin("Window");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x,0.01f);
		
		ImGui::End();

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
