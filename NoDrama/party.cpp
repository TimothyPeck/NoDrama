#include "party.h"

/*
 * Constructors
 */

/**
 * @brief Party::Party Construct a new empty Party object
 */
Party::Party(){

}

/**
 * @brief Party::Party Construct a new Party object
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

    this->guests=QList<User>();

    for(qsizetype i=0;i<predeterminedGuests.size();++i){
        this->guests.append(predeterminedGuests.at(i));
    }

    this->host = host;

    this->createParty();
}

/**
 * @brief Party::Party Construct a new Party object
 * @param name The name of the party
 * @param dateTime The date and time of the party
 * @param minAffinity The minimum affinity required to be invited to the party
 * @param maxPeople The maximum number of people that can be invited to the party
 * @param predeterminedGuests The guests that the host has decided must be invited, does not follow the minAffinity of the party
 * @param futureHost The user obect of the host of the party
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

    this->guests=QList<User>();

    for(qsizetype i=0;i<predeterminedGuests.size();++i){
        this->guests.append(predeterminedGuests.at(i));
    }

    this->host = futureHost;
}

/**
 * @brief Party::Party Construct a new Party object from another Party object
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
 * @param party The party to copy
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
 * @brief Party::~Party Destroy the Party object
 */
Party::~Party(){
    //free(db);
}

/*
 * Getters
 */

/**
 * @brief Party::getPartyName Returns the name of the party
 * @return const QString& The name of the party
 */
const QString &Party::getPartyName() const
{
    return partyName;
}

/**
 * @brief Party::getPartyDate returns the date and time of the party
 * @return const QDateTime& The date and time of the party
 */
const QDateTime &Party::getPartyDate() const
{
    return partyDate;
}

/**
 * @brief Party::getPartyDateString Returns a string of the date part of the party
 * @return  QString The date part of the party
 */
const QString Party::getPartyDateString() const
{
    return this->partyDate.date().toString("ddd dd MMMM yyyy");
}

/**
 * @brief Party::getPartyTimeString Returns a string of the time part of the party
 * @return QString The time of the party
 */
const QString Party::getPartyTimeString() const
{
    return this->partyDate.time().toString("hh:mm ap");
}

/**
 * @brief Party::getMinAffinity Returns the minimum affinity required to be invited to the party
 * @return int The minimum affinity required to be invited to the party
 */
int Party::getMinAffinity() const
{
    return minAffinity;
}

/**
 * @brief Party::getMaxPeople Returns the maximum number of people that can be invited to the party
 * @return int The maximum number of people that can be invited to the party
 */
int Party::getMaxPeople() const
{
    return maxPeople;
}

/**
 * @brief Party::getHost Returns the user object of the host of the party
 * @return const User* The user object of the host of the party
 */
const User &Party::getHost() const
{
    return host;
}

/**
 * @brief Party::getHostID Returns the id of the host of the party
 * @return  int Party host id
 */
const int Party::getHostID()
{
    return this->host.getId();
}

/**
 * @brief Party::getGuests Returns the guests of the party
 * @return const QList<User>& The guests of the party
 */
const QList<User> &Party::getGuests() const
{
    return guests;
}

/**
 * @brief Party::getGuestUsernames Returns all the usernames of the guests
 * @return QList<QString> The usernames of the guests
 */
const QList<QString> Party::getGuestUsernames()
{
    QList<QString> usernames=QList<QString>();
    for(User& u : guests){
        usernames.append(u.getUsername());
    }
    return usernames;
}

/**
 * @brief Party::getPartyId Returns the ID of the party
 * @return int Party id
 */
int Party::getPartyID() const
{
    return partyID;
}

/**
 * @brief Party::getPartyLocation Returns the location a the party
 * @return QString The location of the party
 */
const QString &Party::getPartyLocation() const
{
    return this->location;
}

/*
 * Public functions
 */

/**
 * @brief Party::addGuest Adds a guest to the party
 * @param guest User to add to the guests
 */
void Party::addGuest(User guest){
    this->guests.append(guest);
}

/**
 * @brief Party::addOrRemoveGuest If the guest is in the guest list, it will be removed. Otherwise it will be added to the guest list. Function used by the GUI.
 * @param name Name of the guest
 */
void Party::addOrRemoveGuest(QString name)
{
    for(int i = 0; i < this->guests.size(); ++i)
    {
        if(guests.at(i).getUsername() == name)
        {
            guests.remove(i);
            return;
        }
    }
    this->guests.append(User::getUserByUsername(name));
}

/**
 * @brief Party::isFriendInGuest Determine if a friend is also a guest
 * @param name Name of the guest
 * @return bool Return is a friend is in the guests of the party
 */
bool Party::isFriendInGuest(QString name)
{
    for(int i = 0; i < this->guests.size(); ++i)
    {
        if(guests.at(i).getUsername() == name)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Party::getGuestsForDisplay Return a list of the guests to display in GUI
 * @return QVariantList Returns a QVariantList of the guests usernames
 */
QVariantList Party::getGuestsForDisplay()
{
    QVariantList *list = new QVariantList();

    for(int i = 0; i < this->guests.size(); ++i)
    {
        *list << guests.at(i).getUsername();
    }

    return *list;
}

/**
 * @brief Party::createParty Uses the current party object to create a new party in the database
 */
void Party::createParty(){
    Database *db = Database::getInstance();

    if (!db->isOpen())
        db->openDatabase();

    QString dateTime = this->partyDate.date().toString("yyyy-MM-dd") + " " + this->partyDate.time().toString("hh:mm:s");
    qDebug() << dateTime;

    db->getDatabase().transaction();

    this->query.prepare("INSERT INTO nodrama.parties (name,date,affinity_grade,max_people,host_id,location) VALUES (:name,:date, :aff, :maxPers, :host_id, :loc);");
    this->query.bindValue(":name", this->partyName);
    this->query.bindValue(":date", dateTime);
    this->query.bindValue(":aff", this->minAffinity);
    this->query.bindValue(":maxPers", this->maxPeople);
    this->query.bindValue(":host_id", this->host.getId());
    this->query.bindValue(":loc", this->location);

    this->query.exec();

    qDebug() << this->query.lastError();

    int partyId = this->query.lastInsertId().toInt();

    this->partyID=partyId;

    this->query.prepare("INSERT INTO nodrama.guests (fk_party, fk_user) VALUES (:partyID, :guestID)");

    this->query.bindValue(":partyID", partyId);

    for(qsizetype i = 0; i<guests.size();++i){
        User guest = this->guests.at(i);
        this->query.bindValue(":guestID", guest.getId());

        query.exec();

        qDebug() << this->query.lastError();
    }
    db->getDatabase().commit();
}

/**
 * @brief Party::getPartyById returns the party with the given ID in the database
 * @param id The id of the party
 * @return Party The party corresponding to the if
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
 * @brief Party::getGuestsByPartyId Returns the users of the party with the given ID
 * @param id The id of the party
 * @return QList<User> The list of the party's guests
 */
QList<User> Party::getGuestsByPartyId(int id)
{
    QList<User> guests = QList<User>();
    Database* db=db->getInstance();

    QSqlQuery query=QSqlQuery(db->getDatabase());

    query.prepare("SELECT nodrama.Guests.fk_user FROM nodrama.Guests WHERE fk_party = :id");

    query.bindValue(":id", id);

    query.exec();

    while(query.next()){
        guests.append(User::getUserById(query.value(0).toInt()));
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
    query.prepare("SELECT DISTINCT name, date, affinity_grade, max_people, host_id, location, id_party FROM nodrama.Parties, nodrama.Guests WHERE Parties.id_party=Guests.fk_party AND (Guests.fk_user = :id OR Parties.host_id = :id)");

    query.bindValue(":id", userID);

    query.exec();

    while(query.next()){
        QDateTime partyDate = query.value(1).toDateTime();
        QList<User> guests = Party::getGuestsByPartyId(query.value(6).toInt());
        parties->append(Party(query.value(0).toString(), partyDate, query.value(2).toInt(), query.value(3).toInt(), guests, User::getUserById(query.value(4).toInt()), query.value(5).toString()));
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
    QList<int> partyIDs = QList<int>();

    Database* db=db->getInstance();

    QSqlQuery query=QSqlQuery(db->getDatabase());

    if(!db->isOpen())
        db->openDatabase();

    query.prepare("SELECT DISTINCT id_party FROM nodrama.Parties, nodrama.Guests WHERE Parties.id_party=Guests.fk_party AND (Guests.fk_user = :id OR Parties.host_id = :id)");

    query.bindValue(":id", userID);

    query.exec();

    while(query.next()){
        qDebug()<<"Current party id: "<<query.value(0).toInt();
        partyIDs.append(query.value(0).toInt());
    }

    return partyIDs;
}

/**
 * @brief Party::determineGuests Determines the guests for this party, may take a while with larger parties
 */
void Party::determineGuests()
{
    QList<User> guests = this->guests;

    bool canContinue = true;
    guests.push_front(this->host);
    qDebug() << "Host : " << this->host.getUsername();

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
