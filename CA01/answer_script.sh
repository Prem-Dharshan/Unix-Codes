#!/bin/bash

# Function to print roll numbers for the given courses
printRollNos() {
    local courses=("$@")
    for course in "${courses[@]}"; do
        seq -f "${course}%02g" 1 20
    done
}

filterSevenLetterWords() {
    local filename="$1"
    if [ -f "$filename" ]; then
        echo "In If"
        egrep "b[a-z]{3}da[a-z]" "$filename" | echo 
    else
        echo "File not found: $filename"
    fi
}

createTodayDir() {
    mkdir "$(date +'%y-%m-%d')"
}


printUserNamesAndLength() {
    local names="$(cut -d':' -f1 /etc/passwd)"
    printf "%-20s %s\n" "Username" "Length"
    for name in $names
    do
        printf "%-20s %d\n" "$name" "${#name}"
    done
}

stripPermissions() {
    if [ $# -ne 1 ]
    then
        echo "No arg provided"
        exit 1
    fi

    # Check if directory name is provided
    if [ -z "$1" ]; then
        echo "Usage: $1 directory_name"
        exit 1
    fi

    # Check if the provided argument is a directory
    if [ ! -d "$1" ]; then
        echo "Error: $1 is not a directory."
        exit 1
    fi

    echo "Before"
    ls -l "$1"

    chmod -R go-rwx "$1"

    echo "After"
    ls -l "$1"

    echo "Permissions removed for all files in $1."
}

sortEmpFileAndAlias () {
    if [ $# -ne 1 ]
    then
        echo "No arg provided"
        return 1
    fi

    if [ ! -f "$1" ]
    then
        echo "No such file"
        return 1
    fi

    employeeFile="$1"


    alias sortme="sort -k3,3 -k1,1 "$employeeFile""
}

VII () {

    if [ $# -ne 1 ]
    then
        echo "No args"
        return 1
    fi

    if [ ! -f "$1" ]
    then
        echo "No such file"
        return 1
    fi

    file="$1"

    egrep "[A-Z]{2} [A-Z]" "$file"
}

countFileTypes() {
    local dir="$1"
    
    # Initialize counters
    REG=0
    DIR=0
    SL=0

    # Loop through the first column of 'ls -l' output (i.e., file type)
    for i in $(ls -l "$dir" | cut -c1)
    do
        # Check the type of each file
        if [ "$i" = '-' ]; then
            REG=$(expr $REG + 1)
        elif [ "$i" = 'd' ]; then
            DIR=$(expr $DIR + 1)
        elif [ "$i" = 'l' ]; then
            SL=$(expr $SL + 1)
        else
            continue
        fi
    done

    # Print the counts of each file type
    printf "%-20s %s\n" "Type of files" "Count"
    for var in REG DIR SL; do
        printf "%-20s %s\n" "$var" "$(eval echo \$$var)"
    done
}

display_large_files() {
    local size="$1"      # Number of bytes to compare against
    shift                # Remove the first argument (size) from the list
    local files="$@"     # Remaining arguments are file names

    if [ -z "$size" ]; then
        # If no size argument is given
        >&2 echo "Error: Size argument (SZ) is missing."
        exit 1
    fi

    if [ "$#" -eq 0 ]; then
        # If no file arguments are given
        echo "No files to process."
        exit 0
    fi

    for file in "$files"; do
        if [ -f "$file" ]; then
            # Check if the file exists and is a regular file
            file_size=$(stat -c%s "$file")
            if [ "$file_size" -gt "$size" ]; then
                # Display the file contents if its size is greater than the given size
                cat "$file"
            fi
        # File does not exist or is not a regular file, so ignore and continue
        done
}

organize_files_by_extension() {
    local DIR="$1"
    local BACKUP="$2"

    # Create the backup directory and the no_exten directory if they don't exist
    if [ ! -d "$BACKUP" ]; then
        mkdir -p "$BACKUP/no_exten/"
    fi

    # List only files in the directory
    local files=$(ls -p "$DIR" | grep -v "/")
    echo "$files"

    for file in $files; do
        # Extract the name and extension using cut
        local name=$(echo "$file" | cut -d'.' -f1)
        local exten=$(echo "$file" | cut -d'.' -f2-)

        echo "Name: $name"
        echo "Extension: $exten"

        # Check if the file has no extension
        if [ "$exten" = "$file" ]; then
            cp "$DIR/$file" "$BACKUP/no_exten/"
            continue
        fi

        # Check if the directory for this extension exists
        if [ -d "$BACKUP/$exten" ]; then
            cp "$DIR/$file" "$BACKUP/$exten/"
        else
            mkdir "$BACKUP/$exten"
            cp "$DIR/$file" "$BACKUP/$exten/"
        fi
    done
}

pipeTee() {
    ls | tee >(wc -l)
    ls | tee /dev/tty  |wc -l
}

findFdir() {
    ls -p sample | egrep "^f.*/$"
} 



# Main menu-driven script
while true; do
    echo "Menu:"
    echo "1. Print Roll Numbers for Given Courses"
    echo "2. Exit"
    echo "Enter your choice: "
    read choice
    
    case $choice in
        1)
            echo "Enter the courses (space-separated) for which you want to print roll numbers (e.g., 21PC 21PT 21PW 21PD): "
            read -a courses
            printRollNos "${courses[@]}"
            ;;
        2)
            echo "Exiting..."
            exit 0
            ;;
        *)
            echo "Invalid choice, please try again."
            ;;
    esac
done
