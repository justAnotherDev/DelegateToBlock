//
//  DelegateToBlock.h
//
//  Created by cevanoff on 5/6/15.
//  Copyright (c) 2015 Casey E. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DelegateToBlock : NSObject

/**
 @brief Transform a delegate pattern into a block. When @c selector gets send to @c target the block will be passed all of the input parameters and executed.
 @param selector The target's selector that is being replaced by @c targetThenParametersBlock.
 @param target The object (usually a delegate) that will receive the @c selector.
 @param targetThenParametersBlock The block to replace the selector with. The block must follow this format: ^void(id target, Type argument1, Type argument2, Type argument3)
 @warning If the provided responds already responds to the selector the block will NOT be executed.
 @return Success bool
 
 @code
 
// EXAMPLE CODE

// replace delegate method SEL(alertView:didDismissWithButtonIndex:) with a block
_dismissAlertObject = [[NSObject alloc] init];
[DelegateToBlock replaceSelector:@selector(alertView:didDismissWithButtonIndex:) ofTarget:_dismissAlertObject withBlock:^void(id target, UIAlertView *alertView, NSInteger tappedIndex) {
    NSLog(@"tapped index: %ld", tappedIndex);
}];


// present the alert view with the new object as the delegate
// we could have used self above and here, but the compiler would throw a warning about self not conforming to UIAlertViewDelegate
[[[UIAlertView alloc] initWithTitle:@"title" message:nil delegate:_dismissAlertObject cancelButtonTitle:@"Dismiss" otherButtonTitles:@"Proceed", nil] show]; 
 */
+(BOOL)replaceSelector:(SEL)selector ofTarget:(id)target withBlock:(id)targetThenParametersBlock;

@end
