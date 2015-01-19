//-*- TestCaseName: TestMovieListEditor;-*-
// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>
#include <string>

#include "./common.h"
#include "./MovieList.h"
#include "./Movie.h"
#include "./Movie_test_helper.h"
#include "./mock_MovieListEditorView.h"
#include "./MovieListEditor.h"

using ::testing::Return;
using ::testing::Pointwise;
using ::testing::InSequence;

namespace nowplaying {
namespace tests {

class TestMovieListEditor : public ::testing::Test {
 protected:
  TestMovieListEditor() { }
  ~TestMovieListEditor() { }

  virtual void SetUp() {
    movieList.reset(new MovieList);

    starWars.reset(new Movie{"Star Wars", 5});
    starTrek.reset(new Movie{"Star Trek", 3});
    stargate.reset(new Movie{"Stargate"});

    movies.push_back(starWars);
    movies.push_back(starTrek);
    movies.push_back(stargate);

    movieList->add(starWars);
    movieList->add(starTrek);
    movieList->add(stargate);
  }

  virtual void TearDown() { }

  std::vector<sp<Movie>> movies;
  sp<MovieList> movieList;

  sp<Movie> starWars;
  sp<Movie> starTrek;
  sp<Movie> stargate;

  MockMovieListEditorView mockView;
};

TEST_F(TestMovieListEditor, testList) {
  EXPECT_CALL(mockView, setMovies(::testing::Eq(movies)));

  MovieListEditor editor(movieList, &mockView);
}

TEST_F(TestMovieListEditor, testAdding) {
  const std::string LOST_IN_SPACE { "Lost In Space" };
  sp<Movie> lostInSpace { new Movie(LOST_IN_SPACE) };

  std::vector<sp<Movie>> moviesWithAddition { movies };
  moviesWithAddition.push_back(lostInSpace);

  EXPECT_CALL(mockView, setMovies(Pointwise(MovieEq(), movies)));
  EXPECT_CALL(mockView, getNameField())
      .WillOnce(Return(LOST_IN_SPACE));
  EXPECT_CALL(mockView, getRatingField())
      .WillOnce(Return(-1));
  EXPECT_CALL(mockView,
              setMovies(Pointwise(MovieEq(), moviesWithAddition)));

  MovieListEditor editor{movieList, &mockView};
  editor.add();
}

TEST_F(TestMovieListEditor, testSelecting) {
  EXPECT_CALL(mockView, setMovies(Pointwise(MovieEq(), movies)));

  EXPECT_CALL(mockView, setNameField("Star Wars"));
  EXPECT_CALL(mockView, setRatingField(6));

  EXPECT_CALL(mockView, setNameField("Star Trek"));
  EXPECT_CALL(mockView, setRatingField(4));

  EXPECT_CALL(mockView, setNameField("Stargate"));
  EXPECT_CALL(mockView, setRatingField(0));

  MovieListEditor editor{movieList, &mockView};
  editor.select(0);
  editor.select(1);
  editor.select(2);
}

TEST_F(TestMovieListEditor, testUpdating) {
  std::vector<sp<Movie>> newMovies;
  newMovies.push_back(starWars);
  newMovies.push_back(sp<Movie>(new Movie("Star Trek I", 5)));
  newMovies.push_back(stargate);

  EXPECT_CALL(mockView, setMovies(Pointwise(MovieEq(), movies)));

  EXPECT_CALL(mockView, setNameField("Star Trek"));
  EXPECT_CALL(mockView, setRatingField(4));

  EXPECT_CALL(mockView, getNameField())
      .WillOnce(Return(std::string("Star Trek I")));
  EXPECT_CALL(mockView, getRatingField())
      .WillOnce(Return(6));

  EXPECT_CALL(mockView, setMovies(Pointwise(MovieEq(), newMovies)));

  MovieListEditor editor{movieList, &mockView};
  editor.select(1);
  editor.update();
}

TEST_F(TestMovieListEditor, testDuplicateCausingAdd) {
  EXPECT_CALL(mockView, setMovies(Pointwise(MovieEq(), movies)));
  EXPECT_CALL(mockView, getNameField())
      .WillOnce(Return("Star Wars"));
  EXPECT_CALL(mockView, duplicateException("Star Wars"));

  MovieListEditor editor{movieList, &mockView};
  editor.add();
}

TEST_F(TestMovieListEditor, testDuplicateCausingUpdate) {
  EXPECT_CALL(mockView, setMovies(Pointwise(MovieEq(), movies)));
  EXPECT_CALL(mockView, setNameField("Star Trek"));
  EXPECT_CALL(mockView, getNameField())
      .WillOnce(Return("Star Wars"));
  EXPECT_CALL(mockView, duplicateException("Star Wars"));

  MovieListEditor editor{movieList, &mockView};
  editor.select(1);
  editor.update();
}

TEST_F(TestMovieListEditor, testUpdatingWithSameName) {
  std::vector<sp<Movie>> newMovies;
  newMovies.push_back(starWars);
  newMovies.push_back(sp<Movie>{new Movie{"Star Trek", 5}});
  newMovies.push_back(stargate);

  {
    InSequence dummy;

    EXPECT_CALL(mockView, setMovies(Pointwise(MovieEq(), movies)));
    EXPECT_CALL(mockView, setNameField("Star Trek"));
    EXPECT_CALL(mockView, setRatingField(4));

    EXPECT_CALL(mockView, getNameField())
        .WillOnce(Return("Star Trek"));
    EXPECT_CALL(mockView, getRatingField())
        .WillOnce(Return(6));

    EXPECT_CALL(mockView, setMovies(Pointwise(MovieEq(), newMovies)));
  }

  MovieListEditor editor{movieList, &mockView};
  editor.select(1);
  editor.update();
}


}  // namespace tests
}  // namespace nowplaying
