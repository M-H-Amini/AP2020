//

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Matrix.h"


Matrix::Matrix(const Matrix &mat) {
    size = mat.size;
    for (int i = 0; i < mat.size[0]; ++i) {
        data.push_back(mat.data[i]);
    }
}


Matrix::Matrix() {}

Matrix::Matrix(std::vector<std::vector<double>> data) {
    this->data = data;
    size[0] = data.size();
    size[1] = data[0].size();
}

Matrix::Matrix(std::unique_ptr<std::unique_ptr<double[]>[]> data, size_t m, size_t n) {
    size[0] = m;
    size[1] = n;
}

std::array<int, 2> Matrix::getSize() {
    return size;
}

Matrix::Matrix(size_t m, size_t n, bool ones) {
    size[0] = m;
    size[1] = n;
    for (size_t i = 0; i < m; i++) {
        std::vector<double> v;
        for (size_t j = 0; j < n; ++j) {
            v.push_back((ones) ? 1 : 0);
        }
        data.push_back(v);
    }
}

double Matrix::det() {
    double sum(0);
    if (size[0] == size[1]) {
        if (size[0] == 1) {
            return data[0][0];
        } else if (size[0] > 2) {
            for (int k = 0; k < size[1]; ++k) {
                std::vector<std::vector<double>> subMat;
                for (int i = 1; i < size[0]; ++i) {
                    std::vector<double> forMat;
                    for (int j = 0; j < size[1]; ++j) {
                        if (j != k) {
                            forMat.push_back(data[i][j]);
                        }
                    }
                    subMat.push_back(forMat);
                }
                sum = sum + (pow(-1, k) * data[0][k] * Matrix(subMat).det());
            }
            return sum;
        } else if (size[0] == 2) {
            return (data[0][0] * data[1][1]) - (data[0][1] * data[1][0]);
        }
    } else {
        return 0;
    }
    return 0;
}

Matrix Matrix::T() {
    std::vector<std::vector<double>> newData;
    for (int j = 0; j < size[1]; ++j) {
        std::vector<double> innerVector;
        innerVector.reserve(size[0]);
        for (int i = 0; i < size[0]; ++i) {
            innerVector.push_back(data[i][j]);
        }
        newData.push_back(innerVector);
    }
    return Matrix(newData);
}

void Matrix::show() {
    for (int i = 0; i < size[0]; ++i) {
        for (int j = 0; j < size[1]; ++j) {
            std::cout << data[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::delCol(size_t col) {
    std::vector<std::vector<double>> newData;
    int column(col);
    for (int i = 0; i < size[0]; i++) {
        std::vector<double> innerVector;
        innerVector.reserve(size[1]);
        for (int j = 0; j < size[1]; j++) {
            if (j != column) {
                innerVector.push_back(data[i][j]);
            }
        }
        newData.push_back(innerVector);
    }
    data.clear();
    for (int i = 0; i < size[0]; i++) {
        data.push_back(newData[i]);
    }
    size[1] = newData[0].size();
    return Matrix(newData);
}

Matrix Matrix::col(size_t col) {
    std::vector<std::vector<double>> newData;
    int column(col);
    for (int i = 0; i < size[0]; i++) {
        std::vector<double> innerVector;
        innerVector.reserve(size[1]);
        for (int j = 0; j < size[1]; j++) {
            if (j == column) {
                innerVector.push_back(data[i][j]);
            }
        }
        newData.push_back(innerVector);
    }
    return Matrix(newData);
}

void Matrix::save(const char *c) {
    std::ofstream myfile;
    std::string address(c);
    myfile.open(address + ".csv");
    for (int i = 0; i < size[0]; ++i) {
        std::string row;
        for (int j = 0; j < size[1]; ++j) {
            row = row + std::to_string(data[i][j]) + ((j == size[1] - 1) ? "\n" : " ,");
        }
        myfile << row;
    }
    myfile.close();
}

void Matrix::load(const char *c) {
    std::fstream fin;
    std::string line;
    std::string word;
    fin.open(c, std::ios::in);
    std::vector<std::vector<double>> newData;
    while (std::getline(fin, line)) {
        std::vector<double> vector;
        std::stringstream s(line);
        while (std::getline(s, word, ',')) {
            vector.push_back(atof(word.c_str()));
        }
        newData.push_back(vector);
    }
    data = newData;
    size[0] = newData.size();
    size[1] = newData[0].size();
}

Matrix Matrix::operator+(const Matrix &matrix) {
    std::vector<std::vector<double>> newData;
    if (size[0] == matrix.size[0] && size[1] == matrix.size[1]) {
        for (int i = 0; i < size[0]; ++i) {
            std::vector<double> vector;
            vector.reserve(size[1]);
            for (int j = 0; j < size[1]; ++j) {
                vector.push_back(data[i][j] + matrix.data[i][j]);
            }
            newData.push_back(vector);
        }
        return Matrix(newData);
    } else {
        return Matrix(data);
    }
}

Matrix Matrix::operator-(const Matrix &matrix) {
    std::vector<std::vector<double>> newData;
    if (size[0] == matrix.size[0] && size[1] == matrix.size[1]) {
        for (int i = 0; i < size[0]; ++i) {
            std::vector<double> vector;
            vector.reserve(size[1]);
            for (int j = 0; j < size[1]; ++j) {
                vector.push_back(data[i][j] - matrix.data[i][j]);
            }
            newData.push_back(vector);
        }
        return Matrix(newData);
    } else {
        return Matrix(data);
    }
}

Matrix Matrix::operator*(const Matrix &matrix) {
    if (size[1] == matrix.size[0]) {
        std::vector<std::vector<double>> newData;
        for (int i = 0; i < size[0]; ++i) {
            std::vector<double> vector;
            for (int k = 0; k < matrix.size[1]; ++k) {
                vector.reserve(size[1]);
                double sum(0);
                for (int j = 0; j < size[1]; ++j) {
                    sum = sum + (data[i][j] * matrix.data[j][k]);
                }
                vector.push_back(sum);
            }
            newData.push_back(vector);
        }
        return Matrix(newData);
    } else {
        return Matrix(data);
    }
}

Matrix Matrix::inv() {

    double determinate = det();
    if (determinate != 0) {
        std::vector<std::vector<double >> finalData;
        for (int i = 0; i < size[0]; ++i) {
            std::vector<double> vectorFinal;
            for (int j = 0; j < size[1]; ++j) {
                std::vector<std::vector<double >> newData;
                for (int k = 0; k < size[0]; ++k) {
                    std::vector<double> vector;
                    for (int l = 0; l < size[1]; ++l) {
                        if (k != i && l != j) {
                            vector.push_back(data[k][l]);
                        }
                    }
                    if (!vector.empty()) {
                        newData.push_back(vector);
                    }
                }
                vectorFinal.push_back(pow(-1, i + j) * Matrix(newData).det() / determinate);
            }
            finalData.push_back(vectorFinal);
        }
        return Matrix(finalData).T();
    } else {
        return Matrix() ;
    }
}

std::vector<double >& Matrix::operator[](const int &row) {
    return data[row];
}






