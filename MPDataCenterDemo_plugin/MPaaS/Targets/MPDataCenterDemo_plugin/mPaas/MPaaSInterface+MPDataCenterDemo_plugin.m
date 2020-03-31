
#import "MPaaSInterface+MPDataCenterDemo_plugin.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-protocol-method-implementation"

@implementation MPaaSInterface (MPDataCenterDemo_plugin)

- (BOOL)enableSettingService
{
    return NO;
}

- (NSString *)userId
{
    return nil;
}

@end

#pragma clang diagnostic pop
