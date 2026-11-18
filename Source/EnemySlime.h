#pragma once

#pragma once

#include"System/Model.h"
#include"Enemy.h"

class EnemySlime : public Enemy
{
public:
	EnemySlime();
	~EnemySlime() override;



	void Update(float elapsedTime)override;

	void Render(const RenderContext& rc, ModelRenderer* renderer)override;

private:
	Model* model = nullptr;

};
