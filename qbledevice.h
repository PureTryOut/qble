#ifndef QBLEDEVICE_H
#define QBLEDEVICE_H

#include "qbleservice.h"

#include <QObject>
#include <QtDBus>
#include <QVariantMap>

class QBLEDevice : public QObject
{
    Q_OBJECT
public:
    explicit QBLEDevice(QObject *parent = nullptr);

    QBLEService *service(const QString &uuid);

    void setDevicePath(const QString &path);
    virtual QString pair();
    virtual void pairAsync();

    virtual void connectToDevice();
    virtual void disconnectFromDevice();

    QString devicePath() const;

    Q_SIGNAL void propertiesChanged(const QString &interface, const QVariantMap &map, const QStringList &list);

    Q_SIGNAL void pairFinished(const QString &message);

protected:
    Q_SIGNAL void servicesResolved();

    void addService(const QString &uuid, QBLEService *service);
    QVariant deviceProperty(const char *name) const;

private:
    QString m_devicePath;
    QMap<QString, QBLEService*> m_serviceMap;
    QDBusInterface *m_deviceInterface;

    void introspect();
    Q_SLOT void onPairFinished(QDBusPendingCallWatcher *call);
    Q_SLOT void onPropertiesChangedInt(const QString &interface, const QVariantMap &map, const QStringList &list);
};

#endif // QBLEDEVICE_H
