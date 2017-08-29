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
  connect(image_source_, &qcv::ImageSource::ChangedEvent, [=](void* im, QImage::Format f)
  {
    qcv::ImageBuffer* image_buffer = static_cast<qcv::ImageBuffer*>(im);
    QImage image(image_buffer->buffer,image_buffer->width, image_buffer->height, f);
    image_view_->SetBackgroundImage(image);
  });
}

MainWindow::~MainWindow()
{
}

void MainWindow::SetToolWidget(QWidget* widget)
{
  tool_widget_ = widget;
}

void MainWindow::SetupUi()
{
  image_source_ = qcv::Manager::Instance()->image_source();
  qcv::SetStyleSheet(this, QStringLiteral(":/rc/main_window.qss"));
  QMenu* file_menu = new QMenu(tr("File"));
  QAction* open_file = new QAction(QIcon(":/rc/open-file.png"), tr("Open File"));
  file_menu->addAction(open_file);
  connect(open_file, &QAction::triggered, image_source_, &qcv::ImageSource::Capture);

  QAction* open_capture = new QAction(QIcon(":/rc/capture.png"), tr("Open Capture"));
  file_menu->addAction(open_capture);
  menu_bar_->addMenu(file_menu);

  QMenu* edit_menu = new QMenu(tr("Edit"));
  QAction* copy = new QAction(QIcon(":/rc/save.png"), tr("Save"));
  QAction* undo = new QAction(QIcon(":/rc/undo.png"), tr("Undo"));
  QList<QAction*> edit_actions;
  edit_actions << copy << undo;
  edit_menu->addActions(edit_actions);
  menu_bar_->addMenu(edit_menu);
  tool_bar_->addActions(edit_actions);
  tool_bar_->addSeparator();
  QMenu* view_menu = new QMenu(tr("View"));
  QAction* fit = new QAction(QIcon(":/rc/fit.png"), tr("Fit"));
  QAction* zoom_in = new QAction(QIcon(":/rc/zoom_in.png"), tr("Zoom in"));
  QAction* zoom_out = new QAction(QIcon(":/rc/zoom_out.png"), tr("Zoom out"));
  QAction* original = new QAction(QIcon(":/rc/original.png"), tr("Original"));
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
      unsigned char* data = new unsigned char[image_.width() * image_.height()];
      for (int i = 0; i < image_.width(); ++i)
      {
#pragma omp for
        for (int j = 0; j < image_.height(); ++j)
        {
          unsigned short v = qGray(image_.pixel(i, j));
          v = v << 4;
          *data++ = v;
        }
      }
      feature->Process(data, image_.size());
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