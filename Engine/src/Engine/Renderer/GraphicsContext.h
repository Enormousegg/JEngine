#pragma once

namespace Engine {

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	};

}