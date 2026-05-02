# Online Food Order Management System

An Online Food Order Management System is a digital platform that organizes, processes, and prioritizes customer food orders efficiently to reduce delays and improve service.


## Developers
**The 3 Errors and 1 Solution**

=============================================

Online Food Order Management System
1. ➕ Add Normal Order  
2. ⭐ Add Priority Order  
3. ⚙️ Process Order  
4. 📋 View Queues  
5. 🕘 View Order History  
6. ↩️ Undo Last Order  
7. ❌ Exit Program  

Enter choice:

Enter customer name:

Enter food item:

Normal order added.

=============================================

## Purpose

This project aims to:
- Improve order handling during busy hours  
- Reduce confusion and delays  
- Allow prioritization of urgent orders  
- Provide a simple and efficient ordering flow

  ## System Concept

This system uses basic programming logic and data structures:

- **Queue (FIFO)** → Handles normal orders  
- **Priority Queue** → Handles urgent orders first  
- **Stack** → Stores last action for undo  
- **Loops & Conditions** → Controls system flow  

```cpp
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
void undoOrder() {
    if (!history.empty()) {
        Order o = history.top();
        history.pop();
        if (o.priority > 0) {
            priorityQueue.push(o);
        } else {
            normalQueue.push(o);
        }
        cout << "Undid order: " << o.customer_Name << " - " << o.food_Item << "\n";
    } else {
        cout << "No orders to undo.\n";
    }
}
int main() {
    int choice;
    do {
        cout << "\nOnline Food Order Management System\n";
        cout << "1. Add Normal Order\n";
        cout << "2. Add Priority Order\n";
        cout << "3. Process Order\n";
        cout << "4. View Queues\n";
        cout << "5. View History\n";
        cout << "6. Undo Last Order\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addNormal();
                break;
            case 2:
                addPriority();
                break;
            case 3:
                processOrder();
                break;
            case 4:
                viewQueues();
                break;
            case 5:
                viewHistory();
                break;
            case 6:
                undoOrder();
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}
```
