#pragma once

// Basic-Delay-Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

namespace ap2{

class RingBuffer {
public:
    RingBuffer(double size, double read, double write) {
        mBuffer = std::vector<double>(size, 0);//stores elements of vector, initialises all elements of vector to 0
        mReadPos = read;//delay position
        mWritePos = write;//current position, also write pos
    }
    double read(double read) {
        double delay = std::min(mReadPos, (double)(mBuffer.size() - 1));//ensure delay not greater than buffer size
        mReadPos = (mReadPos + 1);
        if (mReadPos >= mBuffer.size()) mReadPos = 0;
        return mBuffer[delay];
    }

    void write(double write) {
        mBuffer[mWritePos] = write;
        mWritePos = mWritePos + 1;
        if (mWritePos >= mBuffer.size()) mWritePos = 0;

    }

    void clear(double size, double read, double write) {
        mBuffer = std::vector<double>(size, 0);
        mReadPos = read;
        mWritePos = write;

    }
private:
    std::vector<double> mBuffer;
    double mReadPos;
    double mWritePos;
};
}