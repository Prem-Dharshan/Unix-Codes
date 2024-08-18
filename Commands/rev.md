# `rev` Command in Unix/Linux

The `rev` command in Unix/Linux is a simple utility that reads each line from the standard input or a file and then reverses the order of characters in that line. It outputs the reversed line to the standard output.

## Usage

```bash
rev [OPTION]... [FILE]...
```

- If no files are specified, `rev` reads from the standard input.
- If one or more files are specified, `rev` reads from each file in turn.

## Examples

### 1. Reverse the characters of each line in a file

Suppose you have a file `example.txt` with the following content:

```
hello
world
```

To reverse the characters in each line, use the `rev` command:

```bash
rev example.txt
```

**Output:**

```
olleh
dlrow
```

### 2. Reverse the characters of a string provided via standard input

You can use `rev` in combination with echo or directly from the terminal:

```bash
echo "Hello, World!" | rev
```

**Output:**

```
!dlroW ,olleH
```

### 3. Reversing multiple files

If you have multiple files and want to reverse the contents of each:

```bash
rev file1.txt file2.txt
```

This will output the reversed content of each file consecutively.

## Practical Applications

- **Reversing filenames**: Useful when you need to extract file extensions or analyze file patterns from the end of the filename.
- **Palindrome checking**: Helps in checking if a word or phrase is a palindrome by comparing the original and reversed strings.
- **Data manipulation**: Can be used in scripts where reversing data plays a part in processing or formatting.

## Options

The `rev` command has no specific options. It's a straightforward utility with a single purpose: reversing lines of text.

## Related Commands

- `tac`: Reverse the lines in a file (as opposed to reversing the characters).
- `cut`: Extract sections from each line of files.
- `awk`: Pattern scanning and processing language.

---
