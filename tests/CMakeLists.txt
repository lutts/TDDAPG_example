include(xTestUtil)

INIT_QGTEST()

SET(CMAKE_AUTOMOC OFF)

SET(qt_RCS_ images)

foreach(rcs ${qt_RCS_})
SET(qt_RCS "${qt_RCS}Q_INIT_RESOURCE(${rcs});")
endforeach(rcs)

configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

add_gmock_test(TestMovieList  TestMovieList.cpp
  AUTORUN)

add_gmock_test(TestMovieListEditor TestMovieListEditor.cpp AUTORUN)

add_qg_test(TestQtMovieListEditorView
  SRCS QtMessageBoxHelper.cpp
  MOCS TestQtMovieListEditorView.cpp QtMessageBoxHelper.h
  LIBS Qt5::Widgets nowplaying
  AUTORUN)

add_gmock_test(TestMovie TestMovie.cpp AUTORUN)

add_gmock_test(TestMovieListWithPopulatedList
  TestMovieListWithPopulatedList.cpp
  AUTORUN)
