///////////// 2.63////////////////////
'''
#include<cstdio>
#include<climits>
using namespace std;
unsigned srl(unsigned x,int k){
	unsigned xsra = (int)x>>k;
	int w = 8*sizeof(int);
	int msk = (-1)<<(w-k);
	return xsra & (~msk);
}
int sra(int x,int k){
	int xsrl = (unsigned)x>>k;
	int w = 8*sizeof(int);
	int msk = (-1)<<(w-k);
	int pos = (1<<(w-k-1)&xsrl);
	msk += (!pos)<<(w-k);
	return msk|xsrl;
}
'''

//////////////////2.64////////////////
'''
int any_odd_one(unsigned x){
	return !!(x&(0x55555555));
}
'''

//////////////////2.65////////////////
'''
int odd_ones(unsigned x){
    int y = x>>16;x^=y;
    y= x>>8;x^=y;
    y=x>>4;x^=y;
    y=x>>2;x^=y;
    y=x>>1;x^=y;
    return (x&1);
}
'''

////////////////2.66////////////////
'''
int leftmost_one(unsigned x){
    unsigned y = x;// attention:must decalred in unsigned
    y |= y>>1;
    y |= y>>2;
    y |= y>>4;
    y |= y>>8;
    y |= y>>16;//make the mask in the pattern of 0000011...111
    y = ~(y>>1);
    return x & y;
}
'''

///////////////2.67//////////////////
'''
A: when the shift count is too big, some compilers will chose to exert the module operation while some won't.
B: 
int int_size_is_32(){
    int set_msb = 1<<31;
    int beyond_msb = set_msb<<1;
    return set_msb&&!(beyond_msb);
}
C:
int int_size_is_32_on_16bits(){
    unsigned set_msb = 1<<1<<15<<15;
    unsigned beyond_msb = set_msb<<1;
    return set_msb&&!(beyond_msb);
}
'''

/////////////2.68/////////////////
'''
int lower_one_mask(int n){
    int x = 1<<(n-1);
    x |= x>>1;
    x |= x>>2;
    x |= x>>4; 
    x |= x>>8;
    x |= x>>16;
    return x;
}

'''

/////////////2.69////////////////
'''
unsigned rotate_left(unsigned x,int n){
    int msk = 1<<(32-n);
    msk |= msk<<1;
    msk |= msk<<2;
    msk |= msk<<4;
    msk |= msk<<8;
    msk |= msk<<16;
    msk &= x;
    x=x<<n;
    msk = msk>>(32-n);
    x|=msk;
    return x;
}
'''

//////////////2.70/////////////////
'''

int fits_bits(int x,int n){
    int msk = 1<<(31-n);
    msk|=msk>>1;
    msk|=msk>>2;
    msk|=msk>>4;
    msk|=msk>>8;
    msk|=msk>>16;
    msk &=x;
    return !(x^msk);
}
'''

/////////////2.71//////////////////
'''
A:first it should be (bytenum-1)<<3, also the fruit isn't reflect the sign.
B:
int xbyte(packed_t word, int bytenum){
    int size = sizeof(unsigned);
    int shift_left_cnt = (size-1-bytenum)<<3;
    int shift_right_cnt=(size-1)<<3;
    return word<<shift_left_cnt>>shift_right_cnt;
}
//the sigend return can be regarded as acquiring the sign of return.
'''

////////////2.72////////////////
'''
if(maxbytes>=(int)sizeof(val))
'''

//////////2.73///////////////
'''
int saturating_add(int x,int y){
    int c = x+y ;
    int msk = INT_MIN;
    int pos_ = !(x&msk)&&!(y&msk)&&(c&msk);
    int neg_ = (x&msk)&&(y&msk)&&!(c&msk);
    (pos_&&(c=INT_MAX))||(neg_&&(c=INT_MIN));// use the boolean val of expression is forever true
    return c;
}
'''

////////////2.74/////////////
'''
int tsub_ok(int x,int y){
    int c = x - y;
    int msk = INT_MIN;
    int pos_ = !(x&msk)&&!((-y)&msk)&&(c&msk);
    int neg_ = (x&msk)&&((-y)&msk)&&!(c&msk);
    return !(pos_||neg_);
}// return 0 when overflowed
'''

/////////////2.76///////////
'''

void *my_calloc(size_t nmemb,size_t size){
    if(!nmemb||!size)return NULL;
    
    size_t buf_size = nmemb*size;
    if(nmemb == buf_size/size)//cope with the overflow of multiply
    {
        void *ptr = malloc(buf_size);
        memset(ptr,0,buf_size);
        return ptr;
    }
    return NULL;
}

'''
