#pragma once

#include <iostream>
#include <cmath>
#include <array>

# define M_PI           3.14159265358979323846  /* pi */

namespace ap2 {

	class SawOsc {
	public:
		SawOsc(double sampleRate,int phase)
		{
			mTs = 1 / sampleRate;
			mPhase = phase;
			
		}

		SawOsc() {
		}

		float process(float rate,float depth) {
			
			double newPhase = (mPhase + rate * 2 * M_PI * mTs);
		
			mPhase = fmod(newPhase, 2 * M_PI);

			double saw = (2.0*(mPhase / (2 * M_PI))) - 1.0;

			return 2.0 * (abs(saw) - 0.5)*depth;

			
		}
	private:
		double mTs;
		double mPhase;
	};

}