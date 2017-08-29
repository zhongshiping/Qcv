#ifndef __CORE_MANAGER_H__
#define __CORE_MANAGER_H__

#include "def.h"
#include <QList>
#include <QObject>
#include "image_source.h"

namespace qcv
{
class Feature;

class Qcv_API Manager : public QObject
{
  Q_OBJECT
public:
  static Manager* Instance();
  static void Destory();
  
  bool LoadFeaturePlugins();
  bool LoadImageSource();

  QList<Feature*> features() const { return features_; };
  ImageSource* image_source() const { return image_source_; };
protected:
  explicit Manager();
  ~Manager();
private:
  static Manager* instance_;
  QList<Feature*> features_;
  ImageSource* image_source_;
};
  void Qcv_API SetStyleSheet(QWidget* widget, QString file);
}//!namespace qcv;

#endif // !__CORE_MANAGER_H__