//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/	 	/*Update Interval*/	/*Update Signal*/
   
	{"", "volume",			2,		            10},

	{"", "clock",			  5,		            0},
	{ "" ,"battery" ,   5,                0},
	{ "", "memory" ,    5,                0},
	{ "", "disk",       3000,             0},
	{ "","wifi" ,       60,               0},
	{ "","internet",    10,               0},
	{"","nettraf",      2,                0}
	
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = '|';
