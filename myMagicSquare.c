///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2022, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////
   
// add your own File Header information here (as provided in p2A or Commenting guide
////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
// Other Files:      myMagicSquare, magicsquare1.txt
// Semester:         CS 354 Spring 2023
// Instructor:       Mark Mansi
//
// Author:           Akshay Gona
// Email:            gona@wisc.edu
// CS Login:         gona
// GG#:              (your Canvas GG number)
//                   (See https://canvas.wisc.edu/groups for your GG number)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   including family, friends, classmates, tutors,
//                   Peer Mentors, TAs, and Instructor.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the ideas and help they provided.
//
// Online sources:   none
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Structure that represents a magic square
typedef struct {
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 *
 * use stdin
 */
int getSize() {
    int size;
    printf("Enter magic square's size (odd integer >=3)\n");
    scanf("%d", &size);
    // check if size is odd and >= 3
    if(size < 3){
        printf("Magic square size must be >= 3.\n");
        exit(1);
    }
    // check if size is odd
    if(size % 2 == 0){
        printf("Magic square size must be odd.\n");
        exit(1);
    }
    return size;
}
   
/* TODO:
 * Makes a magic square of size n using the
 * Siamese magic square algorithm or alternate from assignment
 * or another valid algorithm that produces a magic square.
 *
 * n is the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 *
 */
MagicSquare *generateMagicSquare(int n) {
    MagicSquare *magic_square = malloc(sizeof(MagicSquare)); // allocate memory for magic square
    // check if malloc failed, or null
    if (magic_square == NULL){
        printf("Error allocating memory\n");
        exit(1);
    }
    magic_square->size = n; // set size of magic square
    magic_square->magic_square = malloc(sizeof(int *) * n); // allocate memory for magic square
    // check if malloc failed, or null
    if (magic_square->magic_square == NULL){
        printf("Error allocating memory\n");
        exit(1);
    }
    // allocate memory for each row
    for (int i = 0; i < n; i++){
        *(magic_square->magic_square + i) = malloc(sizeof(int) * n);
        if (*(magic_square->magic_square + i) == NULL){
            printf("Error allocating memory\n");
            exit(1);
        }
    }
    // siaemese algorithm
    int row = 0; // start at top middle
    int col = n / 2; // start at top middle
    int num = 1; // start at 1
    while (num <= n * n){ //while not all numbers are filled. from 1 to n^2
        *(*(magic_square->magic_square + row) + col) = num;
        num++;
        // check if next row and col are out of bounds
        int nextRow = (row - 1 + n) % n;
        int nextCol = (col + 1) % n;
        //wrap around, empty space
        if (*(*(magic_square->magic_square + nextRow) + nextCol) == 0){
            row = nextRow;
            col = nextCol;
        }
        else{
            row = (row + 1) % n;
        }
    }
    return magic_square;
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
    FILE *fp = fopen(filename, "w");
    // check if file open failed
    fprintf(fp, "%d\n", magic_square->size);
    // print magic square
    for (int i = 0; i < magic_square->size; i++){
        for (int j = 0; j < magic_square->size; j++){
            fprintf(fp, "%d", *(*(magic_square->magic_square + i) + j));
            // check if last number in row
            if (j != magic_square->size - 1){
                fprintf(fp, ",");
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}


/* TODO:
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 * 
 * Add description of required CLAs here
 */
int main(int argc, char **argv) {
    // TODO: Check input arguments to get output filename
    if (argc != 2){
        printf("Usage: ./myMagicSquare <output_filename>\n");
        exit(1);
    }
    // TODO: Get magic square's size from user
    int size = getSize();
    // TODO: Generate the magic square by correctly interpreting 
    //       the algorithm(s) in the write-up or by writing or your own.  
    //       You must confirm that your program produces a 
    //       Magic Square as described in the linked Wikipedia page.
    MagicSquare *magic_square = generateMagicSquare(size);
    // TODO: Output the magic square
    fileOutputMagicSquare(magic_square, *(argv + 1));
    // TODO: free allocated memory
    // free each row
    for (int i = 0; i < size; i++){
        free(*(magic_square->magic_square + i));
    }
    //general frees for the board, hopefully frees any previously unfreed memory
    free(magic_square->magic_square);
    free(magic_square);
    return 0;
} 

// S23
