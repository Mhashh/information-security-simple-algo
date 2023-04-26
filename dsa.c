#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
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

unsigned int findprime(unsigned int min,unsigned int max){
    unsigned int r = min+rand()%(max-min+1);
    while(primes[r]==0)
        r = min+rand()%(max-2+1);
    return r;
}
unsigned int findP(unsigned int q){
    unsigned int max = pow(2,12);
    unsigned int min = pow(2,11);
    unsigned int p = findprime(min+1,max-1);

    while(p%q!=1){
        p = findprime(min+1,max-1);
    }
    return p;
}

unsigned int findH(unsigned int p,unsigned int q){
    unsigned int d = (p-1)/q;
    
    unsigned int h = 2+(rand()%(p-2-2+1));
    unsigned int s = 1;
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

//l 12(2^30), n<l and n 8(2^8 = 256 ) h 10(2^1024)
int main(){
    srand(time(NULL));
    primeinit();
    unsigned int q = findprime(129,255);
    printf("q=%d\n",q);
    unsigned int p = findP(q);
    printf("p=%d\n",p);
    unsigned int h = 2+(rand()%(p-2));
    ui g = powe(h,(p-1)/q,p);
    ui pk = 1+(rand()%(q-1));
    ui y = powe(g,pk,p);
   
    ui k = 1+(rand()%(q-1));

    //sign
    ui r = powe(g,k,p)%q;
    printf("r = %d\n",r);
    ui s = (euclidAlgoInv(k,q)*(((10%1024)+pk*r)%q))%q;
    printf("s = %d\n",s);


    //verify
    ui w = euclidAlgoInv(s,q);
    ui u1 = (10%1024)*(w%q);
    ui u2 = (r*w)%q;
    ui v = ((powe(g,u1,p)*powe(y,u2,p))%p)%q;
    printf("v=%d",v);
    return 0;
}