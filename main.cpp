// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#include "QtMovieListEditorView.h"

#include <QApplication>
#include <QtWidgets>

#include <vector>

#include "./common.h"
#include "./MovieList.h"
#include "./Movie.h"
#include "./MovieListEditor.h"

using nowplaying::MovieList;
using nowplaying::Movie;
using nowplaying::QtMovieListEditorView;
using nowplaying::MovieListEditor;

int main(int argc, char *argv[]) {
  Q_INIT_RESOURCE(images);

  QApplication app(argc, argv);

  sp<MovieList> movieList{new MovieList};

  sp<Movie> starWars{new Movie{"Star Wars", 5}};
  sp<Movie> starTrek{new Movie{"Star Trek", 3}};
  sp<Movie> stargate{new Movie{"Stargate"}};

  movieList->add(starWars);
  movieList->add(starTrek);
  movieList->add(stargate);

  QtMovieListEditorView mainWindow;
  sp<MovieListEditor> editor(new MovieListEditor(movieList, &mainWindow));

  mainWindow.show();

  return app.exec();
}
