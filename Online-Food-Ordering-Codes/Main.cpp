#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

struct Order {
    int id;
    string customer_Name;
    string food_Item;
    int priority;
};

struct CompareOrder {
    bool operator()(const Order &a, const Order &b) const {
        return a.priority < b.priority;
    }
};

queue<Order> normalQueue;
priority_queue<Order, vector<Order>, CompareOrder> priorityQueue;
stack<Order> history;

int orderID = 1;


void addNormal() {
    Order o;
    o.id = orderID++;
    cout << "Enter customer name: ";
    cin >> o.customer_Name;
    cout << "Enter food item: ";
    cin >> o.food_Item;
    o.priority = 0;

    normalQueue.push(o);
    cout << "Normal order added.\n";
}

void addPriority() {
    Order o;
    o.id = orderID++;
    cout << "Enter customer name: ";
    cin >> o.customer_Name;
    cout << "Enter food item: ";
    cin >> o.food_Item;
    cout << "Enter priority (higher number = higher priority): ";
    cin >> o.priority;

    priorityQueue.push(o);
    cout << "Priority order added.\n";
}

void processOrder() {
    if (!priorityQueue.empty()) {
        Order o = priorityQueue.top();
        priorityQueue.pop();
        history.push(o);
        cout << "Processed priority order: " << o.customer_Name << " - " << o.food_Item << "\n";
    } else if (!normalQueue.empty()) {
        Order o = normalQueue.front();
        normalQueue.pop();
        history.push(o);
        cout << "Processed normal order: " << o.customer_Name << " - " << o.food_Item << "\n";
    } else {
        cout << "No orders to process.\n";
    }
}

void viewQueues() {
    cout << "Normal Queue:\n";
    queue<Order> temp = normalQueue;
    while (!temp.empty()) {
        Order o = temp.front();
        temp.pop();
        cout << "ID: " << o.id << ", Customer: " << o.customer_Name << ", Food: " << o.food_Item << "\n";
    }

    cout << "Priority Queue:\n";
    priority_queue<Order, vector<Order>, CompareOrder> tempP = priorityQueue;
    while (!tempP.empty()) {
        Order o = tempP.top();
        tempP.pop();
        cout << "ID: " << o.id << ", Customer: " << o.customer_Name << ", Food: " << o.food_Item << ", Priority: " << o.priority << "\n";
    }
}

void viewHistory() {
    cout << "Order History:\n";
    stack<Order> temp = history;
    while (!temp.empty()) {
        Order o = temp.top();
        temp.pop();
        cout << "ID: " << o.id << ", Customer: " << o.customer_Name << ", Food: " << o.food_Item << "\n";
    }
}
