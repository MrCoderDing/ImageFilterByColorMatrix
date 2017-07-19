//
//  ZHMacroDefinition.h
//  不忘初心，方得始终。
//
//  Created by HenryVarro on 15/4/26.
//  Copyright © 2015年 丁子恒. All rights reserved.
//



#ifndef ZHMacroDefinition_h
#define ZHMacroDefinition_h

///------
/// NSLog
///------

#ifdef DEBUG
#define ZHLog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define ZHLog(...)
#endif

#ifdef DEBUG // 处于开发阶段
#define NSLog(...) NSLog(__VA_ARGS__)
#else // 处于发布阶段
#define NSLog(...)
#endif

///------
/// Block
///------

typedef void (^voidBlock)();
typedef BOOL (^boolBlock)();
typedef int  (^intBlock) ();
typedef id   (^idBlock)  ();

typedef void (^voidBlock_int)(int);
typedef BOOL (^boolBlock_int)(int);
typedef int  (^intBlock_int) (int);
typedef id   (^idBlock_int)  (int);

typedef void (^voidBlock_string)(NSString *);
typedef BOOL (^boolBlock_string)(NSString *);
typedef int  (^intBlock_string) (NSString *);
typedef id   (^idBlock_string)  (NSString *);

typedef void (^voidBlock_id)(id);
typedef BOOL (^boolBlock_id)(id);
typedef int  (^intBlock_id) (id);
typedef id   (^idBlock_id)  (id);

///------
/// Color
///------
#define kRGB(r, g, b) [UIColor colorWithRed:((r) / 255.0) green:((g) / 255.0) blue:((b) / 255.0) alpha:1.0]
#define kRGBAlpha(r, g, b, a) [UIColor colorWithRed:((r) / 255.0) green:((g) / 255.0) blue:((b) / 255.0) alpha:(a)]
#define kHexRGB(rgbValue) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]
#define kHexRGBAlpha(rgbValue, a) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:(a)]
#define kRandomColor      kRGB(arc4random_uniform(256), arc4random_uniform(256), arc4random_uniform(256))

///---------
/// App Info
///---------
#define APP_NAME    ([[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleName"])
#define APP_VERSION ([[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"])
#define APP_BUILD   ([[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"])

///----------------------
/// Persistence Directory
///----------------------
#define kDOCUMENT_DIRECTORY NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES).firstObject
#define kLIBRARY_DIRECTORY NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES)[0]
#define kCACHES_DIRECTORY [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject]

///----------------------
/// NSNotificationCenter
///----------------------
#define ZHNotificationCenter [NSNotificationCenter defaultCenter]

///----------------------
/// Window And ScreenSize
///----------------------
#define kWindow         [UIApplication sharedApplication].keyWindow
#define kTopWindow      [[UIApplication sharedApplication].windows lastObject]

#define kScreenSize     [UIScreen mainScreen].bounds.size
#define kScreenWidth    [UIScreen mainScreen].bounds.size.width
#define kScreenHeight   [UIScreen mainScreen].bounds.size.height
#define kScreenBounds   [UIScreen mainScreen].bounds

#define kIS_IPHONE_4 (fabs((double)[[UIScreen mainScreen] bounds].size.height - (double )480) < DBL_EPSILON )
#define kIS_IPHONE_5 (fabs((double)[[UIScreen mainScreen] bounds].size.height - (double )568) < DBL_EPSILON )
#define kIS_IPHONE_6SIZE (fabs((double)[[UIScreen mainScreen] bounds].size.height - (double )667) < DBL_EPSILON )
#define kIS_IPHONE_6_PLUSSIZE (fabs((double)[[UIScreen mainScreen] bounds].size.height - (double )736) < DBL_EPSILON )

#define kScaleWidth(iphone6Width) [[UIScreen mainScreen] bounds].size.width / 375.f * iphone6Width
#define kScaleHeight(iphone6Height) [[UIScreen mainScreen] bounds].size.height / 667.f * iphone6Height


///------------------------------------
/// RAC Keywordify
///------------------------------------
#if DEBUG
#define rac_keywordify autoreleasepool {}
#else
#define rac_keywordify try {} @catch (...) {}
#endif


///------------------------------------
/// Weak Object or Strong Object
///------------------------------------
#define weakify(object) rac_keywordify __weak __typeof__(object) object##_##weak = object

#define strongify(object) rac_keywordify __strong __typeof__(object) object = object##_##weak



///------------------------------------
/// Suppress PerformSelectorLeakWarning
///------------------------------------
#define SuppressPerformSelectorLeakWarning(Stuff) \
do { \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Warc-performSelector-leaks\"") \
Stuff; \
_Pragma("clang diagnostic pop") \
} while (0)




///------------------------------
/// Table Register Nib For Cell
///------------------------------
#define TableRegisterNib(table,nibName,Identifier) [table registerNib:[UINib nibWithNibName:nibName bundle:nil] forCellReuseIdentifier:Identifier];


///----------
/// Property
///----------
#define ZHString(x) @property(nonatomic,copy)NSString *x
#define ZHArray(x) @property(nonatomic,copy)NSArray *x
#define ZHMutableArray(x) @property(nonatomic,strong)NSMutableArray *x
#define ZHID(x)  @property(nonatomic,strong)id *x
#define ZHIntger(x) @property (nonatomic,assign)NSInteger x


///----------------
/// System Version
///----------------
#define kSystemVersion [[UIDevice currentDevice].systemVersion doubleValue]
#define iOS8 ([[UIDevice currentDevice].systemVersion doubleValue] >= 8.0)

///----------------
/// CGSize Scale
///----------------
#define CGSizeScale(size,scale) CGSizeMake(size.width * scale, size.height * scale)

///----------------
/// User Default
///----------------
#define ZHUserDefaults [NSUserDefaults standardUserDefaults]

///----------------
/// Angel To Randian
///----------------
#define angelToRandian(x)  ((x)/180.0*M_PI)


#endif /* ZHMacroDefinition_h */
