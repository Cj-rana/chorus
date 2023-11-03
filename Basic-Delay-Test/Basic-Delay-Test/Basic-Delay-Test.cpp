// Basic-Delay-Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>


class RingBuffer {
public:
    RingBuffer(int size, int read, int write) {
        mBuffer = std::vector<double>(size, 0);
        mReadPos = read;
        mWritePos = write;
    }
    double read() {
        double val = mBuffer[mReadPos];
        mReadPos = (mReadPos + 1) % mBuffer.size();
        return val;
    }
    void write(double val) {
        mBuffer[mWritePos] = val;
        mWritePos = (mWritePos + 1) % mBuffer.size();
    }
    void reset(int read, int write) {
        std::fill(mBuffer.begin(), mBuffer.end(), 0);
        mReadPos = read;
        mWritePos = write;
    }
private:
    std::vector<double> mBuffer;
    int mReadPos;
    int mWritePos;
};

int main()
{
    RingBuffer buffer(10, 0, 5);
    //creates an array of 10 spaces, pointer for read at 0, write at 5

    for (int i = 0; i < 8; i++) {
        std::cout << buffer.read() << " ";
        buffer.write((double)i);
    }

    std::cout << std::endl;
    buffer.reset(9, 0);
    // use as "delay"

    for (int i = 0; i < 5; i++) {
        double current = (double)i;
        double out = current + buffer.read();
        buffer.write((double)i); //use i as input
        std::cout << out << " ";
    }
    std::cout << std::endl;

}

