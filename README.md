##Testfile Maker

Welcome, this is a tool for making test files.  They will be filled with the numbers 0-9 repeating.

###To Run:
	make
	./testfile_maker [options]

###Options:
#####	[file name] [-c val] [-e [extension name]] [-h] [-l] [-s val[k|m|g]]

	filename:	Default: test

	-c		The count of the files to be created.
			Default: 1

	-e		The extension of the files that will be created.
			Default: No extension

	-l		Writes each character out to a new line.  To maintain size only half the
			number of characters are written out because of the newline character.

	-s		The size of each file measured in bytes. Adding a trailing 'k', 'm', or 'g'
			will convert the value into kilobytes, megabytes, or gigabytes respectively.
			Default: 10
