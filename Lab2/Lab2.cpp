#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct node
{
    string Town;
    int key;
    list<string> TownList;
    map<pair<string, string>, double> Distances;
};

void addTownToList(node* n, const string& town) {
    n->TownList.push_back(town);

    for (const string& existingTown : n->TownList) {
        if (existingTown != town) {
            double distance;
            cout << "Введите расстояние от " << existingTown << " до " << town << ": ";
            cin >> distance;
            n->Distances[{existingTown, town}] = distance;
            n->Distances[{town, existingTown}] = distance;
        }
    }
}

void removeTown(node* n, const string& town) {
    n->TownList.remove(town);

    for (auto it = n->Distances.begin(); it != n->Distances.end();) {
        if (it->first.first == town || it->first.second == town) {
            it = n->Distances.erase(it);
        }
        else {
            ++it;
        }
    }
}

void OutPutScreen(const node* n) {
    for (const string& town : n->TownList) {
        cout << town << endl;
    }
}

void findAllPaths(const node* n, const string& startTown, const string& currentTown, const string& endTown, double distance, vector<string>& path, vector<pair<vector<string>, double>>& allPaths, unordered_set<string>& visited) {
    if (currentTown == endTown) {
        allPaths.push_back({ path, distance });
        return;
    }

    visited.insert(currentTown);
    path.push_back(currentTown);

    for (const auto& entry : n->Distances) {
        if (entry.first.first == currentTown && visited.find(entry.first.second) == visited.end()) {
            findAllPaths(n, startTown, entry.first.second, endTown, distance + entry.second, path, allPaths, visited);
        }
    }

    path.pop_back();
    visited.erase(currentTown);
}

void showAllPaths(const node* n, const string& startTown, const string& finalTown) {
    vector<pair<vector<string>, double>> allPaths;
    unordered_set<string> visited;
    vector<string> path;
    double distance = 0.0;

    findAllPaths(n, startTown, startTown, finalTown, distance, path, allPaths, visited);

    if (allPaths.empty()) {
        cout << "Нет путей от " << startTown << " до " << finalTown << endl;
    }
    else {
        cout << "Все возможные пути от " << startTown << " до " << finalTown << " :" << endl;
        for (const auto& pathData : allPaths) {
            cout << "Путь: ";
            for (const string& town : pathData.first) {
                cout << town << " -> ";
            }
            cout << "расстояние: " << pathData.second << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "");

    node* myNode = new node();
    myNode->key = 1;
    myNode->Town = "";

    int choice;
    char townToAdd[100];
    string startTown;
    string finalTown;
    while (true) {
        cout << "Меню:" << endl;
        cout << "1. Добавить город в список" << endl;
        cout << "2. Вывести все возможные пути от города до других" << endl;
        cout << "3. Вывод на экран" << endl;
        cout << "4. Удалить город и связи с ним" << endl;
        cout << "5. Выйти из программы" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите название города для добавления в список: ";
            cin >> townToAdd;
            addTownToList(myNode, townToAdd);
            break;
        case 2:
            cout << "Введите название города до города чтоб увидеть дистанцию: ";
            cin >> startTown;
            cin >> finalTown;
            showAllPaths(myNode, startTown,finalTown);
            break;
        case 3:
            cout << "Города в списке:" << endl;
            OutPutScreen(myNode);
            break;
        case 4:
            cout << "Введите название города для удаления: ";
            cin >> townToAdd;
            removeTown(myNode, townToAdd);
            cout << "Город " << townToAdd << " удален из списка." << endl;
            break;
        case 5:
            cout << "Программа завершена." << endl;
            delete myNode;
            return 0;
        default:
            cout << "Неверный ввод. Попробуйте снова." << endl;
            break;
        }
    }

    return 0;
}