//
//  SSKeychain.h
//  MobileFoundation
//
//  Created by 朱建 on 13-4-9.
//  Copyright (c) 2013年 Alipay. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Security/Security.h>

/** Error codes that can be returned in NSError objects. */
typedef enum {
	/** No error. */
	APSSKeychainErrorNone = noErr,
	
	/** Some of the arguments were invalid. */
	APSSKeychainErrorBadArguments = -1001,
	
	/** There was no password. */
	APSSKeychainErrorNoPassword = -1002,
	
	/** One or more parameters passed internally were not valid. */
	APSSKeychainErrorInvalidParameter = errSecParam,
	
	/** Failed to allocate memory. */
	APSSKeychainErrorFailedToAllocated = errSecAllocate,
	
	/** No trust results are available. */
	APSSKeychainErrorNotAvailable = errSecNotAvailable,
	
	/** Authorization/Authentication failed. */
	APSSKeychainErrorAuthorizationFailed = errSecAuthFailed,
	
	/** The item already exists. */
	APSSKeychainErrorDuplicatedItem = errSecDuplicateItem,
	
	/** The item cannot be found.*/
	APSSKeychainErrorNotFound = errSecItemNotFound,
	
	/** Interaction with the Security Server is not allowed. */
	APSSKeychainErrorInteractionNotAllowed = errSecInteractionNotAllowed,
	
	/** Unable to decode the provided data. */
	APSSKeychainErrorFailedToDecode = errSecDecode
} APSSKeychainErrorCode;

extern NSString *const kAPSSKeychainErrorDomain;

/** Account name. */
extern NSString *const kAPSSKeychainAccountKey;

/**
 Time the item was created.
 
 The value will be a string.
 */
extern NSString *const kAPSSKeychainCreatedAtKey;

/** Item class. */
extern NSString *const kAPSSKeychainClassKey;

/** Item description. */
extern NSString *const kAPSSKeychainDescriptionKey;

/** Item label. */
extern NSString *const kAPSSKeychainLabelKey;

/** Time the item was last modified.
 
 The value will be a string.
 */
extern NSString *const kAPSSKeychainLastModifiedKey;

/** Where the item was created. */
extern NSString *const kAPSSKeychainWhereKey;

/**
 Simple wrapper for accessing accounts, getting passwords, setting passwords, and deleting passwords using the system
 Keychain on Mac OS X and iOS.
 
 This was originally inspired by EMKeychain and SDKeychain (both of which are now gone). Thanks to the authors.
 SSKeychain has since switched to a simpler implementation that was abstracted from [SSToolkit](http://sstoolk.it).
 */
@interface APSSKeychain : NSObject

///-----------------------
/// @name Getting Accounts
///-----------------------

/**
 Returns an array containing the Keychain's accounts, or `nil` if the Keychain has no accounts.
 
 See the `NSString` constants declared in SSKeychain.h for a list of keys that can be used when accessing the
 dictionaries returned by this method.
 
 @return An array of dictionaries containing the Keychain's accounts, or `nil` if the Keychain doesn't have any
 accounts. The order of the objects in the array isn't defined.
 
 @see allAccounts:
 */
+ (NSArray *)allAccounts;

/**
 Returns an array containing the Keychain's accounts, or `nil` if the Keychain doesn't have any
 accounts.
 
 See the `NSString` constants declared in SSKeychain.h for a list of keys that can be used when accessing the
 dictionaries returned by this method.
 
 @param error If accessing the accounts fails, upon return contains an error that describes the problem.
 
 @return An array of dictionaries containing the Keychain's accounts, or `nil` if the Keychain doesn't have any
 accounts. The order of the objects in the array isn't defined.
  
 @see allAccounts
 */
+ (NSArray *)allAccounts:(NSError **)error;

/**
 Returns an array containing the Keychain's accounts for a given service, or `nil` if the Keychain doesn't have any
 accounts for the given service.
 
 See the `NSString` constants declared in SSKeychain.h for a list of keys that can be used when accessing the
 dictionaries returned by this method.
 
 @param serviceName The service for which to return the corresponding accounts.
 
 @return An array of dictionaries containing the Keychain's accountsfor a given `serviceName`, or `nil` if the Keychain
 doesn't have any accounts for the given `serviceName`. The order of the objects in the array isn't defined.
 
 @see accountsForService:error:
 */
+ (NSArray *)accountsForService:(NSString *)serviceName;

/**
 Returns an array containing the Keychain's accounts for a given service, or `nil` if the Keychain doesn't have any
 accounts for the given service.
 
 @param serviceName The service for which to return the corresponding accounts.
 
 @param error If accessing the accounts fails, upon return contains an error that describes the problem.
 
 @return An array of dictionaries containing the Keychain's accountsfor a given `serviceName`, or `nil` if the Keychain
 doesn't have any accounts for the given `serviceName`. The order of the objects in the array isn't defined.
 
 @see accountsForService:
 */
+ (NSArray *)accountsForService:(NSString *)serviceName error:(NSError **)error;


///------------------------
/// @name Getting Passwords
///------------------------

/**
 Returns a string containing the password for a given account and service, or `nil` if the Keychain doesn't have a
 password for the given parameters.
 
 @param serviceName The service for which to return the corresponding password.
 
 @param account The account for which to return the corresponding password.
 
 @return Returns a string containing the password for a given account and service, or `nil` if the Keychain doesn't
 have a password for the given parameters.
 
 @see passwordForService:account:error:
 */
+ (NSString *)passwordForService:(NSString *)serviceName account:(NSString *)account;

/**
 Returns a string containing the password for a given account and service, or `nil` if the Keychain doesn't have a
 password for the given parameters.
 
 @param serviceName The service for which to return the corresponding password.
 
 @param account The account for which to return the corresponding password.
 
 @param error If accessing the password fails, upon return contains an error that describes the problem.
 
 @return Returns a string containing the password for a given account and service, or `nil` if the Keychain doesn't
 have a password for the given parameters.
 
 @see passwordForService:account:
 */
+ (NSString *)passwordForService:(NSString *)serviceName account:(NSString *)account error:(NSError **)error;

/**
 Returns the password data for a given account and service, or `nil` if the Keychain doesn't have data 
 for the given parameters.
 
 @param serviceName The service for which to return the corresponding password.
 
 @param account The account for which to return the corresponding password.
 
 @param error If accessing the password fails, upon return contains an error that describes the problem.
 
 @return Returns a the password data for the given account and service, or `nil` if the Keychain doesn't
 have data for the given parameters.
 
 @see passwordDataForService:account:error:
 */
+ (NSData *)passwordDataForService:(NSString *)serviceName account:(NSString *)account;

/**
 Returns the password data for a given account and service, or `nil` if the Keychain doesn't have data 
 for the given parameters.
 
 @param serviceName The service for which to return the corresponding password.
 
 @param account The account for which to return the corresponding password.
 
 @param error If accessing the password fails, upon return contains an error that describes the problem.
 
 @return Returns a the password data for the given account and service, or `nil` if the Keychain doesn't
 have a password for the given parameters.
 
 @see passwordDataForService:account:
 */
+ (NSData *)passwordDataForService:(NSString *)serviceName account:(NSString *)account error:(NSError **)error;


///-------------------------
/// @name Deleting Passwords
///-------------------------

/**
 Deletes a password from the Keychain.
 
 @param serviceName The service for which to delete the corresponding password.
 
 @param account The account for which to delete the corresponding password.
 
 @return Returns `YES` on success, or `NO` on failure.
 
 @see deletePasswordForService:account:error:
 */
+ (BOOL)deletePasswordForService:(NSString *)serviceName account:(NSString *)account;

/**
 Deletes a password from the Keychain.
 
 @param serviceName The service for which to delete the corresponding password.
 
 @param account The account for which to delete the corresponding password.
 
 @param error If deleting the password fails, upon return contains an error that describes the problem.
 
 @return Returns `YES` on success, or `NO` on failure.
 
 @see deletePasswordForService:account:
 */
+ (BOOL)deletePasswordForService:(NSString *)serviceName account:(NSString *)account error:(NSError **)error;


///------------------------
/// @name Setting Passwords
///------------------------

/**
 Sets a password in the Keychain.
 
 @param password The password to store in the Keychain.
 
 @param serviceName The service for which to set the corresponding password.
 
 @param account The account for which to set the corresponding password.
 
 @return Returns `YES` on success, or `NO` on failure.
 
 @see setPassword:forService:account:error:
 */
+ (BOOL)setPassword:(NSString *)password forService:(NSString *)serviceName account:(NSString *)account;

/**
 Sets a password in the Keychain.
 
 @param password The password to store in the Keychain.
 
 @param serviceName The service for which to set the corresponding password.
 
 @param account The account for which to set the corresponding password.
 
 @param error If setting the password fails, upon return contains an error that describes the problem.
 
 @return Returns `YES` on success, or `NO` on failure.
 
 @see setPassword:forService:account:
 */
+ (BOOL)setPassword:(NSString *)password forService:(NSString *)serviceName account:(NSString *)account error:(NSError **)error;

/**
 Sets arbirary data in the Keychain.
 
 @param password The data to store in the Keychain.
 
 @param serviceName The service for which to set the corresponding password.
 
 @param account The account for which to set the corresponding password.
 
 @param error If setting the password fails, upon return contains an error that describes the problem.
 
 @return Returns `YES` on success, or `NO` on failure.
 
 @see setPasswordData:forService:account:error:
 */
+ (BOOL)setPasswordData:(NSData *)password forService:(NSString *)serviceName account:(NSString *)account;

/**
 Sets arbirary data in the Keychain.
 
 @param password The data to store in the Keychain.
 
 @param serviceName The service for which to set the corresponding password.
 
 @param account The account for which to set the corresponding password.
 
 @param error If setting the password fails, upon return contains an error that describes the problem.
 
 @return Returns `YES` on success, or `NO` on failure.
 
 @see setPasswordData:forService:account:
 */
+ (BOOL)setPasswordData:(NSData *)password forService:(NSString *)serviceName account:(NSString *)account error:(NSError **)error;


///--------------------
/// @name Configuration
///--------------------

#if __IPHONE_4_0 && TARGET_OS_IPHONE
/**
 Returns the accessibility type for all future passwords saved to the Keychain.
 
 @return Returns the accessibility type.
 
 The return value will be `NULL` or one of the "Keychain Item Accessibility Constants" used for determining when a
 keychain item should be readable.
 
 @see accessibilityType
 */
+ (CFTypeRef)accessibilityType;

/**
 Sets the accessibility type for all future passwords saved to the Keychain.
 
 @param accessibilityType One of the "Keychain Item Accessibility Constants" used for determining when a keychain item
 should be readable.
 
 If the value is `NULL` (the default), the Keychain default will be used.
 
 @see accessibilityType
 */
+ (void)setAccessibilityType:(CFTypeRef)accessibilityType;
#endif

@end
