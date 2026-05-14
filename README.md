# login-system-c
# Mini Login System in C

A simple authentication system developed in C, focused on file handling, hashing (hash table), and basic user management.

## Features
- User registration
- Login authentication via username
- Hash table-based user lookup (O(1) average)
- Collision handling using separate chaining (linked lists)
- Data persistence using text file
- Login logging with timestamp (date and time)
- Internal user ID system

## Architecture
- Hash table implemented using an array of buckets
- Each bucket stores a linked list of users (separate chaining)
- Username is used as the primary key for hash indexing
- Password is validated after user lookup
- ID is used as an internal identifier (not for login/search)

## In Progress
- Password security improvements (hashing in future)
- Code refactoring and input handling improvements
- Further optimization of data structure organization

## Project Structure
```text
.
├── main.c
├── hash.c
├── hash.h
├── datasystem.txt
└── datalog.txt
```

## How to Run
```bash
gcc main.c hash.c -o login_system
./login_system
```
