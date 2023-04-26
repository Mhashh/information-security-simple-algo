#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#define ui unsigned int
int primes[10000];

void primeinit(){
    
    for(int i = 2;i<10000;i++)
        primes[i]=1;   
    for(int i = 2;i<10000;i++){
        if(primes[i]==1){
            for(int j = 2*i;j<10000;j+=i){
                primes[j]=0;
            }
        }
    }
}

ui findprime(ui min,ui max){
    ui r = min+rand()%(max-min+1);
    while(primes[r]==0)
        r = min+rand()%(max-2+1);
    return r;
}
ui findP(ui q){
    ui max = pow(2,12);
    ui min = pow(2,11);
    ui p = findprime(min+1,max-1);

    while(p%q!=1){
        p = findprime(min+1,max-1);
    }
    return p;
}

ui findH(ui p,ui q){
    ui d = (p-1)/q;
    
    ui h = 2+(rand()%(p-2-2+1));
    ui s = 1;
    for(int i = 0;i<d;i++){
        s = ((s*h)%p); 
    }

    while(s>1){
        h = 2+(rand()%(p-2-2+1));
        s = 1;
        for(int i = 0;i<d;i++){
            s = ((s*h)%p); 
        }
    }
    return h;
}

ui powe(ui e,ui p,ui mod){
    ui s= 1;
    for(int i = 0;i<p;i++){
        s = ((s*e)%mod);
    }
    return s;
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

ui hash1024(char* msg){
    int len = strlen(msg);
    ui hash = 0;
    for(int i = 0;i<len;i++){
        hash = (hash+msg[i])%1024
    }
    return hash;
}

//l 12(2^30), n<l and n 8(2^8 = 256 ) h 10(2^1024)
int main(){
    srand(time(NULL));
    primeinit();
    char msg[1000];
    prinf("Input message : ",msg);
    scanf("%s"msg);
    ui q = findprime(129,255);
    printf("q=%d\n",q);
    ui p = findP(q);
    printf("p=%d\n",p);
    ui h = 2+(rand()%(p-2));
    ui g = powe(h,(p-1)/q,p);
    ui pk = 1+(rand()%(q-1));
    ui y = powe(g,pk,p);
   
    ui k = 1+(rand()%(q-1));

    //sign
    printf("\nSignature\n");
    ui r = powe(g,k,p)%q;
    printf("r = %d\n",r);
    ui s = (euclidAlgoInv(k,q)*((hash1024(msg)+pk*r)%q))%q;
    printf("s = %d\n",s);


    //verify
    printf("\nVerify\n");
    ui w = euclidAlgoInv(s,q);
    ui u1 = hash1024(msg)*(w%q);
    ui u2 = (r*w)%q;
    ui v = ((powe(g,u1,p)*powe(y,u2,p))%p)%q;
    printf("v=%d",v);
    return 0;
}
