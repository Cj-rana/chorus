#pragma once

// Basic-Delay-Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>


const int sampleRate = 44100;
double delayTimeMs = 50;

int samplesInDuration = (delayTimeMs / 1000.0) * sampleRate;


class RingBuffer {
public:
    RingBuffer(int size, int delay, int pos) {
        mBuffer = std::vector<double>(size, 0);//stores elements of vector, initialises all elements of vector to 0
        mDelayPos = delay;//delay position
        mPos = pos;//current position, also write pos
    }
    double read() {
        int delay = std::min(mDelayPos, (int)(mBuffer.size() - 1));//ensure delay not greater than buffer size

        mDelayPos = (mDelayPos + 1);
        if (mDelayPos >= mBuffer.size()) mDelayPos = 0;

        return mBuffer[delay];
    }

    void write(double val, int pos) {
        mBuffer[mPos] = val;
        mPos = (mPos + 1) % mBuffer.size();
        if (mPos >= mBuffer.size()) mPos = 0;

    }

    void clear(int size, int delay, int pos) {
        mBuffer = std::vector<double>(size, 0);
        mDelayPos = delay;
        mPos = pos;

    }
private:
    std::vector<double> mBuffer;
    int mDelayPos;
    int mPos;
};
