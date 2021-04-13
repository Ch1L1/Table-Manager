/************************************************************************/
/***                 1. projekt - PrĂĄce s textem                      ***/
/***                                                                  ***/
/***                    TomĂĄĹĄ Homola (xhomol28)                       ***/
/***                                                                  ***/
/*** 15.11.2020                        Ut 8:00-9:50, as. Klobucnikova ***/
/************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_ROW_LENGTH 10243

void find_delim(char *delim, char *delic, char *buffer);
void col_count(int *num_del, char *delim, char *buffer);
int num_col_row(char *num);
int arg_process(char *buffer, int line, int argc, char *argv[], char *delim, int num_col);
void start_end_of_col(int *start, int *end, char *buffer, char *delim, int num_col);
int last_row();
void change_delim(char *buffer, char *delim);
void irow(int num_row, char *delim); 
void arow(int num_row, char *delim);
void drow(int num_row, int line, char *buffer);
void drows(int num_row_1, int num_row_2, int line, char *buffer);
void dcol(int col_to_delete, char *buffer, char *delim);
void dcols(int start_col_to_del, int end_col_to_del, char *buffer, char *delim);
void icol(int num_col, char *delim, char *buffer); 
void acol(char *delim, char *buffer);
int rows(char *start_line, char *end_line, int i_row);
int beginswith(int num_col, char *STR, char *buffer, char *delim);
int contains(int num_col, char *STR, char *buffer, char *delim);
void cset(char STR[], int num_col, char *buffer, char *delim);
void uperrtolower(char *buffer, char *delim, int num_col);
void lowertoupper(char *buffer, char *delim, int num_col);
void rounding(char *buffer, char *delim, int num_col);
void comma_del(char *buffer, char *delim, int num_col);
void copy(char *buffer, char *delim, int num_col_1, int num_col_2);
void swap(char *buffer, char *delim, int num_col_1, int num_col_2);
void move(char *buffer, char *delim, int num_col_1, int num_col_2); 


int main(int argc, char *argv[])
{
    char buffer[MAX_ROW_LENGTH];
    char delim[100];
    int num_col = 0;
    
    strcpy(delim," ");
    
    if (argc > 2 && (strcmp(argv[1], "-d")) == 0){
        strcpy(delim , argv[2]);
    }
    
    for (int line = 0; fgets(buffer, MAX_ROW_LENGTH, stdin) != NULL; line++){
        if (!line){
            col_count(&num_col, delim, buffer); 
        }
        
        change_delim(buffer, delim);

        int res_arg_process = arg_process(buffer, line, argc, argv, delim, num_col);

        if(res_arg_process == -1)
            return 1;

        printf("%s",buffer);
    }

    //funkcia arow//
    for(int j = 0; j < argc; j++){
        if(strcmp(argv[j], "arow" ) == 0) {
            arow(num_col, delim);
        }
    }

    return 0;
}

//spracovananie vstupnych argumentov//
int arg_process(char *buffer, int line, int argc, char *argv[], char *delim, int num_col)
{ 
    for(int j = 0; j < argc; j++){
        // irow //
        if(strcmp(argv[j], "irow") == 0){
            int num_row = num_col_row(argv[j+1]);
            if(num_row == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            if(line == num_row){
                irow(num_row, delim);
            }
        }
        // drow //
        if(strcmp(argv[j], "drow") == 0){
            int num_row = num_col_row(argv[j+1]);
            if(num_row == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            drow(num_row, line, buffer);
        }
        // drows //
        if(strcmp(argv[j], "drows") == 0){
            int num_row_1 = num_col_row(argv[j+1]);
            if(num_row_1 == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            int num_row_2 = num_col_row(argv[j+2]);
            if(num_row_2 == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            drows(num_row_1, num_row_2, line, buffer);
        }
        //dcol //
        if(strcmp(argv[j], "dcol") == 0){
            int col_to_delete = num_col_row(argv[j+1]);
            if(col_to_delete == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            dcol(col_to_delete, buffer, delim);
        }
        //dcols//
        if(strcmp(argv[j], "dcols") == 0){
            int start_col_to_del = num_col_row(argv[j+1]);
            if(start_col_to_del == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            int end_col_to_del = num_col_row(argv[j+2]);
            if(end_col_to_del == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            dcols(start_col_to_del, end_col_to_del, buffer, delim);
        }
        //icol//
        if(strcmp(argv[j], "icol") == 0){
            int num_col = num_col_row(argv[j+1]);
            if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            icol(num_col, delim, buffer);
        }
        //acol//
        if(strcmp(argv[j], "acol") == 0){
            acol(delim, buffer);
        }
        //rows//
        if(strcmp(argv[j], "rows") == 0){
            int i_row = rows(argv[j+1], argv[j+2], line);
            if (i_row == 1) 
                break;
            else if(i_row == -1) {
                fprintf(stderr, "Chybny vstup\n");
                return -1;
            }
        }
        //beginswith//
        if(strcmp(argv[j], "beginswith") == 0){
            int num_col = num_col_row(argv[j+1]);
            if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;
            }
            int i_row = beginswith(num_col, argv[j+2], buffer, delim);
            if (i_row == 1) 
                break;
        }
        //contains//
        if(strcmp(argv[j], "contains") == 0){
            int num_col = num_col_row(argv[j+1]);
            if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;
            }
            int i_row = contains(num_col, argv[j+2], buffer, delim);
            if (i_row == 1) 
                break;
        }    
        //cset//
        if(strcmp(argv[j], "cset") == 0){
            int num_col = num_col_row(argv[j+1]);
            if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            cset(argv[j+2], num_col, buffer, delim);
            if(num_col == 1)
                break;
        }
        //tolower//
        if(strcmp(argv[j], "tolower") == 0){
            int num_col = num_col_row(argv[j+1]);
            if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            uperrtolower(buffer, delim, num_col);
        }
        //toupper//
        if(strcmp(argv[j], "toupper") == 0){
            int num_col = num_col_row(argv[j+1]);
            if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            lowertoupper(buffer, delim, num_col);
        }
        //copy//
        if(strcmp(argv[j], "copy") == 0){
            int num_col_1 = num_col_row(argv[j+1]);
             if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            int num_col_2 = num_col_row(argv[j+2]);
             if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            copy(buffer, delim, num_col_1, num_col_2);
        }
        //int//
        if(strcmp(argv[j], "int") == 0){
            int num_col = num_col_row(argv[j+1]);
            if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            comma_del(buffer, delim, num_col);
        }
        //swap//
        if(strcmp(argv[j], "swap") == 0){
            int num_col_1 = num_col_row(argv[j+1]);
             if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            int num_col_2 = num_col_row(argv[j+2]);
             if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            swap(buffer, delim, num_col_1, num_col_2);
        }
        //move//
        if(strcmp(argv[j], "move") == 0){
            int num_col_1 = num_col_row(argv[j+1]);
             if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            int num_col_2 = num_col_row(argv[j+2]);
             if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            move(buffer, delim, num_col_1, num_col_2);
        } 
        //round//
        if(strcmp(argv[j], "round") == 0){
            int num_col = num_col_row(argv[j+1]);
            if(num_col == -1){
                fprintf(stderr, "Chybny vstup\n");
                return -1;    
            }
            rounding(buffer, delim, num_col);  
        }
    }
    return 0;
}
        //POMOCNE FUNKCIE//

//Najde a urci znak delimiteru//
void find_delim(char *delim, char *delic, char *buffer){
    for(int j = 0; j < (int)strlen(delic); j++){
        if(strchr(buffer, delic[j])){
            *delim = delic[j];
            break;
        }              
    }
}

//spocitanie stlpcov v riadku
void col_count(int *num_del, char *delic,char *buffer){
    char *p = buffer;
    int length = 1;
    char act_del = 0;

    find_delim(&act_del, delic, buffer);

    while ((p = strchr(p, act_del)) != NULL){
        p += length;         //posun za delimiter
        (*num_del)++;       //pocet delimiterov
        find_delim(&act_del, delic, p);
    }
    (*num_del)++;           //= pocet delitelov++ = pocet stlpcov
}

//kontroluje a vrati korektne cislo zo vstupu
int num_col_row(char *num){
    char *zvysok = NULL;
    int number = strtol(num, &zvysok, 10); 
    if(number < 1)
        return -1; 
    if (num != zvysok && zvysok[0] == 0)
        return number;
    return -1;
}

//najde zaciatok a koniec bunky, ktoru editujeme
void start_end_of_col(int *start, int *end, char *buffer, char *delim, int num_col){
    char *start_of_col = buffer;
    char *end_of_col = buffer;
    int i = 0;
    char actual_del = 0;

    find_delim(&actual_del, delim, buffer);

    while ((end_of_col = strchr(end_of_col, actual_del)) != NULL){
        end_of_col += 1;
        i++;
        if (i == num_col){
            break;
        }
        start_of_col = end_of_col;
        find_delim(&actual_del, delim, end_of_col);
    }
    *start = strlen(buffer) - strlen(start_of_col);     //index na zaciatok bunky

    if(end_of_col == NULL)
        *end = strlen(buffer);
    else
        *end = strlen(buffer) - strlen(end_of_col);     //index na koniec bunky
}

//skontroluje, ci sa nachadzam na poslednom riadku
int last_row(){
    int znak = fgetc(stdin);
    if (znak == EOF){
        return 1;
    }
    ungetc(znak, stdin);
    return 0;
}

//nahradenie deliaceho znaku za jednotny (1. v poradi zo vstupu)//
void change_delim(char *buffer, char *delim){
    int row_len = strlen(buffer);
    for(int j = 0; j < row_len; j++){
        if(strchr(delim, buffer[j]))
            buffer[j] = delim[0];
    }
}
        //UPRAVA TABULKY//

//irow funkcia - vlozi prazdny riadok//
void irow(int num_row, char *delim)
{
    for(int i = 0; i < num_row; i++){
        printf("%c",delim[0]);
    }
    printf("\n");
}

//arow function - prida riadok s prazdnymi bunkami na koniec tabulky
void arow(int num_row, char *delim)
{
    for(int i = 1; i < num_row; i++){
        printf("%c",delim[0]);
    }
    printf("\n");
}

//drow funkcia - odstrani cely riadok
void drow(int num_row, int line, char *buffer){
        if(line == num_row-1)
            buffer[0] = '\0';
}


//drows funkcia - odstrani nam riadky N aĹž M (pos aĹž pos2)
void drows(int pos, int pos2, int line, char *buffer)
{
   if (pos-1 <= line && pos2-1 >= line){
       buffer[0] = '\0';
   }
}

//dcol funkcia - odstrani stlpec C
void dcol(int col_to_delete, char *buffer, char *delim)
{
    //lokalizovanie hladanej bunky//
    char *col_end = buffer;
    char *col_start = buffer;
    int i_start_col;
    int i_end_col;

    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, col_to_delete);

    col_start += i_start_col;

    if(i_end_col >= (int)strlen(buffer))
        col_end = NULL;
    else 
        col_end += i_end_col;

    //odstranenie danej bunky a posun riadku//
    if(col_end != NULL) {
    memmove(col_start, col_end, (strlen(col_end)+1));
    }
    else {
        col_start[0] = '\0';
        col_start[-1] = '\n';
    }
}

//dcols funkcia - odstrani stlpce A az B (start_col_to_del az end_col_to_del) 
void dcols(int start_col_to_del, int end_col_to_del, char *buffer, char *delim){
    int del_cols = 0;
    for(int i = start_col_to_del; i <= end_col_to_del; i++){
        dcol(i-del_cols, buffer, delim);
        del_cols++;
    }
}


// icol funkcia - prida prazdny stlpec //
void icol(int num_col, char *delim, char *buffer){
    //lokalizovanie hladanej bunky
    char *col_end = buffer;
    char *col_start = buffer;
    int i_start_col;
    int i_end_col;
    
    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, num_col);

    col_start += i_start_col;

    if(i_end_col >= (int)strlen(buffer))
        col_end = NULL;
    else 
        col_end += i_end_col;

    //pridanie delimiteru(vytvorenie noveho stlpca) a posun znakov v riadku
    memmove(col_start+1, col_start, (strlen(col_start)+1));

    col_start[0] = delim[0];
}
    

// acol funkcia - prida prazdny stlpec za posledny stlpec //
void acol(char *delim, char *buffer){
    size_t buf_len = strlen(buffer)-1;
    strcpy(&buffer[buf_len],delim);
    strcpy(&buffer[buf_len+1],"\n");
}

            // SELEKCE RADKU //

//rows funkcia - spracovanie iba riadkov N - M//
int rows(char *start_line, char *end_line, int i_row){
    char *zvysok = NULL;
    int end_row = strtol(end_line, &zvysok, 10);
    int start_row = strtol(start_line, &zvysok, 10); //riadok, od ktoreho to zacne spracovavat
    
    if(strcmp(start_line, "-") == 0 && strcmp(end_line, "-") == 0 && !last_row())
        return 1;
    else if(strcmp(start_line, "-") == 0 && strcmp(end_line, "-") == 0 && last_row())  
        return 0;

    if (zvysok == start_line || zvysok[0] != '\0')
        return -1; 

    if(strcmp(end_line, "-") == 0 && start_row > i_row+1)
        return 1;
    else if(strcmp(end_line, "-") == 0)
        return 0;
    
    if (zvysok == end_line || zvysok[0] != '\0')
        return -1; 

    if(start_row > i_row+1 || end_row < i_row+1)
        return 1;
        
    return 0;
}

//beginswith funkcia - spracovanie riadkov, ktore obsahuju bunku, ktora zacina retazcom STR//
int beginswith(int num_col, char *STR, char *buffer, char *delim){
    //lokalizovanie hladanej bunky
    char *col_end = buffer;
    char *col_start = buffer;
    int i_start_col;
    int i_end_col;

    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, num_col);

    col_start += i_start_col;

    if(i_end_col >= (int)strlen(buffer))
        col_end = buffer + strlen(buffer)-1;
    else 
        col_end += i_end_col;
    //zistenie, ci sa retaze STR nachadza na zaciatku bunky
    if (strncmp(col_start, STR, strlen(STR)) == 0)
        return 0;
    return 1;       
}

//contains funkcia - spracovanie riadkov, ktore obsahuju bunku, ktora je totozna s retazcom STR//
int contains(int num_col, char *STR, char *buffer, char *delim){
    //lokalizovanie hladanej bunky
    char *col_end = buffer;
    char *col_start = buffer;
    int i_start_col;
    int i_end_col;

    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, num_col);

    col_start += i_start_col;

    if(i_end_col >= (int)strlen(buffer))
        col_end = buffer + strlen(buffer)-1;
    else 
        col_end += i_end_col;
    
    //porovnanie bunky s retazcom zo vstupu
    int cell_length = strlen(col_start) - strlen(col_end);
    char cell[cell_length+1];

    strncpy(cell, col_start, cell_length);
    char *found = strstr(cell, STR);

    if (found == NULL)
        return 1;
    return 0;
}
    
        //Zpracovani dat//

//cset - zameni bunku za retazec zo vstupu
void cset(char STR[], int num_col, char *buffer, char *delim){
    //lokalizovanie bunky
    char *col_end = buffer;
    char *col_start = buffer;
    int i_start_col;
    int i_end_col;
    int length = 1;
    int STR_len = strlen(STR);
    int cell_len = 0;

    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, num_col);

    col_start += i_start_col;

    if(i_end_col >= (int)strlen(buffer))
        col_end = NULL;
    else 
        col_end += i_end_col;

    if (col_end == NULL)    // posledny stlpec
    {
        col_end = col_start+strlen(col_start)-1;    // -1 pre \n
        length = 0;
    }
    cell_len = strlen(col_start) - strlen(col_end); //dlzka bunky na zamenenie
    col_end = col_end - length;
    int cell_offset = STR_len - cell_len +length;

    memmove(col_end+cell_offset, col_end, strlen(col_end)+1);
    strncpy(col_start, STR, STR_len);
}

//funkcia tolower - zameni vsetky pismenka v retazci za male pismena

void uperrtolower(char *buffer, char *delim, int num_col){
    char *col_end = buffer;
    char *col_start = buffer;
    int i_start_col;
    int i_end_col;

    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, num_col);

    col_start += i_start_col;

    if(i_end_col >= (int)strlen(buffer))
        col_end = buffer + strlen(buffer)-1;
    else 
        col_end += i_end_col;
    
    for(int i = i_start_col; i < i_end_col; i++) {
        buffer[i] = tolower(buffer[i]);
    }
}

//funkcia toupper - zameni vsetky pismenka v retazci za velke pismena

void lowertoupper(char *buffer, char *delim, int num_col){
    char *col_end = buffer;
    char *col_start = buffer;
    int i_start_col;
    int i_end_col;

    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, num_col);

    col_start += i_start_col;

    if(i_end_col >= (int)strlen(buffer))
        col_end = buffer + strlen(buffer)-1;
    else 
        col_end += i_end_col;
    
    for(int i = i_start_col; i < i_end_col; i++) {
        buffer[i] = toupper(buffer[i]);
    }    
}

//int funkcia - odstrani desatinnu cast cisla

void comma_del(char *buffer, char *delim, int num_col){
    char *col_end = buffer;
    char *col_start = buffer;
    int i_start_col;
    int i_end_col;

    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, num_col);

    col_start += i_start_col;

    if(i_end_col >= (int)strlen(buffer))
        col_end = buffer + strlen(buffer)-1;
    else 
        col_end += i_end_col;

    const char dot = '.';
    char *find_dot = strchr(col_start, dot);

    if(find_dot == NULL || strlen(col_end) > strlen(find_dot))
        return;

    int i = 1;
    if(i_end_col >= (int)strlen(buffer))
       i = 0;  
    
    memmove(find_dot, col_end-i, strlen(col_end)+2);   
}

//swap funkcia - zameni hodnoty buniek num_col_1 a num_col_2

void swap(char *buffer, char *delim, int num_col_1, int num_col_2){
    //stlpec cislo 1
    char *col_start_1 = buffer;
    int i_start_col;
    int i_end_col;

    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, num_col_1);

    col_start_1 += i_start_col;

    int cell_length = i_end_col - i_start_col;
    char cell_1[cell_length];
    cell_1[cell_length-1] = '\0'; 
    strncpy(cell_1, col_start_1, cell_length-1);   

    //stlpec cislo 2
    char *col_start_2 = buffer;
    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, num_col_2);

    col_start_2 += i_start_col;

    cell_length = i_end_col - i_start_col;
    char cell_2[cell_length];
    cell_2[cell_length-1] = '\0'; 
    strncpy(cell_2, col_start_2, cell_length-1);

    //prepis bunky a posunutie pamate
    cset (cell_2, num_col_1, buffer, delim);
    cset (cell_1, num_col_2, buffer, delim);
}  

//copy funkcia - prepis buniek
void copy(char *buffer, char *delim, int num_col_1, int num_col_2){
    //identifikacia stlpu na kopirovanie
    char *col_start_1 = buffer;
    int i_start_col;
    int i_end_col;

    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, num_col_1);

    col_start_1 += i_start_col;

    int cell_length = i_end_col - i_start_col;
    char cell_1[cell_length];
    cell_1[cell_length-1] = '\0'; 
    strncpy(cell_1, col_start_1, cell_length-1);

    //prepis bunky a posunutie pamate
    cset (cell_1, num_col_2, buffer, delim);
}  

//move funkcia - presunie stlpec num_col_1 pred num_col_2

void move(char *buffer, char *delim, int num_col_1, int num_col_2){
    char *col_start = buffer;
    int i_start_col;
    int i_end_col;

    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, num_col_1);

    col_start += i_start_col;  

    int cell_length = i_end_col - i_start_col;
    char cell_1[cell_length];
    cell_1[cell_length-1] = '\0'; 
    strncpy(cell_1, col_start, cell_length-1);

    icol(num_col_2, delim, buffer);

    cset(cell_1, num_col_2, buffer, delim);
    
    if(num_col_1 > num_col_2) //po pridani stlpcu sa posunu indexy,i_num_col_1 je nutne posun o 1 doprava
        num_col_1++;

    dcol(num_col_1, buffer, delim);
}

//round funkcia - zaokruli cislo v bunke
void rounding(char *buffer, char *delim, int num_col){
    char *col_start = buffer;
    char *col_end = buffer;
    int i_start_col;
    int i_end_col;
    int last_col_offset = -1;

    start_end_of_col(&i_start_col, &i_end_col, buffer, delim, num_col);

    col_start += i_start_col;

    if(i_end_col >= (int)strlen(buffer)){
        col_end = buffer + strlen(buffer)-1;
        last_col_offset = 0;
    }
    else 
        col_end += i_end_col;

    int cell_length = i_end_col - i_start_col;
    char cell_1[cell_length];
    cell_1[cell_length-1] = '\0'; 

    strncpy(cell_1, col_start, cell_length-1);

    float float_num = atof(cell_1); 

    int n = (int)(float_num < 0 ? (float_num - 0.5) : (float_num + 0.5));

    sprintf(col_start, "%d%s", n, col_end+last_col_offset); 
}
