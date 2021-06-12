#include <stdio.h>
#include <stdlib.h>

struct answer_t{
    int if_right;
    char answer_text[];
};

struct possible_answers_t {
    struct answer_t a;
    struct answer_t b;
    struct answer_t c;
    struct answer_t d;
};

struct question_t {
    int difficulty;
    struct possible_answers_t possible_answers;
    char question_text[];
};

struct node_t {
    struct question_t question;
    struct node_t* next;
    struct node_t* prev;
};

struct list_t {
    struct node_t* head;
    struct node_t* tail;
};

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
void joker(){
    
    /*printf("\t Choose your joker from 1 to 3\n");
    printf("50-50\n");
    printf("Call a friend");
    printf("Audience poll\n");
    
    int response = 1;
    int count = 3;
    while(count > 0){
        printf(>>); 
        scanf("%d", &response);
    
        switch(response){
            case 1: \\50-50 break;
            case 2:\\nekuf random; break;
            case 3: \\oshte edin random; break;
        }
            
        
        printf("Do you want another joker? y/n");
        char answer;
        scanf("%c", &answer);
        
        if(answer != 'y' || answer != 'Y') break;
        
        count--;
    }
    
*/
}
void start_game(){
    //otvarq faila
    //chete 10 vyprosa
    //slaga gi v spisyk
    //spisyka se podrejda
    //vseki vypros se printira s vernite otgovori
    //proverqva se otgovora dali e veren
    //ako e veren vzima sledvashtiq
    //ako e greshen se vryshta v menu()
}

void add_question(){
}

void edit_question(){
}

void menu(){
    printf(" *** Welcome to the game 'StaniBogat' *** ");
    puts("\n");
    int response = 1;

    while (response) {
        printf("Choose command:\n");
        printf("\t 1 - Start game\n");
        printf("\t 2 - Add question\n");
        printf("\t 3 - Edit question\n");
        printf("\t 0 - Exit\n");

        printf(">> ");
        scanf("%d", &response);

        switch(response){
            case 0: exit(0); break;
            case 1: start_game(); break;
            case 2: add_question(); break;
            case 3: edit_question(); break;
        }
    }
}

int main(){
    menu();
    return 0;
}
