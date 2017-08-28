#ifndef __APP_MAIN_WINDOW_H__
#define __APP_MAIN_WINDOW_H__

#include <QMainWindow>
class ImageView;
class QMenuBar;
class QToolBar;

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget* object = nullptr);
  ~MainWindow();

  void SetToolWidget(QWidget* widget);
private:
  void SetupUi();
  ImageView* image_view_;
  QMenuBar* menu_bar_;
  QToolBar* tool_bar_;
  QWidget* tool_widget_;
};

#endif //!__APP_MAIN_WINDOW_H__