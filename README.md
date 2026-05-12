# login-system-c
# Mini Login System in C

A simple authentication system developed in C, focused on file handling, hashing (hash table), and basic user management.

## Features
- User registration
- Login authentication via username
- Hash table-based user lookup (O(1) average)
- Data persistence using text file
- Login logging with timestamp (date and time)
- Internal user ID system

## Architecture
- Username is used as the primary key for hash table indexing
- Password is validated after user lookup
- ID is used as an internal identifier (not for login/search)

## In Progress
- Collision handling in hash table
- Improved data structure organization
- Password security improvements (hashing in future)

## How to Run
```bash
gcc main.c -o login
./login
