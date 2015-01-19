// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#ifndef COMMON_H_
#define COMMON_H_

#include <memory>

// default deleter version
template<typename T, typename ... Args>
std::unique_ptr<T> make_unique(Args&&... args) {  // NOLINT
  return std::unique_ptr<T>{new T{args...}};
}

template <class T>
using sp = std::shared_ptr<T>;

template <class T>
using wp = std::weak_ptr<T>;

template <typename T, int N>
constexpr int sizeof_array(const T (&)[N] ) {
  return N;
}

#endif  // COMMON_H_
