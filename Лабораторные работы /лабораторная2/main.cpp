//
//  main.cpp
//  лаба2
//
//  Created by Александр Цыплаков on 01.12.2022.

#include <iostream>
#include "sys/malloc.h"
#include "math.h"

using namespace std;
template <typename T>

class Matrix{ //класс содержит три поля, массив с данными и размерность
public:
    //1
    T** matrix_Array;
    int dim_n;
    int dim_m;
    //2
    Matrix(int n, int m){
        matrix_Array = new T* [n];
        
        for(int i = 0; i < n; i++){
            matrix_Array[i] = new T[m];
        }
        
        this->dim_n = n;
        this->dim_m = m;
        
        for(int i = 0; i < dim_n; i++){
            for(int j = 0; j < dim_m; j++){
                this->matrix_Array[i][j] = 1;
            }
        }
    }
    
    Matrix(int n){
        matrix_Array = new T* [n];
        
        for(int i = 0; i < n; i++){
            matrix_Array[i] = new T;
        }
        
        this->dim_n = n;
        this->dim_m = 1;

    }
    
    Matrix(initializer_list<initializer_list<T>> t){
        this->dim_n = t.size();
        this->dim_m = t.begin()->size();
        matrix_Array = new T* [dim_n];
        
        for(int i = 0; i < dim_n; i++){
            matrix_Array[i] = new T[dim_m];
        }
        
        for(int i = 0; i < dim_n; i++){
            for(int j = 0; i < dim_m; i++){
                matrix_Array[i][j] = *((t.begin() + i)->begin() + j);
            }
        }
        
    }
    
    //3 Конструктор копирования
    Matrix(Matrix* m1){
        this->dim_m = m1->dim_m;
        this->dim_n = m1->dim_n;
        
        matrix_Array = new T* [dim_n];
        
        for(int i = 0; i < dim_n; i++){
            matrix_Array[i] = new T[dim_m];
        }
        
        for(int i = 0; i < dim_n; i++){
            for(int j = 0; j < dim_m; j++){
                this->matrix_Array[i][j] = m1->matrix_Array[i][j];
            }
        }
    }
    
    //4
    Matrix operator = (Matrix* m1){
        
        for(int i = 0; i < this->dim_n; i++){
            delete[] this->matrix_Array[i];
        }
        
        delete[] this->matrix_Array;
        
        this->dim_m = m1->dim_m;
        this->dim_n = m1->dim_n;
        
        matrix_Array = new T* [dim_n];
        
        for(int i = 0; i < dim_n; i++){
            matrix_Array[i] = new T[dim_m];
        }
        
        for(int i = 0; i < dim_n; i++){
            for(int j = 0; j < dim_m; j++){
                this->matrix_Array[i][j] = m1->matrix_Array[i][j];
            }
        }
    }
    
    //5
    Matrix(Matrix&& other){
        dim_m = other.dim_m;
        dim_n = other.dim_n;
        matrix_Array = other.matrix_Array;
        other.matrix_Array = nullptr;
        other.dim_m = 0;
        other.dim_n = 0;
    }
    
    //6
    friend ostream& operator << (ostream& out, Matrix<T>& myMatrix){
        for (int i = 0; i < myMatrix.dim_n; ++i){
            for (int j = 0; j < myMatrix.dim_m; ++j) {
                out << myMatrix.matrix_Array[i][j] << " ";
            }
            out << endl;
        }
        out << endl;
        return out;
    }
    
    void show_Matrix() {
            for (int i = 0; i < dim_n; ++i){
                for (int j = 0; j < dim_m; ++j) {
                    cout << matrix_Array[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
    }
    
    //7
    T& operator()(int row, int col)
    {
        return matrix_Array[row][col];
    }
     
    T operator()(int row, int col) const
    {
        return matrix_Array[row][col];
    }
    
    //8
    Matrix operator - (Matrix m1) {
        try{
            if(dim_m != m1.dim_m || dim_n != m1.dim_n) throw "Exception!";
                Matrix result(dim_n, dim_m);
                for (int i = 0; i < dim_n; i++) {
                    for (int j = 0; j < dim_m; j++) {
                        result.matrix_Array[i][j] = matrix_Array[i][j] -  m1.matrix_Array[i][j];
                    }
                }
                return result;
         }catch(string error){
            cout << error;
        }
      }

    Matrix operator + (Matrix m1) {
        try{
            if(dim_m != m1.dim_m || dim_n != m1.dim_n) throw "Exception!";
                Matrix result(dim_n, dim_m);
                for (int i = 0; i < dim_n; i++) {
                    for (int j = 0; j < dim_m; j++) {
                        result.matrix_Array[i][j] = matrix_Array[i][j] +  m1.matrix_Array[i][j];
                    }
                }
                return result;
         }catch(string error){
            cout << error;
        }
    }
    
    Matrix operator * (int a) {
            Matrix result(dim_n, dim_m);
            for (int i = 0; i < dim_n; i++) {
                for (int j = 0; j < dim_m; j++) {
                    result.matrix_Array[i][j] = a * matrix_Array[i][j] ;
                }
            }
            return result;
    }
    
    Matrix operator * (Matrix m1) {
        try{
            if(dim_m != m1.dim_n) throw "Exception!";
                Matrix result(this->dim_n, m1.dim_m);
                double temp_elem = 0;
                for (int i = 0; i < this->dim_n; i++) {
                    for (int j = 0; j < m1.dim_m; j++) {
                        for (int r = 0; r < this->dim_m; r++) {
                            temp_elem += this->matrix_Array[i][r] * m1.matrix_Array[r][j];
                        }
                        result.matrix_Array[i][j] = temp_elem;
                        temp_elem = 0;
                    }
                }
                return result;
            
        }catch(string error){
            cout << error;
        }
    }
    
    //9
    Matrix& operator+=(Matrix& right) {
        try{
            if(dim_m != right.dim_m || dim_n != right.dim_n) throw "Exception!";
                for (int i = 0; i < dim_n; i++) {
                    for (int j = 0; j < dim_m; j++) {
                        matrix_Array[i][j] +=  right.matrix_Array[i][j];
                    }
                }
            return *this;
        }catch(string error){
            cout << error;
        }
    }
    
    Matrix& operator-=(Matrix& right) {
        try{
            if(dim_m != right.dim_m || dim_n != right.dim_n) throw "Exception!";
                for (int i = 0; i < dim_n; i++) {
                    for (int j = 0; j < dim_m; j++) {
                        matrix_Array[i][j] -=  right.matrix_Array[i][j];
                    }
                }
                return *this;
        }catch(string error){
            cout << error;
        }
    }
    
    Matrix& operator *= (int a) {
        for (int i = 0; i < dim_n; i++) {
            for (int j = 0; j < dim_m; j++) {
                matrix_Array[i][j] *= a;
            }
        }
        return *this;
    }

    
    
};

int main(){
    
    Matrix<double> matrix0(4,6);
    Matrix<double> matrix1(6,2);
    //initializer_list<int> t = {1, 2, 3};
    //initializer_list<initializer_list<int>> k = {{1, 2, 3}, {1, 2, 3}};
    //initializer_list<initializer_list<int>> n = {{1}, {2}, {3}};
    //Matrix<int> matrix2 = {{1, 2, 3}, {1, 2, 3}};
    //matrix2.show_Matrix();
    Matrix<double> matrix3(4,6);
    matrix3 *= 2;
    cout << matrix3;
    
    return 0;
}

