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
            if (row_size <= 0 || col_size <= 0) {
                throw std::invalid_argument(
                    "[Error] Matrix row and column sizes must be greater than zero."
                );
            }
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

//A^t
Matrix transpose_matrix(Matrix& matrix){
    int result_row = matrix.get_col_size();
    int result_col = matrix.get_row_size();

    Matrix result_matrix(result_row,result_col);
    for(int i=0;i<result_row;i++){
        for(int j=0;j<result_col;j++){
            result_matrix(j,i) = matrix(i,j);
        }
    }
    return result_matrix;
}

//Minor is a matrix which is removed one row and one col
Matrix get_minor(Matrix& matrix,int removed_row, int removed_col){
    int result_row = matrix.get_row_size()-1;
    int result_col = matrix.get_col_size()-1;

    if(result_row==0 || result_col==0){
        throw std::invalid_argument(
            "[Error] Cannot create a minor matrix from a matrix with dimension 1.");
    }

    Matrix result_matrix(result_row,result_col);

    int r_m_row_index = 0;

    for(int i=0;i<result_row+1;i++){
        if(i==removed_row) continue;
        int r_m_col_index = 0;
        for(int j=0;j<result_col+1;j++){
            if(j==removed_col) continue;
            result_matrix(r_m_row_index,r_m_col_index) = matrix(i,j);
            r_m_col_index += 1;
        }
        r_m_row_index += 1;
    }
    return result_matrix;
}

//det(A) == sigma(from j==1 to n){(-1)^(i+j)*a_ij*det(M_ij)}
//TODO : Input should be (const Matrix &) because of problem line
//So Should edit Matrix class
//TODO : Do not use recursive function
double determinant(Matrix matrix){
    int matrix_row_size = matrix.get_row_size();
    int matrix_col_size = matrix.get_col_size();

    if(matrix_row_size!=matrix_col_size){
        throw std::invalid_argument(
            "[Error] Matrix is not a square matrix."
        );
    }

    if(matrix_row_size==1)return matrix(0,0);

    //ad-bc
    if(matrix_row_size==2){
        return matrix(0,0)*matrix(1,1) - matrix(0,1)*matrix(1,0);
    }

    //Laplace expansion
    //TODO : Optimization by gaussian elimination
    double result = 0;
    for(int j=0;j<matrix_col_size;j++){
        //Fixed i = 0
        //Very bad method
        int i=0;
        double sign = 1;
        if(((i+1)+(j+1))&1) sign = -1;
        //TODO : Problem line
        result += sign * matrix(i,j)*determinant(get_minor(matrix,i,j));
    }
    return result;
}


bool is_invertible_matrix(Matrix& matrix){
    //if not square matrix
    if(matrix.get_row_size()!=matrix.get_col_size()){
        return false;
    }


}


Matrix inverse_matrix(Matrix& matrix){

}

//Making square matrix from nonsquare matrix
Matrix intuive_matrix(Matrix& matrix){

}