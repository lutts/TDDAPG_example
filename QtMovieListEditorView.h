// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#ifndef QTMOVIELISTEDITORVIEW_H_
#define QTMOVIELISTEDITORVIEW_H_

#include <QDialog>
#include <QLineEdit>

#include <vector>
#include <string>

#include "./common.h"
#include "./MovieListEditorView.h"


class QListWidget;
class QPushButton;
class QComboBox;

namespace nowplaying {

class MovieListEditor;

class QtMovieListEditorView : public QDialog, public MovieListEditorView {
  Q_OBJECT

 public:
  QtMovieListEditorView(QWidget *parent = 0); // NOLINT
  virtual ~QtMovieListEditorView() { }

  void setMovies(const std::vector<sp<Movie>>& movies) override;

  const std::string getNameField() override {
    return nameField->text().toStdString();
  }

  void setEditor(MovieListEditor *editor) override { _editor = editor; }

  void setNameField(const std::string& newName) override;

  void setRatingField(int rating) override;
  int getRatingField();

  void duplicateException(const std::string& msg) override;

 private:
  QListWidget *listWidget;
  QLineEdit *nameField;
  QPushButton *addButton;
  QPushButton *updateButton;
  QComboBox *ratingCombo;

  MovieListEditor *_editor;
};

}  // namespace nowplaying

#endif  // QTMOVIELISTEDITORVIEW_H_
