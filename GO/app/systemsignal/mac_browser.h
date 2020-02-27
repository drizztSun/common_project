#import <Foundation/Foundation.h>

const NSArray* getBrowsersLocation();

const char* nsstring2cstring(NSString *s);

int nsnumber2int(NSNumber *i);

unsigned long nsarraylen(NSArray *arr);

const void* nsarrayitem(NSArray *arr, unsigned long i);
