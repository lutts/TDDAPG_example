// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#ifndef TESTS_MOVIE_TEST_HELPER_H_
#define TESTS_MOVIE_TEST_HELPER_H_

#include "./Movie.h"

#include <tuple>

namespace nowplaying {
namespace tests {

MATCHER(MovieEq, "") {
  sp<Movie> m1 = std::get<0>(arg);
  sp<Movie> m2 = std::get<1>(arg);

  return *m1 == *m2;
}

}  // namespace tests
}  // namespace nowplaying

#endif  // TESTS_MOVIE_TEST_HELPER_H_
