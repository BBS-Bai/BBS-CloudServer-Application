#ifndef MESSAGE_MODEL_H
#define MESSAGE_MODEL_H

#include <QAbstractListModel>
#include <QStringList>

class MessageModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit MessageModel(QObject *parent = nullptr);
    enum Roles {
        SenderRole = Qt::UserRole + 1,
        ContentRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addMessage(const QString &sender, const QString &content);

private:
    struct Message {
        QString sender;
        QString content;
    };
    QList<Message> m_messages;  // 消息存储列表
};

#endif // MESSAGE_MODEL_H