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
		float process(float rate,float depth) {
			double newPhase = (mPhase + rate * 2 * M_PI * mTs) + 28.16;
			mPhase = fmod(newPhase, 2 * M_PI);
			float mAmp = depth;
			return mAmp * cos(mPhase);
		}
	private:
		double mTs;
		double mPhase = 0;
	};

}