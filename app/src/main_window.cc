#include "main_window.h"
#include "opencv2/opencv.hpp"
#include "image_view.h"
#include <QMenuBar>
#include <QToolBar>
#include <QLayout>
#include "manager.h"
#include "feature.h"

MainWindow::MainWindow(QWidget* object)
  : image_view_(new ImageView(this))
  , menu_bar_(new QMenuBar)
  , tool_bar_(new QToolBar)
  , tool_widget_(nullptr)
{
  SetupUi();
  connect(image_source_, &qcv::ImageSource::ChangedEvent, this, &MainWindow::SetBackgroundImage);
}

MainWindow::~MainWindow()
{
}

void MainWindow::SetToolWidget(QWidget* widget)
{
  tool_widget_ = widget;
}

void MainWindow::SetBackgroundImage(cv::Mat& mat)
{
  if (mat.empty())
  {
    return;
  }
  mat_ = mat;
  QImage image;
  if (mat.channels() == 1)
  {
    image = QImage(mat.cols, mat.rows, QImage::Format_Indexed8);
    image.setColorCount(255);
    for (int i = 0; i < 256; i++)
    {
      image.setColor(i, qRgb(i, i, i));
    }
    uchar *pSrc = mat.data;
    for (int row = 0; row < mat.rows; row++)
    {
      uchar *pDest = image.scanLine(row);
      memcpy(pDest, pSrc, mat.cols);
      pSrc += mat.step;
    }
  }
  else if (mat.channels() == 3)
  {
    image = QImage(mat.data, mat.cols, mat.rows, QImage::Format_RGB32);
  }
  else if (mat.channels() == 4)
  {
    image = QImage(mat.data, mat.cols, mat.rows, QImage::Format_ARGB32);
  }
  image_view_->SetBackgroundImage(image.copy());
}

void MainWindow::SetupUi()
{
  image_source_ = qcv::Manager::Instance()->image_source();
  qcv::SetStyleSheet(this, QStringLiteral(":/rc/main_window.qss"));
  QMenu* file_menu = new QMenu(tr("File"));
  QAction* open_file = new QAction(QIcon(":/rc/open-file.png"), tr("Open File"));
  connect(open_file, &QAction::triggered, image_source_, &qcv::ImageSource::Capture);

  QAction* open_capture = new QAction(QIcon(":/rc/capture.png"), tr("Open Capture"));
  QList<QAction*> file_actions;
  file_actions << open_file << open_capture;
  file_menu->addActions(file_actions);
  menu_bar_->addMenu(file_menu);
  tool_bar_->addActions(file_actions);

  QMenu* edit_menu = new QMenu(tr("Edit"));
  QAction* copy = new QAction(QIcon(":/rc/save.png"), tr("Save"));
  connect(copy, &QAction::triggered, image_view_, &ImageView::Save);
  QAction* undo = new QAction(QIcon(":/rc/undo.png"), tr("Undo"));
  QList<QAction*> edit_actions;
  edit_actions << copy << undo;
  edit_menu->addActions(edit_actions);
  menu_bar_->addMenu(edit_menu);
  tool_bar_->addActions(edit_actions);
  tool_bar_->addSeparator();
  QMenu* view_menu = new QMenu(tr("View"));
  QAction* fit = new QAction(QIcon(":/rc/fit.png"), tr("Fit"));
  connect(fit, &QAction::triggered, image_view_, &ImageView::Fit);
  QAction* zoom_in = new QAction(QIcon(":/rc/zoom_in.png"), tr("Zoom in"));
  connect(zoom_in, &QAction::triggered, image_view_, &ImageView::ZoomIn);
  QAction* zoom_out = new QAction(QIcon(":/rc/zoom_out.png"), tr("Zoom out"));
  connect(zoom_out, &QAction::triggered, image_view_, &ImageView::ZoomOut);
  QAction* original = new QAction(QIcon(":/rc/original.png"), tr("Original"));
  connect(original, &QAction::triggered, image_view_, &ImageView::Original);
  QList<QAction*> view_actions;
  view_actions << fit << zoom_in << zoom_out << original;
  view_menu->addActions(view_actions);
  menu_bar_->addMenu(view_menu);
  tool_bar_->addActions(view_actions);
  tool_bar_->addSeparator();

  QMenu* feature_menu = new QMenu(tr("Features"));
  menu_bar_->addMenu(feature_menu);
  foreach(qcv::Feature* feature, qcv::Manager::Instance()->features())
  {
    QAction* action = new QAction(feature->Icon(), feature->Name());
    feature_menu->addAction(action);
    tool_bar_->addAction(action);
    connect(action, &QAction::triggered, [=]
    {
      feature->Process(mat_);
      SetBackgroundImage(mat_);
    });
  }
  setMenuBar(menu_bar_);
  addToolBar(tool_bar_);
  tool_widget_ = qcv::Manager::Instance()->features().first()->ToolWidget();
  QWidget* center_widget = new QWidget;
  QVBoxLayout* center_layout = new QVBoxLayout(center_widget);
  center_layout->addWidget(tool_widget_);
  center_layout->addWidget(image_view_);
  this->setCentralWidget(center_widget);
}
