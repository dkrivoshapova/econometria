#include "matrix.h"

#include <cmath>

S21Matrix::S21Matrix(int rows, int cols) {
    if (rows < 1 || cols < 1) throw std::invalid_argument("Incorrect argument");
    _cols = cols;
    _rows = rows;
    _matrix = new double*[_rows];
    for (int i = 0; i < _rows; i++) {
        _matrix[i] = new double[_cols]();
    }
}

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(const S21Matrix& other) : S21Matrix(other._rows, other._cols) { copy_matrix(other); }

S21Matrix::S21Matrix(S21Matrix&& other) : _rows(0), _cols(0), _matrix(nullptr) { my_swap(other); }

S21Matrix::~S21Matrix() {
    if (_matrix) {
        delete_matrix();
    }
}

int S21Matrix::getRows() const { return _rows; }

int S21Matrix::getCols() const { return _cols; }

void S21Matrix::setRows(int number) {
    if (number < 1) throw std::invalid_argument("Incorrect number");
    S21Matrix tmp(number, _cols);
    for (int i = 0; i < tmp._rows; i++) {
        for (int j = 0; j < tmp._cols; j++) {
            if (i < _rows) {
                tmp._matrix[i][j] = _matrix[i][j];
            }
        }
    }
    *this = tmp;
}

void S21Matrix::setCols(int number) {
    if (number < 1) throw std::invalid_argument("Incorrect number");
    S21Matrix tmp(_rows, number);
    for (int i = 0; i < tmp._rows; i++) {
        for (int j = 0; j < tmp._cols; j++) {
            if (j <_cols) {
                tmp._matrix[i][j] = _matrix[i][j];
            }
        }
    }
    *this = tmp;
}

void S21Matrix::delete_matrix() {
    for (int i = 0; i < _rows; i++) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
    _matrix = nullptr;
}

bool S21Matrix::eq_matrix(const S21Matrix& other) const {
    bool result = false;
    if (eq_matrix_dimensions(other) && eq_matrix_element(other)) result = true;
    return result;
}

bool S21Matrix::eq_matrix_dimensions(const S21Matrix& other) const {
    bool result = false;
    if (other._cols == _cols && other._rows == _rows) result = true;
    return result;
}

bool S21Matrix::eq_matrix_element(const S21Matrix& other) const {
    bool result = true;
    for (int i = 0; i < other._rows; i++) {
        for (int j = 0; j < other._cols; j++) {
            if (fabs(_matrix[i][j] - other._matrix[i][j]) > 1E-7) result = false;
        }
    }
    return result;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
    if (!eq_matrix_dimensions(other)) throw std::invalid_argument("different matrix dimensions");
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] += other._matrix[i][j];
        }
    }
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
    if (!eq_matrix_dimensions(other)) throw std::invalid_argument("different matrix dimensions");
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] -= other._matrix[i][j];
        }
    }
}

void S21Matrix::mul_number(const double num) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] *= num;
        }
    }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
    if (_cols != other._rows)
        throw std::invalid_argument("the number of columns is not equal to the number of rows");
    S21Matrix res(_rows, other._cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < other._cols; j++) {
            for (int n = 0; n < _cols; n++) {
                res._matrix[i][j] += _matrix[i][n] * other._matrix[n][j];
            }
        }
    }
    *this = res;
}

S21Matrix S21Matrix::transpose() {
    S21Matrix transposed(_cols, _rows);
    for (int i = 0; i < _cols; i++) {
        for (int j = 0; j < _rows; j++) {
            transposed._matrix[i][j] = _matrix[j][i];
        }
    }
    return transposed;
}

S21Matrix S21Matrix::minor(int row, int col) {
    S21Matrix result(_rows - 1, _cols - 1);
    for (int i = 0; i < result._rows; i++) {
        for (int j = 0; j < result._rows; j++) {
            int ii = i;
            int jj = j;
            if (i >= row) ii += 1;
            if (j >= col) jj += 1;
            result._matrix[i][j] = _matrix[ii][jj];
        }
    }
    return result;
}

S21Matrix S21Matrix::calc_complements() {
    if (_cols != _rows) throw std::invalid_argument("the matrix is not square");
    S21Matrix complements(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            S21Matrix temp = minor(i, j);
            complements._matrix[i][j] = pow(-1.0, i + j) * temp.determinant();
        }
    }
    return complements;
}

double S21Matrix::determinant() {
    if (_cols != _rows) throw std::invalid_argument("the matrix is not square");
    double determinant = 0.0;
    if (_cols == 1) {
        determinant = _matrix[0][0];
    } else if (_cols == 2) {
        determinant = _matrix[0][0] * _matrix[1][1];
        determinant -= _matrix[0][1] * _matrix[1][0];
    } else {
        for (int j = 0; j < _cols; j++) {
            S21Matrix matrix_minor = minor(0, j);
            determinant += pow(-1.0, j) * _matrix[0][j] * matrix_minor.determinant();
        }
    }
    return determinant;
}

S21Matrix S21Matrix::inverse_matrix() {
    double matrix_determinant = determinant();
    if (fabs(matrix_determinant) < 1E-7 || std::isnan(matrix_determinant)) {
        throw std::invalid_argument("matrix determinant is 0 or Nan");
    }
    S21Matrix matrix_complements = calc_complements();
    S21Matrix matrix_transpose = matrix_complements.transpose();
    matrix_transpose.mul_number(1.0 / matrix_determinant);
    return matrix_transpose;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    S21Matrix result(*this);
    result.sum_matrix(other);
    return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix result(*this);
    result.sub_matrix(other);
    return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix result(*this);
    result.mul_matrix(other);
    return result;
}

S21Matrix S21Matrix::operator*(const double num) {
    S21Matrix result(*this);
    result.mul_number(num);
    return result;
}

S21Matrix operator*(const double num, const S21Matrix& matrix) {
    S21Matrix result(matrix);
    result.mul_number(num);
    return result;
}

bool S21Matrix::operator==(const S21Matrix& other) { return eq_matrix(other); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    S21Matrix tmp(other);
    my_swap(tmp);
    return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    sum_matrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    sub_matrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    mul_matrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
    mul_number(num);
    return *this;
}

double& S21Matrix::operator()(int i, int j) const {
    if (i < 0 || i > _rows || j < 0 || j > _cols) throw std::invalid_argument("Incorrect argument");
    return _matrix[i][j];
}

void S21Matrix::my_swap(S21Matrix& other) {
    std::swap(_rows, other._rows);
    std::swap(_cols, other._cols);
    std::swap(_matrix, other._matrix);
}

void S21Matrix::copy_matrix(const S21Matrix& other) {
    for (int i = 0; i < other._rows; i++) {
        for (int j = 0; j < other._cols; j++) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
}
