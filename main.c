#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct answer_t{
    int if_right;
    char answer_text[100];
    int if_removed;
};

/*struct possible_answers_t {
    struct answer_t* a;
    struct answer_t* b;
    struct answer_t* c;
    struct answer_t* d;
};*/


struct question_t {
    int difficulty;
    //struct possible_answers_t* possible_answers;
    char question_text[100];
    struct answer_t answer[4];
};

struct node_t {
    struct question_t* question;
    struct node_t* next;
    struct node_t* prev;
};

struct list_t {
    struct node_t* head;
    struct node_t* tail;
};

void push_front(struct list_t* list, struct question_t* value) {
  struct node_t* new_node = malloc(sizeof(struct node_t));
  new_node->question = value;

  new_node->prev = NULL;
  if(list->head != NULL) {
    list->head->prev = new_node;
  } else {
    list->tail = new_node;
  }
  new_node->next = list->head;

  list->head = new_node;

  //list->size++;
}

void push_back(struct list_t* list, struct question_t* value) {
  if(!list->head) {
    push_front(list, value);
    return;
  }

  struct node_t* new_node = malloc(sizeof(struct node_t));
  new_node->question = value;

  new_node->next = NULL;
  new_node->prev = list->tail;

  list->tail->next = new_node;
  list->tail = new_node;

  //list->size++;
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

int *joker_50_50(struct question_t *question)
{
    int wrong_answer[2];
    int rand_answer;
    int j=0;

    //namirame 2 greshni otgovora i zapisvame tehnite indeksi v wrong_answer[]
    while(j<2)
    {
        rand_answer = rand() % 3;
        if(question->answer[rand_answer].if_right == 0)
        {
            wrong_answer[j]=rand_answer;
            question->answer[rand_answer].if_removed = 1;    
            j++;
        }
    }

    //alokirame pamet ot 2*int, koqto shte vurnem kato resultat ot funkciqta. V tazi pamet shte zapishem ind.
    //na ostanalite dva otgovora
    int *result = malloc(2*sizeof(int));
    int i=0;
    //proverqvame dali indeksa(j) e v wrong_answer, ako ne e go zapisvame v result
    for(j=0; j<4; j++)
    {
        if(wrong_answer[0] != j && wrong_answer[1] != j)
        {
            result[i] = j;
            i++;
        }
    } 

    return result;
}

int joker_call_friend(struct question_t *question)
{
    int probability[100];
    int j=0;// verniq otgovor
    int k; // broqch za inicializirane na probability masiva
    int random; //sluchaino chislo, koeto priema indeks na greshen otgovor
    //po tozi nachin namirame indeksa(j) na pravilniq otgovor
    while(question->answer[j].if_right != 1)
    j++;

    if(question->difficulty <= 3)// lesni vpr
    {
        for(k=0; k<100; k++)
         {
            if(k<80)
            {
                 probability[k]=j;
            }
            else{
                while((random = rand() % 3) != j);//teglim sluchaino chislo mejdu 0-3, no ako suvpadne s j(verniq otg) teglim pak
                probability[k] = random; //drugite 20% poluchavat otg na sluchaen princip
              }
            }
        }
        else if(question->difficulty >= 4 || question->difficulty <= 6) // sredni vpr
        {
            for(k=0; k<100; k++)
            {
              if(k<60)
              {
                   probability[k]=j;
              }
              else{
                while((random = rand() % 3) != j);//teglim sluchaino chislo mejdu 0-3, no ako suvpadne s j(verniq otg) teglim pak
                probability[k] = random; //drugite 40% poluchavat otg na sluchaen princip
              }
            }
        }
        else{//slojni vuprosi
            for(k=0; k<100; k++)
            {
              if(k<30)
              {
                   probability[k]=j;
              }
              else{
                while((random = rand() % 3) != j);//teglim sluchaino chislo mejdu 0-3, no ako suvpadne s j(verniq otg) teglim pak
                probability[k] = random; //drugite 70% poluchavat otg na sluchaen princip
              }
            }
        }
        random = rand() % 99; //teglim indeksa na nqkoi ot elementite na probability masiva; izteglqme verniq otg
        // kolkoto poveche indeksi na verni otg, tolkva po-golqm e shansa da se iztegli verniq otg
        return probability[random];   
}


void joker(struct question_t *question){
    
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
                //funkciq za joker 50/50
                //masiv ot 2*int res50_50
                int *res50_50 = joker_50_50(question);
                for(int i=0; i<=2; i++)
                {
                    printf("[%d] %s", res50_50[i], question->answer[res50_50[i]].answer_text);
                }
                free(res50_50);
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
                int *call_friend = joker_call_friend(question);
                for(int i=0; i<=2; i++)
                {
                    printf("[%d] %s", call_friend[i], question->answer[call_friend[i]].answer_text);
                }
                free(call_friend);
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

<<<<<<< HEAD

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
 struct question_t* init_question(FILE *file){
=======
 struct node_t* init_question(FILE *file){
>>>>>>> 2ee9999e13a661324f97818a21207a62b1341f7e
    
    struct question_t* new_question = malloc(sizeof(struct question_t));

    char answer_letter = 'a';

    printf("Difficulty (From 1-10): \n");
    scanf("%d", &new_question->difficulty);
    printf("Write down your question: \n");
    fgets(new_question->question_text, 100, stdin);
    
    for(int i = 0;i < 4;i++){
        
        printf("Enter answer %c: \n", answer_letter);
        fgets(new_question->question_text, 30, stdin);
        printf("Is it the right answer?(1 - true ; 0 - false) \n");
        scanf("%d", &new_question->answer->if_right);

        answer_letter++;
    }

    return new_question;
 }

void add_question(struct list_t* list, FILE* file){
    
    struct node_t* new_question = malloc(sizeof(struct node_t));
    new_question->question = init_question(file);

    push_back(list, new_question->question);

    
//Възможност за избор от потребителя в какъв ред иска да въведе парчетата информация за въпроса

    sort_list(list);
}

void fwrite_questions(struct list_t *list, char* filename)
{
    FILE* file = fopen(filename, "wba");

    if(file == NULL)
    {
      printf("Error");
      return;
    }

    size_t count = fwrite(&list, sizeof(struct question_t), 1, file);

    if(count == 0)
    {
        printf("Error");
        return;
    }
        
    fclose(file);
}

struct list_t *fread_questions(struct list_t* list, char* filename)//prochitame faila i vrushtame, tova koeto sme procheli
{
    FILE* file = fopen(filename, "rb");

    fseek(file, 0, SEEK_END);
    int bite_count = ftell(file);
    rewind(file);

    //int size_of_file = bite_count / sizeof(struct question_t);
    int i = 0;
    struct question_t questions[10];

    while(i<10){
        int rand_num = rand() % bite_count;
        fseek(file, rand_num, SEEK_SET);
        fread(&questions, (sizeof(struct question_t)), 1, file);
        rewind(file);
    }

    fclose(file);

    int j = 0;
    struct list_t* list_rand_qst = malloc(sizeof(struct list_t));

    for(j=0; j<i; j++){        
        struct node_t* new_node = malloc(sizeof(struct node_t));
        
        memcpy(&questions[j], new_node->question, sizeof(struct question_t)); //kopirame pametta na question[j] vuvu ukazatelq new
        new_node->next = NULL;

        if (list_rand_qst->head != NULL){
            list_rand_qst->head->prev = new_node;
        } else {
            list_rand_qst->tail = new_node;
        }

        new_node->next = list_rand_qst->head; 
        list_rand_qst->head = new_node;
    }   
    
    return list_rand_qst;
}

void print_list (struct list_t* list) {
    
    struct node_t* curr = list->head;
    int counter = 1;

    while(curr != NULL) {
        printf("[%d] %s\n", counter++, curr->question->question_text);
        curr = curr->next;
    }
    
}

void edit_question(struct list_t* list){
    int question = 0;
    int answer = 1;
    
    printf("Which question to edit?\n");
    print_list(list);
    
    puts("\n");

    printf("Number:\n");
    printf(">> ");
    scanf("%d", &question);

    struct node_t* curr = list->head;
    int counter = 1;

    while(counter < question) {
        curr = curr->next;
    }
    
    int change = 1;
    while (change) {
        printf("What to change? : \n");
        printf("\t 1 - Text of the question \n");
        printf("\t 2 - Difficulty \n");
        printf("\t 3 - Answer's text \n");
        printf("\t 4 - Right answer \n");
        printf("\t 0 - Nothing \n");
        
        printf(">> ");
        scanf("%d", &change);

        switch(change){
            case 1:
                printf("Enter text: \n");
                printf(">> ");
                fgets(curr->question->question_text, 100, stdin);
                break;
            case 2:
                do{
                    printf("Enter difficulty: \n");
                    printf(">> ");
                    scanf("%d", &curr->question->difficulty);
                }while(curr->question->difficulty<10 && curr->question->difficulty>0);
                break;
            case 3:
                while (answer){
                    printf("Which answer to edit: \n");
                    printf("1 - a)\n");
                    printf("2 - b)\n");
                    printf("3 - c)\n");
                    printf("4 - d)\n");
                    printf("0 - Stop\n");
                    printf(">> ");
                    scanf("%d", &answer);

                    printf("Enter text: \n");
                    printf(">> ");
                    switch(answer){
                        case 1: 
                            fgets(curr->question->answer[0].answer_text, 100, stdin);
                            break;
                        case 2:
                            fgets(curr->question->answer[1].answer_text, 100, stdin);
                            break;
                        case 3:
                            fgets(curr->question->answer[2].answer_text, 100, stdin);
                            break;
                        case 4: 
                            fgets(curr->question->answer[3].answer_text, 100, stdin);
                            break;
                        case 5: 
                            answer = 0;
                            break;
                    }
                } 
                break;
            case 4:
                printf("Which answer is right: \n");
                printf("1 - a)\n");
                printf("2 - b)\n");
                printf("3 - c)\n");
                printf("4 - d)\n");
                printf(">> ");
                scanf("%d", &answer);

                curr->question->answer[0].if_right = 0;
                curr->question->answer[1].if_right = 0;
                curr->question->answer[2].if_right = 0;
                curr->question->answer[3].if_right = 0;

                switch(answer){
                    case 1: 
                        scanf("%d", &curr->question->answer[0].if_right);
                        break;
                    case 2:
                        scanf("%d", &curr->question->answer[1].if_right);
                        break;
                    case 3:
                        scanf("%d", &curr->question->answer[2].if_right);
                        break;
                    case 4: break;
                        scanf("%d", &curr->question->answer[3].if_right);
                        break;
                } 
            case 0:
                change = 0;
                break;
       }
    }

}

void start_game(struct list_t* list, char* filename){
    fread_questions(list, filename);

    //chete 10 vyprosa
    //slaga gi v spisyk
    //spisyka se podrejda
    //vseki vypros se printira s vernite otgovori
    //proverqva se otgovora dali e veren
    //ako e veren vzima sledvashtiq
    //ako e greshen se vryshta v menu()
}

void menu(struct list_t* list, FILE* file, char* filename){
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
            case 1: start_game(list, filename); break;
            case 2: add_question(list, file); break;
            case 3: edit_question(list); break;
// bravo na nas <33 mnogo lyubov macki <#3333333 istinski kotaranki, lovkam vi <333333
        }
    }
}

int main(int argc, char** argv) 
{
  struct list_t question_list = {};
  //{
      /* data */
  //};
    /*
    if (argc > 1) {
        //question_list.head = fread_questions(&question_list, argv[1]);
    } else {  */
    FILE* file = fopen("./out.bin", "wb");

    fwrite(&question_list, sizeof(struct question_t), 0, file);
    menu(&question_list, file, argv[1]);
    fclose(file);      
    //trqbva da osvobodim pametta
    return 0;
}