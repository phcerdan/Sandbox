/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <iostream>
#include <algorithm>
#include <string>
// #include <itkeigen/Eigen/Core>
// #include <itkeigen/Eigen/SparseCholesky>
#include <Eigen/Core>
// #include <Eigen/SparseCholesky>

int main(int , char ** )
{
    std::cout << "HOLA!" << std::endl;
    std::string a("adios!");
    a.append("\nWHAT?");
    std::cout << a << std::endl;
    a.assign("Hola");
    Eigen::Matrix2d mat;
    mat.setOnes();
    std::cout << mat << std::endl;
}

