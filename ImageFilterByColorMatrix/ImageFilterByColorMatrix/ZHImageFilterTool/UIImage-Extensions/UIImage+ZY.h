//
//  UIImage+ZY.h
//  ZYNaNian
//
//  Created by YiNian on 16/3/18.
//  Copyright © 2016年 ZYNaNian. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIImage (ZY)
+ (UIImage *)resizedImageWithName:(NSString *)name;
+ (UIImage *)resizedImageWithName:(NSString *)name left:(CGFloat)left top:(CGFloat)top;
+ (UIImage *)blurryImage:(UIImage *)image withBlurLevel:(CGFloat)blur;

/// 图片转换时自动旋转, 调正
+ (UIImage *)cropImage:(UIImage*)image toRect:(CGRect)rect;
//图片旋转纠正
+ (UIImage *)fixOrientation:(UIImage* )aImage;

/**
 生成截图

 @param view 界面
 @return 截图
 */
+ (UIImage *)makeImageWithView:(UIView *)view;
@end
