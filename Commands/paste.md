# `paste` Command

The `paste` command in Unix/Linux is used to merge lines of files side by side. It combines lines from multiple files into a single line, with a specified delimiter between them.

## Synopsis

```bash
paste [OPTION]... [FILE]...
```

## Description

`paste` reads lines from each FILE and concatenates corresponding lines from each file. The result is written to the standard output with lines from each file separated by a delimiter.

## Options

- `-d DELIM`, `--delimiters=DELIM`  
  Use the characters in DELIM as delimiters between lines. If DELIM contains multiple characters, they are cycled through.

- `-s`, `--serial`  
  Paste one file at a time instead of line-by-line. This option concatenates all lines from a file into a single line.

- `-z`, `--zero-terminated`  
  Line endings are treated as null characters (`\0`) instead of newline characters. Useful for working with null-terminated lines.

- `-V`, `--version`  
  Display the version information and exit.

- `-h`, `--help`  
  Display help information and exit.

## Examples

### Basic Usage

Concatenate lines from `file1.txt` and `file2.txt` with tab delimiters (default):

```bash
paste file1.txt file2.txt
```

### Custom Delimiter

Combine lines from `file1.txt` and `file2.txt` with a custom delimiter `,`:

```bash
paste -d ',' file1.txt file2.txt
```

### Multiple Delimiters

Combine lines using multiple delimiters, cycling through them:

```bash
paste -d ' | ' file1.txt file2.txt
```

### Serial Mode

Combine all lines from `file1.txt` into one line, separating them with tabs:

```bash
paste -s file1.txt
```

### Null-Terminated Lines

Combine lines using null characters as delimiters:

```bash
paste -z file1.txt file2.txt
```

## Notes

- If the delimiter string is longer than the number of lines, it will be truncated or cycled through.
- If files have different numbers of lines, `paste` will pad with empty fields for the shorter files.

## Related Commands

- `cat`: Concatenate and display file content.
- `cut`: Remove sections from each line of files.
- `join`: Join lines of two files based on a common field.

---
