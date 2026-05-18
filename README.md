# login-system-c

# Mini Login System in C

A simple authentication system developed in C, focused on low-level programming concepts such as hashing, file handling, modularization, and basic user management.

## Features
- User registration
- Login authentication
- Password masking during input
- Password hashing using FNV-1a
- Hash table-based user lookup (average O(1))
- Collision handling using separate chaining (linked lists)
- Persistent storage using text files
- Login logging with timestamp
- Internal user ID system
- Modularized architecture using separate `.c` and `.h` files

## Architecture
- Hash table implemented using an array of buckets
- Each bucket stores a linked list of users (separate chaining)
- Username is used as the primary key for hash indexing
- Password hashes are stored instead of plain-text passwords
- Password validation is performed by comparing hashes
- Storage system separated into dedicated modules

## Security Notes
This project uses the FNV-1a hash algorithm for educational purposes only.

Although it demonstrates the concept of password hashing, FNV-1a is **not suitable for real-world password security** because it is fast and not resistant to brute-force attacks.

Real authentication systems should use dedicated password hashing algorithms such as:
- bcrypt
- Argon2
- PBKDF2

## In Progress
- Input validation improvements
- Better file handling and error checking
- Refactoring and code organization improvements
- Future migration to stronger password hashing algorithms

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

