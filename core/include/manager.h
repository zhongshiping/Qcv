#ifndef __CORE_MANAGER_H__
#define __CORE_MANAGER_H__

#include "def.h"
#include <QList>
#include <QObject>

namespace qcv
{
class Feature;
class Qcv_API Manager : public QObject
{
  Q_OBJECT
public:
  static Manager* Instance();
  static void Destory();
  bool LoadPlugins();

  QList<Feature*> features() { return features_; };
protected:
  explicit Manager();
  ~Manager();
private:
  static Manager* instance_;
  QList<Feature*> features_;
};
}//!namespace qcv;

#endif // !__CORE_MANAGER_H__