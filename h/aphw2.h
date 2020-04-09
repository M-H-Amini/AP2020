//
// Created by Hossein on 3/18/2020.
//


#include "Matrix.h"
#include <optional>

std::optional<double> det(Matrix&);
std::optional<Matrix> inv(Matrix&);
std::optional<Matrix> transpose(Matrix&);
Matrix findWeights(const char*);
Matrix predict(const char*, const Matrix& w, bool disp=false);
std::vector<std::vector<double>> getData(const char* filename, bool add_bias=true);
size_t findMinNoOfMultiplications(std::vector<Matrix>& v);


