#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_NAME "input/input3.txt"
#define OUTPUT_NAME "output/output3.txt"
#define MYOUTPUT_NAME "myoutput3.txt"

int main(int argc, char **argv) {
    FILE * in_file = fopen(INPUT_NAME, "r");
    if (!in_file) {
        printf("error - main: can't open file %s\n", INPUT_NAME);
        exit(-1);
    }
    FILE* out_file = fopen(OUTPUT_NAME, "r");
    if (!in_file) {
        printf("error - main: can't open file %s\n", INPUT_NAME);
        exit(-1);
    }
    FILE * myOut_file = fopen(MYOUTPUT_NAME, "w");

    int N, outValue, correct_outValue, testCounter = 1, testPassed = 0;
    char new_password[256];
    char old_password[256];
    bool passValidation;

    fscanf(in_file, "%d", &N);
    while (fscanf(in_file, "%s", new_password) == 1 && fscanf(in_file, "%s", old_password) == 1) {
        outValue = 0;
        passValidation = true;

        // 1 - At least 8 characters long
        // 2 - At most 16 characters long
        if (strlen(new_password) < 8 || strlen(new_password) > 16) {
            passValidation = false;
        }

        // 3 - Must contains both uppercase and lowercase letters
        // 4 - Must contains at least 1 digit and 1 special character
        // 5 - Must not cointain two consecutive identical characters
        // 6 - Must not be derivable by old_password by deleting, substituting or adding one character   
        char* str_it = new_password;
        char* old_str_it = old_password;
        int len_diff = strlen(new_password) - strlen(old_password);
        int count_different = 0;
        bool low = false, up = false, digit = false, special = false, consec = true;

        if (passValidation) {
            while (*str_it) {
                if (*str_it >= 'a' && *str_it <= 'z')
                    low = true;
                else if (*str_it >= 'A' && *str_it <= 'Z')
                    up = true;
                else if (*str_it >= '0' && *str_it <= '9')
                    digit = true;
                else
                    special = true;

                if (*str_it == *(str_it+1))
                    consec = false;

                if (*str_it != *old_str_it && *(old_str_it + len_diff) != *(str_it+1))
                    count_different++;

                str_it++;
                old_str_it++;
            }
            if (count_different != 1 && low && up && digit && special && consec)
                outValue = 1;
            else 
                outValue = 0;
        }

        fscanf(out_file, "%d", &correct_outValue);
        
        if (correct_outValue == outValue) {
            printf("Test %d passed\n", testCounter);
            testPassed++;
        }
        else
            printf("Test %d NOT passed\n", testCounter);
            
        fprintf(myOut_file, "%d\n", outValue);
        testCounter++;
    }
    printf("Total test passed -> %d out of %d\n", testPassed, N);
    return 0;
}