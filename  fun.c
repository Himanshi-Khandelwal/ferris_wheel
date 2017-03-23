
float arr[10];
int pc=-1;
char flag[4], ir[50];
int stk[100];
int top=-1;
void set();

int binToDecimal(int x){
	int rem, p=0,base=1;
		while( x>0){
			rem=x%10;
			p=p+rem*base;
			x=x/10;
			base=base*2;
			}
		return(x);
	}

LOAD(int ind)
{	int num[9];
	FILE* fp;
	fp =fopen("abc","r");
	while(!feof(fp))
        {
            fscanf(fp,"%d",&num);
	}
      int p = bintodec(num);
	arr[ind]=p;
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
	arr[ind]=imm;     //move reg ,immediate operation is performed
}

void MOV1(int ind1,int ind2)
{
	arr[ind2]=arr[ind1];   //mov  reg,reg operation is performed
}

void ADD(int ind1,int ind2)
{
	arr[ind2]=ind1+arr[ind2];
	if(arr[ind2]==0)
		flag[2]=1;
	
	else if(arr[ind2]<0)          //add imm,reg operation is performed
		flag[1]=1;
	else
		flag[1]=0;
}

void MUL(int ind1,int ind2)
{
	arr[ind2]=arr[ind1]*arr[ind2];
	if(arr[ind2]==0)
		flag[2]=1;
	else
		flag[2]=0;
	if(arr[ind2]<0)                // multiply reg reg opertaion is performed
		flag[1]=1;
	else
		flag[1]=0;
}

void MUL1(int ind1,int ind2)
{
	arr[ind2]=arr[ind1]*arr[ind2];
	if(arr[ind2]==0)
		flag[2]=1;
	else
		flag[2]=0;
	if(arr[ind2]<0)                // multiply reg reg opertaion is performed
		flag[1]=1;
	else
		flag[1]=0;
}


int CMP(int imm,int ind2)
{
	if(arr[ind2]!=imm)
		return -1;                         //comparision operation is performed.....
	else
		return 1;
}

int CMP1(int ind1,int ind2)
{
	if(arr[ind2]!=arr[ind1])
		return -1;                         //comparision operation is performed.....
	else
		return 1;
}

void INC(int ind)
{
	arr[ind]=arr[ind]+1;
	if(arr[ind]==0)
		flag[2]=1;
	else
		flag[2]=0;                          //decrement operation
	if(arr[ind]<0)
	{
		arr[ind]=0;
		flag[1]=1;
	}
	else
		flag[1]=0;
	
}
void print_reg()
{
	int x1;
	printf("Overflow flag\t\t%d\n",flag[0]); //flag register - ONZU where O- overflow bit , N- negative bit, Z- zero bit, U- underflow bit.
	printf("Negative flag\t\t%d\n",flag[1]);
	printf("Zero flag\t\t%d\n",flag[2]);
	if(top==-1)
		flag[3]=1;
	else
		flag[3]=0;
	printf("Underflow flag\t\t%d\n",flag[3]);
	printf("Program Counter\t\t%d\n",pc);
	printf("Stack Pointer\t\t%d\n",top);
	printf("The contents of general purpose register are\n");
	for(x1=0;x1<10;x1++)
		printf("r%d\t%f\n",x1,arr[x1]);
}
void POP(int ind)
{
	int i;
	if(top!=-1)
	{
		arr[ind]=stk[top];
		top--;
		flag[3]=0;
	}
	else
		flag[3]=1;
	
}
void PUSH(int r)
{
	int i;
	top++;
	stk[top]=r;
	printf("elements in stack\n");       //element is pushed into stack.....
	if(top<100)
	{
		for(i=top;i>=0;i--)
			printf("%d\n",stk[i]);
		flag[0]=0;
	}
	else
		flag[0]=1;
}

void JEQ(char inst[]){
	char addr[11];
	int val;
	int i;
	if(spReg[0] == 2){
		for(i=12;i<=15; i++)
			addr[i-12] = inst[i];
		addr[i-12] = '\0';
		val =  binToDecimal(addr);
		fseek(fpmain, 16*val+1, SEEK_SET);
		spretemp=val;
		printf("\n\tMOVING to LABEL %d\n",val);
	}
	else
		spretemp++;
}

void JNQ(char inst[]){
	char addr[11];
	int val;
	int i;
	if(spReg[0] != 2){
		for(i=12;i<=15; i++)
			addr[i-12] = inst[i];
		addr[i-12] = '\0';
		val =  binToDecimal(addr);
		fseek(fpmain, 16*val+1, SEEK_SET);
		spretemp=val;
		printf("\n\tMOVING to LABEL %d\n",val);
	}
	else
		spretemp++;
}

void JLT(char inst[]){
	char addr[11];
	int val;
	int i;
	if(spReg[0] == 1 ){
		for(i=12;i<=15; i++)
			addr[i-12] = inst[i];
		addr[i-12] = '\0';
		val =  binToDecimal(addr);
		fseek(fpmain, 16*val+1, SEEK_SET);
		spretemp=val;
		printf("\n\tMOVING to LABEL %d\n",val);
	}
	else
		spretemp++;
}

void JGT(char inst[]){
	char addr[11];
	int val;
	int i;
	if(spReg[0] == 0){
		for(i=12;i<=15; i++)
			addr[i-12] = inst[i];
		addr[i-12] = '\0';
		val =  binToDecimal(addr);
		fseek(fpmain, 16*val+1, SEEK_SET);
		spretemp=val;
		printf("\n\tMOVING to LABEL %d\n",val);
	}
	else
		spretemp++;
}

void JMP(char inst[]){
	char addr[11];
	int val;
	int i;
	for(i=12;i<=15; i++)
		addr[i-12] = inst[i];
	addr[i-12] = '\0';
	val =  binToDecimal(addr);
	fseek(fpmain, 16*val+1, SEEK_SET);
	spretemp=val;
	printf("\n\tMOVING to LABEL %d\n",val);
}



void HLT(){
	printf("\n\tProgram Terminated!\n\n");
	fclose(fpmain);
}
	
