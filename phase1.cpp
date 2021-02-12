#include<stdio.h>
#include<iostream>

class OS
{
char M[10][4];
char R[4];
char IR[2];
bool toggle;
int InstR;

void OS();

};

void OS :: OS()
{
int i,j;

for(i=0;i<10;i++)
{
for(j=0;j<4;j++)
{
M[i][j] = 0;
}
}

for(i=0;i<10;i++)
{
for(j=0;j<4;j++)
{
printf("%d", M[i][j];
}
}

} 


int main()
{
OS os;
}

