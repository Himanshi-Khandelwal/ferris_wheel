#include<stdio.h>
#include<string.h>

char code[6]={0};
char bin[16]={0};

//PRINTS THE OP CODE TABLE
void showOpCodes(){
    FILE* fp;
    fp = fopen("OpCodes.txt", "r");
    printf("THE OP CODES ARE\n");
    while(!feof(fp)){
        fscanf(fp, "%s %s", code, bin);
        printf("%s %s\n", code, bin);
    }
    printf("\n");
    fclose(fp);
}

//PRINTS THE REGISTER CODES
void showRegCodes(){
    FILE* fp;
    fp = fopen("regCodes.txt", "r");
    printf("THE REGISTER CODES ARE\n");
    while(!feof(fp)){
        fscanf(fp, "%s %s", code, bin);

        if(code[0] == 'R'){
            printf("%s %s\n", code, bin);
        }
    }
    printf("\n");
    fclose(fp);
}

//NUMBER-->BINARY
void toBinary(int n, char l[]){
    int c, k;
    int ctr=0;
    for(c = 3; c >= 0; c--)
    {
        k = n >> c;
        if (k & 1)
            l[ctr] = '1';
        else
            l[ctr] = '0';
        ctr++;
    }
    l[ctr] = '\0';
}


/*void toBinary(int n, char l[]){*/
/*    int c, k;*/
/*	int value=1;*/
/*int temp[4]={0,0,0,0};*/
/*	*/
/*	*/
/*    */
/*	while(value!=0){*/
/*    for(c = 3; c >= 0; c--)*/
/*    {*/
/*        k=n%2;*/
/*	l[c]=temp[c]+k;*/
/*	value=n/2;*/
/*    }*/
/*   */
/*}*/
/*}*/

//FIRST PASS
void firstPass(char name[]){
    char temp[100];
    FILE* fp;
    FILE* fp1;
    int line=1;
    int lcount=0;
    char l[20];
    int d[100];
    char opCode[16];
    int i, ctr,res;
    int count = 0;
    int s = 0;
    fp = fopen(name, "r");
    fp1 = fopen("table.txt", "w");
    printf("LABELS:");
    while(!feof(fp)){
        fscanf(fp, "%[^\n]\n", temp);
        ctr = 0;
        i = 0;
        while(temp[i] != ' ' && temp[i] != '\0'){
            opCode[ctr] = temp[i];
            i++;
            ctr++;
        }
        opCode[ctr] = '\0';
        if(opCode[0]=='L' && (opCode[2] == ':' || opCode[3] == ':')){
            int count1 = 0;
            if(count!=0)
            {
               for(res=0;res<count;res++)
               {
                  if(d[res]==opCode[1])
                  count1++;
               }
            }
            if(count1==0)
            {
            lcount++;
            toBinary(line-lcount, l);
            opCode[strlen(opCode)-1] = '\0';
            d[s] = opCode[1];
            s++;
            count++;
            printf(" %s", opCode);
            fprintf(fp1, "%s %s\n", opCode, l);
             }
             else
             printf("\nTHE LABEL IS REPEATED");
        }
        line++;
    }
    fclose(fp);
    fclose(fp1);
}

//ASSEMBLY-->BINARY
void fileConvert(){
    char temp[100];
    char name[100] = "assembly.txt";
    FILE* fp;
    FILE* fp1;
    FILE* fp2;
    
    char opCode[16], reg[16];
    int i, ctr, flag,Lfound;
    fp = fopen("assembly.txt", "r");
    firstPass(name);
    printf("\nKEYWORDS: ");
    fp2 = fopen("binaryCode.txt", "w");
    while(!feof(fp)){
        fscanf(fp, "%[^\n]\n", temp);
        ctr = 0;
        i = 0;
        Lfound=0;
        while(temp[i] != ' ' && temp[i] != '\0'){
            opCode[ctr] = temp[i];
            i++;
            ctr++;
        }
        if(!(opCode[0]=='L' && (opCode[2] == ':' || opCode[3] == ':'))){
            opCode[ctr] = '\0';
            flag = 1;
            fp1 = fopen("OpCodes.txt", "r");
            while(!feof(fp1) && flag){
                fscanf(fp1, "%s %s", code, bin);
                if(strcmp(code, opCode) == 0){
                    printf(" %s ",opCode);
                    fprintf(fp2, "%s", bin);
                    flag = 0;
                    fclose(fp1);
                }
            }
            if(flag){
                printf(" %s ",opCode);
                printf("\nINVALID");
                return;
            }
        }
        
        else{
            Lfound=1;
        }
        
        while(temp[i] != '\0'){
            while(temp[i] == ' ' || temp[i] == ','){
                i++;
            }
            ctr = 0;
            while(temp[i] != ' ' && temp[i] != ',' && temp[i] != '\0'){
                reg[ctr] = temp[i];
                i++;
                ctr++;
            }
            reg[ctr] = '\0';
            printf(" %s ",reg);
            if(!(reg[0]=='L'))
            {
                flag = 1;
                fp1 = fopen("regCodes.txt", "r");
                while(!feof(fp1) && flag){
                    if(!feof(fp1)){
                        fscanf(fp1, "%s %s", code, bin);
                        if(strcmp(code, reg) == 0){
                            fprintf(fp2, "%s", bin);
                            flag = 0;
                            fclose(fp1);
                        }
                    }
                }
                
                if(flag){
                    printf(" %s ",reg);
                    printf("\nINVALID");
                    return;
                }
            }
            
            else{
                fp1 = fopen("table.txt", "r");
                flag = 1;
                while(!feof(fp1) && flag){
                    if(!feof(fp1)){
                        fscanf(fp1, "%s %s", code, bin);
                        if(strcmp(code, reg) == 0){
                            fprintf(fp2, "%s", bin);
                            flag = 0;
                            fclose(fp1);
                        }
                    }
                }
                if(flag){
                    printf("\nINVALID");
                    return;
                }
            }
        }
        if(!Lfound){
            fprintf(fp2, "\n");
        }
    }
    fclose(fp2);
    fclose(fp);
}

//CONVERTS BINARY-->ASSEMBLY
void Binary_view(){
    FILE* fp;
    char bin1[30];
	
    fp = fopen("binaryCode.txt", "r");
    if(!fp){
        printf("THE FILE IS NOT CONVERTED\n");
        return;
    }
    printf("THE BINARY CODE IS\n");
    while(!feof(fp)){
        fscanf(fp, "%[^\n]\n", bin1);
        printf("%s\n", bin1);
    }
    fclose(fp);
}

//PRINTS SYMBOL TABLE
void Table_view(){
    FILE* fp;
    fp = fopen("table.txt", "r");
    if(!fp){
        printf("THE FILE IS NOT CONVERTED\n");
        return;
    }
    printf("THE SYMBOL TABLE IS\n");
    while(!feof(fp)){
        fscanf(fp, "%s %s", code, bin);
        if(!feof(fp))
            printf("%s %s\n", code, bin);
    }
    printf("\n");
    fclose(fp);
}

//PRINTS ASSEMBLY CODE
void Assembly_view(){
    FILE* fp;
    char bin1[30];
    fp = fopen("assembly.txt", "r");
    if(!fp){
        printf("\nTHE FILE IS NOT CONVERTED\n");
        return;
    }
    printf("\nTHE ASSEMBLY CODE IS\n");
    while(!feof(fp)){
        fscanf(fp, "%[^\n]\n", bin1);
        printf("%s\n", bin1);
    }
    fclose(fp);
}

