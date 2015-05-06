#DelegateToBlock

## What?

Stop being forced to use the delegate pattern. This helper class easily converts delegate/selector patterns into blocks.

Create the execution block and pass it with the delegate and selector.

## Why?

While Apple has definately made a shift towards blocks, much of UIKit and other frameworks still require delegate patterns. Alert views are the classic example:

### Current Way
```objc

@interface SomeViewController() <UIAlertViewDelegate>
@property (nonatomic, strong) UIAlertView *alertView;
@end

@implementation SomeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.alertView = [[UIAlertView alloc] initWithTitle:@"title" message:nil delegate:self cancelButtonTitle:@"Dismiss" otherButtonTitles:@"Proceed", nil];
    [self.alertView show];
    
}

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    if (alertView == self.alertView) {
        NSLog(@"tapped index: %ld", buttonIndex);
        self.alertView = nil;
    }
}
@end
```

### New Way
```objc
@interface SomeObject()
@end

@implementation SomeObject

- (void)viewDidLoad {
    [super viewDidLoad];

    [DelegateToBlock makeTarget:self respondToSelector:@selector(alertView:didDismissWithButtonIndex:) withBlock:^void(id target, UIAlertView *alertView, NSInteger tappedIndex) {
        NSLog(@"tapped index: %ld", tappedIndex);
    }];
    
    [[[UIAlertView alloc] initWithTitle:@"title" message:nil delegate:self cancelButtonTitle:@"Dismiss" otherButtonTitles:@"Proceed", nil] show];
}
@end
```

## Pitfalls

• Currently no safety checks are in place to ensure that the provided block has the same input parameters as the selector.

• It is unlikely that compiler warnigs will ever work for ensuring the block and selector have matching parameters (it can be a runtime check though)
