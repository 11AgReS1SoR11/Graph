#include "MainWindow.hpp"
#include "GraphicsWidget.hpp"
#include "TextWidget.hpp"
#include "utils/Style/ButtonStyle.hpp"

#include <QPushButton>
#include <QDir>
#include <QDebug>

namespace frontend
{

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setFixedSize(800, 600);
    auto* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainlayout = new QHBoxLayout(centralWidget);
    textWidget = new TextWidget(this);
    graphicsWidget = new GraphicsWidget(this);

    createButtons();

    mainlayout->addWidget(textWidget);
    mainlayout->addLayout(buttonLayout);
    mainlayout->addWidget(graphicsWidget);
}

void MainWindow::createButtons()
{
    buttonLayout = new QVBoxLayout();

    QStringList buttonIcons = {"build/Frontend/Resources/Recompile.jpg", "build/Frontend/Resources/left.png", "build/Frontend/Resources/right.png",
                                "build/Frontend/Resources/down.png", "build/Frontend/Resources/up.png", "build/Frontend/Resources/tree.png"};
    for (auto const& imagePath : buttonIcons)
    {
        auto* btn = new QPushButton(this);
        btn->setFixedSize(40, 40);

        // set Image
        btn->setFlat(true);
        btn->setStyleSheet(QString(utils::BUTTON_STYLE).arg(imagePath));

        buttonLayout->addWidget(btn);
    }
}

} // namespace frontend
