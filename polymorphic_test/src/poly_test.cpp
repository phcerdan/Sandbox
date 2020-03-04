/* Copyright (C) 2019 Pablo Hernandez-Cerdan
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <typeinfo>

struct Base
{
  size_t m_base;
  Base() = default;
  Base(const size_t & input_m_base) : m_base(input_m_base) {};
  virtual ~Base() = default;
};
struct Derived : public Base {
  double m_derived;
  using Base::Base;
  Derived(const size_t &input_m_base, const double & input_m_derived) : Base(input_m_base), m_derived(input_m_derived) {};
};


using vec_base_t = std::vector<std::shared_ptr<Base>>;

void use_vec_base(const std::vector<std::shared_ptr<Base>> & vec_of_bases) {
  std::cout << "Using vec_base with Base type" << std::endl;
}
void use_vec_base(const std::vector<std::shared_ptr<Derived>> & vec_of_bases) {
  std::cout << "Using vec_base with Derived type" << std::endl;
}

void use_base(const Base* base) {
  std::cout << "use_base with pointer of type Base" << std::endl;
}
void use_base(const Derived* derived) {
  std::cout << "use_base with pointer of type Derived" << std::endl;
}

template <class T>
void doMyStuff(T *t) { }  // in general do nothing

template <>
void doMyStuff(Base *t) { std::cout << "do something with Base*"<<std::endl; }

template <>
void doMyStuff(Derived *t) { std::cout << "do something with Derived*"<< std::endl; }

void doMyStuffWithTypeInfo(Base *t) {
  std::cout << "doMyStuffWithTypeInfo something with a Base pointer: ";

  const auto &type_info = typeid(*t);
  if(type_info == typeid(Base))
    std::cout << "typeid is Base." << std::endl;
  if(type_info == typeid(Derived))
    std::cout << "typeid is Derived." << std::endl;
}


int
main(int, char *[])
{
  vec_base_t vec_of_bases;
  vec_of_bases.emplace_back(std::make_shared<Base>(1));
  vec_of_bases.emplace_back(std::make_shared<Base>(2));
  use_vec_base(vec_of_bases);
  use_base(vec_of_bases[0].get());
  doMyStuff(vec_of_bases[0].get());
  // The following works iwith typeid
  doMyStuffWithTypeInfo(vec_of_bases[0].get());

  vec_base_t vec_of_derived;
  vec_of_derived.emplace_back(std::make_shared<Derived>(1, 1.0));
  vec_of_derived.emplace_back(std::make_shared<Derived>(2, 2.0));
  use_vec_base(vec_of_derived);
  use_base(vec_of_derived[0].get());
  // This works, but need to know beforehand what type to cast into
  doMyStuff(std::static_pointer_cast<Derived>(vec_of_derived[0]).get());
  // The following works iwith typeid
  doMyStuffWithTypeInfo(vec_of_derived[1].get());
  return EXIT_SUCCESS;
}
