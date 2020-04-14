#include"mainServer.h"
int main(void)
{
	/* 
	*	The main function where the function calling is done
	*	The user is prompted as to call which function
	*/
    int a;
    printf("Enter 1 for Logistic Regression\nEnter 2 for ReLU:");
    scanf("%d",&a);
    switch (a){
		case 1:
			callLogisticRegression();
			break;
		case 2:
			callReLU();
			break;
		default:
			printf("Invalid code");
			break;
	}
	return 0;
}
