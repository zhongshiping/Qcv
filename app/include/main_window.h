#ifndef __APP_MAIN_WINDOW_H__
#define __APP_MAIN_WINDOW_H__

#include <QMainWindow>
#include "image_source.h"
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
public slots:
  void SetBackgroundImage(cv::Mat& mat);
private:
  void SetupUi();

  ImageView* image_view_;
  QMenuBar* menu_bar_;
  QToolBar* tool_bar_;
  QWidget* tool_widget_;

  QString image_path_;
  qcv::ImageSource* image_source_;
  cv::Mat mat_;
};

#endif //!__APP_MAIN_WINDOW_H__