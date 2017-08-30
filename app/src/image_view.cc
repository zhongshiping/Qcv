#include "image_view.h"
#include "image_view_impl.h"

ImageView::ImageView(QWidget* parent)
  : QScrollArea(parent)
  , impl_(new Impl(this))
{
  setAlignment(Qt::AlignCenter);
  setWidget(impl_);
  connect(impl_, &Impl::ScaleChanged, this, &ImageView::ScaleChanged);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

ImageView::~ImageView()
{
}

void ImageView::SetBackgroundImage(const QImage& image)
{
  impl_->SetBackgroundImage(image);
}

void ImageView::ZoomIn()
{
  impl_->ZoomIn();
}

void ImageView::ZoomOut()
{
  impl_->ZoomOut();
}

void ImageView::Fit()
{
  impl_->Fit(width(), height());
}

void ImageView::Original()
{
  impl_->Original();
}

void ImageView::Save()
{
  impl_->Save();
}
