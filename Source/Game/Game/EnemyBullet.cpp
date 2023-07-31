#include "EnemyBullet.h"
#include "Player.h"
#include "Framework/Scene.h"

void EnemyBullet::Update(float dt)
{
	Actor::Update(dt);
}

void EnemyBullet::OnCollision(Actor* other)
{

	if (other->m_tag == "Player")
	{
		m_destroyed = true;
	}
}