/* File: DebugEveryThing.hpp
* Author: RuneShell (dlhj09@gmail.com)
* Locate: https://github.com/RuneShell/Tools
* Licences: MIT License - Copyright (c) 2025, RuneShell
*/

#pragma once
#define _DEBUGEVERYTHING_HPP

/* [ Usage Exapmple of '_Debug()' ]
#include <iostream>
#include <vector>
#include <string>
#include "DebugEveryThing.hpp"

int main() {
    int a = 3;
    std::string s = "Hello World!";
    std::vector<int> v{ 1, 2, 3 };
    std::vector<std::vector<int>> vv{ {5, 6, 7}, {8, 9} };
    char c[50] = "Hello World!\0";
    const char* cc = "Hello World!";

    // Debug Here
    _Debug(a, s, v, vv, c, cc); // Result Below
    // [ C:\...file_absolute_location...\test.cpp :: main() :: Line 14 ]
    //      int [a] = 3
    //      std::basic_string [s] = Hello World!
    //      std::vector [v] = [1, 2, 3]
    //      std::vector [vv] = [[5, 6, 7], [8, 9]]
    //      char * __ptr64 [c] = Hello World!
    //      char const * __ptr64 [cc] = Hello World!
}
*/

//*======================*/
#include <iostream>
#include <typeinfo>
#include <type_traits>

/*==== Main Function ====*/
#ifndef _Debug(...)
#define _Debug(...) std::cerr << "[ " << __FILE__ << " :: " <<  __func__ << "() :: Line " << __LINE__ << " ]\n"; \
                   _printWrap(#__VA_ARGS__, __VA_ARGS__); std::cout << std::endl;
#endif



/*==== Helper Functions  ====*/

// A trait checks if input is container
template<typename T, typename = void>
struct is_container : std::false_type {};

template<typename T>
struct is_container<T, std::void_t<
    typename T::value_type,
    typename T::iterator,
    decltype(std::declval<T>().begin())
    >> : std::true_type {};


// print typename, varname
void _printMeta(std::string typeName, std::string valName) {
    // if Typyname is too long
    if (typeName.size() >= 5 && typeName.substr(0, 5) == "class") {
        size_t pos = typeName.find('<');
        typeName = typeName.substr(6, pos - 6);
    }
    std::cerr << '\t' << typeName << " [" << valName << "] = ";
}

// print inner values if container
template<typename T>
void _printInner(const T& value) {
    if constexpr (is_container<T>::value && !std::is_same_v<T, std::string>) { // define in compile time
        std::cerr << "[";
        for (const auto& elem : value) {
            _printInner(elem);
            std::cerr << ", ";
        }
        std::cerr << "\b\b]";
    }
    else {
        std::cerr << value;
    }
}

// print_function wrappers
template<typename T>
void _printWrap(std::string valName, T x) {
    _printMeta(typeid(x).name(), valName);
    _printInner(x);
    std::cerr << '\n';
}
template<typename T, typename... Ts>
void _printWrap(std::string valName, T x, Ts... args) {
    size_t pos = valName.find(' ');
    _printMeta(typeid(x).name(), valName.substr(0, pos - 1));
    _printInner(x);
    std::cerr << '\n';
    _printWrap(valName.substr(pos + 1), args...);
}
