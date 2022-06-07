#ifndef PARTY_H
#define PARTY_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVariant>
#include <QMap>
#include <QDateTime>
#include "User.h"
#include <QtQml/qqmlregistration.h>

/**
 * @brief The Party class
 */
class Party : public QObject
{
    Q_OBJECT
    QML_ELEMENT
private:
    int partyID;
    QString partyName;
    QDateTime partyDate;
    int minAffinity;
    int maxPeople;
    User host;
    QString location;
    QList<User> guests;

    Database* db;
    QSqlQuery query;
public:
    Party();
    Q_INVOKABLE Party(QString name, QDateTime dateTime, int minAffinity, int maxPeople, QList<User> predeterminedGuests, User host, QString location);
    Party(const Party&);
    ~Party();

    /**
     * @brief operator = overridden equality operator for the party class
     * @param lhs
     * @return
     */
    bool operator=(const Party& lhs) const{
        return this->partyName==lhs.partyName;
    }

    void addGuest(User guest);
    Q_INVOKABLE void createParty();
    Q_INVOKABLE static Party getPartyById(int);
    //Q_INVOKABLE static Party getPartyByHost(User);
    Q_INVOKABLE static QList<User> getGuestsByPartyId(int);
    Q_INVOKABLE static QList<Party> getPartiesForUser(User* user);

    // Getters
    Q_INVOKABLE const QString &getPartyName() const;
    Q_INVOKABLE const QDateTime &getPartyDate() const;
    Q_INVOKABLE int getMinAffinity() const;
    Q_INVOKABLE int getMaxPeople() const;
    Q_INVOKABLE const User &getHost() const;
    Q_INVOKABLE const QList<User> &getGuests() const;
    Q_INVOKABLE int getPartyID() const;
    Q_INVOKABLE const QString &getPartyLocation() const;
};

#endif // PARTY_H
