#include "Frontend.hpp"
#include "MainWindow.hpp"

#include <QApplication>
namespace frontend
{

int Frontend::exec(int argc, char* argv[]) const
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

} // namespace frontend
