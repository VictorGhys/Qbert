#pragma once
namespace dae
{
	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;
		virtual void LoadGame() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
	};
}
