#include "picture.h"
#include <QFileDialog>
#include <opencv2/opencv.hpp>

Picture::Picture()
  : need_image_(true)
{
  connect(&timer_, &QTimer::timeout, this, &Picture::TimeHandle);
}

Picture::~Picture()
{
  Picture::Close();
}

bool Picture::Open()
{
  return true;
}

void Picture::Close()
{
  Stop();
}

bool Picture::Start()
{
  timer_.start(100);
  return true;
}

void Picture::Stop()
{
  timer_.stop();
  need_image_ = false;
}

cv::Mat Picture::Capture()
{
  Grab();
  return image_;
}

cv::Mat Picture::DisCapture()
{
  return image_;
}

void Picture::Grab()
{
  QString file_name = QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "/home", tr("Image (*.png *.jpg *.bmp *.tiff)"));
  if (file_name.isNull() || file_name.isEmpty())
  {
    return;
  }
  using namespace cv;
  Mat image = imread(file_name.toStdString(), IMREAD_UNCHANGED);

  if (image.empty())
  {
    return;
  }
  image_ = image;

  emit ChangedEvent(image_);
  need_image_ = false;
}

void Picture::TimeHandle()
{
  if (need_image_)
  {
    Grab();
    emit ChangedEvent(image_);
  }
}
