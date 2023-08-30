#pragma once
#include "Component.h"
#include <vector>

namespace kiko
{
	class TilemapComponent : public Component
	{
	public:
		CLASS_DECLARATION(TilemapComponent)

		bool Initialize() override;
		void Update(float dt) override;

	public:
		int numColumns = 0;
		int numRows = 0;
		vec2 size;

		std::vector<std::string> tileNames;
		std::vector<int> tiles;

	};
}
