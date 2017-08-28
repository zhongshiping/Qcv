#ifndef __CORE_FEATURE_H__
#define __CORE_FEATURE_H__

#include "object.h"

namespace qcv
{
  class QToolBar;

  class Qcv_API Feature : public Object
  {
    Q_OBJECT
  public:
    virtual ~Feature() {};

    virtual QString Name() const = 0;
    virtual QWidget* ToolWidget() const = 0;
    virtual QIcon Icon() const = 0;
    virtual void Process(unsigned char* image, const QSize &size) = 0;
  };
} // !namespace qcv

Q_DECLARE_INTERFACE(qcv::Feature, "com.qcv.feature")

#endif // !__CORE_FEATURE_H__