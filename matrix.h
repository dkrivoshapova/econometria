#pragma once
#include <iostream>

class S21Matrix {
 private:
    friend S21Matrix operator*(const double num, const S21Matrix& other);
    int _rows, _cols;
    double** _matrix;

    void print_matrix() const;
    void copy_matrix(const S21Matrix&);
    S21Matrix minor(int rows, int cols);
    void fill_matrix();
    void delete_matrix();
    void my_swap(S21Matrix& other);

 public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    int getRows() const;
    int getCols() const;
    void setRows(int number);
    void setCols(int number);

    bool eq_matrix(const S21Matrix& other) const;
    bool eq_matrix_dimensions(const S21Matrix& other) const;
    bool eq_matrix_element(const S21Matrix& other) const;
    void sum_matrix(const S21Matrix& other);
    void sub_matrix(const S21Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const S21Matrix& other);
    S21Matrix transpose();
    S21Matrix calc_complements();
    double determinant();
    S21Matrix inverse_matrix();

    S21Matrix operator+(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix operator*(const double num);
    bool operator==(const S21Matrix& other);
    S21Matrix& operator=(const S21Matrix& other);
    S21Matrix& operator=(S21Matrix&& other);
    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);
    S21Matrix& operator*=(const double num);
    double& operator()(int i, int j) const;
};
