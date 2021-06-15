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
 struct node_t* init_question(FILE *file){
    
    struct node_t* new_node = malloc(sizeof(struct node_t));

    printf("Difficulty (From 1-10): \n");
    scanf("%d", new_node->question->difficulty);
    printf("Write down your question: \n");
    fgets(new_node->question->question_text, 100, file);
    printf("Enter answer a: \n");
    fgets(new_node->question->question_text, 30, file);
    printf("Is it the right answer? \n");
    scanf("%d", &new_node->question->answer->if_right);
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

/*void read_file (int argc, char** argv, struct list_t* list, int print) {
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

/*void edit_question(int argc, char** argv, struct list_t* list){
    int question = 0;
    int answer = 0;

    printf("Which question to edit?\n");
    read_file (argc, argv, list, 1);
    
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
                printf("Which answer to edit: \n");
                printf("1 - a)\n");
                printf("2 - b)\n");
                printf("3 - c)\n");
                printf("4 - d)\n");
                printf(">> ");
                scanf("%d", &answer);

                printf("Enter text: \n");
                printf(">> ");
                switch(answer){
                    case 1: 
                        fgets(curr->question->possible_answers->a->answer_text, 100, stdin);
                        break;
                    case 2:
                        fgets(curr->question->possible_answers->b->answer_text, 100, stdin);
                        break;
                    case 3:
                        fgets(curr->question->possible_answers->c->answer_text, 100, stdin);
                        break;
                    case 4: break;
                        fgets(curr->question->possible_answers->d->answer_text, 100, stdin);
                        break;
                } 
                break;
            case 4:/*
                printf("Which answer to edit: \n");
                printf("1 - a)\n");
                printf("2 - b)\n");
                printf("3 - c)\n");
                printf("4 - d)\n");
                printf(">> ");
                scanf("%d", &answer);
                switch(answer){
                    case 1: 
                        scanf("%d", &curr->question->possible_answers->a->if_right);
                        break;
                    case 2:
                        scanf("%d", &curr->question->possible_answers->b->if_right);
                        break;
                    case 3:
                        scanf("%d", &curr->question->possible_answers->c->if_right);
                        break;
                    case 4: break;
                        scanf("%d", &curr->question->possible_answers->d->if_right);
                        break;
                }  /*Not working*/
              //  break;
           // case 0:
             //   change = 0;
              //  break;
   // }
  //}
//}

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
           // case 3: edit_question(argc, argv, list); break;
// bravo na nas
        }
    }
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

struct node_t *fread_questions(char* filename)//prochitame faila i vrushtame, tova koeto sme procheli
{
    FILE* file = fopen(filename, "rb");

    fseek(file, 0, SEEK_END);
    int bite_count = ftell(file);
    rewind(file);

    int i = bite_count / sizeof(struct question_t);
    struct question_t questions[i];
    if(i>=10)
    {
        fread(&questions, sizeof(struct question_t), i, file);
    }
    else printf("Not enough questions");
    
    fclose(file);

    int j;
    struct node_t *head; //suzdavame edin spisuk, koito shte sudurja node_t structuri i shte go vurnem
    //edin spisuk ot question structuri
     struct node_t *new;
    for(j=0; j<i; j++)
    {
        new = malloc(sizeof(struct node_t));
        new->question = malloc(sizeof(struct question_t));
        memcpy(&questions[j], new->question, sizeof(struct question_t)); //kopirame pametta na question[j] vuvu ukazatelq new
        head->next = NULL;
        //head->prev = 
        // da se doprenasochat ukazatelite

        if(j == 0)
        {
            head = new;
        }
    }
    return head;
}

int main(int argc, char** argv) 
{
  struct node_t *question_list;
    if (argc > 1) {
        question_list = fread_questions(argv[1]);
    } else {  
        FILE* file = fopen("./out.bin", "wb");

        fwrite(question_list, sizeof(struct question_t), 0, file);
       
        fclose(file);
    }
      //menu(list, file);

  //trqbva da osvobodim pametta
  return 0;
}
