#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"GraphServer.h"
//Functions for Logistic Regression and ReLU

void Disp(int n,float arr[n],char *type);
void Read_File_2(int n, char *inp, float arr[n]);
void File_Input_2(int n,float arr_x[n]);
void File_Output_2(int n,float arr[n]);
void LogisticRegression(int n,float arr_x[n],float final_arr[n]);
void callLogisticRegression(void);
void ReLU(int n,float x[n],float FinalArr[n]);
void callReLU(void);

//Functions to plot Graphs
int PlotBool();


void Disp(int n,float arr[n],char *type){
	//Displays the input parameters of the array
	printf("\nDisplaying %s values",type);
	printf("\nThe values are:");
	int i;
	for(i=0;i<n;i++){
    	printf("\t%.3f",arr[i]);
	}
	printf("\n");
}
void Read_File_2(int n, char *inp, float arr[n]){
	//this function takes the data from a file and assigns it to an array
    FILE *fp;
    int i;
    fp = fopen(inp,"r");
    for(i=0; i<n; i++)
        fscanf(fp,"%f",&arr[i]);
    fclose(fp);

}
void File_Input_2(int n,float arr_x[n]){
	//wrapper function which collects the file name to be accessed
    char input_x[25];
    printf("\nEnter the file name which contains values of x:");
    scanf("%s",input_x);
    Read_File_2(n,input_x,arr_x);


}

void File_Output_2(int n,float arr[n]){
	//Function writes the output obtained to a file
    char input_x[25];
    printf("\nEnter the file name to write the output:");
    scanf("%s",input_x);
    FILE *fp=fopen(input_x,"w");
    int i;
    for(i=0; i<n; i++)
        fprintf(fp,"%f\n",arr[i]);
    fclose(fp);
}

void LogisticRegression(int n,float arr_x[n],float final_arr[n]){
	//Function which does the bulk of the logistic regression

    float sigma_x=0,x_mean=0,sd=0; 
    /*	
		sigma_x -> summation of x terms
    	x_mean -> mean of x terms
    	sd -> Standard deviation
    		sd=sqrt((sum of squares of (x[i] - x_mean))/n)
    	The final_val is the probability which is used as the activation function in CNN's
		prob=1/(1+e^(x-x_mean)/sd)
    
    */
    float e=2.7182;
    int i;
    for(i=0;i<n;i++){
        sigma_x+=arr_x[i];
    }
    x_mean=(float)sigma_x/n;
    for(i=0;i<n;i++){
        sd+=(arr_x[i]-x_mean)*(arr_x[i]-x_mean);
    }
    sd/=n;
    sd=pow(sd,0.5);
    float power=0,final_val=0;
    printf("\nsd :%.3f\nmean :%.3f\n\n",sd,x_mean);
    printf("\ninitial->final\n");
    for(i=0;i<n;i++){
        power=(arr_x[i]-x_mean)/sd;
        power=pow(e,-power);
        final_val=(float)1/(1+power);
        final_arr[i]=final_val;
        printf("%.3f->%.3f\n",arr_x[i],final_val);
    }

}
int PlotBool(){
	//This function prompts the user whether as to plot the graph or not
	char flag;
	fflush(stdin);
	printf("Do you want to plot the above data[y/n]:");
	
	scanf("%c",&flag);
	fflush(stdin);
	if(flag=='y' || flag=='Y')
		return 1;
	else
		return 0;
}
void callLogisticRegression() //Used in the main function to do the particular operation
{
	int n;
	printf("Enter the number of values:");
	scanf("%d",&n);
	float arr_x[n],Res[n];
	File_Input_2(n,arr_x);
	Disp(n,arr_x,"Input");
	LogisticRegression(n,arr_x,Res);
	Disp(n,Res,"after Logistic Regression");
	File_Output_2(n,Res);
	if(PlotBool())
		Plot();
}

// ReLu is the most commonly used Activation Function in CNNs
void ReLU(int n,float x[n],float FinalArr[n]){
	//Function which imitates the ReLU activation function
	//The return value at any point before the activation point is zero and
	//after the activatio point is that point itself
	float ActivationPoint;
    int i;
	printf("\nEnter the point of Activation : ");
    scanf("%f",&ActivationPoint);
    for(i=0;i<n;i++){
        if(x[i]<ActivationPoint){
            printf("%.3f->%.3f\n",x[i],0.0);
            FinalArr[i]=0.0;
    	}else{
            printf("%.3f->%.3f\n",x[i],x[i]);
            FinalArr[i]=x[i];
		}
    }
}

void callReLU() 
{
	//Used in the main function to do the particular operation
	int n;
	printf("Enter the number of values:");
	scanf("%d",&n);
	float arr_x[n],Res[n];
	File_Input_2(n,arr_x);
	Disp(n,arr_x,"input");
	ReLU(n,arr_x,Res);
	Disp(n,Res,"After ReLU");
	File_Output_2(n,Res);
	if(PlotBool())
		Plot();
}

