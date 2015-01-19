// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#include "QtMessageBoxHelper.h"

#include <QApplication>
#include <QtWidgets>
#include <QtTest/QtTest>
#include <QMessageBox>
#include <QTimer>

namespace nowplaying {
namespace tests {

QtMessageBoxHelper::QtMessageBoxHelper() {
  // QTimer::singleShot(2000, this, SLOT(recordInfo()));

  dialogCheckTimer.setInterval(500);
  dialogCheckTimer.setSingleShot(true);
  connect(&dialogCheckTimer, SIGNAL(timeout()), this, SLOT(recordInfo()));

  dialogCheckTimer.start();
}

void QtMessageBoxHelper::recordInfo() {
  bool found = false;

  QWidgetList topWidgets = QApplication::topLevelWidgets();
  for (QWidget *w : topWidgets) {
    if (QMessageBox *mb = qobject_cast<QMessageBox *>(w)) {
      found = true;
      _message = mb->text();
      QTest::keyClick(mb, Qt::Key_Enter);
    }
  }

  if (!found) {
    dialogCheckTimer.start();
  }
}

#include "moc_QtMessageBoxHelper.cpp"

}  // namespace tests
}  // namespace nowplaying
