#include "image_view_impl.h"
#include <QPainter>
#include <QtMath>
#include <QWheelEvent>
#include <QDateTime>
#include <QCoreApplication>

qreal ImageView::Impl::kZoomInRatio = 1.25;

ImageView::Impl::Impl(QWidget* parent)
  : QWidget(parent)
  , in_zoom_fit_(false)
  , scale_(1.0)
{
  setMouseTracking(true);
}

ImageView::Impl::~Impl()
{
}

bool ScaleInRange(qreal scale)
{
  return scale < 15.0 && scale > 0.01;
}
void ImageView::Impl::SetBackgroundImage(const QImage& image)
{
  if (!image.isNull())
  {
    background_pixmap_ = QPixmap::fromImage(image);

    UpdateScale(scale_);
    update();
  }
}

void ImageView::Impl::ZoomIn()
{
  if (background_pixmap_.isNull())
  {
    return;
  }
  qreal scale = scale_;
  if (in_zoom_fit_)
  {
    scale = GetNearestZoomFactor(scale, true);
  }
  else
  {
    scale *= kZoomInRatio;
  }
  in_zoom_fit_ = false;
  if (ScaleInRange(scale))
  {
    UpdateScale(scale);
  }
}

void ImageView::Impl::ZoomOut()
{
  if (background_pixmap_.isNull())
  {
    return;
  }
  qreal scale = scale_;
  if (in_zoom_fit_)
  {
    scale = GetNearestZoomFactor(scale, false);
  }
  else
  {
    scale /= kZoomInRatio;
  }
  in_zoom_fit_ = false;
  if (ScaleInRange(scale))
  {
    UpdateScale(scale);
  }
}

void ImageView::Impl::Fit(int w, int h)
{
  if (background_pixmap_.isNull())
  {
    return;
  }
  QSize size = background_pixmap_.size();
  if (size.isEmpty())
  {
    return;
  }
  qreal h_scale = (qreal)w / size.width();
  qreal v_scale = (qreal)h / size.height();
  qreal scale = qMin(h_scale, v_scale);

  in_zoom_fit_ = true;
  if (ScaleInRange(scale))
  {
    UpdateScale(scale);
  }
}

void ImageView::Impl::Original()
{
  UpdateScale(1.0);
}

void ImageView::Impl::Save()
{
  if (!background_pixmap_.isNull())
  {
    QString file_name = QCoreApplication::applicationDirPath() + "/" + QDateTime::currentDateTime().toString("yyMMddhhmmss") + ".png";
    background_pixmap_.save(file_name);
  }
}

void ImageView::Impl::paintEvent(QPaintEvent* e)
{
  QPainter p(this);
  p.scale(scale_, scale_);
  if (!background_pixmap_.isNull())
  {
    p.drawPixmap(0, 0, background_pixmap_);
  }
  QWidget::paintEvent(e);
}

void ImageView::Impl::wheelEvent(QWheelEvent* e)
{
  if (e->modifiers().testFlag(Qt::ControlModifier))
  {
    if (e->delta() > 0)
    {
      ZoomIn();
    }
    else
    {
      ZoomOut();
    }
  }
  else
  {
    QWidget::wheelEvent(e);
  }
}

void ImageView::Impl::UpdateScale(qreal scale)
{
  scale_ = scale;
  resize(background_pixmap_.size()*scale_);

  emit ScaleChanged(scale_);
}

qreal ImageView::Impl::GetNearestZoomFactor(qreal scale, bool try_zoom_in)
{
  qreal k = qLn(scale_) / qLn(kZoomInRatio);
  int ki = try_zoom_in ? qCeil(k) : qFloor(k);

  return qPow(kZoomInRatio, ki);
}
