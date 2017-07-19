//
//  ZYFilterImageView.h
//  ZYNaNian
//
//  Created by HenryVarro on 16/11/18.
//  Copyright © 2016年 ZYNaNian. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol ZYFilterImageViewDelegate <NSObject>
@required
//滤镜选择后
- (void)imageFilterDidChangeWithAfterImage:(UIImage *)afterImage;

@end

@interface ZYFilterImageView : UIView

//代理
@property (nonatomic,assign)id<ZYFilterImageViewDelegate> delegate;
//原始图
@property (nonatomic,copy)UIImage *originalImage;
//滤镜后
@property (nonatomic,copy)UIImage *afterImage;

/**
 滤镜工具

 @param originalImage 原始图片
 @param frame         滤镜工具条
 @return              滤镜工具条对象
 */
+ (instancetype)filterViewWithImage:(UIImage *)originalImage andFrame:(CGRect)frame;
@end
