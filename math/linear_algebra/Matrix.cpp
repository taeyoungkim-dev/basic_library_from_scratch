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
        int get_row_size(void){
            return this->row_size;
        }
        int get_col_size(void){
            return this->col_size;
        }
        //operator overloading
        //What's wrong?
        friend bool operator=(Matrix right_matrix);
        double operator()(int row, int col){
            return this->data[row*this->col_size+col];
        }

        Matrix operator+(Matrix right_matrix){
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
        Matrix operator-(Matrix right_matrix){
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
        Matrix operator*(Matrix*right_matrix){
        }
}