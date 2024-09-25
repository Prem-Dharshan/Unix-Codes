#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *sourceFile, *destFile;
    char sourceFileName[100], destFileName[100];
    char ch;

    // Input source and destination file names
    printf("Enter the source file name: ");
    scanf("%s", sourceFileName);

    printf("Enter the destination file name: ");
    scanf("%s", destFileName);

    // Open the source file for reading
    sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL) {
        printf("Cannot open source file %s\n", sourceFileName);
        exit(1);
    }

    // Open the destination file for writing (create if it doesn't exist)
    destFile = fopen(destFileName, "w");
    if (destFile == NULL) {
        printf("Cannot open destination file %s\n", destFileName);
        fclose(sourceFile);
        exit(1);
    }

    // Read from source file and write to destination file
    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destFile);
    }

    printf("File copied successfully.\n");

    // Close the files
    fclose(sourceFile);
    fclose(destFile);

    return 0;
}
