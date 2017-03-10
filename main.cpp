// -*- mode: C++; tab-width: 4; -*-
// vi:ts=4 noexpandtab autoindent

/*
 * Matthew Birky
 * 10/22/2014
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <string>
#include <sstream>
using namespace std;

const char *gProgname = "<unknown program>";

/*
* convert a string to any compatible value
*/
template<typename T>
T ValOf(string s)
{
	stringstream	 os;
	T	 val;

	os << s;
	os >> val;

	return val;
}

/*
 * Thank you mwittenberg for the code
 * return the filename (strip off the preceding path, if any)
 */
const char *
GetProgname(const char *argp)
{
	const char	*p = strrchr(argp, '/');

	return p ? p+1 : argp;
}

/*
 * Show usage synopsis
 */
void usage()
{
	cout << gProgname << " [file name] [-c val] [-d dir] [-e [extension name]] [-h] [-l] [-s val[k|m|g]] [-v [val]]" << endl;
}

/*
 * Show optional error message (if desired)
 * before showing usage synopsis
 */
void help(const char ch = '\0')
{
	if(ch)
		cout << gProgname << ": " << "Unknown option '" << ch << "'" << endl;
	usage();

	exit(1);
}

/*
 * Show arbitrary messag (if desired)
 * before showing usage synopsis
 */
void help(const char *cp)
{
	if(cp)
		cout << gProgname << ": " << cp << endl;
	usage();

	exit(1);
}

void SanatizeFileDirectory(string & fileDirectory)
{
    // There may be an issues if the string is less than 3 characters
    if(fileDirectory.compare(fileDirectory.length() -3, 3, "...") == 0) {
        fileDirectory.erase(fileDirectory.end() -3, fileDirectory.end());
    } 

    // The file directory must end with a / or it will be part of the name
    if(fileDirectory.compare(fileDirectory.length() -1, 1, "/")) {
        fileDirectory.push_back('/');
    }
}

int main(int argc, const char * argv[]) {
    int verbose = 0;
	unsigned int fileCount	= 1;
	unsigned long long fileSize	= 10;	//bytes
	const char * fileName	= "test";
    string fileDirectory;
	string fileExtension;

	int const fillArraySize = 20;
	char nolineFillArray[fillArraySize] = {'0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9'};
	char lineFillarray[fillArraySize] = {'0','\n','1','\n','2','\n','3','\n','4','\n','5','\n','6','\n','7','\n','8','\n','9','\n'};
	char * fillArray = nolineFillArray;

	gProgname = GetProgname(*argv);

	while(--argc > 0)	{
		const char *arg = *++argv;

		if(*arg == '-')	{
			while(*++arg)	{
				switch(*arg)	{
				case 'c':
					if( (argc > 1) && isdigit(*argv[1]) ) {
						argc--;
						fileCount = ValOf<unsigned int>(*++argv);
					}
					else {
						help("-c requires a number");
					}
					break;
                case 'd':
                    if(argc > 1)    {
                        argc--;
                        fileDirectory = *++argv;
                        SanatizeFileDirectory(fileDirectory);
                    }
                    break;
				case 'e':
					if(argc > 1)	{
						argc--;
						fileExtension = *++argv;
					}
					else {
						fileExtension = ".txt";
					}
					break;
				case 'h':
					help();
					break;
				case 'l':
					fillArray = lineFillarray;
					break;
				case 's':
					if( (argc > 1) && isdigit(*argv[1]) )	{
						argc--;
						string arg_string = *++argv;
						fileSize = ValOf<unsigned int>(arg_string);
						unsigned int arg_length = arg_string.length();

						switch(arg_string[arg_length - 1])	{
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
							break;
						case 'k':
						case 'K':
							fileSize *= 1024;
							break;
						case 'm':
						case 'M':
							fileSize *= 1024 * 1024;
							break;
						case 'g':
						case 'G':
							fileSize *= 1024 * 1024 * 1024;
							break;
						default:
							help(*arg);
							break;
						}
					}
					else {
						help("-s requires a number");
					}
					break;
                case 'v':
                    if(argc >1) {
                        if(isdigit(*argv[1])) {
                            argc--;
                            verbose = ValOf<int>(*++argv);
                        }
                        else {
                            help("-v requires a number");
                        }
                    }
                    else {
                        verbose = 1;
                    }
                    break;
				default:
					help(*arg);
					break;
				}
			}
		}
		else {
			fileName = arg;
		}
	}

	// Making an output array of 50 times the fill array size
	// This array is then used to reduce the number of write calls needed
	int const outputArraySize = fillArraySize * 50;
	char outputArray[outputArraySize] = {0};
	for(int numMemCpys(0); numMemCpys < (outputArraySize / fillArraySize); ++numMemCpys) {
		memcpy(outputArray + (numMemCpys * fillArraySize), fillArray, fillArraySize);
	}

	// Create number of files as called for
	for(int fileNum(0); fileNum < fileCount; fileNum++) {
		stringstream outputFileName;
		outputFileName << fileDirectory <<  fileName;

		if(fileCount != 1) {
			outputFileName << fileNum;
		}
		/*
		* Tack on the extension only if the user provided an extension,
		* but first interpose a period unless the user-providided extension
		* begins with a period.
		*/
		if( fileExtension.length() ) {
				if( fileExtension[0]!= '.' )
						outputFileName << ".";
				outputFileName << fileExtension;
		}

		std::ofstream outputfile;
		outputfile.open(outputFileName.str().c_str());
		unsigned long long outputSize=fileSize;
		while(outputSize > outputArraySize) {
			outputSize -= outputArraySize;
			outputfile.write(outputArray, outputArraySize);
		}
		outputfile.write(outputArray, outputSize);
		outputfile.close();

        if(verbose > 1) {
            cout << "Made: " << outputFileName.str() << endl;
        }
	}

    if(verbose > 0) {
        cout << "Complete: " << fileCount << " files made" << endl;
    }

	return 0;
}
