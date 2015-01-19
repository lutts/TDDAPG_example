// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#ifndef QTMOVIERATING_H_
#define QTMOVIERATING_H_

#include <QIcon>

#include <array>

namespace nowplaying {

constexpr int MAX_ICONS = 7;

extern const QIcon& iconForRating(int rating);
extern const std::array<QIcon, MAX_ICONS>& rating_icons();

}  // namespace nowplaying

#endif  // QTMOVIERATING_H_
