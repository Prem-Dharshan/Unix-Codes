# Shell Scripting Tasks

This repository contains solutions for various shell scripting tasks, each designed to demonstrate proficiency in Unix/Linux shell commands and script writing. The tasks involve text processing, file manipulation, and system operations. Below is a detailed description of each task.

## Task 1: Menu-Driven Shell Script (12 Marks)

### I. Print Lines Containing Specific Roll Numbers
Write a command that prints lines containing roll numbers of the form `21PC__`, `21PT__`, `21PW__`, `21PD__`. The two underscores must be replaced by two digits.

### II. Display 7-Letter Words Matching a Pattern
Display from a file all 7-letter words of the form `b---da-`, where each `-` represents any lowercase alphabet.

### III. Create a Folder Named After the Current Date
Write a script that fetches the current date from the system and creates a folder with the current date as its name.

### IV. Fetch and Display Usernames with Their Lengths
Write a script that fetches usernames from the first field in the `/etc/passwd` file and prints each username along with its length.

### V. Remove Permissions for Groups and Others
Write a script that accepts a directory name through the command line. The script should remove all permissions for groups and others on all files within the specified directory.

### VI. Sort an Employee File
Sort an employee file with the department as the primary key and the employee ID as the secondary key. The employee file contains the fields: employee ID, name, department, and salary. Create an alias for this command.

### VII. Print Lines Matching a Specific Pattern
Write a command that prints all lines containing two capital letters followed by a space and a capital letter.

### VIII. Display Specific Lines from a File
Display the content of a file from the fifth to the eighth line.

## Task 2: Generate a Report on File Types (5 Marks)

Write a shell script to generate a report that counts the types of files in the current directory. The report should be in the following format:

| Type of Files  | Count |
| -------------- | ----- |
| Regular files  | 5     |
| Directories    | 2     |
| Softlinks      | 3     |

## Task 3: Bash Script for File Size Filtering (8 Marks)

Write a bash script that processes file arguments based on their size. The script takes the following arguments:
- **sz:** The size in bytes.
- **f1, f2, f3, ..., fn:** The file names.

### Script Behavior:
- **If no arguments are given** (i.e., `sz` is missing), the script should write an error message to stderr and exit.
- **If `sz` is present**, the script processes each file argument in turn:
  - If the file does not exist or is not a regular file, the script ignores that file without printing any messages.
  - If the file exists and is a regular file, its contents are displayed if it contains more than `sz` bytes.
  - If there are no file arguments (i.e., only `sz` is present), the script terminates without doing anything further.

---

### How to Run the Scripts

1. Clone the repository:
   ```bash
   git clone <repository_url>
   ```
2. Navigate to the directory containing the scripts:
   ```bash
   cd <directory_name>
   ```
3. Make the scripts executable:
   ```bash
   chmod +x <script_name>.sh
   ```
4. Run the desired script:
   ```bash
   ./<script_name>.sh
   ```

### Note:
- Ensure you have the necessary permissions to execute the scripts.
- Modify the file paths as needed for your specific environment.

---

