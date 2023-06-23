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



		//計算
		Matrix4x4 cameraMatrix = MakeAffineMatrix(scale, cameraRotate, cameraTranslate);
		////ビュー(カメラ)
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		
		//射影
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(WINDOW_SIZE_WIDTH) / float(WINDOW_SIZE_HEIGHT), 0.1f, 100.0f);


		//ビューポート
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0,float(WINDOW_SIZE_WIDTH), float(WINDOW_SIZE_HEIGHT), 0.0f, 1.0f);

		





		Segment segment = { {-2.0f,-1.0f,0.1f},{3.0f,2.0f,2.0f} };
		Vector3 point = { 0.0f,0.6f,0.6f };



		//正射影ベクトルと最近接点
		Vector3 project = Project(Subtract(point, segment.origin), segment.diff);
		Vector3 closestPoint = ClosestPoint(point, segment);

		

		///
		/// ↑更新処理ここまで
		///


		

		///
		/// ↓描画処理ここから
		///
		

		DrawGrid(viewMatrix,projectionMatrix, viewportMatrix);



		//1cmの球を描画
		Sphere pointSphere{ point,0.01f };
		Sphere closestPointSphere{ closestPoint,0.01f };
		


		//線について


		Matrix4x4 WorldMatrixSegmentOrigin = MakeAffineMatrix({1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, segment.origin);
		Matrix4x4 WorldMatrixSegmentDiff=MakeAffineMatrix({1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, segment.diff);
		Matrix4x4 WorldMatrixPoint=MakeAffineMatrix({1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, point);

		////ワールドへ
		Matrix4x4 worldViewProjectionMatrixSegmentOrigin = Multiply(WorldMatrixSegmentOrigin, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 worldViewProjectionMatrixSegmentDiff = Multiply(WorldMatrixSegmentDiff, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 worldViewProjectionMatrixPoint = Multiply(WorldMatrixPoint, Multiply(viewMatrix, projectionMatrix));

		Vector3 ndcVerticesSegmentOrigin = Transform(segment.origin, worldViewProjectionMatrixSegmentOrigin);
		Vector3 ndcVerticesSegmentDiff = Transform(segment.diff, worldViewProjectionMatrixSegmentDiff);
		Vector3 ndcVerticesPoint = Transform(point, worldViewProjectionMatrixPoint);



		//Vector3 screenVerticesSegmentOrigin = Transform(ndcVerticesSegmentOrigin, viewportMatrix);
		//Vector3 screenVerticesSegmentDiff = Transform(ndcVerticesSegmentDiff, viewportMatrix);
		//Vector3 screenVerticesPoint = Transform(ndcVerticesPoint, viewportMatrix);


		
		Vector3 start = Transform(ndcVerticesSegmentOrigin, viewportMatrix);
		Vector3 end = Transform(Add(ndcVerticesSegmentOrigin,ndcVerticesSegmentDiff ), viewportMatrix);
		
		


		//赤の方が描画できていない・・
		DrawSphere(pointSphere, viewMatrix, projectionMatrix, viewportMatrix, RED);
		//黒い方は座標が少しおかしい
		DrawSphere(closestPointSphere, viewMatrix, projectionMatrix, viewportMatrix, BLACK);




		Novice::DrawLine(
			int(start.x), 
			int(start.y), 
			int(end.x), 
			int(end.y), WHITE);

		
	
		ImGui::Begin("Window");
		ImGui::DragFloat3("point", &point.x,0.01f);
		ImGui::DragFloat3("Segment origin", &segment.origin.x,0.01f);
		ImGui::DragFloat3("Segmen difft", &segment.diff.x,0.01f);

		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		

		ImGui::Begin("Camera");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x,0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x,0.01f);
		
		ImGui::End();



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
