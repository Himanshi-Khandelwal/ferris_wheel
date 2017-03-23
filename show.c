void print_reg()
{
	int x1;
	printf("Positive flag\t\t%d\n",flag[0]); //flag register - PNZ where P- positive bit , N- negative bit, Z- zero bit,
	printf("Negative flag\t\t%d\n",flag[1]);
	printf("Zero flag\t\t%d\n",flag[2]);
	printf("Program Counter\t\t%d\n",pc);
	printf("The contents of general purpose register are\n");
	for(x1=0;x1<15;x1++)
		printf("\t\n%d\t%d\n",x1,arr[x1]);
}
