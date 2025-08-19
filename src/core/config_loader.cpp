#include "config_loader.h"
#include "logger.h"

ConfigLoader* ConfigLoader::instance() {
    static ConfigLoader loader;
    return &loader;
}

ConfigLoader::ConfigLoader(QObject *parent) : QObject(parent) {}

ConfigLoader::~ConfigLoader() {}

bool ConfigLoader::loadConfig(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Logger::instance()->error("无法打开配置文件：" + filePath);
        return false;
    }

    QByteArray data = file.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    
    if (error.error != QJsonParseError::NoError) {
        Logger::instance()->error("配置文件解析失败：" + error.errorString());
        return false;
    }

    m_config = doc.object();
    Logger::instance()->info("配置文件加载成功");
    return true;
}

QString ConfigLoader::serverAddress() const {
    return m_config.value("server_address").toString("127.0.0.1");
}

quint16 ConfigLoader::serverPort() const {
    return m_config.value("server_port").toInt(8080);
}