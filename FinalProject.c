#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINES 1000 //This is a constant that states that we think the maximum number of lines in a file is 1000
#define MAX_LEN 1000 //This is a constant that states that we think the maximum expected lenght of a line in a file is 1000

void write_input_files(){     //Writes the input file to read the integers from
    char filename[]="d4.txt";
    FILE *fpointer = fopen(filename,"w");
    fprintf(fpointer,"This course consists of a study of general language design and evaluation. The course will include examination of the design issues of various language constructs, design choices for these constructs in various languages, and comparison of design alternatives. Students will program in a variety of programming languages (FORTAN, C, C++, Java, C#, Lisp, and Prolog) to gain a better understanding of theoretical discussion. In addition, students will get exposure to other languages ranging from Algol-60 to Ada-95.");
    fclose(fpointer);
}

void d1(){

    char d1[MAX_LINES][MAX_LEN],temp[20];   //2D charecter array with the constant deminsions. Alse we create "temp" charecter array or "temp string" in order to use for sorting later
    char spcChar[MAX_LINES][MAX_LEN]; //2D charecter array with the constant deminsions
    char stpWords[MAX_LINES][MAX_LEN]; //2D charecter array with the constant deminsions
    
    FILE *d1file = fopen("d1.txt","r"); //Reads input file
    FILE *spcfile = fopen("specialcharacters.txt","r"); //Reads input file
    FILE *stpfile = fopen("stopwords.txt","r"); //Reads input file
    FILE *tokenfile = fopen("Tokenizedd1.txt", "w"); 
    
    if (d1file == NULL || spcfile == NULL || stpfile == NULL){
        fprintf(stderr,"Error opening file.\n"); //If compiler cant open the file, returns an error through function "stderr"
        exit(1);                                 //We return one as it is a signal to the terminal to signify something is wrong
    } 
    
    int d1line = 0;            //Line keeps track of the current line we are reading in from the file and lets us know where to put it in the 2D array and how many lines are actually in the file
    int spcline = 0;            //Line keeps track of the current line we are reading in from the file and lets us know where to put it in the 2D array and how many lines are actually in the file
    int stpline = 0;            //Line keeps track of the current line we are reading in from the file and lets us know where to put it in the 2D array and how many lines are actually in the file
    while(fgets(spcChar[spcline],MAX_LEN,spcfile) !=NULL){     //Loop that stops when we reach the end of the file or there is an error. When "feo" returns True, end of file, ferror is error. 
        spcChar[spcline][strlen(spcChar[spcline]) - 2] = '\0';
               //"fgets" reads the next line in the file by storing the current line in "D1", its going to store a mx number of charecters "MAX_LEN", and reads from the pointer file "d1file". //fgets will return "NULL" when it hits the end of the file. The line will increment if fegets is not equal to NULL
        spcline++;
        
    }
    while(fgets(stpWords[stpline],MAX_LEN,stpfile) !=NULL){     //Loop that stops when we reach the end of the file or there is an error. When "feo" returns True, end of file, ferror is error. 
        stpWords[stpline][strlen(stpWords[stpline]) - 2] = '\0';   //"fgets" reads the next line in the file by storing the current line in "D1", its going to store a mx number of charecters "MAX_LEN", and reads from the pointer file "d1file". //fgets will return "NULL" when it hits the end of the file. The line will increment if fegets is not equal to NULL
        stpline++;
        
    }
     while(fgets(d1[d1line],MAX_LEN,d1file) !=NULL){     //Loop that stops when we reach the end of the file or there is an error. When "feo" returns True, end of file, ferror is error. 
        d1[d1line][strlen(d1[d1line]) - 1] = '\0';    //"fgets" reads the next line in the file by storing the current line in "D1", its going to store a mx number of charecters "MAX_LEN", and reads from the pointer file "d1file". //fgets will return "NULL" when it hits the end of the file. The line will increment if fegets is not equal to NULL    
        d1line++;
       
    }
    fclose(d1file);
    fclose(spcfile);
    fclose(stpfile);
    
   //printf("%s\n",d1[6]);
   //printf("%s\n",stpWords[355]);
   //printf("%d",strcmp(d1[16],spcChar[13]));
 
    for(int i = 0; i<d1line; i++){
        for(int j = 0; j<spcline; j++){          
            if(strcasecmp(d1[i],spcChar[j])==0){   //Function compares memory of each charecter in a string returns a 0 if they are equal. "strcasecmp" IS CASE INSENSITIVE
                for (int k = i ; k < d1line -1 ; k++) {
                    strcpy(d1[k],d1[k+1]);       
                }
                d1line--;
                i--;
            }
            else{
                continue;
            }

        }
    }
    d1line = d1line-1;
    //printf("%d",d1line);
   for(int i =0 ; i<d1line; i++){     
        for(int y = 0; y<stpline; y++){
            if(strcasecmp(d1[i],stpWords[y])==0){
                for (int k = i ; k < d1line - 1 ; k++) {
                    strcpy(d1[k],d1[k+1]);   
            }
                 d1line--;
                 i--;
            }
            else{
                continue;
            }
        }
    }
     for(int i=1; i<d1line; i++)
    {
        for(int j=1; j<d1line; j++)
        {
            if(strcasecmp(d1[j-1], d1[j])>0) //"strcasecmp" compares the size of two strings and is CASE-insensitive. If the first non-matching character in string1 is greater (in ASCII) than that of string2, it will return a value greater than zero.
            {
                strcpy(temp, d1[j-1]); //We assign the value before the current word being compared to the "temp" string value
                strcpy(d1[j-1], d1[j]); //We then assign the value to the string before the current word to the current word
                strcpy(d1[j], temp);    //We then assign the current string value to the temp string value(d1[j-1]) to complete the swap
            }
        }
    }
    for(int i =0; i<d1line;i++){
        fprintf(tokenfile,"%s\n",d1[i]); //This allows us to write information to a file. We first specify the pointer we created, than we create a string we want to write to the file
    }
    fclose(tokenfile);                      //We want to make sure we close a file before we open it 
   
   int frequencyarray[100];
   double weightarray[100];
   for(int i =0; i <d1line;i++){
    frequencyarray[i] = -1;
    weightarray[i] = 0;
   }
   for(int i =0; i<d1line;i++){
     int frequency = 1;
     for(int j = i +1; j<d1line;j++){
        
        if(strcmp(d1[i],d1[j])==0){
            frequency++;
            frequencyarray[j] = 0;
        }
        else{
           continue;
        }

     }
     if(frequencyarray[i]!=0){
        frequencyarray[i] = frequency;
     }
     else{
        continue;
     }
   }
   int MaxFrequencyValue = frequencyarray[0];
   for(int i =0; i<d1line;i++){
     if(frequencyarray[i]>MaxFrequencyValue){
         MaxFrequencyValue = frequencyarray[i];
     }
     else{
        continue;
     }
   }
   for(int i =0;i<d1line;i++){
        double weight = 0;
        if(frequencyarray[i]!=0){
        int frequency = frequencyarray[i];
        weight = (double)frequency/(double)MaxFrequencyValue;
        weightarray[i] = weight;
        }
   }
   for(int i =0; i<d1line;i++){
        if(frequencyarray[i]!=0){
            printf("%s occurs %d times and its weight is %0.3f\n",d1[i],frequencyarray[i],weightarray[i]);
        }
    }
    
    
}
void d2(){
    
    char d2[MAX_LINES][MAX_LEN],temp[20];   //2D charecter array with the constant deminsions
    char spcChar[MAX_LINES][MAX_LEN]; //2D charecter array with the constant deminsions
    char stpWords[MAX_LINES][MAX_LEN]; //2D charecter array with the constant deminsions
    
    FILE *d2file = fopen("d2.txt","r"); //Reads input file
    FILE *spcfile = fopen("specialcharacters.txt","r"); //Reads input file
    FILE *stpfile = fopen("stopwords.txt","r"); //Reads input file
    FILE *tokenfile = fopen("Tokenizedd2.txt", "w"); 
    int d2line = 0;            //Line keeps track of the current line we are reading in from the file and lets us know where to put it in the 2D array and how many lines are actually in the file
    int spcline = 0;            //Line keeps track of the current line we are reading in from the file and lets us know where to put it in the 2D array and how many lines are actually in the file
    int stpline = 0;            //Line keeps track of the current line we are reading in from the file and lets us know where to put it in the 2D array and how many lines are actually in the file
    
    if (d2file == NULL || spcfile == NULL || stpfile == NULL){
        fprintf(stderr,"Error opening file.\n"); //If compiler cant open the file, returns an error through function "stderr"
        exit(1);                                 //We return one as it is a signal to the terminal to signify something is wrong
    } 
    
   
    while(fgets(spcChar[spcline],MAX_LEN,spcfile) !=NULL){     //Loop that stops when we reach the end of the file or there is an error. When "feo" returns True, end of file, ferror is error. 
        spcChar[spcline][strlen(spcChar[spcline]) - 2] = '\0';
               //"fgets" reads the next line in the file by storing the current line in "D1", its going to store a mx number of charecters "MAX_LEN", and reads from the pointer file "d1file". //fgets will return "NULL" when it hits the end of the file. The line will increment if fegets is not equal to NULL
        spcline++;
        
    }
    while(fgets(stpWords[stpline],MAX_LEN,stpfile) !=NULL){     //Loop that stops when we reach the end of the file or there is an error. When "feo" returns True, end of file, ferror is error. 
        stpWords[stpline][strlen(stpWords[stpline]) - 2] = '\0';   //"fgets" reads the next line in the file by storing the current line in "D1", its going to store a mx number of charecters "MAX_LEN", and reads from the pointer file "d1file". //fgets will return "NULL" when it hits the end of the file. The line will increment if fegets is not equal to NULL
        stpline++;
        
    }
     while(fgets(d2[d2line],MAX_LEN,d2file) !=NULL){     //Loop that stops when we reach the end of the file or there is an error. When "feo" returns True, end of file, ferror is error. 
        d2[d2line][strlen(d2[d2line]) - 1] = '\0';    //"fgets" reads the next line in the file by storing the current line in "D1", its going to store a mx number of charecters "MAX_LEN", and reads from the pointer file "d1file". //fgets will return "NULL" when it hits the end of the file. The line will increment if fegets is not equal to NULL    
        d2line++;
       
    }
    fclose(d2file);
    fclose(spcfile);
    fclose(stpfile);
    for(int i = 0; i<d2line; i++){
        for(int j = 0; j<spcline; j++){
             if(strcmp(d2[i],spcChar[j])==0){
                for (int k = i ; k < d2line -1 ; k++) {
                    strcpy(d2[k],d2[k+1]);       
                }
                d2line--;
                i--;
             }
            else{
                continue;
            }

        }
    }
    d2line = d2line-1;
    for(int i =0 ; i<d2line; i++){
        for(int y = 0; y<stpline; y++){
            if(strcasecmp(d2[i],stpWords[y])==0){
                for (int k = i ; k < d2line -1 ; k++) {
                    strcpy(d2[k],d2[k+1]);       
                }
                d2line--;
                i--;
             }
            else{
                continue;
            }
        }
    }
    for(int i=1; i<d2line; i++)
    {
        for(int j=1; j<d2line; j++)
        {
            if(strcasecmp(d2[j-1], d2[j])>0) //"strcasecmp" compares the size of two strings and is CASE-insensitive. If the first non-matching character in string1 is greater (in ASCII) than that of string2, it will return a value greater than zero.
            {
                strcpy(temp, d2[j-1]); //We assign the value before the current word being compared to the "temp" string value
                strcpy(d2[j-1], d2[j]); //We then assign the value to the string before the current word to the current word
                strcpy(d2[j], temp);    //We then assign the current string value to the temp string value(d1[j-1]) to complete the swap
            }
        }
    }
    for(int i =0; i<d2line;i++){
        fprintf(tokenfile,"%s\n",d2[i]); //This allows us to write information to a file. We first specify the pointer we created, than we create a string we want to write to the file
    }
    fclose(tokenfile);                      //We want to make sure we close a file before we open it 
   
   int frequencyarray[100];
   double weightarray[100];
   for(int i =0; i <d2line;i++){
    frequencyarray[i] = -1;
    weightarray[i] = 0;
   }
   for(int i =0; i<d2line;i++){
     int frequency = 1;
     for(int j = i +1; j<d2line;j++){
        
        if(strcmp(d2[i],d2[j])==0){
            frequency++;
            frequencyarray[j] = 0;
        }
        else{
           continue;
        }

     }
     if(frequencyarray[i]!=0){
        frequencyarray[i] = frequency;
     }
     else{
        continue;
     }
   }
   int MaxFrequencyValue = frequencyarray[0];
   for(int i =0; i<d2line;i++){
     if(frequencyarray[i]>MaxFrequencyValue){
         MaxFrequencyValue = frequencyarray[i];
     }
     else{
        continue;
     }
   }
   for(int i =0;i<d2line;i++){
        double weight = 0;
        if(frequencyarray[i]!=0){
        int frequency = frequencyarray[i];
        weight = (double)frequency/(double)MaxFrequencyValue;
        weightarray[i] = weight;
        }
   }
   for(int i =0; i<d2line;i++){
        if(frequencyarray[i]!=0){
            printf("%s occurs %d times and its weight is %0.3f\n",d2[i],frequencyarray[i],weightarray[i]);
        }
    }
    
}
void d3(){
    char d3[MAX_LINES][MAX_LEN],temp[20];   //2D charecter array with the constant deminsions
    char spcChar[MAX_LINES][MAX_LEN]; //2D charecter array with the constant deminsions
    char stpWords[MAX_LINES][MAX_LEN]; //2D charecter array with the constant deminsions
    
    FILE *d3file = fopen("d3.txt","r"); //Reads input file
    FILE *spcfile = fopen("specialcharacters.txt","r"); //Reads input file
    FILE *stpfile = fopen("stopwords.txt","r"); //Reads input file
    FILE *tokenfile = fopen("Tokenizedd3.txt", "w"); 
    int d3line = 0;            //Line keeps track of the current line we are reading in from the file and lets us know where to put it in the 2D array and how many lines are actually in the file
    int spcline = 0;            //Line keeps track of the current line we are reading in from the file and lets us know where to put it in the 2D array and how many lines are actually in the file
    int stpline = 0;            //Line keeps track of the current line we are reading in from the file and lets us know where to put it in the 2D array and how many lines are actually in the file
   
    if (d3file == NULL || spcfile == NULL || stpfile == NULL){
        fprintf(stderr,"Error opening file.\n"); //If compiler cant open the file, returns an error through function "stderr"
        exit(1);                                 //We return one as it is a signal to the terminal to signify something is wrong
    } 
    
   
    while(fgets(spcChar[spcline],MAX_LEN,spcfile) !=NULL){     //Loop that stops when we reach the end of the file or there is an error. When "feo" returns True, end of file, ferror is error. 
        spcChar[spcline][strlen(spcChar[spcline]) - 2] = '\0';
               //"fgets" reads the next line in the file by storing the current line in "D1", its going to store a mx number of charecters "MAX_LEN", and reads from the pointer file "d1file". //fgets will return "NULL" when it hits the end of the file. The line will increment if fegets is not equal to NULL
        spcline++;
        
    }
    while(fgets(stpWords[stpline],MAX_LEN,stpfile) !=NULL){     //Loop that stops when we reach the end of the file or there is an error. When "feo" returns True, end of file, ferror is error. 
        stpWords[stpline][strlen(stpWords[stpline]) - 2] = '\0';   //"fgets" reads the next line in the file by storing the current line in "D1", its going to store a mx number of charecters "MAX_LEN", and reads from the pointer file "d1file". //fgets will return "NULL" when it hits the end of the file. The line will increment if fegets is not equal to NULL
        stpline++;
        
    }
     while(fgets(d3[d3line],MAX_LEN,d3file) !=NULL){     //Loop that stops when we reach the end of the file or there is an error. When "feo" returns True, end of file, ferror is error. 
        d3[d3line][strlen(d3[d3line]) - 1] = '\0';    //"fgets" reads the next line in the file by storing the current line in "D1", its going to store a mx number of charecters "MAX_LEN", and reads from the pointer file "d1file". //fgets will return "NULL" when it hits the end of the file. The line will increment if fegets is not equal to NULL    
        d3line++;
       
    }
    fclose(d3file);
    fclose(spcfile);
    fclose(stpfile);
  
    for(int i = 0; i<d3line; i++){
        for(int j = 0; j<spcline; j++){
             if(strcasecmp(d3[i],spcChar[j])==0){ //Function compares memory of each charecter in a string returns a 0 if they are equal. "strcasecmp" IS CASE INSENSITIVE
                for (int k = i ; k < d3line -1 ; k++) {
                    strcpy(d3[k],d3[k+1]);       
                }
                d3line--;
                i--;
             }
            else{
                continue;
            }

        }
    }
    d3line = d3line-1;
    for(int i =0 ; i<d3line; i++){
        for(int y = 0; y<stpline; y++){
            if(strcasecmp(d3[i],stpWords[y])==0){
                for (int k = i ; k < d3line -1 ; k++) {
                    strcpy(d3[k],d3[k+1]);       
                }
                d3line--;
                i--;
             }
            else{
                continue;
            }
        }
    }
    for(int i=1; i<d3line; i++)
    {
        for(int j=1; j<d3line; j++)
        {
            if(strcasecmp(d3[j-1], d3[j])>0) //"strcasecmp" compares the size of two strings and is CASE-insensitive. If the first non-matching character in string1 is greater (in ASCII) than that of string2, it will return a value greater than zero.
            {
                strcpy(temp, d3[j-1]); //We assign the value before the current word being compared to the "temp" string value
                strcpy(d3[j-1], d3[j]); //We then assign the value to the string before the current word to the current word
                strcpy(d3[j], temp);    //We then assign the current string value to the temp string value(d1[j-1]) to complete the swap
            }
        }
    }
    for(int i =0; i<d3line;i++){
        fprintf(tokenfile,"%s\n",d3[i]); //This allows us to write information to a file. We first specify the pointer we created, than we create a string we want to write to the file
    }
    fclose(tokenfile);                      //We want to make sure we close a file before we open it 
   
   int frequencyarray[100];
   double weightarray[100];
   for(int i =0; i <d3line;i++){
    frequencyarray[i] = -1;
    weightarray[i] = 0;
   }
   for(int i =0; i<d3line;i++){
     int frequency = 1;
     for(int j = i +1; j<d3line;j++){
        
        if(strcmp(d3[i],d3[j])==0){
            frequency++;
            frequencyarray[j] = 0;
        }
        else{
           continue;
        }

     }
     if(frequencyarray[i]!=0){
        frequencyarray[i] = frequency;
     }
     else{
        continue;
     }
   }
   int MaxFrequencyValue = frequencyarray[0];
   for(int i =0; i<d3line;i++){
     if(frequencyarray[i]>MaxFrequencyValue){
         MaxFrequencyValue = frequencyarray[i];
     }
     else{
        continue;
     }
   }
   for(int i =0;i<d3line;i++){
        double weight = 0;
        if(frequencyarray[i]!=0){
        int frequency = frequencyarray[i];
        weight = (double)frequency/(double)MaxFrequencyValue;
        weightarray[i] = weight;
        }
   }
   for(int i =0; i<d3line;i++){
        if(frequencyarray[i]!=0){
            printf("%s occurs %d times and its weight is %0.3f\n",d3[i],frequencyarray[i],weightarray[i]);
        }
    }
    
}
void d4(){
        
    char d4[MAX_LINES][MAX_LEN],temp[20];   //2D charecter array with the constant deminsions
    char spcChar[MAX_LINES][MAX_LEN]; //2D charecter array with the constant deminsions
    char stpWords[MAX_LINES][MAX_LEN]; //2D charecter array with the constant deminsions
     FILE *tokenfile = fopen("Tokenizedd4.txt", "w"); 
    FILE *d4file = fopen("d4.txt","r"); //Reads input file
    FILE *spcfile = fopen("specialcharacters.txt","r"); //Reads input file
    FILE *stpfile = fopen("stopwords.txt","r"); //Reads input file
    
    int d4line = 0;            //Line keeps track of the current line we are reading in from the file and lets us know where to put it in the 2D array and how many lines are actually in the file
    int spcline = 0;            //Line keeps track of the current line we are reading in from the file and lets us know where to put it in the 2D array and how many lines are actually in the file
    int stpline = 0;            //Line keeps track of the current line we are reading in from the file and lets us know where to put it in the 2D array and how many lines are actually in the file
    
    if (d4file == NULL || spcfile == NULL || stpfile == NULL){
        fprintf(stderr,"Error opening file.\n"); //If compiler cant open the file, returns an error through function "stderr"
        exit(1);                                 //We return one as it is a signal to the terminal to signify something is wrong
    } 
    
   
    while(fgets(spcChar[spcline],MAX_LEN,spcfile) !=NULL){     //Loop that stops when we reach the end of the file or there is an error. When "feo" returns True, end of file, ferror is error. 
        spcChar[spcline][strlen(spcChar[spcline]) - 2] = '\0';
               //"fgets" reads the next line in the file by storing the current line in "D1", its going to store a mx number of charecters "MAX_LEN", and reads from the pointer file "d1file". //fgets will return "NULL" when it hits the end of the file. The line will increment if fegets is not equal to NULL
        spcline++;
        
    }
    while(fgets(stpWords[stpline],MAX_LEN,stpfile) !=NULL){     //Loop that stops when we reach the end of the file or there is an error. When "feo" returns True, end of file, ferror is error. 
        stpWords[stpline][strlen(stpWords[stpline]) - 2] = '\0';   //"fgets" reads the next line in the file by storing the current line in "D1", its going to store a mx number of charecters "MAX_LEN", and reads from the pointer file "d1file". //fgets will return "NULL" when it hits the end of the file. The line will increment if fegets is not equal to NULL
        stpline++;
        
    }
     while(fgets(d4[d4line],MAX_LEN,d4file) !=NULL){     //Loop that stops when we reach the end of the file or there is an error. When "feo" returns True, end of file, ferror is error. 
        d4[d4line][strlen(d4[d4line]) - 1] = '\0';    //"fgets" reads the next line in the file by storing the current line in "D1", its going to store a mx number of charecters "MAX_LEN", and reads from the pointer file "d1file". //fgets will return "NULL" when it hits the end of the file. The line will increment if fegets is not equal to NULL    
        d4line++;
       
    }
    fclose(d4file);
    fclose(spcfile);
    fclose(stpfile);
    for(int i = 0; i<d4line; i++){
        for(int j = 0; j<spcline; j++){
             if(strcasecmp(d4[i],spcChar[j])==0){
                for (int k = i ; k < d4line -1 ; k++) {
                    strcpy(d4[k],d4[k+1]);       
                }
                d4line--;
                i--;
             }
            else{
                continue;
            }

        }
    }
    d4line = d4line-1;
    for(int i =0 ; i<d4line; i++){
        for(int y = 0; y<stpline; y++){
            if(strcasecmp(d4[i],stpWords[y])==0){
                for (int k = i ; k < d4line -1 ; k++) {
                    strcpy(d4[k],d4[k+1]);       
                }
                d4line--;
                i--;
             }
            else{
                continue;
            }
        }
    }
    for(int i=1; i<d4line; i++)
    {
        for(int j=1; j<d4line; j++)
        {
            if(strcasecmp(d4[j-1], d4[j])>0) //"strcasecmp" compares the size of two strings and is CASE-insensitive. If the first non-matching character in string1 is greater (in ASCII) than that of string2, it will return a value greater than zero.
            {
                strcpy(temp, d4[j-1]); //We assign the value before the current word being compared to the "temp" string value
                strcpy(d4[j-1], d4[j]); //We then assign the value to the string before the current word to the current word
                strcpy(d4[j], temp);    //We then assign the current string value to the temp string value(d1[j-1]) to complete the swap
            }
        }
    }
    for(int i =0; i<d4line;i++){
        fprintf(tokenfile,"%s\n",d4[i]); //This allows us to write information to a file. We first specify the pointer we created, than we create a string we want to write to the file
    }
    fclose(tokenfile);                      //We want to make sure we close a file before we open it 
   
   int frequencyarray[100];
   double weightarray[100];
   for(int i =0; i <d4line;i++){
    frequencyarray[i] = -1;
    weightarray[i] = 0;
   }
   for(int i =0; i<d4line;i++){
     int frequency = 1;
     for(int j = i +1; j<d4line;j++){
        
        if(strcmp(d4[i],d4[j])==0){
            frequency++;
            frequencyarray[j] = 0;
        }
        else{
           continue;
        }

     }
     if(frequencyarray[i]!=0){
        frequencyarray[i] = frequency;
     }
     else{
        continue;
     }
   }
   int MaxFrequencyValue = frequencyarray[0];
   for(int i =0; i<d4line;i++){
     if(frequencyarray[i]>MaxFrequencyValue){
         MaxFrequencyValue = frequencyarray[i];
     }
     else{
        continue;
     }
   }
   for(int i =0;i<d4line;i++){
        double weight = 0;
        if(frequencyarray[i]!=0){
        int frequency = frequencyarray[i];
        weight = (double)frequency/(double)MaxFrequencyValue;
        weightarray[i] = weight;
        }
   }
   for(int i =0; i<d4line;i++){
        if(frequencyarray[i]!=0){
            printf("%s occurs %d times and its weight is %0.3f\n",d4[i],frequencyarray[i],weightarray[i]);
        }
    }
    printf("%d",d4line);
}

int main(){
    d4();
    
    return 0;

}
