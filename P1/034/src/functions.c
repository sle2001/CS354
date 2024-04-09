/******************************************************************************
 * @file: functions.c
 *
 * WISC NETID
 * CANVAS USERNAME
 * WISC ID NUMBER
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: YOUR PREFERED NAME (YOUR WISC EMAIL)
 * @modified: SUBMISSION DATE
 *****************************************************************************/
#include <stdio.h>
#include "functions.h"

// Some macros that may be useful to you 
#define MAX_USERNAME_LEN    32
#define MAX_EMAIL_LEN       32
#define MAX_DOMAIN_LEN      64
#define MIN_PASSWORD_LEN    8
#define MAX_PASSWORD_LEN    16
#define NEW_LINE_CHAR       10

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 
// Examples: IsLetter, IsDigit, Length, Find...

/*
 * This helper method checks if the first array element of the username is a letter or not.
 * 
 * Returns 1 if true, 0 if false
 */
int isFirstLetter(char firstLetter) {
	// Checks if the first character in the array is a letter
	if((firstLetter >= 'a' && firstLetter <= 'z') || (firstLetter >= 'A' && firstLetter <= 'Z')) {
		return 1; // First character is a letter
	}
	
	return 0; // First character isn't a letter
}

/*
 * This helper method checks if all of the characters are letters, underscore, or digits
 *
 * Return 1 if true, return 0 is false
 */
int findBadChar(char user) {
	if((user >= 'a' && user <= 'z') || (user >= 'A' && user <= 'Z') || (user >= '0' && user <= '9') || (user == '_')) {
		return 1;  /// Username contains only letters, underscores, and digits
	}
		
	return 0; // Contains a nonletter, nondigit, and not an underscore

}

/*
 * This helper method checks if there is a name in the email
 *
 * Returns 1 if true, return 0 if false
 */
int noName(char name) {
	if(name == '@') {
		return 0; // Contains no name
	}
	return 1; // Contains name
}

/*
 * This helper method checks if the email name only contains letters and digits
 *
 * Returns 1 if true, returns 0 if false
 */
int emailNameChar(char email) {
	if((email >= 'a' && email <= 'z') || (email >= 'A' && email <= 'Z') || (email >= '0' && email <= '9')) {
		return 1; // Contains a letter or a digit
	}
	return 0; // Contains a nonletter or a nondigit
}

/* Helper method to get the length of the name that was given
 *
 * Returns length if it's not null, returns 0 it is
 */
int getLength(char character, int length) {
    // This adds the length
    if(character != '\0') {
    	length++;
	return length;
    }

    return 0;
}

/* Helper method to check if there are any invalid characters in the domain of an email
 *
 * Returns 1 if true, returns 0 if false
 */
int checkDomain(char email) {
	if((email >= 'a' && email <= 'z') || (email >= 'A' && email <= 'Z') || (email >= '0' && email <= '9') || email == '.') {
		return 1; // Valid characters
	}
	return 0; // Contains an invalid character

}
/******************************************************************************
 * Verification functions
 *****************************************************************************/

/*
 * A username must begin with a letter [A-Z, a-z], contain 32 characters
 * or less, and  may only consist of letters, underscores, or 
 * digits [A-Z, a-z, _, 0-9]. An error message is displayed if any of 
 * these conditions are not met. Only print the first applicable error 
 * message. 
 *
 * @param user : The username string
 * @param len : Size of the username input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Username(char user[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    dbgprintf("This line only prints if DEBUG is set to 1\n");

    // This changes the new line that sometimes pop up into null
    int firstLetter = isFirstLetter(user[0]); // Calls helper method to see if first letter is an actual letter
    // It will return an error if firstLetter is 0, meaning it's a nonletter
    if(firstLetter == 0) {
    	printf(ERROR_01_USER_START_INVALID);
   	return 0;
    }

    // Gets the length of the user
    int userLength = 0;
    int j = 0;
    while(getLength(user[j], userLength) != 0) {
	    userLength = getLength(user[j], userLength);
	    j++;
    }

    // If the userlength is bigger than 32, it prints out an error
    if(userLength > 32) {
    	printf(ERROR_02_USER_LEN_INVALID);
    	return 0;
    }

    // Gets all the characters in the username and check it one by one to see if it's a letter, digit, underscore, or none of those
    for(int i = 0; i < userLength; i++) {
    	int badChar = findBadChar(user[i]); // Calls helper method to see what character it is

	// If it's not a letter, digit, or underscore then it will printout the error messasge
   	if(badChar == 0) {
		printf(ERROR_03_USER_CHARS_INVALID);
    		return 0;
	}
    }
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_1_USER);
    return 1;
}

/*
 * An email address has four parts:
 *      name
 *          exists
 *          must start with letter
 *          must be 32 characters or less (inclusive on 32)
 *          may contain only letters and digits
 *      @ symbol
 *          exists
 *      domain name
 *          exists
 *          max of 64 characters
 *          composed of one or more subdomains separated by .
 *          subdomain must begin with a letter
 *          subdomains may contain only letters and digits
 *      top-level domain 
 *          must be [.edu, .com, .net]
 *
 * If the email address contains one or more errors print only the first
 * applicable error from the list.
 *
 * Note this task is based on a real world problem and may not be the best 
 * order to approach writing the code.
 *
 * @param email : The email string
 * @param len : Size of the email input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Email(char email[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */

	// This changes the new line that sometimes pop up into null
	int name = noName(email[0]); // Calls helper method to see if there is a name in the email
	// Will throw error messasge if there is no name in email
	if (name == 0) {	
    		printf(ERROR_04_EMAIL_MISSING_NAME);  // example @domain.com
		return 0;
	}

	int firstLetter = isFirstLetter(email[0]); // Calls helper method to see if there is a letter as the first character
	// Will throw error message if the first character of email is not a letter
	if (firstLetter == 0) {
		printf(ERROR_05_EMAIL_START_INVALID);
		return 0;
	}

	// This gets the length of the email
	int emailLength = 0;
	int j = 0;
	int at_pointer = 0; // The pointer for @
	while(getLength(email[j],emailLength) != 0) {;
		emailLength = getLength(email[j],emailLength);
		j++;
		if(email[j] == '@') {
			at_pointer = j;
		}
	}

	// This gets the length of the email name
	int emailNameLength;
	if(at_pointer != 0) {
		emailNameLength = at_pointer - 1;
	}
	else {
		emailNameLength = emailLength;
	}

	// This checks if the email length is 32 or less
	if(emailNameLength > MAX_EMAIL_LEN) {
		printf(ERROR_06_EMAIL_NAME_LEN_INVALID);
		return 0;
	}

	// Top domain is always the last 4 characters, so the start of top domain is the 4th digit starting from the end.
	int topDomainPeriod = 0;
	if(email[emailLength - 4] == '.') {
		topDomainPeriod = emailLength - 4;
	}
	
	// Checks if there is a @ symbol
	if (at_pointer == 0){
		// If there isn't, we check if there is a top-level domain
		if (topDomainPeriod != 0) {
			// Check the name to see if there is any invalid characters
    			for (int i = 0;i < topDomainPeriod; ++i){
        			if(emailNameChar(email[i])==0){
            				printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
            				return 0;
        			}
   		 	}
		}
		else {
			// Check the name to see if there are any invalid characters
			for (int i = 0; i < emailLength; ++i) {		
				if(emailNameChar(email[i]) == 0) {
					printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
					return 0;
				}
			}
		}
	}
	else {
		// Check the name to see if there is any invalid characters
    		for (int i = 0; i < at_pointer; ++i) {
        		if (emailNameChar(email[i]) == 0) {
            			printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
            			return 0;
        		}
    		}
	}	
	

	// Checks if there is an @ symbol
	if(at_pointer == 0)  {
		printf(ERROR_08_EMAIL_MISSING_SYMBOL);
		return 0;
	}

	// Check if there is a domain
	if(email[at_pointer + 1] == '.' || at_pointer == emailLength - 1) { 
		printf(ERROR_09_EMAIL_MISSING_DOMAIN);
		return 0;
	}

	// Check if the length of the domain is less than 64
	int domainLength = topDomainPeriod - at_pointer - 1; // I added the -1 because at_pointer is not the first char of the domain
	if(domainLength > MAX_DOMAIN_LEN) {
		printf(ERROR_10_EMAIL_DOMAIN_LEN_INVALID);
		return 0;
	}

	// Check if the domain or subdomains start with letters
	if(isFirstLetter(email[at_pointer+1]) == 0) {
		printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
		return 0;
	}
	else {
		for(int i = at_pointer + 1; i < topDomainPeriod; ++i) {
			if(email[i] == '.' && isFirstLetter(email[i+1]) == 0) {
				printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
				return 0;
			}
		}
	}
	
	// Checks if there are any invalid characters in the domain
	for(int i = at_pointer + 1; i < topDomainPeriod; ++i) {
		if(checkDomain(email[i]) == 0) {
			printf(ERROR_12_EMAIL_DOMAIN_CHARS_INVALID);
			return 0;
		}
	}

	// Check if the top level domain is correct
	if(email[topDomainPeriod + 1] != 'e' || email[topDomainPeriod + 2] != 'd' || email[topDomainPeriod + 3] != 'u') {
		if(email[topDomainPeriod + 1] != 'c' || email[topDomainPeriod + 2] != 'o' || email[topDomainPeriod + 3] != 'm') {
			if(email[topDomainPeriod + 1] != 'n' || email[topDomainPeriod + 2] != 'e' || email[topDomainPeriod + 3] != 't') {
				printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
				return 0;
			}
		}
	}
    /* END MODIFYING CODE HERE */
    
    printf(SUCCESS_2_EMAIL);
    return 1;
}

/*
 * The following password requirements must be verified:
 *  - May use any character except spaces (i.e., "my password" is invalid)
 *  - Must contain at least 8 characters (i.e., "Password" has 8 characters 
 *    and is valid)
 *  - May have at most 16 characters (i.e., "1234567890Abcdef" has 16 
 *    characters and is valid)
 *  - Must contain at least one upper case character [A-Z]
 *  - Must contain at least one lower case character [a-z]
 *
 * @param pwd : The original password string
 * @param len : Size of the original password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Password(char pwd[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
	// Get the length of password
	int pwdLength = 0;
	int j = 0;
	while(getLength(pwd[j],pwdLength) != 0) {
		pwdLength++;
		j++;
	}

	// Check if there are any spaces in password
	for(int i = 0; i < pwdLength; ++i) {
		if(pwd[i] == ' ') {
			printf(ERROR_14_PWD_SPACES_INVALID);
			return 0;
		}
	}
    
	// Check if the password has at least 8 and at most 16 characters
	if(pwdLength < MIN_PASSWORD_LEN) {
		printf(ERROR_15_PWD_MIN_LEN_INVALID);
		return 0;
	}
	if(pwdLength > MAX_PASSWORD_LEN) {
    		printf(ERROR_16_PWD_MAX_LEN_INVALID);
		return 0;
	}

	// Check if there is at least one uppercase letter and one lowercase letter
	int numLowercase = 0;
	int numUppercase = 0;
	// This gets the number of lowercase letters and uppercase letters
	for(int i = 0; i < pwdLength; ++i) {
		if(pwd[i] >= 'a' && pwd[i] <= 'z') {
			numLowercase++;
		}
		if(pwd[i] >= 'A' && pwd[i] <= 'Z') {
			numUppercase++;
		}
	}

	if(numUppercase == 0) {
    		printf(ERROR_17_PWD_MIN_UPPER_INVALID);
		return 0;
	}
	else if(numLowercase == 0) {
    		printf(ERROR_18_PWD_MIN_LOWER_INVALID);
		return 0;
	}
    /* END MODIFYING CODE HERE */

    return 1;
}
/*
 * Original Password and the Reentered Password must match
 *
 * @param pwd1 : The original password string
 * @param len1 : Size of the original password input buffer
 * @param pwd2 : The reentered password string
 * @param len2 : Size of the renetered password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Passwords_Match(char pwd1[], size_t len1, char pwd2[], size_t len2) {

    /* BEGIN MODIFYING CODE HERE */
	int pwd1_length = 0;
	int pwd2_length = 0;
	int j = 0;
	// This gets the length of pwd1
	while(getLength(pwd1[j],pwd1_length) != 0) {
		pwd1_length++;
		j++;
	}

	j = 0;
	// This gets the length of pwd2
        while(getLength(pwd2[j],pwd2_length) != 0) {
 		pwd2_length++;
                j++;
        }

	// Check if the length is correct
	if(pwd1_length != pwd2_length) {
		printf(ERROR_19_PWD_MATCH_INVALID);
		return 0;
	}
	else {
		// This verifies if the password and reentered password match
		for(int i = 0; i < pwd1_length; ++i) {
			if(pwd1[i] != pwd2[i]) {
				("MATCHING CHARS IS WRONG");
    				printf(ERROR_19_PWD_MATCH_INVALID);
				return 0;
			}
		}
	}
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_3_PASSWORDS);
    return 1;
}

/******************************************************************************
 * I/O functions
 *****************************************************************************/

/*
 * Prompts user with an input and reads response from stdin
 *
 * @param message : Prompt displayed to the user
 * @param data : char array to hold user repsonse
 * @param MAX_LENGTH : Size of user response input buffer
 */
void Get_User_Data(char *message, char *data, const int MAX_LENGTH) {
    printf("%s", message);
    fgets(data, MAX_LENGTH, stdin);
    /* BEGIN MODIFYING CODE HERE */
    // Change all the new lines to nulls
    for(int i = 0; i < MAX_LENGTH; ++i) {
	    if(data[i] == '\n') {
		    data[i] = '\0';
	    }
    }
    /* END MODIFYING CODE HERE */
    return;
}
