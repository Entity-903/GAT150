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
	public:
		//res_t<Model> model;
	};
}