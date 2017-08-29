#ifndef  __CORE_IMAGE_SOURCE_H__
#define  __CORE_IMAGE_SOURCE_H__

#include "def.h"
#include <QObject>
#include <QImage>

namespace qcv
{

struct ImageBuffer;

class Qcv_API ImageSource : public QObject
{
  Q_OBJECT
public:
  virtual ~ImageSource(){};

  virtual bool Open() = 0;
  virtual void Close() = 0;
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual ImageBuffer* Capture() = 0;
  virtual ImageBuffer* DisCapture() = 0;
signals:
  void ChangedEvent(void*, QImage::Format f);
};

struct ImageBuffer
{
  unsigned char* buffer;
  int width;
  int height;
  int bytes_perline;
  bool used;
};
}// !namespace ImageSource
Q_DECLARE_INTERFACE(qcv::ImageSource, "com.qcv.image_source")

#endif //!__CORE_IMAGE_SOURCE_H__