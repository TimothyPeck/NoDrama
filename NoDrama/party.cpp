#include "party.h"

/*
 * Constructors
 */

Party::Party(){

}

Party::Party(QString name, QDateTime dateTime, int minAffinity, int maxPeople, QList<User> predeterminedGuests, User host)
{
    this->partyName=name;
    this->partyDate=dateTime;
    this->minAffinity=minAffinity;
    this->maxPeople=maxPeople;

    this->guests=QList<User>(maxPeople);

    for(qsizetype i=0;i<predeterminedGuests.size();++i){
        this->guests.append(predeterminedGuests.at(i));
    }

    this->host = host;
}

Party::Party(const Party& party){
    this->partyDate=party.partyDate;
    this->partyName=party.partyName;
    this->guests=party.guests;
    this->host=party.host;
    this->maxPeople=party.maxPeople;
    this->minAffinity=party.minAffinity;
}

Party::~Party(){
    //free(db);
}

/*
 * Getters
 */

const QString &Party::getPartyName() const
{
    return partyName;
}

const QDateTime &Party::getPartyDate() const
{
    return partyDate;
}

int Party::getMinAffinity() const
{
    return minAffinity;
}

int Party::getMaxPeople() const
{
    return maxPeople;
}

const User &Party::getHost() const
{
    return host;
}

const QList<User> &Party::getGuests() const
{
    return guests;
}

int Party::getPartyID() const
{
    return partyID;
}

/*
 * Public functions
 */

void Party::addGuest(User guest){
    this->guests.append(guest);
}

void Party::createParty(){
    this->db = db->getInstance();

    this->query = QSqlQuery(db->getDatabase());

    this->query.prepare("INSERT INTO Parties(name, date, affinity_grade, max_people, host_id) VALUES(:name, :date, :aff, :maxPeps, :host_id");
    this->query.bindValue(":name", this->partyName);
    this->query.bindValue(":date", this->partyDate);
    this->query.bindValue(":aff", this->minAffinity);
    this->query.bindValue(":maxPeps", this->maxPeople);
    this->query.bindValue(":host_id", this->host.getId());

    this->query.exec();

    int partyId = this->query.lastInsertId().toInt();

    this->partyID=partyId;

    this->query.prepare("INSERT INTO Guests(fk_party, fk_user) VALUES(:partyID, :guestID)");

    this->query.bindValue(":partyID", partyId);

    for(qsizetype i = 0; i<guests.size();++i){
        User guest = this->guests.at(i);
        this->query.bindValue(":guestID", guest.getId());

        query.exec();
    }
}

Party Party::getPartyById(int id)
{
    Database* db=db->getInstance();

    QSqlQuery query=QSqlQuery(db->getDatabase());

    query.prepare("SELECT * FROM Parties WHERE id_party = :id");
    query.bindValue(":id", id);

    query.exec();

    if(query.size()==1){
        return Party(
                    query.value(1).toString(),
                    QDateTime::fromString(query.value(2).toString()),
                    query.value(3).toInt(),
                    query.value(4).toInt(),
                    Party::getGuestsByPartyId(id),
                    User::getUserById(query.value(5).toInt())
                );
    }

    return Party();
}

QList<User> Party::getGuestsByPartyId(int id)
{
    QList<User> guests = QList<User>();
    Database* db=db->getInstance();

    QSqlQuery query=QSqlQuery(db->getDatabase());

    query.prepare("SELECT * FROM Guests WHERE fk_party = :id");

    query.exec();

    while(query.next()){
        guests.append(User::getUserById(query.value(1).toInt()));
    }

    return guests;
}
