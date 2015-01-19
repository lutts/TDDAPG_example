//-*- TestCaseName: TestMovie;-*-
// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

#include "./common.h"
#include "./Movie.h"
#include "./UnratedException.h"

namespace nowplaying {

class TestMovie : public ::testing::Test {
 protected:
  TestMovie() { }
  ~TestMovie() { }
  virtual void SetUp() {
    starWars.reset(new Movie{"Star Wars"});
  }
  virtual void TearDown() { }

  sp<Movie> starWars;
};

TEST_F(TestMovie, testMovieName) {
  ASSERT_EQ("Star Wars", starWars->name());
}

TEST_F(TestMovie, testRenaming) {
  std::string newName { "Star Trek" };
  starWars->rename(newName);
  ASSERT_EQ(newName, starWars->name());
}

TEST_F(TestMovie, testNullName) {
  try {
    new Movie(nullptr);
    FAIL() << "null name should have thrown IllegalArgumentException.";
  } catch (std::exception& e) {
  }
}

TEST_F(TestMovie, testEmptyName) {
  try {
    new Movie("");
    FAIL() << "empty name should have thrown IllegalArgumentException.";
  } catch (std::invalid_argument& e) {
  }
}

TEST_F(TestMovie, testNullRename) {
  try {
    starWars->rename(nullptr);
    FAIL() << "null rename should have thrown IllegalArgumentException.";
  } catch (std::exception& e) {
  }
}

TEST_F(TestMovie, testEmptyRename) {
  try {
    starWars->rename("");
    FAIL() << "empty rename should have thrown IllegalArgumentException.";
  } catch (std::invalid_argument& e) {
  }
}

TEST_F(TestMovie, testUnRated) {
  ASSERT_FALSE(starWars->hasRating())
      << "starWars should be unrated.";
}

TEST_F(TestMovie, testRatedMovie) {
  sp<Movie> fotr {new Movie{"Fellowship of the Ring", 5}};
  ASSERT_TRUE(fotr->hasRating()) << "fotr should be rated.";
  ASSERT_EQ(5, fotr->getRating()) << "fotr should be rated at 5.";
}

TEST_F(TestMovie, testUnratedException) {
  try {
    starWars->getRating();
    FAIL() << "getRating() of an unrated Movie should throw UnratedException.";
  } catch (const UnratedException& e) {
    ASSERT_EQ(starWars->name(), e.what())
        << "UnratedException should identify the movie.";
  }
}

}  // namespace nowplaying
