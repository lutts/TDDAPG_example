//-*- TestCaseName: TestQtMovieListEditorView;-*-
// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#include "QtMovieListEditorView.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QtWidgets>
#include <QtTest/QtTest>

#include <vector>
#include <string>
#include <initializer_list>

#include "./testconfig.h"
#include "./common.h"
#include "./MovieList.h"
#include "./Movie.h"
#include "./Movie_test_helper.h"
#include "./MovieListEditor.h"

#include "./QtMessageBoxHelper.h"

Q_DECLARE_METATYPE(sp<nowplaying::Movie>)

namespace nowplaying {


namespace tests {

class TestQtMovieListEditorView : public QObject {
  Q_OBJECT

 private slots:
  void initTestCase() { }
  void cleanupTestCase() { }

  void init() {
    movieList.reset(new MovieList);

    starWars.reset(new Movie{"Star Wars", 5});
    starTrek.reset(new Movie{"Star Trek", 3});
    stargate.reset(new Movie{"Stargate", -1});

    movies.clear();
    movies.push_back(starWars);
    movies.push_back(starTrek);
    movies.push_back(stargate);

    movieList->add(starWars);
    movieList->add(starTrek);
    movieList->add(stargate);

    mainWindow = new QtMovieListEditorView;

    editor.reset(new MovieListEditor(movieList, mainWindow));

    mainWindow->show();
  }

  void cleanup() {
    delete mainWindow;
  }

  void testListContents();
  void testAdding();
  void testSingleSelectMode();
  void testSelecting();
  void testUpdating();
  void testDuplicateCausingAdd();
  void testDuplicateCausingUpdate();
  void testSelectUpdatesRating();
  void testUpdateRating();


 private:
  void clickListItem(int idx);
  void clickListItem(std::initializer_list<int> idxs);

  void clickButton(QString objectName);
  void clickAddButton();
  void clickUpdateButton();

  QLineEdit *getNameField();

  void checkListIsUnchanged();


 private:
  std::vector<sp<Movie>> movies;
  sp<MovieList> movieList;

  sp<Movie> starWars;
  sp<Movie> starTrek;
  sp<Movie> stargate;

  QtMovieListEditorView* mainWindow;
  sp<MovieListEditor> editor;
};

void TestQtMovieListEditorView::testAdding() {
  const std::string LOST_IN_SPACE { "Lost In Space" };
  sp<Movie> lostInSpace { new Movie(LOST_IN_SPACE) };
  movies.push_back(lostInSpace);

  getNameField()->setText(QString::fromStdString(LOST_IN_SPACE));

  clickAddButton();
  checkListIsUnchanged();
}

void TestQtMovieListEditorView::testSingleSelectMode() {
  QListWidget* listWidget =
      mainWindow->findChild<QListWidget*>(QString("listwidget"));

  clickListItem({0, 1});

  QList<QListWidgetItem *> items = listWidget->selectedItems();
  ASSERT_EQ(1, items.size());
}

void TestQtMovieListEditorView::testSelecting() {
  QListWidget* listWidget =
      mainWindow->findChild<QListWidget*>(QString("listwidget"));

  clickListItem(1);

  ASSERT_EQ("Star Trek", getNameField()->text().toStdString());
}

void TestQtMovieListEditorView::testUpdating() {
  QListWidget* listWidget =
      mainWindow->findChild<QListWidget*>(QString("listwidget"));

  clickListItem(1);

  getNameField()->setText(QString("Star Trek I"));

  clickUpdateButton();

  clickListItem({0, 1});

  ASSERT_EQ("Star Trek I", getNameField()->text().toStdString());
}

void TestQtMovieListEditorView::testDuplicateCausingAdd() {
  getNameField()->setText(QString::fromStdString(starWars->name()));

  QtMessageBoxHelper helper;
  clickAddButton();

  ASSERT_EQ("That would result in a duplicate Movie.",
            helper.message().toStdString());

  checkListIsUnchanged();
}

void TestQtMovieListEditorView::testDuplicateCausingUpdate() {
  QListWidget* listWidget =
      mainWindow->findChild<QListWidget*>(QString("listwidget"));

  clickListItem(1);

  getNameField()->setText(QString::fromStdString(starWars->name()));

  QtMessageBoxHelper helper;
  clickUpdateButton();

  ASSERT_EQ("That would result in a duplicate Movie.",
            helper.message().toStdString());

  checkListIsUnchanged();
}

void TestQtMovieListEditorView::testSelectUpdatesRating() {
  QComboBox* ratingCombo =
      mainWindow->findChild<QComboBox *>(QString("rating"));

  ASSERT_NE(nullptr, ratingCombo) << "Rating Combo not found";

  clickListItem(0);
  ASSERT_EQ(6, ratingCombo->currentIndex())
      << "wrong rating from selecting starWars.";

  clickListItem(1);
  ASSERT_EQ(4, ratingCombo->currentIndex())
      << "wrong rating from selecting starTrek.";

  clickListItem(2);
  ASSERT_EQ(0, ratingCombo->currentIndex())
      << "wrong rating from selecting stargate.";
}

void TestQtMovieListEditorView::testUpdateRating() {
  QComboBox* ratingCombo =
      mainWindow->findChild<QComboBox *>(QString("rating"));

  clickListItem(0);
  ratingCombo->setCurrentIndex(4);

  clickUpdateButton();

  clickListItem({1, 0});
  ASSERT_EQ(4, ratingCombo->currentIndex())
      << "updating should have changed rating.";
}



void TestQtMovieListEditorView::clickListItem(int idx) {
  clickListItem({idx});
}

void TestQtMovieListEditorView::clickListItem(std::initializer_list<int> idxs) {
  QListWidget* listWidget =
      mainWindow->findChild<QListWidget*>(QString("listwidget"));

  for (auto idx : idxs) {
    QListWidgetItem* item = listWidget->item(idx);
    QRect rect = listWidget->visualItemRect(item);
    QTest::mouseClick(listWidget->viewport(), Qt::LeftButton, 0, rect.center());
  }
}

void TestQtMovieListEditorView::clickButton(QString objectName) {
  QPushButton *button = mainWindow->findChild<QPushButton *>(objectName);
  QTest::mouseClick(button, Qt::LeftButton);
}

void TestQtMovieListEditorView::clickAddButton() {
  clickButton(QString("add"));
}

void TestQtMovieListEditorView::clickUpdateButton() {
  clickButton(QString("update"));
}

QLineEdit* TestQtMovieListEditorView::getNameField() {
  return mainWindow->findChild<QLineEdit *>(QString("name"));
}

void TestQtMovieListEditorView::testListContents() {
  QListWidget* listWidget =
      mainWindow->findChild<QListWidget*>(QString("listwidget"));

  ASSERT_EQ(movies.size(), listWidget->count())
      << "Movie list is the wrong size";

  for (int i = 0; i < movies.size(); i++) {
    QListWidgetItem* item = listWidget->item(i);
    QVariant var = item->data(Qt::UserRole);
    sp<Movie> movie = var.value<sp<Movie>>();

    ASSERT_EQ(movies.at(i), movie)
        << "Movie list contains bad movie at index " << i;
  }
}

void TestQtMovieListEditorView::checkListIsUnchanged() {
  QListWidget* listWidget =
      mainWindow->findChild<QListWidget*>(QString("listwidget"));

  ASSERT_EQ(movies.size(), listWidget->count())
      << "Movie list is the wrong size";

  for (int i = 0; i < movies.size(); i++) {
    QListWidgetItem* item = listWidget->item(i);
    QVariant var = item->data(Qt::UserRole);
    sp<Movie> movie = var.value<sp<Movie>>();

    ASSERT_EQ(movies.at(i)->name(), item->text().toStdString())
        << "Movie list contains bad movie name at index " << i;
    ASSERT_EQ(*movies.at(i), *movie)
        << "Movie list contains bad movie at index " << i;
  }
}

#include "moc_TestQtMovieListEditorView.cpp"

}  // namespace tests
}  // namespace nowplaying

QTEST_GMOCK_MAIN(::nowplaying::tests::TestQtMovieListEditorView)
