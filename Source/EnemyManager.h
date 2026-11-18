#pragma once

#include<vector>
#include"Enemy.h"

class EnemyManager
{
private:
	EnemyManager(){}
	~EnemyManager(){}

public:
	static EnemyManager& Instance()
	{
		static EnemyManager instance;
		return instance;
	}

	void Update(float elapsedTime);

	void Render(const RenderContext& rc, ModelRenderer* renderer);

	void Register(Enemy* enemy);
	//エネミー全削除
	void Clear();
	//デバッグプリミティブ描画
	void RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer);

	//エネミー数取得
	int GetEnemyCount()const { return static_cast<int>(enemies.size()); }

	//エネミー取得
	Enemy* GetEnemy(int index) { return enemies.at(index); }

private:
	//エネミー同氏の衝突処理
	void CollisionEnemyVsEnemies();

	std::vector<Enemy*>    enemies;

};
