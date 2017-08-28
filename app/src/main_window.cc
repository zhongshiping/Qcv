#include "main_window.h"
#include "opencv2/opencv.hpp"
#include "image_view.h"
#include <QMenuBar>
#include <QToolBar>
#include <QLayout>
#include "manager.h"
#include "feature.h"

MainWindow::MainWindow(QWidget* object)
  : image_view_(new ImageView)
  , menu_bar_(new QMenuBar)
  , tool_bar_(new QToolBar)
  , tool_widget_(nullptr)
{
  SetupUi();
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
  QMenu* file_menu = new QMenu(tr("File"));
  QAction* open_file = new QAction(tr("Open File"));
  file_menu->addAction(open_file);
  QAction* open_capture = new QAction(tr("Open Capture"));
  file_menu->addAction(open_capture);
  menu_bar_->addMenu(file_menu);

  QMenu* edit_menu = new QMenu(tr("Edit"));
  QAction* copy = new QAction(tr("Copy"));
  QAction* undo = new QAction(tr("Undo"));
  edit_menu->addAction(copy);
  edit_menu->addAction(undo);
  menu_bar_->addMenu(edit_menu);

  QMenu* view_menu = new QMenu(tr("View"));
  QAction* fit = new QAction(tr("Fit"));
  QAction* zoom_in = new QAction(tr("Zoom in"));
  QAction* zoom_out = new QAction(tr("Zoom out"));
  QAction* original = new QAction(tr("Original"));
  view_menu->addAction(fit);
  view_menu->addAction(zoom_in);
  view_menu->addAction(zoom_out);
  view_menu->addAction(original);
  menu_bar_->addMenu(view_menu);

  QMenu* feature_menu = new QMenu(tr("Features"));
  menu_bar_->addMenu(feature_menu);
  foreach(qcv::Feature* feature, qcv::Manager::Instance()->features())
  {
    feature_menu->addAction(feature->Name());
    tool_bar_->addAction(feature->Icon(), feature->Name());
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
