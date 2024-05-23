README for Recover JPEG Problem Set
markdown
Copy code
# Recover JPEG

## Project Description
This project is a solution to a CS50x problem set that involves recovering JPEG files from a forensic image. The program scans through the input file, identifies JPEG file signatures, and writes the JPEG files to disk.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Code Explanation](#code-explanation)

## Installation
No special installation is required for this project.

## Usage
To compile and run the project, use the following commands:


make recover
./recover YOUR_IMAGE_FILE
Replace YOUR_IMAGE_FILE with the path to the forensic image file you want to recover JPEGs from.

## Code Explanation
Main Function

``` C
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover YOUR IMAGE FILE \n");
        return 1;
    }
```
#include <stdint.h>, #include <stdio.h>, and #include <stdlib.h> include the necessary libraries for fixed-width integer types, standard input/output functions, and standard library functions respectively.
int main(int argc, char *argv[]) is the entry point of the program where the execution starts. It takes command-line arguments.
The if (argc != 2) statement checks if exactly one command-line argument is provided (the name of the image file). If not, it prints usage instructions and returns 1 to indicate an error.
File Handling and Initialization

``` C
    if (argv[1] == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    FILE *file = NULL;
    uint8_t buffer[512];
    int counter = 0;
```

The if (argv[1] == NULL) statement checks if the provided file path is NULL. If it is, it prints an error message and returns 1.
FILE *input = fopen(argv[1], "r"); opens the input file in read mode.
FILE *file = NULL; initializes a file pointer to keep track of the output JPEG files.
uint8_t buffer[512]; declares a buffer to store 512 bytes (the block size for FAT file systems).
int counter = 0; initializes a counter to keep track of the number of JPEG files found.
Reading and Writing JPEG Files

``` C
    while (fread(buffer, 1, 512, input) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            if (file != NULL)
            {
                fclose(file);
            }
            char filename[8];
            sprintf(filename, "%03i.jpg", counter);
            counter++;
            file = fopen(filename, "w");
        }
        if (file != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, file);
        }
    }
```
The while (fread(buffer, 1, 512, input) == 512) loop reads 512 bytes from the input file into the buffer. It continues until fewer than 512 bytes are read, indicating the end of the file.
The if statement checks for the JPEG file signature in the buffer. JPEG files start with the byte sequence 0xff, 0xd8, 0xff followed by a byte in the range 0xe0 to 0xef.
If a new JPEG file is found and an output file is already open, it closes the current file with fclose(file).
char filename[8]; and sprintf(filename, "%03i.jpg", counter); create a new filename for the JPEG file.
file = fopen(filename, "w"); opens a new file for writing the JPEG data.
fwrite(buffer, sizeof(buffer), 1, file); writes the buffer to the output file if a file is currently open.
Cleanup

``` C
    fclose(input);
    fclose(file);
    return 0;
}
```
fclose(input); closes the input file.
fclose(file); closes the output file if it is open.
return 0; indicates that the program has finished successfully.
