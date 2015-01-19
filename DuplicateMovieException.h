// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#ifndef DUPLICATEMOVIEEXCEPTION_H_
#define DUPLICATEMOVIEEXCEPTION_H_

#include <stdexcept>
#include <string>

using std::logic_error;

namespace nowplaying {

class DuplicateMovieException : public logic_error {
 public:
  explicit DuplicateMovieException(const std::string& what)
      : logic_error(what) { }
  explicit DuplicateMovieException(const char *what)
      : logic_error(what) { }
  virtual ~DuplicateMovieException() { }
};

}  // namespace nowplaying

#endif  // DUPLICATEMOVIEEXCEPTION_H_
