//
//
#include <vector>
#include <iostream>
#include "dense.h"
#include <random>

using namespace std;


// Constructor
Dense::Dense(int heightIn, int widthIn, vector<float> dataIn = {}){
    width = widthIn;
    height = heightIn;
    // Check size of data 
    if(dataIn.size()!=(widthIn * heightIn)){
        cerr << "Width/Height Mismatch" << endl;
    }else{
        if (dataIn.empty()){
            vector<float> defaultData(heightIn*widthIn);
            data = defaultData; 
        }else{
            data = dataIn; 
        }   
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

Dense Dense::Transpose(){
    vector<float> newData;
    for (int col = 0; col < width; col++){
        for(int row = 0; row < height; row++) {
            int addr = GetAddress(row,col);
            newData.push_back(data.at(addr));
        }
    }
    Dense denseOut(width,height,newData);
    return denseOut;
}
int Dense::GetAddress(int row, int col){
    int addr = row*width + col; 
    return addr;
}
Dense Dense::EigenVector(int n){
    // Calculates Eigen Vector using Power methods
    vector<float> newData(width);
    generate(newData.begin(),newData.end(),[](){return (float)rand() / RAND_MAX;});
    Dense b_k(width,1,newData);
    Dense Ab(0,0,{}); 
    for (int i = 0; i < n; i++){
        Ab = Mult(b_k);
        b_k = Ab.Normalize();
    }
    for (int i = 0; i < b_k.data.size(); i++){
        Dense Ab_ = Scale(b_k.data.at(i));
    }
    Ab = Mult(b_k);
    return Ab;
}
Dense Dense::Eye(int m){
    Dense IdentityMatrix(m,m);
    vector<float> eyeData;
    for (int i = 0; i < m; i++){
        IdentityMatrix.Set(i,i,1.0);
    }
    return IdentityMatrix;
}
void Dense::Set(int row, int col, float dataIn){
    int addr = GetAddress(row,col);
    data[addr] = dataIn;
}

Dense Dense::Normalize(){
    float sum = 0;
    for (int i = 0; i < data.size(); i++){
        sum += data.at(i)*data.at(i);
    }
    float NormFactor = 1 / sqrt(sum);
    Dense NormedMat = Scale(NormFactor);
    return NormedMat; 
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