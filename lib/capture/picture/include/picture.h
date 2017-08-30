#ifndef __PICTURE_H__
#define __PICTURE_H__

#include "image_source.h"
#include <QTimer>

class Picture : public qcv::ImageSource
{
  Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qcv.capture.picture")
    Q_INTERFACES(qcv::ImageSource)
public:
  explicit Picture();
  ~Picture() override;

  bool Open() override;
  void Close() override;
  bool Start() override;
  void Stop() override;

  cv::Mat Capture() override;
  cv::Mat DisCapture() override;

private:
  void Grab();
  void TimeHandle();
  QTimer timer_;
  bool need_image_;
  cv::Mat image_;
};

#endif //__PICTURE_H__