#include "Player.h"
#include "System/Input.h"
#include"Camera.h"
#include"EnemyManager.h"
#include"Collision.h"
#include"ProjectileStraight.h"

//コンストラクタ
Player::Player()
{
	model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");

	//モデルが大きいのでスケーリング
	scale.x = scale.y = scale.z = 0.01f;
}

//デストラクタ
Player::~Player()
{
	delete model;
}

//更新処理
void Player::Update(float elapsedTime)
{
	



	////入力情報を取得
	//GamePad& gamePad = Input::Instance().GetGamePad();
	//float ax = gamePad.GetAxisLX();
	//float ay = gamePad.GetAxisLY();

	////移動操作
	//float moveSpeed = 5.0f*elapsedTime;
	//{
	//	//左スティックの入力情報をもとにXY平面への移動処理
	//	position.x += ax * moveSpeed;
	//	position.z += ay * moveSpeed;
	//}

	////回転操作
	//float rotateSpeed = DirectX::XMConvertToRadians(360) * elapsedTime;
	//Aボタン
	//if (gamePad.GetButton() & GamePad::BTN_A)
	//{
	//	//X軸回転操作
	//	angle.x += rotateSpeed;
	//}
	//if (gamePad.GetButton() & GamePad::BTN_B)
	//{
	//	//Y軸回転操作
	//	angle.y += rotateSpeed;
	//}
	//if (gamePad.GetButton() & GamePad::BTN_X)
	//{
	//	//Z軸回転操作
	//	angle.z += rotateSpeed;
	//}

	/*DirectX::XMFLOAT3 moveVec = GetMoveVec();

	float moveSpeed = this->moveSpeed * elapsedTime;
	position.x += moveVec.x * moveSpeed;
	position.z += moveVec.z * moveSpeed;*/

	InputMove(elapsedTime);

	//ジャンプ入力処理
	InputJump();

	//弾丸入力処理
	InputProjectile();

	//速行処理更新
	UpdateVelocity(elapsedTime);

	//弾丸更新処理
	projectileManager.Update(elapsedTime);

	//プレイヤーと敵との衝突処理
	CollisionPlayerVsEnemies();

	//オブジェクト行列を更新
	UpdataTransform();

	//モデル行列更新
	model->UpdateTransform();


}

//void Player::Move(float elapsedTime,float vx, float vz, float speed)
//{
//	speed *= elapsedTime;
//	position.x += vx * speed;
//	position.z += vz * speed;
//}

//void Player::Turn(float elapsedTime, float vx, float vz, float speed) {
//	speed *= elapsedTime;
//	//進行ベクトルがゼロベクトルの場合は処理する必要なし
//	float length = sqrtf(vx * vx + vz * vz);
//	if (length<0.001f)return;
//	//進行ベクトルを単位ベクトル化
//	vx /= length;
//	vz /= length;
//	//自身の回転値から前方向を求める
//	float frontX = sinf(angle.y);
//	float frontZ = cosf(angle.y);
//
//	//回転角を求めるため、２つの単位ベクトルの内積を計算する
//	float dot = (frontX * vx) + (frontZ * vz);
//
//	//内積値は-1.0～1.0で表現されており、２つの単位ベクトルの角度が
//	//小さいほど1.0に近づくという性質を利用して角度速度を調整する
//	float rot = 1.0 - dot;
//	if (rot > speed) rot = speed;
//
//	//左右判定を行うために2つの単位ベクトルの外積を計算する
//	float cross = (frontZ * vx) - (frontX * vz);
//
//
//
//	//2Dの外積値が正の場合か負の場合か
//		if (cross < 0.0f)
//		{
//			angle.y -= speed;
//		}
//		else
//		{
//			angle.y += speed;
//		}
//
//
//	
//}


void Player::InputMove(float elapsedTime)
{
	DirectX::XMFLOAT3 moveVec = GetMoveVec();

	Move(elapsedTime, moveVec.x, moveVec.z, moveSpeed);

	Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);
}



//描画処理
void Player::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);

	//弾丸描画処理
	projectileManager.Render(rc, renderer);
}

void Player::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	//基底クラスの関数呼び出し
	Character::RenderDebugPrimitive(rc, renderer);

	//弾丸デバッグプリミティブ描画
	projectileManager.RenderDebugPrimitive(rc, renderer);
}

//void Player::DrawDebugGUI() {
//	ImVec2 pos=ImGui::GetMainViewport()->GetWorkPos();
//}

DirectX::XMFLOAT3 Player::GetMoveVec()const {

	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();

	Camera& camera = Camera::Instance();
	const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
	const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

	float cameraRightX = cameraRight.x;
	float cameraRightZ = cameraRight.z;
	float cameraRightLength = sqrtf(cameraRightX * cameraRightX+ cameraRightZ * cameraRightZ);

	if (cameraRightLength > 0.0f)
	{

		cameraRightX /= cameraRightLength;
		cameraRightZ /= cameraRightLength;

	}

	float cameraFrontX = cameraFront.x;
	float cameraFrontZ = cameraFront.z;
	float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX+ cameraFrontZ * cameraFrontZ);

	if (cameraFrontLength > 0.0f)
	{
		cameraFrontX /= cameraFrontLength;
		cameraFrontZ /= cameraFrontLength;
	}

		DirectX::XMFLOAT3 vec;
		vec.x = (cameraRightX * ax) + (cameraFrontX * ay);
		vec.z = (cameraRightZ * ax) + (cameraFrontZ * ay);

		vec.y = 0.0f;

	return vec;


}

void Player::CollisionPlayerVsEnemies()
{
	EnemyManager& enemyManager = EnemyManager::Instance();

	//全ての敵と総当たりで衝突処理
	int enemyCount = enemyManager.GetEnemyCount();

	for (int i = 0; i < enemyCount; ++i)
	{
		Enemy* enemy = enemyManager.GetEnemy(i);

		//衝突処理
		DirectX::XMFLOAT3 outPosition;
		//if (Collision::IntersectSphereVsSphere(
		//	position,radius,         //A(プレイヤー)
		//	enemy->GetPosition(),    //B(敵)
		//	enemy->GetRadius(),
		//	outPosition
		//)) 
		//{
		//	//押し出し後の位置設定
		//	//B(敵)を押し出す
		//	enemy->SetPosition(outPosition);

		//}
		if (Collision::IntersectCylinderVsCylinder(
			position,radius,height,         //A(プレイヤー)
			enemy->GetPosition(),    //B(敵)
			enemy->GetRadius(),
			enemy->GetHeight(),
			outPosition
		))
		{
			////押し出し後の位置設定
			//enemy->SetPosition(outPosition);

			DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&position);
			DirectX::XMVECTOR E = DirectX::XMLoadFloat3(&enemy->GetPosition());
			DirectX::XMVECTOR V = DirectX::XMVectorSubtract(P, E);
			DirectX::XMVECTOR N = DirectX::XMVector3Normalize(V);
			DirectX::XMFLOAT3 normal;
			DirectX::XMStoreFloat3(&normal, N);
			
			if(normal.y>0.8f)
			{
				//プレイヤーが敵の下にいる場合は、プレイヤーを押し出す

				
				Jump(jumpSpeed*0.5f);

			}
			else
			{

				enemy->SetPosition(outPosition);

			}
			
				
			

		}
	}
}

//void Player::Jump(float speed) 
//{
//	//上方向への力の設定
//	velocity.y = speed;
//}

//void Player::UpdateVelocity(float elapsedTime) 
//{
//	//重力処理
//	velocity.y += gravity * elapsedTime;
//	//移動処理
//	position.y += velocity.y * elapsedTime;
//	position.x += velocity.x * elapsedTime;
//	position.z += velocity.z * elapsedTime;
//
//	//地面判定
//	if (position.y < 0.0f)
//	{
//		position.y = 0.0f;
//		velocity.y = 0.0f;
//	}
//
//}



//着地したときに呼ばれる
void Player::OnLanding()
{
	jumpCount = 0;
}


//ジャンプ入力処理
void Player::InputJump()
{
	//ボタン入力でジャンプ(ジャンプ回数制限付き)
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButtonDown() & GamePad::BTN_A)
	{
		if (jumpCount < jumpLimit)
		{
			jumpCount++;
			Jump(jumpSpeed);
		}
	}

}

void Player::InputProjectile()
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	//直進弾丸発射
	if (gamePad.GetButtonDown() & GamePad::BTN_X)
	{
		//直進弾丸発射[C]
		DirectX::XMFLOAT3 dir;
		dir.x = sinf(angle.y);
		dir.y = 0.0f;
		dir.z = cosf(angle.y);
		//発射位置(プレイヤーの腰あたり)
		DirectX::XMFLOAT3 pos;
		pos.x = position.x;
		pos.y = position.y + height * 0.5f;
		pos.z = position.z;
			//発射
		ProjectileStraight* projectile = new ProjectileStraight();
		projectile->Launch(dir, pos);
		projectileManager.Register(projectile);

	}

}
