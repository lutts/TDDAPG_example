// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#ifndef MOCK_MOVIELISTEDITORVIEW_H_
#define MOCK_MOVIELISTEDITORVIEW_H_

#include "MovieListEditorView.h"

#include <vector>
#include <string>

namespace nowplaying {
namespace tests {

class MockMovieListEditorView : public MovieListEditorView {
 public:
  MOCK_METHOD1(setMovies, void(const std::vector<sp<Movie>>& movies));
  MOCK_METHOD0(getNameField, const std::string());
  MOCK_METHOD1(setEditor, void(MovieListEditor *editor));
  MOCK_METHOD1(setNameField, void(const std::string& newName));
  MOCK_METHOD1(duplicateException, void(const std::string& msg));
  MOCK_METHOD1(setRatingField, void(int rating));
  MOCK_METHOD0(getRatingField, int());
};

}  // namespace tests
}  // namespace nowplaying

#endif  // MOCK_MOVIELISTEDITORVIEW_H_
