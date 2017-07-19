//
//  ViewController.m
//  ImageFilterByColorMatrix
//
//  Created by HenryVarro on 2017/7/17.
//  Copyright © 2017年 丁子恒. All rights reserved.
//

#import "ViewController.h"
#import "ZYFilterImageView.h"
#import "ZHMacroDefinition.h"
@interface ViewController ()<ZYFilterImageViewDelegate>
@property (weak, nonatomic) IBOutlet UIImageView *filterImageView;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    ZYFilterImageView *filterSeleter =[ZYFilterImageView filterViewWithImage:[UIImage imageNamed:@"1.jpeg"] andFrame:CGRectMake(0, kScreenHeight - 96, kScreenWidth, 96)];
    filterSeleter.delegate = self;
    [self.view addSubview:filterSeleter];
}
//滤镜选择后
- (void)imageFilterDidChangeWithAfterImage:(UIImage *)afterImage{
    self.filterImageView.image = afterImage;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
