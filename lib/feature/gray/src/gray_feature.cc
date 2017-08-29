#include "gray_feature.h"
#include <QWidget>
#include <QIcon>

GrayFeatur::GrayFeatur()
{
}

GrayFeatur::~GrayFeatur()
{
}

QString GrayFeatur::Name() const
{
  return QStringLiteral("Gray");
}

QWidget* GrayFeatur::ToolWidget() const
{
  return new QWidget;
}

void GrayFeatur::Process(unsigned char* image, const QSize& size)
{
}

QIcon GrayFeatur::Icon() const
{
  return QIcon(":/rc/gray.png");
}
