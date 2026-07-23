# ---- Edit these two paths for your machine ----
MYSQL_INCLUDE = C:\Program Files\MySQL\MySQL Server 8.0\include
MYSQL_LIB     = C:\Program Files\MySQL\MySQL Server 8.0\lib

CC     = gcc
CFLAGS = -I"$(MYSQL_INCLUDE)"
LFLAGS = -L"$(MYSQL_LIB)" -lmysql -lws2_32

all: cooperative.exe menu_program.exe

cooperative.exe: cooperative.c db_config.h
	$(CC) cooperative.c -o cooperative.exe $(CFLAGS) $(LFLAGS)

menu_program.exe: menu_program.c db_config.h
	$(CC) menu_program.c -o menu_program.exe $(CFLAGS) $(LFLAGS)

clean:
	del /Q cooperative.exe menu_program.exe 2>nul

.PHONY: all clean