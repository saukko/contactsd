/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (people-users@projects.maemo.org)
**
** This file is part of contactsd.
**
** If you have questions regarding the use of this file, please contact
** Nokia at people-users@projects.maemo.org.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef PENDINGROSTERS_H
#define PENDINGROSTERS_H

#include <TelepathyQt4/PendingOperation>
#include <TelepathyQt4/Types>
#include <TelepathyQt4/Account>
#include <TelepathyQt4/AccountManager>
#include <TelepathyQt4/PendingReady>
#include <TelepathyQt4/PendingContacts>
#include <TelepathyQt4/PendingAccount>
#include <TelepathyQt4/ContactManager>
#include <TelepathyQt4/ConnectionManager>
#include <QList>
#include <tpcontact.h>

class TelepathyController;

class PendingRosters : public Tp::PendingOperation
{
    Q_OBJECT
public:
    explicit PendingRosters(QObject *parent = 0);
    Tp::Contacts rosterList() const;
    QList<QSharedPointer<TpContact> > telepathyRosterList() const;
Q_SIGNALS:
    void contact(QSharedPointer<TpContact>);
private Q_SLOTS:
    void onConnectionReady(Tp::PendingOperation * po);
    void onAccountReady(Tp::PendingOperation* op);
    void onHaveConnectionChanged(bool);
    void onConnectionStatusChanged(Tp::ConnectionStatus status, Tp::ConnectionStatusReason reason);
private:
    Q_DISABLE_COPY(PendingRosters)
    friend class TelepathyController;
    void addRequestForAccount(Tp::AccountPtr);

    Tp::Contacts mContacts;
    QList<QSharedPointer<TpContact> >  mTpContacts;
    QList<Tp::ConnectionPtr> mConnectionList;
    Tp::AccountPtr mAccount;
    int mCapCount;
    bool mWasOnline;

};

#endif // PENDINGROSTERS_H