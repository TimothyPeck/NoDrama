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
Party::Party(int id, QString name, QDateTime dateTime, int minAffinity, int maxPeople, QList<User> predeterminedGuests, User futureHost, QString location)
{
    this->partyID=id;
    this->partyName=name;
    this->partyDate=dateTime;
    this->minAffinity=minAffinity;
    this->maxPeople=maxPeople;
    this->location=location;

    this->guests=QList<User>(maxPeople);

    for(qsizetype i=0;i<predeterminedGuests.size();++i){
        this->guests.append(predeterminedGuests.at(i));
    }

    this->host = futureHost;
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
 * @brief Party::constructor Same as copy constructor @see Party(const Party&)
 * @param party
 */
void Party::constructor(Party *party)
{
    this->partyDate=party->partyDate;
    this->partyName=party->partyName;
    this->guests=party->guests;
    this->host=party->host;
    this->maxPeople=party->maxPeople;
    this->minAffinity=party->minAffinity;
    this->location=party->location;
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
 * @return const User*
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
Party* Party::getPartyById(int id)
{
    Party* part = nullptr;
    Database* db=db->getInstance();

    QSqlQuery query=QSqlQuery(db->getDatabase());

    if(!db->isOpen())
        db->openDatabase();

    query.prepare("SELECT * FROM nodrama.Parties WHERE id_party = :id");
    query.bindValue(":id", id);

    query.exec();

    if(query.size()==1){
        query.first();
        QList<User> guests = Party::getGuestsByPartyId(id);
        User currHost=User::getUserById(query.value(5).toInt());
        return new Party(
                    id,
                    query.value(1).toString(),
                    query.value(2).toDateTime(),
                    query.value(3).toInt(),
                    query.value(4).toInt(),
                    guests,
                    currHost,
                    query.value(6).toString()
                    );
    }
    return nullptr;
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
        guests.append(User::getUserById(query.value(1).toInt()));
    }

    return guests;
}

/**
 * @brief Party::getPartiesForUser
 * @param user The user whose parties are requested
 * @return QList<Party> The list of parties to which the user has been invited
 */
QList<Party>* Party::getPartiesForUser(User *user)
{
    int userID=user->getId();
    QList<Party>* parties = new QList<Party>();

    Database* db=db->getInstance();

    QSqlQuery query=QSqlQuery(db->getDatabase());

    if(!db->isOpen())
        db->openDatabase();
    //                          0     1         2               3       4           5
    query.prepare("SELECT name, date, affinity_grade, max_people, host_id, location FROM nodrama.Parties, nodrama.Guests WHERE Parties.id_party=Guests.fk_party AND Guests.fk_user = :id");

    query.bindValue(":id", userID);

    query.exec();

    while(query.next()){
        QDateTime partyDate = query.value(1).toDateTime();
        QList<User> guests = QList<User>();
        parties->append(Party(query.value(0).toString(),partyDate, query.value(2).toInt(), query.value(3).toInt(), guests, User::getUserById(query.value(4).toInt()), query.value(5).toString()));
    }

    return parties;
}

/**
 * @brief Party::getPartyIdsForUser returns a list of the IDs of the parties to which a user is invited
 * @param user The invited user
 * @return QList<int> The list of ids of the parties to which to userr is inveited
 */
QList<int> Party::getPartyIdsForUser(User *user)
{
    int userID=user->getId();
    QList<int> parties = QList<int>();

    Database* db=db->getInstance();

    QSqlQuery query=QSqlQuery(db->getDatabase());

    if(!db->isOpen())
        db->openDatabase();

    query.prepare("SELECT id_party FROM nodrama.Parties, nodrama.Guests WHERE Parties.id_party=Guests.fk_party AND Guests.fk_user = :id");

    query.bindValue(":id", userID);

    query.exec();

    while(query.next()){
        parties.append(query.value(0).toInt());
    }

    return parties;
}

/**
 * @brief Party::determineGuests Determines the guests for this party, may take a while with larger parties
 */
void Party::determineGuests()
{
    QList<User> guests = this->guests;
    //User *priorUser=nullptr;

    bool canContinue = true;
    guests.push_front(this->host);
    //delete host;

    // Boucle tant qu'on a pas le nombre d'invités requis sans compter l'hôte
    //while (guests.length() < this->getMaxPeople() + 1 && canContinue)
    //{
    // Boucle sur chaque invité -> prendre un nouvel invité
    for (int i = 0; i < guests.length(); i++)
    {
        if(guests.length() < maxPeople + 1)
        {
            User currentGuest = guests.at(i); // orga
            QMap<User, int> friends = currentGuest.getFriendsByAffinity(minAffinity); //liste d'amis de orga
            QMapIterator<User, int> friendsIterator(friends);


            User *maxAverageUser=new User();
            double maxAverage = 0;


            // Boucle sur chaque ami de l'invité qui a l'affinité minimum
            while (friendsIterator.hasNext())
            {
                friendsIterator.next();
                User currentGuestFriend = friendsIterator.key(); // lui c'est A, premier ami de orga

                //check si les l'ami qu'on check est déjà invité à la fête
                // si pas cinfiance en contains
                bool guestContainFriend = false;
                for(int i = 0; guests.length() > i ; i++)
                {
                    if(guests.at(i) == currentGuestFriend)
                    {
                        guestContainFriend = true;
                    }
                }


                // std::cout<<guests.contains(currentGuestFriend)<<std::endl;

                // Si l'ami n'est pas déjà invité
                if (guestContainFriend == false)
                {
                    int sum = friendsIterator.value(), count=1; // --> on va calculer la moyenne de A
                    // Pour chaque invité -> calculer la moyenne de l'ami
                    for (int i = 0; i < guests.length(); i++)
                    {
                        User currentFriend = guests.at(i);

                        QMap<User, int> currentFriendFriends = currentFriend.getFriendsByAffinity(this->getMinAffinity()); //liste d'ami d'orga

                        QMapIterator<User, int> currentFriendFriendsIterator(currentFriendFriends);

                        while (currentFriendFriendsIterator.hasNext()) //boucle sur liste d'amis d'orga
                        {
                            currentFriendFriendsIterator.next();

                            User thisFriend = currentFriendFriendsIterator.key();

                            if(thisFriend!=currentGuestFriend){

                                QMap<User, int> *thisFriendFriends = thisFriend.getFriends(); // list ami de thisFriendFriends

                                //std::cout<<"\tKnown friends count for "<<thisFriend.getUsername()<<" : "<<thisFriendFriends->count()<<std::endl;

                                //std::cout<<"\tthisFriend "<<thisFriend.getUsername()<< ", CurrentGuestFriend : "<<currentGuestFriend.getUsername()<<std::endl;

                                QMapIterator<User, int> thisFriendFriendsIterator(*thisFriendFriends);

                                if(thisFriend!=currentGuest)
                                {
                                    while(thisFriendFriendsIterator.hasNext()){
                                        thisFriendFriendsIterator.next();
                                        User thisFriendFriendsIteratorKey=thisFriendFriendsIterator.key();
                                        if(thisFriendFriendsIteratorKey==currentGuestFriend ){
                                            sum += thisFriendFriendsIterator.value();
                                            count++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    double averageAffinity = count > 0 ? (double)sum / (double)count : 0; //sum > 0 ? sum / knownFriends.count() : 0;

                    // Test si le current friend est plus un bon ami que le maxAverageUser
                    if (averageAffinity > maxAverage)
                    {
                        maxAverage = averageAffinity;
                        maxAverageUser = new User(currentGuestFriend);
                    }
                }
            }
            User testUser = User();

            if (*maxAverageUser != testUser)
            {
                if (!guests.contains(*maxAverageUser))
                    guests.append(*maxAverageUser);
            }

            delete maxAverageUser;
        }
    }
    guests.removeOne(host);
    this->guests=guests;
}
