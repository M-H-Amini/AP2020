//
// Created by Hossein on 3/18/2020.
//

#include <optional>
#include <iostream>
#include "aphw2.h"

std::optional<double> det(Matrix &matrix) {
    if (matrix.getSize()[0] == matrix.getSize()[1]){
        return matrix.det();
    }else{
        return 0;
    }
}

std::optional<Matrix> inv(Matrix & matrix) {
    if (matrix.getSize()[0] == matrix.getSize()[1]){
        return matrix.inv();
    }else{
        std::cout << "Matrix not square" << std::endl;
        return std::nullopt;
    }
}

std::optional<Matrix> transpose(Matrix & matrix) {
    return matrix.T();
}

std::vector<std::vector<double>> getData(const char *filename, bool add_bias) {
    Matrix matrix;
    matrix.load(filename);
    if (add_bias){
        std::vector<std::vector<double >> data;
        for (int i = 0; i < matrix.getSize()[0]; ++i) {
            std::vector<double > vector;
            vector.push_back(1);
            for (int j = 0; j < matrix.getSize()[1]; ++j) {
                vector.push_back(matrix[i][j]);
            }
            data.push_back(vector);
        }
        return data;
    }else{
        std::vector<std::vector<double >> data;
        for (int i = 0; i < matrix.getSize()[0]; ++i) {
            std::vector<double > vector;
            for (int j = 0; j < matrix.getSize()[1]; ++j) {
                vector.push_back(matrix[i][j]);
            }
            data.push_back(vector);
        }
        return data;
    }
}

Matrix findWeights(const char * fileName) {
    Matrix matrix(getData(fileName, true));


    Matrix y = matrix.col(matrix.getSize()[1] - 1);
    Matrix x = matrix.delCol(matrix.getSize()[1] - 1);
//    y.show();

    Matrix w = ((x.T() * x).inv()) * x.T() * y;
//    w.show();
    return w;
}

Matrix predict(const char * fileName, const Matrix& w, bool disp) {
    Matrix matrix = getData(fileName, true);
    Matrix y = matrix.col(matrix.getSize()[1] - 1);
    Matrix x = matrix.delCol(matrix.getSize()[1] - 1);
    Matrix estimate = (x) * w;
//    x.show();
    std::cout << "estimate : " << estimate.getSize()[0] << std::endl;
    std::cout << "estimate : " << estimate.getSize()[1] << std::endl;
//    std::cout << "estimate : " << estimate[0][1] << std::endl;
//    std::cout << "estimate : " << estimate[0][2] << std::endl;
//    std::cout << "estimate : " << estimate[0][3] << std::endl;
//    estimate.show();

    if(disp){
        std::cout << "No" << "\t" << "Real Grade" << "\t" << "Estimated Grade" << std::endl;
        for (int i = 0; i < 40; ++i) {
            std::cout << "*";
        }
        std::cout << std::endl;

        for (int j = 0; j < y.getSize()[0]; ++j) {
            std::cout << j << "\t" << y[j][0] << "\t\t" << estimate[j][0] << std::endl;
        }
    }

    return x * w ;
}

size_t findMinNoOfMultiplications(std::vector<Matrix>& v){
    return 12;
}
