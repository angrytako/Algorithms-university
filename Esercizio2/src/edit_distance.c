#include "edit_distance.h"

int classic_edit_distance(char* str1, char* str2);
int dinamic_edit_distance_aux( char* str1, char* str2,int** mem,int min,int this, int lenght_str1,int lenght_str2);

int** initialize_memory_edit_distance(int str1, int str2);
void free_memory_edit_distance(int** mem,int str1);

        
int ric_edit_distance(char* str1, char* str2){
        if (str1==NULL || str2==NULL) return ERROR_DISTACE; 
        else return classic_edit_distance(str1,str2);
}      

int classic_edit_distance(char* str1, char* str2){
        int lenght_str1,lenght_str2;
        int dnoop=0, dcanc=0,dins=0;
       
        lenght_str1 = (int)strlen(str1);
        lenght_str2 = (int)strlen(str2);
        if (lenght_str1==0) return lenght_str2;
        if (lenght_str2==0) return lenght_str1;
        
        //caso in cui tolgo un elemento da entrambe 
        if (*str1==*str2) dnoop= classic_edit_distance(REST(str1),REST(str2));
        else dnoop = ERROR_DISTACE;

        //secondo caso
        dcanc = 1 + classic_edit_distance(str1,REST(str2));

        dins = 1 + classic_edit_distance(REST(str1),str2);
    
        //min
        if (dcanc<dnoop)dnoop = dcanc;
        if (dins<dnoop)dnoop = dins;
        return dnoop;
}

int dinamic_edit_distance( char* str1, char* str2,int min){
        if (str1==NULL || str2==NULL) return ERROR_DISTACE; 
        else
        {
                int lenght_str1 = (int)strlen(str1);
                int lenght_str2 = (int)strlen(str2);
                int** mem;
                mem = initialize_memory_edit_distance(lenght_str1,lenght_str2);
                int output = dinamic_edit_distance_aux(str1,str2,mem,min,0,lenght_str1,lenght_str2);
                free_memory_edit_distance(mem,lenght_str1);
                return output;
        } 
}

int dinamic_edit_distance_aux( char* str1, char* str2,int** mem,int min,int this, int lenght_str1,int lenght_str2){
        if (this>=min) return ERROR_DISTACE; //per evitare le chiamate che non influenzeranno il risultato
        int dnoop=0, dcanc=0,dins=0;
       
        if (lenght_str1==0) return lenght_str2;
        if (lenght_str2==0) return lenght_str1;
        
        //ceck mem
        if (mem[lenght_str1-1][lenght_str2-1]>=0) return mem[lenght_str1-1][lenght_str2-1];

        //caso in cui tolgo un elemento da entrambe 
        if (*str1==*str2) dnoop= dinamic_edit_distance_aux(REST(str1),REST(str2),mem,min,this,(lenght_str1-1),(lenght_str2-1));
        else dnoop = ERROR_DISTACE; 
        //secondo caso
        dcanc = dinamic_edit_distance_aux(str1,REST(str2),mem,min,this+1,lenght_str1,(lenght_str2-1));
        dins = dinamic_edit_distance_aux(REST(str1),str2,mem,min,this+1,(lenght_str1-1),lenght_str2);
        // per evitare l'overfow
        if (dcanc != ERROR_DISTACE) dcanc++;
        if (dins != ERROR_DISTACE) dins++;

        /*minimo, uso dnoop come variabile di appoggio*/
        if (dcanc<dnoop) dnoop = dcanc;
        if (dins<dnoop) dnoop = dins;


        /*salvo il minimo*/
        mem[lenght_str1-1][lenght_str2-1]=dnoop;
        return dnoop;
}




int** initialize_memory_edit_distance(int lenght_str1, int lenght_str2){
        int** mem;
        mem=malloc(sizeof(int*)*(unsigned int)(lenght_str1));

        for(int i=0;i<lenght_str1;i++){ 
                mem[i]=malloc(sizeof(int)*(unsigned int)(lenght_str2));
                mem[i]=memset(mem[i], -1, sizeof(int)*(unsigned int)(lenght_str2));
        }

        return mem;
}


void free_memory_edit_distance(int** mem,int lenght_str1){
        for(int i=0;i<lenght_str1;i++){ 
                free(mem[i]);
        }
        free(mem);
}

