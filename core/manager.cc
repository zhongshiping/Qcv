#include "manager.h"
#include "feature.h"
#include <QDir>
#include <QPluginLoader>
#include <QCoreApplication>

namespace qcv
{
Manager* Manager::instance_ = nullptr;

Manager* Manager::Instance()
{
  if (!instance_)
  {
    instance_ = new Manager;
  }
  return instance_;
}

void Manager::Destory()
{
  if (instance_)
  {
    delete instance_;
    instance_ = nullptr;
  }
}

bool Manager::LoadPlugins()
{
  QDir plugin_path = QCoreApplication::applicationDirPath();
  plugin_path.cd("./plugins/");
  QFileInfoList file_info_list = plugin_path.entryInfoList();
  foreach(const QFileInfo& file_info, file_info_list)
  { 
    QString name = file_info.fileName();
    if(name == "." || name == "..")
    {
      continue;
    }
    bool is_dir = file_info.isDir();
    if(is_dir)
    { 
      plugin_path.cd(name);
    }
    file_info_list = plugin_path.entryInfoList();
    foreach(const QFileInfo& info, file_info_list)
    {
      if(info.fileName().split(".").last() == "dll")
      {
        QString file_path = info.absoluteFilePath();
        QPluginLoader loader(file_path);
        Feature* feature = qobject_cast<Feature*>(loader.instance());
        if (feature)
        {
          features_.append(feature);
        }
      }
     }
   }
  if(features_.count() == 0)
  {
    return false;
  }
  return true;
}

Manager::Manager()
{
}

Manager::~Manager()
{
}
}