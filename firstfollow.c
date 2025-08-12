#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int n,m=0,i=0,j=0;
char a[10][10],f[10];

void follow(char c);
void first(char c);

int main() {
    int k;
    char ch;

    printf("Enter the no of productions:\n");
    scanf("%d",&n);
    printf("Enter the productions:\n");
    for(i=0;i<n;i++)
        scanf("%s%c",a[i],&ch);

    // Find First and Follow for all unique non-terminals
    for(k=0;k<n;k++) {
        char nt = a[k][0];
        m=0;
        strcpy(f,"");
        first(nt);
        printf("First(%c)={",nt);
        for(i=0;i<m;i++)
            printf("%c, ",f[i]);
        printf("}\n");

        m=0;
        strcpy(f,"");
        follow(nt);
        printf("Follow(%c)={",nt);
        for(i=0;i<m;i++)
            printf("%c ,",f[i]);
        printf("}\n");
    }

    return 0;
}

void first(char c) {
    int k;
    if(!isupper(c))
        f[m++]=c;
    for(k=0;k<n;k++) {
        if(a[k][0]==c) {
            if(a[k][2]=='$')
                follow(a[k][0]);
            else if(islower(a[k][2]) || !isupper(a[k][2]))
                f[m++]=a[k][2];
            else
                first(a[k][2]);
        }
    }
}

void follow(char c) {
    if(a[0][0]==c)
        f[m++]='$';
    for(i=0;i<n;i++) {
        for(j=2;j<strlen(a[i]);j++) {
            if(a[i][j]==c) {
                if(a[i][j+1]!='\0')
                    first(a[i][j+1]);
                if(a[i][j+1]=='\0' && c!=a[i][0])
                    follow(a[i][0]);
            }
        }
    }
}