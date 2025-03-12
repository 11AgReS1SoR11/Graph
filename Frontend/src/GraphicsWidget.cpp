#include "GraphicsWidget.hpp"

namespace frontend
{

GraphicsWidget::GraphicsWidget(QWidget* parent) : BaseWidget(parent)
{
    setFixedSize(350, 550);
    setStyleSheet("background-color:black;");
}

} // namespace frontend
