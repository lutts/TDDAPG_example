// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#ifndef MOVIELISTEDITOR_H_
#define MOVIELISTEDITOR_H_

#include <string>

#include "./MovieList.h"
#include "./MovieListEditorView.h"
#include "./DuplicateMovieException.h"

namespace nowplaying {

class MovieListEditor {
 public:
  MovieListEditor(const sp<MovieList>& movieList, MovieListEditorView* view) {
    _movies = movieList;
    _view = view;
    _view->setMovies(movieList->getMovies());
    _view->setEditor(this);
  }
  virtual ~MovieListEditor() { }

  void add() {
    sp<Movie> newMovie { new Movie(_view->getNameField(),
                                   _view->getRatingField())};
    try {
      _movies->add(newMovie);
      updateMovieList();
    } catch (const DuplicateMovieException& e) {
      _view->duplicateException(e.what());
    }
  }

  void select(int idx) {
    if (idx == -1) {
      selectedMovie.reset();
    } else {
      selectedMovie = _movies->getMovie(idx);
      _view->setNameField(selectedMovie->name());

      try {
        _view->setRatingField(selectedMovie->getRating() + 1);
      } catch (const UnratedException& e) {
        _view->setRatingField(0);
      }
    }
  }

  void update() {
    if (selectedMovie.get() != nullptr) {
      const std::string newName = _view->getNameField();

      if (newName == selectedMovie->name()) {
        updateMovie();
      } else {
        try {
          _movies->rename(selectedMovie, newName);
          updateMovie();
        } catch (const DuplicateMovieException& e) {
          _view->duplicateException(e.what());
        }
      }
    }
  }

 private:
  void updateMovie() {
    selectedMovie->setRating(_view->getRatingField());
    updateMovieList();
  }

  void updateMovieList() {
    _view->setMovies(_movies->getMovies());
  }

 private:
  MovieListEditorView* _view;
  sp<MovieList> _movies;

  sp<Movie> selectedMovie;
};

}  // namespace nowplaying


#endif  // MOVIELISTEDITOR_H_
