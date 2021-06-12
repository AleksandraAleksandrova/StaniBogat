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
    struct possible_answers_t* possible_answers;
    char question_text[];
};

struct node_t {
    struct question_t* question;
    struct node_t* next;
    struct node_t* prev;
};

struct list_t {
    struct node_t* head;
    struct node_t* tail;
    int size;
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

      if(left->question->difficulty > right->question->difficulty) {
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

/*
void joker(){
    
    printf("\t Choose your joker from 1 to 3:\n");
    printf("[1] 50-50\n");
    printf("[2] Call a friend");
    printf("[3] Audience poll\n");
    
    int response = 0;
    int count = 3;
    int is_used_50_50 = 0;
    int is_used_friend = 0;
    int is_used_audience = 0;
    // 0 znachi ne e izpolzwan. 1 znachi e polzvan

    while(count > 0){
        printf("Enter joker number >> \n"); 
        scanf("%d", &response);
    
        switch(response){
            case 1: {
              if(is_used_50_50 == 0){
                //funkciq za 50_50;`
                is_used_50_50 = 1;
                break;
              }else{
                printf("You already used this joker.\n");
                printf("Enter valid joker number >> \n"); 
                scanf("%d", &response);             
              }
            }
            case 2:  {
              if(is_used_friend == 0){
                //funkcq za friend
                is_used_friend = 1;
                break;
              }else{
                printf("You already used this joker. \n");
                printf("Enter valid joker number >> \n"); 
                scanf("%d", &response);
              }
            }
            case 3:  {
              if(is_used_audience == 0){
                //funkciq za audience;
                is_used_audience = 1;
                break;
              }else{
                printf("You already used this joker. \n");
                printf("Enter valid joker number >> \n"); 
                scanf("%d", &response);
              }
            }
        }
        count--;

        printf("Do you want another joker? y/n");
        char answer;
        scanf("%c", &answer);
        
        if(answer != 'y' || answer != 'Y') break;
    }
}
// da se slozhi goto vmesto continue
*/

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
 struct node_t* init_question(file){
    
    struct node_t* new_node = malloc(sizeof(struct node_t));

    printf("Difficulty (From 1-10): \n");
    scanf("%d", new_node->question->difficulty);
    printf("Write down your question: \n");
    fgets(new_node->question->question_text, 100, file);
    printf("Enter answer a: \n");
    fgets(new_node->question->possible_answers->a.answer_text, 30, file);
    printf("Is it the right answer? \n");
    scanf("%d", &new_node->question->possible_answers->a.if_right);
    // za dopisvane

    return new_node;
 }

void add_question(struct list_t* list, FILE* file){
    
    struct node_t* new_node;
    new_node = init_question(file);
    




    sort_list(list);
}

void print_file (struct list_t* list) {
    
    struct node_t* curr = list->head;
    int counter = 1;

    while(curr != NULL) {
        printf("[%d] %s\n", counter++, curr->question->question_text);
        curr = curr->next;
    }
    
}

void read_file (int argc, char** argv, struct list_t* list, int print) {
    if (argc > 1) {
        FILE* file = fopen(argv[1], "rb");

        fseek(file, 0, SEEK_END);
        int bite_count = ftell(file);
        rewind(file);

        int i = bite_count / sizeof(struct question_t);

        fread(&list, sizeof(struct question_t), i, file);
        
        if (print){
            print_file(list);
        }

        fclose(file);
    }
}

void write_file(struct  list_t* list){
    FILE* file = fopen("file./out.bin", "wb");

    fwrite(&list, sizeof(struct question_t), 0, file);
       
    fclose(file);
}

void edit_question(int argc, char** argv, struct list_t* list){
    printf("Which question to edit?\n");
    read_file (argc, argv, list, 1);
    puts("\n");
    printf("Number:\n");
    printf(">> ");
}

/*
Редактиране на въпрос - реализирайте възможност да се избере съществуващ въпрос и да се промени която и да е информация в него. 
Подобно на добавянето на нов, след приключване на редакцията трябва редактираният въпрос да е достъпен за избор при начало на игри или 
при записване във файл. По желание може да разширите работата с:
- Възможност за избор от потребителя в какъв ред и кои парчета информация иска да редактира(вместо да редактира целия въпрос)
- Възможност за филтриране на въпросите с цел по-лесно намиране на търсения
*/

void menu(int argc, char** argv, struct list_t* list){
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
            //case 2: add_question(list); break;
            case 3: edit_question(argc, argv, list); break;

        }
    }
}

int main(int argc, char** argv) {
    struct list_t list = {NULL, NULL};

<<<<<<< HEAD
    if (argc > 1) {
        FILE* file = fopen(argv[1], "rb");

        fseek(file, 0, SEEK_END);
        int bite_count = ftell(file);
        rewind(file);

        int i = bite_count / sizeof(struct question_t);

        fread(&list, sizeof(struct question_t), i, file);

        fclose(file);
    } else {  
        FILE* file = fopen("./out.bin", "wb");

        fwrite(&list, sizeof(struct question_t), 0, file);
       
        fclose(file);
    }
      //menu(list, file);

  return 0;
}
