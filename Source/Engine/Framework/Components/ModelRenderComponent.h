#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace kiko
{

	class ModelRenderComponent : public RenderComponent
	{
	public:
		void Update(float dt);
		void Draw(Renderer& renderer);

		virtual float GetRadius() { return m_model->GetRadius(); }
	public:
		res_t<Model> m_model;

		CLASS_DECLARATION(ModelRenderComponent)
	};
}