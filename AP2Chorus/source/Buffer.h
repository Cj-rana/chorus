#pragma once

// Basic-Delay-Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

namespace ap2 {

    class RingBuffer {
    public:
        RingBuffer(int size, int pos) {
            mBuffer = std::vector<float>(size, 0.0f);//stores elements of vector, initialises all elements of vector to 0
            mPos = pos;//current position, also write pos
        }
        float read(float delay) {
            delay = std::min(delay,(float)(mBuffer.size()-1));//ensure delay not greater than buffer size
            int index = mPos - delay;
            if (index < 0) { index += mBuffer.size();}
            return mBuffer[index];
        }
        void write(float val) {
            mBuffer[mPos] = val;
            mPos = (mPos + 1) % mBuffer.size();
        }

        void clear() {
            std::fill(mBuffer.begin(), mBuffer.end(), 0.0f);
            

        }

        void reset(int size, int pos){
            mBuffer = std::vector<float>(size, 0.0f);
            mPos = pos;
        }
    private:
        std::vector<float> mBuffer;
        int mPos;
    };
}