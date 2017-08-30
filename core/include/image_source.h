#ifndef  __CORE_IMAGE_SOURCE_H__
#define  __CORE_IMAGE_SOURCE_H__

#include "def.h"
#include "object.h"
#include <opencv2/opencv.hpp>

namespace qcv
{

struct ImageBuffer;

class Qcv_API ImageSource : public Object
{
  Q_OBJECT
public:
  virtual ~ImageSource(){};

  virtual bool Open() = 0;
  virtual void Close() = 0;
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual cv::Mat Capture() = 0;
  virtual cv::Mat DisCapture() = 0;
signals:
  void ChangedEvent(cv::Mat&);
};

}// !namespace ImageSource
Q_DECLARE_INTERFACE(qcv::ImageSource, "com.qcv.image_source")

#endif //!__CORE_IMAGE_SOURCE_H__