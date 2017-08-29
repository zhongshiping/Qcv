#include "picture.h"
#include <QFileDialog>

Picture::Picture()
  : image_buffer_(new qcv::ImageBuffer)
  , need_image_(true)
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

qcv::ImageBuffer* Picture::Capture()
{
  Grab();
  return image_buffer_;
}

qcv::ImageBuffer* Picture::DisCapture()
{
  return image_buffer_;
}

void Picture::Grab()
{
  QString file_name = QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "/home", tr("Image (*.png *.jpg *.bmp *.tiff)"));
  if (file_name.isNull() || file_name.isEmpty())
  {
    return;
  }
  image_.load(file_name);
  if (image_.isNull())
  {
    return;
  }
  image_buffer_->buffer = new unsigned char[image_.width() * image_.height()];
  image_buffer_->height = image_.height();
  image_buffer_->width = image_.width();
  image_buffer_->bytes_perline = image_.width();

  image_buffer_->buffer = image_.bits();
  QImage::Format f = image_.format();

  emit ChangedEvent(image_buffer_, f);
  need_image_ = false;
}

void Picture::TimeHandle()
{
  if (need_image_)
  {
    Grab();
    emit ChangedEvent(image_buffer_, image_.format());
  }
}
