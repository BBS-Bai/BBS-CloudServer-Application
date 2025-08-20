#include "src/mainwindow/mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include "src/core/logger.h"
#include "src/core/config_loader.h"
//#include "resources/resources.qrc"  // 包含资源文件


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 加载配置文件
    if (!ConfigLoader::instance()->loadConfig("config.json")) {
        Logger::instance()->error("配置文件加载失败，使用默认值");
    }

    // 设置全局样式
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53,53,53));
    palette.setColor(QPalette::WindowText, Qt::white);
    app.setPalette(palette);

    // 加载样式表
    QFile styleFile(":/styles/dark_theme.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        app.setStyleSheet(style);
        styleFile.close();
    } else {
        Logger::instance()->warning("无法加载样式表文件");
    }

    // 初始化主窗口
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}