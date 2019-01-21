//
//
#include <vector>
#include <iostream>
#include "dense.h"

using namespace std;


// Constructor
Dense::Dense(int heightIn, int widthIn, vector<float> dataIn){
    width = widthIn;
    height = heightIn;
    // Check size of data 
    if(dataIn.size()!=(widthIn * heightIn)){
        cerr << "Width/Height Mismatch" << endl;
    }else{
        data = dataIn; 
    }
}
void Dense::print(){
    cout << "[";
    for (int i = 0; i < data.size(); i++){
        cout << data[i];
        if ((i+1) % width == 0){
            // End line
            if (i == data.size()-1){
                cout << "]" << endl;
            }else{
                cout << endl << " ";
            }
        }else{
            cout << " , ";
        }
    }
}
Dense Dense::Add(Dense B){
    // Check if opperation can be executed
    if (width==B.width && height==B.height){
        vector<float> newData;
        for(int i = 0; i < data.size(); i++){
            newData.push_back(data[i]+B.data[i]);
        }
        Dense C(height,width,newData);
        return C;
    }else{
        cerr << "Add error: A and B must be dame dimensions" << endl;
        return B;
    }
}

Dense Dense::Mult(Dense B){
    // Check if sizes are compatible
    if (width == B.height){
        vector<float> newData;
        for (int i = 0; i < height; i++){
            int AIdxWidthComponent = i*width;
            for (int j = 0; j < B.width; j++){
                float tmp = 0.0;
                for (int k = 0; k < width; k++){
                    int idxB = k*(B.width) + j;
                    int idxA = AIdxWidthComponent + k;
                    tmp += data.at(idxA) * B.data.at(idxB);
                }
                newData.push_back(tmp);
            }
        }
        Dense MatOutput(height,B.width,newData);
        return MatOutput;
    }else{
        cerr << "Dimensions mismach" << endl;
        return B;
    }
}

Dense Dense::Scale(float B){
    vector<float> newData;
    for (int i = 0; i < data.size(); i++){
        newData.push_back(data.at(i)*B);
    }
    Dense DenseOut(height,width,newData);
    return DenseOut;
}

Dense Dense::Dot(Dense B){
    // Check if opperation can be executed
    if (width==B.width && height==B.height){
        vector<float> newData;
        for(int i = 0; i < data.size(); i++){
            newData.push_back(data[i]*B.data[i]);
        }
        Dense C(height,width,newData);
        return C;
    }else if(B.data.size()==1){
        Dense C = Scale(B.data.at(0));    
        return C;
    }else{
        cerr << "Add error: A and B must be dame dimensions" << endl;
        return B;
    }
}