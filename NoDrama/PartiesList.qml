import QtQuick 2.0
import QtQuick.Controls 2.15
import com.myself 1.0

Container{
    Party{
        id: party
    }
    ListModel {

        /*function createListParty(part){
        return{
            name: part.getPartyName(),
            date: part.getPartyDate(),
            time: part.getPartyDate(),
            organiser: part.getPartyHost().getUsername(),
            place: part.getPartyLocation()
        };
    }

        Component.onCompleted: {
            console.log("Enter PartiesList")
            var parties = party.getPartiesForUser(currentUser)
            /*for(var part in parties){
            console.log(part.getPartyName())
            append(createListParty(part))
        }
        }*/

        ListElement {
            name: "Nom de la soirée"
            date: "01.01.1970"
            time: "23:00"
            organiser: "Organisateur"
            place: "Lieu"
        }
        ListElement {
            name: "Nom de la soirée"
            date: "01.01.1970"
            time: "23:00"
            organiser: "Organisateur"
            place: "Lieu"
        }
        ListElement {
            name: "Nom de la soirée"
            date: "01.01.1970"
            time: "23:00"
            organiser: "Organisateur"
            place: "Lieu"
        }
        ListElement {
            name: "Nom de la soirée"
            date: "01.01.1970"
            time: "23:00"
            organiser: "Organisateur"
            place: "Lieu"
        }
        ListElement {
            name: "Nom de la soirée"
            date: "01.01.1970"
            time: "23:00"
            organiser: "Organisateur"
            place: "Lieu"
        }
        ListElement {
            name: "Nom de la soirée"
            date: "01.01.1970"
            time: "23:00"
            organiser: "Organisateur"
            place: "Lieu"
        }
        ListElement {
            name: "Nom de la soirée"
            date: "01.01.1970"
            time: "23:00"
            organiser: "Organisateur"
            place: "Lieu"
        }
    }
}
