#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebSockets/QWebSocket>
#include "../network/websocket_client.h"
#include "../core/logger.h"
#include "../models/message_model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();       // 连接服务器按钮点击
    void on_sendButton_clicked();          // 发送消息按钮点击
    void handleWebSocketConnected();       // WebSocket连接成功
    void handleWebSocketDisconnected();    // WebSocket断开连接
    void handleMessageReceived(const QString &message); // 接收消息

private:
    Ui::MainWindow *ui;
    WebSocketClient *m_webSocket;          // WebSocket客户端实例
    MessageModel *m_messageModel;          // 消息数据模型
    Logger *m_logger;                        // 日志实例
};

#endif // MAINWINDOW_H