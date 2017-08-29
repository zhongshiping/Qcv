#ifndef __GRAY_FEATURE_H__
#define __GRAY_FEATURE_H__

#include "feature.h"

class GrayFeatur : public qcv::Feature
{
  Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qcv.feature.gray")
    Q_INTERFACES(qcv::Feature)
public:
  explicit GrayFeatur();
  ~GrayFeatur() override;

  QString Name() const override;
  QWidget* ToolWidget() const override;
  void Process(unsigned char* image, const QSize& size) override;
  QIcon Icon() const override;
};

#endif //!__GRAY_FEATURE_H__