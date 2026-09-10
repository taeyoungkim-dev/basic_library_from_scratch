#include "My_matrix.h"

#include <iostream>
#include <stdexcept>
#include "My_matrix.h" // 작성하신 헤더 파일

using namespace std;

// 행렬 출력을 돕는 헬퍼 함수
void print_matrix(Matrix& m, const string& name) {
    cout << "=== " << name << " (" << m.get_row_size() << "x" << m.get_col_size() << ") ===" << endl;
    for (int i = 0; i < m.get_row_size(); i++) {
        for (int j = 0; j < m.get_col_size(); j++) {
            cout << m(i, j) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    try {
        cout << "[1] 행렬 초기화 테스트" << endl;
        // 2x3 행렬 A 생성
        Matrix A(2, 3);
        A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
        A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
        print_matrix(A, "Matrix A");

        // 3x2 행렬 B 생성
        Matrix B(3, 2);
        B(0, 0) = 7;  B(0, 1) = 8;
        B(1, 0) = 9;  B(1, 1) = 10;
        B(2, 0) = 11; B(2, 1) = 12;
        print_matrix(B, "Matrix B");

        // 2x3 행렬 C 생성 (A와 더하기/빼기 용도)
        Matrix C(2, 3);
        C(0, 0) = 6; C(0, 1) = 5; C(0, 2) = 4;
        C(1, 0) = 3; C(1, 1) = 2; C(1, 2) = 1;
        print_matrix(C, "Matrix C");

        cout << "[2] 덧셈 및 뺄셈 테스트 (A + C, A - C)" << endl;
        Matrix Add_Result = A + C;
        print_matrix(Add_Result, "A + C");

        Matrix Sub_Result = A - C;
        print_matrix(Sub_Result, "A - C");

        cout << "[3] 대망의 곱셈 테스트 (A * B)" << endl;
        // (2x3) * (3x2) = (2x2) 행렬이 나와야 함
        Matrix Mul_Result = A * B;
        print_matrix(Mul_Result, "A * B");

        cout << "[4] 예외 처리(Exception) 테스트" << endl;
        cout << "크기가 다른 행렬(A와 B)을 더하려고 시도해 봅니다..." << endl;
        Matrix Error_Result = A + B; // 여기서 에러가 발생하고 catch 블록으로 넘어가야 함

    } catch (const std::out_of_range& e) {
        cerr << "\n✅ 의도된 에러 캐치 성공: " << e.what() << endl;
    } catch (const std::exception& e) {
        cerr << "\n❌ 예상치 못한 에러: " << e.what() << endl;
    }

    return 0;
}