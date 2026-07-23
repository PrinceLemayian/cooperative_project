# Setup Guide (for anyone cloning this repo)

This project uses MySQL, and each person needs their own local database
and their own connection settings. Follow these steps after cloning.

## 1. Install MySQL Server

If you don't already have it installed, install MySQL Server on your
machine and note down the `root` password you set during install.

## 2. Create the database

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

## 3. Set up your own database credentials

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

**Do not commit `db_config.h`** — it's already in `.gitignore`, since it
holds your personal password. Only `db_config.h.example` (with no real
password) is meant to be shared.

## 4. Find your MySQL include/lib folders

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

## 5. Compile

Using your own include/lib paths from Step 4:
```
gcc cooperative.c -o cooperative.exe -I"<your include path>" -L"<your lib path>" -lmysql
```

## 6. Copy `libmysql.dll` next to your `.exe`

Compiling needs the `.lib` file, but *running* the program needs the actual
`.dll` file sitting in the same folder as `cooperative.exe`:
```
copy "<your lib path>\libmysql.dll" .
```

Without this step, the program will silently fail to run at all.

## 7. Run it

```
.\cooperative.exe
```

You should see Questions 1-4 print their output, followed by
"Connected to the database successfully!" at the end.

## Editor setup (optional, VS Code)

If you see red squiggly "include not found" errors under
`#include <mysql.h>`, this is just VS Code's IntelliSense not knowing
your include path — it doesn't affect whether the program actually
compiles or runs. To fix the squiggles:

1. `Ctrl+Shift+P` -> **C/C++: Edit Configurations (UI)**
2. Add your include path (from Step 4) to the **Include path** field
3. Save

## Common issues

| Symptom | Likely cause |
|---|---|
| `fatal error: mysql.h: No such file or directory` | Wrong `-I` path, or your `mysql.h` really is inside a `mysql/` subfolder (some installs differ) |
| `unknown type name 'SOCKET'` | Missing `#include <winsock2.h>` before `#include <mysql.h>` |
| Program exits instantly with zero output | Missing `libmysql.dll` next to your `.exe` (check with `echo $LASTEXITCODE` in PowerShell — code `-1073741515` confirms a missing DLL) |
| `ERROR 1049: Unknown database 'cooperative'` | `setup.sql` wasn't actually run yet, or was run from the wrong location |