#pragma once

namespace kiko
{
	template <typename T>
	class Singleton
	{
	public:
		Singleton(const Singleton& other) = delete;
		Singleton& operator = (const Singleton& other) = delete;
		static T& Instance()
		{
			static T instance;
			return instance;
		}

	protected:
		Singleton() = default;
	};
}