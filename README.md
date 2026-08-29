# Ji Li & Friends - Restaurant Ordering & Sales Tracking System

A C++ console-based Point of Sale (POS) and daily sales tracking application for managing dine-in and takeaway patron orders, calculating receipts, and tracking cumulative revenue.

---

## Features

- **Order Management:** Register patron details (Dine-in table allocation/pax or Takeaway) and select items from a preconfigured food and beverage menu.
- **Dynamic Modifications:** Modify active orders with dynamic item addition and quantity deletions before finalisation.
- **Bill Generation:** Formats itemised receipts with calculated totals, formatted dates, and unique order tracking codes.
- **Sales Analytics:** Tracks cumulative sales on both a daily and monthly basis, accounting for leap years and month-end resets.

---

## Getting Started

### Prerequisites

- A C++ compiler (such as `g++`, `clang++`, or MSVC) supporting **C++11** or newer.

### Compilation

Compile the source code using `g++`:

```bash
g++ -std=c++11 main.cpp -o restaurant_pos