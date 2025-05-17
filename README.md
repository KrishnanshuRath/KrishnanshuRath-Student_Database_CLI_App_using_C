
# 📚 Student Database System (C CLI App)

This is a **console-based Student Database Management System** written in **C**, designed for basic record keeping of student data. It demonstrates the use of core C programming concepts such as **structures**, **file handling**, **authentication**, **control flow**, and **user interaction**.

---

## 🔧 Features & Functionalities

### 1. 🔐 User Login / Authorization
- Before accessing the system, users must log in using a **hardcoded admin username and password**.
- Demonstrates string comparison and basic security via input validation using `strcmp()`.

### 2. ➕ Add Student
- Collects student details: `ID`, `Name`, `Age`, `Branch`, `CGPA`, and `Email`.
- Stores records using `fwrite()` in a `.txt` file (binary format).
- Uses C **structures** to encapsulate student data.

### 3. 📋 List Students
- Displays all stored student records in a formatted table.
- Implements **pagination** to show 5 records per page using counters and user prompts.
- Uses `fread()` and `rewind()` for reading structured data from file.

### 4. 📝 Update Student
- Searches for a student by `ID` and allows selective updates (e.g., name, age, CGPA).
- Uses `fseek()` to overwrite the record in-place, demonstrating file position control.

### 5. ❌ Delete Student
- Removes a student by ID using a temporary file:
  - Reads all records
  - Skips the one to delete
  - Renames the temporary file back to the original
- Demonstrates use of `remove()` and `rename()` for safe file replacement.

### 6. 🔎 Search Student
- Searches by **partial match** on `name` or `branch` using `strstr()`.
- Reads each record and prints matches in real-time.

### 7. 📊 Display Statistics
- Calculates:
  - Total number of students
  - Average CGPA
  - Highest CGPA
- Demonstrates **looping**, **floating-point arithmetic**, and aggregations.

---

## 🛠 C Concepts Used

| Concept                | How It’s Used |
|------------------------|---------------|
| **Structures**         | To define a `Student` object and manage multiple fields as one entity |
| **File Handling**      | `fopen()`, `fread()`, `fwrite()`, `fseek()`, `rewind()`, `remove()`, `rename()` to perform CRUD on binary `.txt` file |
| **Strings & Input**    | `fgets()`, `scanf()`, `strcspn()` and `strstr()` to handle safe string input and matching |
| **Authentication**     | Uses `strcmp()` to compare entered login credentials |
| **Control Flow**       | `switch-case`, `do-while`, and `if` logic for CLI navigation |
| **Pagination**         | Uses a record counter and pause prompts to paginate long lists |
| **Modularity**         | Every major operation is encapsulated in its own function |
| **CLI UX**             | Prompts, validation messages, and formatted output improve usability |

---

## 📁 Data Storage

- Data is stored in a binary `.txt` file (`students.txt`)
- Each record is a fixed-size `struct Student` written and read directly with `fwrite()` and `fread()`
- Format is **not human-readable**, but efficient and fast for binary data access

---

## 🧑‍💻 How to Compile and Run

```bash
gcc Enhanced_StudentDatabaseSystem.c -o studentdb
./studentdb
```

**Login credentials:**
```
Username: admin
Password: admin123
```

---

## 📌 Notes

- This program uses a **binary format** for `.txt` — editing it with a text editor will corrupt the data.
- You can extend it to:
  - Export to CSV
  - Add multiple user roles
  - Perform data sorting
  - Store timestamps
