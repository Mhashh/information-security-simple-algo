
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
char* railFence(char* msg,int key){
    int l = strlen(msg);
    char* ab = (char*)calloc(l, sizeof(char));
    int j = 0;
    int maxdiff = 2*(key-1);
    int k = 0;
    for(int p = 0;p<key;p++){
        int diff =k;
        if(diff > 0)
            for(int i = p;i<l;i+=diff){
                ab[j] = msg[i];
                j++;
                diff = maxdiff-diff;
            }
        else
            for(int i = p;i<l;i+=maxdiff){
                ab[j] = msg[i];
                j++;
            }
        k=(k+2)%maxdiff;
    }
    
    return ab;
}

char* railFenceD(char* msg,int key){
    int l = strlen(msg);
    char* ab = (char*)calloc(l, sizeof(char));
    int j = 0;
    int maxdiff = 2*(key-1);
    int k = 0;
    for(int p = 0;p<key;p++){
        int diff =k;
        
        if(diff > 0)
            for(int i = p;i<l;i+=diff){
                ab[i] = msg[j];
                j++;
                diff = maxdiff-diff;
            }
        else
            for(int i = p;i<l;i+=maxdiff){
                ab[i] = msg[j];
                j++;
            }
        k=(k+2)%maxdiff;
    }
    
    return ab;
}

int main() {
    char inp[1000];
    int k = 0;
    printf("Input plain text : ");
    scanf("%[^\n]s",inp);
    printf("Input key : ");
    scanf("%d",&k);
    char* ct  = railFence(inp,k);
    printf("Cipher text : %s \n",ct);
    char* dt = railFenceD(ct,k);
    printf("Decrypted text : %s \n",dt);
    free(ct);
    free(dt);
    return 0;
}