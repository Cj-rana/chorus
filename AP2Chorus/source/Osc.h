#pragma once

#include <iostream>
#include <cmath>
#include <array>

# define M_PI           3.14159265358979323846  /* pi */

namespace ap2 {

	class SineOsc {
	public:
		SineOsc(double sampleRate)
		{
			mTs = 1 / sampleRate;
			
		}
		double process(float rate,float depth) {
			double newPhase = mPhase + rate * 2 * M_PI * mTs;
			mPhase = fmod(newPhase, 2 * M_PI);
			mAmp = depth;
			return mAmp * cos(mPhase);
		}
	private:
		double mTs;
		double mAmp=0;
		double mPhase = 0;
	};

}