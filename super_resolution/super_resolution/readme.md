## 项目说明：  
类似pytorch、tensorflow等深度学习推理平台，亲手搭建自己的c/c++推理平台，主要实现图像超分辨率算法，利用AVX2指令集实现的卷积，和利用openblas矩阵加速库实现的卷积。  
### 图像存储类声明定义：  
[superResolution.h](https://github.com/aoaforever/C_trian/blob/master/super_resolution/super_resolution/superResolution.h)    
### c++/AVX2指令加速的与openblas矩阵加速库的卷积实现  
[superResolution.cpp](https://github.com/aoaforever/C_trian/blob/master/super_resolution/super_resolution/superResolution.cpp)
