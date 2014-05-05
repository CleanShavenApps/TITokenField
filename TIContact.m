//
//  TITokenContact.m
//  TokenFieldExample
//
//  Created by Lin Junjie on 13/11/12.
//
//

#import "TIContact.h"

@implementation TIContact

+ (id)contactWithName:(NSString *)name
				email:(NSString *)email
				label:(NSString *)label
{
	TIContact *contact =
	[[TIContact alloc] initWithName:name email:email label:label];
	
	return contact;
}

- (id)init
{
	return [self initWithName:@"" email:@"" label:@""];
}

- (id)initWithName:(NSString *)name
			 email:(NSString *)email
			 label:(NSString *)label
{
	self = [super init];
	
	if (self)
	{
		_fullName = [name copy];
		_email = [email copy];
		_emailLabel = [label copy];		
	}
	
	return self;
}

- (NSString *)description
{
	return [NSString stringWithFormat:@"TITokenContact: %@ (email: %@, %@ / phone: %@, %@)",
			self.fullName, self.email, self.emailLabel, self.phone, self.phoneLabel];
}

#pragma mark - 

- (NSString *)phoneLabel
{
	if (!_phoneLabel)
	{
		_phoneLabel = [TICONTACT_DEFAULT_LABEL copy];
	}
	
	return _phoneLabel;
}

- (NSString *)emailLabel
{
	if (!_emailLabel)
	{
		_emailLabel = [TICONTACT_DEFAULT_LABEL copy];
	}
	
	return _emailLabel;
}

#pragma mark - Equality Check

- (BOOL)isEqualToContact:(TIContact *)contact
{
	if (self == contact)
	{
		return YES;
	}
	
	if (![contact isKindOfClass:[self class]])
	{
		return NO;
	}
	
	if (![self ti_string:self.fullName isEqual:contact.fullName])
	{
		return NO;
	}
	
	if (![self ti_string:self.email isEqual:contact.email])
	{
		return NO;
	}

	if (![self ti_string:self.emailLabel isEqual:contact.emailLabel])
	{
		return NO;
	}

	if (![self ti_string:self.phone isEqual:contact.phone])
	{
		return NO;
	}

	if (![self ti_string:self.phoneLabel isEqual:contact.phoneLabel])
	{
		return NO;
	}

	if (self.score != contact.score)
	{
		return NO;
	}
	
	return YES;
}

- (BOOL)isEqual:(id)object
{
	return [self isEqualToContact:object];
}

- (NSUInteger)hash
{
	return [self.fullName hash]
	^ [self.email hash]
	^ [self.emailLabel hash]
	^ [self.phone hash]
	^ [self.phoneLabel hash]
	^ [@(self.score) hash];
}

- (BOOL)ti_string:(NSString *)stringA isEqual:(NSString *)stringB
{
	return (!stringA && !stringB) || [stringA isEqualToString:stringB];
}

@end
