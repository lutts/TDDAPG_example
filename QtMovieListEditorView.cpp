// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#include "QtMovieListEditorView.h"

#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QComboBox>

#include <vector>
#include <string>

#include "./common.h"
#include "./Movie.h"
#include "./MovieListEditor.h"
#include "./QtMovieRating.h"

Q_DECLARE_METATYPE(sp<nowplaying::Movie>)

namespace nowplaying {

QtMovieListEditorView::QtMovieListEditorView(QWidget *parent) {
  listWidget = new QListWidget;
  listWidget->setObjectName(QString("listwidget"));

  connect(listWidget, &QListWidget::itemClicked,
          [this](QListWidgetItem * item) {
            _editor->select(listWidget->row(item));
          });

  nameField = new QLineEdit;
  nameField->setObjectName(QString("name"));

  ratingCombo = new QComboBox;
  ratingCombo->setObjectName(QString("rating"));
  for (const auto& icon : rating_icons()) {
    ratingCombo->addItem(icon, QString(""));
  }

  addButton = new QPushButton(tr("Add"));
  addButton->setObjectName(QString("add"));
  connect(addButton, &QPushButton::clicked,
          [this]() {
            _editor->add();
          });

  updateButton = new QPushButton(tr("Update"));
  updateButton->setObjectName(QString("update"));
  connect(updateButton, &QPushButton::clicked,
          [this]() {
            _editor->update();
          });

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(listWidget);
  layout->addWidget(nameField);
  layout->addWidget(ratingCombo);
  layout->addWidget(addButton);
  layout->addWidget(updateButton);

  setLayout(layout);

  setWindowTitle(tr("Movie List"));

  QIcon *icon = new QIcon(":images/three-stars.gif");

#if 0
  std::cout << "available sizes: " << std::endl;
  for (auto size : icon->availableSizes()) {
    std::cout << size.width() << "x" << size.height() << std::endl;
  }
#endif

  QSize iconSize = icon->availableSizes()[0];

  delete icon;

  listWidget->setIconSize(iconSize);
  ratingCombo->setIconSize(iconSize);
}

void QtMovieListEditorView::setMovies(const std::vector<sp<Movie>>& movies) {
  listWidget->clear();
  for (const sp<Movie> movie : movies) {
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(QString::fromStdString(movie->name()));
    newItem->setData(Qt::UserRole, QVariant::fromValue(movie));

    if (movie->hasRating()) {
      newItem->setIcon(iconForRating(movie->getRating() + 1));
    } else {
      newItem->setIcon(iconForRating(0));
    }
    listWidget->addItem(newItem);
  }
}

void QtMovieListEditorView::setNameField(const std::string& newName) {
  nameField->setText(QString::fromStdString(newName));
}

void QtMovieListEditorView::duplicateException(const std::string& msg) {
  QMessageBox::warning(this, tr("Duplicate Movie"),
                       tr("That would result in a duplicate Movie."));
}

void QtMovieListEditorView::setRatingField(int rating) {
  ratingCombo->setCurrentIndex(rating);
}

int QtMovieListEditorView::getRatingField() {
  return ratingCombo->currentIndex() - 1;
}

}  // namespace nowplaying
