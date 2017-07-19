//
//  ZYFilterImageView.m
//  ZYNaNian
//
//  Created by HenryVarro on 16/11/18.
//  Copyright © 2016年 ZYNaNian. All rights reserved.
//

#import "ZYFilterImageView.h"
#import "ZYFilterTool.h"
#import "ColorMatrix.h"
#import "UIImage+Resize.h"
#import "UIImage+ZY.h"
#import "ZHMacroDefinition.h"
#define LeftMagin  54/2.f
#define TopMagin   35/2.f
//内间距
#define InnerMagin 32/2.f
//滤镜选图宽高
#define WidthAndHeight 45
//圆角
#define CornerRadius   12/2.f
@interface ZYFilterImageView()




@end


@implementation ZYFilterImageView
{
    //滤镜名称
    NSArray * filterNameArray ;
    UIScrollView *scrollView;
    //选中框
    UIView * selectView;
    UILabel *_lastLabel;
}


/**
 滤镜工具
 
 @param originalImage 原始图片
 @param frame         滤镜工具条
 @return              滤镜工具条对象
 */
+ (instancetype)filterViewWithImage:(UIImage *)originalImage andFrame:(CGRect)frame{
    ZYFilterImageView *filterView = [[ZYFilterImageView alloc] initWithFrame:frame];
    filterView.originalImage = [UIImage fixOrientation:originalImage];
    [filterView createUI];
    
    return filterView;
}
#pragma mark - 创建UI界面
- (void)createUI {
    filterNameArray = @[@"原图",@"LOMO",@"黑白",@"复古",@"哥特",@"锐色",@"淡雅",@"酒红",@"青柠",@"浪漫",@"光晕",@"蓝调",@"梦幻",@"夜色"];
    
    scrollView = [[UIScrollView alloc]initWithFrame:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height)];
    scrollView.backgroundColor = [UIColor clearColor];
    scrollView.indicatorStyle = UIScrollViewIndicatorStyleBlack;
    scrollView.showsHorizontalScrollIndicator = NO;
    scrollView.showsVerticalScrollIndicator = NO;
    scrollView.bounces = YES;
    
    [self addSubview:scrollView];
    [self createFilterBtn];
    
}
#pragma mark - 创建滤镜选择
- (void)createFilterBtn{
    
    //选择框
    selectView = [[UIView alloc] initWithFrame:CGRectMake(LeftMagin-1, TopMagin-1, WidthAndHeight+2, WidthAndHeight+2)];
    selectView.layer.cornerRadius = CornerRadius;
    selectView.layer.borderColor = [UIColor blackColor].CGColor;
    selectView.layer.borderWidth = 1;
    selectView.clipsToBounds = YES;
    [scrollView addSubview:selectView];
    
    
    UIImage *smallImg = [_originalImage thumbnailImage:WidthAndHeight*2 transparentBorder:0 cornerRadius:0 interpolationQuality:kCGInterpolationDefault];
    
    for (int i = 0; i<filterNameArray.count; i++) {
        UITapGestureRecognizer *recognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(setImageStyle:)];
        recognizer.numberOfTouchesRequired = 1;
        recognizer.numberOfTapsRequired = 1;
        
        
        UIImageView *bgImageView = [[UIImageView alloc]initWithFrame:CGRectMake(LeftMagin+i*(WidthAndHeight+InnerMagin), TopMagin, WidthAndHeight, WidthAndHeight)];
        [bgImageView setTag:i+100];
        [bgImageView addGestureRecognizer:recognizer];
        [bgImageView setUserInteractionEnabled:YES];
        bgImageView.layer.cornerRadius = CornerRadius;
        bgImageView.clipsToBounds = YES;
        [scrollView addSubview:bgImageView];
        
        UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(LeftMagin+i*(WidthAndHeight+InnerMagin), TopMagin+WidthAndHeight+5, WidthAndHeight, 12)];
        [label setBackgroundColor:[UIColor clearColor]];
        [label setText:[filterNameArray objectAtIndex:i]];
        [label setTextAlignment:NSTextAlignmentCenter];
        [label setFont:[UIFont systemFontOfSize:11.0f]];
        [label setTextColor: kRGB(153,153,153)];//zRGBColor(153, 153, 153)];
        [label setUserInteractionEnabled:YES];
        [label setTag:i+200];
        [scrollView addSubview:label];
        
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
             UIImage *bgImage = [self changeImage:i image:smallImg];
            [bgImageView performSelectorOnMainThread:@selector(setImage:) withObject:bgImage waitUntilDone:NO];
        });
    }
    scrollView.contentSize = CGSizeMake(LeftMagin+filterNameArray.count*(WidthAndHeight+InnerMagin), self.frame.size.height);
    
    UILabel *label = [scrollView viewWithTag:200];
    label.textColor = [UIColor blackColor];
    _lastLabel = label;
    
}
#pragma mark - 选择滤镜
- (void)setImageStyle:(UITapGestureRecognizer *)sender
{
    NSInteger num = sender.view.tag-100;
    selectView.center = sender.view.center;
    
    _lastLabel.textColor = kRGB(153, 153, 153);
    UILabel *label = [scrollView viewWithTag:200+num];
    label.textColor = [UIColor blackColor];
    _lastLabel = label;
    
   
   
    if([self.delegate respondsToSelector:@selector(imageFilterDidChangeWithAfterImage:)]){
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
             UIImage *img = [self changeImage:num image:_originalImage];
            dispatch_async(dispatch_get_main_queue(), ^{
                [self.delegate imageFilterDidChangeWithAfterImage:
                 img];
            });
           

        });
        
    }
}

#pragma mark - 滤镜切换
-(UIImage *)changeImage:(NSInteger)index image:(UIImage *)img
{
    if (img == nil) {
        img = _originalImage;
    }
    UIImage *image;
    switch (index) {
        case 0:
        {
            return img;
        }
            break;
        case 1:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_lomo];
        }
            break;
        case 2:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_heibai];
        }
            break;
        case 3:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_huajiu];
        }
            break;
        case 4:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_gete];
        }
            break;
        case 5:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_ruise];
        }
            break;
        case 6:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_danya];
        }
            break;
        case 7:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_jiuhong];
        }
            break;
        case 8:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_qingning];
        }
            break;
        case 9:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_langman];
        }
            break;
        case 10:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_guangyun];
        }
            break;
        case 11:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_landiao];
            
        }
            break;
        case 12:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_menghuan];
            
        }
            break;
        case 13:
        {
            image = [ZYFilterTool imageWithImage:img withColorMatrix:colormatrix_yese];
            
        }
    }
    return image;
}

@end
