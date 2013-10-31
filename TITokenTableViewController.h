//
//  TokenTableViewController.h
//  TokenFieldExample
//
//  Created by jac on 9/5/12.
//
//

#import <UIKit/UIKit.h>
#import "TITokenField.h"


@class TITokenTableViewController;

@protocol TITokenTableViewDataSource <NSObject>
@required



/**
* Provide a list of token filed prompt texts: "To:" "Cc:" ..
*/
-(NSString *)tokenFieldPromptAtRow:(NSUInteger) row;
-(NSUInteger) numberOfTokenRows;


/**
* E.g. a browse address book button.
*/
-(UIView *) accessoryViewForField:(TITokenField*) tokenField;


/**
* Other cells that ore not TITokenFields
**/

- (UITableViewCell *)tokenTableView:(TITokenTableViewController *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;

- (NSInteger)tokenTableView:(TITokenTableViewController *)tableView numberOfRowsInSection:(NSInteger)section;

- (CGFloat)tokenTableView:(TITokenTableViewController *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;


@end




@protocol TITokenTableViewControllerDelegate <NSObject>

@optional
/**
* Called when a token field is selected
*/
-(void)tokenTableViewController:(TITokenTableViewController *)tokenTableViewController didSelectTokenField:(TITokenField*)tokenField;

-(void)tokenTableViewController:(TITokenTableViewController *)tokenTableViewController tokenFieldFrameWillChange:(TITokenField*)tokenField;
-(void)tokenTableViewController:(TITokenTableViewController *)tokenTableViewController tokenFieldFrameDidChange:(TITokenField*)tokenField;

/**
* Called when a cell that is NOT a TIToken cell is selected
*/
- (void)tokenTableViewController:(TITokenTableViewController *)tableView didSelectRowAtIndex:(NSInteger)row;

/**
 * Called when a token field has been set up by the table view controller during
 * initialisation. Useful to further customize the tokenfield further if needed,
 * such as setting a tintColor for all tokens created, etc.
 */
- (void)tokenTableViewController:(TITokenTableViewController *)tableView
	didFinishSettingUpTokenField:(TITokenField *)tokenField;

/**
 * Called when search results will become visible or will be hidden
 */
- (void)tokenTableViewController:(TITokenTableViewController *)tableView searchResultsVisible:(BOOL)visible forTokenField:(TITokenField *)tokenField;

@end


#pragma mark - TITokenTableView

@protocol TITokenTableViewDelegate <UITableViewDelegate>
@optional
- (void)tableViewDidFinishReloading:(UITableView *)tableView;
@end

@interface TITokenTableView : UITableView
@property (nonatomic, assign) id<TITokenTableViewDelegate> delegate;
@property (nonatomic, getter = isReloading) BOOL reloading;
@end


#pragma mark - TITokenTableViewController

@interface TITokenTableViewController : UIViewController <UITableViewDataSource, TITokenTableViewDelegate, TITokenFieldDelegate> {
    NSMutableArray *resultsArray;
    UITableView *resultsTable;
    UIPopoverController *popoverController;

    CGFloat _keyboardHeight;
    BOOL _searchResultIsVisible;
    CGPoint _contentOffsetBeforeResultTable;
}

@property (nonatomic, strong) TITokenTableView *tableView;

@property (nonatomic, readonly) UITableView *resultsTable;

// Default: YES
@property (nonatomic) BOOL tokenFieldsEditable;

// Sets up the all the token fields
@property (nonatomic, strong) NSCharacterSet *tokenizingCharacters;
@property (nonatomic, strong) UIFont *tokenFieldFont;

@property (nonatomic, weak) TITokenField *currentSelectedTokenField;

@property (nonatomic, assign) BOOL showAlreadyTokenized;
@property (nonatomic, copy) NSArray *sourceArray;

@property (nonatomic, weak) id<TITokenTableViewDataSource> tokenDataSource;
@property (nonatomic, weak) id<TITokenTableViewControllerDelegate> delegate;

- (void)updateContentSize;

// Use this to obtain the token field for the prompt
- (TITokenField *)tokenFieldForPrompt:(NSString *)prompt;

@end
