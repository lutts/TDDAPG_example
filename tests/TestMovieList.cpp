//-*- TestCaseName: TestMovieList;-*-
// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#include "MovieList.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "./common.h"
#include "./Movie.h"

namespace nowplaying {
namespace tests {

class TestMovieList : public ::testing::Test {
 protected:
  TestMovieList() { }
  ~TestMovieList() { }

  virtual void SetUp() {
    movieList.reset(new MovieList());
    starWars.reset(new Movie{"StarWars"});
    starTrek.reset(new Movie{"Star Trek"});
    stargate.reset(new Movie{"Stargate"});
  }

  virtual void TearDown() {
  }

  sp<MovieList> movieList;
  sp<Movie> starWars;
  sp<Movie> starTrek;
  sp<Movie> stargate;
};

TEST_F(TestMovieList, testEmptyListSize) {
  ASSERT_EQ(0, movieList->size()) << "Size of empty movie list should be 0.";
}

TEST_F(TestMovieList, testSizeAfterAddingOne) {
  movieList->add(starWars);
  ASSERT_EQ(1, movieList->size()) << "Size of one item list should be 1.";
}

TEST_F(TestMovieList, testSizeAfterAddingTwo) {
  movieList->add(starWars);
  movieList->add(starTrek);
  ASSERT_EQ(2, movieList->size()) << "Size of a two item list should be 2.";
}

TEST_F(TestMovieList, testContents) {
  movieList->add(starWars);
  movieList->add(starTrek);

  ASSERT_TRUE(movieList->contains(starWars))
    << "List should contain starWars.";
  ASSERT_TRUE(movieList->contains(starTrek))
      << "List should contain starTrek.";
  ASSERT_FALSE(movieList->contains(stargate))
      << "List should not contain stargate.";
}

}  // namespace tests
}  // namespace nowplaying
