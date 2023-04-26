
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>
#include<math.h>

int primes[1001];

void primeinit(){
    
    for(int i = 2;i<1001;i++)
        primes[i]=1;   
    for(int i = 2;i<1001;i++){
        if(primes[i]==1){
            for(int j = 2*i;j<1001;j+=i){
                primes[j]=0;
            }
        }
    }
}

int findprime(int max){
    int r = 2+rand()%(max-2+1);
    while(primes[r]==0)
        r = 2+rand()%(max-2+1);
    return r;
}



int euclidAlgoInv(int num,int base){
    int rp = base;
    int rq = num;
    
    
    int xp = 1,xq = 0;
    int yp = 0,yq = 1;
    int q,r,x,y;
    do{
        q = rp/rq;
        r = rp - q*rq;
        x = xp - q*xq;
        y = yp - q*yq;
        
        xp = xq;xq = x;
        yp = yq;yq = y;
	rp = rq;rq = r;
    }while(r>1);
    
    return y<0?base+y:y;
}

int euclidAlgoRem(int num,int base){
    int rp = base;
    int rq = num;
    
    
    int xp = 1,xq = 0;
    int yp = 0,yq = 1;
    int q,r,x,y;
    do{
        q = rp/rq;
        r = rp - q*rq;
        x = xp - q*xq;
        y = yp - q*yq;
        
        xp = xq;xq = x;
        yp = yq;yq = y;
			rp = rq;rq = r;
    }while(r>1);
    
    return r;
}

int* enc(char*msg,int key,int base){
    int l = strlen(msg);
    int* ab = calloc(l,sizeof(int));
    int pows[20];
	int k = 0;
	int r = 0;
    int t = key;
	while(t>0){
		if(t%2==1){
			pows[k] = r;
			k++;
		}
		t/=2;
		r++;
	}
    for(int i = 0;i<l;i++){
      int sub[r];
		sub[0] = (int)pow(msg[i],1)%base;
		for(int j = 1;j<r;j++){
			sub[j] = (sub[j-1]*sub[j-1])%base;
		}
		int s = 1;
		for(int j = 0;j<k;j++){
			s  = (s*sub[pows[j]])%base;
		}
		
		s = s%base;
      
		ab[i] = s;
		
    }
    return ab;
}

int* dec(int*msg,int l,int key,int base){
    
    int* ab = calloc(l,sizeof(int));
    int pows[20];
	int k = 0;
	int r = 0;
    int t = key;
	while(t>0){
		if(t%2==1){
			pows[k] = r;
			k++;
		}
		t/=2;
		r++;
	}
    for(int i = 0;i<l;i++){
      int sub[r];
		sub[0] = (int)pow(msg[i],1)%base;
		for(int j = 1;j<r;j++){
			sub[j] = (sub[j-1]*sub[j-1])%base;
		}
		int s = 1;
		for(int j = 0;j<k;j++){
			s  = (s*sub[pows[j]])%base;
		}
		
		s = s%base;
      
		ab[i] = s;
		
    }
    return ab;
}

int getkey(int tot){
    int r = 2+rand()%(tot-2);
    while(euclidAlgoRem(r,tot)==0)
        r = 2+rand()%(tot-2);
    return r;
}

int main() {
    primeinit();
    srand(time(NULL));
    char inp[1000];
    printf("Input plain text : ");
    scanf("%[^\n]s",inp);
    
    int p = findprime(100);
    int q = findprime(100);
    printf("\np : %d, q : %d \n",p,q);
    int n = p*q;
    
    int tot = (p-1)*(q-1);
    int e = getkey(tot);
    int inv = euclidAlgoInv(e,tot);
    printf("\ne : %d, e-1 : %d, product : %d \n",e,inv,((e*inv)%tot));
    
    int* ct  = enc(inp,e,n);
    printf("Cipher text : ");
	 for(int i = 0;i<strlen(inp);i++){
		 printf("%c",ct[i]);
	 }
	 printf("\n");
    int* dt = dec(ct,strlen(inp),inv,n);
    printf("Decrypted text : ");
    for(int i = 0;i<strlen(inp);i++){
        printf("%c",dt[i]);
    }
    free(ct);
    free(dt);
    return 0;
}