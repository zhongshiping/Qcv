#include "image_view.h"
#include <QPainter>

ImageView::ImageView()
  : scale_(1)
{
}

ImageView::~ImageView()
{
}

void ImageView::SetImage(QImage image)
{
  image_ = image;
}

void ImageView::SetScale(qreal scale)
{
  scale_ = scale;
}

void ImageView::paintEvent(QPaintEvent* e)
{
  QPainter p(this);
  p.scale(scale_, scale_);
  p.drawImage(0, 0, image_);
}
