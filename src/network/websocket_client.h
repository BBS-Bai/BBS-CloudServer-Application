#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QHostAddress>

class WebSocketClient : public QObject {
    Q_OBJECT

public:
    explicit WebSocketClient(QObject *parent = nullptr);
    ~WebSocketClient();

    void connectToServer(const QString &url, quint16 port);
    void disconnectFromServer();
    void sendMessage(const QString &message);
    QAbstractSocket::SocketState state() const;

    signals:
        void connected();                          // 连接成功信号
    void disconnected();                       // 断开连接信号
    void messageReceived(const QString &message);// 接收消息信号
    void errorOccurred(const QString &error);   // 错误信号

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString &message);
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket *m_webSocket;
};

#endif // WEBSOCKET_CLIENT_H