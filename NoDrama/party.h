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
    Q_PROPERTY(int partyID READ getPartyID() CONSTANT)
    QML_ELEMENT
private:
    int partyID;
    QString partyName;
    QDateTime partyDate;
    int minAffinity;
    int maxPeople;
    User host = User();
    QString location;
    QList<User> guests;

    Database* db;
    QSqlQuery query;
public:
    Party();
    Q_INVOKABLE Party(QString name, QDateTime dateTime, int minAffinity, int maxPeople, QList<User> predeterminedGuests, User host, QString location);
    Q_INVOKABLE Party(int id, QString name, QDateTime dateTime, int minAffinity, int maxPeople, QList<User> predeterminedGuests, User host, QString location);
    Q_INVOKABLE Party(const Party&);
    Q_INVOKABLE void constructor(Party*);

    ~Party();

    /**
     * @brief operator == equality operator override fot the party class
     * @param lhs
     * @return bool if equal
     */
    bool operator==(const Party& lhs) const{
        return partyName==lhs.partyName;
    }

    /**
     * @brief operator = overriden assignement operator for the Party class
     * @param lhs
     * @return Party object
     */
    Party& operator=(const Party& lhs) {
        partyID=lhs.partyID;
        partyName=lhs.partyName;
        partyDate=lhs.partyDate;
        minAffinity=lhs.minAffinity;
        maxPeople=lhs.maxPeople;
        host=lhs.host;
        location=lhs.location;
        guests=lhs.guests;
        guests.detach();
        db=lhs.db;
        return *this;
    }

    Q_INVOKABLE void setName(QString n) { this->partyName = n;}
    Q_INVOKABLE void setDate(QString d) { this->partyDate = QDateTime::fromString(d);}
    Q_INVOKABLE void setMinAffi(QString a) { this->minAffinity = a.toInt(); }
    Q_INVOKABLE void setMaxP(QString p) { this->maxPeople = p.toInt(); }
    Q_INVOKABLE void setLoc(QString l) { this->location = l; }

    void addGuest(User guest);
    Q_INVOKABLE void addOrRemoveGuest(QString name);
    Q_INVOKABLE bool isFriendInGuest(QString name);
    Q_INVOKABLE QVariantList getGuestsForDisplay();
    Q_INVOKABLE void createParty();
    Q_INVOKABLE static Party* getPartyById(int);
    //Q_INVOKABLE static Party getPartyByHost(User);
    Q_INVOKABLE static QList<User> getGuestsByPartyId(int);
    Q_INVOKABLE static QList<Party>* getPartiesForUser(User* user);
    Q_INVOKABLE static QList<int> getPartyIdsForUser(User* user);

    Q_INVOKABLE void determineGuests();

    // Getters
    Q_INVOKABLE const QString &getPartyName() const;
    Q_INVOKABLE const QDateTime &getPartyDate() const;
    Q_INVOKABLE int getMinAffinity() const;
    Q_INVOKABLE int getMaxPeople() const;
    Q_INVOKABLE const User &getHost() const;
    //Q_INVOKABLE const User* getHost() const;
    Q_INVOKABLE const QList<User> &getGuests() const;
    Q_INVOKABLE int getPartyID() const;
    Q_INVOKABLE const QString &getPartyLocation() const;
};

#endif // PARTY_H
