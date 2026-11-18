#include"Character.h"

//行列更新処理
void Character::UpdataTransform()
{
	//スケール行列を作成
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x,scale.y,scale.z);
	//回転行列を作成
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x,angle.y,angle.z);
	//位置行列を作成
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x,position.y,position.z);
	//３つの行列を組み合わせ、ワールド行列を作成
	DirectX::XMMATRIX W = S * R * T;
	//計算したワールド行列を取り出す
	DirectX::XMStoreFloat4x4(&transform, W);
	

}
//デバッグプリミティブ描画
void Character::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	/*renderer->RenderSphere(rc, position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));*/
	renderer->RenderCylinder(rc, position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}

void Character::UpdateVelocity(float elapsedTime)
{
	//	//重力処理
	velocity.y += gravity * elapsedTime;
	//	//移動処理
	position.y += velocity.y * elapsedTime;

	//地面判定
	if (position.y < 0.0f)
	{
		position.y = 0.0f;
		velocity.y = 0.0f;

		//着地した
		if (!isGround)
		{
			
			OnLanding();

		}
			
		isGround = true;
	
	}
	else
	{
		isGround = false;
	}

}


void Character::Jump(float speed) 
{
	//上方向への力の設定
	velocity.y = speed;
}


void Character::Move(float elapsedTime,float vx, float vz, float speed)
{
	speed *= elapsedTime;
	position.x += vx * speed;
	position.z += vz * speed;
}

void Character::Turn(float elapsedTime, float vx, float vz, float speed) {
	speed *= elapsedTime;
	//進行ベクトルがゼロベクトルの場合は処理する必要なし
	float length = sqrtf(vx * vx + vz * vz);
	if (length<0.001f)return;
	//進行ベクトルを単位ベクトル化
	vx /= length;
	vz /= length;
	//自身の回転値から前方向を求める
	float frontX = sinf(angle.y);
	float frontZ = cosf(angle.y);

	//回転角を求めるため、２つの単位ベクトルの内積を計算する
	float dot = (frontX * vx) + (frontZ * vz);

	//内積値は-1.0～1.0で表現されており、２つの単位ベクトルの角度が
	//小さいほど1.0に近づくという性質を利用して角度速度を調整する
	float rot = 1.0 - dot;
	if (rot > speed) rot = speed;

	//左右判定を行うために2つの単位ベクトルの外積を計算する
	float cross = (frontZ * vx) - (frontX * vz);



	//2Dの外積値が正の場合か負の場合か
		if (cross < 0.0f)
		{
			angle.y -= speed;
		}
		else
		{
			angle.y += speed;
		}


	
}
