// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#ifndef MOVIE_H_
#define MOVIE_H_

#include <string>
#include <stdexcept>

#include "./UnratedException.h"

namespace nowplaying {

class Movie {
 public:
  explicit Movie(const std::string &name, int rating = -1) : _name(name)  {
    checkEmpty(_name);
    _rating = rating;
    // std::cout << "create Movie " << name << std::endl;
  }

  virtual ~Movie() {
    // std::cout << "destroy Movie" << _name << std::endl;
  }

  bool operator==(const Movie &other) const {
    return _name == other._name;
  }

  const std::string& name() { return _name; }

  void rename(const std::string& newName) {
    checkEmpty(newName);
    _name = newName;
  }

  bool hasRating() { return _rating > -1; }

  int getRating() {
    if (hasRating()) {
      return _rating;
    } else {
      throw UnratedException(_name);
    }
  }

  void setRating(int newRating) {
    _rating = newRating;
  }

 private:
  void checkEmpty(const std::string& newName) {
    if (newName.length() == 0)
      throw std::invalid_argument("Movie name can't be empty.");
  }

 private:
  std::string _name;
  int _rating;
};

}  // namespace nowplaying

#endif  // MOVIE_H_
