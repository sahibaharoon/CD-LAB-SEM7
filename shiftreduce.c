#include <stdio.h>
#include <string.h>
#include <ctype.h>



int n;
struct production{
    char lhs;
    char rhs[10];
};


int reduce(char stack[],int *top,char input[],char action[],struct production p[]){
    for (int i = 0; i < n; i++) {
        int rhslen=strlen(p[i].rhs);
        if(*top+1>=rhslen){
            if(strncmp(stack+(*top-rhslen+1),p[i].rhs,rhslen)==0){
            *top=*top-rhslen+1;
            stack[*top]=p[i].lhs;
            stack[*top+1]='\0';

            sprintf(action,"Reduce %c->%s",p[i].lhs,p[i].rhs);
            return 1;
            }

        }
        
    }
    return 0;
    
}

int main(){
    struct production p[10];
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions:\n");
    for (int i = 0; i < n; i++) {
        char line[50];
        scanf("%s",line);

        p[i].lhs=line[0];
        char *rhs=strchr(line,'=')+1;
        strcpy(p[i].rhs,rhs);
    }
    char input[30];
    printf("ENTER THE STRING TO CHECK:");
    scanf("%s",input);
    strcat(input,"$");

    printf("\n%-5s %-20s %-20s %-25s\n", "Step", "Stack", "Input Buffer", "Action");
    printf("-----------------------------------------------------\n");
    int step=1;
    int i=0;
    int top=-1;
    char stack[30];
    char action[30];
    stack[0]='\0';
    while(1){
        printf("%d          %s      %s      ",step++,stack,input+i);
        //accept
        if(input[i]=='$' && stack[0]==p[0].lhs && stack[1]=='\0'){
            printf("ACCEPT\n");
            break;
        }
        //reduce
        if(reduce(stack,&top,input,action,p)){
            printf("%s\n",action);
            continue;
        }
        //error
        if(input[i]=='$'){
            printf("ERROR\n");
            break;
        }
        //shift
        stack[++top]=input[i];
        i++;
        stack[top+1]='\0';
        printf("SHIFT\n");
    }
    return 0;
}
