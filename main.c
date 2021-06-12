#include <stdio.h>
#include <stdlib.h>

struct answer_t{ 
    int if_to_right;
    // if the answer is to_right if_to_right = 1 and if the answer is wrong if_to_right = 0
    char answer_text[];
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
    struct node_t* tail;
}

void swap_nodes(struct node_t* left, struct node_t* right) {
    struct node_t* next = right->next;

    if(left->prev != NULL)
        left->prev->next = right;

    right->next = left;
    right->prev = left->prev;
    left->next = next;
    left->prev = right;

    if(next != NULL)
        next->prev = left;
}

void sort_list(struct list_t* list) {

  int not_sorted = 1;
  while(not_sorted) {
    not_sorted = 0;
    struct node_t* left = list->head;

    while(left->next != NULL) {
      struct node_t* right = left->next;

      if(left->question.difficulty > right->question.difficulty) {
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

}


int main()
{
    return 0;
}

