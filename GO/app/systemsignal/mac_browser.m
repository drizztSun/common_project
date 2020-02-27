#import "mac_browser.h"

const NSArray* getBrowsersLocation() {
    @autoreleasepool {
        NSArray *browsers = [NSArray arrayWithObjects: @"org.mozilla.firefox", @"com.google.Chrome", @"com.operasoftware.Opera", @"com.apple.Safari", nil];
        NSMutableArray *result = [[NSMutableArray alloc] init];
        for (NSString *bundleId in browsers) {
            NSArray *apps = CFBridgingRelease(LSCopyApplicationURLsForBundleIdentifier(CFBridgingRetain(bundleId), nil));
            if (apps != nil) {
                for(NSURL *url in apps) {
                    NSString *string =  [url.absoluteString stringByRemovingPercentEncoding];
                    [result addObject: string];
                }
            }
        }
        return result;
    }
}

const char* nsstring2cstring(NSString *s) {
    if (s == NULL) { return NULL; }
    const char *cstr = [s UTF8String];
    return cstr;
}

unsigned long nsarraylen(NSArray *arr) {
    if (arr == NULL) { return 0; }
    return arr.count;
}

const void* nsarrayitem(NSArray *arr, unsigned long i) {
    if (arr == NULL) { return NULL; }
    return CFBridgingRetain([arr objectAtIndex:i]);
}
