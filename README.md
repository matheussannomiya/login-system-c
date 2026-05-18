# login-system-c

# Mini Login System in C

A simple authentication system developed in C, focused on file handling, hashing (hash table), and basic user management.

## Features
- User registration
- Login authentication via username
- Password masking during input
- Hash table-based user lookup (O(1) average)
- Collision handling using separate chaining (linked lists)
- Data persistence using text file (modularized storage system)
- Login logging with timestamp (date and time)
- Internal user ID system

## Architecture
- Hash table implemented using an array of buckets
- Each bucket stores a linked list of users (separate chaining)
- Username is used as the primary key for hash indexing
- Password is validated after user lookup
- ID is used as an internal identifier (not for login/search)
- Storage system modularized to handle file operations separately

## In Progress
- Password security improvements (hashing in future)
- Code refactoring and input handling improvements
- Further optimization of data structure organization

## Project Structure
```text
.
├── src/
│   ├── main.c
│   ├── hash.c
│   └── storage.c
│
├── include/
│   ├── hash.h
│   ├── storage.h
│   └── types.h
│
├── datasystem.txt
├── datalog.txt
└── Makefile (optional)
```
## How to Run
```bash
gcc src/main.c src/hash.c src/storage.c -Iinclude -o login_system
./login_system
```

