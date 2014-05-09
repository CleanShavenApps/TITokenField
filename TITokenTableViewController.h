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

/**
 Called when loading cell for representedObject in search results of tokenField.
 */
- (BOOL)tokenTableViewController:(TITokenTableViewController *)controller shouldShowDetailAccessoryViewForRepresentedObject:(id)representedObject forTokenField:(TITokenField *)tokenField;

/**
 Called when user taps on the detail accessory view of a search result belonging to tokenField
 */
- (void)tokenTableViewController:(TITokenTableViewController *)controller tableView:(UITableView *)tableView wantsToShowDetailsOfRepresentedObject:(id)representedObject atIndexPath:(NSIndexPath *)indexPath forTokenField:(TITokenField *)tokenField;

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

/**
 Subclasses to override to search for \c searchString for insertion into
 \c tokenField. Upon completion, call completion block with the results
 so that the view controller can display the search table view
 */
- (void)searchForString:(NSString *)searchString
		  forTokenField:(TITokenField *)tokenField
			 completion:(void (^)(NSArray *results))completion;

/**
 Removes the object from the search results array. Use to manually remove an
 object and update the table view structure. Returns the index of the object
 if successfully removed. Otherwise, returns \c NSNotFound
 */
- (NSUInteger)removeFromSearchResultsSourceObject:(id)object;

/**
 Clears the search result array and reloads the results based on the text found
 in the current selected token field
 */
- (void)clearAndReloadSearchResults;

// Use this to obtain the token field for the prompt
- (TITokenField *)tokenFieldForPrompt:(NSString *)prompt;

@end
