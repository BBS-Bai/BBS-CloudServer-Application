#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

class Logger : public QObject {
    Q_OBJECT

public:
    static Logger* instance();  // 单例访问接口
    void info(const QString &msg);
    void warning(const QString &msg);
    void error(const QString &msg);

private:
    explicit Logger(QObject *parent = nullptr);
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    QFile m_logFile;          // 日志文件
    QTextStream m_logStream;  // 日志流
};

#endif // LOGGER_H