#include "ModelRenderComponent.h"
#include "Framework/Actor.h"

void kiko::ModelRenderComponent::Update(float dt)
{

}

void kiko::ModelRenderComponent::Draw(Renderer& renderer)
{
	m_model->Draw(renderer, m_owner->m_transform);
}
