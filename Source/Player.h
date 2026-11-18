#pragma once

#include"System/modelRenderer.h"
#include"Character.h"
#include"ProjectileManager.h"

//プレイヤー
class Player : public Character
{
public:
	Player();
	~Player() override;

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* renderer);

	/*void DrawDebugGUI();*/

	//ジャンプ処理
	/*void Jump(float speed);*/

	//速力処理更新
	/*void UpdateVelocity(float elapsedTime);*/

	void InputJump();

	//デバッグプリミティブ描画
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)override;

protected:
	//着地したときの呼ばれる
	void OnLanding() override;


private:
	Model* model = nullptr;

	//弾丸入力処理
	void InputProjectile();

	DirectX::XMFLOAT3 GetMoveVec() const;

	/*void Move(float elapsedTime, float vx, float vz, float speed);*/

	void InputMove(float elapsedTime);

	/*void Turn(float elapsedTime, float vx, float vz, float speed);*/

	void CollisionPlayerVsEnemies();

private:

	float moveSpeed = 5.0f;

	float turnSpeed = DirectX::XMConvertToRadians(720);

	float jumpSpeed = 12.0f;

	int jumpCount = 0;

	int jumpLimit = 2;

	/*float gravity = -30.0f;

	DirectX::XMFLOAT3 velocity = { 0,0,0 };*/

	ProjectileManager projectileManager;
};
