#include <iostream>
#include <vector>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>

std::vector<double> gen(){ return {1,2,3}; }

std::vector<double> filter(const std::vector<double> & v ) {
   std::cout << "v SIZE: " << v.size() << std::endl;
   std::cout << "is empty? : " << v.empty() << std::endl;
   std::vector<double> out(v.size());
   return out;
}

PYBIND11_MODULE(bad_alloc, m) {
    m.def("gen", &gen);
    m.def("filter", &filter);
}
