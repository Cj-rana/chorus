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

		SineOsc() {
		}

		float process(float rate,float depth) {
			float mAmp = depth;
			double newPhase = (mPhase + rate * 2 * M_PI * mTs);
			mPhase = fmod(newPhase, 2 * M_PI);
			return mAmp * cos(mPhase) + 28.16;
		}
	private:
		double mTs;
		double mPhase = 0;
	};

}