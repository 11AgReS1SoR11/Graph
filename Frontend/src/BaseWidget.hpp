#pragma once

#include <QWidget>

namespace frontend
{

class BaseWidget : public QWidget
{
public:
    explicit BaseWidget(QWidget* parent = nullptr);
};

} // namespace frontend
