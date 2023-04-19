#pragma once
#include <SDL2/SDL.h>
#include "common/define.h"

namespace el
{
	struct Engine
	{
		void run();

		static uint secondsToFPS(float seconds) {
			return (uint)round(sFPS * seconds);
		}

	protected:
		virtual void start() {};
		virtual void input() {};
		virtual void update();
		virtual void paint();

		virtual void load();
		virtual void loop();
		virtual void render();
		virtual void resize();

		SDL_Window* mWindow;
		SDL_GLContext mContext;
		int mX, mY, mW, mH;
		bool debugging;

		static const uint sFPS;
	};
}