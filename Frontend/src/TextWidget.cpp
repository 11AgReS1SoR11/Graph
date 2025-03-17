#include "TextWidget.hpp"

#include <QVBoxLayout>
#include <QTextEdit>

namespace frontend
{

TextWidget::TextWidget(QWidget* parent) : BaseWidget(parent)
{
    setFixedSize(350, 550);
    auto layout = new QVBoxLayout(this);
    auto textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);
    setLayout(layout);
    setStyleSheet("background-color:white;");
}

} // namespace frontend
