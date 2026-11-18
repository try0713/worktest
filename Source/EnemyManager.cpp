#include"EnemyManager.h"
#include"Collision.h"

void EnemyManager::Update(float elapsedTime)
{
	for (Enemy* enemy : enemies)
	{
		enemy->Update(elapsedTime);
	}

	//敵同士の衝突処理
	CollisionEnemyVsEnemies();

}

void EnemyManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	for (Enemy* enemy : enemies)
	{
		enemy->Render(rc, renderer);
	}
}

void EnemyManager::Register(Enemy* enemy)
{
	enemies.emplace_back(enemy);
}

void EnemyManager::Clear()
{
	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}

	enemies.clear();
}

//デバッグプリミティブ描画
void EnemyManager::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	//全ての敵にデバッグプリミティブ
	for (Enemy* enemy : enemies)
	{
		enemy->RenderDebugPrimitive(rc, renderer);
	}
}
//エネミー同士の衝突処理
void EnemyManager::CollisionEnemyVsEnemies()
{
	EnemyManager& enemyManager = EnemyManager::Instance();

	//全ての敵と総当たりで衝突処理
	/*int enemyCount = enemyManager.GetEnemyCount();*/

	size_t enemyCount = enemies.size();

	for (int i = 0; i < enemyCount; ++i)
	{
		Enemy* enemyA = enemies.at(i);

		for (int j = i + 1; j < enemyCount; ++j)
		{

			Enemy* enemyB = enemies.at(j);
			//衝突処理
			DirectX::XMFLOAT3 outPosition;
			if (Collision::IntersectCylinderVsCylinder(
				enemyA->GetPosition(), enemyA->GetRadius(),
				enemyA->GetHeight(),
				enemyB->GetPosition(),enemyB->GetRadius(),
				enemyB->GetHeight(),
				outPosition
			))
			{
				//押し出し後の位置設定
				//B(敵)を押し出す
				enemyB->SetPosition(outPosition);

			}

		}

	}
}