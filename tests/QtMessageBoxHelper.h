// Copyright (c) 2015
// All rights reserved.
//
// Author: Lutts Cao <<lutts.cao@gmail.com>>
//
// [Desc]

#ifndef TESTS_QTMESSAGEBOXHELPER_H_
#define TESTS_QTMESSAGEBOXHELPER_H_

#include <QObject>
#include <QString>
#include <QTimer>

namespace nowplaying {
namespace tests {

class QtMessageBoxHelper : public QObject {
  Q_OBJECT

 public:
  QtMessageBoxHelper();
  QString message() { return _message; }

 private slots:
  void recordInfo();

 private:
  QString _message;

  QTimer dialogCheckTimer;
};

}  // namespace tests
}  // namespace nowplaying

#endif  // TESTS_QTMESSAGEBOXHELPER_H_
