#ifndef __APP_IMAGE_VIEW_H__
#define __APP_IMAGE_VIEW_H__

#include <QWidget>

class ImageView : public QWidget
{
  Q_OBJECT
public:
  explicit ImageView();
  ~ImageView();

  void SetImage(QImage image);
  void SetScale(qreal scale);
protected:
  void paintEvent(QPaintEvent* e) override;

private:

  QImage image_;
  qreal scale_;
};

#endif //!__APP_IMAGE_VIEW_H__