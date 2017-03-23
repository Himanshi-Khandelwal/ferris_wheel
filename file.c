#include<stdio.h>
#include<stdlib.h>
#include "cfile.c"

void main(){
    int ch=0;
    int i;
    do{
        printf("\nENTER YOUR CHOICE\n");
        printf("1 Show OP Codes \n");
        printf("2 Show Register Codes \n");
        printf("3 Convert File to binary \n");
        printf("4 Show Assembly Code \n");
        printf("5 Show Binary Code \n");
        printf("6 Show Symbol Table \n");
        printf("0 Exit\n");
        scanf("%d", &ch);
        printf("\n");
        switch(ch){
            case 1:showOpCodes();
                break;
            case 2:showRegCodes();
                break;
            case 3:fileConvert();
                break;
            case 4:Assembly_view();
                break;
            case 5:Binary_view();
                break;
            case 6:Table_view();
                break;
            case 0:break;
            default: printf("Invalid Input!\n");
                break;
        }
    }while(ch != 0);
}
