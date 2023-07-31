#pragma once
#include "Framework/Scene.h"

class EnemyBullet : public kiko::Actor
{
public:
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
private:

};