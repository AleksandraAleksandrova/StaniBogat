#include <stdio.h>
#include <stdlib.h>

struct answer_t{
    char answer_text[]; 
    int if_to_right;
    // if the answer is to_right if_to_right = 1 and if the answer is wrong if_to_right = 0
};

struct possible_answers_t {
    struct answer_t a;
    struct answer_t b;
    struct answer_t c;
    struct answer_t d;
};

struct question_t {
    char question_text[];
    int difficulty;
    struct possible_answers_t possible_answers; 
};

struct node_t {
    struct question_t question;
    struct node_t* next;
    struct node_t* prev;
};

struct list_t {
    struct node_t* head;
}

void sort_questions_list(struct node_t* list){
    /*
    int not_sorted = 1;
    while(not_sorted) {
        not_sorted = 0;
        struct node_t* left = list->head;

        while(left->next != NULL) {
        */

// first part is needed

        /*if(curr->value > curr->next->value) {
            swap_nodes(curr, curr->next);
            if(curr == list->head)
            list->head = curr->prev;
            if(curr->next == list->tail)
            list->tail = curr;
        } else {
            curr = curr->next;
        }*/
// this part not

        /*
        struct node_t* right = left->next;
        printf("%d %d\n", left->value, right->value);

        if(left->value > right->value) {
            not_sorted = 1;
            swap_nodes(left, right);
            if(left == list->head)
            list->head = right;
            if(right == list->tail)
            list->tail = left;

            struct node_t* tmp = left;
            left = right;
            right = tmp;
        }   

        left = left->next;
        }

    }
    */

   // needed

    /*for(int i = 0; i < arr.length - 1; i++) {
        for(int j = i + 1; j < arr.length; j++) {
        if(arr[i] > arr[j]) {
            swap()
        }
        }
    }*/
    // not exactly
    }

int main()
{
    //using functions
    return 0;
}

