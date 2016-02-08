/** 
 * @file insertion_sort.c
 * @brief Insertion sort on integer array.
 * @author Kamesh Madduri
 *
 * CMPSC 465, Fall 2014
 * Sorting integers in non-decreasing order  
 * based on CLRS pseudocode.
 * 
 * Last modified Aug 26, 2014
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>

// added by rkn
#include "sort.h"

/* print running time in seconds */
static double timer() {
    
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double) (tp.tv_sec) + 1e-6 * tp.tv_usec);

    /* The code below is for another high resolution timer */
    /* I'm using gettimeofday because it's more portable */
    /*
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return ((double) (tp.tv_sec) + 1e-9 * tp.tv_nsec);
    */
}

void insertion_sort_reference(int* B, const int n)
{
    int i, j, key;
    for (j = 1; j < n; j++) {
        key = B[j];
        i = j - 1;
        while ((i >= 0) && (B[i] > key)) {
            B[i+1] = B[i];
            i = i - 1;
        }
        B[i+1] = key;
    }
}


/* generate different inputs for testing sort */
static int gen_input(int *A, int n, int input_type) {

    int i;

    /* uniform random values */
    if (input_type == 0) {

        srand(123);
        for (i=0; i<n; i++) {
            A[i] = rand() % n;
        }

    /* sorted values */    
    } else if (input_type == 1) {

        for (i=0; i<n; i++) {
            A[i] = i;
        }

    /* almost sorted */    
    } else if (input_type == 2) {

        for (i=0; i<n; i++) {
            A[i] = i;
        }

        /* do a few shuffles */
        int num_shuffles = (n/100) + 1;
        srand(1234);
        for (i=0; i<num_shuffles; i++) {
            int j = (rand() % n);
            int k = (rand() % n);

            /* swap A[j] and A[k] */
            int tmpval = A[j];
            A[j] = A[k];
            A[k] = tmpval;
        }

    /* array with single unique value */    
    } else if (input_type == 3) {

        for (i=0; i<n; i++) {
            A[i] = 1;
        }

    /* sorted in reverse */    
    } else {

        for (i=0; i<n; i++) {
            A[i] = (n + 1 - i);
        }

    }

    return 0;

}

static int sort_routines(int choice, int *A, const int n, const int num_iterations) {

    fprintf(stderr, "N %d\n", n);
    //fprintf(stderr, "Using insertion sort\n");

    fprintf(stderr, "Using ");
    switch(choice)
    {
        case 1:
            fprintf(stderr, "insertion sort\n");
            break;

        case 2:
            fprintf(stderr, "Reference insertion sort\n");
            break;

        case 3:
            fprintf(stderr, "selection sort\n");
            break;

        case 4:
            fprintf(stderr, "merge sort recursive\n");
            break;

        case 5:
            fprintf(stderr, "quicksort\n");
            break;

        case 6:
            fprintf(stderr, "heap sort\n");
            break;

        case 7:
            fprintf(stderr, "Non Recursive Merge sort\n");
            break;

        default:
            fprintf(stderr, "\nUnknown Option for Sort Method!!\nExiting..\n");
            exit(1);
            break;
    }

    fprintf(stderr, "Execution times (ms) for %d iterations:\n", 
            num_iterations);

    int iter;
    double avg_elt;

    /* Copying values in A into another array B */
    /* Sorting B */
    int *B;
    B = (int *) malloc(n * sizeof(int));
    assert(B != NULL);

    avg_elt = 0.0;

    for (iter = 0; iter < num_iterations; iter++) {
        
        int k;

        for (k=0; k<n; k++) {
            B[k] = A[k];
        }

        double elt;
        elt = timer();

        /* Actual sort code goes in here */
        // use switch case
        // Don't forget the breaks as the sort methods cascade and AFFECTS
        // up the timing
        switch(choice)
        {
            case 1:
                insertion_sort<int>(B, n);
                break;

            case 2:
                insertion_sort_reference(B, n);
                break;

            case 3:
                selection_sort<int>(B, n);
                break;

            case 4:
                merge_sort<int>(B, n);
                break;

            case 5:
                quicksort<int>(B, n);
                break;

            case 6:
                heapsort<int>(B, n);
                break;

            case 7:
                non_recursive_merge_sort<int>(B,n);
                break;
        }
        elt = timer() - elt;
        avg_elt += elt;
        fprintf(stderr, "%9.3lf\n", elt*1e3);

        /* correctness check */
        for (k=0; k<n-1; k++) {
            assert(B[k] <= B[k+1]);
        }

    }

    avg_elt = avg_elt/num_iterations;
    
    free(B);

    fprintf(stderr, "Average time: %9.3lf ms.\n", avg_elt*1e3);
    fprintf(stderr, "Average sort rate: %6.3lf MB/s\n", 4.0*n/(avg_elt*1e6));
    return 0;

}

void print_help_message(char**& argv)
{
    fprintf(stderr, "%s <sort choice> <n> <input_type>\n", argv[0]);
    fprintf(stderr, "input_type 0: uniform random\n");
    fprintf(stderr, "           1: already sorted\n");
    fprintf(stderr, "           2: almost sorted\n");
    fprintf(stderr, "           3: single distinct value\n");
    fprintf(stderr, "           4: sorted in reverse\n");
}

void validate_inputs(const int n, const int choice)
{
    assert(n > 0 && n <= 1000000000);

    assert(choice > 0 && choice < 8);
}

int main (int argc, char **argv) {

    if (argc != 4) {
        print_help_message(argv);
        exit(1);
    }

    int n, choice;

    choice = atoi(argv[1]);
    n = atoi(argv[2]);

    validate_inputs(n, choice);

    int *A;
    A = (int *) malloc(n * sizeof(int));
    assert(A != 0);

    int input_type = atoi(argv[3]);
    assert(input_type >= 0);
    assert(input_type <= 4);

    gen_input(A, n, input_type);

    int num_iterations = 10;
   
    sort_routines(choice, A, n, num_iterations);
    //insertion_sort(A, n, num_iterations);

    free(A);

    return 0;
}
