#pragma once

#include "array.hpp"
#include <iostream>
#include <utility>
#include <cmath>
#include <type_traits>

const double zero = 0.0;

template<typename T>
requires std::is_scalar_v<T> && std::is_arithmetic_v<T>
class Figure {
  public:
    virtual T square() const = 0;
    virtual std::pair<T, T> geom_center() const = 0;
    virtual ~Figure() = default;
};