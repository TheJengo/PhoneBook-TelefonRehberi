/* Phone Book */

This is a simple Phone book programme. It consumes 6 main section and Exit on it's menu.

/* Menu */

1. Add Contact
2. List Contacts
3. Update Contact
4. Find Contact with Number
5. Find Contact with Name
6. Delete Contact 
0. Exit

Build a phone book programme for this menu needs.
/* Tips For X digit(s) Phone Numbers */

You guys just got to look at checkContact function in the code and you'll get it.
You just need to change the "If conditions" for your prefers. Code Line : 367 & 374

/* Tips For File Proccesses */

You have 2 ways to make this programme work on file proccesses.
First Route:
	use fprintf and fscanf and make your file readable for a humanbeing.

Second Route:
	use fread-fseek-fwrite and make your programe faster and easier than first route but do not try to get understand whats going on in file.
        Because when u use those three functions they have a different work style with some symbols. But dont worry they'll work.

Third Route: Mix it all :D

/* Tips For Restrictions */

When your phone book full, you can set restrictions for other menu options as like as add contact section.
You can easily enlarge or shrink your phone book capacity with MAX variable.
	For Example:
	int MAX = 100; // Default Value
	int MAX = 200; // New value