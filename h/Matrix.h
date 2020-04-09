//
// Created by Hossein on 3/12/2020.
//

#ifndef APHW2_MATRIX_H
#define APHW2_MATRIX_H


#include <vector>
#include <bits/unique_ptr.h>

class Matrix {
public:
    Matrix();

    Matrix(const Matrix& mat);
    Matrix(std::vector<std::vector<double>> data);
    Matrix (std::unique_ptr<std::unique_ptr<double[]>[]> data, size_t m, size_t n);
    Matrix (size_t m, size_t n, bool ones=true);
    std::array<int, 2> getSize();
    double det();
    Matrix T();
    void show();
    Matrix delCol(size_t i);
    Matrix col(size_t i);
    void save(const char*);
    void load(const char*);

    Matrix operator+ (const Matrix &);
    Matrix operator- (const Matrix &);
    Matrix operator* (const Matrix &);
    std::vector<double >& operator[] (const int &);


    Matrix inv();
private:
    std::array<int, 2> size{};
    std::vector<std::vector<double>> data;

};


#endif //APHW2_MATRIX_H
