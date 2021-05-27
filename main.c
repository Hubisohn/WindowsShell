#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <windows.h>
#include<sys/stat.h>

char command(char comm[50]){

    printf("\n>");
    scanf("%s", comm);

    return comm[50];
}

void help(){

    printf("----Help----\n");
    printf("Commands:\n");
    printf("> ls - display of the contents of a folder or the current working directory\n"
           "  if no folder is specified\n"
           "> cd - current working directory\n"
           "> cat - display the content of one or more files\n"
           "> rm - delete a file\n"
           "> mv - move a file\n"
           "> cp - Copy the contents of a file\n"
           "> echo - output text\n"
           "> mkdir - create a directory\n"
           "> rmdir - delete a directory\n"
           "> pwd - output the current working directory\n"
           "> chmod - change the rights of users (the number method (e.g. 754)\n"
           "  enough)\n"
           "> touch - create a file\n"
           "> help - show help, list of all commands and brief description of how them\n"
           "  function\n"
           "> exit - exit the shell"
           "\n");
}

char cd(char direc[1000]){

    printf("Please enter your Path:\n");
    scanf("%s", direc);

    chdir(direc);

    return direc[1000];
}

void cat(){

    char arr[100];
    char printread[1000];

    FILE *read;

    printf("Please enter the name of your file:\n");
    scanf("%s", arr);

    read = fopen(arr, "r");

    while(fscanf(read, "%s", printread) != EOF){
        printf("%s ", printread);
    }


}

void pwd(){

    char where [100];

    getcwd(where, 100);
    printf("%s", where);
}

void ls(){

    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(".")) == NULL)
        perror("opendir() error\n");
    else {
        printf("Files in your Folder:\n");
        while ((entry = readdir(dir)) != NULL)
            printf("  %s\n", entry->d_name);
        closedir(dir);
    }


}

void echo(){

    char satz[1000];

    printf("Enter your word/sentence:\n");
    fflush(stdin);
    fgets(satz, 1000, stdin);

    printf("%s", satz);

}

void rm(){

    char name[100];

    printf("Please enter the file name:\n");
    fflush(stdin);
    gets(name);
    fflush(stdin);

    if(remove(name) == 0){
        printf("File deleted!");
    }else{
        perror("Error!");
    }

}

void mkdirec(){

    char filename[50];

    printf("Please enter the Name of your Folder:\n");
    fflush(stdin);
    gets(filename);

    if(mkdir(filename) != 0){
        perror("Error while creating Directory. Please try again!");
    }else{
        printf("Successfully created Directory");
    }

}

void movefile(){

    char filename[50];
    char direc[1000];
    BOOL check;

    printf("Please enter the File name:\n");
    fflush(stdin);
    scanf("%s", filename);

    printf("Please enter the Directory\n");
    fflush(stdin);
    gets(direc);

    strcat(direc, "\\");
    strcat(direc, filename);


    check = MoveFile(filename, direc);

    if(check == FALSE){
        perror("File not moved!");
    }else {
        printf("File moved!");
    }

}

void rmdirec(){

    char foldername[50];

    printf("Please enter your foldername:\n");
    fflush(stdin);
    gets(foldername);
    fflush(stdin);

    if(rmdir(foldername) != 0){
        perror("Error!");
    }else{
        printf("Folder removed!");
    }

}

void touch(){

    FILE *file;
    char name[15];

    printf("Please enter your File name:\n");
    fflush(stdin);
    gets(name);
    fflush(stdin);

    if((file = fopen(name, "w"))){
        printf("File created!");
    }else{
        perror("Error while creating file!");
    }

    fclose(file);
}

void cp(char direc[1000]){

    FILE *file;
    FILE *filenm2;

    char name[20];
    char fulltxt[100000];
    char c;

    printf("Please enter the filename of the file you want to copy!\n");
    fflush(stdin);
    gets(name);
    fflush(stdin);

    file = fopen(name, "r");

    int i = 0;

    while(c != EOF){
        c = fgetc(file);
        fulltxt[i] = c;
        i++;
    }

    printf("Please enter the path, where you want to copy your File:\n");
    fflush(stdin);
    cd(direc);
    fflush(stdin);

    filenm2 = fopen(name, "w");

    i = 0;
    c = 'a';

    while(c != EOF){
        c = fulltxt[i];
        fputc(c, filenm2);
        i++;
    }

    fclose(file);
    fclose(filenm2);

    printf("Copyed!");

}

int convertChmodValue(int x){
    int ret=0;

    int values[] = {400, 200, 100, 40, 20, 10, 4, 2, 1};
    int dez[]    = {256, 128, 64,  32, 16,  8, 4, 2, 1};
    int i;
    for(i=0; i<9; i++){
        if(x - values[i] >= 0){
            x = x - values[i];
            ret = ret + dez[i];
        }
    }

    if(x==0){
        return ret;
    }else{
        return -1;
    }
}


int chmodfunk(){

    int temp = 0;
    char argv[100];

    fflush(stdin);
    printf("Please enter filename:\n");
    gets(argv);
    fflush(stdin);
    printf("Please enter the Permission:\n");
    scanf("%d", &temp);
    fflush(stdin);

    if(convertChmodValue(temp) != -1){
        chmod(argv, convertChmodValue(temp));
        printf("DONE\n");
    }else{
        printf("WRONG VALUE\n");
    }

    return 0;
}



int checkcomm(char comm[50], int commnumb, int *fin, char direc[1000]){

    if(strcmp(comm, "help") == 0){
        help();
    }else if(strcmp(comm, "exit") == 0){
        (*fin)++;
        commnumb++;
    }else if(strcmp(comm, "cat") == 0) {
        cat();
    }else if(strcmp(comm, "ls") == 0){
        ls();
    }else if(strcmp(comm, "cd") == 0){
        direc[999] = cd(direc);
        printf("Sie befinden sich nun in: ");
        pwd();
    }else if(strcmp(comm, "rm") == 0){
        rm();
    }else if(strcmp(comm, "mv") == 0){
        movefile();
    }else if(strcmp(comm, "cp") == 0){
        cp(direc);
    }else if(strcmp(comm, "echo") == 0){
        echo();
    }else if(strcmp(comm, "mkdir") == 0){
        mkdirec();
    }else if(strcmp(comm, "rmdir") == 0){
        rmdirec();
    }else if(strcmp(comm, "pwd") == 0){
        pwd();
    }else if(strcmp(comm, "chmod") == 0){
        chmodfunk();
    }else if(strcmp(comm, "touch") == 0){
        touch();
    }else
        printf("Command not found! Please enter a valid one:\n");

    return commnumb;
}


int main() {

    char comm[50];
    int commnumb = 0;
    int *fin;
    int end = 0;
    char direc[1000];
    fin = &end;

    printf("Welcome in your Shell!\n");

    while(*fin == 0) {

        while (commnumb == 0) {
            comm[49] = command(comm);
            commnumb = checkcomm(comm, commnumb, fin, direc);
        }
        printf("Danke, dass Sie unsere Software benutzt haben. Schoenen Tag!");
    }
    return 0;
}