// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#ifndef MOVIELISTEDITORVIEW_H_
#define MOVIELISTEDITORVIEW_H_

#include <vector>
#include <string>

namespace nowplaying {
class Movie;
class MovieListEditor;

class MovieListEditorView {
 public:
  virtual void setMovies(const std::vector<sp<Movie>>& movies) = 0;
  virtual const std::string getNameField() = 0;
  virtual void setEditor(MovieListEditor *editor) = 0;
  virtual void setNameField(const std::string& newName) = 0;
  virtual void duplicateException(const std::string& msg) = 0;
  virtual void setRatingField(int rating) = 0;
  virtual int getRatingField() = 0;

  virtual ~MovieListEditorView() {}
};

}  // namespace nowplaying


#endif  // MOVIELISTEDITORVIEW_H_
