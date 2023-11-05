// Basic-Delay-Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>


class RingBuffer {
public:
    RingBuffer(int size, int delay, int pos) {
        mBuffer = std::vector<double>(size, 0);//stores elements of vector, initialises all elements of vector to 0
        mDelayPos = delay;//delay position
        mPos = pos;//current position, also write pos
    }
    double read() {
       int delay = std::min(mDelayPos, (int)(mBuffer.size() - 1));//ensure delay not greater than buffer size
        int index = mPos - delay;//calculates index based off current -delay
        if (index < 0)index += mBuffer.size();//if less than zero ensures it wraps correctly
       
        return mBuffer[index];

    }

    void write(double val,int pos) {
        mBuffer[mPos]=val;
        mPos = (mPos + 1)% mBuffer.size();
        if (mPos > mBuffer.size()) mPos = pos;
     
    }

    void reset(int delay, int pos) {
        mDelayPos = delay;
        mPos = pos;
       
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


int main()
{
    RingBuffer buffer(10, 5, 0);

    for(int i=0;i<=10;i++){


        buffer.write(i,0);
        std::cout << i << " My position" << buffer.read() << std::endl;


    }

    buffer.reset(5,0);


   
}



