#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct UserInfo {
    char name[50];
    char passwd[50];
    char key[50];
} user ;

char headline[128] ;
char hyphenline[54];
char equal_line[54];

void InitLines();
void GeneratePassword(user *prsnptr);
void DisplayPage();
void CreateAccount();

int main(){
    
    InitLines();
    int command ;

    while(1){
        DisplayPage(); 
        scanf("%d",&command);
        
        int buffclr;
        while((buffclr = getchar()) != '\n' && buffclr != EOF);

        if (command==1) {
            CreateAccount();
        }
        else if (command==2){
            printf("PENDING\n");
        }
        else if (command==3) {
            printf("PENDING\n");
        }
        else {
            printf("\n\nOOPS!!! LOOK LIKE YOU HAVE ENTERED SOMETHING WRONG.\nPLEASE PICK ONE FROM THE LISTED OPTIONS!!!\n\n");
        }
    }
    
}

void InitLines(){
    memset(headline , '_' , 127);
    headline[127]='\0';

    memset(hyphenline , '-' , 53);
    hyphenline[53]='\0';

    memset(equal_line , '=' , 53);
    equal_line[53]='\0';

}

void GeneratePassword(user *prsnptr){

    srand(time(NULL));
    char password[8];
    int min_namelen = strlen(prsnptr->name);
    if( min_namelen > 4 )
        min_namelen=4;
    strncpy(password , prsnptr->name , 4);

    while(1){
        //genrating num for password i.e name(4) + num(3)
        int n = (rand() % 900) + 100 ;
        sprintf(password+min_namelen , "%d" , n); //sprintf(& , fs , value);
        password[min_namelen+3] = '\0' ;

        //check for exisiting password
        char stored_name[50] , stored_passwd[50] , stored_key[50] ;
        FILE *fptr = fopen("users.txt", "r");
        if (fptr != NULL){
            int found = 0 ;
            while ( fscanf(fptr, "%s %s %s", stored_user, stored_passwd, stored_key) != EOF) {
                if (strcmp(password, stored_passwd) == 0) {
                    found=1;
                    fclose(fptr);
                    break;
                }
            } 
            if (found==1)
                continue;
        }    

        //confirm password
        fclose(fptr);
        strcpy(prsnptr->passwd , password);
        break;
    }
}

void DisplayPage(){

    const char *MenuItems[] = {
        "ENCRYPTING YOUR MESSAGE", 
        "1. CREATE AN ACCOUNT", 
        "2. LOGIN TO ACCOUNT", 
        "3. EXIT",
        "ENTER YOUR COMMAND : "
    };
    
    puts(headline);

    printf("\n\t\t\t\t\t\t  %s\n\n",MenuItems[0]);
    
    printf("\t\t\t\t  ");
    puts(hyphenline);

    printf("\n\t\t\t\t\t\t  %s",MenuItems[1]);
    printf("\n\t\t\t\t\t\t  %s",MenuItems[2]);
    printf("\n\t\t\t\t\t\t  %s\n\n",MenuItems[3]);

    printf("\t\t\t\t  ");
    puts(hyphenline);

    puts(headline);

    printf("\n\t\t\t\t\t\t  %s",MenuItems[4]);

}

void CreateAccount(){
     
    user person;
    user *prsnptr = &person ;
    puts(headline);
    printf("\n\t\t\t\t\t\t  SIGN-UP YOUR ACCOUNT\n");
    puts(headline);

    printf("\nEnter Your Username (without spaces) : ");
    scanf("%s",prsnptr->name); 
    strupr(prsnptr->name);
    printf("Enter Your Encryption Key (eg: LEMON) : ");
    scanf("%s",prsnptr->key);
    strupr(prsnptr->key);

    GeneratePassword(prsnptr);
    strupr(prsnptr->passwd);
    printf("\npYOUR PASSWORD IS : %s\n\n",prsnptr->passwd);

    FILE *fptr = fopen("UsersInfo.txt","a");
    fprintf(fptr , "%s %s %s\n" , prsnptr->name , prsnptr->passwd , prsnptr->key);
    fclose(fptr);

    printf("\t\t\t\t  %s\n\n",equal_line);
    printf("\t\t\t\t\t YOUR ACCOUNT IS CREATED SUCCESSFULLY\n\n");
    printf("\t\t\t\t  %s\n\n",equal_line);

    
}