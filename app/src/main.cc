#include <QApplication>
#include "main_window.h"
#include "manager.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  if (!qcv::Manager::Instance()->LoadPlugins())
  {
    return -1;
  }

  MainWindow main_window;
  main_window.show();
  return app.exec();
}