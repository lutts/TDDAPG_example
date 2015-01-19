//-*- TestCaseName: TestMovieListWithPopulatedList;-*-
// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "./DuplicateMovieException.h"
#include "./Movie.h"
#include "./MovieList.h"

namespace nowplaying {
namespace tests {

class TestMovieListWithPopulatedList : public ::testing::Test {
 protected:
  TestMovieListWithPopulatedList() { }
  ~TestMovieListWithPopulatedList() { }

  virtual void SetUp() {
    movieList.reset(new MovieList);

    starWars.reset(new Movie{"Star Wars"});
    starTrek.reset(new Movie{"Star Trek"});
    stargate.reset(new Movie{"Stargate"});

    movieList->add(starWars);
    movieList->add(starTrek);
    movieList->add(stargate);
  }

  virtual void TearDown() { }

  sp<MovieList> movieList;

  sp<Movie> starWars;
  sp<Movie> starTrek;
  sp<Movie> stargate;
};

TEST_F(TestMovieListWithPopulatedList, testAddingDuplicate) {
  auto duplicate = std::make_shared<Movie>(starTrek->name());

  try {
    movieList->add(duplicate);
    FAIL() << "Adding duplicate Movie should throw DuplicateMovieException";
  } catch (const DuplicateMovieException& e) {
    ASSERT_EQ(3, movieList->size())
        << "Failed add of duplicate shouldn't chage the list size.";
  }
}

TEST_F(TestMovieListWithPopulatedList, testRenaming) {
  const std::string newName{ "StarTrek I" };
  movieList->rename(starTrek, newName);
  ASSERT_EQ(newName, starTrek->name());
}

TEST_F(TestMovieListWithPopulatedList, testRenamingDuplicate) {
  try {
    movieList->rename(starTrek, "Star Wars");
    FAIL() << "Renaming to a duplicate should throw DuplicateMovieException";
  } catch (const DuplicateMovieException& e) {
    ASSERT_EQ(3, movieList->size())
        << "Failed rename shouldn't change list size.";

    ASSERT_EQ("Star Trek", starTrek->name())
        << "Failed rename shouldn't change the name.";
  }
}

}  // namespace tests
}  // namespace nowplaying
