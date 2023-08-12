#include <Novice.h>
#include <Function.h>
#include <Vector3.h>
#include <cstdint>
#include <imgui.h>
#include <corecrt_math.h>

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
	Vector3 cameraTranslate = { 0.0f,3.0f,-9.50f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };


	//ローカル
	Vector3 LocalVertics[2] = {};
	LocalVertics[0] = {-0.2f,0.0f,0.0f};
	LocalVertics[1] = {0.2f,0.0f,0.0f};
	

	Sphere sphere1LocalCoodinate = { {0.0f,0.0f,0.0f},0.2f };
	
	Plane planeCoodinate = { {0.0f,1.0f,0.1f},1.0f };


	AABB aabb1 = { .min{-0.5f,-0.5f,-0.5f},.max{0.0f,0.0f,0.1f} };
	AABB aabb2 = { .min{-0.2f,-0.2f,-0.2f},.max{1.0f,1.0f,1.0f} };
	unsigned int color = WHITE;

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

		
#pragma region カメラの計算
		//計算
		Matrix4x4 cameraMatrix = MakeAffineMatrix(scale, cameraRotate, cameraTranslate);
		////ビュー(カメラ)
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		//射影
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(WINDOW_SIZE_WIDTH) / float(WINDOW_SIZE_HEIGHT), 0.1f, 100.0f);


		//ビューポート
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(WINDOW_SIZE_WIDTH), float(WINDOW_SIZE_HEIGHT), 0.0f, 1.0f);

#pragma endregion

		if (IsCollisionAABB(aabb1, aabb2) == true) {
			color = RED;
		}
		else {
			color = WHITE;
		}


		///
		/// ↑更新処理ここまで
		///




		///
		/// ↓描画処理ここから
		///


		//Grid
		DrawGrid(viewMatrix, projectionMatrix, viewportMatrix);

		DrawSphere(sphere1LocalCoodinate, viewMatrix, projectionMatrix, viewportMatrix, color);

		//1個目
		DrawAABB(aabb1, viewMatrix,projectionMatrix, viewportMatrix, color);
		//2個目
		DrawAABB(aabb2, viewMatrix,projectionMatrix, viewportMatrix, color);
		

		//Proj
		//Localを入れるよ
		
		ImGui::Begin("AABB");
		ImGui::DragFloat3("aabb1Max", &aabb1.max.x, 0.01f);
		ImGui::DragFloat3("aabb1Min", &aabb1.min.x, 0.01f);

		ImGui::DragFloat3("aabb2Max", &aabb2.max.x, 0.01f);
		ImGui::DragFloat3("aabb2Min", &aabb2.min.x, 0.01f);

		ImGui::End();



		ImGui::Begin("Camera");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x,0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x,0.01f);
		
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
