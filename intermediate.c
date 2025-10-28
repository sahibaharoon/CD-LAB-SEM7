#include<stdio.h>
#include<string.h>


char token[50][5];
int n=0;
char expr[50];
int count=0;

int main(){
    printf("Enter the expression:\n");
    scanf("%s",expr);
    printf("INTERMEDIATE CODE:\n");
    for(int i=0;expr[i]!='\0';i++){
        char single[2];
        single[0]=expr[i];
        single[1]='\0';
        strcpy(token[n],single);
        n++;
    }
    for(int i=0;i<n;i++){
        //print
        if(token[i][0]=='*'||token[i][0]=='/'){
            printf("t%d=%s %s %s\n",count,token[i-1],token[i],token[i+1]);
            
            //change name
            sprintf(token[i-1],"t%d",count);
            count++;
            //remove others
            for(int j=i+2;j<n;j++){
                strcpy(token[j-2],token[j]);
            }
            n=n-2;
            i=i-1;
        }
    }
    for(int i=0;i<n;i++){
        //print
        if(token[i][0]=='+'||token[i][0]=='-'){
            printf("t%d=%s %s %s\n",count,token[i-1],token[i],token[i+1]);
            //change name
            sprintf(token[i-1],"t%d",count);
            count++;
            //remove others
            for(int j=i+2;j<n;j++){
                strcpy(token[j-2],token[j]);
            }
            n=n-2;
            i=i-1;
        }
    }
    return 0;
}
