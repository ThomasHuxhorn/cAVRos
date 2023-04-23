/*
    This file is part of cAVRos - AVR C++ Framework - simple, fast, modern, type safe
    Copyright (C) 2023- Thomas Huxhorn

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#ifndef IO_HPP
#define IO_HPP

#include <type_traits>

// Include lib avr gcc
#include <avr/io.h>

/// A macro to define bitwise operator overloads for enum types.
/// \TODO Can we do this with c++ templates?
#define ENUM_FLAG_OPERATORS(T)  \
  inline T operator| (T left, T right) { \
    using U = std::underlying_type_t<T>; \
    return T( U(left) | U(right) ); \
  }

// analog digial converter
#include <cavros/detail/adc.hpp>

#endif // IO_HPP
