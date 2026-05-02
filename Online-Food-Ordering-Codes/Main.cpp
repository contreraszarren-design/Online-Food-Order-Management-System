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

// Add normal order
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