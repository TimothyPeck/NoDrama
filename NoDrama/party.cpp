#include "party.h"

/*
 * Constructors
 */

/**
 * @brief Construct a new empty Party object
 *
 */
Party::Party(){

}

/**
 * @brief Construct a new Party object
 *
 * @param name The name of the party
 * @param dateTime The date and time of the party
 * @param minAffinity The minimum affinity required to be invited to the party
 * @param maxPeople The maximum number of people that can be invited to the party
 * @param predeterminedGuests The guests that the host has decided must be invited, does not follow the minAffinity of the party
 * @param host The user obect of the host of the party
 * @param location The location at which the party will be held
 */
Party::Party(QString name, QDateTime dateTime, int minAffinity, int maxPeople, QList<User> predeterminedGuests, User host, QString location)
{
    this->partyName=name;
    this->partyDate=dateTime;
    this->minAffinity=minAffinity;
    this->maxPeople=maxPeople;
    this->location=location;

    this->guests=QList<User>(maxPeople);

    for(qsizetype i=0;i<predeterminedGuests.size();++i){
        this->guests.append(predeterminedGuests.at(i));
    }

    this->host = host;

    this->createParty();
}

/**
 * @brief Construct a new Party object from another Party object
 *
 * @param party The party to copy
 */
Party::Party(const Party& party){
    this->partyDate=party.partyDate;
    this->partyName=party.partyName;
    this->guests=party.guests;
    this->host=party.host;
    this->maxPeople=party.maxPeople;
    this->minAffinity=party.minAffinity;
    this->location=party.location;
}

/**
 * @brief Destroy the Party object
 *
 */
Party::~Party(){
    //free(db);
}

/*
 * Getters
 */

/**
 * @brief Returns the name of the party
 *
 * @return const QString&
 */
const QString &Party::getPartyName() const
{
    return partyName;
}

/**
 * @brief returns the date and time of the party
 *
 * @return const QDateTime&
 */
const QDateTime &Party::getPartyDate() const
{
    return partyDate;
}

/**
 * @brief Returns the minimum affinity required to be invited to the party
 *
 * @return int
 */
int Party::getMinAffinity() const
{
    return minAffinity;
}

/**
 * @brief Returns the maximum number of people that can be invited to the party
 *
 * @return int
 */
int Party::getMaxPeople() const
{
    return maxPeople;
}

/**
 * @brief Returns the user object of the host of the party
 *
 * @return const User&
 */
const User &Party::getHost() const
{
    return host;
}

/**
 * @brief returns the guests of the party
 *
 * @return const QList<User>&
 */
const QList<User> &Party::getGuests() const
{
    return guests;
}

/**
 * @brief Returns the ID of the party
 *
 * @return int
 */
int Party::getPartyID() const
{
    return partyID;
}

const QString &Party::getPartyLocation() const
{
    return this->location;
}

/*
 * Public functions
 */

/**
 * @brief Adds a guest to the party
 *
 * @param guest
 */
void Party::addGuest(User guest){
    this->guests.append(guest);
}

/**
 * @brief Uses the current party object to create a new party in the database
 *
 */
void Party::createParty(){
    this->db = db->getInstance();

    this->query = QSqlQuery(db->getDatabase());

    this->query.prepare("INSERT INTO nodrama.Parties(name, date, affinity_grade, max_people, host_id, location) VALUES(:name, :date, :aff, :maxPeps, :host_id, :location");
    this->query.bindValue(":name", this->partyName);
    this->query.bindValue(":date", this->partyDate);
    this->query.bindValue(":aff", this->minAffinity);
    this->query.bindValue(":maxPeps", this->maxPeople);
    this->query.bindValue(":host_id", this->host.getId());
    this->query.bindValue(":location", this->location);

    this->query.exec();

    int partyId = this->query.lastInsertId().toInt();

    this->partyID=partyId;

    this->query.prepare("INSERT INTO nodrama.Guests(fk_party, fk_user) VALUES(:partyID, :guestID)");

    this->query.bindValue(":partyID", partyId);

    for(qsizetype i = 0; i<guests.size();++i){
        User guest = this->guests.at(i);
        this->query.bindValue(":guestID", guest.getId());

        query.exec();
    }
}

/**
 * @brief returns the party with the given ID in the database
 *
 * @param id The id of the party
 * @return Party
 */
Party Party::getPartyById(int id)
{
    Database* db=db->getInstance();

    QSqlQuery query=QSqlQuery(db->getDatabase());

    query.prepare("SELECT * FROM nodrama.Parties WHERE id_party = :id");
    query.bindValue(":id", id);

    query.exec();

    if(query.size()==1){
        return Party(
                    query.value(1).toString(),
                    QDateTime::fromString(query.value(2).toString()),
                    query.value(3).toInt(),
                    query.value(4).toInt(),
                    Party::getGuestsByPartyId(id),
                    *User::getUserById(query.value(5).toInt()),
                    query.value(6).toString()
                    );
    }

    return Party();
}

/**
 * @brief Returns the users of the party with the given ID
 *
 * @param id
 * @return QList<User>
 */
QList<User> Party::getGuestsByPartyId(int id)
{
    QList<User> guests = QList<User>();
    Database* db=db->getInstance();

    QSqlQuery query=QSqlQuery(db->getDatabase());

    query.prepare("SELECT * FROM nodrama.Guests WHERE fk_party = :id");

    query.exec();

    while(query.next()){
        guests.append(*User::getUserById(query.value(1).toInt()));
    }

    return guests;
}

/**
 * @brief Party::getPartiesForUser
 * @param user The user whose parties are requested
 * @return QList<Party> The list of parties to which the user has been invited
 */
QList<Party> Party::getPartiesForUser(User *user)
{
    int userID=user->getId();
    QList<Party> parties = QList<Party>();

    Database* db=db->getInstance();

    QSqlQuery query=QSqlQuery(db->getDatabase());

    query.prepare("SELECT name, date, affinity_grade, max_people, host_id, location FROM Parties, Guests WHERE Parties.id_party=Guests.fk_party AND Guests.fk_user = :id");

    query.bindValue(":id", userID);

    query.exec();

    qDebug()<<query.size();
    qDebug()<<query.lastError();

    return parties;
}
