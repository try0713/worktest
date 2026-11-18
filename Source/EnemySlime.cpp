#include"EnemySlime.h"

EnemySlime::EnemySlime()
{
	model = new Model("data/Model/Slime/Slime.mdl");

	scale.x = scale.y = scale.z = 0.01f;

	//•E‚‚³Ý’è
	radius = 0.5f;
	height = 1.0f;

}

EnemySlime::~EnemySlime()
{
	delete model;
}

void EnemySlime::Update(float elapsedTime)
{
	//‘¬—Íˆ—XV
	UpdateVelocity(elapsedTime);

	UpdataTransform();

	model->UpdateTransform();
}

void EnemySlime::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc,transform,model,ShaderId::Lambert);
}