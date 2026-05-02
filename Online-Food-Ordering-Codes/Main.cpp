"""
Queue-Based Service Ticketing System (Priority Queue)
======================================================
Course: CC 102 - Advanced Computer Programming
Student: CONTRERAS, ZARREN E.
SR-Code: 25-04115
Section: CS-1206
Batangas State University - Alangilan Campus
"""

import heapq
import datetime

# ──────────────────────────────────────────────
# DATA STRUCTURES
# ──────────────────────────────────────────────

# Priority Queue (heap): stores tuples of (priority_level, timestamp, ticket_number)
# Lower number = higher priority (1 = highest, 4 = lowest)
priority_queue = []

# Dictionary: stores full ticket info keyed by ticket number
tickets = {}

# List: stores completed/served tickets as service history
service_history = []

# Global ticket counter
ticket_counter = 0

# Priority mapping
PRIORITY_LABELS = {
    1: "PWD",
    2: "Senior Citizen",
    3: "Pregnant",
    4: "Regular"
}

PRIORITY_MAP = {
    "1": 1,
    "2": 2,
    "3": 3,
    "4": 4
}


# ──────────────────────────────────────────────
# SECTION I: DISPLAY MENU
# ──────────────────────────────────────────────

def display_menu():
    """Displays the main service menu to the user."""
    print("\n" + "=" * 50)
    print("   QUEUE-BASED SERVICE TICKETING SYSTEM")
    print("=" * 50)
    print("  [1] Generate Service Ticket (Customer)")
    print("  [2] Call Next Ticket       (Staff)")
    print("  [3] View Queue Status      (Staff)")
    print("  [4] Admin Dashboard        (Admin)")
    print("  [5] Exit")
    print("=" * 50)


# ──────────────────────────────────────────────
# SECTION II: GENERATE TICKET
# ──────────────────────────────────────────────

def generate_ticket():
    """
    Creates and assigns a ticket number for a customer.
    Accepts customer name, service category, and priority status.
    """
    global ticket_counter

    print("\n--- GENERATE SERVICE TICKET ---")

    # Input: Customer name
    while True:
        name = input("Enter customer name: ").strip()
        if name:
            break
        print("  Name cannot be empty. Please try again.")

    # Input: Service category
    print("\nService Categories:")
    print("  [A] Billing")
    print("  [B] Medical")
    print("  [C] Registration")
    print("  [D] General Inquiry")

    while True:
        category_choice = input("Select service category (A/B/C/D): ").strip().upper()
        categories = {"A": "Billing", "B": "Medical", "C": "Registration", "D": "General Inquiry"}
        if category_choice in categories:
            category = categories[category_choice]
            break
        print("  Invalid choice. Please enter A, B, C, or D.")

    # Input: Priority status
    print("\nPriority Status:")
    print("  [1] PWD (Persons with Disability)")
    print("  [2] Senior Citizen (60+)")
    print("  [3] Pregnant")
    print("  [4] Regular")

    while True:
        priority_choice = input("Select priority status (1/2/3/4): ").strip()
        if priority_choice in PRIORITY_MAP:
            priority_level = PRIORITY_MAP[priority_choice]
            priority_label = PRIORITY_LABELS[priority_level]
            break
        print("  Invalid choice. Please enter 1, 2, 3, or 4.")

    # Generate ticket number and timestamp
    ticket_counter += 1
    ticket_number = f"T{ticket_counter:04d}"
    timestamp = datetime.datetime.now()

    # Store ticket in dictionary
    ticket_data = {
        "ticket_number": ticket_number,
        "name": name,
        "category": category,
        "priority_level": priority_level,
        "priority_label": priority_label,
        "timestamp": timestamp,
        "status": "Waiting"
    }
    tickets[ticket_number] = ticket_data

    # Add to priority queue
    add_to_queue(priority_level, timestamp, ticket_number)

    # Output: Display generated ticket
    print("\n" + "=" * 40)
    print("        SERVICE TICKET GENERATED")
    print("=" * 40)
    print(f"  Ticket Number : {ticket_number}")
    print(f"  Name          : {name}")
    print(f"  Category      : {category}")
    print(f"  Priority      : {priority_label}")
    print(f"  Time          : {timestamp.strftime('%I:%M %p')}")
    print(f"  Queue Position: {len(priority_queue)}")
    print("=" * 40)
    print("  Please wait for your number to be called.")


# ──────────────────────────────────────────────
# SECTION III: ADD TO QUEUE
# ──────────────────────────────────────────────

def add_to_queue(priority_level, timestamp, ticket_number):
    """
    Adds a ticket to the priority queue (min-heap).
    Heap tuple: (priority_level, timestamp, ticket_number)
    Lower priority_level = served first.
    Timestamp as tiebreaker ensures FIFO within same priority.
    """
    heapq.heappush(priority_queue, (priority_level, timestamp, ticket_number))


# ──────────────────────────────────────────────
# SECTION IV: CALL NEXT TICKET
# ──────────────────────────────────────────────

def call_next_ticket():
    """
    Retrieves the next ticket based on priority queue order.
    Highest priority (lowest number) is served first.
    """
    print("\n--- CALL NEXT TICKET ---")

    if not priority_queue:
        print("  The queue is currently empty. No customers waiting.")
        return

    # Pop the highest-priority ticket from the heap
    priority_level, timestamp, ticket_number = heapq.heappop(priority_queue)
    ticket = tickets[ticket_number]

    # Update ticket status
    ticket["status"] = "Served"
    ticket["served_at"] = datetime.datetime.now()

    # Move to service history
    service_history.append(ticket)

    # Output: Display served ticket info
    print("\n" + "=" * 40)
    print("       NOW SERVING")
    print("=" * 40)
    print(f"  Ticket Number : {ticket_number}")
    print(f"  Name          : {ticket['name']}")
    print(f"  Category      : {ticket['category']}")
    print(f"  Priority      : {ticket['priority_label']}")
    print(f"  Waited Since  : {ticket['timestamp'].strftime('%I:%M %p')}")
    print("=" * 40)

    # Show next in line if any
    if priority_queue:
        next_priority, next_time, next_ticket = priority_queue[0]
        print(f"\n  Next in Queue : {next_ticket} ({tickets[next_ticket]['name']})")
    else:
        print("\n  No more customers in queue.")


# ──────────────────────────────────────────────
# SECTION V: DISPLAY QUEUE STATUS
# ──────────────────────────────────────────────

def display_queue_status():
    """
    Shows the current queue list ordered by priority,
    and displays the latest ticket being served.
    """
    print("\n--- CURRENT QUEUE STATUS ---")

    if not priority_queue:
        print("  The queue is empty.")
    else:
        # Sort a copy of the heap to display in priority order
        sorted_queue = sorted(priority_queue)
        print(f"\n  {'#':<5} {'Ticket':<8} {'Name':<20} {'Category':<18} {'Priority':<15} {'Time'}")
        print("  " + "-" * 80)
        for idx, (priority, timestamp, ticket_number) in enumerate(sorted_queue, start=1):
            t = tickets[ticket_number]
            print(f"  {idx:<5} {ticket_number:<8} {t['name']:<20} {t['category']:<18} {t['priority_label']:<15} {timestamp.strftime('%I:%M %p')}")

    # Show currently being served (last in history)
    if service_history:
        last = service_history[-1]
        print(f"\n  Currently Served : {last['ticket_number']} - {last['name']} ({last['priority_label']})")
    else:
        print("\n  No tickets have been served yet.")


# ──────────────────────────────────────────────
# SECTION VI: ADMIN DASHBOARD
# ──────────────────────────────────────────────

def admin_dashboard():
    """
    Allows admin to monitor ticket volume,
    service efficiency, and view analytics.
    Uses recursion to compute total served count.
    """
    print("\n--- ADMIN DASHBOARD ---")
    print("=" * 50)

    total_tickets = ticket_counter
    waiting_count = len(priority_queue)
    served_count = count_served(service_history, 0)

    print(f"  Total Tickets Generated : {total_tickets}")
    print(f"  Tickets Waiting         : {waiting_count}")
    print(f"  Tickets Served          : {served_count}")

    # Priority breakdown in waiting queue
    print("\n  Waiting Queue Breakdown:")
    breakdown = {label: 0 for label in PRIORITY_LABELS.values()}
    for priority, _, ticket_number in priority_queue:
        label = PRIORITY_LABELS[priority]
        breakdown[label] += 1

    for label, count in breakdown.items():
        bar = "█" * count
        print(f"    {label:<18}: {count:>3}  {bar}")

    # Service history summary
    print("\n  Served Tickets History:")
    if service_history:
        print(f"  {'Ticket':<8} {'Name':<20} {'Category':<18} {'Priority':<15} {'Served At'}")
        print("  " + "-" * 75)
        for t in service_history:
            served_at = t.get("served_at", t["timestamp"]).strftime("%I:%M %p")
            print(f"  {t['ticket_number']:<8} {t['name']:<20} {t['category']:<18} {t['priority_label']:<15} {served_at}")
    else:
        print("  No tickets have been served yet.")

    print("=" * 50)


def count_served(history, index):
    """
    Recursive function to count total number of served tickets.
    Base case: index reaches end of history list.
    """
    if index >= len(history):
        return 0
    return 1 + count_served(history, index + 1)


# ──────────────────────────────────────────────
# MAIN PROGRAM LOOP
# ──────────────────────────────────────────────

def main():
    """
    Entry point of the program.
    Continuously runs to accept menu selections using a loop.
    """
    print("\nWelcome to the Queue-Based Service Ticketing System")
    print("Batangas State University – Service Management")

    while True:
        display_menu()
        choice = input("Select an option (1-5): ").strip()

        if choice == "1":
            generate_ticket()
        elif choice == "2":
            call_next_ticket()
        elif choice == "3":
            display_queue_status()
        elif choice == "4":
            admin_dashboard()
        elif choice == "5":
            print("\nThank you for using the Service Ticketing System.")
            print("Goodbye!\n")
            break
        else:
            print("\n  Invalid option. Please enter a number from 1 to 5.")


if __name__ == "__main__":
    main()