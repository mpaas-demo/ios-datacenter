
#import "ViewController.h"
#import <MPDataCenter/MPDataCenter.h>

# define  dataBusiness @"dataTestCase"

@protocol DemoProtocol <APDAOProtocol>
- (APDAOResult*)insertItem:(NSString*)content;
- (NSString*)getItem:(NSNumber*)index;
@end


@interface MPCodingData : NSObject <NSCoding>
@property (nonatomic, strong) NSString *name;
@property (nonatomic, assign) NSInteger age;
@end

@implementation MPCodingData

- (void)encodeWithCoder:(NSCoder *)aCoder
{
    [aCoder encodeObject:self.name forKey:@"name"];
    [aCoder encodeInteger:self.age forKey:@"age"];
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    MPCodingData *data = [MPCodingData new];
    data.name = [aDecoder decodeObjectForKey:@"name"];
    data.age = [aDecoder decodeIntegerForKey:@"age"];
    return data;
}

@end


@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.title = @"统一存储";
    self.view.backgroundColor = [UIColor whiteColor];
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    button.frame = CGRectMake(30, 150, [UIScreen mainScreen].bounds.size.width-60, 44);
    button.backgroundColor = [UIColor blueColor];
    [button setTitle:@"KV 存储" forState:UIControlStateNormal];
    [button addTarget:self action:@selector(kvStorage) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:button];
    
    UIButton *button1 = [UIButton buttonWithType:UIButtonTypeCustom];
    button1.frame = CGRectOffset(button.frame, 0, 80);
    button1.backgroundColor = [UIColor blueColor];
    [button1 setTitle:@"LRU 存储" forState:UIControlStateNormal];
    [button1 addTarget:self action:@selector(lruStorage) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:button1];
}


- (void)kvStorage
{
    [APCommonPreferences setInteger:11 forKey:@"intkey" business:dataBusiness];
       NSInteger intValue = [APCommonPreferences integerForKey:@"intkey" business:dataBusiness];
       assert(intValue == 11);
       
       
       [APCommonPreferences setDouble:11.11 forKey:@"doubleKey" business:dataBusiness];
       double doubleValue = [APCommonPreferences doubleForKey:@"doubleKey" business:dataBusiness];
       assert(doubleValue == 11.11);
       
       
       [APCommonPreferences setString:@"helloDataCenter" forKey:@"strKey" business:dataBusiness];
       NSString *str = [APCommonPreferences stringForKey:@"strKey" business:dataBusiness];
       assert([str isEqualToString:@"helloDataCenter"]);
       
       
       [APCommonPreferences setObject:@{@"hello": @"data"} forKey:@"plistObjectKey" business:dataBusiness];
       NSDictionary *dict = [APCommonPreferences objectForKey:@"plistObjectKey" business:dataBusiness];
       assert([@"data" isEqualToString:[dict objectForKey:@"hello"]]);
       
       
       MPCodingData *obj = [MPCodingData new];
       obj.name = @"hello";
       obj.age = 12;
       [APCommonPreferences archiveObject:obj forKey:@"archObjKey" business:dataBusiness];
       MPCodingData *encodeObj = [APCommonPreferences objectForKey:@"archObjKey" business:dataBusiness];
       assert([encodeObj.name isEqualToString:@"hello"] && encodeObj.age == 12);
       
}

- (void)lruStorage
{
    APLRUMemoryCache *mCache = [[APLRUMemoryCache alloc] initWithCapacity:10];
    [mCache setObject:@"vv" forKey:@"key"];
    NSString *str = [mCache objectForKey:@"key"];
    assert([str isEqualToString:@"vv"]);
    
    
    APLRUDiskCache *dCache = [[APLRUDiskCache alloc] initWithName:@"diskCache" capacity:100 userDependent:NO crypted:NO];
    [dCache setObject:@"vvd" forKey:@"key"];
    assert([@"vvd" isEqualToString:[dCache objectForKey:@"key"]]);
    
}


@end

