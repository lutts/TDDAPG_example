// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#ifndef MOVIELIST_H_
#define MOVIELIST_H_

#include "Movie.h"

#include <vector>
#include <string>
#include <algorithm>

#include "./common.h"
#include "./DuplicateMovieException.h"

namespace nowplaying {

class MovieList {
 public:
  MovieList() { }
  virtual ~MovieList() { }

  int size() { return movies.size(); }

  void add(const sp<Movie>& movie) {
    if (this->contains(movie)) {
      throw DuplicateMovieException{movie->name()};
    }
    movies.push_back(movie);
  }

  bool contains(const sp<Movie>& movie) {
    return containsName(movie->name());
  }

  const std::vector<sp<Movie>>& getMovies() {
    return movies;
  }

  const sp<Movie>& getMovie(int idx) {
    return movies.at(idx);
  }

  void rename(const sp<Movie>& movie, const std::string& newName) {
    if (containsName(newName)) {
      throw DuplicateMovieException{newName};
    }

    movie->rename(newName);
  }

 private:
  bool containsName(const std::string& name) {
    std::vector<sp<Movie>>::const_iterator it =
        std::find_if(movies.cbegin(), movies.cend(),
                     [&name](const sp<Movie>& other) {
                       return name == other->name();
                     });
    return it != movies.cend();
  }

 private:
  std::vector<sp<Movie>> movies;

  MovieList(const MovieList& other) = delete;
};

}  // namespace nowplaying


#endif  // MOVIELIST_H_
