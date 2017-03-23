#include<stdio.h>
#include<string.h>
#include<math.h>

//ALU SIGNALS ADD:00 MULT:01 DIVI:10  subtr:11

int compare(int a,char temp[],char bin[]);
char inst[16];
int arr[100];
char code[6]={0};
char bin[16]={0};
char op1[10],op2[10];
FILE* fp1;
int abc = 0;
int pc = 1;


int compare(int a,char temp[],char bin[])
{
   int equal,i;
	for( i=0; i<a; i++){
		if(temp[i] != bin[i])
			return 0;
	}
	return 1;
}


char flag[4]={0}, ir[50];
int stk[100];
int top=-1;
void set();

void print_reg()
{
	int x1;
	printf("\tPositive flag\t\t%d\n",flag[0]); 		//flag register - PNZ where P- positive bit , N- negative bit, Z- zero bit,
	printf("\tNegative flag\t\t%d\n",flag[1]);
	printf("\tZero flag\t\t%d\n",flag[2]);
	printf("\tProgram Counter\t\t%d\n",pc);
	printf("The contents of general purpose register are\n");
	printf("\nRegisters\t\t\tValue\n");
	for(x1=0;x1<15;x1++)
		printf("\t\n%d\t\t\t\t%d",x1,arr[x1]);

	printf("\n________________________________________");
}

int THRUST(int base,int power){
	int value1;	
	value1 = arr[power];
	int value = 1;
	while(value1>0){
		value = value*base;
		value1--;
	}
	arr[power]=value;
	printf("Thrust calculated is %d\n",value);
	//printf("Control Signal is 01 and 10\n");
	print_reg();
	return value;
}

int POW(int base,int power){
	int value = 1;
	while(power>0){
		value*=base;
		power--;
	}
	return value;
}

int binToDecimal(char binVal[]){
	int len = strlen(binVal);
	int value=0;
	int power = 0;
	int i;
	for( i=len-1; i>=0; i--){
		if(binVal[i] == '1'){
			value += POW(2,power);
		}
		power++;
	}
	return value;
}

void set()
{
	int x1;
	for(x1=0;x1<10;x1++)       //array is set to zero
		arr[x1]=0;
	
}

void MOV(int imm,int ind)
{	
	int x1;
	arr[ind]=imm;			 //move reg ,immediate operation is performed
        printf("\nthe immediate value is\t\t%d\n",imm);
	print_reg();
}

void MOV1(int ind1,int ind2)
{
	arr[ind2]=arr[ind1];   //mov  reg,reg operation is performed
	print_reg();
}

void RUN(){
	printf("\t\tWHEEL IS ROTATING...........\n");
}

int WGTO(){
	printf("\t\tWEIGHT OVERLOAD !!!!!!!!\n");
	return 0;
}

int PASSW()
{
	FILE* fp3;
	int num;
        char num1[9];
   	printf("ENTER PASSWORD\n");
	scanf("%d",&num);
	fp3 = fopen("abc.txt","r");
	fscanf(fp3,"%s",num1);
        int dec = binToDecimal(num1);
	print_reg();
	if (num==dec)
        {
           printf("Password matched\n");
           return 1;
        }
        else
	{
		printf("Password incorrect\n");
	}
        return 0;	
}

void ADD(int ind1,int ind2)
{
	printf("ALU is adding....... 1st input : %d 2nd input : %d\n" , ind1 , arr[ind2]);
	arr[ind2]=ind1+arr[ind2];
	printf("\nthe immediate value is\t\t%d\n",ind1);
	if(arr[ind2]==0){
		flag[1]=0;
		flag[0]=0;
		flag[2]=1;}
	else if(arr[ind2]<0){          //add imm,reg operation is performed
		flag[1]=1;
		flag[0]=0;
		flag[2]=0;}
	else{
		flag[1]=0;
		flag[0]=1;
		flag[2]=0;}
	print_reg();
}

void MULT(int ind1,int ind2)
{
	arr[ind2]=arr[ind1]*arr[ind2];
	if(arr[ind2]==0){
		flag[1]=0;
		flag[0]=0;
		flag[2]=1;}
	if(arr[ind2]<0){
		flag[1]=1;
		flag[0]=0;
		flag[2]=0;}
	else{
		flag[1]=0;
		flag[0]=1;
		flag[2]=0;}
	print_reg();
}

void MULT1(int ind1,int ind2)
{	
	printf("ALU is multiplying....... 1st input : %d 2nd input : %d\n" , arr[ind1] , arr[ind2]);
	arr[ind2]=arr[ind1]*arr[ind2];
	if(arr[ind2]==0){
		flag[1]=0;
		flag[0]=0;
		flag[2]=1;}
	if(arr[ind2]<0){
		flag[1]=1;
		flag[0]=0;
		flag[2]=0;}
	else{
		flag[1]=0;
		flag[0]=1;
		flag[2]=0;}
	print_reg();
}


int CMP(int imm,int ind2)
{
	printf("ALU is comparing....... 1st input : %d 2nd input : %d\n" , imm , arr[ind2]);
	if(imm<arr[ind2])
       		{
		 flag[0] = 1;
		 flag[1] = 0;
		 flag[2] = 0;		
		}
        else if(imm>arr[ind2])
        	{
		flag[1] = 1;
		flag[0] = 0;
		flag[2] = 0;
		}
        else{
        flag[2] = 1;
	flag[0] = 0;
	flag[1] = 0;}
        print_reg();
}

int CMP1(int ind1,int ind2)
{
	printf("ALU is comparing....... 1st input : %d 2nd input : %d\n" , arr[ind1] , arr[ind2]);
        if(arr[ind1]<arr[ind2]){
        flag[0] = 1;
	flag[1] = 0;
	flag[2] = 0;}
        else if(arr[ind1]>arr[ind2]){
        flag[1] = 1;
	flag[0] = 0;
	flag[2] = 0;}
        else{
        flag[2] = 1;
	flag[1] = 0;
	flag[0] = 0;}
        print_reg();
}

void INC(int ind)
{
	printf("ALU is incrementing(adding) by 1....... input is: %d\n" ,arr[ind]);
	arr[ind]=arr[ind]+1;
	if(arr[ind]==0){
		flag[2]=1;
		flag[1]=0;
		flag[0]=0;}
	else{
		flag[2]=0; 
		flag[1]=0;
		flag[0]=0;}                         
	if(arr[ind]<0)
	{
		arr[ind]=0;
		flag[1]=1;
		flag[0]=0;
		flag[2]=0;
	}
	else{
		flag[0]=1;
		flag[1]=0;
		flag[2]=0;}
	print_reg();
	
}


void JLT(char inst[]){
	char addr[11];
	int val;
	int i;
	if(flag[1] == 1){
		for(i=12;i<=15; i++)
			addr[i-12] = inst[i];
		addr[i-12] = '\0';
		val =  binToDecimal(addr);
		fseek(fp1, 16*val+1, SEEK_SET);
		pc=val;
		print_reg();
		pc--; 
		printf("\n\tMOVING to LABEL %d\n",val);
	}
	else
		{pc=pc;
		print_reg();}
	
}

void JGT(char inst[]){
	char addr[11];
	int val;
	int i;
	if(flag[0] == 1){
		for(i=12;i<=15; i++)
			addr[i-12] = inst[i];
		addr[i-12] = '\0';
		val =  binToDecimal(addr);
		fseek(fp1, 16*val+1, SEEK_SET);
		pc=val;
		printf("\n\tMOVING to LABEL %d\n",val);
		print_reg();
		pc--;
	}
	else
		{pc=pc;
	print_reg();}
}

void JMP(char inst[]){
	char addr[11];
	int val;
	int i;
	for(i=12;i<=15; i++)
		addr[i-12] = inst[i];
	addr[i-12] = '\0';
	val =  binToDecimal(addr);
	fseek(fp1, 16*val+1, SEEK_SET);
	pc=val;
	print_reg();
	pc--;
	printf("\n\tMOVING to LABEL %d\n",val);
	
}


int main(){
	char temp[16];
        int num,num1;
        char temp1[16];
	int a;
        int p=1;
	fp1 = fopen("binaryCode.txt","r");
        while(!feof(fp1))
        {
		fscanf(fp1, "%[^\n]\n", temp);			             
                FILE* fp;
                fp = fopen("OpCodes.txt", "r");
			if(p==1)
			{	
                		while(!feof(fp))
				{				
                		fscanf(fp, "%s %s", code, bin);
               			a = strlen(bin);
                		int b = compare(a,temp,bin);
				if(b ==1)
				
				{	
					abc=abc+1;					
					int d1,d2,k,i;	
					
                			if(strcmp(code,"PASSW")==0)            
                				{
						p = PASSW();
						}
									
        			        else if(strcmp(code,"MOV")==0)
        			        	{
							int count = 3;
							for(i=count;i<count+9;i++)
							{
								op1[i-count]=temp[i];
								
							}
							op1[i-count]='\0';
							for(k=i;k<16;k++)
							{
								op2[k-i]=temp[k];
							}
							op2[k-i]='\0';						
							d1=binToDecimal(op1);   
							d2=binToDecimal(op2);
							printf("\n\nInstruction register\tmov %d,r%d\n",d1,d2);
							MOV(d1,d2);
						
						}
                				
						else if(strcmp(code,"MOV1")==0)
						{
						int count =8;
						for(i=count;i<count+4;i++)
						{
								op1[i-count]=temp[i];  
						}
						op1[i-count]='\0';
						for(k=i;k<16;k++)
						{
								op2[k-i]=temp[k];
						}
						op2[k-i]='\0';
						d1=binToDecimal(op1);
						d2=binToDecimal(op2);
						printf("\n\nInstruction register\tmov1 r%d,r%d\n",d1,d2);
						MOV1(d1,d2);
						}			
						
						else if(strcmp(code,"RUN")==0)            
                				{
							RUN();
						}
				
						else if(strcmp(code,"WGTO")==0)            
                				{
							WGTO();
						}
               				        
						else if(strcmp(code,"CMP")==0)            
                                                {
						int count = 3;
						for(i=count;i<count+9;i++)
						{
								op1[i-count]=temp[i];
						}
						op1[i-count]='\0';
						for(k=i;k<16;k++)
						{
								op2[k-i]=temp[k];
						}
						op2[k-i]='\0';
						d1=binToDecimal(op1);   
						d2=binToDecimal(op2);
						printf("\n\nInstruction register\tcmp %d,r%d\n",d1,d2);
						CMP(d1,d2);
						}
                				
						else if(strcmp(code,"CMP1")==0)            
						{
						int count =8;
						for(i=count;i<count+4;i++)
						{
								op1[i-count]=temp[i];  
						}
						op1[i-count]='\0';
						for(k=i;k<16;k++)
						{
								op2[k-i]=temp[k];
						}
						op2[k-i]='\0';
						d1=binToDecimal(op1);
						d2=binToDecimal(op2);
						printf("\n\nInstruction register\tcmp1 r%d,r%d\n",d1,d2);
						CMP1(d1,d2);
						}

                				else if(strcmp(code,"MULT")==0)            
						{
						int count = 3;
						for(i=count;i<count+9;i++)
						{
								op1[i-count]=temp[i];
								
						}
						op1[i-count]='\0';
						for(k=i;k<16;k++)
						{
								op2[k-i]=temp[k];
						}
						op2[k-i]='\0';						
						d1=binToDecimal(op1);   
						d2=binToDecimal(op2);						
						}
                				
						else if(strcmp(code,"MULT1")==0)            
						{
						int count =8;
						for(i=count;i<count+4;i++)
						{
								op1[i-count]=temp[i];  
						}
						op1[i-count]='\0';
						for(k=i;k<16;k++)
						{
								op2[k-i]=temp[k];
						}
						op2[k-i]='\0';
						d1=binToDecimal(op1);
						d2=binToDecimal(op2);
						printf("\n\nInstruction register\tmult r%d,r%d\n",d1,d2);
						MULT1(d1,d2);
		
               
						}
                				else if(strcmp(code,"THRUST")==0)            
                				{
							int count = 3;
							for(i=count;i<count+9;i++)
							{
								op1[i-count]=temp[i];
								
							}
							op1[i-count]='\0';
							for(k=i;k<16;k++)
							{
								op2[k-i]=temp[k];
							}
							op2[k-i]='\0';
						
							d1=binToDecimal(op1);   
							d2=binToDecimal(op2);
							printf("\n\nInstruction register\tTHRUST %d,r%d\n",d1,d2);
							THRUST(d1,d2);
						
						}

                				else if(strcmp(code,"ADD")==0)            
						{
						int count = 3;
						for(i=count;i<count+9;i++)
						{
								op1[i-count]=temp[i];
								
						}
						op1[i-count]='\0';
						for(k=i;k<16;k++)
						{
								op2[k-i]=temp[k];
						}
						op2[k-i]='\0';						
						d1=binToDecimal(op1);   
						d2=binToDecimal(op2);
						printf("\n\nInstruction register\tadd %d,r%d\n",d1,d2);
						ADD(d1,d2);
						}

						else if(strcmp(code,"ADDW")==0)            
						{
						int d1,i =12;
						printf("ENTER THE WEIGHT\n");
						scanf("%d",&d1);
						//op1[i-count]='\0';
						for(k=i;k<16;k++)
						{
								op2[k-i]=temp[k];
						}
						op2[k-i]='\0';						
						//d1=binToDecimal(op1);   
						d2=binToDecimal(op2);
						printf("\n\nInstruction register\tadd %d,r%d\n",d1,d2);
						ADD(d1,d2);
						}
                				
						else if(strcmp(code,"INC")==0)            
                				{
						int count =12;
						for(i=count;i<count+4;i++)
						{
								op1[i-count]=temp[i];
								
						}
						op1[i-count]='\0';
						d1=binToDecimal(op1);
						printf("\n\nInstruction register\tinc r%d\n",d1);
						INC(d1);
						}
        				        
						else if(strcmp(code,"JGT")==0)
						{                  				
						printf("\n\nInstruction register JGT\n");
						JGT( temp);
						}
               					
						else if(strcmp(code,"JMP")==0)            
                				{
						printf("\n\nInstruction register JMP\n");
						JMP(temp);
						}
                				
						else if(strcmp(code,"JLT")==0)            
                				{
						printf("\n\nInstruction register JLT\n");
						JLT(temp);						
						}
     
                				else if(strcmp(code,"HLT")==0)            
                				{
						printf("\n\nTHE PROGRAM IS TERMINATED\n");
						pc--;
						print_reg();
						printf("\n");
						return 0;
						}
                				else
						continue;
    				}
           		   	}

			}

		else
	{
	break;
	}
	pc=pc+1;
	}
}
