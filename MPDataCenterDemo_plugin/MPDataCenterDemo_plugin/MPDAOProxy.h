#import "MPInfo.h"

@protocol MPDAOProxy <APDAOProtocol>

- (APDAOResult *)save_info:(MPInfo *)info;
- (MPInfo *)get_info:(NSString *)code;
- (APDAOResult *)update_info:(MPInfo *)info;
- (APDAOResult *)delete_info:(NSString *)code;

@end
