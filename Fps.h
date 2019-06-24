#pragma once

#include <SDL.h>

#include "AttrWindow.h"

//The application time based timer
class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    protected:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};

class FpsPrinter {
 public: 
    FpsPrinter();
    void checkpoint( AttrWindow::Window * _window );
 protected:
    int countedFrames_ = 0;
    LTimer fpsTimer_{};
};

class FpsCapper {
 public: 
    FpsCapper( int _fps );
    void checkpoint( AttrWindow::Window * _window );
 protected:
    int fps_;
    int ticksPerFrame_;
    LTimer fpsTimer_{};
};