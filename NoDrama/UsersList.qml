import QtQuick 2.0
import QtQuick.Controls 2.15
import com.myself 1.0

Container {
    ListModel {
        id: usersListModel

        Component.onCompleted: {
            update();
        }
    }

    function createListElement(n, a){
        return {
            name: n,
            affi: a
        }
    }

    function justOneElement(n, a){
        usersListModel.clear();
        usersListModel.append(createListElement(n,a));
    }

    function update(){
        var friends = currentUser.getFriends();
        for(var friend in friends){
            console.log(friend);
        }
    }
}


