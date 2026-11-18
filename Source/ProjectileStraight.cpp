#include"ProjectileStraight.h"

//コンストラクタ
ProjectileStraight::ProjectileStraight()
{
	model = new Model("Data/Model/SpikeBall/SpikeBall.mdl");

	//表現サイズを調整
	scale.x = scale.y = scale.z = 0.5f;
}

//デストラクタ
ProjectileStraight::~ProjectileStraight()
{
	delete model;
}

//更新処理
void ProjectileStraight::Update(float elapsedTime)
{
	//移動
	float speed = this->speed * elapsedTime;
	position.x += direction.x * speed;
	position.y += direction.y * speed;
	position.z += direction.z * speed;

										
	//オブジェクト行列を更新
	UpdateTransform();

	//モデル行列更新
	model->UpdateTransform();

}

//描画処理
void ProjectileStraight::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}

//発射
void ProjectileStraight::Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
{
	this->direction = direction;
	this->position = position;

}




