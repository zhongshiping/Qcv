#include "manager.h"
#include "feature.h"
#include <QDir>
#include <QPluginLoader>
#include <QCoreApplication>
#include <QWidget>
#include <QTextStream>

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

bool Manager::LoadImageSource()
{
  QDir plugin_dir = QCoreApplication::applicationDirPath();
  if(!plugin_dir.cd("./plugins/capture/picture"))
  {
    return false;
  }
  QStringList filter("*.dll");
  QStringList files = plugin_dir.entryList(filter);
  foreach(const QString& file_name, files)
  {
    QPluginLoader loader(plugin_dir.absoluteFilePath(file_name));
    ImageSource* image_source = qobject_cast<ImageSource*>(loader.instance());
    if(image_source != nullptr)
    {
      image_source_ = image_source;
    }
  }
  if(image_source_ == nullptr)
  {
    return false;
  }
  return true;
}

bool Manager::LoadFeaturePlugins()
{
  QDir plugin_path = QCoreApplication::applicationDirPath();
  plugin_path.cd("./plugins/feature");
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

Manager::Manager(): image_source_(nullptr)
{
}

Manager::~Manager()
{
}

void SetStyleSheet(QWidget* widget, QString file_path)
{
  QFile file;
  file.setFileName(file_path);
  if(!file.open(QIODevice::ReadOnly))
  {
    return;
  }
  QTextStream text_stream(&file);
  widget->setStyleSheet(text_stream.readAll());
}
}
