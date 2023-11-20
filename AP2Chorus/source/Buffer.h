#pragma once

// Basic-Delay-Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

namespace ap2{

const int sampleRate = 44100;
double delayTimeMs = 50;

int samplesInDuration = (delayTimeMs / 1000.0) * sampleRate;


class RingBuffer {
public:
    RingBuffer(int size, int read, int write) {
        mBuffer = std::vector<double>(size, 0);//stores elements of vector, initialises all elements of vector to 0
        mReadPos = read;//delay position
        mWritePos = write;//current position, also write pos
    }
    double read() {
        int delay = std::min(mReadPos, (int)(mBuffer.size() - 1));//ensure delay not greater than buffer size

        mReadPos = (mReadPos + 1);
        if (mReadPos >= mBuffer.size()) mReadPos = 0;

        return mBuffer[delay];
    }

    void write(double val, int pos) {
        mBuffer[mWritePos] = val;
        mWritePos = (mWritePos + 1) % mBuffer.size();
        if (mWritePos >= mBuffer.size()) mWritePos = 0;

    }

    void clear(int size, int delay, int pos) {
        mBuffer = std::vector<double>(size, 0);
        //mDelayPos = delay;
        mWritePos = pos;

    }
private:
    std::vector<double> mBuffer;
    int mReadPos;
    int mWritePos;
};
}