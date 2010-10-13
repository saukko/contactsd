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

#ifndef CONTACTSPLUGINLOADER_H_
#define CONTACTSPLUGINLOADER_H_

#include <QObject>
#include <QMap>

#include "importstate.h"

class QPluginLoader;
class QString;
class QStringList;
class ContactsdPluginInterface;

class ContactsdPluginLoader : public QObject
{
    Q_OBJECT

public:
    ContactsdPluginLoader();
    ~ContactsdPluginLoader();

    void loadPlugins(const QStringList &plugins);
    void loadPlugins(const QString &pluginsDir, const QStringList &plugins);
    QStringList loadedPlugins() const;

public Q_SLOTS:
    bool hasActiveImports();

Q_SIGNALS:
    void importStarted(const QStringList &services);
    void importStateChanged(const QStringList &finishedServices,
                            const QStringList &newServices);
    void importEnded(int contactsAdded, int contactsRemoved,
                     int contactsMerged);
    void pluginsLoaded();

private slots:
    void onPluginImportStarted(const QStringList &services);
    void onPluginImportStateChanged(const QStringList &finishedServices,
                                    const QStringList &newServices);
    void onPluginImportEnded(int contactsAdded, int contactsRemoved,
                             int contactsMerged);

private:
    void registerNotificationService();
    QString pluginName(ContactsdPluginInterface *plugin);

    typedef QMap<QString, QPluginLoader *> PluginStore;
    PluginStore mPluginStore;
    
    ImportState mImportState;
};

#endif
