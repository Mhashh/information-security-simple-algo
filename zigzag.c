#include <stdio.h>
#include <stdlib.h>
#include<string.h>

char* zigzag(char* msg){
    int l = strlen(msg);
    char* ab = (char*)calloc(l, sizeof(char));
    int j = 0;
    
    for(int i = 0;i<l;i+=2){
        ab[j] = msg[i];
        j++;
    }
    for(int i = 1;i<l;i+=2){
        ab[j] = msg[i];
        j++;
    }
    
    return ab;
}

char* zigzagD(char* msg){
    int l = strlen(msg);
    char* ab = (char*)calloc(l, sizeof(char));
    int j = 0;
    
    for(int i = 0;i<l;i+=2){
        ab[i] = msg[j];
        j++;
    }
    for(int i = 1;i<l;i+=2){
        ab[i] = msg[j];
        j++;
    }
    
    return ab;
}

int main() {
    char inp[1000];
    printf("Input plain text : ");
    scanf("%[^\n]s",inp);
    char* ct  = zigzag(inp);
    printf("Cipher text : %s \n",ct);
    char* dt = zigzagD(ct);
    printf("Cipher text : %s \n",dt);
    free(ct);
    free(dt);
    return 0;
}