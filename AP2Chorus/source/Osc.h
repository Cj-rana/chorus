#pragma once

#include <iostream>
#include <cmath>
#include <array>

# define M_PI           3.14159265358979323846  /* pi */

namespace ap2 {
class TriangularOsc {
    public:
        TriangularOsc(double sampleRate)
        {
            mTs = 1 / sampleRate;

        }

        TriangularOsc() {
        }

        float process(float rate, float depth) {
            float mAmp = depth;
            double newPhase = (mPhase + rate * 2 * M_PI * mTs);
            mPhase = fmod(newPhase, 2 * M_PI);

            // Generate a sawtooth waveform
            float sawtooth = static_cast<float>((2.0 / M_PI) * asin(sin(mPhase)));

            // Apply folding to convert the sawtooth to a triangular waveform
            float triangular = 2.0 * (sawtooth - floor(0.5 + sawtooth));

            return mAmp * triangular + 28.16;
        }

    private:
        double mTs;
        double mPhase = 0;
    };

}

	/*/class SineOsc {
	public:
		SineOsc(double sampleRate)
		{
			mTs = 1 / sampleRate;
			
		}

		SineOsc() {
		}

		float process(float rate,float depth) {
			float mAmp = depth;
			//double newPhase = (mPhase + rate * 2 * M_PI * mTs);
			//mPhase = fmod(newPhase, 2 * M_PI);
            double saw = (2.0 * (mPhase/ (2 * M_PI))) - 1.0;
             return 2.0 * (abs(saw) - 0.5);
			//return mAmp * cos(mPhase) + 28.16;
		}
	private:
		double mTs;
		double mPhase = 0;
	};

}/*/
