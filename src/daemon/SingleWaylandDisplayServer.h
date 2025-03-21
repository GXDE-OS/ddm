// Copyright (C) 2023 Dingyuan Zhang <lxz@mkacg.com>.
// SPDX-License-Identifier: Apache-2.0 OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "DisplayServer.h"

#include <QMap>
#include <QDBusVariant>

class QLocalSocket;
class QLocalServer;

namespace DDM {
    class SocketServer;
}

class SingleWaylandDisplayServer : public DDM::DisplayServer
{
    Q_OBJECT
    Q_DISABLE_COPY(SingleWaylandDisplayServer)
public:
    explicit SingleWaylandDisplayServer(DDM::SocketServer *socketServer, DDM::Display *parent);
    ~SingleWaylandDisplayServer();

    QString sessionType() const;

    void setDisplayName(const QString &displayName);

Q_SIGNALS:
    void createWaylandSocketFinished();

public Q_SLOTS:
    bool start();
    void stop();
    void finished();
    void setupDisplay();
    void activateUser(const QString &user);
    QString getUserWaylandSocket(const QString &user) const;
    void onLoginFailed(const QString &user);
    void onLoginSucceeded(const QString &user);

private:
    DDM::SocketServer *m_socketServer;
    QList<QLocalSocket*> m_greeterSockets;
    QMap<QString, QString> m_waylandSockets;
};
