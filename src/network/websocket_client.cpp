#include "websocket_client.h"
#include "../core/logger.h"

WebSocketClient::WebSocketClient(QObject *parent)
    : QObject(parent)
    , m_webSocket(new QWebSocket)
{
    connect(m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
    connect(m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this, &WebSocketClient::onError);
}

WebSocketClient::~WebSocketClient() {
    disconnectFromServer();
    delete m_webSocket;
}

void WebSocketClient::connectToServer(const QString &url, quint16 port) {
    QString fullUrl = QString("ws://%1:%2").arg(url).arg(port);
    m_webSocket->open(QUrl(fullUrl));
    Logger::instance()->info("正在连接WebSocket：" + fullUrl);
}

void WebSocketClient::disconnectFromServer() {
    if (m_webSocket->state() == QAbstractSocket::ConnectedState) {
        m_webSocket->close();
    }
}

void WebSocketClient::sendMessage(const QString &message) {
    if (m_webSocket->state() == QAbstractSocket::ConnectedState) {
        m_webSocket->sendTextMessage(message);
    }
}

QAbstractSocket::SocketState WebSocketClient::state() const {
    return m_webSocket->state();
}

// 私有槽函数实现
void WebSocketClient::onConnected() {
    Logger::instance()->info("WebSocket连接已建立");
    emit connected();
}

void WebSocketClient::onDisconnected() {
    Logger::instance()->info("WebSocket连接已断开");
    emit disconnected();
}

void WebSocketClient::onTextMessageReceived(const QString &message) {
    Logger::instance()->info("接收到文本消息：" + message);
    emit messageReceived(message);
}

void WebSocketClient::onError(QAbstractSocket::SocketError error) {
    QString errorMsg = QString("WebSocket错误：%1").arg(m_webSocket->errorString());
    Logger::instance()->error(errorMsg);
    emit errorOccurred(errorMsg);
}