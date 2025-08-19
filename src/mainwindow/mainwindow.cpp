#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core/config_loader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_webSocket(new WebSocketClient(this))
    , m_messageModel(new MessageModel(this))
    , m_logger(Logger::instance())
{
    ui->setupUi(this);

    // 初始化界面
    ui->messageView->setModel(m_messageModel);  // 关联消息模型
    ui->serverAddressEdit->setText(ConfigLoader::instance()->serverAddress());
    ui->serverPortEdit->setText(QString::number(ConfigLoader::instance()->serverPort()));

    // 连接信号槽
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::on_connectButton_clicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);
    connect(m_webSocket, &WebSocketClient::connected, this, &MainWindow::handleWebSocketConnected);
    connect(m_webSocket, &WebSocketClient::disconnected, this, &MainWindow::handleWebSocketDisconnected);
    connect(m_webSocket, &WebSocketClient::messageReceived, this, &MainWindow::handleMessageReceived);

    m_logger->info("主窗口初始化完成");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_connectButton_clicked() {
    QString address = ui->serverAddressEdit->text();
    quint16 port = ui->serverPortEdit->text().toUShort();

    if (address.isEmpty() || port == 0) {
        m_logger->error("服务器地址或端口为空");
        return;
    }

    m_webSocket->connectToServer(address, port);
    m_logger->info("尝试连接服务器：" + address + ":" + QString::number(port));
}

void MainWindow::on_sendButton_clicked() {
    QString message = ui->messageEdit->text().trimmed();
    if (message.isEmpty()) return;

    if (m_webSocket->state() == QAbstractSocket::ConnectedState) {
        m_webSocket->sendMessage(message);
        m_messageModel->addMessage("我", message);  // 本地消息入模型
        ui->messageEdit->clear();
    } else {
        m_logger->warning("未连接到服务器，无法发送消息");
    }
}

void MainWindow::handleWebSocketConnected() {
    m_logger->info("WebSocket连接成功");
    ui->statusLabel->setText("已连接");
    ui->connectButton->setText("断开连接");
}

void MainWindow::handleWebSocketDisconnected() {
    m_logger->info("WebSocket连接断开");
    ui->statusLabel->setText("未连接");
    ui->connectButton->setText("连接服务器");
}

void MainWindow::handleMessageReceived(const QString &message) {
    m_logger->info("接收到消息：" + message);
    // 假设消息格式为"用户名: 内容"，实际需根据协议解析
    QStringList parts = message.split(": ");
    if (parts.size() == 2) {
        m_messageModel->addMessage(parts[0], parts[1]);
    } else {
        m_messageModel->addMessage("未知用户", message);
    }
}