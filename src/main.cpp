#include <bits/stdc++.h>
#include "graph/Graph.hpp"
using namespace std;

int main() {
    Graph g;
    int choice;
    string u1, u2, uname;

    while (true) {
        cout << "\n===== Social Graph Menu =====\n";
        cout << "1. Add User\n";
        cout << "2. Remove User\n";
        cout << "3. Add Friendship\n";
        cout << "4. Remove Friendship\n";
        cout << "5. Display All Users\n";
        cout << "6. Get Friends of a User\n";
        cout << "7. Get Mutual Friends\n";
        cout << "8. Check Connection (via BFS)\n";
        cout << "9. Compute PageRank\n";
        cout << "10. Recommend Friends\n";
        cout << "11. Clear Graph\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter username: ";
                cin >> uname;
                cout << (g.addUser(uname) ? " User added!\n" : "  User already exists.\n");
                break;

            case 2:
                cout << "Enter username: ";
                cin >> uname;
                cout << (g.removeUser(uname) ? " User removed.\n" : "  User not found.\n");
                break;

            case 3:
                cout << "Enter two usernames: ";
                cin >> u1 >> u2;
                cout << (g.addFriendship(u1, u2) ? "Friendship added!\n" : "  Error adding friendship.\n");
                break;

            case 4:
                cout << "Enter two usernames: ";
                cin >> u1 >> u2;
                cout << (g.removeFriendship(u1, u2) ? "Friendship removed.\n" : "  Error removing friendship.\n");
                break;

            case 5:
                g.displayAllUsers();
                break;

            case 6: {
                cout << "Enter username: ";
                cin >> uname;
                auto friends = g.getFriends(uname);
                if (friends.empty()) cout << "  No friends or user not found.\n";
                else {
                    cout << "Friends of " << uname << ": ";
                    for (auto &f : friends) cout << f << " ";
                    cout << "\n";
                }
                break;
            }

            case 7: {
                cout << "Enter two usernames: ";
                cin >> u1 >> u2;
                auto mutual = g.getMutualFriends(u1, u2);
                if (mutual.empty()) cout << "  No mutual friends.\n";
                else {
                    cout << "Mutual friends: ";
                    for (auto &f : mutual) cout << f << " ";
                    cout << "\n";
                }
                break;
            }

            case 8:
                cout << "Enter two usernames: ";
                cin >> u1 >> u2;
                cout << (g.areConnected(u1, u2)
                         ? "They are connected!\n"
                         : " No connection found.\n");
                break;

            case 9:
                g.computePageRank();
                g.displayPageRank();
                break;

            case 10:
                cout << "Enter username for recommendation: ";
                cin >> uname;
                g.recommendFriends(uname, 3);
                break;

            case 11:
                g.clear();
                break;

            case 0:
                cout << "Saving data before exit...\n";
                g.save();  // persist current graph without clearing
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "  Invalid choice.\n";
        }
    }
}