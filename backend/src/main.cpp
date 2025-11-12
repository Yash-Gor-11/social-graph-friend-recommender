#include <bits/stdc++.h>
#include "graph/Graph.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    
    bool silentMode = false;
    
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg.rfind("--", 0) == 0) { // if any CLI flag starts with --
            silentMode = true;
            break;
        }
    }
    
    Graph g(silentMode);

    // g.loadwithhashes();   // ensure graph loads from dataset/users.csv or users_demo.csv

    // // ─────────────────────────────────────────────────────────────
    //  FRONTEND / AUTOMATION  MODE  (argument-based)
    // ─────────────────────────────────────────────────────────────
    if (argc >= 2) {
        string cmd = argv[1];
        
        if(cmd == "--search" && argc >= 3) {
            string prefix = argv[2];
            auto results = g.searchPrefix(prefix);
            for(size_t i=0;i<results.size();++i) {
                cout << results[i];
                if(i + 1 < results.size()) std::cout << ",";
            }
            cout << endl;
            return 0;
        }
        
        if (cmd == "--add" && argc == 3) {
            string user = argv[2];
            cout << (g.addUser(user) ? "Added user: " + user
                                     : "User already exists.") << endl;
            g.save();
            return 0;
        }

        if (cmd == "--remove" && argc == 3) {
            string user = argv[2];
            cout << (g.removeUser(user) ? "Removed user: " + user
                                        : "User not found.") << endl;
            g.save();
            return 0;
        }

        if (cmd == "--addFriend" && argc == 4) {
            string u1 = argv[2], u2 = argv[3];
            cout << (g.addFriendship(u1, u2)
                     ? "Friendship added between " + u1 + " and " + u2
                     : "Error adding friendship.") << endl;
            g.save();
            return 0;
        }

        if (cmd == "--removeFriend" && argc == 4) {
            string u1 = argv[2], u2 = argv[3];
            cout << (g.removeFriendship(u1, u2)
                     ? "Friendship removed between " + u1 + " and " + u2
                     : "Error removing friendship.") << endl;
            g.save();
            return 0;
        }

        if (cmd == "--friends" && argc == 3) {
            string uname = argv[2];
            auto friends = g.getFriends(uname);
            if (friends.empty()) cout << "No friends or user not found.\n";
            else {
                cout << "Friends of " << uname << ": ";
                for (auto &f : friends) cout << f << " ";
                cout << endl;
            }
            return 0;
        }

        if (cmd == "--mutual" && argc == 4) {
            string u1 = argv[2], u2 = argv[3];
            auto mutual = g.getMutualFriends(u1, u2);
            if (mutual.empty()) cout << "No mutual friends.\n";
            else {
                cout << "Mutual friends of " << u1 << " & " << u2 << ": ";
                for (auto &f : mutual) cout << f << " ";
                cout << endl;
            }
            return 0;
        }

        if (cmd == "--connection" && argc == 4) {
            string u1 = argv[2], u2 = argv[3];
            cout << (g.areConnected(u1, u2)
                     ? "Connected: Yes"
                     : "Connected: No") << endl;
            return 0;
        }

        if (cmd == "--pagerank") {
            g.computePageRank();
            g.displayPageRank();
            return 0;
        }

        if (cmd == "--recommend" && argc == 3) {
            string uname = argv[2];
            g.recommendFriends(uname, 3);
            return 0;
        }

        if (cmd == "--clear") {
            g.clear();
            g.save();
            cout << "Graph cleared.\n";
            return 0;
        }

        if (cmd == "--exit") {
            cout << "Exiting...\n";
            return 0;
        }

        cout << "Unknown command.\n";
        return 0;
    }

    // ─────────────────────────────────────────────────────────────
    //  INTERACTIVE CLI MENU  (your existing Phase-2.5 interface)
    // ─────────────────────────────────────────────────────────────
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
                cout << (g.addUser(uname) ? "User added!\n" : "User already exists.\n");
                break;

            case 2:
                cout << "Enter username: ";
                cin >> uname;
                cout << (g.removeUser(uname) ? "User removed.\n" : "User not found.\n");
                break;

            case 3:
                cout << "Enter two usernames: ";
                cin >> u1 >> u2;
                cout << (g.addFriendship(u1, u2) ? "Friendship added!\n" : "Error adding friendship.\n");
                break;

            case 4:
                cout << "Enter two usernames: ";
                cin >> u1 >> u2;
                cout << (g.removeFriendship(u1, u2) ? "Friendship removed.\n" : "Error removing friendship.\n");
                break;

            case 5:
                g.displayAllUsers();
                break;

            case 6: {
                cout << "Enter username: ";
                cin >> uname;
                auto friends = g.getFriends(uname);
                if (friends.empty()) cout << "No friends or user not found.\n";
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
                if (mutual.empty()) cout << "No mutual friends.\n";
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
                         : "No connection found.\n");
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
                g.save();
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }
}
