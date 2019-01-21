#include "dense.h"
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<float> Adata = {1,1,1,1};
    vector<float> Bdata = {1,5,2,1};
    Dense A(2,2,Adata);
    Dense B(2,2,Bdata);
    // Addition
    cout << endl << "----- Addition -----" << endl;
    cout << "Matrix A: " << endl;
    A.print();
    cout << "Matrix B: " << endl;
    B.print();

    // Multiplication
    cout << endl << "----- Multiplication -----" << endl;
    Adata = {1, 2, 3, 4, 5, 6};
    Bdata = {7,8,1,9,10,1,11,12,1};
    Dense A2(2,3,Adata);
    Dense B2(3,3,Bdata);
    
    cout << "Matrix A: " << endl;
    A2.print();
    cout << "Matrix B: " << endl;
    B2.print();

    Dense C = A2.Mult(B2);
    cout << "Matrix A * B: " << endl;
    C.print();

    // Dot
    cout << endl << "----- Dot Product -----" << endl;
    Adata = {1, 2, 3, 4, 5, 6};
    Bdata = {1, 2, 3, 4, 5, 6};
    Dense A3(2,3,Adata);
    Dense B3(2,3,Bdata);
    
    cout << "Matrix A: " << endl;
    A3.print();
    cout << "Matrix B: " << endl;
    B3.print();

    C = A3.Dot(B3);
    cout << "Matrix A .* B: " << endl;
    C.print();

    // Scaling
    cout << endl << "----- Scale -----" << endl;
    C = A3.Scale(2);
    cout << "Matrix A * 2" << endl;
    C.print();
    // This also works
    B = Dense(1,1,{2});
    C = A3.Dot(B);
    cout << "Matrix A .* 2" << endl;
    C.print();

    return 0;
}
