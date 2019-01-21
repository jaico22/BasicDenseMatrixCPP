#ifndef DENSE_H
#define DENSE_H

#include <vector>

class Dense
{
    public:
        int width;
        int height;
        std::vector<float> data;

        // Member Functions
        Dense(int widthIn, int heightIn, std::vector<float> dataIn);
        Dense Add(Dense B);
        Dense Mult(Dense B);
        Dense Dot(Dense B);
        Dense Scale(float B);
        void print();
};

#endif