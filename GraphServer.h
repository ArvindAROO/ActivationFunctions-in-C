#include<stdio.h>
#define NUM_COMMANDS 2

void Plot();
void ReadFileForPlot(int n, char *inp, float arr[n]);

void ReadFileForPlot(int n, char *inp, float arr[n]){
 	//this function takes the data from a file and assigns it to an array
 	//for handling and plotting of graphs
	int i;
    FILE *fp;
    fp = fopen(inp,"r");
    for(i=0; i<n; i++)
        fscanf(fp,"%f",&arr[i]);
    fclose(fp);

}
void Plot(){
	/*
		*The main function for plotting
		*This function uses 'GNUPLOT' and it must be set as path variable before hand
		*Failure to meet the above condition will result in crashing of the program
		*It is left to the user to disable the plot() function before if gnuplot is not installed
	*/
	printf("\n\nNow plotting the graph\n");
	int i, n;
	printf("Enter the number of vals:");
	scanf("%d",&n);
	char name_x[25],name_y[25];
	printf("\nEnter the file name which contains values of x:");
	scanf("%s",name_x);
	printf("\nEnter the file name which contains values of y:");
	scanf(" %s",name_y);
	float xvals[n];
    float yvals[n];
    ReadFileForPlot(n,name_x,xvals);
	ReadFileForPlot(n,name_y,yvals);
    char * commandsForGnuplot[] = {"set title \"PLOT OF THE DATA\"", "plot 'data.plt' with linespoints"};
    FILE * temp = fopen("data.plt", "w");
    //Do not edit 
    //All are bash and terminal and system commands. 
    //The c program will pass commands as user to the terminal activating and 
	//passing the required parameters to the 'gnuplot' application
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    //'-persistent' keeps the plot of the graph open even after the completion of program
    for (i=0; i < n; i++){
    	fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]); 
		//Write the data to a temporary file
    }
    for (i=0; i < NUM_COMMANDS; i++){
    	fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); 
		//Send commands to gnuplot one by one.
		//The plot functions takes corresponding x and y values
		//and join corresponding points to the previous point.. i.e data must be sorted
		//or else the graph will be hapazard
		
    }
	
}



