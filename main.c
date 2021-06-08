printf("Hello World!");
printf("Uspeshno promenqm main.c - Aleks");

// trying some random things 07.06.2021
#include <stdio.h>
#include <stdlib.h>

struct question_t {
    // char[] name;
    int difficulty;
    struct possible_answers_t answers;
}:

struct answer_t{
    char[] answer_text;
    int if_right_answer;
}:

struct possible_answers_t {
    struct answer_t a;
    struct answer_t b;
    struct answer_t c;
    struct answer_t d;
}
