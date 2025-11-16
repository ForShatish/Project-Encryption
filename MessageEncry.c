#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

typedef struct UserInfo {
    char name[50];
    char passwd[50];
    char key[50];
} user ;

char headline[128] ;
char hyphenline[54];
char equal_line[54];

void InitLines();
void DisplayPage(char *MenuItems[] , int n);
void GeneratePassword(user *prsnptr);
void CreateAccount(user *prsnptr);
int LoginAccount(user *prsnptr);
int CheckPassword(user *prsnptr , char password[] , char purpose[]);
int PersonScreen(user *prsnptr);
int EncrypDecryp(char purpose[], char key[], char message[]);

int main(){
    
    system("chcp 65001 > nul");
    InitLines();
    user person;
    user *prsnptr = &person ;
    int command ;

    char *MenuItems[] = {
        "ENCRYPTING YOUR MESSAGE", 
        "1. CREATE AN ACCOUNT", 
        "2. LOGIN TO ACCOUNT", 
        "3. EXIT",
        "ENTER YOUR COMMAND : "
    };
    while(1){
        DisplayPage(MenuItems , 5); 
        scanf("%d",&command);
        
        int buffclr;
        while((buffclr = getchar()) != '\n' && buffclr != EOF);

        if (command==1) {
            CreateAccount(prsnptr);
            PersonScreen(prsnptr);
        }
        else if (command==2){
            if (LoginAccount(prsnptr)) {
                printf("\n\n"); 
                PersonScreen(prsnptr); 
            }
        }
        else if (command==3) {
            printf("\n\nAPPERICIATE YOUR TIME VIEWING OUR PROGRAM 🥰🥰\nTHANK YOU!!!");
            break;
        }
        else {
            printf("\n\n😭😭 OOPS!!! LOOK LIKE YOU HAVE ENTERED SOMETHING WRONG.\nPLEASE PICK ONE FROM THE LISTED OPTIONS!!!\n\n");
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

void DisplayPage(char *MenuItems[] , int n){
    
    puts(headline);

    printf("\n\t\t\t\t\t\t  %s\n\n",MenuItems[0]);
    
    printf("\t\t\t\t  ");
    puts(hyphenline);

    for (int i=1 ; i<=n-2 ; i++){
        printf("\n\t\t\t\t\t\t  %s",MenuItems[i]);
    }

    printf("\n\n\t\t\t\t  ");
    puts(hyphenline);

    puts(headline);

    printf("\n\t\t\t\t\t\t  %s",MenuItems[n-1]);

}

void GeneratePassword(user *prsnptr){

    srand(time(NULL));
    char password[8];
    int min_namelen = strlen(prsnptr->name);
    if ( min_namelen > 4 ) { min_namelen=4; }
    strncpy(password , prsnptr->name , min_namelen);

    while(1){
        //genrating num for password i.e name(4) + num(3)
        int n = (rand() % 900) + 100 ;
        sprintf(password+min_namelen , "%d" , n); //sprintf(& , fs , value);
        password[min_namelen+3] = '\0' ;

        if (CheckPassword(prsnptr,password,"Create")) { continue ; }

        // confirm password 
        strcpy(prsnptr->passwd , password);
        break;
    }
}

void CreateAccount(user *prsnptr){
     
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
    printf("\nYOUR PASSWORD IS : %s\n\n",prsnptr->passwd);

    FILE *fptr = fopen("UsersInfo.txt","a");
    fprintf(fptr , "%s : %s : %s\n" , prsnptr->name , prsnptr->passwd , prsnptr->key);
    fclose(fptr);

    printf("\t\t\t\t  %s\n\n",equal_line);
    printf("\t\t\t\t\t YOUR ACCOUNT IS CREATED SUCCESSFULLY\n\n");
    printf("\t\t\t\t  %s\n\n",equal_line);
  
}

int LoginAccount(user *prsnptr){

    puts(headline);
    printf("\n\t\t\t\t\t\t  SIGN-IN YOUR ACCOUNT\n");
    puts(headline);

    printf("\nEnter Your Password : ");
    scanf("%s",prsnptr->passwd);
    strupr(prsnptr->passwd);
    if (CheckPassword(prsnptr,prsnptr->passwd,"Login")) { return 1; }

    printf("\n😭😭 OOPS!!! YOUR ENTERED PASSWORD DOESNT EXIST IN OUR CURRENT DATABASE\nPLESAE TRY AGAIN.\n\n");
    return 0;
}

int CheckPassword(user *prsnptr , char password[] , char purpose[]){

    char stored_name[50] , stored_passwd[50] , stored_key[50] ;
    FILE *fptr = fopen("UsersInfo.txt", "r");
    if (fptr != NULL){
        while ( fscanf(fptr, "%s : %s : %s", stored_name, stored_passwd, stored_key) != EOF) {
            if (strcmp(password, stored_passwd) == 0) {
                if (strcmp("Login",purpose) == 0) {
                    strcpy(prsnptr->name , stored_name);
                    strcpy(prsnptr->key , stored_key);
                }
                fclose(fptr);
                return 1; 
            }
        } 
    }    
    fclose(fptr);
    return 0;
}

int PersonScreen(user *prsnptr){
    
    int command ;
    char *MenuItems[] = {
        "WELCOME TO YOUR DASHBOARD",
        "1. SEND A MESSAGE",
        "2. VIEW YOUR MESSAGES",
        "3. DELETE A MESSAGE",
        "4. LOGOUT",
        "ENTER YOUR COMMAND : "
    };

    while (1){
        DisplayPage(MenuItems , 6);
        scanf("%d",&command);

        int buffclr;
        while((buffclr = getchar()) != '\n' && buffclr != EOF);

        if (command == 1){
            char message[150];
            printf("\n\nWrite Your Message From Here : ");
            fgets(message,150,stdin);

            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            char date[11] , time[9] ;
            sprintf(date , "%02d-%02d-%04d" , t->tm_mday,t->tm_mon+1,t->tm_year+1900);
            sprintf(time , "%02d:%02d:%02d" , t->tm_hour,t->tm_min,t->tm_sec);
            EncrypDecryp("Encryp",prsnptr->key,message);

            FILE *fptr = fopen("Message.txt","a");
            fprintf(fptr , "%s : %s : %s : %s" , prsnptr->passwd,date,time,message);
            fclose(fptr);

            printf("\n\t\t\t\t  %s\n\n",equal_line);
            printf("\t\t\t\t\t\tMESSAGE ADDED SUCCESSFULLY\n\n");
            printf("\t\t\t\t  %s\n\n",equal_line);
        }
        else if ( command == 2){
            FILE *fptr = fopen("Message.txt","r");
            if (fptr==NULL){ 
                printf("\n\n😅😅 OOPS!!! LOOK LIKE YOU HAVENT ENTERD A MESSAGE YET.\n\n");
                continue ;
            }
            char passwd[50] , date[11] , time[9] , msg[150] ;
            while(fscanf(fptr, "%s : %s : %s : %[^\n]", passwd,date,time,msg) != EOF){
                if(strcmp(prsnptr->passwd,passwd)==0){
                    printf("\n\nDate : %s\nTime : %s\n\nEncrypted message :  %s",date,time,msg);

                    char key[50] ;
                    printf("\n\nEnter Your Key To Decrypt : ");
                    scanf("%s",key);

                    if (strcmpi(key,prsnptr->key)==0){
                        printf("\nDecrypted message : ");
                        EncrypDecryp("Decryp",key,msg);
                        printf("\n\n");
                        continue ;
                    }
                    break;
                }
            }
        }
        else if ( command == 3){
            printf("Pending");
        }
        else if ( command == 4) {
            break;
        }
        else {
            printf("\n\n😭😭 OOPS!!! LOOK LIKE YOU HAVE ENTERED SOMETHING WRONG.\nPLEASE PICK ONE FROM THE LISTED OPTIONS!!!\n\n");
        }
    }
}

int EncrypDecryp(char purpose[], char key[], char message[]){

    int key_len = strlen(key);
    int msg_len = strlen(message);
    strupr(key);
    for(int i=0 ; i<msg_len ; i++){
        if (isalpha(message[i])){
            int c_index = (toupper(message[i]) - 'A');
            char key_char = key[i%key_len];
            int k_index = (key_char-'A');

            if(strcmp(purpose,"Encryp") == 0){
                char encry_c = ((c_index + k_index) % 26) + 'A' ;
                message[i]=(message[i]>='a' && message[i]<='z') ? tolower(encry_c) : encry_c ;  
            }
            else{
                char decry_c = ((c_index - k_index + 26) % 26) + 'A';  
                printf("%c", (message[i] >= 'a' && message[i] <= 'z') ? tolower(decry_c) : decry_c);
            }
        }
        else if (strcmp(purpose,"Decryp") == 0){ printf("%c",message[i]);}
    }

}
 