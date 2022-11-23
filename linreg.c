#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Get inputs in terms of x and y
// calculate B1 and B0
// we need mean of x and y, and other summation functions in the program below

double mean(int *arr,int size);
double beta1(int *x,int* y,double xbar,double ybar,int size);
double beta0(double xbar,double ybar,double B1);
double rsquared(int *y,int *x,double B0,double B1,double ybar,int size);

int main()
{
    FILE* ptr = fopen("input.txt","r");
    char line[500];
    int i = 0;

    /* while(fgets(line,500,ptr))
    {
        i++;
        printf("%s\n",line);
    }

    printf("Number of lines: %d",i);
    fclose(ptr);
    return 0; */

    int x[10000];
    int y[10000];
    char *token;

    while(fgets(line,500,ptr))
    {
        token = strtok(line," ");
        x[i] = atoi(token);
        token = strtok(NULL," ");
        y[i] = atoi(token);
        i++;
    }

    double xbar = mean(x,i);
    double ybar = mean(y,i);

    //printf("%f",xbar);
    double B1 = beta1(x,y,xbar,ybar,i);
    double B0 = beta0(xbar,ybar,B1);

    double coeff_determination = rsquared(y,x,B0,B1,ybar,i);

    printf("Value of y-intercept is: %lf\n",B0);
    printf("Value of slope is: %lf\n",B1);
    printf("y = %lf + %lfx\n",B0,B1);
    printf("Coefficient of determination: %lf",coeff_determination);
}

double mean(int *arr,int size)
{
    double meanval = 0;

    for(int i=0;i<size;i++) meanval += (double)arr[i];

    return (meanval/size);
}
double beta1(int *x,int* y,double xbar,double ybar,int size)
{
    // compute XY (numerator)
    // compute X^2 (denominator)
    double num,den;
    num = den = 0;

    for(int i=0;i<size;i++) num += ((double)x[i]-xbar)*((double)y[i]-ybar);

    for(int i=0;i<size;i++) den += ((double)x[i]-xbar)*((double)x[i]-xbar);

    return (num/den);
}

double beta0(double xbar,double ybar,double B1)
{
    return (ybar - B1*xbar);
}

double rsquared(int *y,int *x,double B0,double B1,double ybar,int size)
{
    double y_fitted[size];
    int i;
    double totsum,errsum;
    // fitted values of y
    for(i=0;i<size;i++) y_fitted[i] = B0 + B1*(double)x[i];
    // total sum of squares
    for(i=0;i<size;i++) errsum += ((double)y[i] - y_fitted[i])*((double)y[i] - y_fitted[i]);
    // error sum of squares
    for(i=0;i<size;i++) totsum += ((double)y[i] - ybar)*((double)y[i] - ybar);

    return (totsum - errsum)/totsum;
}
