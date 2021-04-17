//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	// {"Mem:", "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	30,		0},
	// {"",  "battery",                            5,    0},
	// {"", "date '+%b %d (%a) %I:%M%p'",					5,		0},
	{"", "volume",			2,		            10},

	{"", "clock",			  5,		            0},
	{ "" ,"battery" ,   5,                0},
	// { "", "memory" ,    5,                0},
	// { "", "disk",       3000,             0},
	{ "","wifi" ,       60,               0},
	// { "","internet",    10,               0},
	// {"","nettraf",      2,                0}
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
