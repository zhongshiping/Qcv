#include "gray_feature.h"
#include <QWidget>
#include <QIcon>
#include <opencv2/opencv.hpp>

using namespace cv;

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

void GrayFeatur::Process(cv::Mat& mat)
{
  switch (mat.channels())
  {
  case 1:
    break;
  case 3:
    cvtColor(mat, mat, COLOR_BGR2GRAY);
  case 4:
    cvtColor(mat, mat, COLOR_BGRA2GRAY);
    break;
  default:
    break;
  }
}

QIcon GrayFeatur::Icon() const
{
  return QIcon(":/rc/gray.png");
}