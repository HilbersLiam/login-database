# Simple Login System

This is a simple login system implemented in C, allowing users to log in or create an account. User information is stored in a text file.

## Usage

1. **Compilation:**

   ```bash
   gcc login_system.c -o login_system
   ```
3. **Run:**

   ```bash
   ./login_system your_file.txt
   ```
Replace "your_file.txt" with the name of the text file that stores the data.

## Functionality
* The program reads the user information from the specified file.  
* Users can log in with an existing account or create a new one.  
* Account information is stored in the file in the format:
   
  ```bash
  Username: example_user  
  Password: example_password
  ```

