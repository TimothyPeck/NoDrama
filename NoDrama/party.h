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
    Q_PROPERTY(QString partyName READ getPartyName() CONSTANT)
    Q_PROPERTY(QString partyDate READ getPartyDateString() CONSTANT)
    Q_PROPERTY(QString partyTime READ getPartyTimeString() CONSTANT)
    Q_PROPERTY(int minAffinity READ getMinAffinity() CONSTANT)
    Q_PROPERTY(int maxPeople READ getMaxPeople() CONSTANT)
    Q_PROPERTY(User host READ getHost() CONSTANT)
    Q_PROPERTY(int hostID READ getHostID() CONSTANT)
    Q_PROPERTY(QString location READ getPartyLocation() CONSTANT)
    Q_PROPERTY(QList<User> guests READ getGuests() CONSTANT)
    Q_PROPERTY(QList<QString> guestUsernames READ getGuestUsernames() CONSTANT)
    QML_ELEMENT
private:
    /**
     * @brief partyID Id of the party
     */
    int partyID;
    /**
     * @brief partyName Name of the party
     */
    QString partyName;
    /**
     * @brief partyDate Date of the party
     */
    QDateTime partyDate;
    /**
     * @brief minAffinity The minimum affinity required to be invited to the party
     */
    int minAffinity;
    /**
     * @brief maxPeople The maximum number of people qho can be invited to the party
     */
    int maxPeople;
    /**
     * @brief host The host of the party
     */
    User host = User();
    /**
     * @brief location The location of the party
     */
    QString location;
    /**
     * @brief guests The guests of the party
     */
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

    /**
     * @brief setName Set the party name
     * @param n New party name
     */
    Q_INVOKABLE void setName(QString n) { this->partyName = n;}

    /**
     * @brief setDate Set the party date
     * @param d New party date
     */
    Q_INVOKABLE void setDate(QString d) { this->partyDate.setDate(QDate::fromString(d, "dd.MM.yyyy")); }

    /**
     * @brief setTime Set the party time
     * @param t New party time
     */
    Q_INVOKABLE void setTime(QString t) { this->partyDate.setTime(QTime::fromString(t, "h:m")); }
    /**
     * @brief setMinAffi Set the party minimum affinity
     * @param a New minimum affinity
     */
    Q_INVOKABLE void setMinAffi(QString a) { this->minAffinity = a.toInt(); }
    /**
     * @brief setMaxP Set the party max guests
     * @param p The new max guests
     */
    Q_INVOKABLE void setMaxP(QString p) { this->maxPeople = p.toInt(); }
    /**
     * @brief setLoc Set the party location
     * @param l The new party location
     */
    Q_INVOKABLE void setLoc(QString l) { this->location = l; }
    /**
     * @brief setHost Set the party host
     * @param u New party host
     */
    Q_INVOKABLE void setHost(User* u) { this->host = u; }

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
    Q_INVOKABLE const QString getPartyDateString() const;
    Q_INVOKABLE const QString getPartyTimeString() const;
    Q_INVOKABLE int getMinAffinity() const;
    Q_INVOKABLE int getMaxPeople() const;
    Q_INVOKABLE const User &getHost() const;
    Q_INVOKABLE const int getHostID();
    //Q_INVOKABLE const User* getHost() const;
    Q_INVOKABLE const QList<User> &getGuests() const;
    Q_INVOKABLE const QList<QString> getGuestUsernames();
    Q_INVOKABLE int getPartyID() const;
    Q_INVOKABLE const QString &getPartyLocation() const;
};

#endif // PARTY_H
