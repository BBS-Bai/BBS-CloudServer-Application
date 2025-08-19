#include "logger.h"

Logger* Logger::instance() {
    static Logger logger;
    return &logger;
}

Logger::Logger(QObject *parent) : QObject(parent) {
    // 日志文件路径（可配置）
    QString logPath = QCoreApplication::applicationDirPath() + "/client.log";
    m_logFile.setFileName(logPath);
    
    if (!m_logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qWarning() << "无法打开日志文件：" << logPath;
        return;
    }
    
    m_logStream.setDevice(&m_logFile);
    m_logStream.setCodec("UTF-8");
    
    // 写入日志头
    m_logStream << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "] "
                << "日志系统初始化完成" << "\n";
}

Logger::~Logger() {
    if (m_logFile.isOpen()) {
        m_logStream << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "] "
                    << "日志系统关闭" << "\n";
        m_logFile.close();
    }
}

void Logger::info(const QString &msg) {
    QString log = QString("[%1] [INFO] %2\n")
                  .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                  .arg(msg);
    m_logStream << log;
    qDebug() << log.trimmed();  // 同时输出到控制台
}

void Logger::warning(const QString &msg) {
    QString log = QString("[%1] [WARNING] %2\n")
                  .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                  .arg(msg);
    m_logStream << log;
    qWarning() << log.trimmed();
}

void Logger::error(const QString &msg) {
    QString log = QString("[%1] [ERROR] %2\n")
                  .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                  .arg(msg);
    m_logStream << log;
    qCritical() << log.trimmed();
}