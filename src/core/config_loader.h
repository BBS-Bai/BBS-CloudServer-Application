#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <QObject>
#include <QJsonObject>
#include <QFile>

class ConfigLoader : public QObject {
    Q_OBJECT

public:
    static ConfigLoader* instance();
    bool loadConfig(const QString &filePath = "config.json");
    QString serverAddress() const;
    quint16 serverPort() const;

private:
    explicit ConfigLoader(QObject *parent = nullptr);
    ~ConfigLoader();

    QJsonObject m_config;  // 配置数据
};

#endif // CONFIG_LOADER_H