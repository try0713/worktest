#include"Collision.h"

//球と球の交差判定


bool Collision::IntersectSphereVsSphere(
	const DirectX::XMFLOAT3& positionA,
	float radiusA,
	const DirectX::XMFLOAT3& positionB,
	float radiusB,
	DirectX::XMFLOAT3& outPositionB)
{
	//A->Bの単位ベクトルを算出
	DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat3(&positionA);
	DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat3(&positionB);
	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(PositionB, PositionA);
	DirectX::XMVECTOR LengthSq = DirectX::XMVector3LengthSq(Vec);
	float lengthSq;
	DirectX::XMStoreFloat(&lengthSq, LengthSq);
	//距離判定
	float range = radiusA + radiusB;
		if (lengthSq>range*range)
		{
			return false; //当たっていない
		}
	//AがBを押し出す
	//A->Bの単位ベクトルを算出
		Vec = DirectX::XMVector3Normalize(Vec);
		Vec = DirectX::XMVectorScale(Vec,range);
		PositionB = DirectX::XMVectorAdd(PositionA,Vec);
		DirectX::XMStoreFloat3(&outPositionB, PositionB);

	return true;

}

bool Collision::IntersectCylinderVsCylinder(const DirectX::XMFLOAT3& positionA,
	float radiusA,
	float heightA,
	const DirectX::XMFLOAT3& positionB,
	float radiusB, 
	float heightB, 
	DirectX::XMFLOAT3& outPositionB)
{
	//Aの足元がBの頭より上なら当たっていない
	if (positionA.y>positionB.y+heightB)
	{
		return false;
	}
	//Bの足元がAの頭より上なら当たっていない
	if (positionB.y > positionA.y + heightA)
	{
		return false;
	}
	//XZ平面での範囲チェック
	float vx = positionB.x - positionA.x;
	float vz = positionB.z - positionA.z;
	float range = radiusA + radiusB;
	float distXZ = sqrtf(vx * vx + vz * vz);
	if (distXZ>range)
	{
		return false;
	}
	//単位ベクトル化
		vx /= distXZ;
		vz /= distXZ;
	//AがBを押し出す
	outPositionB.x = positionA.x + (vx * range);
	outPositionB.y = positionB.y;
	outPositionB.z = positionA.z + (vz * range);

	return true;
}


