// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#ifndef UNRATEDEXCEPTION_H_
#define UNRATEDEXCEPTION_H_

#include <stdexcept>
#include <string>

using std::logic_error;

namespace nowplaying {

class UnratedException : public logic_error {
 public:
  explicit UnratedException(const std::string& what)
      : logic_error(what) { }
  explicit UnratedException(const char *what)
      : logic_error(what) { }
  virtual ~UnratedException() { }
};

}  // namespace nowplaying

#endif  // UNRATEDEXCEPTION_H_
