#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#pragma warning(push)
#pragma warning(disable:26812)
#pragma warning(disable:26819)
#include "SDL.h"
#pragma warning(pop)
#include "Minigin.h"

int main(int, char* []) {
	dae::Minigin engine;
	engine.Run(nullptr);
	return 0;
}