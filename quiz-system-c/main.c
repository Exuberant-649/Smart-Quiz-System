#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct new_user
{
    char id[25];
    char password[25];
};

char id[25];

void sign_up();
int login();
int is_unique(char *id);
int take_quiz(char *user_id);
void (view_mark(const char *user_id));
int exit_prog();
void user_home();
void admin_home();
void add_quiz();

int main()
{
    int user_choice;
    int login_success = 0;
    int a;
    while(1)
    {
        printf("========== QUIZ SYSTEM ==========\n\n");
        printf("1. Sign up\n");
        printf("2. Login\n");
        printf("Enter your choice: ");
        scanf("%i", &user_choice);
        printf("\n");
    
        switch(user_choice)
        {
            case(1):
                sign_up();
                break;
            case(2):
                a = login();
                if(a)
                {
                    login_success = 1;
                }
                break;
        }  

        if (login_success == 1)
        {
            break;
        } 
    }
    

}


void sign_up()
{
    FILE *file = fopen("user.txt", "a");
    struct new_user user;
    printf("\nEnter ID: ");
    scanf("%s", user.id);
    printf("Enter Password: ");
    scanf("%s", user.password);
    if (is_unique(user.id))
    {
        fprintf(file, "%s %s\n", user.id, user.password);
        fflush(file);
        printf("\nSIGN IN SUCCESSFUL!\n\n");
        return;
    }
    else
    {
        printf("\nSorry. The ID you entered is not available!\nPlease try again..\n");
        return;
    }
}

int login()
{
    char password[20];
    char id[25];
    FILE *file = fopen("user.txt", "r");
    struct new_user check_user;
    if (file == NULL)
    {
        printf("\nSorry. ID not found.\n");
        return 0;
    }

    printf("\nEnter ID: ");
    scanf("%s", id);
    printf("Enter Password: ");
    scanf("%s", password);

    
    
    while (fscanf(file, "%s %s", check_user.id, check_user.password) != EOF)
    {
        if ((strcmp(check_user.id, id) == 0 && strcmp(check_user.password, password) == 0))
        {
            printf("\nUSER LOGIN SUCCESSFUL!\n");
            fclose(file);
            user_home(id);
            return 1;
        }
    }
    fclose(file);
    
    FILE *file1 = fopen("admin.txt", "r");
    if (file1 == NULL)
    {
        printf("\nSorry. ID not found.\n");
        return 0;
    }

    while (fscanf(file1, "%s %s", check_user.id, check_user.password) !=EOF)
    {
        if ((strcmp(check_user.id, id) == 0 && strcmp(check_user.password, password) == 0))
        {
            printf("\nADMIN LOGIN SUCCESSFUL!\n");
            fclose(file1);
            admin_home();
            return 1;
        }
            
    }
    
    fclose(file);
    printf("\nSorry. Incorrect ID or Password entered. Try Again.\n\n");
    return 0;
}

int is_unique(char *id)
{
    struct new_user temp_user;
    FILE *file = fopen("user.txt", "r");
    if (file == NULL)
    {
        return 0;
    }

    while (fscanf(file, "%s %s", temp_user.id, temp_user.password) != EOF)
    {
        if (strcmp(temp_user.id, id) == 0)
        {
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;    
}

void user_home(char id[])
{
    int user_choice;
    int mark;
    int to_exit = 0;
    while(1)
    {
        printf("\n=========== USER HOME ==========\n");
        printf("\n1. Take a quiz\n");
        printf("2. View scores\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%i", &user_choice);
    
        switch(user_choice)
        {
            case(1):
                mark = take_quiz(id);
                if (mark != 99)
                {
                    printf("\nYou got %i\n", mark);
                }
                break;
            case(2):
                view_mark(id);
                break;
            case(3):
                to_exit = exit_prog();
                break;
            default:
                printf("\nInvalid choice..\nPlease try again!\n");
        }

        if (to_exit == 1)
        {
            break;
        }
        
    }
    
}


int take_quiz(char *user_id) {  
    int sl_no = 1;
    char line[256];
    char user_input[10];  
    FILE *file = fopen("quizzes.txt", "r");

    printf("\n========== CHOOSE A QUIZ ==========\n\n");
    if (file == NULL) {
        printf("\nSorry. No quizzes available currently.\n");
        return 0;  
    }

   
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        sl_no++;
    }

    
    printf("\nEnter the quiz number: ");
    scanf("%s", user_input);

    rewind(file);  
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == user_input[0]) {  
            found = 1;
            
            
            line[strcspn(line, "\n")] = '\0';  

            break;
        }
    }

    if (!found) {
        printf("\nQuiz not found!\n");
        return 99;
    }

    
    char quiz_filename[256];
    sprintf(quiz_filename, "%s.txt", line);  

    FILE *quiz_file = fopen(quiz_filename, "r");
    if (quiz_file == NULL) {
        printf("\nError: quiz does not exist.\n");
        return 99;
    }

    int line_count = 0;
    char quiz_line[256];
    int marks = 0;
    char correct_answer[10];
    char user_choice[10];  
    int n = 0;

    
    while (fgets(quiz_line, sizeof(quiz_line), quiz_file)) {
        printf("\n");
        
        if (line_count >= n && line_count < n + 5) {
            
            printf("%s", quiz_line);
        } else if (line_count == n + 5) {
            
            quiz_line[strcspn(quiz_line, "\n")] = '\0';  
            strcpy(correct_answer, quiz_line);  

            
            printf("Enter your answer: ");
            scanf("%s", user_choice);  

            
            if (strcmp(correct_answer, user_choice) == 0) {
                marks++;
            }

            
            n += 6;
        }

        line_count++;
    }

    fclose(quiz_file);  

    
    FILE *result_file = fopen("results.txt", "a");  
    if (result_file == NULL) {
        printf("Error: Could not open results.txt\n");
        return 99;
    }

   
    fprintf(result_file, "ID: %s | Quiz: %s | Marks: %d\n", user_id, &line[2], marks);
    fclose(result_file);  

    return marks;  
}


void view_mark(const char *user_id) {
    FILE *file = fopen("results.txt", "r");
    if (file == NULL) {
        printf("\nError: Could not open results.txt\n");
        return;
    }

    char line[256];
    int found = 0;

    
    while (fgets(line, sizeof(line), file)) {
       
        if (strstr(line, user_id) != NULL) {
            printf("\nResult: %s", line);  
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo results found for ID: %s\n", user_id);
    }

    fclose(file);  // Close the file
}

int exit_prog()
{
    return 1;
}

void admin_home() {
    int to_exit = 0;
    while (1) {
        printf("\n========== Admin Home ==========\n\n");
        printf("1. Add Quiz\n");
        printf("2. Exit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_quiz(); break;
            case 2: 
                exit_prog(); 
                to_exit = 1;
                break;
            default: printf("Invalid choice, please try again.\n");
        }
        if (to_exit == 1)
        {
            break;
        }
    }
}

void add_quiz()
{
    FILE *file = fopen("quizzes.txt", "r");
    char admin_choice[25];
    char line[25];
    char temp_file[25];
    char question[100];
    char option_1[100]; 
    char option_2[100]; 
    char option_3[100]; 
    char option_4[100]; 
    char answer[10];
    int to_exit = 0;
    int count = 0;
    int new_count = 1;
    char buffer[25];
    printf("\n========== ADD QUIZ ==========\n\n");
    printf("Enter quiz name: ");
    scanf("%s", admin_choice);
    while(fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';
        sprintf(buffer,"%s", &line[2]);
        if (strcmp(admin_choice, buffer) == 0)
        {
            printf("\nSorry. Quiz name already exists!\n");
            to_exit = 1;
        }
        count++;
    }

    if (to_exit == 1)
    {
        fclose(file);
        return;
    }
    fclose(file);

    FILE *quiz = fopen("quizzes.txt", "a");
    fprintf(quiz, "%i %s\n", count + 1, admin_choice);
    fclose(quiz);

    sprintf(temp_file, "%i %s.txt", count +1, admin_choice);
    FILE *quiz_1 = fopen(temp_file, "a");
    while (1)
    {
        printf("\nEnter question: ");
        getchar();  
        fgets(question, sizeof(question), stdin);  
        question[strcspn(question, "\n")] = '\0';  
        fprintf(quiz_1, "q%i) %s\n", new_count, question);

        printf("\nEnter option a: ");
        fgets(option_1, sizeof(option_1), stdin);
        option_1[strcspn(option_1, "\n")] = '\0';  
        fprintf(quiz_1, "a) %s\n", option_1);

        printf("\nEnter option b: ");
        fgets(option_2, sizeof(option_2), stdin);
        option_2[strcspn(option_2, "\n")] = '\0';
        fprintf(quiz_1, "b) %s\n", option_2);

        printf("\nEnter option c: ");
        fgets(option_3, sizeof(option_3), stdin);
        option_3[strcspn(option_3, "\n")] = '\0';
        fprintf(quiz_1, "c) %s\n", option_3);

        printf("\nEnter option d: ");
        fgets(option_4, sizeof(option_4), stdin);
        option_4[strcspn(option_4, "\n")] = '\0';
        fprintf(quiz_1, "d) %s\n", option_4);

        printf("\nEnter correct answer (e.g., a, b, c, d): ");
        scanf("%s", answer);
        fprintf(quiz_1, "%s\n", answer);
        new_count++;

        printf("\nDo you want to continue?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("\nEnter your choice: ");
        scanf("%i", &to_exit);
        if (to_exit == 2)
        {
            break;
        }
    }
    fclose(quiz_1);
    return;
}