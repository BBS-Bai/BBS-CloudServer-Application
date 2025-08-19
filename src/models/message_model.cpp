#include "message_model.h"

MessageModel::MessageModel(QObject *parent)
    : QAbstractListModel(parent) {}

int MessageModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return m_messages.size();
}

QVariant MessageModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_messages.size())
        return QVariant();

    const Message &msg = m_messages[index.row()];
    switch (role) {
    case SenderRole: return msg.sender;
    case ContentRole: return msg.content;
    default: return QVariant();
    }
}

QHash<int, QByteArray> MessageModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[SenderRole] = "sender";
    roles[ContentRole] = "content";
    return roles;
}

void MessageModel::addMessage(const QString &sender, const QString &content) {
    beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
    m_messages.append({sender, content});
    endInsertRows();
}