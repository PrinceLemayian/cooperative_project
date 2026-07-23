# Nyeri Green Farmers Cooperative Project

A C program written for a university Programming assignment. It processes
farmer produce delivery records by calculating payments, updating payment
status, generating reports etc. using arrays, loops, and MySQL for
persistent storage.

The case study follows **Nyeri Green Farmers Cooperative**, a fictional
cooperative in Nyeri County, Kenya, that collects milk, coffee, maize,
potatoes, and vegetables from registered farmers and needs to track
deliveries and payments.

---

## Table of Contents

- [Academic Context](#academic-context)
- [Project Structure](#project-structure)
- [What Each Program Does](#what-each-program-does)
- [Questions Covered](#questions-covered)
- [Prerequisites](#prerequisites)
- [Setup Guide](#setup-guide)
- [Building the Project](#building-the-project)
- [Running the Programs](#running-the-programs)
- [Editor Setup (VS Code)](#editor-setup-vs-code)
- [Common Issues](#common-issues)

---

## Academic Context

This project was completed as coursework covering:
- Arrays and parallel array structures
- Loops (single and nested) for searching, filtering, and aggregation
- String handling in C (`strcmp`, `strcpy`)
- Connecting a C program to a MySQL database (`mysql.h` / MySQL Connector/C)
- Writing and executing SQL statements (`SELECT`, `UPDATE`, `DELETE`) from C
- Parameterised queries (`mysql_stmt_prepare` / `mysql_stmt_bind_param`) as
  a safer alternative to string-concatenated SQL
- Menu-driven program design using `switch` statements

Written answers for questions that ask for an explanation or pseudocode
rather than code (e.g. Question 13's database-update pseudocode, and the
short-answer Question 16) are not part of the `.c` files, check the
separate written submission for those.

---

## Project Structure

```
COOPERATIVE_PROJECT/
├── cooperative.c         # Questions 1-15: array processing + matching SQL
├── menu_program.c        # Extended Task: menu-driven program, loads from DB
├── setup.sql              # Creates the database and sample data
├── db_config.h.example   # Template for your local DB credentials
├── db_config.h            # Your personal credentials (not committed)
├── Makefile                # Builds both executables
├── .gitignore
└── README.md
```

---

## What Each Program Does

### `cooperative.c`
Walks through Questions 1–15 from the case study brief in order, using
hardcoded sample data (6 farmers) for the array-based parts, and live
SQL queries against the database for the matching database-driven parts
of each question. Run it, and it prints all output top to bottom, then
exits.

### `menu_program.c`
The Extended Programming Task. On startup, it connects to the database
and loads all farmer records into arrays, then presents an interactive
menu:

```
1. Display all farmer deliveries
2. Search for a farmer
3. Calculate farmer payments
4. Display pending payments
5. Update payment status
6. Display large deliveries
7. Generate daily report
8. Save updated records to the database
9. Exit
```

Changes made through options 5 (update status in memory) are only
written back to the database when you choose option 8, which asks for
confirmation and validates each record (skipping invalid or duplicate
entries) before saving.

---

## Questions Covered

| Question | Topic | Where |
|---|---|---|
| 1 | Display farmer records | `cooperative.c` |
| 2 | Calculate farmer payments | `cooperative.c` |
| 3 | Calculate total payment | `cooperative.c` |
| 4 | Identify pending payments (array + SQL) | `cooperative.c` |
| 5 | Update payment status (array + SQL) | `cooperative.c` |
| 6 | Find highest delivery (array + SQL) | `cooperative.c` |
| 7 | Find lowest payment (array + SQL) | `cooperative.c` |
| 8 | Search for a farmer (array + SQL) | `cooperative.c` |
| 9 | Count produce categories | `cooperative.c` |
| 10 | Payments by produce type (nested loops) | `cooperative.c` |
| 11 | Identify large deliveries (array + SQL) | `cooperative.c` |
| 12 | Apply cooperative levy | `cooperative.c` |
| 13 | Pseudocode: update DB with net payments | Written submission |
| 14 | Remove invalid records (array + SQL) | `cooperative.c` |
| 15 | Generate daily summary | `cooperative.c` |
| 16 | Short-answer conceptual questions | Written submission |
| Extended Task | Menu-driven program | `menu_program.c` |

---

## Prerequisites

- **MySQL Server** installed locally
- **MySQL Connector/C** (provides `mysql.h`, `libmysql.lib`, `libmysql.dll`)
- **GCC** (e.g. via MinGW-w64 on Windows)
- **Make** (optional but recommended - see [Building](#building-the-project))

---

## Setup Guide

### 1. Install MySQL Server

If you don't already have it installed, install MySQL Server on your
machine and note down the `root` password you set during install.

### 2. Create the database

Open the MySQL command-line client (or a terminal, then `mysql -u root -p`),
and run:

```sql
source setup.sql;
```

Run this from inside the project folder, so MySQL can find the file
without needing a full path. This creates the `cooperative` database
and the `ProduceDeliveries` table with the sample data.

Verify it worked:
```sql
USE cooperative;
SHOW TABLES;
SELECT * FROM ProduceDeliveries;
```
You should see the `ProduceDeliveries` table and 6 rows of farmer data.

### 3. Set up your own database credentials

Copy the example config file and rename it:
```
db_config.h.example  ->  db_config.h
```

Open `db_config.h` and fill in your own MySQL password:
```c
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "your_actual_password_here"
#define DB_NAME "cooperative"
```

**Do not commit `db_config.h`** as it's already in `.gitignore`, since it
holds your personal password. Only `db_config.h.example` (with no real
password) is meant to be shared.

### 4. Find your MySQL include/lib folders

These paths differ depending on your MySQL version and install location.
Look for two folders:
- One containing `mysql.h` (this is your **include** path)
- One containing `libmysql.lib` and `libmysql.dll` (this is your **lib** path)

They're commonly under something like:
```
C:\Program Files\MySQL\MySQL Server <version>\include
C:\Program Files\MySQL\MySQL Server <version>\lib
```

If you can't find them, search for `mysql.h` directly using File Explorer's
search bar, or in PowerShell:
```powershell
Get-ChildItem -Path "C:\Program Files\MySQL" -Filter "mysql.h" -Recurse
```

---

## Building the Project

### Option A: Using the Makefile (recommended)

Open `Makefile` and set your paths from Step 4:
```makefile
MYSQL_INCLUDE = C:\Program Files\MySQL\MySQL Server 8.0\include
MYSQL_LIB     = C:\Program Files\MySQL\MySQL Server 8.0\lib
```

Then build both programs at once:
```
make
```

If Windows doesn't recognize `make`, it's usually bundled with
MinGW-w64 as `mingw32-make` instead:
```
mingw32-make
```

To remove the built executables:
```
make clean
```

### Option B: Compiling manually

Using your own include/lib paths from Step 4:
```
gcc cooperative.c -o cooperative.exe -I"<your include path>" -L"<your lib path>" -lmysql -lws2_32
gcc menu_program.c -o menu_program.exe -I"<your include path>" -L"<your lib path>" -lmysql -lws2_32
```

### Copy `libmysql.dll` next to your `.exe` files

Compiling needs the `.lib` file, but *running* the program needs the actual
`.dll` file sitting in the same folder as your executables:
```
copy "<your lib path>\libmysql.dll" .
```

Without this step, both programs will silently fail to run at all.

---

## Running the Programs

```
.\cooperative.exe     # runs Questions 1-15 top to bottom, then exits
.\menu_program.exe    # connects to the DB, loads records, shows the menu
```

For `cooperative.exe`, you should see Questions 1–15 print their output
in order, followed by the SQL-driven sections near the end.

For `menu_program.exe`, you should see `Connected to the database
successfully!`, followed by `Loaded X farmer records from the database.`
and the menu prompt. Enter a number 1–9 to choose an option.

---

## Editor Setup (VS Code)

If you see red squiggly "include not found" errors under
`#include <mysql.h>`, this is just VS Code's IntelliSense not knowing
your include path and it doesn't affect whether the program actually
compiles or runs. To fix the squiggles:

1. `Ctrl+Shift+P` → **C/C++: Edit Configurations (UI)**
2. Add your include path (from Step 4) to the **Include path** field
3. Save

---

## Common Issues

| Symptom | Likely cause |
|---|---|
| `fatal error: mysql.h: No such file or directory` | Wrong `-I` path, or your `mysql.h` really is inside a `mysql/` subfolder (some installs differ) |
| `unknown type name 'SOCKET'` | Missing `#include <winsock2.h>` before `#include <mysql.h>` |
| Program exits instantly with zero output | Missing `libmysql.dll` next to your `.exe` (check with `echo $LASTEXITCODE` in PowerShell — code `-1073741515` confirms a missing DLL) |
| `ERROR 1049: Unknown database 'cooperative'` | `setup.sql` wasn't actually run yet, or was run from the wrong location |
| `make` / `mingw32-make` not recognized | Make isn't installed or isn't on your PATH — install it via MinGW-w64, or fall back to compiling manually (Option B above) |
| `no rule to make target 'db_config.h'` | You haven't completed Step 3 — copy `db_config.h.example` to `db_config.h` and fill in your credentials |