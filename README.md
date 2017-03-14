## Testfile Maker

### About
    This tool was developed to help with software testing. There were two original requirements, the first was to quickly generate ten thousand plus files and the second was to generate a file of one gigabyte in size. How to Break Software by James A. Whittaker inspired the zero to nine repeating pattern so that any changes made to a file are easily recognizable.

### To Run:
	make
	./testfile_maker [options]

### Options:
##### [file name] [-c val] [-d dir] [-e [extension name]] [-h] [-l] [-s val[k|m|g]] [-v [val]]

	filename:	Default: test

	-c		The count of the files to be made.
			Default: 1

    -d      The directory where the files should be made.
            Default: Current working directory

	-e		The extension of the files that will be made.
			Default: No extension

	-l		Writes each character out to a new line.  To maintain size only half the
			number of characters are written out because of the newline character.

	-s		The size of each file measured in bytes. Adding a trailing 'k', 'm', or 'g'
			will convert the value into kilobytes, megabytes, or gigabytes respectively.
			Default: 10

    -v      Turns on output for completion of different tasks.
            Level 1 - The following text is output when all files have been made, "Complete: <file count> files made"
            Level 2 - The completion message is output along with the following for each file made, "Made: <file name>"
            Default: No Output
