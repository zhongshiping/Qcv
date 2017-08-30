#ifndef __CORE_OBJECT_H__
#define __CORE_OBJECT_H__

#include <QVariantHash>
#include "def.h"
#include <Qimage>

namespace qcv
{
  class Qcv_API Object : public QObject
  {
    Q_OBJECT
  public:
    virtual ~Object() {};

    void Set(const QString &key, QVariant &v)
    {
      if (propertys_.contains(key) && propertys_.value(key).type() == v.type())
      {
        if (propertys_[key] != v)
        {
          propertys_[key] = v;
        }
      }
    }

    QVariant Get(const QString &key)
    {
      if (propertys_.contains(key))
      {
        return propertys_[key];
      }
      return QVariant();
    }

    int PropertyCount() const { return propertys_.count(); }
    QStringList PropertyKeys() const { return propertys_.keys(); }
  private:
    QVariantHash propertys_;
  };
}
#endif //!__CORE_OBJECT_H__