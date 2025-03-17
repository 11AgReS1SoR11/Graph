#pragma once

#include <QMainWindow>
#include <QHBoxLayout>

namespace frontend
{

class TextWidget;
class GraphicsWidget;

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget* parent = nullptr);

private:
    void createButtons();

    TextWidget* textWidget;
    GraphicsWidget* graphicsWidget;
    QHBoxLayout* mainlayout;
    QVBoxLayout* buttonLayout;
};

} // namespace frontend
