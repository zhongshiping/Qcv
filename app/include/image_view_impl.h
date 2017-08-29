#ifndef __IMAGE_VIEW_IMPL_H__
#define __IMAGE_VIEW_IMPL_H__

#include "image_view.h"

class ImageView::Impl : public QWidget
{
  Q_OBJECT
public:
  explicit Impl(QWidget* parent = nullptr);
  ~Impl();

  void SetBackgroundImage(const QImage& image);
  void ZoomIn();
  void ZoomOut();
  void Fit(int w, int h);
signals:
  void ScaleChanged(qreal scale);

protected:
  void paintEvent(QPaintEvent *e) override;
  void wheelEvent(QWheelEvent* e) override;

private:
  static qreal kZoomInRatio;
  
  void UpdateScale(qreal scale);
  qreal GetNearestZoomFactor(qreal scale, bool try_zoom_in);

  QPixmap background_pixmap_;
  bool in_zoom_fit_;
  qreal scale_;
};

#endif //!__IMAGE_VIEW_IMPL_H__