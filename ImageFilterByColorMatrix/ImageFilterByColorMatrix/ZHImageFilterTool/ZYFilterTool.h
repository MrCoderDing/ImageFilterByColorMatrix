//
//  ZYFilterTool.h
//  ZYNaNian
//
//  Created by HenryVarro on 16/11/18.
//  Copyright © 2016年 ZYNaNian. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@interface ZYFilterTool : NSObject



/**
 获取滤镜图

 @param inImage 原图
 @param f       matrix矩阵
 @return        滤镜完成后图片
 */
+ (UIImage*)imageWithImage:(UIImage*)inImage withColorMatrix:(const float*) f;
@end
