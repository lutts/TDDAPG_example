// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#include "QtMovieRating.h"

namespace nowplaying {

const QIcon& iconForRating(int rating) {
  return rating_icons().at(rating);
}

const std::array<QIcon, MAX_ICONS>& rating_icons() {
  static std::array<QIcon, 7> movie_rating_icons = {
    QIcon(":images/no-rating.gif"),
    QIcon(":images/zero-stars.gif"),
    QIcon(":images/one-star.gif"),
    QIcon(":images/two-stars.gif"),
    QIcon(":images/three-stars.gif"),
    QIcon(":images/four-stars.gif"),
    QIcon(":images/five-stars.gif")
  };

  return movie_rating_icons;
}

}  // namespace nowplaying
