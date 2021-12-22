//给定一个非负整数、求它的开方，向下取整
//用二分法来做

//1.找区间
//f(x)=x^2-a = 0 
//f(0)=-a <0
//f(a)= a^2-a >0
//因此在[0,a]上必有零解

//2.为了避免除以零，把a=0单独考虑，因此区间为[1,a]进行二分查找

//a= mid*mid
//mid = a/mid
//sqrt = a/mid
//if(sqrt== mid )
int mySqrt(int a){
    if (a==0) 
        return a;//0的开方=0

    int left = 1, right =a, mid, sqrt;
    while(left<=right){
        //先求mid
        // mid = (left+right)/2;//这种情况可能会溢出,因此用下面这种
        mid = (right-left)/2+left;

        sqrt = a/mid;

        if(sqrt==mid)
            return sqrt;
        else if(sqrt<mid)//mid太大了
            right=mid-1;
        else    
            left=mid+1;

    }

    //不然的话
    return right;
}