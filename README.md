![Demo截图](http://img.blog.csdn.net/20170719103812736?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvUmljaGFyX0RfVHlzb24=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

Demo链接：https://github.com/MrCoderDing/ImageFilterByColorMatrix


说到滤镜一般比较熟悉的是CIFilter、GPUImage、vImage API还有一种比较简单的滤镜ColorMatrix。
之前在项目中一个小功能要加滤镜，需求是要够用，方便。在没有考虑直接用第三方滤镜的情况下，最后还是选择使用ColorMatrix来完成任务。并且这个方案安卓和iOS通用，如果花时间做一套颜色矩阵，成本将降低很多。

1、颜色矩阵
---------

lomo和黑白我做了细微调整，会稍微舒服一些：

``` // 1、LOMO
const float colormatrix_lomo[] = {
//    1.7f,  0.1f, 0.1f, 0, -73.1f,
//    0,  1.7f, 0.1f, 0, -73.1f,
//    0,  0.1f, 1.6f, 0, -73.1f,
//    0,  0, 0, 1.0f, 0
    1.20, 0.10, 0.10, 0.00, -73.10,
    0.00, 1.20, 0.10, 0.00, -73.10,
    0.00, 0.10, 1.10, 0.00, -73.10,
    0.00, 0.00, 0.00, 0.00, 0.00
};

// 2、黑白
const float colormatrix_heibai[] = {
    

//    0.8f,  1.6f, 0.2f, 0, -163.9f,
//    0.8f,  1.6f, 0.2f, 0, -163.9f,
//    0.8f,  1.6f, 0.2f, 0, -163.9f,
//    0,  0, 0, 1.0f, 0
    0.00, 0.00, 1.00, 0.00, -1,
    0.00, 0.00, 1.00, 0.00, -1,
    0.00, 0.00, 1.00, 0.00, -1,
    0.00, 0.00, 0.00, 1.00, 0.00
};
// 3、复古
const float colormatrix_huajiu[] = { 
    0.2f,0.5f, 0.1f, 0, 40.8f,
    0.2f, 0.5f, 0.1f, 0, 40.8f, 
    0.2f,0.5f, 0.1f, 0, 40.8f, 
    0, 0, 0, 1, 0 };

// 4、哥特
const float colormatrix_gete[] = { 
    1.9f,-0.3f, -0.2f, 0,-87.0f,
    -0.2f, 1.7f, -0.1f, 0, -87.0f, 
    -0.1f,-0.6f, 2.0f, 0, -87.0f, 
    0, 0, 0, 1.0f, 0 };

// 5、锐化
const float colormatrix_ruise[] = { 
    4.8f,-1.0f, -0.1f, 0,-388.4f,
    -0.5f,4.4f, -0.1f, 0,-388.4f, 
    -0.5f,-1.0f, 5.2f, 0,-388.4f,
    0, 0, 0, 1.0f, 0 };


// 6、淡雅
const float colormatrix_danya[] = { 
    0.6f,0.3f, 0.1f, 0,73.3f,
    0.2f,0.7f, 0.1f, 0,73.3f, 
    0.2f,0.3f, 0.4f, 0,73.3f,
    0, 0, 0, 1.0f, 0 };

// 7、酒红
const float colormatrix_jiuhong[] = { 
    1.2f,0.0f, 0.0f, 0.0f,0.0f,
    0.0f,0.9f, 0.0f, 0.0f,0.0f, 
    0.0f,0.0f, 0.8f, 0.0f,0.0f,
    0, 0, 0, 1.0f, 0 };

// 8、清宁
const float colormatrix_qingning[] = { 
    0.9f, 0, 0, 0, 0, 
    0, 1.1f,0, 0, 0, 
    0, 0, 0.9f, 0, 0, 
    0, 0, 0, 1.0f, 0 };

// 9、浪漫
const float colormatrix_langman[] = { 
    0.9f, 0, 0, 0, 63.0f, 
    0, 0.9f,0, 0, 63.0f, 
    0, 0, 0.9f, 0, 63.0f, 
    0, 0, 0, 1.0f, 0 };

// 10、光晕
const float colormatrix_guangyun[] = { 
    0.9f, 0, 0,  0, 64.9f,
    0, 0.9f,0,  0, 64.9f,
    0, 0, 0.9f,  0, 64.9f,
    0, 0, 0, 1.0f, 0 };

// 11、蓝调
const float colormatrix_landiao[] = {
    2.1f, -1.4f, 0.6f, 0.0f, -31.0f, 
    -0.3f, 2.0f, -0.3f, 0.0f, -31.0f,
    -1.1f, -0.2f, 2.6f, 0.0f, -31.0f, 
    0.0f, 0.0f, 0.0f, 1.0f, 0.0f
};

// 12、梦幻
const float colormatrix_menghuan[] = {
    0.8f, 0.3f, 0.1f, 0.0f, 46.5f, 
    0.1f, 0.9f, 0.0f, 0.0f, 46.5f, 
    0.1f, 0.3f, 0.7f, 0.0f, 46.5f, 
    0.0f, 0.0f, 0.0f, 1.0f, 0.0f
};

// 13、夜色
const float colormatrix_yese[] = {
    1.0f, 0.0f, 0.0f, 0.0f, -66.6f,
    0.0f, 1.1f, 0.0f, 0.0f, -66.6f, 
    0.0f, 0.0f, 1.0f, 0.0f, -66.6f, 
    0.0f, 0.0f, 0.0f, 1.0f, 0.0f
};

```
矩阵及代表每一种滤镜。

2、滤镜处理Image对象
-------
```
/**
 获取滤镜图

 @param inImage 原图
 @param f       matrix矩阵
 @return        滤镜完成后图片
 */
+ (UIImage*)imageWithImage:(UIImage*)inImage withColorMatrix:(const float*) f;
```
 实现：
 
 
```
+ (UIImage*)imageWithImage:(UIImage*)inImage withColorMatrix:(const float*) f
{
    
    CGImageRef img = [inImage CGImage];
    CGSize size = [inImage size];
    CGContextRef context = NULL;
    CGColorSpaceRef colorSpace;
    void *bitmapData; //内存空间的指针，该内存空间的大小等于图像使用RGB通道所占用的字节数。
    unsigned long bitmapByteCount;
    unsigned long bitmapBytesPerRow;
    
    size_t pixelsWide = CGImageGetWidth(img); //获取横向的像素点的个数
    size_t pixelsHigh = CGImageGetHeight(img); //纵向
    
    bitmapBytesPerRow	= (pixelsWide * 4); //每一行的像素点占用的字节数，每个像素点的ARGB四个通道各占8个bit(0-255)的空间
    bitmapByteCount	= (bitmapBytesPerRow * pixelsHigh); //计算整张图占用的字节数
    
    colorSpace = CGColorSpaceCreateDeviceRGB();//创建依赖于设备的RGB通道
    
    bitmapData = malloc(bitmapByteCount); //分配足够容纳图片字节数的内存空间
    
    context = CGBitmapContextCreate (bitmapData, pixelsWide, pixelsHigh, 8, bitmapBytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast);
    //创建CoreGraphic的图形上下文，该上下文描述了bitmaData指向的内存空间需要绘制的图像的一些绘制参数
    
    CGColorSpaceRelease( colorSpace );

   
    
    CGRect rect = {{0,0},{size.width, size.height}};
     //使用上面的函数创建上下文
    CGContextDrawImage(context, rect, img); //将目标图像绘制到指定的上下文，实际为上下文内的bitmapData。
    unsigned char *data = CGBitmapContextGetData (context);
    
    CGContextRelease(context);
    //释放上面的函数创建的上下文
    unsigned char *imgPixel = data;
   
    int wOff = 0;
    int pixOff = 0;
    
    
    for(GLuint y = 0;y< pixelsHigh;y++)//双层循环按照长宽的像素个数迭代每个像素点
    {
        pixOff = wOff;
        
        for (GLuint x = 0; x<pixelsWide; x++)
        {
            int red = (unsigned char)imgPixel[pixOff];
            int green = (unsigned char)imgPixel[pixOff+1];
            int blue = (unsigned char)imgPixel[pixOff+2];
            int alpha = (unsigned char)imgPixel[pixOff+3];
            changeRGBA(&red, &green, &blue, &alpha, f);
            
            //回写数据
            imgPixel[pixOff] = red;
            imgPixel[pixOff+1] = green;
            imgPixel[pixOff+2] = blue;
            imgPixel[pixOff+3] = alpha;
            
            
            pixOff += 4; //将数组的索引指向下四个元素
        }
        
        wOff += pixelsWide * 4;
    }
    
    NSInteger dataLength = pixelsWide * pixelsHigh * 4;
    
    //下面的代码创建要输出的图像的相关参数
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, imgPixel, dataLength, NULL);
    
    int bitsPerComponent = 8;
    int bitsPerPixel = 32;
    unsigned long bytesPerRow = 4 * pixelsWide;
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    
    CGImageRef imageRef = CGImageCreate(pixelsWide, pixelsHigh, bitsPerComponent, bitsPerPixel, bytesPerRow,colorSpaceRef, bitmapInfo, provider, NULL, NO, renderingIntent);//创建要输出的图像
    
    UIImage *myImage = [UIImage imageWithCGImage:imageRef];
    
    CFRelease(imageRef);
    CGColorSpaceRelease(colorSpaceRef);
    
    CGDataProviderRelease(provider);
    NSData *imageData = UIImageJPEGRepresentation(myImage, 0.5);
    free(bitmapData);
    return [UIImage imageWithData:imageData];
}
```
 注意：参考网上几个实现的方法中，基本都有一个问题没有被注意到，就是bitmapData在申请地址后，最终产出UIImage对象后没有释放掉，导致选择滤镜的过程中内存不断增长。


综合上面的方法就可以自己做滤镜了。简单封装了一个滤镜选择器（即下方的选择条）：
``` 
 /**
 滤镜工具

 @param originalImage 原始图片
 @param frame         滤镜工具条
 @return              滤镜工具条对象
 */
+ (instancetype)filterViewWithImage:(UIImage *)originalImage andFrame:(CGRect)frame; 

```
滤镜选择后代理方法：
```
//滤镜选择后
- (void)imageFilterDidChangeWithAfterImage:(UIImage *)afterImage;
```

用colormatrix处理图片会阻塞线程，所以把图片处理都放到异步来做，回到主线程改变图片，例如代理的回调：
```
dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
             UIImage *img = [self changeImage:num image:_originalImage];
            dispatch_async(dispatch_get_main_queue(), ^{
                [self.delegate imageFilterDidChangeWithAfterImage:
                 img];
            });
           

        });
```
