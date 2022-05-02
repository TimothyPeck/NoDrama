#ifndef PARTY_H
#define PARTY_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QVariant>
#include <QMap>
#include <QDateTime>
#include "User.h"

class Party
{
private:
    int partyID;
    QString partyName;
    QDateTime partyDate;
    int minAffinity;
    int maxPeople;
    User host;
    QList<User> guests;

    Database* db;
    QSqlQuery query;
public:
    Party();
    Party(QString name, QDateTime dateTime, int minAffinity, int maxPeople, QList<User> predeterminedGuests, User host);
    Party(const Party&);
    ~Party();

    void addGuest(User guest);
    void createParty();
    static Party getPartyById(int);
    static Party getPartyByHost(User);
    static QList<User> getGuestsByPartyId(int);

    // Getters
    const QString &getPartyName() const;
    const QDateTime &getPartyDate() const;
    int getMinAffinity() const;
    int getMaxPeople() const;
    const User &getHost() const;
    const QList<User> &getGuests() const;
    int getPartyID() const;
};

#endif // PARTY_H
