#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;
class Matrix
{   
    private:
        double* data;
        int row_size;
        int col_size;

    public:
        Matrix(int row_size,int col_size)
            : row_size(row_size), col_size(col_size) {
            data = new double[row_size*col_size];
        }

        ~Matrix(){
            delete[] data;
        }

        /*bool insert(int row, int col, double data){
            if (row>=row_size){
                throw std::out_of_range("[Error] Matrix row index out of bound");
            }
            else if(col>=col_size){
                throw std::out_of_range("[Error] Matrix col index out of bound");
            }
            this->data[row*col_size+col] = data;
            return true;
        }

        double get(int row, int col){
            if (row>=row_size){
                //error log
                throw std::out_of_range("[Error] Matrix row index out of bound");
            }
            else if(col>=col_size){
                //error log
                throw std::out_of_range("[Error] Matrix col index out of bound");
            }
            return data[row*col_size+col];
        }
        */
        //custom function
        double dot_product(double* v1,double* v2,int size){
            double result = 0;
            for(int i=0;i<size;i++){
                result += v1[i]*v2[i];
            }
            return result;
        }

        int get_row_size(void){
            return this->row_size;
        }
        int get_col_size(void){
            return this->col_size;
        }

        //operator overloading
        Matrix& operator=(Matrix& right_matrix){
            // if left matrix is right_matrix
            if(this == &right_matrix){
                return *this;//for a=b=c command
            }
            if(this->row_size!=right_matrix.get_row_size()){
                throw std::out_of_range("[Error] Row size is differenet.");
            }
            if(this->col_size!=right_matrix.get_col_size()){
                throw std::out_of_range("[Error] Col size is differenet.");
            }
            int total_elements_num = this->row_size * this->col_size;
            for(int i=0;i<total_elements_num;i++){
                this->data[i] = right_matrix.data[i];
            }
            return *this;//for a=b=c command
        }
        double& operator()(int row, int col){
            if(this->row_size<=row||row<0){
                throw std::out_of_range("[Error] Row index is out of range.");
            }
            if(this->col_size<=col||col<0){
                throw std::out_of_range("[Error] Col index is out of range.");
            }
            return this->data[row*this->col_size+col];
        }

        Matrix operator+(Matrix &right_matrix){
            if(this->row_size!=right_matrix.get_row_size()){
                throw std::out_of_range("[Error] Row size is differenet.");
            }
            if(this->col_size!=right_matrix.get_col_size()){
                throw std::out_of_range("[Error] Col size is differenet.");
            }
            Matrix result_matrix(this->row_size,this->col_size);
            int total_elements_num = this->row_size * this->col_size;
            int i;
            for(i=0;i<total_elements_num;i++){
                result_matrix.data[i] = this->data[i] + right_matrix.data[i];
            }
            return result_matrix;
        }
        Matrix operator-(Matrix &right_matrix){
            if(this->row_size!=right_matrix.get_row_size()){
                throw std::out_of_range("[Error] Row size is differenet.");
            }
            if(this->col_size!=right_matrix.get_col_size()){
                throw std::out_of_range("[Error] Col size is differenet.");
            }
            Matrix result_matrix(this->row_size,this->col_size);
            int total_elements_num = this->row_size * this->col_size;
            int i;
            for(i=0;i<total_elements_num;i++){
                result_matrix.data[i] = this->data[i] - right_matrix.data[i];
            }
            return result_matrix;
        }

        Matrix operator*(Matrix &right_matrix){
            if(this->col_size!=right_matrix.get_row_size()){
                throw std::out_of_range("[Error] Matrix multiplication has a row,col problem.");
            }
            int new_row_size = this->row_size;
            int new_col_size = right_matrix.get_col_size();
            Matrix result_matrix(new_row_size,new_col_size);
//My method
            double* row_vector_pointer;
            double* col_vector_pointer;
            //Making col_vector from right_matrix
            int col_vecotor_num = right_matrix.get_col_size();//right matrix를 분리해서 만들 vector의 갯수. 세로 벡터는 col 갯수만큼이 있음.
            double** col_vector_array_pointer = new double*[col_vecotor_num];//vector들을 순서대로 관리할 array
            for(int i=0;i<col_vecotor_num;i++){//array에 vector 크기만큼의 array 배치
                col_vector_array_pointer[i] = new double[right_matrix.get_row_size()];
            }
            //완성된 빈 vector들에게 값을 복사. 어차피 대칭이니까 하나씩 거꾸로 옮기기.
            for(int i=0;i<right_matrix.get_row_size();i++){
                for(int j=0;j<right_matrix.get_col_size();j++){
                    col_vector_array_pointer[j][i] = right_matrix(i,j);
                }
            }

            for(int i=0;i<new_row_size;i++){
                row_vector_pointer = &(this->data[i*(this->col_size)]);
                for(int j=0;j<new_col_size;j++){
                    col_vector_pointer = col_vector_array_pointer[j];
                    result_matrix(i,j) = dot_product(row_vector_pointer,col_vector_pointer,this->col_size);
                }
            }
            for(int i=0;i<col_vecotor_num;i++){
                delete[] col_vector_array_pointer[i];
            }
            delete[] col_vector_array_pointer;
            //TODO : Search and study how to make matrix multifly faster
            return result_matrix;
        }
};