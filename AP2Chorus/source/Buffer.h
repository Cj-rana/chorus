#pragma once

// Basic-Delay-Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

namespace ap2 {

    class RingBuffer {
    public:
        RingBuffer(int size) {
            mBuffer = std::vector<float>(size, 0.0f);//stores elements of vector, initialises all elements of vector to 0
            mPos = size-1;//current position, also write pos
        }
        RingBuffer() {






        }

        float read(float delay) {
            delay = std::min(delay,(float)(mBuffer.size()-1));//ensure delay not greater than buffer size
            int index = mPos - delay;
            if (index < 0) { index += mBuffer.size();}
            return mBuffer[index];
        }

        float readInterp(float delay) {
            float samples = float(delay);
            float v1 = read(samples);
            float v2 = read(samples + 1);
            float frac = delay - samples;
            return v1 + frac * (v2 - v1);
        }
        void write(float val) {
            mBuffer[mPos] = val;
            mPos = (mPos + 1) % mBuffer.size();
        }

        void clear() {
            std::fill(mBuffer.begin(), mBuffer.end(), 0.0f);
            

        }

        void reset(int size){
            mBuffer = std::vector<float>(size, 0.0f);
            mPos = size-1;
        }
    private:
        std::vector<float> mBuffer;
        int mPos;
    };
}