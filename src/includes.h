




/*
	File created by Chris Johnson.
	These were previously all in game.cpp.

	This file includes all the the enums, defines, and included headers required globally by all components.

	All code released under GNU GPL.
*/
#ifndef INCLUDES_H_INCLUDED
#define INCLUDES_H_INCLUDED0
constexpr auto __USE_MINGW_ANSI_STDIO = 0;
#include <windows.h>
#include <io.h> //needed for unlink()
#include <direct.h>
#include <ciso646> // alternate keywords included in the ISO C++ standard
// but not directly supported by Microsoft Visual Studio C++
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <time.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>
#include <deque>
#include <queue>
#include <math.h>
#include <cstring>
#include "cmarkup/Markup.h" //For XML.
#include <locale.h>

#include <mbctype.h>

#include "sdl/SDL.h"
#include "sdl/SDL_mixer.h"

#include <string.h>

using namespace std;


const int BIT1 = (1 << 0);
const int BIT2 = (1 << 1);
const int BIT3 = (1 << 2);
const int BIT4 = (1 << 3);
const int BIT5 = (1 << 4);
const int BIT6 = (1 << 5);
const int BIT7 = (1 << 6);
const int BIT8 = (1 << 7);
const int BIT9 = (1 << 8);
const int BIT10 = (1 << 9);
const int BIT11 = (1 << 10);
const int BIT12 = (1 << 11);
const int BIT13 = (1 << 12);
const int BIT14 = (1 << 13);
const int BIT15 = (1 << 14);
const int BIT16 = (1 << 15);
const int BIT17 = (1 << 16);
const int BIT18 = (1 << 17);
const int BIT19 = (1 << 18);
const int BIT20 = (1 << 19);
const int BIT21 = (1 << 20);
const int BIT22 = (1 << 21);
const int BIT23 = (1 << 22);
const int BIT24 = (1 << 23);
const int BIT25 = (1 << 24);
const int BIT26 = (1 << 25);
const int BIT27 = (1 << 26);
const int BIT28 = (1 << 27);
const int BIT29 = (1 << 28);
const int BIT30 = (1 << 29);
const int BIT31 = (1 << 30);
const int BIT32 = (1 << 31);
const int MAX_PATH_SIZE = 2048;
const int RNG_SIZE = 4;
/* These 6 random number generator functions are implemented in compat.cpp */
unsigned long getSeed();
unsigned long r_num();
long LCSrandom(long max);
void initMainRNG();
void copyRNG(unsigned long(&dest)[RNG_SIZE], unsigned long(&src)[RNG_SIZE]);
void initOtherRNG(unsigned long(&rng)[RNG_SIZE]);
/* Determine size of vectors and any other container that implements the size() function.
This basically includes all types of containers except for the C++11 std::forward_list. */
template <class Container> inline long len(const Container& x)
{
	return x.size();
}
/* Determine array size in pickrandom() and various functions throughout the code.
Only works on actual arrays, not on vectors or other containers. */
template <typename T, size_t N> inline long len(const T(&x)[N])
{
	return N;
}
/* Override of the prior function for null-terminated C-strings as char arrays.
This override allows pickrandom() to pick a random character from a C-string we have as a char array. */
template <size_t N> inline long len(const char(&x)[N])
{
	return strlen(x);
}
/* Override of the prior function for null-terminated C-strings as char pointers.
This override allows pickrandom() to pick a random character from a C-string we have as a char pointer. */
inline long len(const char* x)
{
	return strlen(x);
}
/* Override for when it doesn't work with const in front of the char*
(compilers are weird about template function overrides) */
inline long len(char* x)
{
	return strlen(x);
}
/* Pick a random element from a vector/deque/map/std::string/C++11 std::array/etc. (e.g. a random string from a vector of strings).
It works on any container class that implements the [] operator, size() function, and value_type typename.
This doesn't work if the vector/deque/map/std::string/C++11 std::array/etc. has zero elements. */
template <class Container> inline typename Container::value_type& pickrandom(const Container& x)
{
	return const_cast<typename Container::value_type&>(x[LCSrandom(len(x))]);
}
/* Pick a random element from an array (e.g. a random string from an array of strings).
This doesn't work if the array has zero elements. */
template <typename T, size_t N> inline T& pickrandom(const T(&x)[N])
{
	return const_cast<T&>(x[LCSrandom(len(x))]);
}
/* Pick a random element from a C-string.
Returns '\x0' (null character) for empty string. */
inline char& pickrandom(const char* x)
{
	return const_cast<char&>(x[LCSrandom(len(x))]);
}
/* Override for when it doesn't work with const in front of the char*
(compilers are weird about template function overrides) */
inline char& pickrandom(char* x)
{
	return x[LCSrandom(len(x))];
}
/* Deletes a specified pointer and sets it to NULL. */
template <typename T> inline void delete_and_nullify(T* &o)
{
	delete o;
	o = NULL;
}
/* Deletes and removes a specified pointer from a container. */
template <class Container> inline void delete_and_remove(Container& c, int i)
{
	if (i <= -1) return; // check for invalid index, and don't delete anything in this case
	delete c[i];
	c.erase(c.begin() + i);
}
/* Deletes and removes a specified pointer from 2 containers it's in.
c1 and c2 must not be the same container! */
template <class Container> inline void delete_and_remove(Container& c1, int i1, Container& c2, int i2)
{
	if (i1 <= -1 || i2 <= -1) return; // check for invalid index, and don't delete anything in this case
	if (c1[i1] == c2[i2])
	{ // it's the same pointer, so just delete it once, then remove it from both containers
		delete_and_remove(c1, i1);
		if (c1 != c2 || i1 != i2) c2.erase(c2.begin() + i2); // remove it from 2nd location, unless 2nd location is identical to 1st location
	}
	else
	{ // it's 2 different pointers, so delete them both and remove them from both containers
		delete_and_remove(c1, i1);
		delete_and_remove(c2, i2);
	}
}
/* Deletes and removes all pointers in a container. */
template <class Container> inline void delete_and_clear(Container& c)
{
	while (len(c))
	{
		delete c.back();
		c.pop_back();
	}
}
/* Deletes and removes all pointers that 2 containers have in common. */
template <class Container> inline void delete_and_clear(Container& c1, Container& c2)
{
	for (int i1 = len(c1) - 1; i1 >= 0; i1--)
		for (int i2 = len(c2) - 1; i2 >= 0; i2--)
			if (c1[i1] == c2[i2]) delete_and_remove(c1, i1, c2, i2);
}

enum LCSIO_FLAGS
{
	LCSIO_PRE_ART = 1, /// Append the given file name to the art directory path.
	LCSIO_PRE_HOME = 2 /// Append the given file name to the home directory path.
};
FILE* LCSOpenFile(const char* filename, const char* mode, int flags);
bool LCSOpenFileCPP(std::string filename, std::ios_base::openmode mode, int flags, std::fstream &file);
void LCSCloseFile(FILE* handle);
void LCSCloseFileCPP(std::fstream &file);
void LCSDeleteFile(const char* filename, int flags);
void LCSRenameFile(const char* old_filename, const char* new_filename, int flags);
//returns a list of all files in homedir with extension .dat
vector<string> LCSSaveFiles();

void pause_ms(int t);
void alarmset(int t);
void alarmwait();
#define CH_USE_CP437



#ifndef NDEBUG
#define NDEBUG
#endif


const int TAB = 9;
const int ENTER = 10;
const int ESC = 27;
const int SPACEBAR = 32;

class Log;

enum Alignment
{
	ALIGN_ARCHCONSERVATIVE = -2,
	ALIGN_CONSERVATIVE,
	ALIGN_MODERATE,
	ALIGN_LIBERAL,
	ALIGN_ELITELIBERAL,
	ALIGN_STALINIST
};

enum UnlockTypes
{
	UNLOCK_DOOR,
	UNLOCK_CAGE,
	UNLOCK_CAGE_HARD,
	UNLOCK_CELL,
	UNLOCK_SAFE,
	UNLOCK_ARMORY,
	UNLOCK_VAULT,
	UNLOCKNUM
};

enum HackTypes
{
	HACK_SUPERCOMPUTER,
	HACK_VAULT,
	HACKNUM
};

enum SpecialAttacks
{
	ATTACK_CANNON,
	ATTACK_FLAME,
	ATTACK_SUCK,
	ATTACKNUM
};

enum EndGameStatus
{
	ENDGAME_NONE,
	ENDGAME_CCS_APPEARANCE,
	ENDGAME_CCS_ATTACKS,
	ENDGAME_CCS_SIEGES,
	ENDGAME_CCS_DEFEATED,
	ENDGAME_MARTIALLAW,
	ENDGAMENUM
};

enum CCSexposure
{
	CCSEXPOSURE_NONE,
	CCSEXPOSURE_LCSGOTDATA,
	CCSEXPOSURE_EXPOSED,
	CCSEXPOSURE_NOBACKERS,
	CCSEXPOSURENUM
};

const int ARMORFLAG_DAMAGED = BIT1;
const int ARMORFLAG_BLOODY = BIT2;


/* *JDS* I'm making laws an array instead of a bunch
 * of bits which are either on or off. Each charge can be
 * duplicated, for multiple counts, and intense focus
 * for wanted persons.
 */
enum Lawflags
{
	LAWFLAG_TREASON,      // "Treason"
	LAWFLAG_TERRORISM,    // "Terrorism"
	LAWFLAG_MURDER,       // "Murder"
	LAWFLAG_KIDNAPPING,   // "Kidnapping"
	LAWFLAG_BANKROBBERY,  // "Bank robbery"
	LAWFLAG_ARSON,        // "Arson"
	LAWFLAG_BURNFLAG,     // "Flag burning" / "Flag Murder"
	LAWFLAG_SPEECH,       // "Harmful speech"
	LAWFLAG_BROWNIES,     // "Drug dealing"
	LAWFLAG_ESCAPED,      // "Escaping prison"
	LAWFLAG_HELPESCAPE,   // "Releasing prisoners"
	LAWFLAG_JURY,         // "Jury tampering"
	LAWFLAG_RACKETEERING, // "Racketeering"
	LAWFLAG_EXTORTION,    // "Extortion"
	LAWFLAG_ARMEDASSAULT, // "Armed assault"
	LAWFLAG_ASSAULT,      // "Assault"
	LAWFLAG_CARTHEFT,     // "Grand theft auto"
	LAWFLAG_CCFRAUD,      // "Credit card fraud"
	LAWFLAG_THEFT,        // "Theft"
	LAWFLAG_PROSTITUTION, // "Prostitution"
	LAWFLAG_HIREILLEGAL,  // "Hiring illegal aliens" / "Hiring undocumented workers"
	LAWFLAG_COMMERCE,     // "Electronic sabotage"
	LAWFLAG_INFORMATION,  // "Hacking"
	LAWFLAG_BURIAL,       // "Unlawful burial"
	LAWFLAG_BREAKING,     // "Breaking and entering"
	LAWFLAG_VANDALISM,    // "Vandalism"
	LAWFLAG_RESIST,       // "Resisting arrest"
	LAWFLAG_DISTURBANCE,  // "Disturbing the peace"
	LAWFLAG_PUBLICNUDITY, // "Public nudity"
	LAWFLAG_LOITERING,    // "Loitering"
	LAWFLAGNUM
};

/* *JDS* In addition to laws being an array,
 * each law will be associated with a tag_heat value,
 * indicating how much that particular crime draws
 * police attention to the wanted person, and to the
 * LCS as a whole. This is a global array, available
 * at runtime and indexed to the lawflag enum, so that
 * code can dynamically look up these heat values as
 * needed at runtime.
 */


enum AnimalGlosses
{
	ANIMALGLOSS_NONE,//IMPORTANT THAT THIS BE HERE AT ZERO
	ANIMALGLOSS_TANK,
	ANIMALGLOSS_ANIMAL,
	ANIMALGLOSSNUM
};

enum Activity
{
	ACTIVITY_NONE,
	ACTIVITY_VISIT,
	ACTIVITY_HOSTAGETENDING,
	ACTIVITY_TROUBLE,
	ACTIVITY_GRAFFITI,
	ACTIVITY_COMMUNITYSERVICE,
	ACTIVITY_SELL_ART,
	ACTIVITY_SELL_MUSIC,
	ACTIVITY_SELL_TSHIRTS,
	ACTIVITY_DONATIONS,
	ACTIVITY_SELL_DRUGS,
	ACTIVITY_PROSTITUTION,
	ACTIVITY_POLLS,
	ACTIVITY_CCFRAUD,
	ACTIVITY_DOS_RACKET,
	ACTIVITY_DOS_ATTACKS,
	ACTIVITY_HACKING,
	ACTIVITY_REPAIR_ARMOR,
	ACTIVITY_MAKE_ARMOR,
	ACTIVITY_STEALCARS,
	ACTIVITY_WHEELCHAIR,
	ACTIVITY_BURY,
	ACTIVITY_WRITE_BLOG,
	ACTIVITY_WRITE_LETTERS,
	ACTIVITY_WRITE_GUARDIAN,
	ACTIVITY_TEACH_POLITICS,
	ACTIVITY_TEACH_FIGHTING,
	ACTIVITY_TEACH_COVERT,
	ACTIVITY_STUDY_DEBATING,
	ACTIVITY_STUDY_MARTIAL_ARTS,
	ACTIVITY_STUDY_DRIVING,
	ACTIVITY_STUDY_PSYCHOLOGY,
	ACTIVITY_STUDY_FIRST_AID,
	ACTIVITY_STUDY_LAW,
	ACTIVITY_STUDY_DISGUISE,
	ACTIVITY_STUDY_SCIENCE,
	ACTIVITY_STUDY_BUSINESS,
	ACTIVITY_STUDY_GYMNASTICS,
	ACTIVITY_STUDY_MUSIC,
	ACTIVITY_STUDY_ART,
	ACTIVITY_STUDY_TEACHING,
	ACTIVITY_STUDY_WRITING,
	ACTIVITY_STUDY_LOCKSMITHING,
	ACTIVITY_STUDY_COMPUTERS,
	ACTIVITY_STUDY_FENCING,
	ACTIVITY_STUDY_WEAVING,
	ACTIVITY_STUDY_RELIGION,
	ACTIVITY_STUDY_CLUB,
	ACTIVITY_STUDY_STREETSENSE,
	ACTIVITY_STUDY_THROWING,
	ACTIVITY_STUDY_STEALTH,
	ACTIVITY_STUDY_SEDUCTION,
	ACTIVITY_CLINIC,
	ACTIVITY_HEAL,
	ACTIVITY_SLEEPER_LIBERAL,
	ACTIVITY_SLEEPER_CONSERVATIVE,
	ACTIVITY_SLEEPER_SPY,
	ACTIVITY_SLEEPER_RECRUIT,
	ACTIVITY_SLEEPER_SCANDAL,
	ACTIVITY_SLEEPER_EMBEZZLE,
	ACTIVITY_SLEEPER_STEAL,
	ACTIVITY_SLEEPER_JOINLCS,
	ACTIVITY_RECRUITING,
	ACTIVITY_AUGMENT,
	ACTIVITYNUM
};



enum CarChaseObstacles
{
	CARCHASE_OBSTACLE_FRUITSTAND,
	CARCHASE_OBSTACLE_TRUCKPULLSOUT,
	CARCHASE_OBSTACLE_CROSSTRAFFIC,
	CARCHASE_OBSTACLE_CHILD,
	CARCHASE_OBSTACLENUM
};

enum SquadStances
{
	SQUADSTANCE_ANONYMOUS,
	SQUADSTANCE_STANDARD,
	SQUADSTANCE_BATTLECOLORS,
	SQUADSTANCE_MAX
};

const int ENCMAX = 18;
// ENCMAX _HAS_ to be 26 or less, or else there aren't enough letters


enum GameModes
{
	GAMEMODE_TITLE,
	GAMEMODE_BASE,
	GAMEMODE_SITE,
	GAMEMODE_CHASECAR,
	GAMEMODE_CHASEFOOT
};

enum MusicModes
{
	MUSIC_TITLEMODE,
	MUSIC_NEWGAME,
	MUSIC_BASEMODE,
	MUSIC_SIEGE,
	MUSIC_ACTIVATE,
	MUSIC_SLEEPERS,
	MUSIC_STOPEVIL,
	MUSIC_REVIEWMODE,
	MUSIC_LIBERALAGENDA,
	MUSIC_DISBANDED,
	MUSIC_FINANCES,
	MUSIC_CARTHEFT,
	MUSIC_ELECTIONS,
	MUSIC_SHOPPING,
	MUSIC_SITEMODE,
	MUSIC_SUSPICIOUS,
	MUSIC_ALARMED,
	MUSIC_HEAVYCOMBAT,
	MUSIC_DEFENSE,
	MUSIC_CONQUER,
	MUSIC_CARCHASE,
	MUSIC_FOOTCHASE,
	MUSIC_INTERROGATION,
	MUSIC_TRIAL,
	MUSIC_RECRUITING,
	MUSIC_DATING,
	MUSIC_NEWSPAPER,
	MUSIC_LACOPS,
	MUSIC_NEWSCAST,
	MUSIC_GLAMSHOW,
	MUSIC_ANCHOR,
	MUSIC_ABORT,
	MUSIC_VICTORY,
	MUSIC_DEFEAT,
	MUSIC_REAGANIFIED,
	MUSIC_STALINIZED,
	MUSIC_OFF, // this one must come immediately after the ones corresponding to music files (this one is to have silence)
	MUSIC_PREVIOUS, // this one must come after MUSIC_OFF (this one is to play the previous song)
	MUSIC_CURRENT, // this one must come after MUSIC_OFF (this one continues playing the current song)
	MUSIC_RANDOM // this one must come after MUSIC_OFF (this one plays a random song)
};

enum WinConditions
{
	WINCONDITION_ELITE,
	WINCONDITION_EASY
};
enum FieldSkillRates
{
	FIELDSKILLRATE_FAST,
	FIELDSKILLRATE_CLASSIC,
	FIELDSKILLRATE_HARD
};

enum Views
{
	VIEW_STALIN = -2, // this one is -2 and is actually calculated based on views >=0 and <VIEWNUM-3
	VIEW_MOOD, // this one is -1 and is likewise calculated based on views >=0 and <VIEWNUM-3
	VIEW_GAY, // view #0, the first one that is actually in the attitude[] array
	VIEW_DEATHPENALTY,
	VIEW_TAXES,
	VIEW_NUCLEARPOWER,
	VIEW_ANIMALRESEARCH,
	VIEW_POLICEBEHAVIOR,
	VIEW_TORTURE,
	VIEW_INTELLIGENCE,
	VIEW_FREESPEECH,
	VIEW_GENETICS,
	VIEW_JUSTICES,
	VIEW_GUNCONTROL,
	VIEW_SWEATSHOPS,
	VIEW_POLLUTION,
	VIEW_CORPORATECULTURE,
	VIEW_CEOSALARY,
	VIEW_WOMEN,//XXX: VIEW_ABORTION DOES NOT EXIST
	VIEW_CIVILRIGHTS,
	VIEW_DRUGS,
	VIEW_IMMIGRATION,
	VIEW_MILITARY,
	VIEW_PRISONS,
	//*JDS* I'm using VIEWNUM-5 in a random generator that rolls a
	//random issue, not including the media/politicalviolence ones, and this will
	//break if these stop being the last 4 issues; do a search
	//for VIEWNUM-5 to change it if it needs to be changed.
	VIEW_AMRADIO,
	VIEW_CABLENEWS,
	//THESE THREE MUST BE LAST FOR VIEWNUM-3 TO WORK IN PLACES
	VIEW_LIBERALCRIMESQUAD,
	VIEW_LIBERALCRIMESQUADPOS,
	//THIS ONE MUST BE LAST. randomissue RELIES ON IT BEING LAST TO IGNORE IT IF
	//CCS IS DEAD.
	VIEW_CONSERVATIVECRIMESQUAD,
	VIEWNUM
};

enum Laws
{
	LAW_STALIN = -2, // not a real law: this is -2 and is actually calculated based on views >=0 and <VIEWNUM-3
	LAW_MOOD, // not a real law: this is -1 and is likewise calculated based on views >=0 and <VIEWNUM-3
	LAW_ABORTION, // law #0, the first one that is actually in the law[] array
	LAW_ANIMALRESEARCH,
	LAW_POLICEBEHAVIOR,
	LAW_PRIVACY,
	LAW_DEATHPENALTY,
	LAW_NUCLEARPOWER,
	LAW_POLLUTION,
	LAW_LABOR,
	LAW_GAY,
	LAW_CORPORATE,
	LAW_FREESPEECH,
	LAW_FLAGBURNING,
	LAW_GUNCONTROL,
	LAW_TAX,
	LAW_WOMEN,
	LAW_CIVILRIGHTS,
	LAW_DRUGS,
	LAW_IMMIGRATION,
	LAW_ELECTIONS,
	LAW_MILITARY,
	LAW_PRISONS,
	LAW_TORTURE,
	LAWNUM
};

enum Crimes
{
	CRIME_STOLEGROUND,
	CRIME_UNLOCKEDDOOR,
	CRIME_BROKEDOWNDOOR,
	CRIME_ATTACKED_MISTAKE,
	CRIME_ATTACKED,
	CRIME_CARCHASE,
	CRIME_CARCRASH,
	CRIME_FOOTCHASE,
	CRIME_KILLEDSOMEBODY,
	CRIME_SHUTDOWNREACTOR,
	CRIME_POLICE_LOCKUP,
	CRIME_COURTHOUSE_LOCKUP,
	CRIME_PRISON_RELEASE,
	CRIME_JURYTAMPERING,
	CRIME_HACK_INTEL,
	CRIME_BREAK_SWEATSHOP,
	CRIME_BREAK_FACTORY,
	CRIME_HOUSE_PHOTOS,
	CRIME_CORP_FILES,
	CRIME_FREE_RABBITS,
	CRIME_FREE_BEASTS,
	CRIME_ARSON,
	CRIME_TAGGING,
	CRIME_ARMORY,
	CRIME_VANDALISM,
	CRIME_BANKVAULTROBBERY,
	CRIME_BANKTELLERROBBERY,
	CRIME_BANKSTICKUP,
	CRIMENUM
};

enum NewsStories
{
	NEWSSTORY_MAJOREVENT,
	NEWSSTORY_SQUAD_SITE,
	NEWSSTORY_SQUAD_ESCAPED,
	NEWSSTORY_SQUAD_FLEDATTACK,
	NEWSSTORY_SQUAD_DEFENDED,
	NEWSSTORY_SQUAD_BROKESIEGE,
	NEWSSTORY_SQUAD_KILLED_SIEGEATTACK,
	NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE,
	NEWSSTORY_SQUAD_KILLED_SITE,
	NEWSSTORY_CCS_SITE,
	NEWSSTORY_CCS_DEFENDED,
	NEWSSTORY_CCS_KILLED_SIEGEATTACK,
	NEWSSTORY_CCS_KILLED_SITE,
	NEWSSTORY_CARTHEFT,
	NEWSSTORY_MASSACRE,
	NEWSSTORY_KIDNAPREPORT,
	NEWSSTORY_NUDITYARREST,
	NEWSSTORY_WANTEDARREST,
	NEWSSTORY_DRUGARREST,
	NEWSSTORY_GRAFFITIARREST,
	NEWSSTORY_BURIALARREST,
	NEWSSTORY_RAID_CORPSESFOUND,
	NEWSSTORY_RAID_GUNSFOUND,
	NEWSSTORY_HOSTAGE_RESCUED,
	NEWSSTORY_HOSTAGE_ESCAPES,
	NEWSSTORY_CCS_NOBACKERS,
	NEWSSTORY_CCS_DEFEATED,
	NEWSSTORY_PRESIDENT_IMPEACHED,
	NEWSSTORY_PRESIDENT_BELIEVED_DEAD,
	NEWSSTORY_PRESIDENT_FOUND_DEAD,
	NEWSSTORY_PRESIDENT_FOUND,
	NEWSSTORY_PRESIDENT_KIDNAPPED,
	NEWSSTORY_PRESIDENT_MISSING,
	NEWSSTORY_PRESIDENT_ASSASSINATED,
	NEWSSTORYNUM
};

const int SQUAD_NAMELEN = 40;


const int SLOGAN_LEN = 80;

const int SCORENUM = 5;

enum EndTypes
{
	END_BUT_NOT_END = -2,
	END_OTHER = -1,
	END_WON,
	END_HICKS,
	END_CIA,
	END_POLICE,
	END_CORP,
	END_REAGAN,
	END_DEAD,
	END_PRISON,
	END_EXECUTED,
	END_DATING,
	END_HIDING,
	END_DISBANDLOSS,
	END_DISPERSED,
	END_CCS,
	END_FIREMEN,
	END_STALIN,
	ENDNUM
};

enum Execs
{
	EXEC_PRESIDENT,
	EXEC_VP,
	EXEC_STATE,
	EXEC_ATTORNEY,
	EXECNUM
};

enum PoliticalParties
{
	LIBERAL_PARTY,
	CONSERVATIVE_PARTY,
	STALINIST_PARTY,
	PARTYNUM
};

// full house (100%) - for looping thru full house
const int  HOUSENUM = 435;
// just over half of house (50%+1) - to pass bills
const int  HOUSEMAJORITY = 218;
// 3/5 of house - has no significance other than in seeing if you won game
const int  HOUSECOMFYMAJORITY = 261;
// 2/3 of house - to override veto or pass constitutional amendment
const int  HOUSESUPERMAJORITY = 290;
// full senate (100%) - for looping thru full senate
const int  SENATENUM = 100;
// just over half of senate(50%+1) - to bass bills
const int  SENATEMAJORITY = 51;
// 3/5 of senate - to break filibuster in real world, but in game, has no significance other than seeing if you won
const int  SENATECOMFYMAJORITY = 60;
// 2/3 of senate - to override veto or pass constitutional amendment
const int  SENATESUPERMAJORITY = 67;
// full court (100%) - for looping thru full court
const int  COURTNUM = 9;
// just over half of court (50%+1) - to make majority rulings
const int  COURTMAJORITY = 5;
// 2/3 of court - has no significance other than seeing if you won game
const int  COURTSUPERMAJORITY = 6;
// all states (100%) - for looping thru all states
const int  STATENUM = 50;
// 3/4 of states (75%) - needed to pass constitutional amendments
const int  STATESUPERMAJORITY = 38;

const int  POLITICIAN_NAMELEN = 80;

enum ReviewModes
{
	REVIEWMODE_LIBERALS,
	REVIEWMODE_HOSTAGES,
	REVIEWMODE_CLINIC,
	REVIEWMODE_JUSTICE,
	REVIEWMODE_SLEEPERS,
	REVIEWMODE_DEAD,
	REVIEWMODE_AWAY,
	REVIEWMODENUM
};

enum SortingChoices
{
	SORTING_NONE,
	SORTING_NAME,
	SORTING_LOCATION_AND_NAME,
	SORTING_SQUAD_OR_NAME,
	SORTINGNUM
};

enum ActiveSortingChoices
{
	SORTINGCHOICE_LIBERALS, //They're prefixed SORTINGCHOICE because they're used as
	SORTINGCHOICE_HOSTAGES, //array indices for the array activesortingchoice.
	SORTINGCHOICE_CLINIC,   //activesortingchoice holds the chosen way to sort the lists.
	SORTINGCHOICE_JUSTICE,
	SORTINGCHOICE_SLEEPERS,
	SORTINGCHOICE_DEAD,
	SORTINGCHOICE_AWAY,
	SORTINGCHOICE_ACTIVATE,
	SORTINGCHOICE_ACTIVATESLEEPERS,
	SORTINGCHOICE_ASSEMBLESQUAD,
	SORTINGCHOICE_BASEASSIGN,
	SORTINGCHOICENUM
};

/*
   Declarations for every function grouped by folder and file.
   Created by jonathansfox.
*/

/* This is declared again lower down, just needed here for this header. */
std::string tostring(long i);


//

//#include "vehicle/vehicletype.h"
//#include "vehicle/vehicle.h"


//just a float that is initialized to 0
struct Float_Zero
{
	Float_Zero() : n(0.0f) { }
	operator float&() { return n; }
	float n;
};
//Interrogation information for the InterrogationST system, to be
//dynamically created on capture and deleted when InterrogationST ends,
//referenced using a pointer typecast into one of the arguments
//of the target's current action.
struct InterrogationST
{
	InterrogationST() : druguse(0) { techniques[0] = 1, techniques[1] = 1, techniques[2] = 0, techniques[3] = 0, techniques[4] = 0, techniques[5] = 0; }
	bool techniques[6]; //yesterday's InterrogationST plan
	int druguse; //total days of drug use
				 //Maps individual characters to the rapport built with them
	map<long, struct Float_Zero> rapport;
};

struct ActivityST
{
	ActivityST() : type(0), arg(0), arg2(0) { }
	int type;
	long arg, arg2;
	// return a reference to arg, with arg typecast as a pointer to an object of type InterrogationST,
	// allowing us to easily access and modify the InterrogationST data without typecasting outside this function
	InterrogationST* &intr() { InterrogationST** i = reinterpret_cast<InterrogationST**>(&arg); return *i; }
};

int get_associated_attribute(int skill_type);


enum Bouncer_Reject_Reason
{
	REJECTED_CCS,
	REJECTED_NUDE,
	REJECTED_WEAPONS,
	REJECTED_UNDERAGE,
	REJECTED_FEMALEISH,
	REJECTED_FEMALE,
	REJECTED_BLOODYCLOTHES,
	REJECTED_DAMAGEDCLOTHES,
	REJECTED_CROSSDRESSING,
	REJECTED_GUESTLIST,
	REJECTED_DRESSCODE,
	REJECTED_SECONDRATECLOTHES,
	REJECTED_SMELLFUNNY,
	NOT_REJECTED
};


enum bigListOfEnumTags {
	ENUM_tag_only_sell_legal_items,
	ENUM_tag_fullscreen,
	ENUM_tag_allow_selling,
	ENUM_tag_increase_prices_with_illegality,
	ENUM_tag_department,
	ENUM_tag_entry,
	ENUM_tag_exit,
	ENUM_tag_sell_masks,
	ENUM_tag_letter,
	ENUM_tag_item,

	ENUM_tag_class,
	ENUM_tag_type,
	ENUM_tag_description,
	ENUM_tag_price,
	ENUM_tag_sleeperprice,

	ENUM_tag_alignment,
	ENUM_tag_PUBLIC_MOOD,
	ENUM_tag_LIBERAL,
	ENUM_tag_MODERATE,
	ENUM_tag_CONSERVATIVE,
	ENUM_tag_age,
	ENUM_tag_DOGYEARS,
	ENUM_tag_CHILD,
	ENUM_tag_TEENAGER,
	ENUM_tag_YOUNGADULT,
	ENUM_tag_MATURE,
	ENUM_tag_GRADUATE,
	ENUM_tag_MIDDLEAGED,
	ENUM_tag_SENIOR,
	ENUM_tag_attribute_points,
	ENUM_tag_attributes,
	ENUM_tag_juice,
	ENUM_tag_gender,
	ENUM_tag_infiltration,
	ENUM_tag_money,
	ENUM_tag_skills,
	ENUM_tag_armor,
	ENUM_tag_weapon,
	ENUM_tag_encounter_name,
	ENUM_tag_type_name,

	ENUM_tag_shortname,
	ENUM_tag_shortname_future,
	ENUM_tag_name_sub_1,
	ENUM_tag_name_sub_2,
	ENUM_tag_name_future_sub_1,
	ENUM_tag_name_future_sub_2,
	ENUM_tag_shortname_sub_1,
	ENUM_tag_shortname_sub_2,
	ENUM_tag_shortname_future_sub_1,
	ENUM_tag_shortname_future_sub_2,
	ENUM_tag_can_take_hostages,
	ENUM_tag_threatening,
	ENUM_tag_can_threaten_hostages,
	ENUM_tag_protects_against_kidnapping,
	ENUM_tag_musical_attack,
	ENUM_tag_instrument,
	ENUM_tag_graffiti,
	ENUM_tag_legality,
	ENUM_tag_bashstrengthmod,
	ENUM_tag_auto_break_locks,
	ENUM_tag_suspicious,
	ENUM_tag_size,
	ENUM_tag_attack,

	ENUM_tag_priority,
	ENUM_tag_ranged,
	ENUM_tag_thrown,
	ENUM_tag_can_backstab,
	ENUM_tag_ammotype,
	ENUM_tag_attack_description,
	ENUM_tag_hit_description,
	ENUM_tag_always_describe_hit,
	ENUM_tag_hit_punctuation,
	ENUM_tag_skill,
	ENUM_tag_accuracy_bonus,
	ENUM_tag_number_attacks,
	ENUM_tag_successive_attacks_difficulty,
	ENUM_tag_strength_min,
	ENUM_tag_strength_max,
	ENUM_tag_random_damage,
	ENUM_tag_fixed_damage,
	ENUM_tag_bruises,
	ENUM_tag_tears,
	ENUM_tag_cuts,
	ENUM_tag_burns,
	ENUM_tag_shoots,
	ENUM_tag_bleeding,
	ENUM_tag_severtype,
	ENUM_tag_damages_armor,
	ENUM_tag_armorpiercing,
	ENUM_tag_no_DR_for_limbs_chance,
	ENUM_tag_critical,
	ENUM_tag_fire,

	ENUM_tag_name,
	ENUM_tag_attribute,
	ENUM_tag_effect,
	ENUM_tag_max_age,
	ENUM_tag_min_age,
	ENUM_tag_cost,
	ENUM_tag_difficulty,

	ENUM_tag_make_difficulty,
	ENUM_tag_make_price,
	ENUM_tag_deathsquad_legality,
	ENUM_tag_can_get_bloody,
	ENUM_tag_can_get_damaged,
	ENUM_tag_body_covering,
	ENUM_tag_interrogation,
	ENUM_tag_professionalism,
	ENUM_tag_conceal_weapon_size,
	ENUM_tag_stealth_value,
	ENUM_tag_mask,
	ENUM_tag_surprise,
	ENUM_tag_qualitylevels,
	ENUM_tag_durability,

	ENUM_tag_vtypeidname,
	ENUM_tag_vtypeid,
	ENUM_tag_color,
	ENUM_tag_heat,
	ENUM_tag_location,
	ENUM_tag_myear,
	ENUM_tag_id,

	ENUM_tag_year,
	ENUM_tag_start_at_current_year,
	ENUM_tag_start_at_year,
	ENUM_tag_add_random_up_to_current_year,
	ENUM_tag_add_random,
	ENUM_tag_add,
	ENUM_tag_colors,
	ENUM_tag_display_color,
	ENUM_tag_drivebonus,
	ENUM_tag_base,
	ENUM_tag_skillfactor,
	ENUM_tag_softlimit,
	ENUM_tag_hardlimit,
	ENUM_tag_dodgebonus,
	ENUM_tag_attackbonus,
	ENUM_tag_driver,
	ENUM_tag_passenger,
	ENUM_tag_longname,
	ENUM_tag_stealing,
	ENUM_tag_difficulty_to_find,
	ENUM_tag_extra_heat,
	ENUM_tag_sense_alarm_chance,
	ENUM_tag_touch_alarm_chance,
	ENUM_tag_low_armor_min,
	ENUM_tag_low_armor_max,
	ENUM_tag_high_armor_min,
	ENUM_tag_high_armor_max,
	ENUM_tag_armor_midpoint,
	ENUM_tag_available_at_dealership,
};

string skill_enum_to_string(int skill_type);
string showXmlSkill(int skill_, int value_);
string showXmlAttribute(int attribute_, int value_);

const string PACKAGE_VERSION_STR = "4.12.40";
const int version = 41240;
const int lowestloadversion = 40100;
const int lowestloadscoreversion = 31203;

const string BLANK_STRING = "";
const string singleDot = ".";
const string dotSpace = ". ";
const string COMMA_SPACE = ", ";
const string spaceDashSpace = " - ";
const string spaceParanthesisDollar = " ($";
const string paranthesisDollar = "($";
const string COLON_SPACE = ": ";
const string ampersandC = "&c";
const string CLOSE_PARENTHESIS = ")";
const string percentSign = "%";
const string singleSpace = " ";

const string CHOOSE_A_LIBERAL_TO = "Choose a Liberal squad member to ";

const string AND = " and ";
const string string_sleeper = "Sleeper ";
const string ampersandR = "&r";
const string show_squad_liberal_status = "0 - Show the squad's Liberal status";
const string HASH_CHECK_STATUS_OF_LIBERAL = "# - Check the status of a squad Liberal";
const string O_CHANGE_SQUAD_ORDER = "O - Change the squad's Liberal order";
const string enter_done = "Enter - Done";
const string undefined = "UNDEFINED";
const string exclamationPoint = "!";
const string failedToLoad = "Failed to load ";
const string pressAnyOtherKey = "Press any other key to continue...";
const string pressAnyKeyString = "Press any other key when ready to begin...";
const string city = "CITY: ";
const string tag_heat = "heat";

enum BillStatus
{
	BILL_SIGNED = -2,
	BILL_OVERRIDE_VETO = -1,
	BILL_PASSED_CONGRESS = 0,
	BILL_FAILED = 1
};
#ifdef	ACTIVATE_CPP
//activate.cpp


#include "../creature/creature.h"
#include "../locations/locations.h"
#include "../items/armortype.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../creature/augmenttype.h"
#include "../common/translateid.h"
// for  int getsquad(int)
//#include "../common/commonactions.h"
void sorting_prompt(short listforsorting);
#include "../common/commonactionsCreature.h"
// for void sortliberals(std::vector<Creature *>&,short,bool)
#include "../common/commondisplay.h"
#include "../common/commondisplayCreature.h"
// for void printfunds(int,int,char*)
//#include "../common/getnames.h"
std::string gettitle(const int align, const int juice);
string getactivity(ActivityST &act);
//#include "../common/help.h"
void HelpActivities(int);
//#include "../common/stringconversion.h"
string attribute_enum_to_string(int);
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
char getseigedFromLocation(int secondaryLocation);
void createTempSquadWithJustThisLiberal(DeprecatedCreature *cr, int cursquadid);
#include "../common/creaturePoolCreature.h"
#include "../common/musicClass.h"

extern bool ZEROMORAL;
extern int selectedsiege;
extern Log gamelog;
extern long cursquadid;
extern MusicClass music;
extern short lawList[LAWNUM];
extern short mode;
extern short activesortingchoice[SORTINGCHOICENUM];
extern vector<ArmorType *> armortype;
extern vector<RecruitData> recruitable_creatures;

const string ACTIVATE_UNINVOLVED_LIBERALS = "Activate Uninvolved Liberals";
const string CODENAME_SKILL_HEALTH_LOCATION_HEADER = "컴컴CODE NAME컴컴컴컴컴컴SKILL컴횴EALTH컴횸OCATION컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

const string OTHER_CLASSES = "Other classes";
const string CLASSES_COST_SIXTY = "Classes cost $60 a day. Study what?";
const string PRESS_A_LETTER_TO_SELECT_PROFESSION = "Press a Letter to select a Profession";
const string TYPE_DIFFICULTY_HEADER = "컴컴TYPE컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴횯IFFICULTY TO ARRANGE MEETING컴";
const string TRY_TO_MEET_AND_RECRUIT = " try to meet and recruit today?";
const string WHAT_TYPE_OF_PERSON_WILL = "What type of person will ";
const string AGE_COLON = "Age: ";
const string HEART_COLON = "Heart: ";
const string STATUS_COLON = "Status:";
const string HAS_BEEN_BRUTALLY_MURDERED_BY = " has been brutally murdered by ";
const string HAS_BEEN_AUGMENTED_WITH = " has been augmented with ";
const string HAS_BEEN_HORRIBLY_DISFIGURED = " has been horribly disfigured";
const string PRESS_ANY_KEY = "Press any key to return";
const string ARE_YOU_SURE_Y_N = "Are you sure? (y/n)";
const string LONG_LINE_BUT_NOT_EIGHTY = "컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴";
const string DESCRIPTION = "Description";
const string CHANCE_AT_SUCCESS_COLON = "Chance at Success: ";
const string SPACE_PLUS = " +";
const string EFFECT_COLON = "Effect: ";
const string AUGMENTATION_COLON = "Augmentation: ";
const string SUBJECT_COLON = "Subject: ";
const string SELECT_AUGMENTATION = "Select an Augmentation";
const string EIGHTY_LINE = "컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴";
const string PRESS_A_LETTER_TO_SELECT_LIBERAL = "Press a Letter to select a Liberal";
const string NAME_HEALTH_HEART_HEADER = "컴컴NAME컴컴컴컴컴컴컴컴컴컴컴횴EALTH컴컴컴컴컴컴HEART컴컴컴컴AGE컴컴컴컴컴컴컴�";
const string SELECT_LIBERAL_TO_PERFORM_EXPERIMENTS_UPON = "Select a Liberal to perform experiments on";
const string PRESS_A_LETTER_TO_SELECT_CLOTHING_TYPE = "Press a Letter to select a Type of Clothing";
const string NAME_DIFFICULTY_COST_HEADER = "컴컴NAME컴컴컴컴컴컴컴컴컴컴컴컴컴컴횯IFFICULTY컴컴컴컴컴컴횮OST컴컴컴컴컴컴컴컴";
const string TRY_TO_MAKE_NOTE_HALF_COST_WITH_CLOTH = " try to make?   (Note: Half Cost if you have cloth)";
const string WHICH_WILL = "Which will ";
const string PRESS_A_LETTER_TO_SELECT_CONSERVATIVE = "Press a Letter to select a Conservative";
const string CONST_X_DAY = "Day";
const string CONST_X_DAYS = "Days";
const string DAYS_IN_CAPTIVITY = "DAYS IN CAPTIVITY";
const string BE_WATCHING_OVER = " be watching over?";
const string WHICH_HOSTAGE_WILL = "Which hostage will ";
const string SPACE_WILL_SPACE = " will ";
const string X_NOTHING = "X - Nothing for Now";
const string CONST_X_ENTER_CONFIRM = "Enter - Confirm Selection";
const string QUESTION_HELP = "? - Help";
const string E_EQUIP_THIS_LIBERAL = "E - Equip this Liberal";
const string Z_DIZPOSE_OF_BODIES = "Z - Dispose of bodies";
const string H_HEAL_LIBERALS = "H - Heal Liberals";
const string M_MOVE_TO_CLINIC = "M - Move to the Free Clinic";
const string L_LEARN_IN_UNIVERSITY = "L - Learn in the University District";
const string I_TEND_TO_HOSTAGE = "I - Tend to a Conservative hostage";
const string T_TEACHING_OTHER_LIBERALS = "T - Teaching Other Liberals";
const string BE_DOING_TODAY = " be doing today?";
const string TAKING_ACTION_COLON_WHAT_WILL = "Taking Action: What will ";
const string YESTERDAY_WHAT_NOW = " yesterday. What now?";
const string MADE_DOLLARS = " made $";
const string PRESS_A_LETTER_TO_ASSIGN_ACTIVITY_OR_NUMBER = "Press a Letter to Assign an Activity.  Press a Number to select an Activity.";
const string BULK_ACTIVITY_HEADER = "BULK ACTIVITY";
const string CODE_NAME_CURRENT_ACTIVITY_HEADER = "컴컴CODE NAME컴컴컴컴컴컴CURRENT ACTIVITY컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�";
const string Z_TO_ASSIGN_SIMPLE_TASKS = "Press Z to assign simple tasks in bulk.";
const string CONST_X_T_TO_SORT = " T to sort people.";
const string PRESS_A_LETTER_TO_ASSIGN_ACTIVITY = "Press a Letter to Assign an Activity.";
const string CONST_X_TITLE_ACTIVITY = "ACTIVITY";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";

const string STANDARD_ACTIVITIES_AND_DATA_TXT = "standard_activities_and_data.txt";
const string BULK_ACTIVITY_STRING_TXT = "bulkActivityString.txt";
vector<ActivityAndString> data_lessons;
map<Activity, Data_Activity> data_activities;
map<char, vector<ActivityAndString> > activate_menu_items;

vector<CreatureTypes> ACTIVITY_TEACH_FIGHTING_DEFAULT;
// this first block are creatures with All Weapon Skills, Martial Arts, Dodge, and First Aid
vector<CreatureTypes> ACTIVITY_TEACH_COVERT_DEFAULT;
// this second block are creatures with Computers, Security, Stealth, Disguise, Tailoring, Seduction, Psychology, & Driving
vector<CreatureTypes> ACTIVITY_TEACH_POLITICS_DEFAULT;
// this third block are creatures with Writing, Persuasion, Law, Street Sense, Science, Religion, Business, Music, & Art

#endif	//ACTIVATE_CPP
#ifdef	ACTIVATE_SLEEPERS_CPP
//activate_sleepers.cpp
#include "../creature/creature.h"
//#include "../common/commonactions.h"
void sorting_prompt(short listforsorting);
#include "../common/commonactionsCreature.h"
// for void sortliberals(std::vector<Creature *>&,short,bool)
#include "../common/commondisplay.h"
//#include "../common/commondisplayCreature.h"
void printcreatureinfo(DeprecatedCreature *cr, unsigned char knowledge = 255);
//#include "../common/getnames.h"
string getactivity(ActivityST &act);
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"
#include "../common/creaturePoolCreature.h"
//extern string spaceDashSpace;
//extern string percentSign;


//	extern string percentSign;
extern MusicClass music;
extern short activesortingchoice[SORTINGCHOICENUM];
//// #include "../common/commonactions.h"
void sorting_prompt(short listforsorting);
string getactivity(ActivityST &act);
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

const string WILL_STEAL = " will steal equipment and send it to the Shelter.";
const string WILL_EMBEZZLE = " will embezzle money for the LCS.";
const string WILL_SNOOP = " will snoop around for secrets and enemy plans.";
const string WILL_TRY_TO_RECRUIT = " will try to recruit additional sleeper agents.";
const string WILL_BUILD_SUPPORT = " will build support for Liberal causes.";
const string WILL_STAY_OUT_OF_TROUBLE = " will stay out of trouble.";
const string THREE_STEAL = "3 - Steal Equipment";
const string TWO_EMBEZZLE = "2 - Embezzle Funds";
const string ONE_UNCOVER_SECRETS = "1 - Uncover Secrets";
const string THREE_NEED_MORE_JUICE_TO_RECRUIT = "3 - [Need More Juice to Recruit]";
const string THREE_ENLIGHTENED_CANNOT_RECRUIT = "3 - [Enlightened Can't Recruit]";
const string THREE_EXPAND_SLEEPER_NETWORK = "3 - Expand Sleeper Network";
const string TWO_ADVOCATE_LIBERALISM = "2 - Advocate Liberalism";
const string ONE_LAY_LOW = "1 - Lay Low";
const string ENTER_CONFIRM_SELECTION = "Enter - Confirm Selection";
const string C_JOIN_ACTIVE_LCS = "C - Join the Active LCS";
const string B_ESPIONAGE = "B - Espionage";
const string A_COMMUNICATION = "A - Communication and Advocacy";
const string FOCUS_ON = " focus on?";
const string TAKING_UNDERCOVER_ACTION_WHAT_WILL = "Taking Undercover Action:   What will ";

const string T_TO_SORT_PEOPLE = " T to sort people.";
const string PRESS_A_LETTER_TO_ASSIGN = "Press a Letter to Assign an Activity.";
const string EFFECTIVENESS_COLON = "Effectiveness: ";
const string ACTIVITY_HEADER = "ACTIVITY";
const string SITE_HEADER = "SITE";
const string JOB_HEADER = "JOB";
const string CODE_NAME_HEADER = "CODE NAME";
const string ACTIVATE_SLEEPER = "Activate Sleeper Agents";

#endif	//ACTIVATE_SLEEPERS_CPP
#ifdef	ACTIVITIES_CPP
// activities.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../items/armortype.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../basemode/activate.h"
// for armor_makedifficulty
#include "../items/loottype.h"
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
#include "../common/commondisplayCreature.h"
// for addstr
#include "../common/translateid.h"
// for  int getsquad(int)
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
// for void criminalize(Creature &,short);
#include "../common/getnames.h"
// for std::string getview(short, bool)
#include "../politics/politics.h"
//for int publicmood(int l);
#include "../combat/chase.h"
#include "../combat/chaseCreature.h"
//for void makechasers(long sitetype,long sitecrime);
#include "../combat/fightCreature.h"  

#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"
#include "../items/lootTypePoolItem.h"
#include "../common/creaturePool.h"


void doActivitySolicitDonations(vector<DeprecatedCreature *> &solicit, char &clearformess);
void doActivitySellTshirts(vector<DeprecatedCreature *> &tshirts, char &clearformess);
void doActivitySellArt(vector<DeprecatedCreature *> &art, char &clearformess);
void doActivitySellMusic(vector<DeprecatedCreature *> &music, char &clearformess);
void doActivitySellBrownies(vector<DeprecatedCreature *> &brownies, char &clearformess);
void doActivityHacking(vector<DeprecatedCreature *> &hack, char &clearformess);
void doActivityGraffiti(vector<DeprecatedCreature *> &graffiti, char &clearformess);
void doActivityProstitution(vector<DeprecatedCreature *> &prostitutes, char &clearformess);
void doActivityLearn(vector<DeprecatedCreature *> &students, char &clearformess);
void doActivityTrouble(vector<DeprecatedCreature *> &trouble, char &clearformess);
void doActivityTeach(vector<DeprecatedCreature *> &teachers, char &clearformess);
void doActivityBury(vector<DeprecatedCreature *> &bury, char &clearformess);

void addLootToLoc(int loc, Item* it);
char tryFindCloth(int cursite);
string wasUnableToFind(const string old);
string considerLeaving(const bool sensealarm, const bool alarmon, const string name);
extern bool SHOWMECHANICS;
extern char endgamestate;
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern char newscherrybusted;
extern chaseseqst chaseseq;
extern class Ledger ledger;
extern Deprecatednewsstoryst *sitestory;
extern Log gamelog;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short background_liberal_influence[VIEWNUM];
extern short exec[EXECNUM];
extern short fieldskillrate;
extern short interface_pgdn;
extern short interface_pgup;
extern short lawList[LAWNUM];
extern short mode;
extern short public_interest[VIEWNUM];
extern vector<ArmorType *> armortype;
extern vector<DeprecatedCreature *> pool;
extern vector<Deprecatednewsstoryst *> newsstory;
extern vector<Deprecatedsquadst *> squad;
static const char SURVEY_PAGE_SIZE = 14;
string gimmeASprayCan(DeprecatedCreature* graffiti);
Vehicle* getVehicleOfThisType(int cartype);
void buyMeASprayCan(DeprecatedCreature* graffiti);
void newVehicle(Vehicle *startcar);

enum CarHotwireMethod {
	UNDETERMINED,
	ATTEMPT_HOTWIRE,
	USE_KEYS
};


const string CONST_X_CAN = " can.";
const string CONST_X_HAS_LEARNED_AS_MUCH_AS_ = " has learned as much as ";

const string tag_POLICECAR = "POLICECAR";
const string tag_WEAPON_SPRAYCAN = "WEAPON_SPRAYCAN";
const string tag_WEAPON = "WEAPON";
const string CONST_X_HAS_ = " has ";
const string CONST_X_EXCLAMATION_POINT = "!";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string CONST_X_PERUSES_MAGAZINES = " peruses some sewing magazines.";
const string CONST_X_CLEANS_KITCHEN = " cleans the kitchen.";
const string CONST_X_REORGANIZES_CLOSET = " reorganizes the armor closet.";
const string CONST_X_TIDIES_SAFEHOUSE = " tidies up the safehouse.";
const string CONST_X_RUINED = " ruined";
const string CONST_X_REPAIRS_SOMEWHAT = " repairs what little can be fixed of ";
const string CONST_X_NO_HOPE_TO_REPAIR = " finds there is no hope of repairing ";
const string CONST_X_REPAIRS = " repairs ";
const string CONST_X_IS_WORKING_TO_REPAIR = " is working to repair ";
const string CONST_X_CLEANS = " cleans ";
const string CONST_X_DISPOSES_OF = " disposes of ";
const string CONST_X_WASTED_MATERIALS = " wasted the materials for a";
const string CONST_X_TH_RATE = "th-rate";
const string CONST_X_FOURTH_RATE = "fourth-rate";
const string CONST_X_THIRD_RATE = "third-rate";
const string CONST_X_SECOND_RATE = "second-rate";
const string CONST_X_FIRST_RATE = "first-rate";
const string CONST_X_HAS_MADE_A = " has made a ";
const string CONST_X_CANNOT_FIND_CLOTH = " cannot find enough cloth to reduce clothing costs.";
const string CONST_X_CANNOT_AFFORD_MATERIAL = " cannot afford material for clothing.";
const string CONST_X_LITTLE_WHITESPACE = "    ";
const string CONST_X_ENTER_DONE = "Enter - Done";
const string CONST_X_LIBERAL_PERCENTAGE_POINTS = " Liberal percentage points.";
const string CONST_X_RESULTS_ARE_PLUS_MINUS = "Results are +/- ";
const string CONST_X_ISSUE_PUBLIC_INTEREST_HEADER = "XX% Issue 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴횾ublic Interest";
const string CONST_X_ADDITIONAL_FINDINGS = "Additional notable findings:";
const string CONST_X_AMNESTY_FOR_IMMIGRANTS = "wanted amnesty for illegal immigrants";
const string CONST_X_CONDEMN_IMMIGRATION_REGULATIONS = "condemned unnecessary immigration regulations";
const string CONST_X_BELIEVE_IN_LEGAL_MARIJUANA = "believed in legalizing marijuana";
const string CONST_X_SUPPORTED_MARIJUANA_LEGAL = "supported keeping marijuana legal";
const string CONST_X_PERCENT_SIGN = "% ";
const string CONST_X_TWO_QUESTION_MARKS = "??";
const string CONST_X_NONE_SPACE = "None     ";
const string CONST_X_LOW = "Low      ";
const string CONST_X_MODERATE = "Moderate ";
const string CONST_X_HIGH = "High     ";
const string CONST_X_VERY_HIGH = "Very High";
const string CONST_X_UNKNOWN = "Unknown  ";
const string CONST_X_MANY_DOTS = "........................................................";
const string CONST_X_LOTS_OF_WHITESPACE = "                                                                                ";
const string CONST_X_LIBERAL_MEDIA_BIAS = "Liberal Media Bias.";
const string CONST_X_CONSERVATIVE_MEDIA_BIAS = "Conservative Media Bias.";
const string CONST_X_THE_LCS_TERRORISTS = "the LCS terrorists.";
const string CONST_X_THE_LIBERAL_CRIME_SQUAD = "the Liberal Crime Squad.";
const string CONST_X_ACTIVIST_POLITICAL_GROUPS = "activist political groups.";
const string CONST_X_THE_PUBLIC_IS_UNCONCERNED = "The public is not concerned with politics right now.";

const string CONST_X_TAKING_STRONG_ACTION = "taking strong action.";
const string CONST_X_THE_PEOPLE_ARE_MOST_CONCERNED = "The people are most concerned about ";
const string CONST_X_PRESIDENT = "President ";
const string CONST_X_HAD_FAVORABLE_OPINION = "% had a favorable opinion of ";
const string CONST_X_SURVEY_OF_PUBLIC_OPINION = "Survey of Public Opinion, According to Recent Polls";
const string CONST_X_IS_ACCOSTED_BY_POLICE = " is accosted by police while ";
const string CONST_X_SOLICITING_DONATIONS = "soliciting donations";
const string CONST_X_SELLING_SHIRTS = "selling shirts";
const string CONST_X_SKETCHING_PORTRAITS = "sketching portraits";

const string CONST_X_PLAYING_MUSIC = "playing music";
const string CONST_X_SELLING_BROWNIES = "selling brownies";
const string CONST_X_A_SPACE = " a ";
const string CONST_X_YOUR_HACKERS_HAVE_LOWERCASE = "Your hackers have ";
const string CONST_X_YOUR_HACKERS_HAVE_ = "Your Hackers have ";
const string CONST_X_HAS_BEGUN_WORK_ON_A_LARGE_MURAL_ABOUT_ = " has begun work on a large mural about ";
const string CONST_X_WORKS_THROUGH_THE_NIGHT_ON_A_LARGE_MURAL = " works through the night on a large mural.";
const string CONST_X_MURAL_ABOUT_ = " mural about ";
const string CONST_X_BEAUTIFUL = " beautiful";
const string CONST_X_HAS_COMPLETED_A = " has completed a";
const string CONST_X_WHILE_SPRAYING_AN_LCS_TAG = " while spraying an LCS tag!";
const string CONST_X_WHILE_WORKING_ON_THE_MURAL = " while working on the mural!";
const string CONST_X_WAS_SPOTTED_BY_THE_POLICE = " was spotted by the police";
const string CONST_X_NEEDS_A_SPRAYCAN_EQUIPPED_TO_DO_GRAFFITI = " needs a spraycan equipped to do graffiti.";
const string CONST_X_BOUGHT_SPRAYPAINT_FOR_GRAFFITI = " bought spraypaint for graffiti.";
const string CONST_X_FROM_ = " from ";
const string CONST_X_GRABBED_A_ = " grabbed a ";
const string CONST_X_WAS_NEARLY_CAUGHT_IN_A_PROSTITUTION_STING = " was nearly caught in a prostitution sting.";
const string CONST_X_HAS_BEEN_ARRESTED_IN_A_PROSTITUTION_STING = " has been arrested in a prostitution sting.";
const string CONST_X_SET_UP_A_MOCK_SWEATSHOP_IN_THE_MIDDLE_OF_THE_MALL = "set up a mock sweatshop in the middle of the mall!";
const string CONST_X_BURNED_A_CORPORATE_SYMBOL_AND_DENOUNCED_CAPITALISM = "burned a corporate symbol and denounced capitalism!";
const string CONST_X_DISTRIBUTED_FLIERS_GRAPHICALLY_ILLUSTRATING_CIA_TORTURE = "distributed fliers graphically illustrating CIA torture!";
const string CONST_X_DISTRIBUTED_FLIERS_GRAPHICALLY_ILLUSTRATING_EXECUTIONS = "distributed fliers graphically illustrating executions!";
const string CONST_X_SQUIRTED_BUSINESS_PEOPLE_WITH_FAKE_POLLUTED_WATER = "squirted business people with fake polluted water!";
const string CONST_X_DRESSED_UP_AND_PRETENDED_TO_BE_A_RADIOACTIVE_MUTANT = "dressed up and pretended to be a radioactive mutant!";
const string CONST_X_DRESSED_UP_AND_PRETENDED_TO_BE_RADIOACTIVE_MUTANTS = "dressed up and pretended to be radioactive mutants!";
const string CONST_X_GONE_DOWNTOWN_AND_REENACTED_A_POLICE_BEATING = "gone downtown and reenacted a police beating!";
const string CONST_X_POSTED_HORRIFYING_DEAD_ABORTION_DOCTOR_PICTURES_DOWNTOWN = "posted horrifying dead abortion doctor pictures downtown!";
const string CONST_X_DISRUPTED_A_TRADITIONAL_WEDDING_AT_A_CHURCH = "disrupted a traditional wedding at a church!";
const string CONST_X_RUN_AROUND_UPTOWN_SPLASHING_PAINT_ON_FUR_COATS = "run around uptown splashing paint on fur coats!";
const string CONST_X_BROKEN = "broken!";
const string CONST_X_S_LAST_UNBROKEN_RIB_IS_ = "'s last unbroken rib is ";
const string CONST_X_S_RIB_IS_ = "'s rib is ";
const string CONST_X_ONE_OF_ = "One of ";
const string CONST_X_S_RIBS_ARE_ = "'s ribs are ";
const string CONST_X_OF_ = " of ";
const string CONST_X_ALL_SPACE = "All ";
const string CONST_X_S_TOOTH_HAS_BEEN_PULLED_OUT_WITH_PLIERS = "'s tooth has been pulled out with pliers!";
const string CONST_X_S_TEETH_HAVE_BEEN_SMASHED_OUT_ON_THE_CURB = "'s teeth have been smashed out on the curb.";
const string CONST_X_S_NECK_HAS_BEEN_BROKEN = "'s neck has been broken!";
const string CONST_X_S_UPPER_SPINE_HAS_BEEN_BROKEN = "'s upper spine has been broken!";
const string CONST_X_S_LOWER_SPINE_HAS_BEEN_BROKEN = "'s lower spine has been broken!";
const string CONST_X_IS_SEVERELY_BEATEN_BEFORE_THE_MOB_IS_BROKEN_UP = " is severely beaten before the mob is broken up.";
const string CONST_X_OUT_OF_EVERYONE_WHO_GOT_CLOSE = " out of everyone who got close!";
const string CONST_X_SHIT = "shit";
const string CONST_X_TAR = "[tar]";
const string CONST_X_BEAT_THE = " beat the ";
const string CONST_X_THE_MOB_SCATTERS = "The mob scatters!";
const string CONST_X_BRANDISHES_THE_ = " brandishes the ";
const string CONST_X_IS_CORNERED_BY_A_MOB_OF_ANGRY_REDNECKS = " is cornered by a mob of angry rednecks.";
const string CONST_X_CAUSING_TROUBLE = "causing trouble";
const string CONST_X_YOUR_ACTIVISTS_HAVE_ = "Your Activists have ";
const string CONST_X_PRESS_A_LETTER_TO_SELECT_A_TYPE_OF_CAR = "Press a Letter to select a Type of Car";
const string CONST_X_TYPEDIFFICULTY_TO_FIND_UNATTENDED = "컴컴TYPE컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴DIFFICULTY TO FIND UNATTENDED컴";
const string CONST_X_TRY_TO_FIND_AND_STEAL_TODAY = " try to find and steal today?";
const string CONST_X_WHAT_TYPE_OF_CAR_WILL_ = "What type of car will ";
const string CONST_X_STANDS_BY_THE_ = " stands by the ";
const string CONST_X_THIS_IS_THE_VIPER_STAND_AWAY = "THIS IS THE VIPER!   STAND AWAY!";
const string CONST_X_THE_VIPER_COLON = "THE VIPER:   ";
const string CONST_X_STAND_AWAY_FROM_THE_VEHICLE_BEEP_BEEP = "STAND AWAY FROM THE VEHICLE!   <BEEP!!> <BEEP!!>";
const string CONST_X_BEEP_BEEP_BEEP_BEEP = "<BEEP!!> <BEEP!!> <BEEP!!> <BEEP!!>";
const string CONST_X_COLON_SPACE_SPACE = ":   ";
const string CONST_X_THE_VIPER = "THE VIPER";
const string CONST_X_B_BREAK_THE_WINDOW = "B - Break the window.";
const string CONST_X_A_PICK_THE_LOCK = "A - Pick the lock.";
const string CONST_X_BUT_IT_IS_STILL_SOMEWHAT_INTACT = " but it is still somewhat intact.";
const string CONST_X_WITH_A_ = " with a ";
const string CONST_X_CRACKS_THE_WINDOW = " cracks the window";
const string CONST_X_SMASHES_THE_WINDOW = " smashes the window";
const string CONST_X_FIDDLES_WITH_THE_LOCK_WITH_NO_LUCK = " fiddles with the lock with no luck.";
const string CONST_X_AN_ALARM_SUDDENLY_STARTS_BLARING = "An alarm suddenly starts blaring!";
const string CONST_X_JIMMIES_THE_CAR_DOOR_OPEN = " jimmies the car door open.";
const string CONST_X_HAS_BEEN_SPOTTED_BY_A_PASSERBY = " has been spotted by a passerby!";

const string CONST_X_ADVENTURES_IN_LIBERAL_CAR_THEFT = "Adventures in Liberal Car Theft";

const string CONST_X_IF_THEY_WERE_HERE_ID_HAVE_FOUND_THEM_BY_NOW = "If they were here, I'd have found them by now.";
const string CONST_X_I_DONT_THINK_THEYRE_IN_HERE = "I don't think they're in here...";
const string CONST_X_ARE_THEY_EVEN_IN_HERE = "Are they even in here?";
const string CONST_X_RUMMAGING_ = ": <rummaging> ";
const string CONST_X_FOUND_THE_KEYS = " found the keys ";
const string CONST_X_HOLY_SHIT_ = "Holy shit!  ";
const string CONST_X_HOLY_CAR_KEYS_ = "Holy [Car Keys]!  ";
const string CONST_X_UNDER_THE_BACK_SEAT = "under the back seat!";
const string CONST_X_UNDER_THE_FRONT_SEAT = "under the front seat!";
const string CONST_X_IN_THE_GLOVE_COMPARTMENT = "in the glove compartment!";
const string CONST_X_ABOVE_THE_PULLDOWN_SUNBLOCK_THINGY = "above the pull-down sunblock thingy!";
const string CONST_X_IN_THE_IGNITION_DAMN = "in the ignition.  Damn.";
const string CONST_X_IN_SPACE_WITH_ALIENS_SERIOUSLY = "in SPACE. With ALIENS. Seriously.";

const string CONST_X_HOTWIRES_THE_CAR = " hotwires the car!";
const string CONST_X_ENTER_THE_VIPER_HAS_FINALLY_DETERRED_ = "Enter - The Viper has finally deterred ";
const string CONST_CALL_IT_A_DAY_PRESS_ENTER = "Enter - Call it a day.";
const string CONST_X_B_DESPERATELY_SEARCH_FOR_KEYS = "B - Desperately search for keys.";
const string CONST_X_A_HOTWIRE_THE_CAR = "A - Hotwire the car.";


const string CONST_X_REMOVE_YOURSELF_FROM_THE_VEHICLE_BEEP_BEEP = "REMOVE YOURSELF FROM THE VEHICLE!   <BEEP!!> <BEEP!!>";


const string CONST_X_IS_BEHIND_THE_WHEEL_OF_A_ = " is behind the wheel of a ";
const string CONST_X_A_APPROACH_THE_DRIVERS_SIDE_DOOR = "A - Approach the driver's side door.";
const string CONST_X_LOOKS_FROM_A_DISTANCE_AT_AN_EMPTY_ = " looks from a distance at an empty ";
const string CONST_X_FOUND_A = " found a ";
const string CONST_X_LOOKS_AROUND_FOR_AN_ACCESSIBLE_VEHICLE = " looks around for an accessible vehicle...";
const string CONST_X_WAS_UNABLE_TO_GET_A_WHEELCHAIR_MAYBE_TOMORROW = " was unable to get a wheelchair.  Maybe tomorrow...";
const string CONST_X_HAS_PROCURED_A_WHEELCHAIR = " has procured a wheelchair.";
const string ACTIVITIES_FOLDER = "activities\\";

const string CONST_X_CANT_FIND_KEYS_NFS_TXT = "cant_find_keys_no_free_speech.txt";
const string CONST_X_CANT_FIND_KEYS_TXT = "cant_find_keys.txt";
const string CONST_X_ALMOST_HOTWIRE_TXT = "almost_hotwire_car.txt";
const string CONST_X_CANT_HOTWIRE_TXT = "cant_hotwire_car.txt";
const string CONST_X_GETS_NERVOUS_TXT = "gets_nervous.txt";
const string CONST_X_CAR_WONT_START_TXT = "car_wont_start.txt";
const string CONST_X_LOST_HAND_TO_HAND_TXT = "lose_hand_to_hand.txt";
const string CONST_X_WIN_HAND_TO_HAND_TXT = "win_hand_to_hand.txt";
const string CONST_X_ENEMY_WEBSITE_TXT = "enemy_website.txt";
const string CONST_X_WORDS_MEANING_HACKED_TXT = "words_meaning_hacked.txt";
const string CONST_X_QUALITY_50_TXT = "quality_50.txt";
const string CONST_X_QUALITY_35_TXT = "quality_35.txt";
const string CONST_X_QUALITY_20_TXT = "quality_20.txt";
const string CONST_X_QUALITY_0_TXT = "quality_0.txt";
const string CONST_X_S_BODY = "'s body";
const string CONST_X_BURYING_ = "burying ";

#endif	//ACTIVITIES_CPP
#ifdef	ADVANCE_CPP

// advance.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"

#include "sitedisplay.h"

#include "../log/log.h"

//#include "common/commondisplay.h"
void printparty();

#include "../common/commonactions.h"
// for void criminalizeparty(short crime)

#include "../combat/fight.h"
#include "../combat/fightCreature.h"  

//#include "combat/haulkidnap.h"
void squadgrab_immobile(char dead);
//#include "combat/haulkidnapCreature.h"

#include "../cursesAlternative.h"
#include "../set_color_support.h"

#include "../locations/locationsPool.h"
#include "../common/creaturePool.h"

void addLocationChange(int cursite, sitechangest change);
void squadgrab_immobile(char dead);
//// #include "combat/haulkidnapCreature.h"
void freehostage(DeprecatedCreature &cr, char situation);
void advancecreature(const int e);
bool isThereASiteAlarm();
void setSiteAlarmOne();
void resetSiteAlarm();

extern coordinatest loc_coord;
extern Deprecatednewsstoryst *sitestory;
extern Deprecatedsquadst *activesquad;
extern int ccs_boss_kills;
extern int ccs_siege_kills;
extern int sitecrime;
extern int stat_dead;
extern int stat_kills;
extern Log gamelog;
extern short lawList[LAWNUM];
extern short mode;
extern short postalarmtimer;
extern short sitealarmtimer;
extern short siteonfire;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];


vector<NameAndAlignment> getEncounterNameAndAlignment();
short getCurrentSite();
const string smellsPanic = "The Squad smells Conservative panic.";
const string ABLE_TO_SLOW_BLEEDING = " was able to slow the bleeding of";
const string sWounds = "'s wounds.";
const string isBurned = " is burned!";
const string drops = " drops ";
const string sBody = "'s body.";
const string tag_value = "value";

const string tag_attribute = "attribute";


const string tag_skill = "skill";

#endif	 //ADVANCE_CPP
#ifdef	ARMOR_CPP
// armor.cpp

#include "../items/itemtype.h"
#include "../items/item.h"
#include "../items/armortype.h"
#include "../items/armor.h"
//own header
#include "../common/stringconversion.h"
//for int stringtobool(std::string)
#include "../common/translateid.h"
// for  int getarmortype


const string CLOSE_BRACKET = "]";
const string OPEN_BRACKET = "[";
const string tag_D = "D";
const string tag_B = "B";
const string tag_X = "X";
const string tag_quality = "quality";
const string tag_false = "false";
const string tag_damaged = "damaged";
const string tag_true = "true";
const string tag_bloody = "bloody";
const string tag_blood = "blood";
const string tag_armor = "armor";
const string ruinedName = "Tattered Rags";

extern vector<ArmorType *> armortype;
#endif	//ARMOR_CPP
#ifdef	ARMORTYPE_CPP
// armortype.cpp
#include "../creature/creatureEnums.h"
//#include "../items/item.h"
#include "../items/itemtype.h"
//#include "../items/armor.h"
#include "../items/armortype.h"
//own header
#include "../common/stringconversion.h"
//for stringtobool

const string CONST_armortypeUNDEF = "UNDEF";
const string UNKNOWN_ELEMENT_FOR_ARMOR_TYPE = "Unknown element for armor type ";
const string COLON_INTERROGATION_ST = "::InterrogationST: ";
const string COLON_ARMOR = "::armor: ";
const string COLON_CONCEAL_FACE = "::body_covering::conceal_face: ";
const string INVALID_BOOLEAN_FOR_ARMOR = "Invalid boolean value for armor type ";
const string COLON_LEG_COVERING = "::body_covering::legs: ";
const string COLON_ARM_COVERING = "::body_covering::arms: ";
const string COLON_HEAD_COVERING = "::body_covering::head: ";
const string COLON_BODY_COVERING = "::body_covering::body: ";
const string COLON_FIREPROTECTION = "::armor::fireprotection: ";
const string COLON_DEATHSQUAD_LEGALITY = "::deathsquad_legality: ";

const string tag_durability = "durability";
const string tag_qualitylevels = "qualitylevels";
const string tag_quality = "quality";
const string tag_description = "description";
const string tag_surprise = "surprise";
const string tag_mask = "mask";
const string tag_stealth = "stealth";
const string tag_stealth_value = "stealth_value";
const string tag_conceal_weapon_size = "conceal_weapon_size";
const string tag_professionalism = "professionalism";
const string tag_drugbonus = "drugbonus";
const string tag_assaultbonus = "assaultbonus";
const string tag_basepower = "basepower";
const string tag_base = "base";
const string tag_interrogation = "interrogation";
const string tag_shortname = "shortname";
const string tag_conceals_face = "conceals_face";
const string tag_legs = "legs";
const string tag_arms = "arms";
const string tag_head = "head";
const string tag_body = "body";
const string tag_body_covering = "body_covering";
const string tag_fire = "fire";
const string tag_fireprotection = "fireprotection";
const string tag_limbs = "limbs";
const string tag_armor = "armor";
const string tag_can_get_damaged = "can_get_damaged";
const string tag_can_get_bloody = "can_get_bloody";
const string tag_deathsquad_legality = "deathsquad_legality";
const string tag_make_price = "make_price";
const string tag_make_difficulty = "make_difficulty";

map<string, int> armorTypeInitTags = {
	map<string, int>::value_type(tag_make_difficulty, ENUM_tag_make_difficulty),
	map<string, int>::value_type(tag_make_price, ENUM_tag_make_price),
	map<string, int>::value_type(tag_deathsquad_legality, ENUM_tag_deathsquad_legality),
	map<string, int>::value_type(tag_can_get_bloody, ENUM_tag_can_get_bloody),
	map<string, int>::value_type(tag_can_get_damaged, ENUM_tag_can_get_damaged),
	map<string, int>::value_type(tag_armor, ENUM_tag_armor),
	map<string, int>::value_type(tag_body_covering, ENUM_tag_body_covering),
	map<string, int>::value_type(tag_shortname, ENUM_tag_shortname),
	map<string, int>::value_type(tag_interrogation, ENUM_tag_interrogation),
	map<string, int>::value_type(tag_professionalism, ENUM_tag_professionalism),
	map<string, int>::value_type(tag_conceal_weapon_size, ENUM_tag_conceal_weapon_size),
	map<string, int>::value_type(tag_stealth_value, ENUM_tag_stealth_value),
	map<string, int>::value_type(tag_mask, ENUM_tag_mask),
	map<string, int>::value_type(tag_surprise, ENUM_tag_surprise),
	map<string, int>::value_type(tag_description, ENUM_tag_description),
	map<string, int>::value_type(tag_qualitylevels, ENUM_tag_qualitylevels),
	map<string, int>::value_type(tag_durability, ENUM_tag_durability),
};
extern int year;
#endif	//ARMORTYPE_CPP
#ifdef	AUGMENTATION_CPP
// augmentation.cpp
#include "augmentation.h"

const string CONSERVATIVE_BUG = "Conservative Swine! (Bug)";
const string CONST_X_SKIN = "Skin";
const string CONST_X_LEGS = "Legs";
const string CONST_X_ARMS = "Arms";
const string CONST_X_BODY = "Body";
const string CONST_X_HEAD = "Head";
const string tag_skin = "skin";
const string tag_effect = "effect";
const string tag_type = "type";
const string tag_name = "name";
const string tag_augmentation = "augmentation";

const string tag_value = "value";
const string tag_attribute = "attribute";

const string tag_legs = "legs";
const string tag_arms = "arms";
const string tag_body = "body";
const string tag_head = "head";

#endif	//AUGMENTATION_CPP
#ifdef	AUGMENTTYPE_CPP
// augmenttype.cpp

#include "augmentation.h"
#include "augmenttype.h"
//own header
#include "../log/log.h"
// for log
#include "../common/stringconversion.h"

const string LACKS_IDNAME_LOWERCASE = " lacks idname.";
const string AUGMENT_TYPE_SPACE = "Augment type ";
const string LACKS_IDNAME = "LACKS IDNAME ";

const string tag_difficulty = "difficulty";
const string tag_cost = "cost";
const string tag_min_age = "min_age";
const string tag_max_age = "max_age";
const string tag_description = "description";
const string tag_effect = "effect";
const string tag_attribute = "attribute";
const string tag_type = "type";
const string tag_name = "name";
const string tag_idname = "idname";
const string tag_id = "id";


map<string, int> augmentTags = {
	map<string, int>::value_type(tag_name, ENUM_tag_name),
	map<string, int>::value_type(tag_type, ENUM_tag_type),
	map<string, int>::value_type(tag_attribute, ENUM_tag_attribute),
	map<string, int>::value_type(tag_effect, ENUM_tag_effect),
	map<string, int>::value_type(tag_description, ENUM_tag_description),
	map<string, int>::value_type(tag_max_age, ENUM_tag_max_age),
	map<string, int>::value_type(tag_min_age, ENUM_tag_min_age),
	map<string, int>::value_type(tag_cost, ENUM_tag_cost),
	map<string, int>::value_type(tag_difficulty, ENUM_tag_difficulty),
};
extern Log xmllog;
#endif	//AUGMENTTYPE_CPP
#ifdef	AUTOMATEDDATATESTS_CPP
// automatedDataTests.cpp
#include "cursesAlternative.h"

extern map<short, string>  conservativeLegalArgument;
extern map<short, string>  youAreStupidTalkAboutIssues;
extern map<short, string>  issueTooLiberal;
extern map<short, string>  issueEventString;
extern map<short, string>  conservatiseLaw;
extern map<short, string>  liberalizeLaw;
extern map<short, string>  discussIssues;
extern map<short, string>  discussesIssues;
extern map<short, vector<string> >  talkAboutTheIssues; 
extern map<short, vector<string> >  endgameLawStrings; 
extern bool multipleCityMode;
extern short lawList[LAWNUM];
void testCreature();

const string CONST_X_TEST = "TEST";
const string SUCCESS = "SUCCESS";

#endif	//AUTOMATEDDATATESTS_CPP
#ifdef	BASEACTIONS_CPP
// baseactions.cpp


#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
//#include "../cursesgraphics.h"

#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
//#include "../common/getnames.h"
void enter_name(int, int, char*, int, const char*);
#include "../common/commondisplay.h"
// for void printparty(void)
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/creaturePool.h"

int getkey_cap_alt();
int lenVehiclePool();
int getCarID(const int l);
string getCarFullname(const int l);

extern char slogan[SLOGAN_LEN];
extern Deprecatedsquadst *activesquad;
extern string slogan_str;
extern vector<string> default_slogans;
extern short party_status;

const string VEHICLE_PARAGRAPH_TXT = "vehicleParagraph.txt";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string BE_A_PASSENGER = "be a passenger.";
const string DRIVE_IT = "drive it.";
const string CHOOSING_THE_RIGHT_LIBERAL_VEHICLE = "Choosing the Right Liberal Vehicle";
const string IN_SPOT_SPACE = " in Spot ";
const string CHOSE_SQUAD_MEMBER_TO_REPLACE = "Choose squad member to replace ";
const string CHOOSE_SQUAD_MEMBER_TO_MOVE = "Choose squad member to move";
const string MANY_SPACES_SOMETHING = "                                                                                          ";
const string WHAT_IS_YOUR_NEW_SLOGAN = "What is your new slogan?";

#endif	//BASEACTIONS_CPP
#ifdef	BASEMODE_CPP
// basemode.cpp
#include "../creature/creature.h"
////


#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
//#include "../pdcurses/curses.h"
#include "../cursesgraphics.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
//#include "../basemode/liberalagenda.h"
bool liberalagenda(signed char won);
#include "../basemode/baseactions.h"
//#include "../basemode/activate_sleepers.h"
void activate_sleepers();
//#include "../basemode/activate.h"
void activate();
//#include "../basemode/reviewmode.h"
void review();
#include "../common/translateid.h"
// for  int getsquad(int)
#include "../common/getnames.h"
// for std::string getmonth(int)
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
//for int mvaddstr(int, int, const char*)
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
//#include "../common/equipment.h"
void equip(vector<Item *> &loot, int loc);
//#include "../politics/politics.h"
bool stalinview(short view, bool islaw);
//#include "../monthly/monthly.h"
void passmonth(char &clearformess, char canseethings);
#include "../daily/daily.h"
//for int monthday();
#include "../daily/siege.h"
//for giveup()
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../common/musicClass.h"
#include "../common/creaturePool.h"
#include "../locations/locationsPool.h"
enum CantSeeReason
{
	CANTSEE_DATING = 1,
	CANTSEE_HIDING = 2,
	CANTSEE_OTHER = 3,
	CANTSEE_DISBANDING = 4
};
bool isPartOfJusticeSystem(int cursite);
bool isThisSafehouse(int loc);
extern bool stalinmode;
extern char cantseereason;
extern char disbanding;
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern class Ledger ledger;
extern Deprecatedsquadst *activesquad;
extern int day;
extern int disbandtime;
extern int month;
extern int selectedsiege;
extern int stat_burns;
extern int stat_buys;
extern int year;
extern Log gamelog;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short court[COURTNUM];
extern short exec[EXECNUM];
extern short execterm;
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short party_status;
extern short senate[SENATENUM];
extern string slogan_str;
extern vector<DeprecatedCreature *> pool;
extern vector<Deprecatedsquadst *> squad;
int countSafeHouses();
int lenVehiclePool();
Location* getLocation();
void addStringYear();
void burnFlagAtLocation(int l);
void equipLoot(int l, int loc);
void printFlag();


const string P_PATRIOTISM = "P - PATRIOTISM: fly a flag here ($20)";
const string P_PROTEST = "P - PROTEST: burn the flag";
const string S_FREE_SPEECH_LIBERAL_SLOGAN = "S - FREE SPEECH: the Liberal Slogan";
const string NEXT_MONTH = " (next month)";
const string W_WAIT_A_DAY = "W - Wait a day";
const string W_WAIT_OUT_SIEGE = "W - Wait out the siege";
const string CANNOT_WAIT_UNTIL_RESOLVED = "Cannot Wait until Siege Resolved";
const string X_LIVE_TO_FIGHT_ANOTHER_DAY = "X - Live to fight EVIL another day";
const string F_GO_FORTH_TO_STOP_EVIL = "F - Go forth to stop EVIL";
const string G_GIVE_UP = "G - Give Up";
const string F_ESCAPE_ENGAGE = "F - Escape/Engage";
const string C_CANCEL_DEPARTURE = "C - Cancel this Squad's Departure";
const string B_SLEEPERS = "B - Sleepers";
const string A_ACTIVATE_LIBERALS = "A - Activate Liberals";
const string L_STATUS_OF_AGENDA = "L - The Status of the Liberal Agenda";
const string Z_NEXT_LOCATION = "Z - Next Location";
const string TAB_NEXT_SQUAD = "TAB - Next Squad";
const string O_REORDER = "O - Reorder";
const string R_REVIEW_ASSETS_AND_FORM_SQUAD = "R - Review Assets and Form Squads";
const string V_VEHICLES = "V - Vehicles";
const string E_EQUIP_SQUAD = "E - Equip Squad";
const string PLANNING_HEADER = "컴� PLANNING 컴�";
const string ACTIVISM_HEADER = "컴� ACTIVISM 컴�";
const string COLONS_NO_DOTS = ":::::::::";
const string COLONS_AND_DOTS = ":.:.:.:.:";
const string NO_FOOD = " (No Food)";
const string UNDER_SIEGE = "Under Siege";
const string UNDER_ATTACK = "Under Attack";
const string I_INVEST_IN_LOCATION = "I - Invest in this location";

const string tag_Sta = "Sta, ";
const string tag_Libp = "Lib+, ";
const string tag_Lib = "Lib, ";
const string tag_Mod = "Mod, ";
const string tag_Cons = "Cons, ";
const string tag_Consp = "Cons+";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string HOUSE_COLON = "House: ";
const string SENATE_COLON = "Senate: ";
const string SUPREME_COURT_COLON = "Supreme Court: ";
const string MID_LENGTH_LINE = "컴컴컴컴컴컴컴컴";
const string PUBLIC_MOOD = "Public Mood";
const string LIBERTARIAN = "Libertarian";
const string STALINIST = "Stalinist";
const string CONSERVATIVE = "Conservative";
const string LIBERAL = "Liberal";
const string SECOND_TERM = ", 2nd Term";
const string FIRST_TERM = ", 1st Term";
const string PRESIDENT_COLON = "President: ";
const string R_RECREATE_THE_LCS_OR_WAIT_NEXT_MONTH = "R - Recreate the Liberal Crime Squad                  Any Other Key - Next Month";
const string IT_HAS_BEEN_WHILE = "It sure has been a while.  Things might have changed a bit.";
const string IT_HAS_BEEN_LONG_LOT_CHANGED = "It has been a long time.  A lot must have changed...";
const string HOW_LONG_SINCE_TIMES_HAVE_CHANGED = "How long since you've heard these sounds...  times have changed.";
const string TIME_PASSES = "Time passes...";

#endif	//BASEMODE_CPP
#ifdef	CHASE_CPP
// chase.cpp

#include "../creature/creature.h"
////


#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
//#include "basemode/baseactions.h"
void orderparty();
//#include "sitemode/advance.h"
void creatureadvance();
#include "../sitemode/sitedisplay.h"
//#include "sitemode/miscactions.h"
void reloadparty(bool wasteful = false);
#include "../log/log.h"
// for gamelog
#include "../common/translateid.h"
// for  int id_getcar(int)
#include "../common/commondisplay.h"
// for addstr (with log)
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
//#include "common/equipment.h"
void equip(vector<Item *> &loot, int loc);
#include "fight.h"
#include "fightCreature.h"  
// for void youattack();
#include "haulkidnapCreature.h"
// for  void kidnaptransfer(Creature &cr);
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"
#include "../common/creaturePool.h"
enum LOOP_CONTINUATION {
	RETURN_ZERO,
	RETURN_ONE,
	REPEAT
};
vector<NameAndAlignment> getEncounterNameAndAlignment();
void makecreature(const int x, const short type);
const string hereTheyCome = "Here they come!";
const string BEING_FOLLOWED = "being followed by Conservative swine!";
const string lostThem = "It looks like you've lost them!";
const string isSeized = " is seized, ";

const string CARCHASE_OBSTACLE_CHILD_TXT = "carchase_obstacle_child.txt";
const string CARCHASE_OBSTACLE_CROSS_TRAFFIC_TXT = "carchase_obstacle_cross_traffic.txt";
const string CARCHASE_OBSTACLE_TRUCK_PULLS_OUT_TXT = "carchase_obstacle_truck_pulls_out.txt";
const string CARCHASE_OBSTACLE_FRUIT_STAND_TXT = "carchase_obstacle_fruit_stand.txt";
const string CARCHASE_OBSTACLE_NONE_TXT = "carchase_obstacle_none.txt";
const string DIE_IN_CAR_TXT = "die_in_car.txt";
const string CAR_CRASH_FATALITIES_TXT = "car_crash_fatalities.txt";
const string CAR_CRASH_MODES_TXT = "car_crash_modes.txt";
const string CAR_PLOWS_THROUGH_TXT = "car_plows_through.txt";
const string CAR_SPEED_TXT = "car_speed.txt";

const string IS_STILL_ON_YOUR_TAIL = " is still on your tail!";
const string C_REFLECT_ON_YOUR_LACK_OF_SKILL = "C - Reflect on your lack of skill.";
const string F_FIGHT = "F - Fight!";
const string E_EQUIP = "E - Equip";
const string D_TRY_TO_LOSE_THEM = "D - Try to lose them!";

const string tag_POLICECAR = "POLICECAR";
const string tag_The = "The ";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string chase = "chase\\";
const string IS_FREE = " is free.";
const string S_ARE_FREE = "s are free.";
const string YOUR_HOSTAGE = "Your hostage";
const string YOU_PULL_OVER_AND_ARRESTED = "You pull over and are arrested.";
const string YOU_STOP_AND_ARE_ARRESTED = "You stop and are arrested.";
const string YOU_SCALE_A_SMALL_BUILDING = "You scale a small building and leap between rooftops!";
const string YOU_CLIMB_A_FENCE = "You climb a fence in record time!";
const string YOU_RUN_AS_FAST_AS_YOU_CAN = "You run as fast as you can!";
const string YOU_SUDDENLY_DART_INTO_ALLEY = "You suddenly dart into an alley!";
const string THROWN_TO_GROUND_AND_TAZED = "thrown to the ground, and tazed repeatedly!";
const string THROWN_TO_GROUND_TAZED_TO_DEATH = "thrown to the ground, and tazed to death!";
const string PUSHED_TO_GROUND_HANDCUFFED = "pushed to the ground, and handcuffed!";
const string THROWN_TO_GROUND_AND_SHOT = "thrown to the ground, and shot in the head!";
const string CRUSHED_BENEATH_TANK = " crushed beneath the tank's treads!";
const string THROWN_TO_GROUND_AND_BEATEN_SENSELESS = "thrown to the ground, and beaten senseless!";
const string THROWN_TO_GROUND_AND_BEATEN_DEAD = "thrown to the ground, and beaten to death!";
const string BREAKS_AWAY = " breaks away!";
const string CANT_KEEP_UP = " can't keep up!";
const string TIPS_INTO_A_POOL_TANK_IS_TRAPPED = " tips into a pool. The tank is trapped!";
const string CONST_X_G_GIVE_UP = "G - Give Up";
const string AS_YOU_EXIT_YOU_NOTICE = "As you exit the site, you notice that you are ";
const string BRAKES_HARD = " brakes hard and nearly crashes!";
const string BACKS_OFF = " backs off for safety.";
const string SKIDS_OUT = " skids out!";
const string FALLS_BEHIND = " falls behind!";
const string YOU_MAKE_OBSCENE_GESTURES = "You make obscene gestures at the pursuers!";
const string YOU_BOLDLY_WEAVE_THROUGH_TRAFFIC = "You boldly weave through oncoming traffic!";
const string CRAWLS_FREE_OF_CAR = " crawls free of the car, shivering with pain.";
const string GASPS_IN_PAIN_BUT_LIVES = " gasps in pain, but lives, for now.";
const string FEET_PERIOD = " feet.";
const string WHEELCHAIR_PERIOD = " wheelchair.";
const string AND_STRUGGLES_TO = " and struggles to ";
const string CAR_FRAME = "car frame";
const string GRIPS_THE_SPACE = " grips the ";
const string SEAT_OUT_COLD_AND_DIES = " seat, out cold, and dies.";
const string SLUMPS_IN = " slumps in ";
const string YOUR_SPACE = "Your ";
const string TAKES_OVER_THE_WHEEL = " takes over the wheel.";
const string YOU_SWERVE_TO_AVOID = "You swerve to avoid the obstacle!";
const string P_PULL_OVER = "P - Pull over";
const string B_BAIL_OUT = "B - Bail out and run!";
const string AS_YOU_PULL_AWAY_YOU_NOTICE = "As you pull away from the site, you notice that you are ";
const string STATIONWAGON = "STATIONWAGON";
const string CONST_X_PICKUP = "PICKUP";
const string CONST_X_JEEP = "JEEP";
const string CONST_X_SUV = "SUV";
const string AGENTCAR = "AGENTCAR";
const string CONST_X_HMMWV = "HMMWV";
//crashenemycar

const string HITS_A_PARKED_CAR = " hits a parked car and flips over.";
const string PERSON_INSIDE_IS_SQUASHED_INTO_CUBE = "The person inside is squashed into a cube.";
const string EVERYONE_INSIDE_PEELED_OFF_AGAINST_PAVEMENT = "Everyone inside is peeled off against the pavement.";
const string SPINS_OUT_AND_CRASHES = " spins out and crashes.";
const string SLAMS_INTO_BUILDING = " slams into a building.";
// obstacledrive

const string BOTH_SIDES_AVOID_ENDANGERING_CHILD = "Both sides refrain from endangering the child...";
const string CONSERVATIVES_UNLEASH_GUNFIRE = "The Conservative bastards unleash a hail of gunfire!";
const string YOU_SLOW_DOWN_AND_AVOID_KID = "You slow down and carefully avoid the kid.";
const string FRUIT_SELLER_IS_SQUASHED = "The fruit seller is squashed!";
const string FRUIT_SMASHES_ALL_OVER_WINDSHIELD = "Fruit smashes all over the windshield!";
const string YOU_SLOW_DOWN_AND_EVADE = "You slow down, and carefully evade the truck.";
const string YOU_SLOW_DOWN = "You slow down, and turn the corner.";

const int DRIVING_RANDOMNESS = 13;
extern char endgamestate;
extern char foughtthisround;
extern chaseseqst chaseseq;
extern DeprecatedCreature encounter[ENCMAX];
extern Deprecatednewsstoryst *sitestory;
extern Deprecatedsquadst *activesquad;
extern int stat_dead;
extern Log gamelog;
extern long cursquadid;
extern MusicClass music;
extern short fieldskillrate;
extern short lawList[LAWNUM];
extern short mode;
extern short party_status;
int baddieCount();
int baddieCount(const bool in_car);
int driveskill(DeprecatedCreature &cr, int v);
int encounterSize();
int getEncounterCarID(const int p);
Vehicle* getVehicleOfThisType(int cartype);
void addCreatueVehiclesToCollection(DeprecatedCreature *cr[6], vector<Vehicle *> &veh);
void conservatise(const int e);
void deleteVehicles(vector<Vehicle *>& carid);
void removeCreatureFromSquad(DeprecatedCreature &cr, int oldsqid);


void emptyEncounter();

vector<string> car_speed;
vector<string> car_plows_through;
vector<string> car_crash_modes;
vector<string> car_crash_fatalities;
vector<string> die_in_car;
vector<string> carchase_obstacle_none;
vector<string> carchase_obstacle_fruit_stand;
vector<string> carchase_obstacle_truck_pulls_out;
vector<string> carchase_obstacle_cross_traffic;
vector<string> carchase_obstacle_child;
vector<file_and_text_collection> chase_text_file_collection = {
	/*chase.cpp*/
	customText(&car_speed, chase + CAR_SPEED_TXT),
	customText(&car_plows_through, chase + CAR_PLOWS_THROUGH_TXT),
	customText(&car_crash_modes, chase + CAR_CRASH_MODES_TXT),
	customText(&car_crash_fatalities, chase + CAR_CRASH_FATALITIES_TXT),
	customText(&die_in_car, chase + DIE_IN_CAR_TXT),
	customText(&carchase_obstacle_none, MOSTLY_ENDINGS_FOLDER + CARCHASE_OBSTACLE_NONE_TXT),
	customText(&carchase_obstacle_fruit_stand, MOSTLY_ENDINGS_FOLDER + CARCHASE_OBSTACLE_FRUIT_STAND_TXT),
	customText(&carchase_obstacle_truck_pulls_out, MOSTLY_ENDINGS_FOLDER + CARCHASE_OBSTACLE_TRUCK_PULLS_OUT_TXT),
	customText(&carchase_obstacle_cross_traffic, MOSTLY_ENDINGS_FOLDER + CARCHASE_OBSTACLE_CROSS_TRAFFIC_TXT),
	customText(&carchase_obstacle_child, MOSTLY_ENDINGS_FOLDER + CARCHASE_OBSTACLE_CHILD_TXT),
};
map<short, vector<string> > carchaseObstacles;


#endif	//CHASE_CPP
#ifdef	CLIP_CPP
// clip.cpp
#include "../creature/creatureEnums.h"
#include "../items/itemtype.h"
#include "../items/item.h"
#include "../items/cliptype.h"
#include "../items/clip.h"
//own header
#include "../common/translateid.h"
// for  int getcliptype

const string UNKNOWN_ELEMENT_FOR_CLIP = "Unknown element for clip type ";

const string tag_ammo = "ammo";
const string tag_clip = "clip";

extern vector<ClipType *> cliptype;
#endif	//CLIP_CPP
#ifdef	COMMONACTIONS_CPP
// commonactions.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locationsEnums.h"
//#include "../pdcurses/curses.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../common/translateid.h"
// for  int getsquad(int)
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
// for makedelimeter
#include "../title/highscore.h"       
//for void savehighscore(char endtype)
#include "../politics/politics.h"
//for int publicmood(int l)
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/creaturePool.h"
/* end the game and clean up */
void end_game(int err = EXIT_SUCCESS);
//extern string singleSpace;
//extern string spaceDashSpace;
//extern string singleDot;

const string enterDash = "Enter - ";
const string selectA = "Press a Letter to select a ";
const string selectAn = "Press a Letter to select an ";

const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string HARMFUL_SPEECH = "harmful speech";
const string CONST_X_MONTH = "month";
const string CONST_X_MONTHS = "months";
const string FOR_SPACE = " for ";
const string WILL_BE_AT_SPACE = " will be at ";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string METHOD_OF_SORTING_TXT = "methodOfSorting.txt";
const string CHOOSE_HOW_TO_SORT_LIST = "Choose how to sort list of ";
const string DOLLARSIGN = "$";

short getCurrentSite();
extern short mode;
extern Deprecatedsquadst *activesquad;
extern vector<Deprecatedsquadst *> squad;
extern short activesortingchoice[SORTINGCHOICENUM];
extern class Ledger ledger;
extern Log gamelog;

#endif	//COMMONACTIONS_CPP
#ifdef	COMMONDISPLAY_CPP
// commondisplay.cpp
#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locationsEnums.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../sitemode/stealth.h"
#include "../common/getnames.h"
// for getmonth
#include "../common/translateid.h"
// for  int getcar(int)
#include "../common/commonactionsCreature.h"
// for void sortliberals(std::vector<Creature *>&,short,bool)
#include "../daily/siege.h"
// for statebrokenlaws(cr);
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"

std::string gettitle(const int align, const int juice);
bool isThereNoActivesquad();
bool isThereASiteAlarm();
void makedelimiter(int y = 8, int x = 0);
void printcreatureinfo(DeprecatedCreature *cr, unsigned char knowledge = 255);
void set_color_for_armor(const Armor armor);
void setColorForArmor(const Armor ar);
void statebrokenlaws(CreatureJustice cr, const int flag);

extern bool mapshowing;
extern char showcarprefs;
extern Deprecatedsquadst *activesquad;
extern int day;
extern int month;
extern int year;
extern short mode;
extern short party_status;
extern short sitealarmtimer;




const string CONST_X_SINGLE_COMMA = ",";
const string CONST_SpaceOpenParenthesis = " (";
const string NAME_COLON = "Name: ";
const string CODE_NAME_COLON = "Code name: ";
const string CONST_X_COLON_SPACE = ": ";
const string POINT_DOUBLE_ZERO = ".00";
const string NINETY_NINE_PLUS = "99+";
const string DOUBLE_ZERO = "00";
const string CONST_X_DOT = ".";
const string NOW_MAX = "NOW   MAX";
const string CONST_X_SKILL = "SKILL";
const string ON_FOOT = "On \"Foot\"";
const string CONST_X_ON_FOOT = "On Foot";
const string WHEEL_CHAIR = "Wheelchair";
const string CONST_X_DASH_D = "-D";
const string FIFTY_OR_SO_SPACES = "                                                                                ";
const string WEAPON_COLON = "Weapon: ";
const string CONST_X_CUT = "Cut";
const string BRUISED = "Bruised";
const string CONST_X_SHOT = "Shot";
const string CONST_commondisplay116 = "Liberal";
const string CONST_X_ANIMAL = "Animal";
const string SEVERED = "Severed";
const string RIPPED_OFF = "Ripped off";
const string LEFT_LEG_COLON = "Left Leg:";
const string RIGHT_LEG_COLON = "Right Leg:";
const string LEFT_ARM_COLON = "Left Arm:";
const string RIGHT_ARM_COLON = "Right Arm:";
const string BODY_COLON = "Body:";
const string HEAD_COLON = "Head:";
const string CLOTHES_COLON = "Clothes: ";
const string MISSING_TEETH = "Missing Teeth";
const string NO_TEETH = "No Teeth";
const string NO_TONGUE = "No Tongue";



const string tag_0 = "0";
const string CONST_X_LONG_LINE = "컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴";
const string SEVENTY_NINE_LINE = "컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컫컴컴컴컴컴컴컴컴컴컴컴컴컫";
const string CONST_commondisplay044 = "Moderate";
const string CONST_commondisplay043 = "Conservative";
const string CONSRVTV = "Consrvtv";
const string LIGHTLY_WOUNDED = "Lightly Wounded";
const string LTWOUND = "LtWound";
const string WOUNDED = "Wounded";
const string BADLY_WOUNDED = "Badly Wounded";
const string BADWOUND = "BadWound";
const string NEAR_DEATH = "Near Death";
const string NEAR_DETH = "NearDETH";
const string DECEASED = "Deceased";
const string ONE_LEG = "One Leg";
const string ONE_ARM = "One Arm";
const string ONE_ARM_ONE_LEG = "One Arm, One Leg";
const string ONEARMONELEG = "1Arm1Leg";
const string CONST_X_NO_LEGS = "No Legs";
const string CONST_X_NO_ARMS = "No Arms";
const string ONELIMB = "One Limb";
const string NOLIMBS = "No Limbs";
const string MISSING_EYE = "Missing Eye";
const string ONE_EYE = "One Eye";
const string MISSING_NOSE = "Missing Nose";
const string NOSEGONE = "NoseGone";
const string FACE_MUTILATED = "Face Mutilated";
const string FACEMUTL = "FaceMutl";
const string CONST_X_BLIND = "Blind";

const string MISTEETH = "MisTeeth";
const string NOTONGUE = "NoTongue";
const string FACE_GONE = "Face Gone";
const string FACEGONE = "FaceGone";
const string PARAPLEGIC = "Paraplegic";
const string PARAPLEG = "Parapleg";
const string QUADRAPLEGIC = "Quadraplegic";
const string QUADPLEG = "Quadpleg";
const string NECK_BROKEN = "Neck Broken";
const string NCKBROKE = "NckBroke";
const string QUESTION_MARK = "?";
const string CHAR_COLON = "Char:   ";
const string STR_COLON = "Str:    ";
const string AGI_COLON = "Agi:    ";
const string HLTH_COLON = "Hlth:   ";
const string WIS_COLON = "Wis:    ";
const string INT_COLON = "Int:    ";
const string HRT_COLON = "Hrt:    ";
const string AN_ANGRY_HANGIN_JUDGE = "an angry Hangin' Judge";
const string A_FRIGHTENED_EMINENT_SCIENTIST = "a frightened Eminent Scientist";
const string A_SMARMY_NEWS_ANCHOR = "a smarmy News Anchor";
const string A_CRYING_RADIO_PERSON = "a crying Radio Personality";
const string A_SQUIRMING_CEO = "a squirming CEO";
const string A_CURSING_POLITICIAN = "a cursing Politician";
const string CONST_X_BRN = "Brn";
const string CONST_X_TRN = "Trn";
const string CONST_X_BRS = "Brs";
const string CONST_X_SHT = "Sht";
const string CLEAN_SEVER = "Clean sever";
const string TOP_SKILLS_COLON = "Top Skills:";
const string SEVEN_QUESTION_MARKS = "???????";

const string TRANS_COLON = "Trans: ";

const string COMMA_HOLDING = ", holding ";
const string ONE_PARENTHESIS = " (1)";
const string X_X_PARENTHESIS = " (XX)";
const string CONST_X_SLASH = "/";
const string CONST_X_H = "+H";
const string CODENAME_SKILL_WEAPON_ARMOR_HEALTH_HEADER = "#횮ODE NAME컴컴컴컴컴컴SKILL컴훇EAPON컴컴컴컴횫RMOR컴컴컴컴컴HEALTH컴훂RANSPORT�";
const string CONST_X_BURNED = "Burned";
const string CONST_X_TORN = "Torn";
const string SCHEDULED_DATES = "Scheduled Dates:    ";
const string LETTER_S = "s";
const string ROMANTIC_INTEREST = " Romantic Interest";
const string SCHEDULED_MEETINGS = "Scheduled Meetings: ";
const string CANT_RECRUIT = "Can't Recruit";
const string ENLIGHTENED = "Enlightened ";
const string SPACE_MAX = " Max";
const string RECRUITS_SLASH = " Recruits / ";
const string CAR_COLON = "Car: ";
const string JUICE_COLON = "Juice: ";
const string ASTERISK = "*";
const string COMMA_GENDERQUEER = ", Genderqueer";
const string COMMA_FEMALE = ", Female";
const string COMMA_MALE = ", Male";
const string AGE_SPACE = " (Age ";
const string BORN_SPACE = "Born ";
//juiceuntillevelup


const string ONE_THOUSAND = "1000";
const string FIVE_HUNDRED = "500";
const string TWO_HUNDRED = "200";
const string ONE_HUNDRED = "100";
const string CONST_X_NUM_50 = "50";
const string CONST_X_NUM_10 = "10";
const string NEXT_COLON = "Next:  ";
//printcreatureattributes


const string CHARISMA_COLON = "Charisma: ";
const string STRENGTH_COLON = "Strength: ";
const string AGILITY_COLON = "Agility: ";
const string HEALTH_COLON = "Health: ";
const string WISDOM_COLON = "Wisdom: ";
const string INTELLIGENCE_COLON = "Intelligence: ";
const string HEART_COLON = "Heart: ";
//printliberalcrimes

const string CONST_X_NUM = "NUM";
const string CONST_X_CRIME = "CRIME";
const string MONTHS_IN_PRISON = " months in prison.";
const string SENTENCED_TO_SPACE = "Sentenced to ";
const string SERVING_SPACE = "Serving ";
const string SENTENCED_TO_LIFE_IN_PRISON = "Sentenced to life in prison";
const string SERVING_LIFE_IN_PRISON = "Serving life in prison";
const string SENTENCED_TO_DEATH = "Sentenced to DEATH";
const string ON_DEATH_ROW = "On DEATH ROW";
//fullstatus

const string WHAT_IS_NEW_CODENAME = "What is the new code name?                                                      ";
const string UP_DOWN_MORE_INFO = "    UP/DOWN  - More Info";
const string PRESS_KEY_TO_CONTINUE_STRUGGLE = "Press any other key to continue the Struggle";
const string LEFT_RIGHT_OTHER_LIBERALS = "    LEFT/RIGHT - Other Liberals";
const string N_CHANGE_CODENAME_G_FIX_GENDER_LABEL = "N - Change Code Name      G - Fix Gender Label";
const string PROFILE_OF_A_LIBERAL = "Profile of a Liberal";

map<int, map<bool, ColorSetup> > alignmentColors = {
	// Liberal activism
	map<int,  map<bool, ColorSetup> >::value_type(ALIGN_ARCHCONSERVATIVE,{ map<bool, ColorSetup>::value_type(true, RED_ON_BLACK_BRIGHT) }),
	map<int,  map<bool, ColorSetup> >::value_type(ALIGN_CONSERVATIVE,{ map<bool, ColorSetup>::value_type(true, MAGENTA_ON_BLACK_BRIGHT), map<bool, ColorSetup>::value_type(false, RED_ON_BLACK_BRIGHT) }),
	map<int,  map<bool, ColorSetup> >::value_type(ALIGN_MODERATE,{ map<bool, ColorSetup>::value_type(true, YELLOW_ON_BLACK_BRIGHT) }),
	map<int,  map<bool, ColorSetup> >::value_type(ALIGN_LIBERAL,{ map<bool, ColorSetup>::value_type(true, CYAN_ON_BLACK_BRIGHT), map<bool, ColorSetup>::value_type(false, GREEN_ON_BLACK_BRIGHT) }),
	map<int,  map<bool, ColorSetup> >::value_type(ALIGN_ELITELIBERAL,{ map<bool, ColorSetup>::value_type(true, GREEN_ON_BLACK_BRIGHT) }),
	map<int,  map<bool, ColorSetup> >::value_type(ALIGN_STALINIST,{ map<bool, ColorSetup>::value_type(true, RED_ON_BLACK_BRIGHT) }),
};
map<int, ColorSetup> activityColors = {
	// Liberal activism
	map<int, ColorSetup>::value_type(ACTIVITY_SLEEPER_LIBERAL, GREEN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_TROUBLE, GREEN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_GRAFFITI, GREEN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_DOS_ATTACKS, GREEN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_HACKING, GREEN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_WRITE_LETTERS, GREEN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_WRITE_GUARDIAN, GREEN_ON_BLACK_BRIGHT),
	// Recruitment
	map<int, ColorSetup>::value_type(ACTIVITY_RECRUITING, GREEN_ON_BLACK),
	// Less exciting liberal activities
	map<int, ColorSetup>::value_type(ACTIVITY_SLEEPER_SPY, BLUE_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_COMMUNITYSERVICE, BLUE_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_POLLS, BLUE_ON_BLACK_BRIGHT),
	// Stealing things
	map<int, ColorSetup>::value_type(ACTIVITY_SLEEPER_STEAL, CYAN_ON_BLACK),
	map<int, ColorSetup>::value_type(ACTIVITY_WHEELCHAIR, CYAN_ON_BLACK),
	map<int, ColorSetup>::value_type(ACTIVITY_STEALCARS, CYAN_ON_BLACK),
	// Illegal fundraising
	map<int, ColorSetup>::value_type(ACTIVITY_SLEEPER_EMBEZZLE, RED_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_SELL_DRUGS, RED_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_PROSTITUTION, RED_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_CCFRAUD, RED_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_DOS_RACKET, RED_ON_BLACK_BRIGHT),
	// Legal fundraising
	map<int, ColorSetup>::value_type(ACTIVITY_DONATIONS, CYAN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_SELL_TSHIRTS, CYAN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_SELL_ART, CYAN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_SELL_MUSIC, CYAN_ON_BLACK_BRIGHT),
	// Clothing/garment stuff
	map<int, ColorSetup>::value_type(ACTIVITY_REPAIR_ARMOR, CYAN_ON_BLACK),
	map<int, ColorSetup>::value_type(ACTIVITY_MAKE_ARMOR, CYAN_ON_BLACK),
	// Teaching
	map<int, ColorSetup>::value_type(ACTIVITY_TEACH_POLITICS, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_TEACH_FIGHTING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_TEACH_COVERT, MAGENTA_ON_BLACK_BRIGHT),
	//and studying
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_DEBATING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_MARTIAL_ARTS, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_DRIVING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_PSYCHOLOGY, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_FIRST_AID, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_LAW, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_DISGUISE, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_SCIENCE, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_BUSINESS, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_GYMNASTICS, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_ART, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_MUSIC, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_TEACHING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_WRITING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_LOCKSMITHING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_COMPUTERS, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_FENCING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_WEAVING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_RELIGION, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_CLUB, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_STREETSENSE, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_THROWING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_STEALTH, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_SEDUCTION, MAGENTA_ON_BLACK_BRIGHT),
	// Interrogating
	map<int, ColorSetup>::value_type(ACTIVITY_HOSTAGETENDING, YELLOW_ON_BLACK_BRIGHT),
	// Dealing with your injuries
	map<int, ColorSetup>::value_type(ACTIVITY_CLINIC, RED_ON_BLACK),
	// Doing something Conservative
	map<int, ColorSetup>::value_type(ACTIVITY_SLEEPER_CONSERVATIVE, RED_ON_BLACK_BRIGHT),
	// Dealing with the dead
	map<int, ColorSetup>::value_type(ACTIVITY_BURY, BLACK_ON_BLACK_BRIGHT),
	// Nothing terribly important
	map<int, ColorSetup>::value_type(ACTIVITY_HEAL, WHITE_ON_BLACK),// Identical to none in practice
	map<int, ColorSetup>::value_type(ACTIVITY_NONE, WHITE_ON_BLACK),
	map<int, ColorSetup>::value_type(ACTIVITYNUM, WHITE_ON_BLACK),
	// Going somewhere
	map<int, ColorSetup>::value_type(ACTIVITY_VISIT, YELLOW_ON_BLACK_BRIGHT),
	// Quitting being a sleeper to join the LCS
	map<int, ColorSetup>::value_type(ACTIVITY_SLEEPER_JOINLCS, RED_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_AUGMENT, BLUE_ON_BLACK_BRIGHT),
};
/* checks if a creature's weapon is suspicious or illegal */
char weaponcheck(const DeprecatedCreature &cr, bool metaldetect = false);
/* checks if a creature's uniform is appropriate to the location */
char hasdisguise(const DeprecatedCreature &cr);
string getVehicleShortname(int i);
map<int, string> prisoner_description = {
	map<int, string>::value_type(CREATURE_POLITICIAN, A_CURSING_POLITICIAN),
	map<int, string>::value_type(CREATURE_CORPORATE_CEO, A_SQUIRMING_CEO),
	map<int, string>::value_type(CREATURE_RADIOPERSONALITY, A_CRYING_RADIO_PERSON),
	map<int, string>::value_type(CREATURE_NEWSANCHOR, A_SMARMY_NEWS_ANCHOR),
	map<int, string>::value_type(CREATURE_SCIENTIST_EMINENT, A_FRIGHTENED_EMINENT_SCIENTIST),
	map<int, string>::value_type(CREATURE_JUDGE_CONSERVATIVE, AN_ANGRY_HANGIN_JUDGE),
};
vector<string> printSpecialWounds(const char special[SPECIALWOUNDNUM]);
#endif	//COMMONDISPLAY_CPP
#ifdef	CONFIGFILE_CPP
// configfile.cpp

#include "../items/itemtype.h"
#include "../items/item.h"
// needed for locations
#include "../locations/locations.h"
#include "../configfile.h"
//own header
#include "../cursesAlternative.h"
//extern string singleSpace;
const string ATTEMPTING_TO_OPEN = "Attempting to open filename: ";

const string SPECIALS_CSV = "_Specials.csv";
const string TILES_CSV = "_Tiles.csv";
const string MAPCSV_BANK2_TILES_CSV = "mapCSV_Bank2_Tiles.csv";
const string MAPCSV_BANK_TILES_CSV = "mapCSV_Bank_Tiles.csv";
const string MAPCSV_ = "mapCSV_";
const string CONST_X_OBJECT = "OBJECT";

extern char artdir[MAX_PATH_SIZE];
extern siteblockst levelmap[MAPX][MAPY][MAPZ];

map<int, SpecialBlocks> mapCBSpecial = {
	map<int, SpecialBlocks>::value_type(0,  SPECIAL_NONE),
	map<int, SpecialBlocks>::value_type(1,  SPECIAL_LAB_COSMETICS_CAGEDANIMALS),
	map<int, SpecialBlocks>::value_type(2,  SPECIAL_LAB_GENETIC_CAGEDANIMALS),
	map<int, SpecialBlocks>::value_type(3,  SPECIAL_POLICESTATION_LOCKUP),
	map<int, SpecialBlocks>::value_type(4,  SPECIAL_COURTHOUSE_LOCKUP),
	map<int, SpecialBlocks>::value_type(5,  SPECIAL_COURTHOUSE_JURYROOM),
	map<int, SpecialBlocks>::value_type(6,  SPECIAL_PRISON_CONTROL),
	map<int, SpecialBlocks>::value_type(7,  SPECIAL_PRISON_CONTROL_LOW),
	map<int, SpecialBlocks>::value_type(8,  SPECIAL_PRISON_CONTROL_MEDIUM),
	map<int, SpecialBlocks>::value_type(9,  SPECIAL_PRISON_CONTROL_HIGH),
	map<int, SpecialBlocks>::value_type(10,  SPECIAL_INTEL_SUPERCOMPUTER),
	map<int, SpecialBlocks>::value_type(11,  SPECIAL_SWEATSHOP_EQUIPMENT),
	map<int, SpecialBlocks>::value_type(12,  SPECIAL_POLLUTER_EQUIPMENT),
	map<int, SpecialBlocks>::value_type(13,  SPECIAL_NUCLEAR_ONOFF),
	map<int, SpecialBlocks>::value_type(14,  SPECIAL_HOUSE_PHOTOS),
	map<int, SpecialBlocks>::value_type(15,  SPECIAL_HOUSE_CEO),
	map<int, SpecialBlocks>::value_type(16,  SPECIAL_CORPORATE_FILES),
	map<int, SpecialBlocks>::value_type(17,  SPECIAL_RADIO_BROADCASTSTUDIO),
	map<int, SpecialBlocks>::value_type(18,  SPECIAL_NEWS_BROADCASTSTUDIO),
	map<int, SpecialBlocks>::value_type(19,  SPECIAL_APARTMENT_LANDLORD),
	map<int, SpecialBlocks>::value_type(20,  SPECIAL_SIGN_ONE),
	map<int, SpecialBlocks>::value_type(21,  SPECIAL_RESTAURANT_TABLE),
	map<int, SpecialBlocks>::value_type(22,  SPECIAL_CAFE_COMPUTER),
	map<int, SpecialBlocks>::value_type(23,  SPECIAL_PARK_BENCH),
	map<int, SpecialBlocks>::value_type(24,  SPECIAL_STAIRS_UP),
	map<int, SpecialBlocks>::value_type(25,  SPECIAL_STAIRS_DOWN),
	map<int, SpecialBlocks>::value_type(26,  SPECIAL_CLUB_BOUNCER),
	map<int, SpecialBlocks>::value_type(27,  SPECIAL_CLUB_BOUNCER_SECONDVISIT),
	map<int, SpecialBlocks>::value_type(28,  SPECIAL_ARMORY),
	map<int, SpecialBlocks>::value_type(29,  SPECIAL_DISPLAY_CASE),
	map<int, SpecialBlocks>::value_type(30,  SPECIAL_SIGN_TWO),
	map<int, SpecialBlocks>::value_type(31,  SPECIAL_SIGN_THREE),
	map<int, SpecialBlocks>::value_type(32,  SPECIAL_SECURITY_CHECKPOINT),
	map<int, SpecialBlocks>::value_type(33,  SPECIAL_SECURITY_METALDETECTORS),
	map<int, SpecialBlocks>::value_type(34,  SPECIAL_SECURITY_SECONDVISIT),
	map<int, SpecialBlocks>::value_type(35,  SPECIAL_BANK_VAULT),
	map<int, SpecialBlocks>::value_type(36,  SPECIAL_BANK_TELLER),
	map<int, SpecialBlocks>::value_type(37,  SPECIAL_BANK_MONEY),
	map<int, SpecialBlocks>::value_type(38,  SPECIAL_CCS_BOSS),
	map<int, SpecialBlocks>::value_type(39,  SPECIAL_OVAL_OFFICE_NW),
	map<int, SpecialBlocks>::value_type(40,  SPECIAL_OVAL_OFFICE_NE),
	map<int, SpecialBlocks>::value_type(41,  SPECIAL_OVAL_OFFICE_SW),
	map<int, SpecialBlocks>::value_type(42,  SPECIAL_OVAL_OFFICE_SE),
};
#endif	//CONFIGFILE_CPP
#ifdef	CREATURE_CPP
// creature.cpp

#include "../creature/creature.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../sitemode/stealth.h"
// for hasdisguise
//#include "../common/stringconversion.h"
string attribute_enum_to_string(int attribute);
#include "../common/translateid.h"
// for  int getweapontype(int )
//#include "../politics/politics.h"
/* politics -- promotes the Vice President to President, and replaces VP */
void promoteVP();
//only use here. --Schmel924
#include "../combat/chaseCreature.h"
//for Vehicle* getChaseVehicle(const Creature &c);
		//hmm --Schmel924
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"

const string LETTER_Z = "z";

const string LETTER_X = "x";

const string SLASH_MARK = "/";
const string CONST_X_SELVES = "selves";
const string THEM_LOWERCASE = "them";
const string HER_LOWERCASE = "her";
const string THEMSELF_LOWERCASE = "themself";
const string HERS_LOWERCASE = "hers";
const string HE_AND_SHE = "heANDshe";
const string XYR_LOWERCASE = "xyr";
const string XEM_LOWERCASE = "xem";
const string CONST_X_QUESTION_MARK = "?";
const string COMMA_AMBIGUOUS = ", Ambiguous";
const string CONST_X_FEMALE = ", Female";
const string CONST_X_MALE = ", Male";
const string VERY_OLD = "Very Old";
const string EIGHTIES = "80s";
const string SEVENTIES = "70s";
const string SIXTIES = "60s";
const string FIFTIES = "50s";
const string FORTIES = "40s";
const string THIRTIES = "30s";
const string TWENTIES = "20s";
const string SPACE_PARENTHESIS = " (";
const string PARENTHESIS_QUESTION = " (?)";
const string CONST_X_NONE = "None";
const string ZERO_OVER = " (0/";
const string ONE_OVER = " (1/";
const string CONST_X_SELF = "self";
const string XEMSELF_LOWERCASE = "xemself";
const string CONST_X_XEM = "Xem";
const string CONST_X_HER = "Her";
const string CONST_X_HIM = "Him";
const string CONST_X_S = "s";
const string CONST_X_XYRS = "xyrs";
const string CONST_X_XYR = "Xyr";
const string CONST_X_HIS = "His";
const string XE_LOWERCASE = "xe";
const string XE_SPACE = "Xe";
const string SHE_SPACE = "She";
const string HE_SPACE = "He";
const string CONST_X_PRESIDENT_ = "President ";
const string CCS_HEAVY = "CCS Heavy";
const string SOLDIER = "Soldier";
const string ELITE_SECURITY = "Elite Security";
const string ENLIGHTENED_JUDGE = "Enlightened Judge";
const string NEW_UNION_WORKER = "New Union Worker";
const string JADED_LIBERAL_JUDGE = "Jaded Liberal Judge";
const string EX_UNION_WORKER = "Ex-Union Worker";
const string IMPOSSIBLE = ", IMPOSSIBLE";
const string DIFFICULTY = ", Difficulty ";
const string SKILL_CHECK = " SkillCheck(";
const string OUTCOME_OF_SPACE = ", Outcome of ";
const string ADJUSTED_ATTRIBUTE_VALUE = "Adjusted Attribute Value ";
const string AUTOMATIC_FAILURE = "automatic failure";
const string SKILL_VALUE = ", Skill Value ";
const string SKILL_ROLL = " SkillRoll(";
const string ILLEGAL_SKILL_ROLL = "-=ILLEGAL SKILL ROLL=-";
const string ATTRIBUTE_CHECK = " AttributeCheck(";
const string ATTRIBUTE_LEVEL = ", Attribute Level ";
const string ATTRIBUTE_ROLL = " AttributeRoll(";
const string PERCENT_F = "%f";
const string SCRUFFY_UNNAMED_JANITOR = "ScruffyUnnamedJanitor";
const string CONST_CREATURE_WORKER_JANITOR = "CREATURE_WORKER_JANITOR";
const string CCS_COVERNAME_OTHER_TXT = "ccs_covername_other.txt";
const string CCS_COVERNAME_SHOTGUN_TXT = "ccs_covername_shotgun.txt";
const string HE_LOWERCASE = "he";
const string SHE_LOWERCASE = "she";
const string HIS_LOWERCASE = "his";
const string CONST_X_HER_LOWERCASE = "her";
const string CONST_X_XYR_LOWERCASE = "xyr";
const string HIM_LOWERCASE = "him";
const string CONST_X_XEM_LOWERCASE = "xem";

const string tag_value = "value";
const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_NONE = "ARMOR_NONE";
const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_NONE = "WEAPON_NONE";
const string tag_Pres = "Pres";
const string tag_Pres_state = "Pres_state";
const string tag_Pres_ID = "Pres_ID";
const string tag_CEO = "CEO";
const string tag_CEO_state = "CEO_state";
const string tag_CEO_ID = "CEO_ID";
const string tag_uniquecreatures = "uniquecreatures";
const string tag_WEAPON_SHOTGUN_PUMP = "WEAPON_SHOTGUN_PUMP";
const string tag_ARMOR_HEAVYARMOR = "ARMOR_HEAVYARMOR";
const string tag_ARMOR_ARMYARMOR = "ARMOR_ARMYARMOR";
const string tag_ARMOR_CIVILLIANARMOR = "ARMOR_CIVILLIANARMOR";
const string tag_reports_to_police = "reports_to_police";
const string tag_kidnap_resistant = "kidnap_resistant";
const string tag_talkreceptive = "talkreceptive";
const string tag_seethroughstealth = "seethroughstealth";
const string tag_seethroughdisguise = "seethroughdisguise";
const string tag_dontname = "dontname";
const string tag_flag = "flag";
const string tag_pref_is_driver = "pref_is_driver";
const string tag_pref_carid = "pref_carid";
const string tag_is_driver = "is_driver";
const string tag_carid = "carid";
const string tag_arg = "arg";
const string tag_arg2 = "arg2";
const string tag_type = "type";
const string tag_activity = "activity";
const string tag_base = "base";
const string tag_cantbluff = "cantbluff";
const string tag_worklocation = "worklocation";
const string tag_location = "location";
const string tag_crimes_suspected = "crimes_suspected";
const string tag_special = "special";
const string tag_blood = "blood";
const string tag_wound = "wound";
const string tag_income = "income";
const string tag_juice = "juice";
const string tag_money = "money";
const string tag_has_thrown_weapon = "has_thrown_weapon";
const string tag_stunned = "stunned";
const string tag_forceinc = "forceinc";
const string tag_meetings = "meetings";
const string tag_hireid = "hireid";
const string tag_id = "id";
const string tag_deathdays = "deathdays";
const string tag_joindays = "joindays";
const string tag_deathpenalty = "deathpenalty";
const string tag_confessions = "confessions";
const string tag_sentence = "sentence";
const string tag_prisoner = "prisoner";
const string tag_trainingsubject = "trainingsubject";
const string tag_trainingtime = "trainingtime";
const string tag_hiding = "hiding";
const string tag_dating = "dating";
const string tag_clinic = "clinic";
const string tag_specialattack = "specialattack";
const string tag_animalgloss = "animalgloss";
const string tag_infiltration = "infiltration";
const string tag_type_idname = "type_idname";
const string tag_alive = "alive";
const string tag_align = "align";
const string tag_exists = "exists";
const string tag_birthday_day = "birthday_day";
const string tag_birthday_month = "birthday_month";
const string tag_age = "age";
const string tag_squadid = "squadid";
const string tag_gender = "gender";
const string tag_gender_liberal = "gender_liberal";
const string tag_gender_conservative = "gender_conservative";
const string tag_propername = "propername";
const string tag_name = "name";
const string tag_skill_experience = "skill_experience";
const string tag_skill = "skill";
const string tag_creature = "creature";
const string tag_clip = "clip";
const string tag_augmentation = "augmentation";
const string tag_armor = "armor";
const string tag_weapon = "weapon";
const string tag_attribute = "attribute";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string creature = "creature\\";

vector<string> ccs_covername_shotgun;
vector<string> ccs_covername_other;
vector<file_and_text_collection> creature_text_file_collection = {
	/*creature.cpp*/
	customText(&ccs_covername_shotgun, creature + CCS_COVERNAME_SHOTGUN_TXT),
	customText(&ccs_covername_other, creature + CCS_COVERNAME_OTHER_TXT),
};

char hasdisguise(const DeprecatedCreature &cr);

extern Log gamelog;
extern bool SHOWMECHANICS;
extern bool ZEROMORAL;
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern char oldPresidentName[POLITICIAN_NAMELEN];
extern short exec[EXECNUM];
extern long curcreatureid;
extern UniqueCreatures uniqueCreatures;

#endif	//CREATURE_CPP
#ifdef	CREATURENAMES_CPP
// creaturenames.cpp

const string ARCHCONSERVATIVE_LAST_NAMES_TXT = "archconservative_last_names.txt";
const string REGULAR_LAST_NAMES_TXT = "regular_last_names.txt";
const string GWMP_FIRST_NAMES_TXT = "great_white_male_patriarch_first_names.txt";
const string GENDER_NEUTRAL_FIRST_NAMES_TXT = "gender_neutral_first_names.txt";
const string FEMALE_FIRST_NAMES_TXT = "female_first_names.txt";
const string MALE_FIRST_NAMES_TXT = "male_first_names.txt";
const string names = "names\\";
#endif	//CREATURENAMES_CPP
#ifdef	CREATUREPOOL_CPP
// creaturePool.cpp


#include "../creature/creature.h"

#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../common/creaturePool.h"
#include "../common/creaturePoolCreature.h"
#include "../cursesAlternative.h"
#include "../log/log.h"
#include "../sitemode/advance.h"
/* handles end of round stuff for one creature */
void advancecreature(DeprecatedCreature &cr);
#include "../common/commonactionsCreature.h"
#include "../combat/fightCreature.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"
#include "../set_color_support.h"
#include "../common/commondisplay.h"
#include "../common/commondisplayCreature.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../common/getnames.h"
#include "../common/translateid.h"
// for  int getpoolcreature(int)
#include "../daily/siege.h"
#include "../common/commonactions.h"

const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_PRISONER = "ARMOR_PRISONER";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

const string THE_LIBERAL_IS_NOW_A_NORMAL_SQUAD_MEMBER = "The Liberal is now at your command as a normal squad member.";
const string HAS_BEEN_OUTED_BY_YOUR_ATTACK = " has been outed by your bold attack!";
const string THIS_WHOLE_THING_WAS_A_MISTAKE = "This whole thing was a mistake. There won't be another meeting.";
const string COMESOFF_AS_INSANE = " comes off as slightly insane.";
const string NEEDS_MORE_EXPERIENCE = " needs more experience.";
const string CONST_X_MAYBE_ = "Maybe ";
const string REALLY_UNDERSTANDS_PROBLEM = " really understands the problem.";
const string ISNT_CONVINCED = " isn't convinced ";
const string THEYLL_MEET_AGAIN_MAYBE = "They'll meet again tomorrow.";
const string S_ARGUMENTS = "'s arguments.";
const string IS_SKEPTICAL_ABOUT = " is skeptical about some of ";
const string THEYLL_MEET_AGAIN = "They'll definitely meet again tomorrow.";
const string S_VIEWS_INSIGHTFUL = "'s views to be insightful.";
const string FOUND_SPACE = " found ";
const string VIEWS_ON = " views on ";
const string EXPLAINS_SPACE = " explains ";
const string SHARES_SPACE = " shares ";
const string ACCEPTS_AND_IS_EAGER = " accepts, and is eager to get started.";
const string JOIN_THE_LIBERAL_CRIME_SQUAD = " join the Liberal Crime Squad.";
const string OFFERS_TO_LET = " offers to let ";
const string D_BREAK_OFF_MEETINGS = "D - Break off the meetings.";
const string ISNT_READY_TO_JOIN = " isn't ready to join the LCS.";
const string CONST_X_C_DASH = "C - ";
const string NEEDS_MORE_JUICE_TO_RECRUIT = " needs more Juice to recruit.";
const string JOIN_THE_LCS = " join the LCS as a full member.";
const string C_OFFER_TO_LET = "C - Offer to let ";
const string B_CASUALLY_CHAT = "B - Just casually chat with them and discuss politics.";
const string A_SPEND_FIFTY_DOLLARS = "A - Spend $50 on props and a book for them to keep afterward.";
const string APPROACH_THE_SITUATION = " approach the situation?";
const string HOW_SHOULD_SPACE = "How should ";
const string KIND_OF_REGRETS_AGREEING = " kind of regrets agreeing to this.";
const string IS_READY_TO_FIGHT = " is ready to fight for the Liberal Cause.";
const string FEELS_SOMETHING_MUST_BE_DONE = " feels something needs to be done.";
const string IS_INTERESTED_IN_LEARNING_MORE = " is interested in learning more.";
const string WILL_TAKE_A_LOT_OF_PERSUADING = " will take a lot of persuading.";
const string MEETING_WITH_SPACE = "Meeting with ";
const string EXCLAMATION_POINT = "!";
const string GET_IT_TOGETHER_COMMA = "Get it together, ";
const string DUE_TO_MULTIPLE_BOOKING_OR_RECRUITMENT = "due to multiple booking of recruitment sessions.";
const string ACCIDENTALLY_MISSED_THE_MEETING_WITH = " accidentally missed the meeting with ";
const string HAS_ESCAPED = " has escaped!";
const string S_INJURIES_REQUIRE_PROFESSIONAL = "'s injuries require professional treatment.";
const string HAS_DIED_OF_INJURIES = " has died of injuries.";
const string HAS_LOST_TOUCH_WITH_LCS = " has lost touch with the Liberal Crime Squad.";
const string HAS_ABANDONED_THE_LCS = " has abandoned the LCS.";
const string THE_LIBERAL_HAS_GONE_INTO_HIDING = "The Liberal has gone into hiding...";
const string HAS_LEFT = " has left ";
const string HAS_BEEN_TRANSFERRED_TO = " has been transferred to ";

const string IS_MOVED_TO_THE_COURTHOUSE = " is moved to the courthouse for trial.";
const string THE_TRAITOR_WILL_TESTIFY = "The traitor will testify in court, and safehouses may be compromised.";
const string HAS_BROKEN_AND_RATTED_YOU_OUT = " has broken under the pressure and ratted you out!";
const string DEPORTATION = "deportation.";
const string EXECUTION = "execution.";
const string HAS_BEEN_SHIPPED_OUT_TO_THE_INS = " has been shipped out to the INS to face ";
const string S_MIND_WITH_CONSERVATISM = "'s mind with Conservatism!";
const string COPS_RE_POLLUTED = "Cops re-polluted ";
const string IS_THE_NEW_LEADER_OF_LCS = " is the new leader of the Liberal Crime Squad!";
const string HAS_DIED = " has died.";
const string IN_THE_COMMAND_CHAIN = " in the command chain.";
const string WILL_TAKE_OVER_FOR = " will take over for ";
const string DUE_TO_THE_DEATH_OF = "due to the death of ";
const string HAS_PROMOTED = " has promoted ";
const string THERE_ARE_NONE_WHO_CAN_LEAD = "There are none left with the courage and conviction to lead....";

enum LOOP_CONTINUATION {
	RETURN_ZERO,
	RETURN_ONE,
	REPEAT
};



enum DispersalTypes
{
	DISPERSAL_SAFE = -1,
	DISPERSAL_BOSSSAFE,
	DISPERSAL_NOCONTACT,
	DISPERSAL_BOSSINPRISON,
	DISPERSAL_HIDING,
	DISPERSAL_BOSSINHIDING,
	DISPERSAL_ABANDONLCS
};
extern Log gamelog;
extern char disbanding;
extern int stat_recruits;
extern class Ledger ledger;
extern vector<Deprecatedsquadst *> squad;
extern MusicClass music;
extern short lawList[LAWNUM];

//#include "../monthly/justice.h"
void trial(DeprecatedCreature &g);
char prison(DeprecatedCreature &g);
//#include "../monthly/sleeper_update.h"
void sleepereffect(DeprecatedCreature &cr, char &clearformess, char canseethings, int(&libpower)[VIEWNUM]);
void savehighscore(char endtype);
void viewhighscores(int musicoverride = MUSIC_OFF);
void end_game(int err = EXIT_SUCCESS);
short getCurrentSite();
#endif	//CREATUREPOOL_CPP
#ifdef	CREATURETYPE_CPP
// creaturetype.cpp

const string NONE = "NONE";
const string CONST_creaturetypeB086 = ": ";
const string CONST_X_LACKS_IDNAME = " lacks idname.";
const string CONST_X_COMMA_SPACE = ", ";
const string CONST_X_IN_ = " in ";
const string FIREMAN = "Fireman";
const string CAR_SALESMAN = "Car Salesman";
const string MIGRANT_WORKER = "Migrant Worker";
const string CUSTODIAN = "Custodian";
const string CONST_X_SLAVE = "Slave";
const string TYPE_NAME_NOT_DEFINED = "type_name not defined for ";
const string UNKNOWN_ELEMENT = "Unknown element for ";
const string INVALID_ARMORTYPE = "Invalid armor type for ";
const string UNKNOWN_SKILL = "Unknown skill for ";
const string INVALID_GENDER = "Invalid gender for ";
const string UNKNOWN_ATTRIBUTE = "Unknown attribute in ";
const string INVALID_ALIGNMENT = "Invalid alignment for ";
const string CREATURE_TYPE = "Creature type ";
const string CONST_X_LACKS_IDNAME__ALLCAPS = "LACKS IDNAME ";
const string INVALID_CLIP_TYPE = "Invalid clip type for ";
const string CAN_NOT_BE_USED_BY = "can not be used by ";
const string IN_SPACE = "In ";
const string INVALID_WEAPON_TYPE = "Invalid weapon type for ";
const string UNKNOWN_ELEMENT_FOR_WEAPON = "Unknown element for weapon in ";
const string INVALID_INTERVAL = "Invalid interval for ";

const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_NONE = "ARMOR_NONE";
const string tag_CLIP_45 = "CLIP_45";
const string tag_CLIP = "CLIP";
const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_SEMIPISTOL_45 = "WEAPON_SEMIPISTOL_45";
const string tag_CLIP_9 = "CLIP_9";
const string tag_WEAPON_SEMIPISTOL_9MM = "WEAPON_SEMIPISTOL_9MM";
const string tag_CLIP_38 = "CLIP_38";
const string tag_WEAPON_REVOLVER_38 = "WEAPON_REVOLVER_38";
const string tag_WEAPON_NONE = "WEAPON_NONE";
const string tag_CIVILIAN = "CIVILIAN";
const string tag_type = "type";
const string tag_type_name = "type_name";
const string tag_encounter_name = "encounter_name";
const string tag_creature = "creature";
const string tag_weapon = "weapon";
const string tag_armor = "armor";
const string tag_skills = "skills";
const string tag_skill = "skill";
const string tag_money = "money";
const string tag_infiltration = "infiltration";
const string tag_gender = "gender";
const string tag_juice = "juice";
const string tag_attributes = "attributes";
const string tag_attribute = "attribute";
const string tag_attribute_points = "attribute_points";
const string tag_SENIOR = "SENIOR";
const string tag_MI = "MI";
const string tag_MIDDLEAGED = "MIDDLEAGED";
const string tag_GRADUATE = "GRADUATE";
const string tag_MATURE = "MATURE";
const string tag_Y = "Y";
const string tag_YOUNGADULT = "YOUNGADULT";
const string tag_TEENAGER = "TEENAGER";
const string tag_CHILD = "CHILD";
const string tag_CHI = "CHI";
const string tag_D = "D";
const string tag_DOGYEARS = "DOGYEARS";
const string tag_age = "age";
const string tag_CONSERVATIVE = "CONSERVATIVE";
const string tag_MODERATE = "MODERATE";
const string tag_LIBERAL = "LIBERAL";
const string tag_PUBLIC_MOOD = "PUBLIC MOOD";
const string tag_align = "align";
const string tag_alignment = "alignment";
const string tag_idname = "idname";
const string tag_id = "id";
const string tag_APPROPRIATE = "APPROPRIATE";
const string tag_number_clips = "number_clips";
const string tag_clip = "clip";
const string tag_cliptype = "cliptype";
const string tag_number_weapons = "number_weapons";
const string tag_value = "value";
const string tag_CLIP_BUCKSHOT = "CLIP_BUCKSHOT";
const string tag_CLIP_SMG = "CLIP_SMG";
const string tag_CLIP_ASSAULT = "CLIP_ASSAULT";
const string tag_WEAPON_AUTORIFLE_AK47 = "WEAPON_AUTORIFLE_AK47";
const string tag_CLIP_44 = "CLIP_44";
const string tag_WEAPON_AXE = "WEAPON_AXE";
const string tag_CLIP_GASOLINE = "CLIP_GASOLINE";
const string tag_WEAPON_TORCH = "WEAPON_TORCH";
const string tag_WEAPON_PITCHFORK = "WEAPON_PITCHFORK";
const string tag_WEAPON_GAVEL = "WEAPON_GAVEL";

const string GIANT_MOSQUITO = "Giant Mosquito";
const string FLAMING_RABBIT = "Flaming Rabbit";
const string PET_SPACE = "Pet ";
const string CCS_TEAM_LEADER = "CCS Team Leader";
const string FIREFIGHTER = "Firefighter";
const string CONST_X_FIREMAN = "Fireman";
const string POLICE_NEGOTIATOR = "Police Negotiator";
const string CEO_SPACE = "CEO ";
const string ENFORCER = "Enforcer";
const string GENETIC_MONSTER_TXT = "genetic_monster.txt";
const string WORDS_MEANING_HICK_TXT = "words_meaning_hick.txt";
const string CCS_LIEUTENANT = "CCS Lieutenant";
const string CCS_FOUNDER = "CCS Founder";

const string tag_WEAPON_FLAMETHROWER = "WEAPON_FLAMETHROWER";
const string tag_LOOT_COMPUTER = "LOOT_COMPUTER";
const string tag_LOOT_CHEAPJEWELERY = "LOOT_CHEAPJEWELERY";
const string tag_LOOT_TRINKET = "LOOT_TRINKET";
const string tag_LOOT_SILVERWARE = "LOOT_SILVERWARE";
const string tag_LOOT_CELLPHONE = "LOOT_CELLPHONE";
const string tag_ARMOR_CIVILLIANARMOR = "ARMOR_CIVILLIANARMOR";
const string tag_ARMOR_SECURITYUNIFORM = "ARMOR_SECURITYUNIFORM";
const string tag_ARMOR_ARMYARMOR = "ARMOR_ARMYARMOR";
const string tag_ARMOR_HEAVYARMOR = "ARMOR_HEAVYARMOR";
const string tag_ARMOR_CHEAPSUIT = "ARMOR_CHEAPSUIT";
const string tag_ARMOR_WORKCLOTHES = "ARMOR_WORKCLOTHES";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_ARMOR_TRENCHCOAT = "ARMOR_TRENCHCOAT";
const string tag_WEAPON_AUTORIFLE_M16 = "WEAPON_AUTORIFLE_M16";
const string tag_WEAPON_SMG_MP5 = "WEAPON_SMG_MP5";
const string tag_WEAPON_CARBINE_M4 = "WEAPON_CARBINE_M4";
const string tag_WEAPON_REVOLVER_44 = "WEAPON_REVOLVER_44";
const string tag_LOOT_PDA = "LOOT_PDA";
const string tag_LOOT_MICROPHONE = "LOOT_MICROPHONE";
const string tag_LOOT_CABLENEWSFILES = "LOOT_CABLENEWSFILES";
const string tag_LOOT_AMRADIOFILES = "LOOT_AMRADIOFILES";
const string tag_LOOT_FAMILYPHOTO = "LOOT_FAMILYPHOTO";
const string tag_LOOT_WATCH = "LOOT_WATCH";
const string tag_ARMOR_BONDAGEGEAR = "ARMOR_BONDAGEGEAR";
const string tag_ARMOR_EXPENSIVESUIT = "ARMOR_EXPENSIVESUIT";
const string tag_ARMOR_EXPENSIVEDRESS = "ARMOR_EXPENSIVEDRESS";
const string tag_LOOT_CORPFILES = "LOOT_CORPFILES";
const string tag_LOOT_CHEMICAL = "LOOT_CHEMICAL";
const string tag_LOOT_FINECLOTH = "LOOT_FINECLOTH";
const string tag_ARMOR_BUNKERGEAR = "ARMOR_BUNKERGEAR";
const string tag_LOOT_SECRETDOCUMENTS = "LOOT_SECRETDOCUMENTS";
const string tag_WEAPON_SHANK = "WEAPON_SHANK";
const string tag_ARMOR_PRISONER = "ARMOR_PRISONER";
const string tag_LOOT_JUDGEFILES = "LOOT_JUDGEFILES";
const string tag_LOOT_POLICERECORDS = "LOOT_POLICERECORDS";
const string tag_ARMOR_POLICEARMOR = "ARMOR_POLICEARMOR";
const string tag_ARMOR_SWATARMOR = "ARMOR_SWATARMOR";
const string tag_ARMOR_POLICEUNIFORM = "ARMOR_POLICEUNIFORM";
const string tag_ARMOR_DEATHSQUADUNIFORM = "ARMOR_DEATHSQUADUNIFORM";
const string tag_WEAPON_SHOTGUN_PUMP = "WEAPON_SHOTGUN_PUMP";
const string tag_WEAPON_NIGHTSTICK = "WEAPON_NIGHTSTICK";
const string tag_LOOT_LABEQUIPMENT = "LOOT_LABEQUIPMENT";
const string tag_LOOT_RESEARCHFILES = "LOOT_RESEARCHFILES";
const string tag_LOOT_EXPENSIVEJEWELERY = "LOOT_EXPENSIVEJEWELERY";
const string tag_ARMOR_BLACKROBE = "ARMOR_BLACKROBE";
const string tag_ARMOR_LABCOAT = "ARMOR_LABCOAT";
const string tag_ARMOR_BLACKDRESS = "ARMOR_BLACKDRESS";
const string tag_ARMOR_BLACKSUIT = "ARMOR_BLACKSUIT";
const string tag_WEAPON_SEMIRIFLE_AR15 = "WEAPON_SEMIRIFLE_AR15";
const string tag_WEAPON_COMBATKNIFE = "WEAPON_COMBATKNIFE";
const string tag_WEAPON_BASEBALLBAT = "WEAPON_BASEBALLBAT";
const string tag_WEAPON_DAISHO = "WEAPON_DAISHO";
const string tag_ARMOR_CLOWNSUIT = "ARMOR_CLOWNSUIT";
const string tag_ARMOR_DONKEYSUIT = "ARMOR_DONKEYSUIT";
const string tag_ARMOR_ELEPHANTSUIT = "ARMOR_ELEPHANTSUIT";
const string tag_ARMOR_CHEAPDRESS = "ARMOR_CHEAPDRESS";
const string tag_WEAPON_GUITAR = "WEAPON_GUITAR";
const string tag_LOOT_DIRTYSOCK = "LOOT_DIRTYSOCK";
const string tag_LOOT_KIDART = "LOOT_KIDART";
const string tag_ARMOR_TOGA = "ARMOR_TOGA";
const string tag_WEAPON_SYRINGE = "WEAPON_SYRINGE";
const string tag_WEAPON_CHAIN = "WEAPON_CHAIN";
const string tag_WEAPON_CROWBAR = "WEAPON_CROWBAR";
const string creature = "creature\\";

#include "../creature/creature.h"
#include "../locations/locationsEnums.h"
#include "../common/interval.h"
#include "creaturetype.h"
//own header
#include "../log/log.h"
// for LOG
#include "../common/translateid.h"
// for  int getweapontype(int)
#include "../common/stringconversion.h"
//for creaturetype_string_to_enum
#include "../politics/politics.h"
//for int publicmood(int l);

map<string, int> creatureTypeTags = {
	map<string, int>::value_type(tag_alignment, ENUM_tag_alignment),
	map<string, int>::value_type(tag_PUBLIC_MOOD, ENUM_tag_PUBLIC_MOOD),
	map<string, int>::value_type(tag_LIBERAL, ENUM_tag_LIBERAL),
	map<string, int>::value_type(tag_MODERATE, ENUM_tag_MODERATE),
	map<string, int>::value_type(tag_CONSERVATIVE, ENUM_tag_CONSERVATIVE),
	map<string, int>::value_type(tag_age, ENUM_tag_age),
	map<string, int>::value_type(tag_DOGYEARS, ENUM_tag_DOGYEARS),
	map<string, int>::value_type(tag_CHILD, ENUM_tag_CHILD),
	map<string, int>::value_type(tag_TEENAGER, ENUM_tag_TEENAGER),
	map<string, int>::value_type(tag_YOUNGADULT, ENUM_tag_YOUNGADULT),
	map<string, int>::value_type(tag_MATURE, ENUM_tag_MATURE),
	map<string, int>::value_type(tag_GRADUATE, ENUM_tag_GRADUATE),
	map<string, int>::value_type(tag_MIDDLEAGED, ENUM_tag_MIDDLEAGED),
	map<string, int>::value_type(tag_SENIOR, ENUM_tag_SENIOR),
	map<string, int>::value_type(tag_attribute_points, ENUM_tag_attribute_points),
	map<string, int>::value_type(tag_attributes, ENUM_tag_attributes),
	map<string, int>::value_type(tag_juice, ENUM_tag_juice),
	map<string, int>::value_type(tag_gender, ENUM_tag_gender),
	map<string, int>::value_type(tag_infiltration, ENUM_tag_infiltration),
	map<string, int>::value_type(tag_money, ENUM_tag_money),
	map<string, int>::value_type(tag_skills, ENUM_tag_skills),
	map<string, int>::value_type(tag_armor, ENUM_tag_armor),
	map<string, int>::value_type(tag_weapon, ENUM_tag_weapon),
	map<string, int>::value_type(tag_encounter_name, ENUM_tag_encounter_name),
	map<string, int>::value_type(tag_type_name, ENUM_tag_type_name),

};

vector<CreatureTypes> armAsCivilian = {
	// Curiously, CREATURE_CRACKHEAD has a chance to be armed with a shank, regardless of whether they are granted a civilian weapon
	CREATURE_CRACKHEAD, CREATURE_MUTANT, CREATURE_BUM, CREATURE_WORKER_FACTORY_UNION, CREATURE_WORKER_FACTORY_NONUNION, CREATURE_SCIENTIST_EMINENT, CREATURE_SCIENTIST_LABTECH
};

map<short, vector<CreatureTypes> > replaceTheseCreatures = {
	// The original code has a 1/10 chance to replace with CREATURE_THIEF
	// Otherwise, random selection between the other five.
	// This code changes this to a 1/11 chance to replace with CREATURE_THIEF
	// Which is close enough.
	map<CreatureTypes, vector<CreatureTypes> >::value_type(CREATURE_PRISONER,{ CREATURE_THIEF, CREATURE_GANGMEMBER, CREATURE_PROSTITUTE, CREATURE_CRACKHEAD, CREATURE_TEENAGER, CREATURE_HSDROPOUT, CREATURE_GANGMEMBER, CREATURE_PROSTITUTE, CREATURE_CRACKHEAD, CREATURE_TEENAGER, CREATURE_HSDROPOUT })

};
vector<CreatureTypes> doNotArmInThisFunction = {
	CREATURE_JUDGE_LIBERAL,
	CREATURE_POLITICIAN,
	CREATURE_CORPORATE_MANAGER,
	CREATURE_WORKER_SERVANT,
	CREATURE_WORKER_JANITOR,
	CREATURE_WORKER_SECRETARY,
	CREATURE_LANDLORD,
	CREATURE_BANK_TELLER,
	CREATURE_BANK_MANAGER,
	CREATURE_TEENAGER,
	CREATURE_SOLDIER,
	CREATURE_VETERAN,
	CREATURE_HARDENED_VETERAN,
	CREATURE_SWAT,
	CREATURE_DEATHSQUAD,
	CREATURE_GANGUNIT,
	CREATURE_AGENT,
	CREATURE_SECRET_SERVICE,
	CREATURE_RADIOPERSONALITY,
	CREATURE_NEWSANCHOR,
	CREATURE_JUROR,
	CREATURE_WORKER_FACTORY_CHILD,
	CREATURE_SEWERWORKER,
	CREATURE_COLLEGESTUDENT,
	CREATURE_MUSICIAN,
	CREATURE_MATHEMATICIAN,
	CREATURE_TEACHER,
	CREATURE_HSDROPOUT,
	CREATURE_PRIEST,
	CREATURE_ENGINEER,
	CREATURE_TELEMARKETER,
	CREATURE_CARSALESMAN,
	CREATURE_OFFICEWORKER,
	CREATURE_MAILMAN,
	CREATURE_GARBAGEMAN,
	CREATURE_PLUMBER,
	CREATURE_CHEF,
	CREATURE_CONSTRUCTIONWORKER,
	CREATURE_AMATEURMAGICIAN,
	CREATURE_AUTHOR,
	CREATURE_JOURNALIST,
	CREATURE_CRITIC_ART,
	CREATURE_CRITIC_MUSIC,
	CREATURE_BIKER,
	CREATURE_TRUCKER,
	CREATURE_TAXIDRIVER,
	CREATURE_PROGRAMMER,
	CREATURE_NUN,
	CREATURE_RETIREE,
	CREATURE_PAINTER,
	CREATURE_SCULPTOR,
	CREATURE_DANCER,
	CREATURE_PHOTOGRAPHER,
	CREATURE_CAMERAMAN,
	CREATURE_HAIRSTYLIST,
	CREATURE_FASHIONDESIGNER,
	CREATURE_CLERK,
	CREATURE_ACTOR,
	CREATURE_YOGAINSTRUCTOR,
	CREATURE_MARTIALARTIST,
	CREATURE_ATHLETE,
	CREATURE_LOCKSMITH,
	CREATURE_MILITARYPOLICE,
	CREATURE_SEAL,
	// These are not used in the switch statement anymore, but appear in the defaultWeapons collection
	//CREATURE_SECURITY_GUARD
	//CRREATURE_MERC
};
struct weaponLayout {
	string weaponTag;
	string clipTag;
	int ammunition;
	weaponLayout(string whichSkill_, string experience_, int maxLevel_) :weaponTag(whichSkill_), clipTag(experience_), ammunition(maxLevel_) {}
	weaponLayout(string whichSkill_) :weaponTag(whichSkill_), clipTag(""), ammunition(0) {}
	weaponLayout() : weaponLayout(tag_WEAPON_NONE) {}
};
struct fullWeaponLayout {
	weaponLayout cplus;
	weaponLayout c;
	weaponLayout moderate;
	weaponLayout l;
	weaponLayout lplus;
	fullWeaponLayout() : cplus(weaponLayout()), c(weaponLayout()), moderate(weaponLayout()), l(weaponLayout()), lplus(weaponLayout()) {}
	fullWeaponLayout(weaponLayout cplus_, weaponLayout c_, weaponLayout moderate_, weaponLayout l_, weaponLayout lplus_) : cplus(cplus_), c(c_), moderate(moderate_), l(l_), lplus(lplus_) {}

};


map<const short, const fullWeaponLayout> defaultWeapons = {
	map<const short, const fullWeaponLayout>::value_type(CREATURE_BOUNCER, fullWeaponLayout(weaponLayout(tag_WEAPON_SMG_MP5, tag_CLIP_SMG, 4), weaponLayout(tag_WEAPON_REVOLVER_44, tag_CLIP_44, 4), weaponLayout(tag_WEAPON_REVOLVER_38, tag_CLIP_38, 4), weaponLayout(tag_WEAPON_NIGHTSTICK), weaponLayout(tag_WEAPON_NIGHTSTICK))),
	map<const short, const fullWeaponLayout>::value_type(CREATURE_SECURITYGUARD, fullWeaponLayout(weaponLayout(tag_WEAPON_SMG_MP5, tag_CLIP_SMG, 4), weaponLayout(tag_WEAPON_NIGHTSTICK), weaponLayout(tag_WEAPON_NIGHTSTICK), weaponLayout(tag_WEAPON_NIGHTSTICK), weaponLayout(tag_WEAPON_REVOLVER_38, tag_CLIP_38, 4))),
	map<const short, const fullWeaponLayout>::value_type(CREATURE_MERC, fullWeaponLayout(weaponLayout(tag_WEAPON_AUTORIFLE_M16, tag_CLIP_ASSAULT, 7), weaponLayout(tag_WEAPON_AUTORIFLE_M16, tag_CLIP_ASSAULT, 7), weaponLayout(tag_WEAPON_AUTORIFLE_M16, tag_CLIP_ASSAULT, 7), weaponLayout(tag_WEAPON_SEMIRIFLE_AR15, tag_CLIP_ASSAULT, 7), weaponLayout(tag_WEAPON_SEMIRIFLE_AR15, tag_CLIP_ASSAULT, 7))),

};

#define AGE_TEENAGER    14+LCSrandom(4)  /* HS dropout, teenager, some fast food workers */
#define AGE_YOUNGADULT  18+LCSrandom(18) /* young lads and ladies */
#include "locations/locationsPool.h"
#include "sitemode/stealth.h"
short getCurrentSite();
struct fullName {
	string first;
	string middle;
	string last;

};
fullName generate_long_name(char gender = GENDER_NEUTRAL);
#include "customMaps.h"
vector<string> words_meaning_hick;
vector<string> genetic_monster;
vector<file_and_text_collection> creaturetypes_text_file_collection = {
	/*creaturetypes.cpp*/
	customText(&words_meaning_hick, creature + WORDS_MEANING_HICK_TXT),
	customText(&genetic_monster, creature + GENETIC_MONSTER_TXT),
};
bool isThereASiteAlarm();
extern char ccs_kills;
extern char endgamestate;
extern Log xmllog;
extern short lawList[LAWNUM];
extern short mode;
extern short sitealienate;
extern short sitetype;
extern vector<ClipType *> cliptype;
extern vector<WeaponType *> weapontype;

#endif	//CREATURETYPE_CPP
#ifdef	CURSESALTERNATIVE_CPP
// cursesAlternative.cpp


#endif	//CURSESALTERNATIVE_CPP
#ifdef	CURSESMOVIE_CPP
// cursesmovie.cpp

const string CONST_X_RB = "rb";
const string CONST_X_WB = "wb";
#endif	//CURSESMOVIE_CPP
#ifdef	DAILY_CPP
// daily.cpp

const string notEnoughMoney = "You don't have enough money!";
const string CHOOSE_A_COLOR = "Choose a color";
const string theseColorsAreCon = "These colors are Conservative";
const string thisColor = "Color";
const string CHOOSE_A_VEHICLE = "Choose a vehicle";
const string thisVehicle = "Vehicle";
const string weDontNeedCar = "We don't need a Conservative car";
const string B_CHOOSE_BUYER = "B - Choose a buyer";
const string s_sellCar = "S - Sell a car";
const string s_sellThe = "S - Sell the ";
const string g_getCar = "G - Get a Liberal car";
const string toSpend = "SPEND.";
const string enterLeave = "Enter - Leave";
const string f_fixWounds = "F - Go in and fix up Conservative wounds";
const string WAS_TOO_HOT_TO_RISK = " was too hot to risk.";
const string DECIDED = " decided ";
const string REGAINS_CONTACT = " regains contact with the LCS.";
const string CONST_CREATURE_POLITICALACTIVIST = "CREATURE_POLITICALACTIVIST";
const string CONST_CREATURE_TEENAGER = "CREATURE_TEENAGER";
const string THE_LIBERAL_WILL_BE_MISSED = ". The Liberal will be missed.";
const string HAS_PASSED_AWAY = " has passed away at the age of ";
const string SURFS_THE_NET = " surfs the Net for recent opinion polls.";
const string WHY_IS_THE_SQUAD_HERE = "Why is the squad here?   (S)afe House, to cause (T)rouble, or (B)oth?";
const string HAS_ARRIVED_AT = " has arrived at ";
const string LOOKS_AROUND = " looks around ";
const string ARRIVES_IN = " arrives in ";
const string SPENT_ON_TICKETS = "%s spent $%d on tickets to go to %s.";
const string COULDNT_AFFORD_TICKETS = "%s couldn't afford tickets to go to %s.";
const string TRAVEL_LOCATION = "travel location";
const string DIDNT_HAVE_A_CAR = " didn't have a car to get to ";
const string COULDNT_USE_THE = " couldn't use the ";
const string INSTEAD_OF = " instead of ";
const string ACTED_WITH = " acted with ";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string CONST_OUBLIETTE_XML = "oubliette.xml";
const string CONST_DEPTSTORE_XML = "deptstore.xml";
const string CONST_P_REPAINT_CAR_REPLACE_PLATES_AND_TAGS_500 = "P - Repaint car, replace plates and tags ($500)";
const string CONST_PAWNSHOP_XML = "pawnshop.xml";
const string CONST_ARMSDEALER_XML = "armsdealer.xml";
const string SPENT_DOLLARS = " spent $";
const string ON_TICKETS = " on tickets to go to ";
const string SINGLE_DOT = ".";
const string COULDNT_AFFORD_TICKETSA = " couldn't afford tickets to go to %";
const string COULDNT_AFFORD_TICKETSB = ".";

#include "../creature/creature.h"
////

#include "../creature/deprecatedCreatureA.h"

#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
//#include "../news/news.h"
void majornewspaper(char &clearformess, char canseethings);
//#include "../sitemode/sitemode.h"
void mode_site(const short loc);
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
// for makedelimeter
#include "../common/getnames.h"
// for std::string getactivity(ActivityST)
#include "../common/translateid.h"
// for  int getsquad(int)
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
/* tells how many total members a squad has (including dead members) */
// for void basesquad(squadst *,long)
#include "../daily/daily.h"
/* squad members with no chain of command lose contact */
void dispersalcheck(char &clearformess);

#include "../daily/activities.h"
//for void repairarmor(Creature &cr,char &clearformess); and stealcar
#include "../daily/siege.h"        
//for sigeturn and siegecheck
//#include "../daily/recruit.h"
void recruitment_activity(DeprecatedCreature &cr);
char completerecruitmeeting(Deprecatedrecruitst &d, const int p);
//#include "../daily/date.h"
char completevacation(Deprecateddatest &d, int p);
char completedate(Deprecateddatest &d, int p);
#include "../combat/chaseCreature.h"
//for int driveskill(Creature &cr,Vehicle &v);
//hmm --Schmel924
#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include "../title/titlescreen.h"
#include "../locations/locationsPool.h"
#include "../common/creaturePool.h"


#include "../sitemode/shop.h"
#include "../common/musicClass.h"


bool carselect(DeprecatedCreature &cr, short &cartype);
bool stealcar(DeprecatedCreature &cr, char &clearformess);
bool vehicletypeavailableatshop(const int i);
DeprecatedCreature* findSleeperCarSalesman(int loc);
extern char artdir[MAX_PATH_SIZE];
extern char disbanding;
extern char showcarprefs;
extern class Ledger ledger;
extern Deprecatedsquadst *activesquad;
extern int day;
extern int month;
extern int year;
extern Log gamelog;
extern MusicClass music;
extern short fieldskillrate;
extern short party_status;
extern vector<DeprecatedCreature *> pool;
extern vector<Deprecatednewsstoryst *> newsstory;
extern vector<Deprecatedrecruitst *> recruit;
extern vector<Deprecatedsquadst *> squad;
extern vector<Vehicle *> vehicle;
int driveskill(DeprecatedCreature &cr, int v);
int getVehicleTypePrice(const int carchoice);
int getVehicleTypeSleeperPrice(const int carchoice);
int lenVehicleType();
string getVehicleFullname(int i);
string vehicleTypelongname(const int p);
vector<string> getVehicleTypeColor(const int carchoice);
Vehicle* getVehicleFromTypeYear(const int carchoice, const int colorchoice, const int year);
void basesquad(Deprecatedsquadst *st, long loc);
void clearCarStates();
void determineMedicalSupportAtEachLocation(bool clearformess);
void doDates(char &clearformess);
void getwheelchair(DeprecatedCreature &cr, char &clearformess);
void locateActiveSquad(const int loc);
void locatesquad(Deprecatedsquadst *st, long loc);
void makearmor(DeprecatedCreature &cr, char &clearformess);
void repairarmor(DeprecatedCreature &cr, char &clearformess);
void survey(DeprecatedCreature *cr);
void tendhostage(DeprecatedCreature *cr, char &clearformess);



#endif	//DAILY_CPP
#ifdef	DATE_CPP
// date.cpp

const string CONST_S = "'s ";
const string CONST_CELL_PHONE = " cell phone.";
const string CONST_PET = " pet";
const string CONST_FAVOURITE_TV_SHOW = " favourite TV show.";
const string CONST_HAIR = " hair.";
const string CONST_S_FROZEN_CONSERVATIVE_HEART = "'s frozen Conservative heart.";
const string CONST_THE_LIBERAL_WAKES_UP_IN_THE_POLICE_STATION = "The Liberal wakes up in the police station...";
const string CONST_REMEMBERS_SEEING = " remembers seeing!";
const string CONST_S_FIST_IS_THE_LAST_THING = "'s fist is the last thing ";
const string CONST_HAS_FAILED_TO_KIDNAP_THE_CONSERVATIVE = " has failed to kidnap the Conservative.";
const string CONST_MANAGES_TO_GET_AWAY_ON_THE_WAY_BACK_TO_THE_SAFEHOUSE = " manages to get away on the way back to the safehouse!";
const string CONST_IF_YOU_DO_NOT_ENTER_ANYTHING_THEIR_REAL_NAME_WILL_BE_USED = "If you do not enter anything, their real name will be used.";
const string CONST_IN_ITS_PRESENCE = " in its presence?";
const string CONST_WHAT_NAME_WILL_YOU_USE_FOR_THIS = "What name will you use for this ";
const string CONST_THE_EDUCATION_OF = "The Education of ";
const string CONST_KIDNAPS_THE_CONSERVATIVE = " kidnaps the Conservative!";
const string CONST_STRUGGLES_AND_YELLS_FOR_HELP_BUT_NOBODY_COMES = " struggles and yells for help, but nobody comes.";
const string CONST_DOESN_T_RESIST = " doesn't resist.";
const string CONST_NOT_TO_RESIST = "not to [resist]!";
const string CONST_NOT_TO_FUCK_AROUND = "not to fuck around!";
const string CONST_SEIZES_THE_CONSERVATIVE_SWINE_FROM_BEHIND_AND_WARNS_IT = " seizes the Conservative swine from behind and warns it";
const string CONST_TO_THE_CORPORATE_SLAVE_S_THROAT = "to the corporate slave's throat!";
const string CONST_GRABS_THE_CONSERVATIVE_FROM_BEHIND_HOLDING_THE = " grabs the Conservative from behind, holding the ";
const string CONST_AND_THREATENS_TO_BLOW_THE_CONSERVATIVE_S_BRAINS_OUT = "and threatens to blow the Conservative's brains out!";
const string CONST_COMES_BACK_FROM_THE_BATHROOM_TOTING_THE = " comes back from the bathroom toting the ";
const string CONST_E_JUST_KIDNAP_THE_CONSERVATIVE_BITCH = "E - Just kidnap the Conservative bitch.";
const string CONST_D_BREAK_IT_OFF = "D - Break it off.";
const string CONST_C_SPEND_A_WEEK_ON_A_CHEAP_VACATION_MUST_BE_UNINJURED = "C - Spend a week on a cheap vacation (must be uninjured).";
const string CONST_C_SPEND_A_WEEK_ON_A_CHEAP_VACATION_STANDS_UP_ANY_OTHER_DATES = "C - Spend a week on a cheap vacation (stands up any other dates).";
const string CONST_B_TRY_TO_GET_THROUGH_THE_EVENING_WITHOUT_SPENDING_A_PENNY = "B - Try to get through the evening without spending a penny.";
const string CONST_A_SPEND_A_HUNDRED_BUCKS_TONIGHT_TO_GET_THE_BALL_ROLLING = "A - Spend a hundred bucks tonight to get the ball rolling.";
const string CONST_APPROACH_THE_SITUATION = " approach the situation?";
const string CONST_HOW_SHOULD = "How should ";
const string CONST_SEEING = "Seeing ";
const string CONST_THINGS_GO_DOWNHILL_FAST = "Things go downhill fast.";
const string CONST_MIXES_UP_THE_NAMES_OF = " mixes up the names of ";
const string REALIZES = " realizes ";
const string HAS_COMMITTED = " has committed to eating ";
const string MEALS_AT_ONCE = " meals at once.";
const string RUH_ROH = "Ruh roh...";
const string UNFORTUNATELY_THEY_TURN_UP_AT_ONCE = "Unfortunately, they turn up at the same time.";
const string UNFORTUNATELY_THEY_ALL_TURN_UP_AT_ONCE = "Unfortunately, they all turn up at the same time.";
const string AN_AMBUSH_FOR_THE_DOG = ".  An ambush was set for the lying dog...";
const string UNFORTUNATELY_THEY_KNOW_EACHOTHER = "Unfortunately, they know each other and had been discussing";
const string UNFORTUNATELY_THEY_ALL_KNOW_EACHOTHER = "Unfortunately, they all know each other and had been discussing";
const string AT_SPACE = " at ";
const string DATES_TO_MANAGE = "dates to manage with ";
const string A_HOT_DATE = "a hot date with ";
const string A_H_O_T_DATE = "a \"hot\" date with ";
const string CONST_date062 = " has ";
const string IS_BACK_FROM_VACATION = " is back from vacation.";
const string THE_RELATIONSHIP_IS_OVER = "This relationship is over.";
const string CAN_SENSE_THAT_THINGS_ARENT_WORKING = " can sense that things just aren't working out.";
const string FROM_MEETING_SPACE = " from meeting ";
const string SCHEDULE_FOR_KEEPING = "schedule for keeping ";
const string MIND_BENDING = "mind-bending ";
const string DETAILED = "detailed ";
const string COMPLICATED = "complicated ";
const string INTRICATE = "intricate ";
const string AWE_INSPIRING = "awe-inspiring ";
const string NOTICES = "notices ";
const string THE_DATE_STARTS_WELL_UNTIL = "The date starts well, but goes horribly wrong when ";
const string ESCAPES_THE_POLICE_AMBUSH = " escapes the police ambush!";
const string BUT_SPACE = "But ";
const string HAS_BEEN_ARRESTED = " has been arrested.";
const string WAS_LEAKING_INFORMATION_TO_POLICE = " was leaking information to the police the whole time!";
const string S_MIND_WITH_WISDOM = "'s mind with wisdom!!!";
const string ACTUALLY_CURSES = " actually curses ";
const string TALKING_WITH = "Talking with ";
const string THEYLL_MEET_AGAIN_TOMORROW = "They'll meet again tomorrow.";
const string TO_RECHARGE = " to recharge ";
const string TO_GO_TO_BIRTHDAY = " to go to a birthday party.";
const string SIX_LEGGED_PIG = " six-legged pig.";
const string CONST_X_FISH = " fish.";
const string CONST_X_DOG = " dog.";
const string CONST_X_CAT = " cat.";
const string TO_TAKE_CARE_OF = " to take care of ";
const string TO_CATCH = " to catch ";
const string DUE_TO_EARLY_MEETING = " due to an early meeting tomorrow.";
const string DUE_TO_ALLERGY = " due to an allergy attack.";
const string TO_WASH = " to wash ";
const string SEEMED_TO_HAVE_FUN_BUT_LEFT_EARLY = " seemed to have fun, but left early";
const string KNOWS_THIS_ALREADY = " knows all about that already.";
const string WAS_ABLE_TO_CREATE_MAP = " was able to create a map of the site with this information.";
const string TURNS_THE_TOPIC_OF_DISCUSSION = " turns the topic of discussion to the ";
const string IS_SLOWLY_WARMING = " is slowly warming ";
const string SELF_NULLIFYING_INFATUATION_OF = "The Self-Nullifying Infatuation of ";
const string S_TOTALLY_LOVE_SLAVE = "'s totally unconditional love-slave!";
const string IS_SPACE = " is ";
const string IN_FACT = "In fact, ";
const string IT_WAS_FUN_PART_AMICABLY = "It was fun though. They agree to part ways amicably.";
const string RELATIONSHIP = " relationship.";
const string YET_ANOTHER = "yet another";
const string ANOTHER = "another";
const string ISNT_SEDUCTIVE_ENOUGH = " isn't seductive enough to juggle ";
const string CONST_X_PEOPLE = " people!";
const string SOMEONE = "someone!";
const string IS_ALREADY_DATING = " is already dating ";
const string S_UNIQUE_PHILOSOPHY = "'s unique life philosophy...";
const string IS_QUITE_TAKEN_WITH = " is quite taken with ";
const string DATE_FAIL_TXT = "date_fail.txt";

const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string datey = "date\\";


#include "../creature/creature.h"
////

#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"
//#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
#include "../common/commondisplayCreature.h"
// for  addstr
#include "../common/commonactionsCreature.h"
// for int loveslavesleft(const Creature&)
#include "../common/getnames.h"
// for void enter_name(int,int,char *,int,const char *=NULL)
//#include "../common/translateid.h"
int getarmortype(const string &idname);
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../common/creaturePoolCreature.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"

extern class Ledger ledger;
extern int stat_kidnappings;
extern int stat_recruits;
extern Log gamelog;
extern MusicClass music;
extern short lawList[LAWNUM];
extern vector<DeprecatedCreature *> pool;

vector<string> date_fail;
vector<file_and_text_collection> date_text_file_collection = {
	/*date.cpp*/
	customText(&date_fail, datey + DATE_FAIL_TXT),
};
enum DateResults
{
	DATERESULT_MEETTOMORROW,
	DATERESULT_BREAKUP,
	DATERESULT_JOINED,
	DATERESULT_ARRESTED
};
int getpoolcreature(int id);
char completedate(Deprecateddatest &d, int p);
void removesquadinfo(DeprecatedCreature &cr);
char completevacation(Deprecateddatest &d, int p);
#endif	//DATE_CPP
#ifdef	ENDGAME_CPP
// endgame.cpp

const string CONSERVATIVES_HAVE_REMADE_THE_WORLD = "The Conservatives have made the world in their image.";
const string stalinistsRemakeWorld = "The Stalinists have made the world in their image.";
const string youWentOnVacation = "You went on vacation when the country was on the verge of collapse.";
const string youWentIntoHiding = "You went into hiding when the country was on the verge of collapse.";
const string whileYouWereInPrison = "While you were on the inside, the country degenerated...";
const string youDisappearedSafely = "You disappeared safely, but you hadn't done enough.";
const string proposeConservative = "The Arch-Conservative Congress is proposing an ARCH-CONSERVATIVE AMENDMENT!";
const string proposeStalinist = "The Stalinist Congress is proposing a STALINIST AMENDMENT!";
const string they_ll_round_you_up = "They'll round up the last of you up eventually.  All is lost.";
const string pressKeyToReflect = "Press any key to reflect on what has happened.";
const string YEA = " Yea";
const string NAY = " Nay";
const string CONST_PRESS_ANY_KEY_TO_BREATHE_A_SIGH_OF_RELIEF = "Press any key to breathe a sigh of relief.                   ";
const string CONST_PRESS_ANY_KEY_TO_REFLECT_ON_WHAT_HAS_HAPPENED_ONE_LAST_TIME = "Press any key to reflect on what has happened ONE LAST TIME.";
const string CONST_PRESS_C_TO_WATCH_THE_RATIFICATION_PROCESS_UNFOLD = "Press 'C' to watch the ratification process unfold.";
const string CONST_INVALID_ALIGNMENT_FOR_AMENDMENT = "INVALID ALIGNMENT FOR AMENDMENT";
const string CONST_PRESS_ANY_KEY_TO_HOLD_NEW_ELECTIONS = "Press any key to hold new elections!                           ";
const string CONST_A_NATIONAL_CONVENTION_HAS_PROPOSED_AN_ELITE_LIBERAL_AMENDMENT = "A National Convention has proposed an ELITE LIBERAL AMENDMENT!";
const string CONST_THE_SENATE = "the Senate.";
const string CONST_THE_PRESIDENT_S_CHOOSING_WITH_THE_ADVICE_AND_CONSENT_OF = "the President's choosing with the advice and consent of";
const string CONST_ALSO_OF = ", also of";
const string CONST_A_PROPER_JUSTICE = "a Proper Justice";
const string CONST_PROPER_JUSTICES = "Proper Justices";
const string CONST_CHOOSING_TO_BE_REPLACED_BY = "choosing to be replaced by ";
const string CONST_OF_THE_PRESIDENT_S = " of the President's";
const string CONST_A_CONSERVATIVE_COUNTRY = "a Conservative country";
const string CONST_CONSERVATIVE_COUNTRIES = "Conservative countries";
const string CONST_BE_DEPORTED_TO = "be deported to ";
const string CONST_WILL = " will";
const string CONST_endgame028 = "s";
const string CONST_NOT_SERVE_ON_THE_SUPREME_COURT_SAID_FORMER_CITIZEN = "not serve on the Supreme Court.  Said former citizen";
const string CONST_MAY = " may";
const string CONST_IN_PARTICULAR_THE_AFOREMENTIONED_FORMER_CITIZEN = "In particular, the aforementioned former citizen";
const string CONST_BRANDED_ARCH_CONSERVATIVE = " branded Arch-Conservative:";
const string CONST_IS = " is";
const string CONST_S_ARE = "s are";
const string CONST_THE_FOLLOWING_FORMER_CITIZEN = "The following former citizen";
const string CONST_THE_ELITE_LIBERAL_CONGRESS_IS_PROPOSING_AN_ELITE_LIBERAL_AMENDMENT = "The Elite Liberal Congress is proposing an ELITE LIBERAL AMENDMENT!";
const string CONST_TO_THE_UNITED_STATES_CONSTITUTION = " to the United States Constitution:";
const string CONST_PROPOSED_AMENDMENT = "Proposed Amendment ";
const string CONST_AMENDMENT_REJECTED = "AMENDMENT REJECTED.";
const string CONST_AMENDMENT_ADOPTED = "AMENDMENT ADOPTED.";
const string CONST_NAY = "Nay";
const string CONST_YEA = "Yea";
const string CONST_PRESS_ANY_KEY_TO_WATCH_THE_STATE_VOTES_UNFOLD = "Press any key to watch the State votes unfold.              ";
const string CONST_PRESS_ANY_KEY_TO_WATCH_THE_CONGRESSIONAL_VOTES_UNFOLD = "Press any key to watch the Congressional votes unfold.     ";
const string CONST_SENATE = "Senate";
const string CONST_HOUSE = "House";
const string CONST_THE_RATIFICATION_PROCESS = "The Ratification Process:";
const string CONST_STALINIZEDCABINET_TXT = "stalinizedCabinet.txt";
const string CONST_REAGANIFIEDCABINET_TXT = "reaganifiedCabinet.txt";
const string CONST_STALINISTPRISON_TXT = "stalinistPrison.txt";
const string CONST_CONSERVATIVEPRISON_TXT = "conservativePrison.txt";
const string CONST_AMENDMENTPASS_TXT = "amendmentPass.txt";
const string CONST_ARCHCONSERVATIVEAMENDMENT_TXT = "archConservativeAmendment.txt";
const string CONST_STALINAMENDMENT_TXT = "stalinAmendment.txt";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";

#include "../creature/creatureEnums.h"
/* fills a string with a proper name */
void generate_name(char *str, char gender = GENDER_NEUTRAL);
#include "../basemode/liberalagenda.h"
// for liberalagenda
//#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
// for void printfunds(int,int,char*)
#include "../common/misc.h"
// for char* statename(int)
		 //shouldn't be in getnames? --Schmel924
// for romannumeral (int)
		 //only usage here --Schmel924
#include "../title/titlescreen.h"
// for void reset;
#include "../title/highscore.h"
// for void savehighscore(char endtype);
//#include "../monthly/EndGameStatus.h"
//own header
		//does not compile without --Schmel924
#include "../politics/politics.h"
//for publicmood
#include "../cursesAlternative.h"
#include <gui_constants.h>
#include "../set_color_support.h"
/* end the game and clean up */
void end_game(int err = EXIT_SUCCESS);
#include "../common/musicClass.h"
vector<int> state_biases;
vector<string> reaganifiedCabinet;
vector<string> stalinizedCabinet;
vector<string> archConservativeAmendment;
vector<string> stalinAmendment;

vector<string> conservativePrison;
vector<string> stalinistPrison;
vector<string> amendmentPass;
#include "../customMaps.h"
vector<file_and_text_collection> endgame_text_file_collection = {
	customText(&stalinAmendment, MOSTLY_ENDINGS_FOLDER + CONST_STALINAMENDMENT_TXT),
	customText(&archConservativeAmendment, MOSTLY_ENDINGS_FOLDER + CONST_ARCHCONSERVATIVEAMENDMENT_TXT),
	customText(&amendmentPass, MOSTLY_ENDINGS_FOLDER + CONST_AMENDMENTPASS_TXT),
	customText(&conservativePrison, MOSTLY_ENDINGS_FOLDER + CONST_CONSERVATIVEPRISON_TXT),
	customText(&stalinistPrison, MOSTLY_ENDINGS_FOLDER + CONST_STALINISTPRISON_TXT),
	customText(&reaganifiedCabinet, MOSTLY_ENDINGS_FOLDER + CONST_REAGANIFIEDCABINET_TXT),
	customText(&stalinizedCabinet, MOSTLY_ENDINGS_FOLDER + CONST_STALINIZEDCABINET_TXT),
};
struct fullName {
	string first;
	string middle;
	string last;

};
extern bool termlimits;
extern char cantseereason;
extern char courtname[COURTNUM][POLITICIAN_NAMELEN];
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern int amendnum;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short court[COURTNUM];
extern short exec[EXECNUM];
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short senate[SENATENUM];

fullName generate_long_name(char gender = GENDER_NEUTRAL);
#endif	//ENDGAME_CPP
#ifdef	EXTERNALLYSTOREDDATA_CPP
// externallyStoredData.cpp

const string talky = "talk\\";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";

const string CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT = "attend classes in the University District";
const string CONST_AT_A_COST_OF_60_A_DAY = "at a cost of $60 a day.";


const string CONST_SELL_LIBERAL_ART = "Sell Liberal Art";
const string CONST_SELL_LIBERAL_T_SHIRTS = "Sell Liberal T-Shirts";
const string CONST_UNCONTROLLED_IMMIGRATION = "uncontrolled immigration.";
const string CONST_LEGALIZING_NUCLEAR_POWER = "legalizing nuclear power.";
const string CONST_RESTORING_THE_DEATH_PENALTY = "restoring the death penalty.";
const string CONST_CLASSES_COST_UP_TO_60_DAY_TO_CONDUCT_ALL_LIBERALS_ABLE_WILL_ATTEND = "Classes cost up to $60/day to conduct. All Liberals able will attend.";
const string CONST_CLASSES_COST_UP_TO_20_DAY_TO_CONDUCT_ALL_LIBERALS_ABLE_WILL_ATTEND = "Classes cost up to $20/day to conduct. All Liberals able will attend.";
const string CONST_WILL_CREATE_AND_SELL_PAINTINGS_EMBRACING_THE_LIBERAL_AGENDA = "will create and sell paintings embracing the Liberal agenda.";
const string CONST_WILL_PRINT_AND_DISTRIBUTE_SHIRTS_WITH_LIBERAL_SLOGANS = "will print and distribute shirts with Liberal slogans.";
const string CONST_ACTIVIST_IS = "activist is.";
const string CONST_MULTIPLE_HACKERS_WILL_INCREASE_CHANCES_OF_BOTH_SUCCESS_AND_DETECTION = "Multiple hackers will increase chances of both success and detection.";
const string CONST_AND_INTELLIGENCE_WILL_PROVIDE_BETTER_RESULTS = "and intelligence will provide better results.";

const string CONST_DRUG_LAW = "Drug Law";
const string CONST_TAX_LAW = "Tax Law";
const string CONST_FREEDOM_OF_SPEECH = "Freedom of Speech";
const string CONST_CORPORATE_ETHICS = "Corporate Ethics";
const string CONST_HOMOSEXUAL_RIGHTS = "Homosexual Rights";
const string CONST_WORKERS_RIGHTS = "Workers' Rights";
const string CONST_CAPITAL_PUNISHMENT = "Capital Punishment";
const string CONST_X_PRIVACY = "Privacy";
const string CONST_POLICE_BEHAVIOR = "Police Behavior";
const string CONST_ANIMAL_RESEARCH = "Animal Research";
const string CONST_X_THE_CCS_TERRORISTS = "The CCS Terrorists";
const string CONST_WHY_WE_ROCK = "Why We Rock";
const string CONST_WHO_WE_ARE = "Who We Are";
const string CONST_THE_NEED_FOR_ACTION = "The Need For Action";
const string CONST_CABLE_NEWS_LIES = "Cable \"News\" Lies";
const string CONST_AM_RADIO_PROPAGANDA = "AM Radio Propaganda";
const string CONST_X_IMMIGRANT_RIGHTS = "Immigrant Rights";
const string CONST_OPPRESSIVE_DRUG_LAWS = "Oppressive Drug Laws";
const string CONST_RACIAL_EQUALITY = "Racial Equality";
const string CONST_GENDER_EQUALITY = "Gender Equality";
const string CONST_X_CEO_COMPENSATION = "CEO Compensation";
const string CONST_X_CORPORATE_CORRUPTION = "Corporate Corruption";
const string CONST_MASS_SHOOTINGS = "Mass Shootings";
const string CONST_THE_JUDICIARY = "The Judiciary";
const string CONST_DANGEROUS_GMOS = "Dangerous GMOs";
const string CONST_X_THE_PRISON_SYSTEM = "The Prison System";
const string CONST_X_TORTURE = "Torture";
const string CONST_POLICE_MISCONDUCT = "Police Misconduct";
const string CONST_X_ANIMAL_CRUELTY = "Animal Cruelty";
const string CONST_NUCLEAR_MELTDOWNS = "Nuclear Meltdowns";
const string CONST_THE_TAX_STRUCTURE = "The Tax Structure";
const string CONST_BARBARIC_EXECUTIONS = "Barbaric Executions";
const string CONST_X_LGBTQ_RIGHTS = "LGBTQ Rights";
const string CONST_X_PUBLIC_MOOD = "Public Mood";
const string CONST_PLAY_LIBERAL_MUSIC = "Play Liberal Music";
const string CONST_SELL_PAINTINGS = "Sell Paintings";
const string CONST_SELL_EMBROIDERED_SHIRTS = "Sell Embroidered Shirts";
const string CONST_ENHANCING_INTERROGATIONS = "enhancing interrogations.";
const string CONST_THE_CCS_TERRORISTS = "the CCS terrorists.";
const string CONST_DEFENDING_THE_NATION = "defending the nation.";
const string CONST_PROTECTING_THE_SECOND_AMENDMENT = "protecting the Second Amendment.";
const string CONST_TROUBLEMAKING_MINORITIES = "troublemaking minorities.";
const string CONST_WOMEN = "women.";
const string CONST_DRUG_ABUSE = "drug abuse.";
const string CONST_ILLEGAL_IMMIGRATION = "illegal immigration.";
const string CONST_PUTTING_THE_PRISONERS_IN_LINE = "putting the prisoners in line.";
const string CONST_RESISTING_COMMUNIST_WAGE_LIMITS = "resisting communist wage limits.";
const string CONST_EXCESSIVE_REGULATION_OF_CORPORATIONS = "excessive regulation of corporations.";
const string CONST_EXCESSIVE_REGULATION_OF_INDUSTRY = "excessive regulation of industry.";
const string CONST_CORRUPT_UNION_THUGS = "corrupt union thugs.";
const string CONST_APPOINTING_PROPER_CONSERVATIVE_JUSTICES = "appointing proper Conservative justices.";
const string CONST_EXCESSIVE_REGULATION_OF_GENETIC_RESEARCH = "excessive regulation of genetic research.";
const string CONST_ENDING_HATE_SPEECH = "ending hate speech.";
const string CONST_NATIONAL_SECURITY_AND_INTELLIGENCE = "national security and intelligence.";
const string CONST_EXPANDING_POLICE_POWERS = "expanding police powers.";
const string CONST_EXCESSIVE_REGULATION_OF_ANIMAL_RESEARCH = "excessive regulation of animal research.";
const string CONST_THREATS_TO_NUCLEAR_POWER = "threats to nuclear power.";
const string CONST_THE_EXCESSIVE_TAX_BURDEN = "the excessive tax burden.";
const string CONST_PROTECTING_THE_DEATH_PENALTY = "protecting the death penalty.";
const string CONST_PROTECTING_THE_TRADITIONAL_FAMILY = "protecting the traditional family.";
const string CONST_CLASSES_COST_UP_TO_100_DAY_TO_CONDUCT_ALL_LIBERALS_ABLE_WILL_ATTEND = "Classes cost up to $100/day to conduct. All Liberals able will attend.";
const string CONST_SEDUCTION_PSYCHOLOGY_DRIVING = "Seduction, Psychology, Driving";
const string CONST_RELIGION_BUSINESS_MUSIC_ART = "Religion, Business, Music, Art";
const string CONST_PHYSICALLY_SUPERIOR = "physically superior.";
const string CONST_MAJOR_WEBSITES = "major websites.";
const string CONST_MAGICAL_SHIMMERING_DOORWAYS_TO_THE_ADAMANTIUM_PITS = "magical shimmering doorways to the adamantium pits.";
const string CONST_OR_PLAY_GUITAR_IF_ONE_IS_EQUIPPED = "or play guitar if one is equipped.";
const string CONST_WILL_MAKE_PRETTY_PAINTINGS_AND_SELL_THEM_ON_THE_STREETS = "will make pretty paintings and sell them on the streets.";
const string CONST_WILL_EMBROIDER_SHIRTS_AND_SELL_THEM_ON_THE_STREET = "will embroider shirts and sell them on the street.";
const string CONST_BASED_ON_PERSUASION_PUBLIC_S_VIEW_ON_THE_CAUSE_AND_HOW_WELL_DRESSED_THE = "Based on persuasion, public's view on the cause, and how well dressed the";
const string CONST_COMPUTER_SKILL_AND_INTELLIGENCE_WILL_GIVE_MORE_FREQUENT_RESULTS = "Computer skill and intelligence will give more frequent results.";
const string CONST_WILL_GIVE_GREATER_EFFECT = "will give greater effect.";
const string CONST_POLLS_WILL_GIVE_AN_IDEA_ON_HOW_THE_LIBERAL_AGENDA_IS_GOING_COMPUTERS = "Polls will give an idea on how the liberal agenda is going. Computers";
const string CONST_ENHANCE_THE_LIBERAL_EFFECT = "enhance the liberal effect.";
const string CONST_THAT_IS_LIBERAL = "that is Liberal.";

const string CONST_HIRING_UNDOCUMENTED_WORKERS = "Hiring undocumented workers";
const string CONST_HIRING_ILLEGAL_ALIENS = "Hiring illegal aliens";
const string CONST_X_FLAG_BURNING = "Flag burning";
const string CONST_FLAG_MURDER = "Flag Murder";
const string CONST_LOITERING = "Loitering";
const string CONST_PUBLIC_NUDITY = "Public nudity";
const string CONST_DISTURBING_THE_PEACE = "Disturbing the peace";
const string CONST_RESISTING_ARREST = "Resisting arrest";
const string CONST_VANDALISM = "Vandalism";
const string CONST_BREAKING_AND_ENTERING = "Breaking and entering";
const string CONST_UNLAWFUL_BURIAL = "Unlawful burial";
const string CONST_HACKING = "Hacking";
const string CONST_ELECTRONIC_SABOTAGE = "Electronic sabotage";
const string CONST_CARRYING_ILLEGAL_WEAPONS = "Carrying illegal weapons";
const string CONST_FIRING_ILLEGAL_WEAPONS = "Firing illegal weapons";
const string CONST_PROSTITUTION = "Prostitution";
const string CONST_THEFT = "Theft";
const string CONST_X_CREDIT_CARD_FRAUD = "Credit card fraud";
const string CONST_GRAND_THEFT_AUTO = "Grand theft auto";
const string CONST_ASSAULT = "Assault";
const string CONST_ARMED_ASSAULT = "Armed assault";
const string CONST_EXTORTION = "Extortion";
const string CONST_RACKETEERING = "Racketeering";
const string CONST_JURY_TAMPERING = "Jury tampering";
const string CONST_RELEASING_PRISONERS = "Releasing prisoners";
const string CONST_ESCAPING_PRISON = "Escaping prison";
const string CONST_DRUG_DEALING = "Drug dealing";
const string CONST_HARMFUL_SPEECH = "Harmful speech";
const string CONST_ARSON = "Arson";
const string CONST_BANK_ROBBERY = "Bank robbery";
const string CONST_KIDNAPPING = "Kidnapping";
const string CONST_MURDER = "Murder";
const string CONST_TERRORISM = "Terrorism";
const string CONST_TREASON = "Treason";
const string CONST_HUMAN_RIGHTS = "Human Rights";
const string CONST_PRISON_REGULATION = "Prison Regulation";
const string CONST_MILITARY_SPENDING = "Military Spending";
const string CONST_ELECTION_REFORM = "Election Reform";
const string CONST_X_IMMIGRATION = "Immigration";
const string CONST_DRUG_LAWS = "Drug Laws";
const string CONST_externallyStoredData673 = "Civil Rights";
const string CONST_X_WOMENS_RIGHTS = "Women's Rights";
const string CONST_TAX_STRUCTURE = "Tax Structure";
const string CONST_X_GUN_CONTROL = "Gun Control";
const string CONST_FLAG_BURNING = "Flag Burning";
const string CONST_X_FREE_SPEECH = "Free Speech";
const string CONST_CORPORATE_LAW = "Corporate Law";
const string CONST_GAY_RIGHTS = "Gay Rights";
const string CONST_LABOR_LAWS = "Labor Laws";
const string CONST_X_POLLUTION = "Pollution";
const string CONST_X_NUCLEAR_POWER = "Nuclear Power";
const string CONST_DEATH_PENALTY = "Death Penalty";
const string CONST_PRIVACY_RIGHTS = "Privacy Rights";
const string CONST_POLICE_REGULATION = "Police Regulation";
const string CONST_ANIMAL_RIGHTS = "Animal Rights";
const string CONST_ABORTION_RIGHTS = "Abortion Rights";
const string CONST_THE_CCS = "the CCS";
const string CONST_THE_LCS = "the LCS";
const string CONST_POLITICAL_VIOLENCE = "political violence";
const string CONST_CABLE_NEWS = "cable news";
const string CONST_AM_RADIO = "AM radio";
const string CONST_THE_MILITARY = "the military";
const string CONST_IMMIGRATION = "immigration";
const string CONST_DRUGS = "drugs";
const string CONST_X_CIVIL_RIGHTS = "civil rights";
const string CONST_WOMEN_S_RIGHTS = "women's rights";
const string CONST_CEO_COMPENSATION = "CEO compensation";
const string CONST_CORPORATIONS = "corporations";
const string CONST_POLLUTION = "pollution";
const string CONST_LABOR_UNIONS = "labor unions";
const string CONST_GUN_CONTROL = "gun control";
const string CONST_JUDGES = "judges";
const string CONST_GENETIC_RESEARCH = "genetic research";
const string CONST_FREE_SPEECH = "free speech";
const string CONST_PRIVACY = "privacy";
const string CONST_THE_PRISON_SYSTEM = "the prison system";
const string CONST_TORTURE = "torture";
const string CONST_COPS = "cops";
const string CONST_ANIMAL_CRUELTY = "animal cruelty";
const string CONST_NUCLEAR_POWER = "nuclear power";
const string CONST_TAXES = "taxes";
const string CONST_THE_DEATH_PENALTY = "the death penalty";
const string CONST_LGBTQ_RIGHTS = "LGBTQ rights";
const string CONST_PUBLIC_MOOD = "public mood";
const string CONST_STALINISM = "Stalinism";
const string CONST_AUGMENTING_LIBERAL = "Augmenting Liberal";
const string CONST_STEALING_EQUIPMENT = "Stealing Equipment";
const string CONST_EMBEZZLING_FUNDS = "Embezzling Funds";
const string CONST_CREATING_A_SCANDAL = "Creating a Scandal";
const string CONST_QUITTING_JOB = "Quitting Job";
const string CONST_RECRUITING_SLEEPERS = "Recruiting Sleepers";
const string CONST_SNOOPING_AROUND = "Snooping Around";
const string CONST_SPOUTING_CONSERVATISM = "Spouting Conservatism";
const string CONST_PROMOTING_LIBERALISM = "Promoting Liberalism";
const string CONST_ATTENDING_CLASSES = "Attending Classes";
const string CONST_GOING_TO_FREE_CLINIC = "Going to Free CLINIC";
const string CONST_WRITING_NEWS = "Writing news";
const string CONST_WRITING_LETTERS = "Writing letters";
const string CONST_LAYING_LOW = "Laying Low";
const string CONST_TENDING_TO_INJURIES = "Tending to Injuries";
const string CONST_SELLING_BROWNIES = "Selling Brownies";
const string CONST_SOLICITING_DONATIONS = "Soliciting Donations";
const string CONST_DISPOSING_OF_BODIES = "Disposing of Bodies";
const string CONST_SELLING_MUSIC = "Selling Music";
const string CONST_TEACHING_COVERT_OPS = "Teaching Covert Ops";
const string CONST_TEACHING_FIGHTING = "Teaching Fighting";
const string CONST_TEACHING_POLITICS = "Teaching Politics";
const string CONST_SELLING_ART = "Selling Art";
const string CONST_SELLING_T_SHIRTS = "Selling T-Shirts";
const string CONST_HACKING_NETWORKS = "Hacking Networks";
const string CONST_ATTACKING_WEBSITES = "Attacking Websites";
const string CONST_EXTORTING_WEBSITES = "Extorting Websites";
const string CONST_CREDIT_CARD_FRAUD = "Credit Card Fraud";
const string CONST_MAKING_GRAFFITI = "Making Graffiti";
const string CONST_VOLUNTEERING = "Volunteering";
const string CONST_PROSTITUTING = "Prostituting";
const string CONST_CAUSING_TROUBLE = "Causing Trouble";
const string CONST_GATHERING_OPINION_INFO = "Gathering Opinion Info";
const string CONST_STEALING_A_CAR = "Stealing a Car";
const string CONST_PROCURING_A_WHEELCHAIR = "Procuring a Wheelchair";
const string CONST_REPAIRING_CLOTHING = "Repairing Clothing";
const string CONST_X_RECRUITING = "Recruiting";
const string CONST_NEW_YORK = "New York";
const string CONST_LOS_ANGELES = "Los Angeles";
const string CONST_A_TROPICAL_PARADISE = "A Tropical Paradise.";
const string CONST_THE_PRIDE_OF_THE_SOUTH = "The Pride of the South.";
const string CONST_MURDER_CAPITAL_OF_AMERICA = "Murder Capital of America.";
const string CONST_MAFIA_HEADQUARTERS = "Mafia Headquarters.";
const string CONST_THE_NATION_S_CAPITAL = "The Nation's Capital.";
const string CONST_WALL_STREET_AND_BIG_MEDIA = "Wall Street and Big Media.";
const string CONST_HOLLYWOOD_AND_TRADE = "Hollywood and Trade.";
const string CONST_BIRTHPLACE_OF_THE_LCS = "Birthplace of the LCS.";
const string CONST_X_CLOSE_BRACKET = "]";
const string CONST_SLEEPER = "Sleeper";
const string SPACE_OPEN_BRACKET = " [";
const string CONST_IN_HIDING = "In Hiding";
const string CONST_IN_JAIL = "In Jail";
const string CONST_ARRESTED = "Arrested";
const string TWO_SPACE_OPEN_BRACKET = "   [";
const string CONST_ENLIGHTENED = "Enlightened";
const string CONST_X_BACKSLASH = "/";
const string CONST_SEDUCED = "Seduced";
const string CONST_RECRUITED = "Recruited/";
const string CONST_DAYS_UNTIL_RETURN = "DAYS UNTIL RETURN";
const string CONST_DAYS_SINCE_PASSING = "DAYS SINCE PASSING";
const string CONST_PROFESSION = "PROFESSION";
const string CONST_PROGNOSIS = "PROGNOSIS";
const string CONST_MONTHS_LEFT = "MONTHS LEFT";
const string CONST_DAYS_IN_CAPTIVITY = "DAYS IN CAPTIVITY";
const string CONST_SQUAD_ACTIVITY = "SQUAD / ACTIVITY";
const string CONST_LIBERALS_THAT_ARE_AWAY = "Liberals that are Away";
const string CONST_LIBERAL_MARTYRS_AND_DEAD_BODIES = "Liberal Martyrs and Dead Bodies";
const string CONST_X_SLEEPERS = "Sleepers";
const string CONST_LIBERALS_AND_THE_JUSTICE_SYSTEM = "Liberals and the Justice System";
const string CONST_LIBERALS_IN_CLINICS = "Liberals in CLINICS";
const string CONST_CONSERVATIVE_AUTOMATONS_IN_CAPTIVITY = "Conservative Automatons in Captivity";
const string CONST_X_ACTIVE_LIBERALS = "Active Liberals";

const string CONST_WHITEHOUSE = "WhiteHouse";
const string CONST_NUCLEARPLANT = "NuclearPlant";
const string CONST_BANK = "Bank";
const string CONST_PARK = "Park";
const string CONST_VEGANCOOP = "VeganCoOp";
const string CONST_LATTESTAND = "LatteStand";
const string CONST_CIGARBAR = "CigarBar";
const string CONST_INTERNETCAFE = "InternetCafe";
const string CONST_JUICEBAR = "JuiceBar";
const string CONST_CABLENEWS = "CableNews";
const string CONST_RADIOSTATION = "RadioStation";
const string CONST_CEOHOUSE = "CEOHouse";
const string CONST_CORPORATEHQ = "CorporateHQ";
const string CONST_FACTORY = "Factory";
const string CONST_SWEATSHOP = "Sweatshop";
const string CONST_FIRESTATION = "FireStation";
const string CONST_ARMYBASE = "ArmyBase";
const string CONST_INTELLIGENCEHQ = "IntelligenceHQ";
const string CONST_PRISON = "Prison";
const string CONST_COURTHOUSE = "Courthouse";
const string CONST_POLICESTATION = "PoliceStation";
const string CONST_GENETICSLAB = "GeneticsLab";
const string CONST_COSMETICSLAB = "CosmeticsLab";
const string CONST_BUNKER = "Bunker";
const string CONST_BOMBSHELTER = "BombShelter";
const string CONST_BARANDGRILL = "BarAndGrill";
const string CONST_CRACKHOUSE = "CrackHouse";
const string CONST_HOMELESSSHELTER = "HomelessShelter";
const string CONST_WAREHOUSE = "Warehouse";
const string CONST_APARTMENTDOWNTOWN = "ApartmentDowntown";
const string CONST_APARTMENTUNIVERSITY = "ApartmentUniversity";
const string CONST_APARTMENTINDUSTRIAL = "ApartmentIndustrial";
const string CONST_OTHER_EXPENSES = "Other Expenses";
const string CONST_T_SHIRT_MATERIALS = "T-Shirt Materials";
const string CONST_TRAINING = "Training";
const string CONST_SAFEHOUSE_INVESTMENTS = "Safehouse Investments";
const string CONST_RENT = "Rent";
const string CONST_RECRUITMENT = "Recruitment";
const string CONST_PURCHASING_GOODS = "Purchasing Goods";
const string CONST_NEW_CARS = "New Cars";
const string CONST_MANUFACTURING = "Manufacturing";
const string CONST_LEGAL_FEES = "Legal Fees";
const string CONST_HOSTAGE_TENDING = "Hostage Tending";
const string CONST_GROCERIES = "Groceries";
const string CONST_DRAWING_MATERIALS = "Drawing Materials";
const string CONST_DATING = "Dating";
const string CONST_CONFISCATED = "Confiscated";
const string CONST_ACTIVISM = "Activism";
const string CONST_OTHER_INCOME = "Other Income";
const string CONST_T_SHIRT_SALES = "T-Shirt Sales";
const string CONST_THIEVERY = "Thievery";
const string CONST_STREET_MUSIC = "Street Music";
const string CONST_PAWNING_GOODS = "Pawning Goods";
const string CONST_HUSTLING = "Hustling";
const string CONST_EMBEZZLEMENT = "Embezzlement";
const string CONST_DRAWING_SALES = "Drawing Sales";
const string CONST_DONATIONS = "Donations";
const string CONST_CAR_SALES = "Car Sales";
const string CONST_BROWNIES = "Brownies";
const string CONST_ERROR_INVALID_VALUE_FOR_SORTINGCHOICE = "ERROR: INVALID VALUE FOR SORTINGCHOICE!";
const string CONST_SQUADLESS_MEMBERS = "squadless members.";
const string CONST_AVAILABLE_LIBERALS = "available Liberals.";
const string CONST_SLEEPER_ACTIVITY = "sleeper activity.";
const string CONST_LIBERAL_ACTIVITY = "Liberal activity.";
const string CONST_PEOPLE_AWAY = "people away.";
const string CONST_DEAD_PEOPLE = "dead people.";
const string CONST_X_SLEEPERS_DOT = "sleepers.";
const string CONST_OPPRESSED_LIBERALS = "oppressed Liberals.";
const string CONST_LIBERALS_IN_HOSPITAL = "Liberals in hospital.";
const string CONST_HOSTAGES = "hostages.";
const string CONST_ACTIVE_LIBERALS = "active Liberals.";
const string CONST_TEACHER = "Teacher";
const string CONST_TAXI_DRIVER = "Taxi Driver";
const string CONST_PSYCHOLOGIST = "Psychologist";
const string CONST_PROSTITUTE = "Prostitute";
const string CONST_MUTANT = "Mutant";
const string CONST_MUSICIAN = "Musician";
const string CONST_MARTIAL_ARTIST = "Martial Artist";
const string CONST_LOCKSMITH = "Locksmith";
const string CONST_LAWYER = "Lawyer";
const string CONST_JUDGE = "Judge";
const string CONST_JOURNALIST = "Journalist";
const string CONST_HIPPIE = "Hippie";
const string CONST_GANG_MEMBER = "Gang Member";
const string CONST_FASHION_DESIGNER = "Fashion Designer";
const string CONST_DOCTOR = "Doctor";
const string CONST_DANCER = "Dancer";
const string CONST_COMPUTER_PROGRAMMER = "Computer Programmer";
const string CONST_COLLEGE_STUDENT = "College Student";
const string CONST_ATHLETE = "Athlete";
const string CONST_ARMY_VETERAN = "Army Veteran";
const string CONST_URBAN_WARFARE = "Urban Warfare";
const string CONST_INFILTRATION = "Infiltration";
const string CONST_POLITICAL_ACTIVISM = "Political Activism";
const string CONST_TEACH_LIBERALS_ABOUT_WHAT = "Teach Liberals About What?";
const string CONST_AUGMENT_A_LIBERAL = "Augment a Liberal";
const string CONST_PROCURE_A_WHEELCHAIR = "Procure a Wheelchair";
const string CONST_STEAL_A_CAR = "Steal a Car";
const string CONST_X_REPAIR_CLOTHING = "Repair Clothing";
const string CONST_X_MAKE_CLOTHING = "Make Clothing";
const string CONST_STEAL_CREDIT_CARD_NUMBERS = "Steal Credit Card Numbers";
const string CONST_ELECTRONIC_PROTECTION_RACKET = "Electronic Protection Racket";
const string CONST_SELL_BROWNIES = "Sell Brownies";
const string CONST_PLAY_STREET_MUSIC = "Play Street Music";
const string CONST_SELL_PORTRAIT_SKETCHES = "Sell Portrait Sketches";
const string CONST_SELL_TIE_DYED_T_SHIRTS = "Sell Tie-Dyed T-Shirts";
const string CONST_SOLICIT_DONATIONS = "Solicit Donations";
const string CONST_WRITE_FOR_THE_LIBERAL_GUARDIAN = "Write for The Liberal Guardian";
const string CONST_WRITE_TO_NEWSPAPERS = "Write to Newspapers";
const string CONST_HARASS_WEBSITES = "Harass Websites";
const string CONST_SEARCH_OPINION_POLLS = "Search Opinion Polls";
const string CONST_X_GRAFFITI = "Graffiti";
const string CONST_LIBERAL_DISOBEDIENCE = "Liberal Disobedience";
const string CONST_COMMUNITY_SERVICE = "Community Service";
const string CONST_INTERCEPTED_INTERNAL_MEDIA_EMAILS = "intercepted internal media emails.";
const string CONST_PILFERED_FILES_FROM_A_CORPORATE_SERVER = "pilfered files from a Corporate server.";
const string CONST_UNCOVERED_INFORMATION_ON_DANGEROUS_RESEARCH = "uncovered information on dangerous research.";
const string CONST_DISCOVERED_EVIDENCE_OF_JUDICIAL_CORRUPTION = "discovered evidence of judicial corruption.";
const string CONST_SABOTAGED_A_GENETICS_RESEARCH_COMPANY_S_NETWORK = "sabotaged a genetics research company's network.";
const string CONST_SUBVERTED_A_CONSERVATIVE_FAMILY_FORUM = "subverted a Conservative family forum.";
const string CONST_BROKE_INTO_MILITARY_NETWORKS_LEAVING_LCS_SLOGANS = "broke into military networks leaving LCS slogans.";
const string CONST_CAUSED_A_SCARE_BY_BREAKING_INTO_A_CIA_NETWORK = "caused a scare by breaking into a CIA network.";
const string CONST_SPREAD_VIDEOS_OF_RACIST_POLICE_BRUTALITY = "spread videos of racist police brutality.";
const string CONST_PUBLISHED_EMAILS_REVEALING_CEO_TAX_EVASION = "published emails revealing CEO tax evasion.";
const string CONST_REVEALED_HUGE_POLITICAL_BIAS_IN_INS_PROCESSES = "revealed huge political bias in INS processes.";
const string CONST_BUYING_DRINKS = "Buying Drinks";
const string CONST_BASKETBALL = "Basketball";
const string CONST_POLICE_PROCEDURE = "Police Procedure";
const string CONST_BASEBALL = "Baseball";
const string CONST_MAGIC = "Magic";
const string CONST_WEAVING = "Weaving";
const string CONST_FENCING = "Fencing";
const string CONST_COMPUTER_SCIENCE = "Computer Science";
const string CONST_LOCKSMITHING = "Locksmithing";
const string CONST_EDUCATION = "Education";
const string CONST_GYMNASTICS = "Gymnastics";
const string CONST_KUNG_FU = "Kung Fu";
const string CONST_THEATRE = "Theatre";
const string CONST_PAINTING = "Painting";
const string CONST_DRIVERS_ED = "Drivers Ed";
const string CONST_PHYSICS = "Physics";
const string CONST_CRIMINAL_LAW = "Criminal Law";
const string CONST_ECONOMICS = "Economics";
const string CONST_PUBLIC_POLICY = "Public Policy";
const string CONST_ENDING_THE_USE_OF_TORTURE = "ending the use of torture.";
const string CONST_THE_CONSERVATIVE_CRIME_SQUAD = "the Conservative Crime Squad.";
const string CONST_MILITARY_IMPERIALISM = "military imperialism.";
const string CONST_GUN_VIOLENCE = "gun violence.";
const string CONST_CIVIL_RIGHTS = "civil rights.";
const string CONST_WOMEN_S_EQUALITY = "women's equality.";
const string CONST_DRUG_RIGHTS = "drug rights.";
const string CONST_IMMIGRANT_RIGHTS = "immigrant rights.";
const string CONST_STOPPING_THE_PRISONERS_SUFFERING = "stopping the prisoners' suffering.";
const string CONST_SEVERE_INCOME_INEQUALITY = "severe income inequality.";
const string CONST_CORPORATE_CORRUPTION = "corporate corruption.";
const string CONST_THREATS_TO_THE_ENVIRONMENT = "threats to the environment.";
const string CONST_THREATS_TO_LABOR_RIGHTS = "threats to labor rights.";
const string CONST_APPOINTING_PROPER_LIBERAL_JUSTICES = "appointing proper Liberal justices.";
const string CONST_THE_DANGERS_OF_GENETIC_ENGINEERING = "the dangers of genetic engineering.";
const string CONST_PROTECTING_FREE_SPEECH = "protecting free speech.";
const string CONST_CIVIL_LIBERTIES_AND_PERSONAL_PRIVACY = "civil liberties and personal privacy.";
const string CONST_PREVENTING_POLICE_BRUTALITY = "preventing police brutality.";
const string CONST_BRUTAL_ANIMAL_RESEARCH_PRACTICES = "brutal animal research practices.";
const string CONST_THE_DANGERS_OF_NUCLEAR_POWER = "the dangers of nuclear power.";
const string CONST_THE_OPPRESSIVE_TAX_STRUCTURE = "the oppressive tax structure.";
const string CONST_THE_UNJUST_DEATH_PENALTY = "the unjust death penalty.";
const string CONST_PROTECTING_GAY_RIGHTS = "protecting gay rights.";
const string CONST_SKILLS_TRAINED_ALL_WEAPON_SKILLS_MARTIAL_ARTS_DODGE_FIRST_AID = "Skills Trained: All Weapon Skills, Martial Arts, Dodge, First Aid";
const string CONST_SKILLS_TRAINED_COMPUTERS_SECURITY_STEALTH_DISGUISE_TAILORING = "Skills Trained: Computers, Security, Stealth, Disguise, Tailoring,";
const string CONST_SKILLS_TRAINED_WRITING_PERSUASION_LAW_STREET_SENSE_SCIENCE = "Skills Trained: Writing, Persuasion, Law, Street Sense, Science,";
const string CONST_BURY_DEAD_BODIES = "bury dead bodies.";
const string CONST_GO_TO_THE_CLINIC = "go to the clinic.";
const string CONST_TEND_TO_HOSTAGES = "tend to hostages.";
const string CONST_ATTEMPT_FIRST_AID = "attempt first aid.";
const string CONST_WILL_AUGMENT_ANOTHER_LIBERAL_TO_MAKE_THEM = "will augment another Liberal to make them";
const string CONST_TRY_TO_FIND_A_WHEELCHAIR = "try to find a wheelchair.";
const string CONST_REPAIR_CLOTHING = "repair clothing.";
const string CONST_MAKE_CLOTHING = "make clothing.";
const string CONST_TRY_TO_FIND_AND_STEAL_A_CAR = "try to find and steal a car.";
const string CONST_TRY_TO_FIND_SOMEONE_TO_JOIN_THE_LCS = "try to find someone to join the LCS.";
const string CONST_DEMAND_MONEY_IN_EXCHANGE_FOR_NOT_BRINGING_DOWN = "demand money in exchange for not bringing down";
const string CONST_COMMIT_CREDIT_CARD_FRAUD_ONLINE = "commit credit card fraud online.";
const string CONST_TRADE_SEX_FOR_MONEY = "trade sex for money.";
const string CONST_BAKE_AND_SELL_SPECIAL_ADULT_BROWNIES_THAT_OPEN = "bake and sell special adult brownies that open";
const string CONST_GO_OUT_INTO_THE_STREETS_AND_DRUM_ON_BUCKETS = "go out into the streets and drum on buckets,";
const string CONST_SKETCH_PEOPLE_AND_SELL_PORTRAITS_BACK_TO_THEM = "sketch people and sell portraits back to them.";
const string CONST_TIE_DYE_T_SHIRTS_AND_SELL_THEM_ON_THE_STREET = "tie-dye T-shirts and sell them on the street.";
const string CONST_WALK_AROUND_AND_ASK_FOR_DONATIONS_TO_THE_LCS = "walk around and ask for donations to the LCS.";
const string CONST_WRITE_ARTICLES_FOR_THE_LCS_S_NEWSPAPER = "write articles for the LCS's newspaper.";
const string CONST_WRITE_LETTERS_TO_NEWSPAPERS_ABOUT_CURRENT_EVENTS = "write letters to newspapers about current events.";
const string CONST_HARASS_WEBSITES_AND_HACK_PRIVATE_NETWORKS = "harass websites and hack private networks.";
const string CONST_HARASS_CONSERVATIVE_WEBSITES_COMPUTER_SKILL = "harass Conservative websites. Computer skill";
const string CONST_SEARCH_THE_INTERNET_FOR_PUBLIC_OPINION_POLLS = "search the internet for public opinion polls.";
const string CONST_SPRAY_POLITICAL_GRAFFITI_ART_AND_HEART_WILL = "spray political graffiti. Art and Heart will";
const string CONST_CREATE_PUBLIC_DISTURBANCES = "create public disturbances. ";
const string CONST_HELP_THE_ELDERLY_LOCAL_LIBRARY_ANYTHING = "help the elderly, local library, anything";
const string CONST_X_STALINIZED = "stalinized";
const string CONST_X_REAGANIFIED = "reaganified";
const string CONST_X_DEFEAT = "defeat";
const string CONST_X_VICTORY = "victory";
const string CONST_X_ABORT = "abort";
const string CONST_X_ANCHOR = "anchor";
const string CONST_X_GLAMSHOW = "glamshow";
const string CONST_X_NEWSCAST = "newscast";
const string CONST_X_LACOPS = "lacops";
const string CONST_X_NEWSPAPER = "newspaper";
const string CONST_X_RECRUITING_LOWERCASE = "recruiting";
const string CONST_X_TRIAL = "trial";
const string CONST_X_FOOTCHASE = "footchase";
const string CONST_X_CARCHASE = "carchase";
const string CONST_X_CONQUER = "conquer";
const string CONST_X_DEFENSE_LOWERCASE = "defense";
const string CONST_X_HEAVYCOMBAT = "heavycombat";
const string CONST_X_PASTORALE = "Pastorale";
const string CONST_X_ALARMED = "alarmed";
const string CONST_X_SITEMODE = "sitemode";
const string CONST_X_SHOPPING = "shopping";
const string CONST_X_ELECTIONS = "elections";
const string CONST_X_CARTHEFT = "cartheft";
const string CONST_X_FINANCES = "finances";
const string CONST_X_DISBANDED = "disbanded";
const string CONST_X_LIBERALAGENDA = "liberalagenda";
const string CONST_X_REVIEWMODE = "reviewmode";
const string CONST_X_STOPEVIL = "stopevil";
const string CONST_X_SLEEPERS_LOWERCASE = "sleepers";
const string CONST_X_ACTIVATE = "activate";
const string CONST_X_SIEGE = "siege";
const string CONST_X_MARS = "Mars";
const string CONST_X_BASEMODE = "basemode";
const string CONST_X_NEWGAME = "newgame";
const string CONST_X_TITLEMODE = "titlemode";
const string CONST_X_STALINIST = "Stalinist";
const string CONST_X_ELITE_LIBERAL = "Elite Liberal";
const string CONST_X_LIBERAL = "Liberal";
const string CONST_ACTIVITY_SLEEPER_SPY5 = "Moderate";
const string CONST_X_CONSERVATIVE = "Conservative";
const string CONST_X_ARCHCONSERVATIVE = "Arch-Conservative";
const string CONST_X_CHA = "CHA";
const string CONST_X_HLTH = "HLTH";
const string CONST_X_HRT = "HRT";
const string CONST_X_INT = "INT";
const string CONST_X_WIS = "WIS";
const string CONST_X_AGI = "AGI";
const string CONST_X_STR = "STR";
const string CONST_X_DODGE = "Dodge";
const string CONST_X_FIRST_AID = "First Aid";
const string CONST_X_SEDUCTION = "Seduction";
const string CONST_X_STREET_SENSE = "Street Sense";
const string CONST_X_TEACHING = "Teaching";
const string CONST_X_STEALTH = "Stealth";
const string CONST_X_BUSINESS = "Business";
const string CONST_X_SCIENCE = "Science";
const string CONST_X_RELIGION = "Religion";
const string CONST_X_ART = "Art";
const string CONST_X_MUSIC = "Music";
const string CONST_X_WRITING = "Writing";
const string CONST_X_DRIVING = "Driving";
const string CONST_X_TAILORING = "Tailoring";
const string CONST_X_LAW = "Law";
const string CONST_X_COMPUTERS = "Computers";
const string CONST_X_DISGUISE = "Disguise";
const string CONST_X_SECURITY = "Security";
const string CONST_X_PSYCHOLOGY = "Psychology";
const string CONST_X_PERSUASION = "Persuasion";
const string CONST_X_SMG = "SMG";
const string CONST_X_SHOTGUN = "Shotgun";
const string CONST_X_HEAVY_WEAPONS = "Heavy Weapons";
const string CONST_X_RIFLE = "Rifle";
const string CONST_X_PISTOL = "Pistol";
const string CONST_X_AXE = "Axe";
const string CONST_CLUB = "Club";
const string CONST_THROWING = "Throwing";
const string CONST_SWORD = "Sword";
const string CONST_KNIFE = "Knife";
const string CONST_MARTIAL_ARTS = "Martial Arts";
const string CONST_F_SLAM_THE_BRAKES = "F - Slam the brakes!";
const string CONST_D_SWERVE_AROUND_HIM = "D - Swerve around him!";
const string CONST_A_KID_RUNS_INTO_THE_STREET_FOR_HIS_BALL = "A kid runs into the street for his ball!";
const string CONST_F_SLOW_DOWN_AND_TURN = "F - Slow down and turn!";
const string CONST_D_RUN_THE_LIGHT_ANYWAY = "D - Run the light anyway!";
const string CONST_THERE_S_A_RED_LIGHT_WITH_CROSS_TRAFFIC_AHEAD = "There's a red light with cross traffic ahead!";
const string CONST_F_SLOW_DOWN = "F - Slow down!";
const string CONST_D_SPEED_AROUND_IT = "D - Speed around it!";
const string CONST_A_TRUCK_PULLS_OUT_IN_YOUR_PATH = "A truck pulls out in your path!";
const string CONST_F_PLAY_IT_SAFE_AND_PLOW_THROUGH_IT = "F - Play it safe and plow through it!";
const string CONST_D_SWERVE_TO_AVOID_HITTING_ANYONE = "D - Swerve to avoid hitting anyone!";
const string CONST_YOU_ARE_SPEEDING_TOWARD_A_FLIMSY_FRUIT_STAND = "You are speeding toward a flimsy fruit stand!";
const string CONST_WASHINGTON_DC = "Washington, DC";
const string CONST_MIAMI_FL = "Miami, FL";
const string CONST_ATLANTA_GA = "Atlanta, GA";
const string CONST_DETROIT_MI = "Detroit, MI";
const string CONST_CHICAGO_IL = "Chicago, IL";
const string CONST_LOS_ANGELES_CA = "Los Angeles, CA";
const string CONST_NEW_YORK_NY = "New York, NY";
const string CONST_SEATTLE_WA = "Seattle, WA";
const string CONST_WERE_MURDERED_TRYING_TO_ESCAPE_FROM_A_POLICE_SIEGE_YESTERDAY_ACCORDING = "were murdered trying to escape from a police siege yesterday, according ";
const string CONST_WERE_SLAIN_TRYING_TO_ESCAPE_FROM_A_POLICE_SIEGE_YESTERDAY_ACCORDING = "were slain trying to escape from a police siege yesterday, according ";
const string CONST_WERE_MURDERED_DURING_A_POLICE_RAID_YESTERDAY_ACCORDING = "were murdered during a police raid yesterday, according ";
const string CONST_WERE_SLAIN_DURING_A_POLICE_RAID_YESTERDAY_ACCORDING = "were slain during a police raid yesterday, according ";
const string CONST_VIOLENTLY_BROKE_A_POLICE_SIEGE_YESTERDAY_ACCORDING = "violently broke a police siege yesterday, according ";
const string CONST_FOUGHT_OFF_A_POLICE_RAID_YESTERDAY_ACCORDING = "fought off a police raid yesterday, according ";
const string CONST_ESCAPED_FROM_POLICE_OFFICERS_DURING_A_RAID_YESTERDAY_ACCORDING = "escaped from police officers during a raid yesterday, according ";
const string CONST_ESCAPED_FROM_A_POLICE_SIEGE_YESTERDAY_ACCORDING = "escaped from a police siege yesterday, according ";
const string CONST_THE_STALINIST_PARTY_CLAIMS_VICTORY = "The Stalinist Party claims victory!";
const string CONST_THE_PROGRESSIVE_ELITE_SOCIAL_LIBERAL_GREEN_PARTY_CLAIMS_VICTORY = "The Progressive Elite Social Liberal Green Party claims victory!";
const string CONST_THE_LIBERAL_PARTY_CLAIMS_VICTORY = "The Liberal Party claims victory!";
const string CONST_THE_NEXT_TWO_YEARS_PROMISE_TO_BE_MORE_OF_THE_SAME = "The next two years promise to be more of the same.";
const string CONST_THE_CONSERVATIVE_PARTY_CLAIMS_VICTORY = "The Conservative Party claims victory!";
const string CONST_THE_U_S_A_FLAG_EAGLE_CONSERVATIVE_TEA_PARTY_CLAIMS_VICTORY = "The $$ U.S.A. Flag Eagle $$ Conservative Tea Party claims victory!";
const string CONST_THOUGHT_POLITICAL_VIOLENCE_WAS_JUSTIFIED = "thought political violence was justified";
const string CONST_HAVE_A_NEGATIVE_OPINION_OF_CABLE_NEWS_PROGRAMS = "have a negative opinion of cable news programs";
const string CONST_DO_NOT_LIKE_AM_RADIO = "do not like AM radio";
const string CONST_WANTED_TO_END_PRISONER_ABUSE_AND_TORTURE = "wanted to end prisoner abuse and torture";
const string CONST_HELD_THE_CONSERVATIVE_CRIME_SQUAD_IN_CONTEMPT = "held the Conservative Crime Squad in contempt";
const string CONST_OF_THESE_HELD_THE_LIBERAL_CRIME_SQUAD_IN_HIGH_REGARD = "of these held the Liberal Crime Squad in high regard";
const string CONST_RESPECTED_THE_POWER_OF_THE_LIBERAL_CRIME_SQUAD = "respected the power of the Liberal Crime Squad";
const string CONST_OPPOSED_INCREASING_MILITARY_SPENDING = "opposed increasing military spending";
const string CONST_ARE_CONCERNED_ABOUT_GUN_VIOLENCE = "are concerned about gun violence";
const string CONST_FELT_MORE_WORK_WAS_NEEDED_FOR_RACIAL_EQUALITY = "felt more work was needed for racial equality";
const string CONST_FAVORED_DOING_MORE_FOR_GENDER_EQUALITY = "favored doing more for gender equality";
const string CONST_BELIEVED_THAT_CEO_SALARIES_ARE_TOO_GREAT = "believed that CEO salaries are too great";
const string CONST_WERE_DISGUSTED_BY_CORPORATE_MALFEASANCE = "were disgusted by corporate malfeasance";
const string CONST_THOUGHT_INDUSTRY_SHOULD_LOWER_POLLUTION = "thought industry should lower pollution";
const string CONST_WOULD_BOYCOTT_COMPANIES_THAT_USED_SWEATSHOPS = "would boycott companies that used sweatshops";
const string CONST_WERE_FOR_THE_APPOINTMENT_OF_LIBERAL_JUSTICES = "were for the appointment of Liberal justices";
const string CONST_ABHORRED_GENETICALLY_ALTERED_FOOD_PRODUCTS = "abhorred genetically altered food products";
const string CONST_BELIEVED_IN_UNFETTERED_FREE_SPEECH = "believed in unfettered free speech";
const string CONST_THOUGHT_THE_INTELLIGENCE_COMMUNITY_INVADES_PRIVACY = "thought the intelligence community invades privacy";
const string CONST_WANTED_STRONGER_MEASURES_TO_PREVENT_TORTURE = "wanted stronger measures to prevent torture";
const string CONST_WERE_CRITICAL_OF_THE_POLICE = "were critical of the police";
const string CONST_DEPLORED_ANIMAL_RESEARCH = "deplored animal research";
const string CONST_WERE_TERRIFIED_OF_NUCLEAR_POWER = "were terrified of nuclear power";
const string CONST_WERE_AGAINST_CUTTING_TAXES = "were against cutting taxes";
const string CONST_OPPOSED_THE_DEATH_PENALTY = "opposed the death penalty";
const string CONST_WERE_IN_FAVOR_OF_EQUAL_RIGHTS_FOR_HOMOSEXUALS = "were in favor of equal rights for homosexuals";
const string CONST_LEFT_LEG = "left leg";
const string CONST_RIGHT_LEG = "right leg";
const string CONST_LEFT_ARM = "left arm";
const string CONST_RIGHT_ARM = "right arm";
const string CONST_LEFT_REAR_LEG = "left rear leg";
const string CONST_RIGHT_REAR_LEG = "right rear leg";
const string CONST_LEFT_FRONT_LEG = "left front leg";
const string CONST_RIGHT_FRONT_LEG = "right front leg";
const string CONST_LEFT_TREAD = "left tread";
const string CONST_RIGHT_TREAD = "right tread";
const string CONST_LEFT_SIDE = "left side";
const string CONST_RIGHT_SIDE = "right side";
const string CONST_FRONT = "front";
const string CONST_TURRET = "turret";

// These are filenames, which the variable names should reflect
const string CONST_HELPTOPICS_TXT = "helpTopics.txt";
const string CONST_STATE_BIASES_TXT = "state_biases.txt";
const string CONST_ENDGAMELAWSTRINGS_TXT = "endgameLawStrings.txt";
const string CONST_TALKABOUTTHEISSUES_TXT = "talkAboutTheIssues.txt";
const string CONST_DISCUSSESISSUES_TXT = "discussesIssues.txt";
const string CONST_DISCUSSISSUES_TXT = "discussIssues.txt";
const string CONST_LIBERALIZELAW_TXT = "liberalizeLaw.txt";
const string CONST_CONSERVATISELAW_TXT = "conservatiseLaw.txt";
const string CONST_ISSUEEVENTSTRING_TXT = "issueEventString.txt";
const string CONST_ISSUETOOLIBERAL_TXT = "issueTooLiberal.txt";
const string CONST_YOUARESTUPIDTALKABOUTISSUES_TXT = "youAreStupidTalkAboutIssues.txt";
const string CONST_CONSERVATIVELEGALARGUMENT_TXT = "conservativeLegalArgument.txt";
const string CONST_CASEREJECTED_SECONDRATECLOTHES_TXT = "caseREJECTED_SECONDRATECLOTHES.txt";
const string CONST_CASEREJECTED_DAMAGEDCLOTHES_TXT = "caseREJECTED_DAMAGEDCLOTHES.txt";
const string CONST_CASEREJECTED_BLOODYCLOTHES_TXT = "caseREJECTED_BLOODYCLOTHES.txt";
const string CONST_CASEREJECTED_SMELLFUNNY_TXT = "caseREJECTED_SMELLFUNNY.txt";
const string CONST_CASEREJECTED_DRESSCODE_TXT = "caseREJECTED_DRESSCODE.txt";
const string CONST_CASEREJECTED_UNDERAGE_TXT = "caseREJECTED_UNDERAGE.txt";
const string CONST_REJECTEDBECAUSEGUESTLIST_TXT = "rejectedBecauseGuestList.txt";
const string CONST_REJECTEDBECAUSEWEAPONS_TXT = "rejectedBecauseWeapons.txt";
const string CONST_REJECTEDBECAUSESECONDRATECLOTHES_TXT = "rejectedBecauseSecondRateClothes.txt";
const string CONST_REJECTEDBECAUSEDAMAGEDCLOTHES_TXT = "rejectedBecauseDamagedClothes.txt";
const string CONST_REJECTEDBECAUSEBLOODYCLOTHES_TXT = "rejectedBecauseBloodyClothes.txt";
const string CONST_REJECTEDBECAUSEDRESSCODE_TXT = "rejectedBecauseDresscode.txt";
const string CONST_REJECTEDBECAUSEFEMALEISH_TXT = "rejectedBecauseFemaleish.txt";
const string CONST_REJECTEDBECAUSEFEMALE_TXT = "rejectedBecauseFemale.txt";
const string CONST_REJECTEDBECAUSEUNDERAGE_TXT = "rejectedBecauseUnderage.txt";
const string CONST_REJECTEDBECAUSENUDE_TXT = "rejectedBecauseNude.txt";
const string CONST_REJECTEDBYCCS_TXT = "rejectedByCCS.txt";

// Most of these are tags, and should only be defined a single time, rather than both here and elsewhere
const string CONST_SITE_OUTDOOR_BUNKER = "SITE_OUTDOOR_BUNKER";
const string CONST_SITE_OUTDOOR_PUBLICPARK = "SITE_OUTDOOR_PUBLICPARK";
const string CONST_SITE_BUSINESS_BARANDGRILL = "SITE_BUSINESS_BARANDGRILL";
const string CONST_SITE_BUSINESS_INTERNETCAFE = "SITE_BUSINESS_INTERNETCAFE";
const string CONST_SITE_BUSINESS_VEGANCOOP = "SITE_BUSINESS_VEGANCOOP";
const string CONST_SITE_BUSINESS_LATTESTAND = "SITE_BUSINESS_LATTESTAND";
const string CONST_SITE_BUSINESS_CIGARBAR = "SITE_BUSINESS_CIGARBAR";
const string CONST_SITE_BUSINESS_JUICEBAR = "SITE_BUSINESS_JUICEBAR";
const string CONST_SITE_BUSINESS_CRACKHOUSE = "SITE_BUSINESS_CRACKHOUSE";
const string CONST_SITE_MEDIA_CABLENEWS = "SITE_MEDIA_CABLENEWS";
const string CONST_SITE_MEDIA_AMRADIO = "SITE_MEDIA_AMRADIO";
const string CONST_SITE_CORPORATE_HOUSE = "SITE_CORPORATE_HOUSE";
const string CONST_SITE_CORPORATE_HEADQUARTERS = "SITE_CORPORATE_HEADQUARTERS";
const string CONST_SITE_INDUSTRY_WAREHOUSE = "SITE_INDUSTRY_WAREHOUSE";
const string CONST_SITE_INDUSTRY_NUCLEAR = "SITE_INDUSTRY_NUCLEAR";
const string CONST_SITE_INDUSTRY_POLLUTER = "SITE_INDUSTRY_POLLUTER";
const string CONST_SITE_INDUSTRY_SWEATSHOP = "SITE_INDUSTRY_SWEATSHOP";
const string CONST_SITE_GOVERNMENT_FIRESTATION = "SITE_GOVERNMENT_FIRESTATION";
const string CONST_SITE_GOVERNMENT_INTELLIGENCEHQ = "SITE_GOVERNMENT_INTELLIGENCEHQ";
const string CONST_SITE_GOVERNMENT_PRISON = "SITE_GOVERNMENT_PRISON";
const string CONST_SITE_GOVERNMENT_COURTHOUSE = "SITE_GOVERNMENT_COURTHOUSE";
const string CONST_SITE_GOVERNMENT_POLICESTATION = "SITE_GOVERNMENT_POLICESTATION";
const string CONST_SITE_LABORATORY_GENETIC = "SITE_LABORATORY_GENETIC";
const string CONST_SITE_LABORATORY_COSMETICS = "SITE_LABORATORY_COSMETICS";
const string CONST_SITE_RESIDENTIAL_BOMBSHELTER = "SITE_RESIDENTIAL_BOMBSHELTER";
const string CONST_SITE_RESIDENTIAL_APARTMENT_UPSCALE = "SITE_RESIDENTIAL_APARTMENT_UPSCALE";
const string CONST_SITE_RESIDENTIAL_APARTMENT = "SITE_RESIDENTIAL_APARTMENT";
const string CONST_SITE_RESIDENTIAL_TENEMENT = "SITE_RESIDENTIAL_TENEMENT";
const string CONST_SITE_RESIDENTIAL_SHELTER = "SITE_RESIDENTIAL_SHELTER";
const string CONST_CREATURE_POLITICIAN = "CREATURE_POLITICIAN";
const string CONST_CREATURE_SECRET_SERVICE = "CREATURE_SECRET_SERVICE";
const string CONST_CREATURE_BANK_MANAGER = "CREATURE_BANK_MANAGER";
const string CONST_CREATURE_BANK_TELLER = "CREATURE_BANK_TELLER";
const string CONST_CREATURE_MILITARYOFFICER = "CREATURE_MILITARYOFFICER";
const string CONST_CREATURE_SEAL = "CREATURE_SEAL";
const string CONST_CREATURE_MILITARYPOLICE = "CREATURE_MILITARYPOLICE";
const string CONST_CREATURE_LOCKSMITH = "CREATURE_LOCKSMITH";
const string CONST_CREATURE_PSYCHOLOGIST = "CREATURE_PSYCHOLOGIST";
const string CONST_CREATURE_CCS_SNIPER = "CREATURE_CCS_SNIPER";
const string CONST_CREATURE_CCS_MOLOTOV = "CREATURE_CCS_MOLOTOV";
const string CONST_CREATURE_POLITICALACTIVIST = "CREATURE_POLITICALACTIVIST";
const string CONST_CREATURE_CCS_ARCHCONSERVATIVE = "CREATURE_CCS_ARCHCONSERVATIVE";
const string CONST_CREATURE_CCS_VIGILANTE = "CREATURE_CCS_VIGILANTE";
const string CONST_CREATURE_NURSE = "CREATURE_NURSE";
const string CONST_CREATURE_DOCTOR = "CREATURE_DOCTOR";
const string CONST_CREATURE_MUTANT = "CREATURE_MUTANT";
const string CONST_CREATURE_NUN = "CREATURE_NUN";
const string CONST_CREATURE_TAXIDRIVER = "CREATURE_TAXIDRIVER";
const string CONST_CREATURE_TRUCKER = "CREATURE_TRUCKER";
const string CONST_CREATURE_BIKER = "CREATURE_BIKER";
const string CONST_CREATURE_ATHLETE = "CREATURE_ATHLETE";
const string CONST_CREATURE_MARTIALARTIST = "CREATURE_MARTIALARTIST";
const string CONST_CREATURE_YOGAINSTRUCTOR = "CREATURE_YOGAINSTRUCTOR";
const string CONST_CREATURE_ACTOR = "CREATURE_ACTOR";
const string CONST_CREATURE_THIEF = "CREATURE_THIEF";
const string CONST_CREATURE_CLERK = "CREATURE_CLERK";
const string CONST_CREATURE_FASHIONDESIGNER = "CREATURE_FASHIONDESIGNER";
const string CONST_CREATURE_HAIRSTYLIST = "CREATURE_HAIRSTYLIST";
const string CONST_CREATURE_CAMERAMAN = "CREATURE_CAMERAMAN";
const string CONST_CREATURE_PHOTOGRAPHER = "CREATURE_PHOTOGRAPHER";
const string CONST_CREATURE_DANCER = "CREATURE_DANCER";
const string CONST_CREATURE_JOURNALIST = "CREATURE_JOURNALIST";
const string CONST_CREATURE_AUTHOR = "CREATURE_AUTHOR";
const string CONST_CREATURE_SCULPTOR = "CREATURE_SCULPTOR";
const string CONST_CREATURE_PAINTER = "CREATURE_PAINTER";
const string CONST_CREATURE_RETIREE = "CREATURE_RETIREE";
const string CONST_CREATURE_PROGRAMMER = "CREATURE_PROGRAMMER";
const string CONST_CREATURE_SOCIALITE = "CREATURE_SOCIALITE";
const string CONST_CREATURE_CRITIC_MUSIC = "CREATURE_CRITIC_MUSIC";
const string CONST_CREATURE_CRITIC_ART = "CREATURE_CRITIC_ART";
const string CONST_CREATURE_HIPPIE = "CREATURE_HIPPIE";
const string CONST_CREATURE_PRISONGUARD = "CREATURE_PRISONGUARD";
const string CONST_CREATURE_HARDENED_VETERAN = "CREATURE_HARDENED_VETERAN";
const string CONST_CREATURE_VETERAN = "CREATURE_VETERAN";
const string CONST_CREATURE_SOLDIER = "CREATURE_SOLDIER";
const string CONST_CREATURE_HICK = "CREATURE_HICK";
const string CONST_CREATURE_MERC = "CREATURE_MERC";
const string CONST_CREATURE_TANK = "CREATURE_TANK";
const string CONST_CREATURE_AMATEURMAGICIAN = "CREATURE_AMATEURMAGICIAN";
const string CONST_CREATURE_CONSTRUCTIONWORKER = "CREATURE_CONSTRUCTIONWORKER";
const string CONST_CREATURE_CHEF = "CREATURE_CHEF";
const string CONST_CREATURE_PLUMBER = "CREATURE_PLUMBER";
const string CONST_CREATURE_GARBAGEMAN = "CREATURE_GARBAGEMAN";
const string CONST_CREATURE_MAILMAN = "CREATURE_MAILMAN";
const string CONST_CREATURE_PROSTITUTE = "CREATURE_PROSTITUTE";
const string CONST_CREATURE_FOOTBALLCOACH = "CREATURE_FOOTBALLCOACH";
const string CONST_CREATURE_OFFICEWORKER = "CREATURE_OFFICEWORKER";
const string CONST_CREATURE_CARSALESMAN = "CREATURE_CARSALESMAN";
const string CONST_CREATURE_TELEMARKETER = "CREATURE_TELEMARKETER";
const string CONST_CREATURE_BARTENDER = "CREATURE_BARTENDER";
const string CONST_CREATURE_BARISTA = "CREATURE_BARISTA";
const string CONST_CREATURE_BAKER = "CREATURE_BAKER";
const string CONST_CREATURE_FASTFOODWORKER = "CREATURE_FASTFOODWORKER";
const string CONST_CREATURE_ENGINEER = "CREATURE_ENGINEER";
const string CONST_CREATURE_PRIEST = "CREATURE_PRIEST";
const string CONST_CREATURE_CRACKHEAD = "CREATURE_CRACKHEAD";
const string CONST_CREATURE_GANGMEMBER = "CREATURE_GANGMEMBER";
const string CONST_CREATURE_BUM = "CREATURE_BUM";
const string CONST_CREATURE_HSDROPOUT = "CREATURE_HSDROPOUT";
const string CONST_CREATURE_TEACHER = "CREATURE_TEACHER";
const string CONST_CREATURE_MATHEMATICIAN = "CREATURE_MATHEMATICIAN";
const string CONST_CREATURE_MUSICIAN = "CREATURE_MUSICIAN";
const string CONST_CREATURE_COLLEGESTUDENT = "CREATURE_COLLEGESTUDENT";
const string CONST_CREATURE_SEWERWORKER = "CREATURE_SEWERWORKER";
const string CONST_CREATURE_LAWYER = "CREATURE_LAWYER";
const string CONST_CREATURE_JUROR = "CREATURE_JUROR";
const string CONST_CREATURE_PRISONER = "CREATURE_PRISONER";
const string CONST_CREATURE_GUARDDOG = "CREATURE_GUARDDOG";
const string CONST_CREATURE_GENETIC = "CREATURE_GENETIC";
const string CONST_CREATURE_NEWSANCHOR = "CREATURE_NEWSANCHOR";
const string CONST_CREATURE_RADIOPERSONALITY = "CREATURE_RADIOPERSONALITY";
const string CONST_CREATURE_AGENT = "CREATURE_AGENT";
const string CONST_CREATURE_JUDGE_CONSERVATIVE = "CREATURE_JUDGE_CONSERVATIVE";
const string CONST_CREATURE_JUDGE_LIBERAL = "CREATURE_JUDGE_LIBERAL";
const string CONST_CREATURE_GANGUNIT = "CREATURE_GANGUNIT";
const string CONST_CREATURE_EDUCATOR = "CREATURE_EDUCATOR";
const string CONST_CREATURE_FIREFIGHTER = "CREATURE_FIREFIGHTER";
const string CONST_CREATURE_DEATHSQUAD = "CREATURE_DEATHSQUAD";
const string CONST_CREATURE_SWAT = "CREATURE_SWAT";
const string CONST_CREATURE_COP = "CREATURE_COP";
const string CONST_CREATURE_TEENAGER = "CREATURE_TEENAGER";
const string CONST_CREATURE_LANDLORD = "CREATURE_LANDLORD";
const string CONST_CREATURE_WORKER_FACTORY_UNION = "CREATURE_WORKER_FACTORY_UNION";
const string CONST_CREATURE_WORKER_SECRETARY = "CREATURE_WORKER_SECRETARY";
const string CONST_CREATURE_WORKER_FACTORY_CHILD = "CREATURE_WORKER_FACTORY_CHILD";
const string CONST_CREATURE_WORKER_FACTORY_NONUNION = "CREATURE_WORKER_FACTORY_NONUNION";
const string CONST_CREATURE_WORKER_SWEATSHOP = "CREATURE_WORKER_SWEATSHOP";
const string CONST_CREATURE_WORKER_JANITOR = "CREATURE_WORKER_JANITOR";
const string CONST_CREATURE_WORKER_SERVANT = "CREATURE_WORKER_SERVANT";
const string CONST_CREATURE_CORPORATE_CEO = "CREATURE_CORPORATE_CEO";
const string CONST_CREATURE_CORPORATE_MANAGER = "CREATURE_CORPORATE_MANAGER";
const string CONST_CREATURE_SCIENTIST_EMINENT = "CREATURE_SCIENTIST_EMINENT";
const string CONST_CREATURE_SCIENTIST_LABTECH = "CREATURE_SCIENTIST_LABTECH";
const string CONST_CREATURE_SECURITYGUARD = "CREATURE_SECURITYGUARD";
const string CONST_CREATURE_BOUNCER = "CREATURE_BOUNCER";
const string CONST_ATTRIBUTE_CHARISMA = "ATTRIBUTE_CHARISMA";
const string CONST_ATTRIBUTE_HEALTH = "ATTRIBUTE_HEALTH";
const string CONST_ATTRIBUTE_STRENGTH = "ATTRIBUTE_STRENGTH";
const string CONST_ATTRIBUTE_AGILITY = "ATTRIBUTE_AGILITY";
const string CONST_ATTRIBUTE_INTELLIGENCE = "ATTRIBUTE_INTELLIGENCE";
const string CONST_ATTRIBUTE_WISDOM = "ATTRIBUTE_WISDOM";
const string CONST_ATTRIBUTE_HEART = "ATTRIBUTE_HEART";
const string CONST_SKILL_WRITING = "SKILL_WRITING";
const string CONST_SKILL_THROWING = "SKILL_THROWING";
const string CONST_SKILL_TEACHING = "SKILL_TEACHING";
const string CONST_SKILL_TAILORING = "SKILL_TAILORING";
const string CONST_SKILL_SWORD = "SKILL_SWORD";
const string CONST_SKILL_STREETSENSE = "SKILL_STREETSENSE";
const string CONST_SKILL_STEALTH = "SKILL_STEALTH";
const string CONST_SKILL_SMG = "SKILL_SMG";
const string CONST_SKILL_SHOTGUN = "SKILL_SHOTGUN";
const string CONST_SKILL_SEDUCTION = "SKILL_SEDUCTION";
const string CONST_SKILL_SECURITY = "SKILL_SECURITY";
const string CONST_SKILL_SCIENCE = "SKILL_SCIENCE";
const string CONST_SKILL_RIFLE = "SKILL_RIFLE";
const string CONST_SKILL_RELIGION = "SKILL_RELIGION";
const string CONST_SKILL_PSYCHOLOGY = "SKILL_PSYCHOLOGY";
const string CONST_SKILL_PISTOL = "SKILL_PISTOL";
const string CONST_SKILL_PERSUASION = "SKILL_PERSUASION";
const string CONST_SKILL_MUSIC = "SKILL_MUSIC";
const string CONST_SKILL_HANDTOHAND = "SKILL_HANDTOHAND";
const string CONST_SKILL_LAW = "SKILL_LAW";
const string CONST_SKILL_KNIFE = "SKILL_KNIFE";
const string CONST_SKILL_HEAVYWEAPONS = "SKILL_HEAVYWEAPONS";
const string CONST_SKILL_FIRSTAID = "SKILL_FIRSTAID";
const string CONST_SKILL_DRIVING = "SKILL_DRIVING";
const string CONST_SKILL_DODGE = "SKILL_DODGE";
const string CONST_SKILL_DISGUISE = "SKILL_DISGUISE";
const string CONST_SKILL_COMPUTERS = "SKILL_COMPUTERS";
const string CONST_SKILL_CLUB = "SKILL_CLUB";
const string CONST_SKILL_BUSINESS = "SKILL_BUSINESS";
const string CONST_SKILL_AXE = "SKILL_AXE";
const string CONST_SKILL_ART = "SKILL_ART";
const string CONST_TRINKET = "TRINKET";
const string CONST_SILVERWARE = "SILVERWARE";
const string CONST_WATCH = "WATCH";
const string CONST_MICROPHONE = "MICROPHONE";
const string CONST_CELLPHONE = "CELLPHONE";
const string CONST_FINEJEWELERY = "FINEJEWELERY";
const string CONST_POLICERECORDS = "POLICERECORDS";
const string CONST_AMRADIOFILES = "AMRADIOFILES";
const string CONST_CABLENEWSFILES = "CABLENEWSFILES";
const string CONST_PRISONFILES = "PRISONFILES";
const string CONST_RESEARCHFILES = "RESEARCHFILES";
const string CONST_JUDGEFILES = "JUDGEFILES";
const string CONST_CORPFILES = "CORPFILES";
const string CONST_INTHQDISK = "INTHQDISK";
const string CONST_CEOPHOTOS = "CEOPHOTOS";
const string CONST_SECRETDOCUMENTS = "SECRETDOCUMENTS";
const string CONST_CHEAPJEWELERY = "CHEAPJEWELERY";
const string CONST_LAPTOP = "LAPTOP";
const string CONST_LABEQUIPMENT = "LABEQUIPMENT";
const string CONST_PDA = "PDA";
const string CONST_CHEMICAL = "CHEMICAL";
const string CONST_FINECLOTH = "FINECLOTH";
const string CONST_CLUB_BOUNCER_SECONDVISIT = "CLUB_BOUNCER_SECONDVISIT";
const string CONST_CLUB_BOUNCER = "CLUB_BOUNCER";
const string CONST_STAIRS_DOWN = "STAIRS_DOWN";
const string CONST_STAIRS_UP = "STAIRS_UP";
const string CONST_PARK_BENCH = "PARK_BENCH";
const string CONST_CAFE_COMPUTER = "CAFE_COMPUTER";
const string CONST_RESTAURANT_TABLE = "RESTAURANT_TABLE";
const string CONST_APARTMENT_SIGN = "APARTMENT_SIGN";
const string CONST_APARTMENT_LANDLORD = "APARTMENT_LANDLORD";
const string CONST_NEWS_BROADCASTSTUDIO = "NEWS_BROADCASTSTUDIO";
const string CONST_RADIO_BROADCASTSTUDIO = "RADIO_BROADCASTSTUDIO";
const string CONST_CORPORATE_FILES = "CORPORATE_FILES";
const string CONST_HOUSE_CEO = "HOUSE_CEO";
const string CONST_ARMYBASE_ARMORY = "ARMYBASE_ARMORY";
const string CONST_HOUSE_PHOTOS = "HOUSE_PHOTOS";
const string CONST_NUCLEAR_ONOFF = "NUCLEAR_ONOFF";
const string CONST_POLLUTER_EQUIPMENT = "POLLUTER_EQUIPMENT";
const string CONST_SWEATSHOP_EQUIPMENT = "SWEATSHOP_EQUIPMENT";
const string CONST_INTEL_SUPERCOMPUTER = "INTEL_SUPERCOMPUTER";
const string CONST_PRISON_CONTROL_HIGH = "PRISON_CONTROL_HIGH";
const string CONST_PRISON_CONTROL_MEDIUM = "PRISON_CONTROL_MEDIUM";
const string CONST_PRISON_CONTROL_LOW = "PRISON_CONTROL_LOW";
const string CONST_PRISON_CONTROL = "PRISON_CONTROL";
const string CONST_COURTHOUSE_JURYROOM = "COURTHOUSE_JURYROOM";
const string CONST_COURTHOUSE_LOCKUP = "COURTHOUSE_LOCKUP";
const string CONST_POLICESTATION_LOCKUP = "POLICESTATION_LOCKUP";
const string CONST_LAB_GENETIC_CAGEDANIMALS = "LAB_GENETIC_CAGEDANIMALS";
const string CONST_LAB_COSMETICS_CAGEDANIMALS = "LAB_COSMETICS_CAGEDANIMALS";
const string CONST_OUTDOOR_PUBLICPARK = "OUTDOOR_PUBLICPARK";
const string CONST_GENERIC_ONEROOM = "GENERIC_ONEROOM";
const string CONST_OUTDOOR_LATTESTAND = "OUTDOOR_LATTESTAND";
const string CONST_BUSINESS_RESTRICTEDCAFE = "BUSINESS_RESTRICTEDCAFE";
const string CONST_BUSINESS_INTERNETCAFE = "BUSINESS_INTERNETCAFE";
const string CONST_BUSINESS_CAFE = "BUSINESS_CAFE";
const string CONST_MEDIA_CABLENEWS = "MEDIA_CABLENEWS";
const string CONST_MEDIA_AMRADIO = "MEDIA_AMRADIO";
const string CONST_CORPORATE_HOUSE = "CORPORATE_HOUSE";
const string CONST_CORPORATE_HEADQUARTERS = "CORPORATE_HEADQUARTERS";
const string CONST_INDUSTRY_NUCLEAR = "INDUSTRY_NUCLEAR";
const string CONST_INDUSTRY_POLLUTER = "INDUSTRY_POLLUTER";
const string CONST_INDUSTRY_SWEATSHOP = "INDUSTRY_SWEATSHOP";
const string CONST_GOVERNMENT_ARMYBASE = "GOVERNMENT_ARMYBASE";
const string CONST_GOVERNMENT_WHITE_HOUSE = "GOVERNMENT_WHITE_HOUSE";
const string CONST_GOVERNMENT_INTELLIGENCEHQ = "GOVERNMENT_INTELLIGENCEHQ";
const string CONST_GOVERNMENT_PRISON = "GOVERNMENT_PRISON";
const string CONST_GOVERNMENT_COURTHOUSE = "GOVERNMENT_COURTHOUSE";
const string CONST_GOVERNMENT_POLICESTATION = "GOVERNMENT_POLICESTATION";
const string CONST_LABORATORY_GENETICS = "LABORATORY_GENETICS";
const string CONST_LABORATORY_COSMETICS = "LABORATORY_COSMETICS";
const string CONST_GENERIC_LOBBY = "GENERIC_LOBBY";
const string CONST_GENERIC_UNSECURE = "GENERIC_UNSECURE";
const string CONST_RESIDENTIAL_APARTMENT = "RESIDENTIAL_APARTMENT";
const string CONST_VIEWNUM = "VIEWNUM";
const string CONST_VIEW_CONSERVATIVECRIMESQUAD = "VIEW_CONSERVATIVECRIMESQUAD";
const string CONST_VIEW_LIBERALCRIMESQUADPOS = "VIEW_LIBERALCRIMESQUADPOS";
const string CONST_VIEW_LIBERALCRIMESQUAD = "VIEW_LIBERALCRIMESQUAD";
const string CONST_VIEW_CABLENEWS = "VIEW_CABLENEWS";
const string CONST_VIEW_AMRADIO = "VIEW_AMRADIO";
const string CONST_VIEW_PRISONS = "VIEW_PRISONS";
const string CONST_VIEW_MILITARY = "VIEW_MILITARY";
const string CONST_VIEW_IMMIGRATION = "VIEW_IMMIGRATION";
const string CONST_VIEW_DRUGS = "VIEW_DRUGS";
const string CONST_VIEW_CIVILRIGHTS = "VIEW_CIVILRIGHTS";
const string CONST_VIEW_WOMEN = "VIEW_WOMEN";
const string CONST_VIEW_CEOSALARY = "VIEW_CEOSALARY";
const string CONST_VIEW_CORPORATECULTURE = "VIEW_CORPORATECULTURE";
const string CONST_VIEW_POLLUTION = "VIEW_POLLUTION";
const string CONST_VIEW_SWEATSHOPS = "VIEW_SWEATSHOPS";
const string CONST_VIEW_GUNCONTROL = "VIEW_GUNCONTROL";
const string CONST_VIEW_JUSTICES = "VIEW_JUSTICES";
const string CONST_VIEW_GENETICS = "VIEW_GENETICS";
const string CONST_VIEW_FREESPEECH = "VIEW_FREESPEECH";
const string CONST_VIEW_INTELLIGENCE = "VIEW_INTELLIGENCE";
const string CONST_VIEW_TORTURE = "VIEW_TORTURE";
const string CONST_VIEW_POLICEBEHAVIOR = "VIEW_POLICEBEHAVIOR";
const string CONST_VIEW_ANIMALRESEARCH = "VIEW_ANIMALRESEARCH";
const string CONST_VIEW_NUCLEARPOWER = "VIEW_NUCLEARPOWER";
const string CONST_VIEW_TAXES = "VIEW_TAXES";
const string CONST_VIEW_DEATHPENALTY = "VIEW_DEATHPENALTY";
const string CONST_VIEW_GAY = "VIEW_GAY";
const string CONST_VIEW_MOOD = "VIEW_MOOD";
const string CONST_VIEW_STALIN = "VIEW_STALIN";
const string CONST_LAWNUM = "LAWNUM";
const string CONST_LAW_TORTURE = "LAW_TORTURE";
const string CONST_LAW_PRISONS = "LAW_PRISONS";
const string CONST_LAW_MILITARY = "LAW_MILITARY";
const string CONST_LAW_ELECTIONS = "LAW_ELECTIONS";
const string CONST_LAW_IMMIGRATION = "LAW_IMMIGRATION";
const string CONST_LAW_DRUGS = "LAW_DRUGS";
const string CONST_LAW_CIVILRIGHTS = "LAW_CIVILRIGHTS";
const string CONST_LAW_WOMEN = "LAW_WOMEN";
const string CONST_LAW_TAX = "LAW_TAX";
const string CONST_LAW_GUNCONTROL = "LAW_GUNCONTROL";
const string CONST_LAW_FLAGBURNING = "LAW_FLAGBURNING";
const string CONST_LAW_FREESPEECH = "LAW_FREESPEECH";
const string CONST_LAW_CORPORATE = "LAW_CORPORATE";
const string CONST_LAW_GAY = "LAW_GAY";
const string CONST_LAW_LABOR = "LAW_LABOR";
const string CONST_LAW_POLLUTION = "LAW_POLLUTION";
const string CONST_LAW_NUCLEARPOWER = "LAW_NUCLEARPOWER";
const string CONST_LAW_DEATHPENALTY = "LAW_DEATHPENALTY";
const string CONST_LAW_PRIVACY = "LAW_PRIVACY";
const string CONST_LAW_POLICEBEHAVIOR = "LAW_POLICEBEHAVIOR";
const string CONST_LAW_ANIMALRESEARCH = "LAW_ANIMALRESEARCH";
const string CONST_LAW_ABORTION = "LAW_ABORTION";
const string CONST_LAW_MOOD = "LAW_MOOD";
const string CONST_LAW_STALIN = "LAW_STALIN";
const string CONST_THEGREATUNKNOWN = "theGreatUnknown";
const string CONST_ACTIVITYNUM = "ACTIVITYNUM";
const string CONST_ACTIVITY_AUGMENT = "ACTIVITY_AUGMENT";
const string CONST_X_OPEN = "OPEN";
const string CONST_X_FIRE_END = "FIRE_END";
const string CONST_X_FIRE_PEAK = "FIRE_PEAK";
const string CONST_X_FIRE_START = "FIRE_START";
const string CONST_ACTIVITY_RECRUITING = "ACTIVITY_RECRUITING";
const string CONST_X_GRAFFITI_OTHER = "GRAFFITI_OTHER";
const string CONST_X_GRAFFITI_CCS = "GRAFFITI_CCS";
const string CONST_X_GRAFFITI_ALLCAPS = "GRAFFITI";
const string CONST_X_DEBRIS = "DEBRIS";
const string CONST_X_OUTDOOR = "OUTDOOR";
const string CONST_X_GRASSY = "GRASSY";
const string CONST_BLOODY_2 = "BLOODY2";
const string CONST_X_BLOODY = "BLOODY";
const string CONST_X_RESTRICTED = "RESTRICTED";
const string CONST_X_CLOCK = "CLOCK";
const string CONST_ACTIVITY_SLEEPER_JOINLCS = "ACTIVITY_SLEEPER_JOINLCS";
const string CONST_X_KLOCK = "KLOCK";
const string CONST_X_LOCKED = "LOCKED";
const string CONST_X_KNOWN = "KNOWN";
const string CONST_X_DOOR = "DOOR";
const string CONST_X_BLOCK = "BLOCK";
const string CONST_X_EXIT = "EXIT";
const string CONST_ACTIVITY_STUDY_RELIGION = "ACTIVITY_STUDY_RELIGION";
const string CONST_ACTIVITY_STUDY_CLUB = "ACTIVITY_STUDY_CLUB";
const string CONST_ACTIVITY_STUDY_STREETSENSE = "ACTIVITY_STUDY_STREETSENSE";
const string CONST_ACTIVITY_STUDY_THROWING = "ACTIVITY_STUDY_THROWING";
const string CONST_ACTIVITY_STUDY_STEALTH = "ACTIVITY_STUDY_STEALTH";
const string CONST_ACTIVITY_STUDY_SEDUCTION = "ACTIVITY_STUDY_SEDUCTION";
const string CONST_ACTIVITY_CLINIC = "ACTIVITY_CLINIC";
const string CONST_ACTIVITY_HEAL = "ACTIVITY_HEAL";
const string CONST_ACTIVITY_SLEEPER_LIBERAL = "ACTIVITY_SLEEPER_LIBERAL";
const string CONST_ACTIVITY_SLEEPER_CONSERVATIVE = "ACTIVITY_SLEEPER_CONSERVATIVE";
const string CONST_ACTIVITY_SLEEPER_SPY = "ACTIVITY_SLEEPER_SPY";
const string CONST_ACTIVITY_SLEEPER_RECRUIT = "ACTIVITY_SLEEPER_RECRUIT";
const string CONST_ACTIVITY_SLEEPER_EMBEZZLE = "ACTIVITY_SLEEPER_EMBEZZLE";
const string CONST_ACTIVITY_SLEEPER_STEAL = "ACTIVITY_SLEEPER_STEAL";
const string CONST_ACTIVITY_SLEEPER_SCANDAL = "ACTIVITY_SLEEPER_SCANDAL";
const string CONST_SPECIALWOUND_LOWERSPINE = "SPECIALWOUND_LOWERSPINE";
const string CONST_ACTIVITY_STUDY_WEAVING = "ACTIVITY_STUDY_WEAVING";
const string CONST_SPECIALWOUND_UPPERSPINE = "SPECIALWOUND_UPPERSPINE";
const string CONST_SPECIALWOUND_NECK = "SPECIALWOUND_NECK";
const string CONST_SPECIALWOUND_RIBS = "SPECIALWOUND_RIBS";
const string CONST_SPECIALWOUND_SPLEEN = "SPECIALWOUND_SPLEEN";
const string CONST_SPECIALWOUND_LEFTKIDNEY = "SPECIALWOUND_LEFTKIDNEY";
const string CONST_SPECIALWOUND_RIGHTKIDNEY = "SPECIALWOUND_RIGHTKIDNEY";
const string CONST_SPECIALWOUND_STOMACH = "SPECIALWOUND_STOMACH";
const string CONST_SPECIALWOUND_LIVER = "SPECIALWOUND_LIVER";
const string CONST_SPECIALWOUND_HEART = "SPECIALWOUND_HEART";
const string CONST_SPECIALWOUND_LEFTLUNG = "SPECIALWOUND_LEFTLUNG";
const string CONST_ACTIVITY_STUDY_FENCING = "ACTIVITY_STUDY_FENCING";
const string CONST_SPECIALWOUND_RIGHTLUNG = "SPECIALWOUND_RIGHTLUNG";
const string CONST_SPECIALWOUND_TONGUE = "SPECIALWOUND_TONGUE";
const string CONST_SPECIALWOUND_NOSE = "SPECIALWOUND_NOSE";
const string CONST_SPECIALWOUND_LEFTEYE = "SPECIALWOUND_LEFTEYE";
const string CONST_SPECIALWOUND_RIGHTEYE = "SPECIALWOUND_RIGHTEYE";
const string CONST_SPECIALWOUND_TEETH = "SPECIALWOUND_TEETH";
const string CONST_SITE_GOVERNMENT_WHITE_HOUSE = "SITE_GOVERNMENT_WHITE_HOUSE";
const string CONST_SITE_GOVERNMENT_LIBERAL_PARTY_HQ = "SITE_GOVERNMENT_LIBERAL_PARTY_HQ";
const string CONST_SITE_BUSINESS_BANK = "SITE_BUSINESS_BANK";
const string CONST_SITE_GOVERNMENT_ARMYBASE = "SITE_GOVERNMENT_ARMYBASE";
const string CONST_ACTIVITY_STUDY_COMPUTERS = "ACTIVITY_STUDY_COMPUTERS";
const string CONST_ACTIVITY_STUDY_LOCKSMITHING = "ACTIVITY_STUDY_LOCKSMITHING";
const string CONST_ACTIVITY_STUDY_WRITING = "ACTIVITY_STUDY_WRITING";
const string CONST_ACTIVITY_STUDY_TEACHING = "ACTIVITY_STUDY_TEACHING";
const string CONST_ACTIVITY_STUDY_ART = "ACTIVITY_STUDY_ART";
const string CONST_ACTIVITY_STUDY_MUSIC = "ACTIVITY_STUDY_MUSIC";
const string CONST_ACTIVITY_STUDY_GYMNASTICS = "ACTIVITY_STUDY_GYMNASTICS";
const string CONST_ACTIVITY_STUDY_BUSINESS = "ACTIVITY_STUDY_BUSINESS";
const string CONST_ACTIVITY_STUDY_SCIENCE = "ACTIVITY_STUDY_SCIENCE";
const string CONST_ACTIVITY_STUDY_DISGUISE = "ACTIVITY_STUDY_DISGUISE";
const string CONST_ACTIVITY_STUDY_LAW = "ACTIVITY_STUDY_LAW";
const string CONST_ACTIVITY_STUDY_FIRST_AID = "ACTIVITY_STUDY_FIRST_AID";
const string CONST_ACTIVITY_STUDY_PSYCHOLOGY = "ACTIVITY_STUDY_PSYCHOLOGY";
const string CONST_ACTIVITY_STUDY_DRIVING = "ACTIVITY_STUDY_DRIVING";
const string CONST_ACTIVITY_STUDY_MARTIAL_ARTS = "ACTIVITY_STUDY_MARTIAL_ARTS";
const string CONST_ACTIVITY_STUDY_DEBATING = "ACTIVITY_STUDY_DEBATING";
const string CONST_ACTIVITY_TEACH_COVERT = "ACTIVITY_TEACH_COVERT";
const string CONST_ACTIVITY_TEACH_FIGHTING = "ACTIVITY_TEACH_FIGHTING";
const string CONST_ACTIVITY_TEACH_POLITICS = "ACTIVITY_TEACH_POLITICS";
const string CONST_ACTIVITY_WRITE_GUARDIAN = "ACTIVITY_WRITE_GUARDIAN";
const string CONST_ACTIVITY_WRITE_LETTERS = "ACTIVITY_WRITE_LETTERS";
const string CONST_ACTIVITY_WRITE_BLOG = "ACTIVITY_WRITE_BLOG";
const string CONST_ACTIVITY_BURY = "ACTIVITY_BURY";
const string CONST_ACTIVITY_WHEELCHAIR = "ACTIVITY_WHEELCHAIR";
const string CONST_ACTIVITY_STEALCARS = "ACTIVITY_STEALCARS";
const string CONST_ACTIVITY_MAKE_ARMOR = "ACTIVITY_MAKE_ARMOR";
const string CONST_ACTIVITY_REPAIR_ARMOR = "ACTIVITY_REPAIR_ARMOR";
const string CONST_ACTIVITY_HACKING = "ACTIVITY_HACKING";
const string CONST_ACTIVITY_DOS_ATTACKS = "ACTIVITY_DOS_ATTACKS";
const string CONST_ACTIVITY_DOS_RACKET = "ACTIVITY_DOS_RACKET";
const string CONST_ACTIVITY_CCFRAUD = "ACTIVITY_CCFRAUD";
const string CONST_ACTIVITY_POLLS = "ACTIVITY_POLLS";
const string CONST_ACTIVITY_PROSTITUTION = "ACTIVITY_PROSTITUTION";
const string CONST_ACTIVITY_SELL_DRUGS = "ACTIVITY_SELL_DRUGS";
const string CONST_ACTIVITY_DONATIONS = "ACTIVITY_DONATIONS";
const string CONST_ACTIVITY_SELL_TSHIRTS = "ACTIVITY_SELL_TSHIRTS";
const string CONST_ACTIVITY_SELL_MUSIC = "ACTIVITY_SELL_MUSIC";
const string CONST_ACTIVITY_SELL_ART = "ACTIVITY_SELL_ART";
const string CONST_ACTIVITY_COMMUNITYSERVICE = "ACTIVITY_COMMUNITYSERVICE";
const string CONST_ACTIVITY_GRAFFITI = "ACTIVITY_GRAFFITI";
const string CONST_ACTIVITY_TROUBLE = "ACTIVITY_TROUBLE";
const string CONST_ACTIVITY_HOSTAGETENDING = "ACTIVITY_HOSTAGETENDING";
const string CONST_ACTIVITY_VISIT = "ACTIVITY_VISIT";
const string CONST_ACTIVITY_NONE = "ACTIVITY_NONE";
const string SINGLE_SPACE = " ";

const string tag_LOOT = "LOOT";
const string tag_dating = "dating";
const string tag_interrogation = "interrogation";
const string tag_suspicious = "suspicious";
const string tag_body = "body";
const string tag_head = "head";
const string tag_Travel = "Travel";
const string tag_City_Outskirts = "City Outskirts";
const string tag_Outskirts = "Outskirts";
const string tag_i_District = "I-District";
const string tag_Industrial_District = "Industrial District";
const string tag_Shopping = "Shopping";
const string tag_University_District = "University District";
const string tag_u_District = "U-District";
const string tag_D = "D";
const string tag_Downtown = "Downtown";
const string tag_DC = "DC";
const string tag_Miami = "Miami";
const string tag_MI = "MI";
const string tag_ATL = "ATL";
const string tag_Atlanta = "Atlanta";
const string tag_DET = "DET";
const string tag_Detroit = "Detroit";
const string tag_Chicago = "Chicago";
const string tag_CHI = "CHI";
const string tag_NYC = "NYC";
const string tag_LA = "LA";
const string tag_SEA = "SEA";
const string tag_Seattle = "Seattle";
const string tag_LOOT_TRINKET = "LOOT_TRINKET";
const string tag_LOOT_SILVERWARE = "LOOT_SILVERWARE";
const string tag_LOOT_WATCH = "LOOT_WATCH";
const string tag_LOOT_MICROPHONE = "LOOT_MICROPHONE";
const string tag_LOOT_CELLPHONE = "LOOT_CELLPHONE";
const string tag_LOOT_EXPENSIVEJEWELERY = "LOOT_EXPENSIVEJEWELERY";
const string tag_LOOT_POLICERECORDS = "LOOT_POLICERECORDS";
const string tag_LOOT_AMRADIOFILES = "LOOT_AMRADIOFILES";
const string tag_LOOT_CABLENEWSFILES = "LOOT_CABLENEWSFILES";
const string tag_LOOT_PRISONFILES = "LOOT_PRISONFILES";
const string tag_LOOT_RESEARCHFILES = "LOOT_RESEARCHFILES";
const string tag_LOOT_JUDGEFILES = "LOOT_JUDGEFILES";
const string tag_LOOT_CORPFILES = "LOOT_CORPFILES";
const string tag_LOOT_INTHQDISK = "LOOT_INTHQDISK";
const string tag_LOOT_CEOPHOTOS = "LOOT_CEOPHOTOS";
const string tag_LOOT_SECRETDOCUMENTS = "LOOT_SECRETDOCUMENTS";
const string tag_LOOT_CHEAPJEWELERY = "LOOT_CHEAPJEWELERY";
const string tag_LOOT_COMPUTER = "LOOT_COMPUTER";
const string tag_LOOT_LABEQUIPMENT = "LOOT_LABEQUIPMENT";
const string tag_LOOT_PDA = "LOOT_PDA";
const string tag_LOOT_CHEMICAL = "LOOT_CHEMICAL";
const string tag_LOOT_FINECLOTH = "LOOT_FINECLOTH";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";


#include "../creature/creature.h"
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../customMaps.h"
#include "../set_color_support.h"
file_and_text_collection customText(vector<string>  *collection_, string fileName_) {
	file_and_text_collection newWound;
	newWound.collection = collection_;
	newWound.fileName = fileName_;
	newWound.superCollection = false;
	return newWound;
}
file_and_text_collection customText(string fileName_) {
	file_and_text_collection newWound;
	vector<string> vsr;
	vsr.push_back(SINGLE_SPACE);
	newWound.collection = &vsr;
	newWound.fileName = fileName_;
	newWound.superCollection = false;
	return newWound;
}
file_and_text_collection customText(vector<vector<string> >  *collection_, string fileName_, int dimensions_) {
	file_and_text_collection newWound;
	newWound.super_collection = collection_;
	newWound.fileName = fileName_;
	newWound.dimensions = dimensions_;
	newWound.superCollection = true;
	return newWound;
}
file_and_text_collection customText(string fileName_, int dimensions_) {
	file_and_text_collection newWound;
	newWound.fileName = fileName_;
	newWound.dimensions = dimensions_;
	newWound.superCollection = true;
	return newWound;
}
struct stringAndColor
{
	string str;
	ColorSetup type;
	stringAndColor(string str_, ColorSetup type_) : str(str_), type(type_) { }
	stringAndColor(ColorSetup type_, string str_) : str(str_), type(type_) { }
};
int getLawFromFlag(int type);

extern  map<Activity, Data_Activity> data_activities;
extern map< Activity, CreatureSkill> trainingActivity;
extern map< Views, stringConnectedToView > pollingData;
extern map<char, vector<ActivityAndString> > activate_menu_items;
extern map<int, vector<string> > caseRejectionReasons;
extern map<int, vector<string> > rejectionReasons;
extern map<short, map<short, string> > getLawFlagStringFull;
extern map<short, string> animalBodyParts;
extern map<short, string> attEnumToString;
extern map<short, string> buildThisSite;
extern map<short, string> cityNames;
extern map<short, string> conservatiseLaw;
extern map<short, string> conservativeLegalArgument;
extern map<short, string> discussesIssues;
extern map<short, string> discussIssues;
extern map<short, string> enumToCreature;
extern map<short, string> expenseTypes;
extern map<short, string> getActivityString;
extern map<short, string> getAlignString;
extern map<short, string> getCityDescription;
extern map<short, string> getLawFlagString;
extern map<short, string> getLawString;
extern map<short, string> humanBodyParts;
extern map<short, string> incomeTypes;
extern map<short, string> issueEventString;
extern map<short, string> issueTooLiberal;
extern map<short, string> liberalizeLaw;
extern map<short, string> musicList;
extern map<short, string> reviewStrings;
extern map<short, string> reviewStringsSecondLine;
extern map<short, string> siteReadMap;
extern map<short, string> skillEnumToString;
extern map<short, string> supportsLiberalLaw;
extern map<short, string> tankBodyParts;
extern map<short, string> trainingActivitySorting;
extern map<short, string> winnerOfElection;
extern map<short, string> youAreStupidTalkAboutIssues;
extern map<short, vector<string> > carchaseObstacles;
extern map<short, vector<string> > endgameLawStrings;
extern map<short, vector<string> > getSiteName;
extern map<short, vector<string> > getViewString;
extern map<short, vector<string> > helpTopics;
extern map<short, vector<string> > newsStories;
extern map<short, vector<string> > talkAboutTheIssues;
extern map<string, short> getAttributeEnumFromString;
extern map<string, short> getBaseEnumFromString;
extern map<string, short> getCreatureEnumFromString;
extern map<string, short> getSkillEnumFromString;
extern map<string, short> getSpecial;
extern map<string, short> getSpecialWoundEnumFromString;
extern map<string, short> getUnique;
extern map<string, short> site_tile_list;
extern map<string, string> getLootString;
extern vector<ActivityAndString> data_lessons;
extern vector<activityData> hackingActivities;
extern vector<CreatureTypes> ACTIVITY_TEACH_COVERT_DEFAULT;
extern vector<CreatureTypes> ACTIVITY_TEACH_FIGHTING_DEFAULT;
extern vector<CreatureTypes> ACTIVITY_TEACH_POLITICS_DEFAULT;
extern vector<int> state_biases;
extern vector<RecruitData> recruitable_creatures;
extern vector<string> theGreatUnknown;
extern vector<stringAndColor> liberalListAndColor;

vector<string> conservativeLegalArgumentUnprocessed;
vector<string> youAreStupidTalkAboutIssuesUnprocessed;
vector<string> issueTooLiberalUnprocessed;
vector<string> issueEventStringUnprocessed;
vector<string> conservatiseLawUnprocessed;
vector<string> liberalizeLawUnprocessed;
vector<string> discussIssuesUnprocessed;
vector<string> discussesIssuesUnprocessed;
vector<string> talkAboutTheIssuesUnprocessed;
vector<string> endgameLawStringsUnprocessed;
vector<string> helpTopicUnprocessed;
vector<string> state_biases_Unprocessed;
map<string, short> string_to_activity = {
	map<string, short>::value_type(CONST_ACTIVITY_NONE, ACTIVITY_NONE),
	map<string, short>::value_type(CONST_ACTIVITY_VISIT, ACTIVITY_VISIT),
	map<string, short>::value_type(CONST_ACTIVITY_HOSTAGETENDING, ACTIVITY_HOSTAGETENDING),
	map<string, short>::value_type(CONST_ACTIVITY_TROUBLE, ACTIVITY_TROUBLE),
	map<string, short>::value_type(CONST_ACTIVITY_GRAFFITI, ACTIVITY_GRAFFITI),
	map<string, short>::value_type(CONST_ACTIVITY_COMMUNITYSERVICE, ACTIVITY_COMMUNITYSERVICE),
	map<string, short>::value_type(CONST_ACTIVITY_SELL_ART, ACTIVITY_SELL_ART),
	map<string, short>::value_type(CONST_ACTIVITY_SELL_MUSIC, ACTIVITY_SELL_MUSIC),
	map<string, short>::value_type(CONST_ACTIVITY_SELL_TSHIRTS, ACTIVITY_SELL_TSHIRTS),
	map<string, short>::value_type(CONST_ACTIVITY_DONATIONS, ACTIVITY_DONATIONS),
	map<string, short>::value_type(CONST_ACTIVITY_SELL_DRUGS, ACTIVITY_SELL_DRUGS),
	map<string, short>::value_type(CONST_ACTIVITY_PROSTITUTION, ACTIVITY_PROSTITUTION),
	map<string, short>::value_type(CONST_ACTIVITY_POLLS, ACTIVITY_POLLS),
	map<string, short>::value_type(CONST_ACTIVITY_CCFRAUD, ACTIVITY_CCFRAUD),
	map<string, short>::value_type(CONST_ACTIVITY_DOS_RACKET, ACTIVITY_DOS_RACKET),
	map<string, short>::value_type(CONST_ACTIVITY_DOS_ATTACKS, ACTIVITY_DOS_ATTACKS),
	map<string, short>::value_type(CONST_ACTIVITY_HACKING, ACTIVITY_HACKING),
	map<string, short>::value_type(CONST_ACTIVITY_REPAIR_ARMOR, ACTIVITY_REPAIR_ARMOR),
	map<string, short>::value_type(CONST_ACTIVITY_MAKE_ARMOR, ACTIVITY_MAKE_ARMOR),
	map<string, short>::value_type(CONST_ACTIVITY_STEALCARS, ACTIVITY_STEALCARS),
	map<string, short>::value_type(CONST_ACTIVITY_WHEELCHAIR, ACTIVITY_WHEELCHAIR),
	map<string, short>::value_type(CONST_ACTIVITY_BURY, ACTIVITY_BURY),
	map<string, short>::value_type(CONST_ACTIVITY_WRITE_BLOG, ACTIVITY_WRITE_BLOG),
	map<string, short>::value_type(CONST_ACTIVITY_WRITE_LETTERS, ACTIVITY_WRITE_LETTERS),
	map<string, short>::value_type(CONST_ACTIVITY_WRITE_GUARDIAN, ACTIVITY_WRITE_GUARDIAN),
	map<string, short>::value_type(CONST_ACTIVITY_TEACH_POLITICS, ACTIVITY_TEACH_POLITICS),
	map<string, short>::value_type(CONST_ACTIVITY_TEACH_FIGHTING, ACTIVITY_TEACH_FIGHTING),
	map<string, short>::value_type(CONST_ACTIVITY_TEACH_COVERT, ACTIVITY_TEACH_COVERT),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_DEBATING, ACTIVITY_STUDY_DEBATING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_MARTIAL_ARTS, ACTIVITY_STUDY_MARTIAL_ARTS),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_DRIVING, ACTIVITY_STUDY_DRIVING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_PSYCHOLOGY, ACTIVITY_STUDY_PSYCHOLOGY),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_FIRST_AID, ACTIVITY_STUDY_FIRST_AID),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_LAW, ACTIVITY_STUDY_LAW),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_DISGUISE, ACTIVITY_STUDY_DISGUISE),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_SCIENCE, ACTIVITY_STUDY_SCIENCE),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_BUSINESS, ACTIVITY_STUDY_BUSINESS),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_GYMNASTICS, ACTIVITY_STUDY_GYMNASTICS),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_MUSIC, ACTIVITY_STUDY_MUSIC),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_ART, ACTIVITY_STUDY_ART),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_TEACHING, ACTIVITY_STUDY_TEACHING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_WRITING, ACTIVITY_STUDY_WRITING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_LOCKSMITHING, ACTIVITY_STUDY_LOCKSMITHING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_COMPUTERS, ACTIVITY_STUDY_COMPUTERS),
	//ACTIVITY_STUDY_COOKING
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_FENCING, ACTIVITY_STUDY_FENCING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_WEAVING, ACTIVITY_STUDY_WEAVING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_RELIGION, ACTIVITY_STUDY_RELIGION),
	//ACTIVITY_STUDY_MAGIC
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_CLUB, ACTIVITY_STUDY_CLUB),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_STREETSENSE, ACTIVITY_STUDY_STREETSENSE),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_THROWING, ACTIVITY_STUDY_THROWING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_STEALTH, ACTIVITY_STUDY_STEALTH),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_SEDUCTION, ACTIVITY_STUDY_SEDUCTION),
	map<string, short>::value_type(CONST_ACTIVITY_CLINIC, ACTIVITY_CLINIC),
	map<string, short>::value_type(CONST_ACTIVITY_HEAL, ACTIVITY_HEAL),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_LIBERAL, ACTIVITY_SLEEPER_LIBERAL),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_CONSERVATIVE, ACTIVITY_SLEEPER_CONSERVATIVE),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_SPY, ACTIVITY_SLEEPER_SPY),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_RECRUIT, ACTIVITY_SLEEPER_RECRUIT),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_SCANDAL, ACTIVITY_SLEEPER_SCANDAL),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_EMBEZZLE, ACTIVITY_SLEEPER_EMBEZZLE),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_STEAL, ACTIVITY_SLEEPER_STEAL),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_JOINLCS, ACTIVITY_SLEEPER_JOINLCS),
	map<string, short>::value_type(CONST_ACTIVITY_RECRUITING, ACTIVITY_RECRUITING),
	map<string, short>::value_type(CONST_ACTIVITY_AUGMENT, ACTIVITY_AUGMENT),
	map<string, short>::value_type(CONST_ACTIVITYNUM, ACTIVITYNUM),
	map<string, short>::value_type(CONST_THEGREATUNKNOWN, -1),
};
map<string, short> string_to_law = {
	map<string, short>::value_type(CONST_LAW_STALIN, LAW_STALIN),
	map<string, short>::value_type(CONST_LAW_MOOD, LAW_MOOD),
	map<string, short>::value_type(CONST_LAW_ABORTION, LAW_ABORTION),
	map<string, short>::value_type(CONST_LAW_ANIMALRESEARCH, LAW_ANIMALRESEARCH),
	map<string, short>::value_type(CONST_LAW_POLICEBEHAVIOR, LAW_POLICEBEHAVIOR),
	map<string, short>::value_type(CONST_LAW_PRIVACY, LAW_PRIVACY),
	map<string, short>::value_type(CONST_LAW_DEATHPENALTY, LAW_DEATHPENALTY),
	map<string, short>::value_type(CONST_LAW_NUCLEARPOWER, LAW_NUCLEARPOWER),
	map<string, short>::value_type(CONST_LAW_POLLUTION, LAW_POLLUTION),
	map<string, short>::value_type(CONST_LAW_LABOR, LAW_LABOR),
	map<string, short>::value_type(CONST_LAW_GAY, LAW_GAY),
	map<string, short>::value_type(CONST_LAW_CORPORATE, LAW_CORPORATE),
	map<string, short>::value_type(CONST_LAW_FREESPEECH, LAW_FREESPEECH),
	map<string, short>::value_type(CONST_LAW_FLAGBURNING, LAW_FLAGBURNING),
	map<string, short>::value_type(CONST_LAW_GUNCONTROL, LAW_GUNCONTROL),
	map<string, short>::value_type(CONST_LAW_TAX, LAW_TAX),
	map<string, short>::value_type(CONST_LAW_WOMEN, LAW_WOMEN),
	map<string, short>::value_type(CONST_LAW_CIVILRIGHTS, LAW_CIVILRIGHTS),
	map<string, short>::value_type(CONST_LAW_DRUGS, LAW_DRUGS),
	map<string, short>::value_type(CONST_LAW_IMMIGRATION, LAW_IMMIGRATION),
	map<string, short>::value_type(CONST_LAW_ELECTIONS, LAW_ELECTIONS),
	map<string, short>::value_type(CONST_LAW_MILITARY, LAW_MILITARY),
	map<string, short>::value_type(CONST_LAW_PRISONS, LAW_PRISONS),
	map<string, short>::value_type(CONST_LAW_TORTURE, LAW_TORTURE),
	map<string, short>::value_type(CONST_LAWNUM, LAWNUM),
};
map<string, short> string_to_view = {
	map<string, short>::value_type(CONST_VIEW_STALIN, VIEW_STALIN),
	map<string, short>::value_type(CONST_VIEW_MOOD, VIEW_MOOD),
	map<string, short>::value_type(CONST_VIEW_GAY, VIEW_GAY),
	map<string, short>::value_type(CONST_VIEW_DEATHPENALTY, VIEW_DEATHPENALTY),
	map<string, short>::value_type(CONST_VIEW_TAXES, VIEW_TAXES),
	map<string, short>::value_type(CONST_VIEW_NUCLEARPOWER, VIEW_NUCLEARPOWER),
	map<string, short>::value_type(CONST_VIEW_ANIMALRESEARCH, VIEW_ANIMALRESEARCH),
	map<string, short>::value_type(CONST_VIEW_POLICEBEHAVIOR, VIEW_POLICEBEHAVIOR),
	map<string, short>::value_type(CONST_VIEW_TORTURE, VIEW_TORTURE),
	map<string, short>::value_type(CONST_VIEW_INTELLIGENCE, VIEW_INTELLIGENCE),
	map<string, short>::value_type(CONST_VIEW_FREESPEECH, VIEW_FREESPEECH),
	map<string, short>::value_type(CONST_VIEW_GENETICS, VIEW_GENETICS),
	map<string, short>::value_type(CONST_VIEW_JUSTICES, VIEW_JUSTICES),
	map<string, short>::value_type(CONST_VIEW_GUNCONTROL, VIEW_GUNCONTROL),
	map<string, short>::value_type(CONST_VIEW_SWEATSHOPS, VIEW_SWEATSHOPS),
	map<string, short>::value_type(CONST_VIEW_POLLUTION, VIEW_POLLUTION),
	map<string, short>::value_type(CONST_VIEW_CORPORATECULTURE, VIEW_CORPORATECULTURE),
	map<string, short>::value_type(CONST_VIEW_CEOSALARY, VIEW_CEOSALARY),
	map<string, short>::value_type(CONST_VIEW_WOMEN, VIEW_WOMEN),
	map<string, short>::value_type(CONST_VIEW_CIVILRIGHTS, VIEW_CIVILRIGHTS),
	map<string, short>::value_type(CONST_VIEW_DRUGS, VIEW_DRUGS),
	map<string, short>::value_type(CONST_VIEW_IMMIGRATION, VIEW_IMMIGRATION),
	map<string, short>::value_type(CONST_VIEW_MILITARY, VIEW_MILITARY),
	map<string, short>::value_type(CONST_VIEW_PRISONS, VIEW_PRISONS),
	map<string, short>::value_type(CONST_VIEW_AMRADIO, VIEW_AMRADIO),
	map<string, short>::value_type(CONST_VIEW_CABLENEWS, VIEW_CABLENEWS),
	map<string, short>::value_type(CONST_VIEW_LIBERALCRIMESQUAD, VIEW_LIBERALCRIMESQUAD),
	map<string, short>::value_type(CONST_VIEW_LIBERALCRIMESQUADPOS, VIEW_LIBERALCRIMESQUADPOS),
	map<string, short>::value_type(CONST_VIEW_CONSERVATIVECRIMESQUAD, VIEW_CONSERVATIVECRIMESQUAD),
	map<string, short>::value_type(CONST_VIEWNUM, VIEWNUM),
};
// TODO these should have error detection, but that is kinda low priority
void processTheUnprocessed(vector<string> &unprocessed, map<short, string> &processed, map<string, short> string_to_short);
void processTheUnprocessed(vector<string> &unprocessed, map<short, vector<string> > &processed, map<string, short> string_to_short);

vector<string> rejectedByCCS;
vector<string> rejectedBecauseNude;
vector<string> rejectedBecauseUnderage;
vector<string> rejectedBecauseFemale;
vector<string> rejectedBecauseFemaleish;
vector<string> rejectedBecauseDresscode;
vector<string> rejectedBecauseBloodyClothes;
vector<string> rejectedBecauseDamagedClothes;
vector<string> rejectedBecauseSecondRateClothes;
vector<string> rejectedBecauseWeapons;
vector<string> rejectedBecauseGuestList;
// the vector<string> 'caseREJECTED' and 'rejected' are similar but not identicle.
// TODO the precise differences should be made more apparant
vector<string> caseREJECTED_UNDERAGE;
vector<string> caseREJECTED_DRESSCODE;
vector<string> caseREJECTED_SMELLFUNNY;
vector<string> caseREJECTED_BLOODYCLOTHES;
vector<string> caseREJECTED_DAMAGEDCLOTHES;
vector<string> caseREJECTED_SECONDRATECLOTHES;
vector<file_and_text_collection> externally_stored_data_text_file_collection = {
	customText(&rejectedByCCS, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBYCCS_TXT),
	customText(&rejectedBecauseNude, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSENUDE_TXT),
	customText(&rejectedBecauseUnderage, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEUNDERAGE_TXT),
	customText(&rejectedBecauseFemale, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEFEMALE_TXT),
	customText(&rejectedBecauseFemaleish, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEFEMALEISH_TXT),
	customText(&rejectedBecauseDresscode, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEDRESSCODE_TXT),
	customText(&rejectedBecauseBloodyClothes, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEBLOODYCLOTHES_TXT),
	customText(&rejectedBecauseDamagedClothes, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEDAMAGEDCLOTHES_TXT),
	customText(&rejectedBecauseSecondRateClothes, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSESECONDRATECLOTHES_TXT),
	customText(&rejectedBecauseWeapons, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEWEAPONS_TXT),
	customText(&rejectedBecauseGuestList, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEGUESTLIST_TXT),
	customText(&caseREJECTED_UNDERAGE, MOSTLY_ENDINGS_FOLDER + CONST_CASEREJECTED_UNDERAGE_TXT),
	customText(&caseREJECTED_DRESSCODE, MOSTLY_ENDINGS_FOLDER + CONST_CASEREJECTED_DRESSCODE_TXT),
	customText(&caseREJECTED_SMELLFUNNY, MOSTLY_ENDINGS_FOLDER + CONST_CASEREJECTED_SMELLFUNNY_TXT),
	customText(&caseREJECTED_BLOODYCLOTHES, MOSTLY_ENDINGS_FOLDER + CONST_CASEREJECTED_BLOODYCLOTHES_TXT),
	customText(&caseREJECTED_DAMAGEDCLOTHES, MOSTLY_ENDINGS_FOLDER + CONST_CASEREJECTED_DAMAGEDCLOTHES_TXT),
	customText(&caseREJECTED_SECONDRATECLOTHES, MOSTLY_ENDINGS_FOLDER + CONST_CASEREJECTED_SECONDRATECLOTHES_TXT),
	customText(&conservativeLegalArgumentUnprocessed, talky + CONST_CONSERVATIVELEGALARGUMENT_TXT),
	customText(&youAreStupidTalkAboutIssuesUnprocessed, talky + CONST_YOUARESTUPIDTALKABOUTISSUES_TXT),
	customText(&issueTooLiberalUnprocessed, talky + CONST_ISSUETOOLIBERAL_TXT),
	customText(&issueEventStringUnprocessed, talky + CONST_ISSUEEVENTSTRING_TXT),
	customText(&conservatiseLawUnprocessed, talky + CONST_CONSERVATISELAW_TXT),
	customText(&liberalizeLawUnprocessed, talky + CONST_LIBERALIZELAW_TXT),
	customText(&discussIssuesUnprocessed, talky + CONST_DISCUSSISSUES_TXT),
	customText(&discussesIssuesUnprocessed, talky + CONST_DISCUSSESISSUES_TXT),
	customText(&talkAboutTheIssuesUnprocessed, talky + CONST_TALKABOUTTHEISSUES_TXT),
	customText(&endgameLawStringsUnprocessed, talky + CONST_ENDGAMELAWSTRINGS_TXT),
	customText(&state_biases_Unprocessed, MOSTLY_ENDINGS_FOLDER + CONST_STATE_BIASES_TXT),
	customText(&helpTopicUnprocessed, CONST_HELPTOPICS_TXT),
};
bool initialize_more_incomplete_txt();
#endif	//EXTERNALLYSTOREDDATA_CPP
#ifdef	EXTERNALLYSTOREDTEXT_CPP
// externallyStoredText.cpp

const string CONST_NOVERBOSECOMMENTS = "NOVERBOSECOMMENTS";
const string CONST_VERBOSESAVEFILE = "VERBOSESAVEFILE";
const string CONST_ALLOWSTALIN = "ALLOWSTALIN";
const string CONST_MORERANDOM = "MORERANDOM";
const string CONST_ZEROMORAL = "ZEROMORAL";
const string CONST_INTERNAL = "INTERNAL";
const string CONST_SPINE = "SPINE";
const string CONST_NOFACE = "NOFACE";
const string CONST_NOWALK = "NOWALK";
const string CONST_BLIND = "BLIND";
const string CONST_THEFUTURE = "THEFUTURE";
const string CONST_SHOWMECHANICS = "SHOWMECHANICS";
const string CONST_SHOWWAIT = "SHOWWAIT";
const string CONST_AUTOENLIGHTEN = "AUTOENLIGHTEN";
const string CONST_HIGHFUNDS = "HIGHFUNDS";
const string CONST_GIVEBLOODYARMOR = "GIVEBLOODYARMOR";
const string CONST_REVOLUTIONNOW = "REVOLUTIONNOW";
const string CONST_PERFECTLAWS = "PERFECTLAWS";
const string CONST_SHITLAWS = "SHITLAWS";
const string CONST_NOENEMYATTACK = "NOENEMYATTACK";
const string CONST_NOSAVE = "NOSAVE";
const string CONST_DISPLAYDEBUG = "DISPLAYDEBUG";

#include "../creature/creatureEnums.h"
#include <queue>
#include <map>
#include "../customMaps.h"
struct pointerAndString {
	bool *super_collection;
	string fileName;
	pointerAndString(bool *super_, const string& file_) : fileName(file_), super_collection(super_) {}
};

/*
DEBUG DEFINES
*/
// inform player of ACTIVATED debug codes
extern bool DISPLAYDEBUG;
// Don't save the game
extern bool NOSAVE;
// Enemies don't attack
extern bool NOENEMYATTACK;
// Laws start archconservative
extern bool SHITLAWS;
// Laws start elite liberal
extern bool PERFECTLAWS;
// Public opinion starts at 100% Liberal
extern bool REVOLUTIONNOW;
// Gives you bloody armor
extern bool GIVEBLOODYARMOR;
// Start with lots of money
extern bool HIGHFUNDS;
// Interrogation always enlightens
extern bool AUTOENLIGHTEN;
// Show polls when you can't see things
extern bool SHOWWAIT;
// Show die rolls, 100% accurate poll numbers
extern bool SHOWMECHANICS;
// Make the year 2100
extern bool THEFUTURE;
// Make the founder blind
extern bool BLIND;
// Make the founder unable to walk
extern bool NOWALK;
// Make the founder have no face
extern bool NOFACE;
// Make the founder have a severely injured spine
extern bool SPINE;
// Make the founder have severe internal damage
extern bool INTERNAL;
// Make age not matter for dating or prostitution
extern bool ZEROMORAL;
// Re-seed the Random Number Generator every time it's called
extern bool MORERANDOM;
// Allow experimental, incomplete Stalinist Comrade Squad mode to be chosen for new games
extern bool ALLOWSTALIN;
// Store savefiles in plaintext, making it human readable and editable
extern bool VERBOSESAVEFILE;
// NOVERBOSECOMMENTS only affect anything if VERBOSESAVEFILE is active
// Remove almost all automatically generated comments from verbose savefiles
extern bool NOVERBOSECOMMENTS;

vector<pointerAndString> debug_defines = {
	pointerAndString(&DISPLAYDEBUG, CONST_DISPLAYDEBUG),
	pointerAndString(&NOSAVE, CONST_NOSAVE),
	pointerAndString(&NOENEMYATTACK, CONST_NOENEMYATTACK),
	pointerAndString(&SHITLAWS, CONST_SHITLAWS),
	pointerAndString(&PERFECTLAWS, CONST_PERFECTLAWS),
	pointerAndString(&REVOLUTIONNOW, CONST_REVOLUTIONNOW),
	pointerAndString(&GIVEBLOODYARMOR, CONST_GIVEBLOODYARMOR),
	pointerAndString(&HIGHFUNDS, CONST_HIGHFUNDS),
	pointerAndString(&AUTOENLIGHTEN, CONST_AUTOENLIGHTEN),
	pointerAndString(&SHOWWAIT, CONST_SHOWWAIT),
	pointerAndString(&SHOWMECHANICS, CONST_SHOWMECHANICS),
	pointerAndString(&THEFUTURE, CONST_THEFUTURE),
	pointerAndString(&BLIND, CONST_BLIND),
	pointerAndString(&NOWALK, CONST_NOWALK),
	pointerAndString(&NOFACE, CONST_NOFACE),
	pointerAndString(&SPINE, CONST_SPINE),
	pointerAndString(&INTERNAL, CONST_INTERNAL),
	pointerAndString(&ZEROMORAL, CONST_ZEROMORAL),
	pointerAndString(&MORERANDOM, CONST_MORERANDOM),
	pointerAndString(&ALLOWSTALIN, CONST_ALLOWSTALIN),
	pointerAndString(&VERBOSESAVEFILE, CONST_VERBOSESAVEFILE),
	pointerAndString(&NOVERBOSECOMMENTS, CONST_NOVERBOSECOMMENTS)
};
#endif	//EXTERNALLYSTOREDTEXT_CPP
#ifdef	FIGHT_CPP
// fight.cpp

const string fighty = "fight\\";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string CONST_S_NECK_IS_BROKEN = "'s neck is broken!";
const string CONST_S_NECK_BONES_ARE_SHATTERED = "'s neck bones are shattered!";
const string CONST_S_NOSE_IS_REMOVED = "'s nose is removed!";
const string CONST_S_NOSE_IS_CUT_OFF = "'s nose is cut off!";
const string CONST_S_NOSE_IS_TORN_OFF = "'s nose is torn off!";
const string CONST_S_NOSE_IS_BURNED_AWAY = "'s nose is burned away!";
const string CONST_S_NOSE_IS_BLASTED_OFF = "'s nose is blasted off!";
const string CONST_S_TONGUE_IS_REMOVED = "'s tongue is removed!";
const string CONST_S_TONGUE_IS_CUT_OFF = "'s tongue is cut off!";
const string CONST_S_TONGUE_IS_TORN_OUT = "'s tongue is torn out!";
const string CONST_S_TONGUE_IS_BURNED_AWAY = "'s tongue is burned away!";
const string CONST_S_TONGUE_IS_BLASTED_OFF = "'s tongue is blasted off!";
const string CONST_S_LEFT_EYE_IS_REMOVED = "'s left eye is removed!";
const string CONST_S_LEFT_EYE_IS_POKED_OUT = "'s left eye is poked out!";
const string CONST_S_LEFT_EYE_IS_TORN_OUT = "'s left eye is torn out!";
const string CONST_S_LEFT_EYE_IS_BURNED_AWAY = "'s left eye is burned away!";
const string CONST_S_LEFT_EYE_IS_BLASTED_OUT = "'s left eye is blasted out!";
const string CONST_S_RIGHT_EYE_IS_REMOVED = "'s right eye is removed!";
const string CONST_S_RIGHT_EYE_IS_POKED_OUT = "'s right eye is poked out!";
const string CONST_S_RIGHT_EYE_IS_TORN_OUT = "'s right eye is torn out!";
const string CONST_S_RIGHT_EYE_IS_BURNED_AWAY = "'s right eye is burned away!";
const string CONST_S_RIGHT_EYE_IS_BLASTED_OUT = "'s right eye is blasted out!";
const string CONST_KNOCKED_OUT = "knocked out!";
const string CONST_CUT_OUT = "cut out!";
const string CONST_GOUGED_OUT = "gouged out!";
const string CONST_BURNED_AWAY = "burned away!";
const string CONST_SHOT_OUT = "shot out!";
const string CONST_S_LAST_TOOTH_IS = "'s last tooth is ";
const string CONST_S_TEETH_IS = "'s teeth is ";
const string CONST_ONE_OF = "One of ";
const string CONST_S_TEETH_ARE = "'s teeth are ";
const string CONST_OF = " of ";
const string CONST_ALL = "All ";
const string CONST_S_FACE_IS_REMOVED = "'s face is removed!";
const string CONST_S_FACE_IS_CUT_AWAY = "'s face is cut away!";
const string CONST_S_FACE_IS_TORN_OFF = "'s face is torn off!";
const string CONST_S_FACE_IS_BURNED_AWAY = "'s face is burned away!";
const string CONST_S_FACE_IS_BLASTED_OFF = "'s face is blasted off!";
const string CONST_BROKEN = "broken!";
const string CONST_SHOT_APART = "shot apart!";
const string CONST_S_LAST_UNBROKEN_RIB_IS = "'s last unbroken rib is ";
const string CONST_S_RIB_IS = "'s rib is ";
const string CONST_S_RIBS_ARE = "'s ribs are ";
const string CONST_S_SPLEEN_IS_PUNCTURED = "'s spleen is punctured!";
const string CONST_S_SPLEEN_IS_TORN = "'s spleen is torn!";
const string CONST_S_SPLEEN_IS_BLASTED = "'s spleen is blasted!";
const string CONST_S_LEFT_KIDNEY_IS_PUNCTURED = "'s left kidney is punctured!";
const string CONST_S_LEFT_KIDNEY_IS_TORN = "'s left kidney is torn!";
const string CONST_S_LEFT_KIDNEY_IS_BLASTED = "'s left kidney is blasted!";
const string CONST_S_RIGHT_KIDNEY_IS_PUNCTURED = "'s right kidney is punctured!";
const string CONST_S_RIGHT_KIDNEY_IS_TORN = "'s right kidney is torn!";
const string CONST_S_RIGHT_KIDNEY_IS_BLASTED = "'s right kidney is blasted!";
const string CONST_S_STOMACH_IS_PUNCTURED = "'s stomach is punctured!";
const string CONST_S_STOMACH_IS_TORN = "'s stomach is torn!";
const string CONST_S_STOMACH_IS_BLASTED = "'s stomach is blasted!";
const string CONST_S_LIVER_IS_PUNCTURED = "'s liver is punctured!";
const string CONST_S_LIVER_IS_TORN = "'s liver is torn!";
const string CONST_S_LIVER_IS_BLASTED = "'s liver is blasted!";
const string CONST_S_HEART_IS_PUNCTURED = "'s heart is punctured!";
const string CONST_S_HEART_IS_TORN = "'s heart is torn!";
const string CONST_S_HEART_IS_BLASTED = "'s heart is blasted!";
const string CONST_S_LEFT_LUNG_IS_PUNCTURED = "'s left lung is punctured!";
const string CONST_S_LEFT_LUNG_IS_TORN = "'s left lung is torn!";
const string CONST_S_LEFT_LUNG_IS_BLASTED = "'s left lung is blasted!";
const string CONST_S_RIGHT_LUNG_IS_PUNCTURED = "'s right lung is punctured!";
const string CONST_S_RIGHT_LUNG_IS_TORN = "'s right lung is torn!";
const string CONST_S_RIGHT_LUNG_IS_BLASTED = "'s right lung is blasted!";
const string CONST_S_LOWER_SPINE_IS_BROKEN = "'s lower spine is broken!";
const string CONST_S_LOWER_SPINE_IS_SHATTERED = "'s lower spine is shattered!";
const string CONST_S_UPPER_SPINE_IS_BROKEN = "'s upper spine is broken!";
const string CONST_S_UPPER_SPINE_IS_SHATTERED = "'s upper spine is shattered!";
const string CONST_S_BODY = "'s body.";
const string CONST_DROPS = " drops ";
const string CONST_SUPER_ENEMY = "super enemy";
const string CONST_DANGEROUS_ENEMIES = "dangerous enemies";
const string CONST_SUPER_ENEMIES = "super enemies";
const string CONST_MISSES_COMPLETELY = " misses completely!";
const string CONST_JUST_BARELY_MISSED = " just barely missed!";
const string CONST_MISSED = " missed!";
const string CONST_KNOCKS_THE_BLOW_ASIDE_AND_COUNTERS = " knocks the blow aside and counters!";
const string CONST_TO_NO_EFFECT = " to no effect.";
const string CONST_fight152 = " BLOWING IT OFF!";
const string CONST_fight151 = " CUTTING IT OFF!";
const string CONST_fight150 = " BLOWING IT IN HALF!";
const string CONST_fight149 = " BLOWING IT APART!";
const string CONST_fight148 = " CUTTING IT IN HALF!";
const string CONST_fight146 = "!";
const string CONST_S_CORPSE = "'s corpse";
const string CONST_SHIELDS = " shields ";
const string CONST_HEROICALLY = " heroically";
const string CONST_MISGUIDEDLY = " misguidedly";
const string CONST_THE = "the ";
const string CONST_THE_ATTACK_BOUNCES_OFF = "The attack bounces off ";
const string CONST_THROUGH = " through ";
const string CONST_STRIKING = "striking";
const string CONST_X_S_SPACE = "'s ";
const string CONST_HITS = " hits ";
const string CONST_X_STABS_ = " stabs ";
const string CONST_WITH_A = " with a ";
const string CONST_SNEAKS_UP_ON = "sneaks up on";
const string CONST_BITES = "bites";
const string CONST_STABS = "stabs";
const string CONST_BREATHES_FIRE_AT = "breathes fire at";
const string CONST_FIRES_A_120MM_SHELL_AT = "fires a 120mm shell at";
const string CONST_fight126 = "gracefully strikes at";
const string CONST_fight125 = "jump kicks";
const string CONST_fight124 = "strikes at";
const string CONST_fight123 = "kicks";
const string CONST_fight122 = "grapples with";
const string CONST_fight121 = "swings at";
const string CONST_fight120 = "punches";
const string CONST_MISTAKENLY = "MISTAKENLY ";
const string CONST_READIES_ANOTHER = " readies another ";
const string CONST_RELOADS = " reloads.";
const string CONST_ACTUAL = "actual";
const string CONST_A_PLAGUE_ON_BOTH_YOUR_HOUSES = "\"A plague on both your houses...\"";
const string CONST_SPEAKS_THESE_FINAL_WORDS = " speaks these final words: ";
const string CONST_X_SOILS_THE_FLOOR = "soils the floor.";
const string CONST_X_MAKES_A_MESS = "[makes a mess].";
const string CONST_GASPS_A_LAST_BREATH_AND = " gasps a last breath and ";
const string CONST_SOMETHING_ABOUT_JESUS_AND_DIES = "something about Jesus, and dies.";
const string CONST_SOMETHING_GOOD_ABOUT_JESUS_AND_DIES = "something [good] about Jesus, and dies.";
const string CONST_SWEATS_PROFUSELY_MURMURS = " sweats profusely, murmurs ";
const string CONST_THE_NECK_HOLE_THEN_IS_QUIET = "the neck hole, then is quiet.";
const string CONST_SUCKS_A_LAST_BREATH_THROUGH = " sucks a last breath through ";
const string CONST_NECK_AND_FALLS_TO_THE_SIDE = "neck and falls to the side.";
const string CONST_NECK_AND_RUNS_DOWN_THE_HALL = "neck and runs down the hall.";
const string CONST_OUT_OF_THE = " out of the ";
const string CONST_RED_WATER = "[red water]";
const string CONST_SQUIRTS = " squirts ";
const string CONST_MOMENT_THEN_CRUMPLES_OVER = "moment then crumples over.";
const string CONST_SITS_HEADLESS_FOR_A = " sits headless for a ";
const string CONST_STANDS_HEADLESS_FOR_A = " stands headless for a ";
const string CONST_IS_NO_HEAD_AND_SLUMPS_OVER = "is no head, and slumps over.";
const string CONST_IS_NO_HEAD_AND_FALLS = "is no head, and falls.";
const string CONST_REACHES_ONCE_WHERE_THERE = " reaches once where there ";
const string CONST_HAS_BEEN_DESTROYED = " has been destroyed.";
const string CONST_S_GRASP = "'s grasp.";
const string CONST_SLIPS_FROM = " slips from";
const string CONST_NULL_BODYPART = "NULL BODYPART";
const string CONST_REMAINS_STRONG = " remains strong.";
const string CONST_HAS_TURNED_LIBERAL = " has turned Liberal!";
const string CONST_S_HEART_SWELLS = "'s Heart swells!";
const string CONST_SEEMS_LESS_BADASS = " seems less badass!";
const string CONST_DOESN_T_WANT_TO_FIGHT_ANYMORE = " doesn't want to fight anymore";
const string CONST_IS_TURNED_CONSERVATIVE = " is turned Conservative";
const string CONST_CAN_T_BEAR_TO_LEAVE = " can't bear to leave!";
const string CONST_IS_TAINTED_WITH_WISDOM = " is tainted with Wisdom!";
const string CONST_LOSES_JUICE = " loses juice!";
const string CONST_ALREADY_AGREES_WITH = " already agrees with ";
const string CONST_IS_IMMUNE_TO_THE_ATTACK = " is immune to the attack!";
const string CONST_ROCKS_OUT_AT = "rocks out at";
const string CONST_PLAYS_COUNTRY_SONGS_AT = "plays country songs at";
const string CONST_PLAYS_PROTEST_SONGS_AT = "plays protest songs at";
const string CONST_AT = " at";
const string CONST_BLOWS_A_HARMONICA = "blows a harmonica";
const string CONST_STRUMS_THE = "strums the ";
const string CONST_SINGS_TO = "sings to";
const string CONST_PLAYS_A_SONG_FOR = "plays a song for";
const string CONST_EXPLAINS_ETHICAL_RESEARCH_TO = "explains ethical research to";
const string CONST_EXPLAINS_THE_BENEFITS_OF_RESEARCH_TO = "explains the benefits of research to";
const string CONST_SPITS_UP_A_CLUSTER_OF_BLOODY_BUBBLES = " spits up a cluster of bloody bubbles.";
const string CONST_MAKES_A_MESS = " [makes a mess].";
const string CONST_VOMITS_UP_A_CLOT_OF_BLOOD = " vomits up a clot of blood.";
const string CONST_S_GUMS_START_CHATTERING = "'s gums start chattering.";
const string CONST_S_TOOTH_STARTS_CHATTERING = "'s tooth starts chattering.";
const string CONST_S_TEETH_START_CHATTERING = "'s teeth start chattering.";
const string CONST_PISSES_ON_THE_FLOOR_MOANING = " pisses on the floor, moaning.";
const string CONST_MAKES_A_MESS_MOANING = " [makes a mess], moaning.";
const string CONST_STARES_OUT_WITH_HOLLOW_SOCKETS = " stares out with hollow sockets.";
const string CONST_STARES_INTO_SPACE_WITH_ONE_EMPTY_EYE = " stares into space with one empty eye.";
const string CONST_STARES_OFF_INTO_SPACE = " stares off into space.";
const string CONST_LEANS_AGAINST_THE_DOOR = " leans against the door.";
const string CONST_STUMBLES_AGAINST_A_WALL = " stumbles against a wall.";
const string CONST_SOILS_THE_FLOOR = " soils the floor.";
const string CONST_MAKES_A_STINKY = " [makes a stinky].";
const string CONST_fight035 = " times";
const string CONST_FIVE_TIMES = " five times";
const string CONST_FOUR_TIMES = " four times";
const string CONST_THREE_TIMES = " three times";
const string CONST_TWICE = " twice";
const string CONST_EVASIONSTRINGSALT_TXT = "evasionStringsAlt.txt";
const string CONST_EVASIONSTRINGS_TXT = "evasionStrings.txt";
const string CONST_BODY_FALLS_APART_TXT = "body_falls_apart.txt";
const string CONST_DOUBLE_LINE_DEATH_TXT = "double_line_death.txt";
const string CONST_BLEEDING_ANIMAL_TXT = "bleeding_animal.txt";
const string CONST_PARALYZED_TANK_TXT = "paralyzed_tank.txt";
const string CONST_PARALYZED_TEXT_TXT = "paralyzed_text.txt";
const string CONST_STUNNED_TEXT_TXT = "stunned_text.txt";
const string CONST_BLEEDING_TO_DEATH_TXT = "bleeding_to_death.txt";
const string CONST_CRY_ALARM_TXT = "cry_alarm.txt";
const string CONST_SCIENTIST_DEBATE_TXT = "scientist_debate.txt";
const string CONST_POLICE_DEBATE_TXT = "police_debate.txt";
const string CONST_MILITARY_DEBATE_TXT = "military_debate.txt";
const string CONST_MEDIA_DEBATE_TXT = "media_debate.txt";
const string CONST_OTHER_POLITICIAN_DEBATE_TXT = "other_politician_debate.txt";
const string CONST_CONSERVATIVE_POLITICIAN_DEBATE_TXT = "conservative_politician_debate.txt";
const string CONST_OTHER_CEO_DEBATE_TXT = "other_ceo_debate.txt";
const string CONST_CONSERVATIVE_CEO_DEBATE_TXT = "conservative_ceo_debate.txt";
const string CONST_JUDGE_DEBATE_TXT = "judge_debate.txt";
const string CONST_ESCAPE_CRAWLING_TXT = "escape_crawling.txt";
const string CONST_ESCAPE_RUNNING_TXT = "escape_running.txt";
const string CONST_CRIES_MOMMY = " cries \"Mommy!\"";
const string CONST_MURMURS_WHAT_ABOUT_MY_OFFSPRING = " murmurs \"What about my offspring?\"";
const string CONST_MURMURS_WHAT_ABOUT_MY_PUPPIES = " murmurs \"What about my puppies?\"";
const string CONST_MURMURS_WHAT_ABOUT_MY_CHILDREN = " murmurs \"What about my children?\"";
const string CONST_BETTER_DEAD_THAN_LIBERAL = "\"Better dead than liberal...\"";

const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_PRISONER = "ARMOR_PRISONER";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_false = "false";
const string tag_blood = "blood";
const string tag_The = "The ";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../sitemode/stealth.h"
#include "../sitemode/sitedisplay.h"
#include "../items/money.h"
#include "../log/log.h"
// for gamelog
//#include "../common/translateid.h"
int getarmortype(const string &idname);
//#include "../common/commondisplay.h"
void printparty();
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
//#include "../combat/chaseCreature.h"
Vehicle* getChaseVehicle(const DeprecatedCreature &c);
DeprecatedCreature* getChaseDriver(const DeprecatedCreature &c);
//#include "../combat/haulkidnapCreature.h"
void freehostage(DeprecatedCreature &cr, char situation);
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/creaturePool.h"
vector<string> escape_running;
vector<string> escape_crawling;
vector<string> judge_debate;
vector<string> conservative_ceo_debate;
vector<string> other_ceo_debate;
vector<string> conservative_politician_debate;
vector<string> other_politician_debate;
vector<string> media_debate;
vector<string> military_debate;
vector<string> police_debate;
vector<string> scientist_debate;
vector<string> cry_alarm;
vector<string> bleeding_to_death;
vector<string> stunned_text;
vector<string> paralyzed_text;
vector<string> paralyzed_tank;
vector<string> bleeding_animal;
vector<vector<string> > double_line_death;
vector<string> body_falls_apart;
vector<string> evasionStringsAlt;
vector<string> evasionStrings;
const int DOUBLE_LINE = 2;
vector<file_and_text_collection> fighty_text_file_collection = {
	/*fight.cpp*/
	customText(&escape_running, fighty + CONST_ESCAPE_RUNNING_TXT),
	customText(&escape_crawling, fighty + CONST_ESCAPE_CRAWLING_TXT),
	customText(&judge_debate, fighty + CONST_JUDGE_DEBATE_TXT),
	customText(&conservative_ceo_debate, fighty + CONST_CONSERVATIVE_CEO_DEBATE_TXT),
	customText(&other_ceo_debate, fighty + CONST_OTHER_CEO_DEBATE_TXT),
	customText(&conservative_politician_debate, fighty + CONST_CONSERVATIVE_POLITICIAN_DEBATE_TXT),
	customText(&other_politician_debate, fighty + CONST_OTHER_POLITICIAN_DEBATE_TXT),
	customText(&media_debate, fighty + CONST_MEDIA_DEBATE_TXT),
	customText(&military_debate, fighty + CONST_MILITARY_DEBATE_TXT),
	customText(&police_debate, fighty + CONST_POLICE_DEBATE_TXT),
	customText(&scientist_debate, fighty + CONST_SCIENTIST_DEBATE_TXT),
	customText(&cry_alarm, fighty + CONST_CRY_ALARM_TXT),
	customText(&bleeding_to_death, fighty + CONST_BLEEDING_TO_DEATH_TXT),
	customText(&stunned_text, fighty + CONST_STUNNED_TEXT_TXT),
	customText(&paralyzed_text, fighty + CONST_PARALYZED_TEXT_TXT),
	customText(&paralyzed_tank, fighty + CONST_PARALYZED_TANK_TXT),
	customText(&bleeding_animal, fighty + CONST_BLEEDING_ANIMAL_TXT),
	customText(&double_line_death, fighty + CONST_DOUBLE_LINE_DEATH_TXT, DOUBLE_LINE),
	customText(&body_falls_apart, fighty + CONST_BODY_FALLS_APART_TXT),
	customText(&evasionStrings, MOSTLY_ENDINGS_FOLDER + CONST_EVASIONSTRINGS_TXT),
	customText(&evasionStringsAlt, MOSTLY_ENDINGS_FOLDER + CONST_EVASIONSTRINGSALT_TXT),
};

extern bool NOENEMYATTACK;
extern char foughtthisround;
extern coordinatest loc_coord;
extern DeprecatedCreature encounter[ENCMAX];
extern Deprecatednewsstoryst *sitestory;
extern Deprecatedsquadst *activesquad;
extern int ccs_boss_kills;
extern int ccs_siege_kills;
extern int sitecrime;
extern int stat_dead;
extern int stat_kills;
extern Log gamelog;
extern short lawList[LAWNUM];
extern short mode;
extern short sitealarmtimer;
extern short sitetype;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];
extern string slogan_str;
extern vector<DeprecatedCreature *> pool;

short  getCurrentSite();
void addLocationChange(int cursite, sitechangest change);



vector<Item *> groundloot;


vector<NameAndAlignment> getEncounterNameAndAlignment();
void delenc(const short e, const char loot);
string specialWoundPossibilityBody(
	DeprecatedCreature &target,
	const char breakdam,
	const char pokedam,
	const char damtype
);
string specialWoundPossibilityHead(
	DeprecatedCreature &target,
	const char breakdam,
	const char heavydam,
	const char damtype
);
map<short, string> tankBodyParts;
map<short, string> animalBodyParts;
map<short, string> humanBodyParts;
std::string burstHitString(int bursthits);
void bloodyUpEncounterArmor();
/* attack handling for an individual creature and its target */
// returns a boolean representing whether it was the intended target or CONST_ACTUAL
// so bool actual does not need to be passed by reference
bool attack(DeprecatedCreature &a, DeprecatedCreature &t, const char mistake, const bool force_melee = false);

void setSiteAlarmOne();
string howGracefulAttack(int handToHand);
string dismemberingWound(const int w, const int wound);
int bodypartSeverAmount(const int w);

class AttackInfliction {
public:
	AttackInfliction(const bool, const int, const int, const attackst);
	const bool sneak_attack;
	const int aroll;
	const int droll;
	const attackst attack_used;
};
AttackInfliction::AttackInfliction(const bool _sneak_attack, const int _aroll, const int _droll, const attackst _attack_used) : sneak_attack(_sneak_attack), aroll(_aroll < 0 ? 0 : _aroll),
	droll(_droll < 0 ? 0 : _droll),
	attack_used(_attack_used) {


}
class AttackSeverity {
public:
	AttackSeverity::AttackSeverity(const int, const int, const int, const int);
	const int damamount;
	const int damagearmor;
	const int severtype;
	const int hit_location;

};
AttackSeverity::AttackSeverity(const int _damamount, const int _damagearmor, const int _severtype, const int w) : damamount(_damamount),
damagearmor(_damagearmor),
severtype(_severtype),
hit_location(w)
{


}

struct damageDetails {
	const int mod;
	const int hit_location;
	const int extraarmor;
	const char armorpiercing;
	damageDetails(int _mod, int _hit_location, int _extraarmor, char _armorpiercing) : mod(_mod), hit_location(_hit_location), extraarmor(_extraarmor), armorpiercing(_armorpiercing) {};
};
bool attackPoolEncounter(const int p, const int t, const char mistake, const bool force_melee = false);
void addLocationChange(int cursite, sitechangest change);
bool isThereASiteAlarm();
vector<NameAndAlignment> getEncounterNameAndAlignment();
enum LOOP_CONTINUATION {
	RETURN_ZERO,
	RETURN_ONE,
	REPEAT
};
void conservatise(const int e);
#endif	//FIGHT_CPP
#ifdef	GAME_CPP
// game.cpp

#include "creature/newcreature.h"
#include "../items/armortype.h"
#include "common/interval.h"
#include "vehicle/vehicletype.h"
#include "vehicle/vehicle.h"
//#include "news/news.h"
void loadgraphics();
#include "items/loottype.h"
#include "creature/augmenttype.h"
//#include "configfile.h"
// Reads in an entire configuration file
// Returns 0 for read successful, returns -1 if failed read
int readConfigFile(const std::string& filename);
#include "log/log.h"
//for the gamelog
//#include "common/consolesupport.h"
// for getkey
#include "common/stringconversion.h"
//for string conversion
//#include "common/getnames.h"
std::string cityname();
#include "common/translateid.h"
// for  getarmortype 
#include "title/initfile.h"
//for void loadinitfile();
#include "title/titlescreen.h"
//for void mode_title();
#include "common/creaturePool.h"
#include "locations/locationsPool.h"
#include "cursesAlternative.h"
#include "customMaps.h"
/* end the game and clean up */
void end_game(int err = EXIT_SUCCESS);
#ifdef WIN32
bool fixcleartype = false;
#endif
struct pointerAndString {
	bool *super_collection;
	string fileName;
	pointerAndString(bool *super_, const string& file_) : fileName(file_), super_collection(super_) {}
};
struct fullName {
	string first;
	string middle;
	string last;

};
void init_console();
void initialize_debug_defines();
#include "common/musicClass.h"
const int CITY_NAMELEN = 80;


bool xml_population (bool xml_loaded_ok);
extern bool DISPLAYDEBUG;
extern bool PERFECTLAWS;
extern bool REVOLUTIONNOW;
extern bool SHITLAWS;
extern char artdir[MAX_PATH_SIZE];
extern char courtname[COURTNUM][POLITICIAN_NAMELEN];
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern char lcityname[CITY_NAMELEN];
extern Log gamelog; //The gamelog.
extern MusicClass music;
extern short  exec[EXECNUM];
extern short activesortingchoice[SORTINGCHOICENUM];
extern short attitude[VIEWNUM];
extern short background_liberal_influence[VIEWNUM];
extern short court[COURTNUM];
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short public_interest[VIEWNUM];
extern short senate[SENATENUM];
extern unsigned long attorneyseed[RNG_SIZE];
extern vector<file_and_text_collection> activate_text_file_collection;
extern vector<file_and_text_collection> activities_text_file_collection;
extern vector<file_and_text_collection> baseactions_text_file_collection;
extern vector<file_and_text_collection> chase_text_file_collection;
extern vector<file_and_text_collection> common_text_file_collection;
extern vector<file_and_text_collection> creature_text_file_collection;
extern vector<file_and_text_collection> creaturetypes_text_file_collection;
extern vector<file_and_text_collection> date_text_file_collection;
extern vector<file_and_text_collection> endgame_text_file_collection;
extern vector<file_and_text_collection> externally_stored_data_text_file_collection;
extern vector<file_and_text_collection> fighty_text_file_collection;
extern vector<file_and_text_collection> get_names_text_file_collection;
extern vector<file_and_text_collection> globals_text_file_collection;
extern vector<file_and_text_collection> interrogate_text_file_collection;
extern vector<file_and_text_collection> justice_text_file_collection;
extern vector<file_and_text_collection> liberl_agenda_text_file_collection;
extern vector<file_and_text_collection> locations_text_file_collection;
extern vector<file_and_text_collection> locationspool_text_file_collection;
extern vector<file_and_text_collection> majorevent_text_file_collection;
extern vector<file_and_text_collection> map_specials_text_file_collection;
extern vector<file_and_text_collection> misc_activities_text_file_collection;
extern vector<file_and_text_collection> misc_text_file_collection;
extern vector<file_and_text_collection> names_text_file_collection;
extern vector<file_and_text_collection> newgame_file_collection;
extern vector<file_and_text_collection> politics_text_file_collection;
extern vector<file_and_text_collection> reviewmode_text_file_collection;
extern vector<file_and_text_collection> siege_text_file_collection;
extern vector<file_and_text_collection> stealth_text_file_collection;
extern vector<file_and_text_collection> talk_file_collection;
extern vector<file_and_text_collection> title_screen_text_files;
extern vector<pointerAndString> debug_defines;
fullName generate_long_name(char gender = GENDER_NEUTRAL);

void set_title(char *s);
const string defaultMissingForMask = "Default missing for masks!";
const string defaultUnknownForMask = "Default for masks is not a known armor type!";
const string ACTIVATED = " ACTIVATED";
const string debugCode = "debug code ";
const string failedToLoadSitemaps = "Failed to load sitemaps.txt! Reverting to old map mode.";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string CONST_MASKTYPE = "masktype";
const string CONST_DEFAULT = "default";
const string CONST_UNSPECIFIED_ERROR_WITH_CUSTOM_TEXT = "Unspecified error with custom text";
const string CONST_game012 = "We need a slogan!";
const string CONST_DEBUG_DEFINES_TXT = "debug_defines.txt";
const string CONST_FILE_ERROR_INITIATEMOREINCOMPLETETEXT = "File Error: InitiateMoreIncompleteText";
const string CONST_FILE_ERROR_INITIATEINCOMPLETETEXT = "File Error: InitiateIncompleteText";
const string CONST_FILE_ERROR = "File Error: ";
const string CONST_COMMENT_FOUND = "Comment Found";
const string CONST_SITEMAPS_TXT = "sitemaps.txt";
const string CONST_LIBERAL_CRIME_SQUAD = "Liberal Crime Squad ";

#endif	//GAME_CPP
#ifdef	GETNAMES_CPP
// getnames.cpp

#include "../creature/newcreature.h"
#include "../cursesAlternative.h"
#include "../customMaps.h"
extern short lawList[LAWNUM];

const string moderateLC = "moderate";
const string BUGGY_STRING = "Buggy";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string names = "names\\";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string CONST_GETMONTH_TXT = "getMonth.txt";
const string CONST_CITY_NAMES_TXT = "city_names.txt";
const string CONST_getnames043 = "Software Bugs";
const string CONST_BUGGY_SOFTWARE = "Buggy Software";
const string CONST_BUGS = "bugs";
const string CONST_getnames040 = "Elite Liberal";
const string CONST_LIBERAL_GUARDIAN = "Liberal Guardian";
const string CONST_URBAN_COMMANDO = "Urban Commando";
const string CONST_REVOLUTIONARY = "Revolutionary";
const string CONST_SOCIALIST_THREAT = "Socialist Threat";
const string CONST_ACTIVIST = "Activist";
const string CONST_CIVILIAN = "Civilian";
const string CONST_PUNK = "Punk";
const string CONST_SOCIETY_S_DREGS = "Society's Dregs";
const string CONST_DAMN_WORTHLESS = "Damn Worthless";
const string CONST_DARN_WORTHLESS = "[Darn] Worthless";
const string CONST_PEACE_PRIZE_WINNER = "Peace Prize Winner";
const string CONST_PEACEMAKER = "Peacemaker";
const string CONST_GREAT_PERSON = "Great Person";
const string CONST_UPSTANDING_CITIZEN = "Upstanding Citizen";
const string CONST_RESPECTED = "Respected";
const string CONST_HARD_WORKING = "Hard Working";
const string CONST_NON_LIBERAL = "Non-Liberal";
const string CONST_NON_LIBERAL_PUNK = "Non-Liberal Punk";
const string CONST_EVIL_INCARNATE = "Evil Incarnate";
const string CONST_getnames017 = "Arch-Conservative";
const string CONST_INSANE_VIGILANTE = "Insane Vigilante";
const string CONST_HEARTLESS_BASTARD = "Heartless Bastard";
const string CONST_HEARTLESS_JERK = "Heartless [Jerk]";
const string CONST_STUBBORN_AS_HELL = "Stubborn as Hell";
const string CONST_STUBBORN_AS_HECK = "Stubborn as [Heck]";
const string CONST_WRONG_THINKER = "Wrong-Thinker";
const string CONST_MINDLESS_CONSERVATIVE = "Mindless Conservative";
const string CONST_CONSERVATIVE_PUNK = "Conservative Punk";
const string CONST_CONSERVATIVE_DREGS = "Conservative Dregs";
#endif	//GETNAMES_CPP
#ifdef	GLOBALS_CPP
// globals.cpp

#include "creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"

#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../items/armortype.h"
#include "common/interval.h"
// needed for creaturetype
#include "vehicle/vehicletype.h"
#include "vehicle/vehicle.h"
#include "creature/creaturetype.h"
#include "creature/augmenttype.h"
//#include "common/consolesupport.h"
// for end_cleartype_fix()
#include "common/musicClass.h"
#include "common/creaturePool.h"
#include "locations/locationsPool.h"
#include "items/itemPool.h"
#include "items/lootTypePool.h"
void delete_and_clear_sitemaps();
void delete_and_clear_groundloot();
int endwinAlt(void);
void delete_and_clear_vehicle_types();
void delete_and_clear_date_pool();
void delete_and_clear_weapon_type();
#include <common\\consolesupport.h>
#include "items/loottype.h"
#include "log/log.h"
#include "cursesAlternative.h"
#include "common/ledgerEnums.h"
#include "common/ledger.h"
#include "items/money.h"
#include "common/creaturePoolCreature.h"

extern class Ledger ledger;
extern DeprecatedCreature encounter[ENCMAX];
extern Deprecatednewsstoryst *sitestory;
extern Deprecatedsquadst *activesquad;
extern Log gamelog;
extern Log xmllog;
extern short mode;
extern vector<DeprecatedCreature *> pool;
extern vector<Deprecatedsquadst *> squad;
extern vector<LootType *> loottype;
extern vector<VehicleType *> vehicletype;
extern vector<WeaponType *> weapontype;

int driveskill(DeprecatedCreature &cr, Vehicle &v);
int getloottype(const string &idname);
int getweapontype(const string &idname);
int subordinatesleft(const DeprecatedCreature& cr);
Item* getNewLoot(const string& newLootType, int num = 1);
void addCreature(DeprecatedCreature* cr);
void addjuice(DeprecatedCreature &cr, long juice, long cap);
void assemblesquad(Deprecatedsquadst *cursquad);
void consolidateloot(vector<Item *> &loot);
void criminalize(DeprecatedCreature &cr, short crime);
void fullstatus(const int party_status);
void makeloot(DeprecatedCreature &cr);
void printReporterDuringSiege(const string repname, const string name, const int segmentpower);
void removesquadinfo(DeprecatedCreature &cr);
Deprecatednewsstoryst* lastNewsStory();
bool populate_masks_from_xml(vector<ArmorType*>& masks, const string& file, Log& log);


const string hasRecruited = " has recruited a new ";
const string looksForwardToServing = " looks forward serving the Liberal cause!";
const string CONST_game012 = "We need a slogan!";
const string tag_WEAPON_FLAMETHROWER = "WEAPON_FLAMETHROWER";
const string tag_WEAPON_DESERT_EAGLE = "WEAPON_DESERT_EAGLE";
const string CONST_X_DEFENSE = " Defense";
const string CONST_THE_INTERVIEW_IS_WIDE_RANGING_COVERING_A_VARIETY_OF_TOPICS = "The interview is wide-ranging, covering a variety of topics.";
const string CONST_DECIDES_TO_GIVE_AN_INTERVIEW = " decides to give an interview.";
const string CONST_AUGMENTATIONS_XML = "augmentations.xml";
const string CONST_CREATURES_XML = "creatures.xml";
const string CONST_LOOT_XML = "loot.xml";
const string CONST_MASKS_XML = "masks.xml";
const string CONST_ARMORS_XML = "armors.xml";
const string CONST_WEAPONS_XML = "weapons.xml";
const string CONST_CLIPS_XML = "clips.xml";
const string CONST_VEHICLES_XML = "vehicles.xml";
const string CONST_XMLLOG = "xmllog";
const string CONST_DEFAULT_SLOGANS_TXT = "default_slogans.txt";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

#endif	//GLOBALS_CPP
#ifdef	HAULKIDNAP_CPP
// haulkidnap.cpp

const string CONST_IS_THE_ONLY_VIABLE_TARGET = " Is The Only Viable Target";
const string CONST_STILL_KIDNAP_Y_N = "Still Kidnap? [Y/N]";
const string CONST_HAULS = " hauls ";
const string CONST_IS_LEFT_TO_BE_CAPTURED = " is left to be captured.";
const string CONST_NOBODY_CAN_CARRY_MARTYR = "Nobody can carry Martyr ";
const string CONST_CAN_NO_LONGER_HANDLE = " can no longer handle ";
const string CONST_X_SOME_WHITESPACE = "                                  ";
const string CONST_THE_HOSTAGE_SHOUTS_FOR_HELP = "The hostage shouts for help!      ";
const string CONST_RELEASE_THEIR_HOSTAGE = "release their hostage.";
const string CONST_NO_HOSTAGES_ARE_BEING_HELD = "No hostages are being held.       ";
const string CONST_X_MUCH_WHITESPACE = "                                                     ";
const string CONST_ALL_OF_THE_TARGETS_ARE_TOO_DANGEROUS = "All of the targets are too dangerous.                ";
const string CONST_KIDNAP_WHOM = "Kidnap whom?";
const string CONST_DO_THE_JOB = "do the job.";
const string CONST_NO_ONE_CAN_DO_THE_JOB = "No one can do the job.            ";
const string CONST_X_IS_CAPTURED = " is captured.";
const string CONST_X_IS_RECAPTURED = " is recaptured.";
const string CONST_A_HOSTAGE_ESCAPES = "A hostage escapes!";
const string CONST_IS_CAPTURED = " is captured";
const string CONST_IS_RECAPTURED = " is recaptured";
const string CONST_AND_A_HOSTAGE_IS_FREED = " and a hostage is freed";
const string CONST_AND_SAYS = "and says, ";
const string CONST_X_THE_ = " the ";
const string CONST_SHOWS = " shows ";
const string CONST_WRITHES_AWAY = " writhes away!";
const string CONST_BUT = "but ";
const string CONST_GRABS_AT = " grabs at ";
const string CONST_IS_STRUGGLING_AND_SCREAMING = " is struggling and screaming!";
const string CONST_haulkidnap005 = "!";
const string CONST_SNATCHES = " snatches ";
const string CONST_PLEASE_BE_COOL = "\"[Please], be cool.\"";
const string CONST_BITCH_BE_COOL = "\"Bitch, be cool.\"";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../sitemode/advance.h"
// for creatureadvance
#include "../sitemode/stealth.h"
#include "../sitemode/sitedisplay.h"
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
// for printparty
//// #include "../common/commonactions.h"
void criminalizeparty(short crime);
//// #include "../common/commonactionsCreature.h"
void removesquadinfo(DeprecatedCreature &cr);
/* roll on the kidnap attempt and show the results */
#include "set_color_support.h"
#include "cursesAlternative.h"

void conservatise(const int cr);

void capturecreature(DeprecatedCreature &t);
vector<NameAndAlignment> getEncounterNameAndAlignment();

bool isThereASiteAlarm();
void setSiteAlarmOne();

extern short offended_amradio;
extern short offended_cablenews;
extern int sitecrime;
extern short party_status;

extern short sitealarmtimer;
extern Deprecatedsquadst *activesquad;
extern DeprecatedCreature encounter[ENCMAX];
extern short lawList[LAWNUM];

extern short mode;
extern Log gamelog;

void enemyattack();
void delenc(const short e, const char loot);
void makeloot(DeprecatedCreature &cr);
#endif	//HAULKIDNAP_CPP
#ifdef HELP_CPP

const string liberalHelpOn = "Liberal help on:";
const string pressAnyKeyToReturn = "   Press any key - Return to previous screen";
#endif //HELP_CPP
#ifdef	HIGHSCORE_CPP
// highscore.cpp

#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../title/titlescreen.h"
#include "../common/getnames.h"
// for getmonth
#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include "../common/musicClass.h"

extern class Ledger ledger;
extern int month;
extern int stat_burns;
extern int stat_buys;
extern int stat_dead;
extern int stat_kidnappings;
extern int stat_kills;
extern int stat_recruits;
extern int ustat_burns;
extern int ustat_buys;
extern int ustat_dead;
extern int ustat_funds;
extern int ustat_kidnappings;
extern int ustat_kills;
extern int ustat_recruits;
extern int ustat_spent;
extern int year;
extern int yourscore;
extern MusicClass music;
extern string slogan_str;


MusicModes getEndingMusic(EndTypes e);
string getEndingString(EndTypes e);
struct  saveLoadChunk {
	void * Buffer;
	size_t      ElementSize;
	size_t      ElementCount;
	saveLoadChunk(void * _Buffer, int _ElementSize, int _ElementCount) :Buffer(_Buffer), ElementSize(_ElementSize), ElementCount(_ElementCount) {}
};

struct highscorest
{
	char valid, endtype, slogan[SLOGAN_LEN];
	int month, year, stat_recruits, stat_kidnappings, stat_dead, stat_kills, stat_funds, stat_spent, stat_buys, stat_burns;
};
highscorest score[SCORENUM];

vector<saveLoadChunk> highScoreSaveLoad = {
	saveLoadChunk(&ustat_recruits, sizeof(int), 1),
	saveLoadChunk(&ustat_dead, sizeof(int), 1),
	saveLoadChunk(&ustat_kills, sizeof(int), 1),
	saveLoadChunk(&ustat_kidnappings, sizeof(int), 1),
	saveLoadChunk(&ustat_funds, sizeof(int), 1),
	saveLoadChunk(&ustat_spent, sizeof(int), 1),
	saveLoadChunk(&ustat_buys, sizeof(int), 1),
	saveLoadChunk(&ustat_burns, sizeof(int), 1),
	saveLoadChunk(score, sizeof(highscorest), SCORENUM)
};
const string univer = "Universal Liberal Statistics:";
const string numRecruit = "Recruits: ";
const string numMartyr = "Martyrs: ";
const string numKills = "Kills: ";
const string numKidnap = "Kidnappings: ";
const string CASH_TAXED = "$ Taxed: ";
const string CASH_SPENT = "$ Spent: ";
const string flagsBought = "Flags Bought: ";
const string flagsBurned = "Flags Burned: ";
const string noValid = "No valid scores, press any button to return.";
const string heLiElite = "The Liberal ELITE";
const string heLiLiber = "The Liberal Crime Squad liberalized the country in ";
const string heLiBrought = "The Liberal Crime Squad was brought to justice in ";
const string heLiBlot = "The Liberal Crime Squad was blotted out in ";
const string heLiMob = "The Liberal Crime Squad was mobbed in ";
const string heLiDownsized = "The Liberal Crime Squad was downsized in ";
const string heLiKIA = "The Liberal Crime Squad was KIA in ";
const string hecoReag = "The country was Reaganified in ";
const string heLiDie = "The Liberal Crime Squad died in prison in ";
const string heLiExec = "The Liberal Crime Squad was executed in ";
const string heLiVaca = "The Liberal Crime Squad was on vacation in ";
const string heLiHide = "The Liberal Crime Squad was in permanent hiding in ";
const string heLiHunted = "The Liberal Crime Squad was hunted down in ";
const string heLiScattered = "The Liberal Crime Squad was scattered in ";
const string heLiOutCrime = "The Liberal Crime Squad was out-Crime Squadded in ";
const string heLiBurned = "The Liberal Crime Squad was burned in ";
const string hecoStalinized = "The country was Stalinized in ";
const string CONST_WB = "wb";
const string CONST_RB = "rb";
const string CONST_SCORE_DAT = "score.dat";
#endif	//HIGHSCORE_CPP
#ifdef	INITFILE_CPP

// initfile.cpp

#include "../common/stringconversion.h"
//for int stringtobool(std::string boolstr);
//#include "../common/consolesupport.h"
// for void begin_cleartype_fix();
#include "../title/titlescreen.h"
extern short interface_pgup;
extern short interface_pgdn;
extern bool fixcleartype;
const string CONST_INIT_TXT = "init.txt";

const string tag_fixcleartype = "fixcleartype";
const string tag_autosave = "autosave";
const string tag_page = "page";
const string tag_brackets = "brackets";
const string tag_azerty = "azerty";
const string tag_pagekeys = "pagekeys";
#endif	//INITFILE_CPP
#ifdef	INTERROGATION_CPP
// interrogation.cpp

const string feels_sick_and = " feels sick to the stomach afterward and ";
const string interrogate = "interrogation\\";
const string QUOTATION_MARK = "\"";
const string CONST_HUGS = "hugs ";
const string CONST_PRESS_ANY_KEY_TO_REFLECT_ON_THIS = "Press any key to reflect on this.";
const string CONST_S_DISAPPEARANCE_HAS_NOT_YET_BEEN_REPORTED = "'s disappearance has not yet been reported.";
const string CONST_WAS_ABLE_TO_CREATE_A_MAP_OF_THE_SITE_WITH_THIS_INFORMATION = " was able to create a map of the site with this information.";
const string CONST_UNFORTUNATELY_NONE_OF_IT_IS_USEFUL_TO_THE_LCS = "Unfortunately, none of it is useful to the LCS.";
const string CONST_REVEALS_DETAILS_ABOUT_THE = " reveals details about the ";
const string CONST_THE_CONVERSION_IS_CONVINCING_ENOUGH_THAT_THE_POLICE_NO_LONGER_CONSIDER_IT_A_KIDNAPPING = "The conversion is convincing enough that the police no longer consider it a kidnapping.";
const string CONST_THE_AUTOMATON_HAS_BEEN_ENLIGHTENED_YOUR_LIBERAL_RANKS_ARE_SWELLING = "The Automaton has been Enlightened!   Your Liberal ranks are swelling!";
const string CONST_GROWS_COLDER = " grows colder.";
const string CONST_S_INTERROGATION = "'s interrogation.";
const string CONST_UNDER = " under ";
const string CONST_IS_DEAD = " is dead";
const string CONST_HAS_COMMITTED_SUICIDE = " has committed suicide.";
const string CONST_HAS_BEEN_TAINTED_WITH_WISDOM = " has been tainted with wisdom!";
const string CONST_interrogation154 = "!";
const string CONST_TURNS_THE_TABLES_ON = " turns the tables on ";
const string CONST_HOLDS_FIRM = " holds firm.";
const string CONST_BEGS_FOR_THE_NIGHTMARE_TO_END = " begs for the nightmare to end.";
const string CONST_CURLS_UP_AND = " curls up and";
const string CONST_TO_STOP_LOOKING_LIKE_HITLER = " to stop looking like Hitler.";
const string CONST_SCREAMS_FOR = " screams for ";
const string CONST_BEGS_HITLER_TO_STAY_AND_KILL = " begs Hitler to stay and kill ";
const string CONST_TALKS_ABOUT_HUGGING = "talks about hugging ";
const string CONST_STAMMERS_AND = " stammers and ";
const string CONST_TAKES_IT_WELL = " takes it well.";
const string CONST_S_WEAKENED_BODY_CRUMBLES_UNDER_THE_BRUTAL_ASSAULT = "'s weakened body crumbles under the brutal assault.";
const string CONST_IS_BADLY_HURT = " is badly hurt.";
const string CONST_SEEMS_TO_BE_GETTING_THE_MESSAGE = " seems to be getting the message.";
const string CONST_A_DETAILED_MAP_HAS_BEEN_CREATED_OF = "A detailed map has been created of ";
const string CONST_BEATS_INFORMATION_OUT_OF_THE_PATHETIC_THING = " beats information out of the pathetic thing.";
const string CONST_WONDERS_ABOUT_DEATH = " wonders about death.";
const string CONST_WONDERS_ABOUT_APPLES = " wonders about apples.";
const string CONST_CRIES_HELPLESSLY = " cries helplessly.";
const string CONST_BARKS_HELPLESSLY = " barks helplessly.";
const string CONST_CURLS_UP_IN_THE_CORNER_AND_DOESN_T_MOVE = " curls up in the corner and doesn't move.";
const string CONST_GOES_LIMP_IN_THE_RESTRAINTS = " goes limp in the restraints.";
const string CONST_MOMMY = "mommy.";
const string CONST_GOD_S_MERCY = "God's mercy.";
const string CONST_JOHN_LENNON_S_MERCY = "John Lennon's mercy.";
const string CONST_SCREAMS_HELPLESSLY_FOR = " screams helplessly for ";
const string CONST_IN_ITS_FACE = "!\" in its face.";
const string EXCLAMATION_POINT_SPACE = "! ";
const string CONST_X_THE_AUTOMATON = " the Automaton";
const string CONST_S_GUARDS_BEAT = "'s guards beat";
const string CONST_BEAT = " beat";
const string CONST_BEATS = " beats";
const string CONST_SCREAMING = "screaming \"";
const string CONST_HAD_A_NEAR_DEATH_EXPERIENCE_AND_MET_JOHN_LENNON = " had a near-death experience and met John Lennon.";
const string CONST_HAD_A_NEAR_DEATH_EXPERIENCE_AND_MET_GOD_IN_HEAVEN = " had a near-death experience and met God in heaven.";
const string CONST_CLUMSILY_RESCUES_IT_FROM_CARDIAC_ARREST_WITH_A_DEFIBRILLATOR = " clumsily rescues it from cardiac arrest with a defibrillator.";
const string CONST_FROM_ANY_HEALTH_DAMAGE = " from any health damage.";
const string CONST_SKILLFULLY_SAVES = " skillfully saves ";
const string CONST_DEFTLY_RESCUES_IT_FROM_CARDIAC_ARREST_WITH_A_DEFIBRILLATOR = " deftly rescues it from cardiac arrest with a defibrillator.";
const string CONST_S_INCOMPETENCE_AT_FIRST_AID = "'s incompetence at first aid.";
const string CONST_DIES_DUE_TO = " dies due to ";
const string CONST_S_WEAKENED_STATE = "'s weakened state.";
const string CONST_IT_IS_A_LETHAL_OVERDOSE_IN = "It is a lethal overdose in ";
const string CONST_PANTS = " pants.";
const string CONST_HAS_A_PANIC_ATTACK_AND_SHITS = " has a panic attack and shits ";
const string CONST_HAS_A_PANIC_ATTACK_AND_MAKES_A_STINKY = " has a panic attack and [makes a stinky].";
const string CONST_FLATLINES = " flatlines.";
const string CONST_USES_A_DEFIBRILLATOR_REPEATEDLY_BUT = " uses a defibrillator repeatedly but ";
const string CONST_FOAMS_AT_THE_MOUTH_AND_ITS_EYES_ROLL_BACK_IN_ITS_SKULL = " foams at the mouth and its eyes roll back in its skull.";
const string CONST_IT_IS_SUBJECTED_TO_DANGEROUS_HALLUCINOGENS = "It is subjected to dangerous hallucinogens.";
const string CONST_CONVERTED_INTO_A_MAKESHIFT_CELL = "converted into a makeshift cell.";
const string CONST_IS_LOCKED_IN_A_BACK_ROOM = " is locked in a back room ";
const string CONST_IN_THE_MIDDLE_OF_A_BACK_ROOM = "in the middle of a back room.";
const string CONST_IS_TIED_HANDS_AND_FEET_TO_A_METAL_CHAIR = " is tied hands and feet to a metal chair";
const string CONST_THE_AUTOMATON = "The Automaton";
const string CONST_DAY = ": Day ";
const string CONST_X_THE_EDUCATION_OF_ = "The Education of ";
const string CONST_IN_COLD_BLOOD = " in cold blood.";
const string CONST_EXECUTE = "execute ";
const string CONST_THERE_IS_NO_ONE_ABLE_TO_GET_UP_THE_NERVE_TO = "There is no one able to get up the nerve to ";
const string CONST_BY = " by ";
const string CONST_EXECUTES = " executes ";
const string CONST_THE_FINAL_EDUCATION_OF = "The Final Education of ";
const string CONST_PRESS_ENTER_TO_CONFIRM_THE_PLAN = "Press Enter to Confirm the Plan";
const string CONST_K_KILL_THE_HOSTAGE = "K - Kill the Hostage";
const string CONST_50 = "($50)";
const string CONST_HALLUCINOGENIC_DRUGS = "Hallucinogenic Drugs    ";
const string CONST_NO = "No ";
const string CONST_E = "E - ";
const string CONST_250 = "($250)";
const string CONST_EXPENSIVE_PROPS = "Expensive Props     ";
const string CONST_D = "D - ";
const string CONST_VIOLENTLY_BEATEN = "Violently Beaten    ";
const string CONST_NOT = "Not ";
const string CONST_C = "C - ";
const string CONST_PHYSICAL_RESTRAINTS = "Physical Restraints   ";
const string CONST_B = "B - ";
const string CONST_ATTEMPT_TO_CONVERT = "Attempt to Convert";
const string CONST_NO_VERBAL_CONTACT = "No Verbal Contact     ";
const string CONST_A = "A - ";
const string CONST_SELECTING_A_LIBERAL_INTERROGATION_PLAN = "Selecting a Liberal Interrogation Plan";
const string CONST_THE_EXECUTION_OF_AN_AUTOMATON = "The Execution of an Automaton         ";
const string CONST_X_MURDER_SPACE = "murder ";
const string CONST_THE_CONSERVATIVE_WOULD_LIKE_TO = "The Conservative would like to ";
const string CONST_THE_CONSERVATIVE_HATES = "The Conservative hates ";
const string CONST_TOWARD = "toward ";
const string CONST_THE_CONSERVATIVE_IS_UNCOOPERATIVE = "The Conservative is uncooperative ";
const string CONST_THE_CONSERVATIVE_LIKES = "The Conservative likes ";
const string CONST_AS_ITS_ONLY_FRIEND = " as its only friend.";
const string CONST_TO = "to ";
const string CONST_THE_CONSERVATIVE_CLINGS_HELPLESSLY = "The Conservative clings helplessly ";
const string CONST_OUTFIT = "Outfit: ";
const string CONST_WISDOM = "Wisdom: ";
const string HEART_COLON = "Heart: ";
const string CONST_PSYCHOLOGY_SKILL = "Psychology Skill: ";
const string CONST_HEALTH = "Health: ";
const string CONST_LEAD_INTERROGATOR = "Lead Interrogator: ";
const string CONST_PRISONER = "Prisoner: ";
const string CONST_interrogation038 = "                                  ";
const string CONST_CLING_TO_SCIENCE_TXT = "cling_to_science.txt";
const string CONST_CLING_TO_BUSINESS_TXT = "cling_to_business.txt";
const string CONST_CLING_TO_SCIENCE_ONE_LINE_TXT = "cling_to_science_one_line.txt";
const string CONST_CLING_TO_BUSINESS_ONE_LINE_TXT = "cling_to_business_one_line.txt";
const string CONST_VANILLA_RECRUIT_TXT = "vanilla_recruit.txt";
const string CONST_DISCUSS_TXT = "discuss.txt";
const string CONST_CLING_TO_RELIGION_ONE_LINE_TXT = "cling_to_religion_one_line.txt";
const string CONST_CLING_TO_RELIGION_TXT = "cling_to_religion.txt";
const string CONST_CLINGING_ONE_LINE_TXT = "clinging_one_line.txt";
const string CONST_CLING_TO_INTERROGATER_TXT = "cling_to_interrogater.txt";
const string CONST_INTERROGATER_SHOWS_COMPASSION_TXT = "interrogater_shows_compassion.txt";
const string CONST_INTERROGATER_SHOWS_COMPASSION_ONE_LINE_TXT = "interrogater_shows_compassion_one_line.txt";
const string CONST_DEVELOPS_HATRED_TXT = "develops_hatred.txt";
const string CONST_DEVELOPS_HATRED_ONE_LINE_TXT = "develops_hatred_one_line.txt";
const string CONST_SMARTER_THAN_YOU_TXT = "smarter_than_you.txt";
const string CONST_SMARTER_THAN_YOU_ONE_LINE_TXT = "smarter_than_you_one_line.txt";
const string CONST_GOOD_TRIP_COMPANION_TXT = "good_trip_companion.txt";
const string CONST_BAD_TRIP_TXT = "bad_trip.txt";
const string CONST_FALL_IN_LOVE_TXT = "fall_in_love.txt";
const string CONST_GOOD_TRIP_TXT = "good_trip.txt";
const string CONST_SELF_WOUNDING_TXT = "self_wounding.txt";
const string CONST_BROODS_OVER_DEATH_TXT = "broods_over_death.txt";
const string CONST_PARTIAL_CONVERSION_TXT = "partial_conversion.txt";
const string CONST_RESIST_DRUGS_TXT = "resist_drugs.txt";
const string CONST_USE_PROPS_TXT = "use_props.txt";
const string CONST_PRAYS_ON_DRUGS_TXT = "prays_on_drugs.txt";
const string CONST_PRAYS_TXT = "prays.txt";
const string CONST_WORDS_TO_SCREAM_TXT = "words_to_scream.txt";
const string CONST_WORDS_MEANING_SCREAMING_TXT = "words_meaning_screaming.txt";
const string CONST_BEAT_WITH_PROPS_TXT = "beat_with_props.txt";
const string CONST_SCREAMING_TXT = "screaming.txt";
const string CONST_LOW_HEART_TORTURE_PROPS_TXT = "low_heart_torture_props.txt";
const string CONST_FEELS_SICK_TXT = "feels_sick.txt";
const string CONST_EXECUTION_TXT = "execution.txt";

const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

#include "../creature/creature.h"
#include "../locations/locationsEnums.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../log/log.h"
#include "../common/commondisplayCreature.h"
// for void printhealthstat(Creature &,int,int,char);
#include "../common/getnames.h"
// for std::string getview(short ,bool );
#include "../common/commonactionsCreature.h"
// for  void sleeperize_prompt(Creature &,Creature &,int);
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../common/creaturePoolCreature.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"

extern Log gamelog;
// Interrogation always enlightens
extern bool AUTOENLIGHTEN;
extern MusicClass music;
extern int stat_recruits;
extern int stat_kills;
extern class Ledger ledger;
extern short lawList[LAWNUM];

vector<string> execution;
vector<string> feels_sick;
vector<string> low_heart_torture_props;
vector<string> screaming;
vector<string> beat_with_props;
vector<string> words_meaning_screaming;
vector<string> words_to_scream;
vector<string> prays;
vector<string> prays_on_drugs;
vector<string> use_props;
vector<string> resist_drugs;
vector<string> partial_conversion;
vector<string> broods_over_death;
vector<string> self_wounding;
vector<string> good_trip;
vector<vector<string> > fall_in_love;
vector<vector<string> > bad_trip;
vector<vector<string> > good_trip_companion;
vector<string> smarter_than_you_one_line;
vector<vector<string> > smarter_than_you;
vector<string> develops_hatred_one_line;
vector<vector<string> > develops_hatred;
vector<string> interrogater_shows_compassion_one_line;
vector<vector<string> > interrogater_shows_compassion;
vector<vector<string> > cling_to_interrogater;
vector<string> clinging_one_line;
vector<vector<string> > cling_to_religion;
vector<string> cling_to_religion_one_line;
vector<vector<string> > discuss;
vector<string> vanilla_recruit;
vector<vector<string> > cling_to_business;
vector<vector<string> > cling_to_science;
vector<string> cling_to_business_one_line;
vector<string> cling_to_science_one_line;
const int DOUBLE_LINE = 2;
vector<file_and_text_collection> interrogate_text_file_collection = {
	/*InterrogationST.cpp*/
	customText(&execution, interrogate + CONST_EXECUTION_TXT),
	customText(&feels_sick, interrogate + CONST_FEELS_SICK_TXT),
	customText(&low_heart_torture_props, interrogate + CONST_LOW_HEART_TORTURE_PROPS_TXT),
	customText(&screaming, interrogate + CONST_SCREAMING_TXT),
	customText(&beat_with_props, interrogate + CONST_BEAT_WITH_PROPS_TXT),
	customText(&words_meaning_screaming, interrogate + CONST_WORDS_MEANING_SCREAMING_TXT),
	customText(&words_to_scream, interrogate + CONST_WORDS_TO_SCREAM_TXT),
	customText(&prays, interrogate + CONST_PRAYS_TXT),
	customText(&prays_on_drugs, interrogate + CONST_PRAYS_ON_DRUGS_TXT),
	customText(&use_props, interrogate + CONST_USE_PROPS_TXT),
	customText(&resist_drugs, interrogate + CONST_RESIST_DRUGS_TXT),
	customText(&partial_conversion, interrogate + CONST_PARTIAL_CONVERSION_TXT),
	customText(&broods_over_death, interrogate + CONST_BROODS_OVER_DEATH_TXT),
	customText(&self_wounding, interrogate + CONST_SELF_WOUNDING_TXT),
	customText(&good_trip, interrogate + CONST_GOOD_TRIP_TXT),
	customText(&fall_in_love, interrogate + CONST_FALL_IN_LOVE_TXT, DOUBLE_LINE),
	customText(&bad_trip, interrogate + CONST_BAD_TRIP_TXT, DOUBLE_LINE),
	customText(&good_trip_companion, interrogate + CONST_GOOD_TRIP_COMPANION_TXT, DOUBLE_LINE),
	customText(&smarter_than_you_one_line, interrogate + CONST_SMARTER_THAN_YOU_ONE_LINE_TXT),
	customText(&smarter_than_you, interrogate + CONST_SMARTER_THAN_YOU_TXT, DOUBLE_LINE),
	customText(&develops_hatred_one_line, interrogate + CONST_DEVELOPS_HATRED_ONE_LINE_TXT),
	customText(&develops_hatred, interrogate + CONST_DEVELOPS_HATRED_TXT, DOUBLE_LINE),
	customText(&interrogater_shows_compassion_one_line, interrogate + CONST_INTERROGATER_SHOWS_COMPASSION_ONE_LINE_TXT),
	customText(&interrogater_shows_compassion, interrogate + CONST_INTERROGATER_SHOWS_COMPASSION_TXT, DOUBLE_LINE),
	customText(&cling_to_interrogater, interrogate + CONST_CLING_TO_INTERROGATER_TXT, DOUBLE_LINE),
	customText(&clinging_one_line, interrogate + CONST_CLINGING_ONE_LINE_TXT),
	customText(&cling_to_religion, interrogate + CONST_CLING_TO_RELIGION_TXT, DOUBLE_LINE),
	customText(&cling_to_religion_one_line, interrogate + CONST_CLING_TO_RELIGION_ONE_LINE_TXT),
	customText(&discuss, interrogate + CONST_DISCUSS_TXT, DOUBLE_LINE),
	customText(&vanilla_recruit, interrogate + CONST_VANILLA_RECRUIT_TXT),
	customText(&cling_to_business_one_line, interrogate + CONST_CLING_TO_BUSINESS_ONE_LINE_TXT),
	customText(&cling_to_science_one_line, interrogate + CONST_CLING_TO_SCIENCE_ONE_LINE_TXT),
	customText(&cling_to_business, interrogate + CONST_CLING_TO_BUSINESS_TXT, DOUBLE_LINE),
	customText(&cling_to_science, interrogate + CONST_CLING_TO_SCIENCE_TXT, DOUBLE_LINE),
};

enum InterrogationTechnqiues
{
	TECHNIQUE_TALK,
	TECHNIQUE_RESTRAIN,
	TECHNIQUE_BEAT,
	TECHNIQUE_PROPS,
	TECHNIQUE_DRUGS,
	TECHNIQUE_KILL
};
string getDespairString(const bool drugs, const bool restrain, const bool religion);
string victimPrays(const bool onDrugs);
string getFallsInLove(const string name, const bool restrain);
string getBadTrip(const string name, const bool restrain, const bool rapport);
string outPsychologyCaptor(const string name);
string triedConvertingTheAbused(const string name);
string feelsBadForAbused(const string name);
string stockholmSyndrome(const string name);
string failToBreakReligion(const string a, const string cr);
string failedToBreakBusiness(const string a, const string cr);
string failedToBreakScience(const string a, const string cr);
#endif	//INTERROGATION_CPP
#ifdef	ITEM_CPP
// item.cpp
const string CONST_X_LETTER_A = "a";
const string CONST_AN = "an";
const string CONST_NUMBER = "number";
const string CONST_ITEMTYPEID = "itemtypeid";
const string CONST_ITEMTYPENAME = "itemtypename";

#endif	//ITEM_CPP
#ifdef	ITEMTYPE_CPP
// itemtype.cpp


#include "../items/itemtype.h"
extern int year;
const string CONST_UNKNOWN_ELEMENT_FOR_ITEM_TYPE_IDNAME = "Unknown element for item type << idname_ << ";
const string CONST_LACKS_IDNAME = "LACKS IDNAME ";
const string CONST_UNDEFINED = "UNDEFINED";

const string tag_fencevalue = "fencevalue";
const string tag_name_future = "name_future";
const string tag_name = "name";
const string tag_idname = "idname";
const string tag_id = "id";
#endif	//ITEMTYPE_CPP
#ifdef	JUSTICE_CPP
// justice.cpp

const string counts_of = " counts of ";
const string execution_in_three_months = "The execution is scheduled to occur three months from now.";
const string justice = "justice\\";
const string CONST_HIRING_AN_UNDOCUMENTED_WORKER = "hiring an undocumented worker";
const string CONST_X_HIRING_UNDOCUMENTED_WORKERS = "hiring undocumented workers";
const string CONST_MONTHS = " months.";
const string CONST_IS_DUE_TO_BE_EXECUTED_IN = " is due to be executed in ";
const string CONST_IS_DUE_TO_BE_RELEASED_NEXT_MONTH = " is due to be released next month.";
const string CONST_IS_DUE_TO_BE_EXECUTED_NEXT_MONTH = " is due to be executed next month.";
const string CONST_NO_DOUBT_THERE_ARE_SOME_MENTAL_SCARS_BUT_THE_LIBERAL_IS_BACK = "No doubt there are some mental scars, but the Liberal is back.";
const string CONST_HAS_BEEN_RELEASED_FROM_PRISON = " has been released from prison.";
const string CONST_IF_YOU_CAN_T_PROTECT_YOUR_OWN_PEOPLE_WHO_CAN_YOU_PROTECT = "If you can't protect your own people, who can you protect?";
const string CONST_HAS_FAILED_THE_LIBERAL_CRIME_SQUAD = " has failed the Liberal Crime Squad.";
const string CONST_X_BY_SPACE = "by ";
const string CONST_TODAY_THE_CONSERVATIVE_MACHINE_EXECUTED = "Today, the Conservative Machine executed ";
const string CONST_FOR_SHAME = "FOR SHAME:";
const string CONST_DUE_TO_THE_ABOLITION_OF_THE_DEATH_PENALTY = "due to the abolition of the death penalty.";
const string CONST_S_DEATH_SENTENCE_HAS_BEEN_COMMUTED_TO_LIFE = "'s death sentence has been commuted to life, ";
const string CONST_SEEMS_TO_BE_MOSTLY_FINE_THOUGH = " seems to be mostly fine, though.";
const string CONST_IS_KINDA_LOSING_IT_IN_HERE_JUICE_THAT_IS = " is kinda losing it in here. Juice, that is.";
const string CONST_HAS_BECOME_A_MORE_HARDENED_JUICIER_CRIMINAL = " has become a more hardened, Juicier criminal.";
const string CONST_THE_LCS_WILL_RISE_AGAIN_MULTIPLE_LCS_MEMBERS_ESCAPE = "The LCS will rise again! Multiple LCS members escape!";
const string CONST_ANOTHER_IMPRISONED_LCS_MEMBER_ALSO_GETS_OUT = "Another imprisoned LCS member also gets out!";
const string CONST_ESCAPED_FROM_PRISON = " escaped from prison!";
const string CONST_INTENTIONALLY_ODS_ON_SMUGGLED_DRUGS_THEN_BREAKS_OUT_OF_THE_MEDICAL_WARD = " intentionally ODs on smuggled drugs, then breaks out of the medical ward!";
const string CONST_JIMMIES_THE_CELL_DOOR_AND_CUTS_THE_OUTER_FENCE_IN_THE_DEAD_OF_NIGHT = " jimmies the cell door and cuts the outer fence in the dead of night!";
const string CONST_PUTS_ON_SMUGGLED_STREET_CLOTHES_AND_CALMLY_WALKS_OUT_OF_PRISON = " puts on smuggled street clothes and calmly walks out of prison.";
const string CONST_CODES_A_VIRUS_ON_A_SMUGGLED_PHONE_THAT_OPENS_ALL_THE_PRISON_DOORS = " codes a virus on a smuggled phone that opens all the prison doors!";
const string CONST_LEADS_A_RIOT_WITH_DOZENS_OF_PRISONERS_CHANTING_THE_LCS_SLOGAN = " leads a riot with dozens of prisoners chanting the LCS slogan!";
const string CONST_MANAGED_TO_AVOID_LASTING_INJURY = " managed to avoid lasting injury.";
const string CONST_IS_FOUND_DEAD = " is found dead.";
const string CONST_IS_BADLY_HURT_IN_THE_PROCESS = " is badly hurt in the process.";
const string CONST_CONSUMES_DRUGS_THAT_SIMULATE_DEATH_AND_IS_THROWN_OUT_WITH_THE_TRASH = " consumes drugs that simulate death, and is thrown out with the trash!";
const string CONST_PICKS_THE_LOCK_ON_THEIR_LEG_CHAINS_AND_THEN_SNEAKS_AWAY = " picks the lock on their leg chains and then sneaks away!";
const string CONST_WEARS_AN_ELECTRICIAN_S_OUTFIT_AND_RIDES_AWAY_WITH_SOME_CONTRACTORS = " wears an electrician's outfit and rides away with some contractors.";
const string CONST_LEADS_THE_OPPRESSED_PRISONERS_AND_OVERWHELMS_THE_PRISON_GUARDS = " leads the oppressed prisoners and overwhelms the prison guards!";
const string CONST_X_REMAINS_STRONG = " remains strong.";
const string CONST_ABANDONS_THE_LIBERAL_CRIME_SQUAD = " abandons the Liberal Crime Squad!";
const string CONST_ONLY_STAYS_LOYAL_TO_THE_LCS_FOR = " only stays loyal to the LCS for ";
const string CONST_SILENTLY_GROWS_WISER = " silently grows Wiser...";
const string CONST_FEELS_BAD_ABOUT_LCS_ACTIONS_AND_LOSES_JUICE = " feels bad about LCS actions, and loses juice!";
const string CONST_THE_COURT_ACCEPTS_THE_PLEA = "The court accepts the plea.";
const string CONST_NOLO = "nolo";
const string CONST_LESS_A_MONTH_FOR_TIME_ALREADY_SERVED = ", less a month for time already served.";
const string CONST_WILL_BE_RETURNED_TO_PRISON_TO_RESUME_AN_EARLIER_SENTENCE = " will be returned to prison to resume an earlier sentence";
const string CONST_IS_FREE = " is free!";
const string CONST_NOT_GUILTY = "NOT GUILTY!";
const string CONST_THE_PROSECUTION_DECLINES_TO_RE_TRY_THE_CASE = "The prosecution declines to re-try the case.";
const string CONST_THE_CASE_WILL_BE_RE_TRIED_NEXT_MONTH = "The case will be re-tried next month.";
const string CONST_BUT_THEY_CAN_T_REACH_A_VERDICT = "But they can't reach a verdict!";
const string CONST_THE_JURY_HAS_RETURNED_FROM_DELIBERATIONS = "The jury has returned from deliberations.";
const string CONST_THE_JURY_LEAVES_TO_CONSIDER_THE_CASE = "The jury leaves to consider the case.";
const string CONST_TO_ACQUIT = " to acquit)";
const string CONST_NEED = ", need ";
const string CONST_X_SPACE_PARENTHESIS = " (";
const string CONST_HAD_THE_JURY_JUDGE_AND_PROSECUTION_CRYING_FOR_FREEDOM = " had the jury, judge, and prosecution crying for freedom.";
const string CONST_MADE_A_VERY_POWERFUL_CASE = " made a very powerful case.";
const string CONST_WORKED_THE_JURY_VERY_WELL = " worked the jury very well.";
const string CONST_S_ARGUMENTS_WERE_PRETTY_GOOD = "'s arguments were pretty good.";
const string CONST_DID_ALL_RIGHT_BUT_MADE_SOME_MISTAKES = " did all right, but made some mistakes.";
const string CONST_S_CASE_REALLY_SUCKED = "'s case really sucked.";
const string CONST_MAKES_ONE_HORRIBLE_MISTAKE_AFTER_ANOTHER = " makes one horrible mistake after another.";
const string CONST_CONDUCTS_AN_INCREDIBLE_DEFENSE = " conducts an incredible defense.";
const string CONST_AND_SHOUT_NOT_GUILTY_BEFORE_DELIBERATIONS_EVEN_BEGAN = "and shout \"NOT GUILTY!\" before deliberations even began.";
const string CONST_S_ARGUMENTS_MADE_SEVERAL_OF_THE_JURORS_STAND_UP = "'s arguments made several of the jurors stand up ";
const string CONST_THE_DEFENSE_IS_EXTREMELY_COMPELLING = "The defense is extremely compelling.";
const string CONST_THE_DEFENSE_MAKES_THE_PROSECUTION_LOOK_LIKE_AMATEURS = "The defense makes the prosecution look like amateurs.";
const string CONST_THE_DEFENSE_WAS_REALLY_SLICK = "The defense was really slick.";
const string CONST_DEFENSE_ARGUMENTS_WERE_PRETTY_GOOD = "Defense arguments were pretty good.";
const string CONST_THE_DEFENSE_WAS_LACKLUSTER = "The defense was lackluster.";
const string CONST_THE_DEFENSE_IS_TOTALLY_LAME = "The defense is totally lame.";
const string CONST_THE_DEFENSE_ATTORNEY_ACCIDENTALLY_SAID_MY_CLIENT_IS_GUILTY_DURING_CLOSING = "The defense attorney accidentally said \"My client is GUILTY!\" during closing.";
const string CONST_THE_DEFENSE_ATTORNEY_RARELY_SHOWED_UP = "The defense attorney rarely showed up.";
const string CONST_TO_CONVICT = " to convict)";
const string CONST_X_TO_PLUS = " to +";
const string PARENTHESIS_PLUS = " (+";
const string CONST_THE_PROSECUTION_IS_INCREDIBLY_STRONG = "The prosecution is incredibly strong.";
const string CONST_THE_PROSECUTION_MAKES_AN_AIRTIGHT_CASE = "The prosecution makes an airtight case.";
const string CONST_THE_PROSECUTION_S_CASE_IS_SOLID = "The prosecution's case is solid.";
const string CONST_THE_PROSECUTION_GIVES_A_STANDARD_PRESENTATION = "The prosecution gives a standard presentation.";
const string CONST_THE_PROSECUTION_S_PRESENTATION_IS_TERRIBLE = "The prosecution's presentation is terrible.";
const string CONST_THE_JURY_IS_A_BIT_CONSERVATIVE = "The jury is a bit Conservative.";
const string CONST_THE_JURY_IS_QUITE_MODERATE = "The jury is quite moderate.";
const string CONST_THE_JURY_IS_FAIRLY_LIBERAL = "The jury is fairly Liberal.";
const string CONST_S_BEST_FRIEND_FROM_CHILDHOOD_IS_A_JUROR = "'s best friend from childhood is a juror.";
const string CONST_S_CONSERVATIVE_ARCH_NEMESIS_WILL_REPRESENT_THE_PROSECUTION = "'s CONSERVATIVE ARCH-NEMESIS will represent the prosecution!!!";
const string CONST_S_FAVOR = "'s favor!";
const string CONST_ENSURES_THE_JURY_IS_STACKED_IN = " ensures the jury is stacked in ";
const string CONST_THE_TRIAL_PROCEEDS_JURY_SELECTION_IS_FIRST = "The trial proceeds.  Jury selection is first.";
const string CONST_IS_STANDING_TRIAL = " is standing trial.";
const string CONST_INTELLIGENCE = "Intelligence: ";
const string CONST_X_LAW_COLON = "Law: ";
const string CONST_CHARISMA = "Charisma: ";
const string CONST_X_PERSUASION_COLON = "Persuasion: ";
const string HEART_COLON = "Heart: ";
const string CONST_S_OFFER_TO_ASSIST_PRO_BONO = "'s offer to assist pro bono.";
const string CONST_E_ACCEPT_SLEEPER = "E - Accept sleeper ";
const string CONST_D_PAY_5000_TO_HIRE_ACE_LIBERAL_ATTORNEY = "D - Pay $5000 to hire ace Liberal attorney ";
const string CONST_C_PLEAD_GUILTY = "C - Plead guilty.";
const string CONST_B_DEFEND_SELF = "B - Defend self!";
const string CONST_A_USE_A_COURT_APPOINTED_ATTORNEY = "A - Use a court-appointed attorney.";
const string CONST_HOW_WILL_YOU_CONDUCT_THE_DEFENSE = "How will you conduct the defense?";
const string CONST_A_FORMER_LCS_MEMBER_WILL_TESTIFY_AGAINST = "A former LCS member will testify against ";
const string CONST_FORMER_LCS_MEMBERS_WILL_TESTIFY_AGAINST = " former LCS members will testify against ";
const string CONST_X_LOITERING = "loitering";
const string CONST_INDECENT_EXPOSURE = "indecent exposure";
const string CONST_X_DISTURBING_THE_PEACE = "disturbing the peace";
const string CONST_X_RESISTING_ARREST = "resisting arrest";
const string CONST_X_VANDALISM = "vandalism";
const string CONST_X_BREAKING_AND_ENTERING = "breaking and entering";
const string CONST_X_UNLAWFUL_BURIAL = "unlawful burial";
const string CONST_UNLAWFUL_ACCESS_OF_AN_INFORMATION_SYSTEM = "unlawful access of an information system";
const string CONST_INTERFERENCE_WITH_INTERSTATE_COMMERCE = "interference with interstate commerce";
const string CONST_POSSESSION_OF_AN_ILLEGAL_WEAPON = "possession of an illegal weapon";
const string CONST_FIRING_AN_ILLEGAL_WEAPON = "firing an illegal weapon";
const string CONST_HIRING_AN_ILLEGAL_ALIEN = "hiring an illegal alien";
const string CONST_X_HIRING_ILLEGAL_ALIENS = "hiring illegal aliens";
const string CONST_X_PROSTITUTION = "prostitution";
const string CONST_PETTY_LARCENY = "petty larceny";
const string CONST_X_CREDIT_CARD_FRAUD_LOWERCASE = "credit card fraud";
const string CONST_X_GRAND_THEFT_AUTO = "grand theft auto";
const string CONST_MISDEMEANOR_ASSAULT = "misdemeanor assault";
const string CONST_FELONY_ASSAULT = "felony assault";
const string CONST_X_EXTORTION = "extortion";
const string CONST_X_RACKETEERING = "racketeering";
const string CONST_X_JURY_TAMPERING = "jury tampering";
const string CONST_AIDING_A_PRISON_ESCAPE = "aiding a prison escape";
const string CONST_X_ESCAPING_PRISON = "escaping prison";
const string CONST_X_DRUG_DEALING = "drug dealing";
const string CONST_SEDITION = "sedition";
const string CONST_X_FLAG_BURNING_LOWERCASE = "flag burning";
const string CONST_FELONY_FLAG_BURNING = "felony flag burning";
const string CONST_X_FLAG_MURDER = "Flag Murder";
const string CONST_X_ARSON = "arson";
const string CONST_X_BANK_ROBBERY = "bank robbery";
const string CONST_X_KIDNAPPING = "kidnapping";
const string CONST_X_MURDER = "murder";
const string CONST_X_TERRORISM = "terrorism";
const string CONST_X_TREASON = "treason";
const string CONST_IS_CHARGED_WITH = ", is charged with ";
const string CONST_THE_DEFENDANT = "The defendant, ";
const string CONST_THE_JUDGE_READS_THE_CHARGES = "The judge reads the charges:";
const string CONST_READS_THE_CHARGES_TRYING_TO_HIDE_A_SMILE = " reads the charges, trying to hide a smile:";
const string CONST_TO_BE_SERVED_CONSECUTIVELY = "to be served consecutively";
const string CONST_TO_BE_SERVED_CONCURRENTLY = "to be served concurrently";
const string CONST_X_COMMA = ",";
const string CONST_IN_PRISON = " in prison";
const string CONST_LETTER_S = "s";
const string CONST_MONTH = " month";
const string CONST_YEARS_IN_PRISON = " years in prison";
const string CONST_LIFE_IN_PRISON = "life in prison";
const string CONST_HAVE_A_NICE_DAY = "Have a nice day, ";
const string CONST_CONSECUTIVE_LIFE_TERMS_IN_PRISON = " consecutive life terms in prison";
const string CONST_YOU_ARE_SENTENCED_TO = ", you are sentenced to ";
const string CONST_CONSIDER_THIS_A_WARNING_YOU_ARE_FREE_TO_GO = ", consider this a warning.  You are free to go.";
const string CONST_YOU_WILL_BE_RETURNED_TO_PRISON_TO_RESUME_IT = "You will be returned to prison to resume it";
const string CONST_THE_COURT_SEES_NO_NEED_TO_ADD_TO_YOUR_EXISTING_SENTENCE = ", the court sees no need to add to your existing sentence.";
const string CONST_YOU_ARE_SENTENCED_TO_DEATH = ", you are sentenced to DEATH!";
const string CONST_YOU_WILL_BE_RETURNED_TO_PRISON_TO_CARRY_OUT_YOUR_DEATH_SENTENCE = ", you will be returned to prison to carry out your death sentence.";
const string CONST_DURING_SENTENCING_THE_JUDGE_GRANTS_SOME_LENIENCY = "During sentencing, the judge grants some leniency.";
const string CONST_GUILTY = "GUILTY!";
const string CONST_GENERAL_EXPERIENCES_TXT = "general_experiences.txt";
const string CONST_BAD_EXPERIENCES_TXT = "bad_experiences.txt";
const string CONST_GOOD_EXPERIENCES_TXT = "good_experiences.txt";
const string CONST_LABOR_CAMP_EXPERIENCES_TXT = "labor_camp_experiences.txt";
const string CONST_REEDUCATION_EXPERIENCES_TXT = "reeducation_experiences.txt";
const string CONST_SUPPOSEDLY_PAINLESS_EXECUTION_METHOD_TXT = "supposedly_painless_execution_method.txt";
const string CONST_STANDARD_EXECUTION_METHODS_TXT = "standard_execution_methods.txt";
const string CONST_CRUEL_AND_UNUSUAL_EXECUTION_METHODS_TXT = "cruel_and_unusual_execution_methods.txt";
const string CONST_CONSERVATIVE_JURY_TXT = "conservative_jury.txt";
const string CONST_LIBERAL_JURY_TXT = "liberal_jury.txt";

const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_ARMOR_WORKCLOTHES = "ARMOR_WORKCLOTHES";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

const string SINGLE_DOT = ".";
const string CONST_X_COMMA_SPACE = ", ";
const string CONST_SPACE_AND_SPACE = " and ";
const string LETTER_S = "s";

#include "../creature/creature.h"
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../log/log.h"
//#include "../common/commonactions.h"
int scare_factor(int lawflag, int crimenumber);
#include "../common/commonactionsCreature.h"
// for  bool iscriminal(Creature &)
#include "../common/translateid.h"
// for  int getarmortype
#include "../politics/politics.h"
//for publicmood
#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include "../common/creaturePoolCreature.h"
vector<string> liberal_jury;
vector<string> conservative_jury;
vector<string> cruel_and_unusual_execution_methods;
vector<string> standard_execution_methods;
vector<string> supposedly_painless_execution_method;
vector<string> reeducation_experiences;
vector<string> labor_camp_experiences;
vector<string> good_experiences;
vector<string> bad_experiences;
vector<string> general_experiences;
#include "../customMaps.h"
vector<file_and_text_collection> justice_text_file_collection = {
	/*justice.cpp*/
	customText(&liberal_jury, justice + CONST_LIBERAL_JURY_TXT),
	customText(&conservative_jury, justice + CONST_CONSERVATIVE_JURY_TXT),
	customText(&cruel_and_unusual_execution_methods, justice + CONST_CRUEL_AND_UNUSUAL_EXECUTION_METHODS_TXT),
	customText(&standard_execution_methods, justice + CONST_STANDARD_EXECUTION_METHODS_TXT),
	customText(&supposedly_painless_execution_method, justice + CONST_SUPPOSEDLY_PAINLESS_EXECUTION_METHOD_TXT),
	customText(&reeducation_experiences, justice + CONST_REEDUCATION_EXPERIENCES_TXT),
	customText(&labor_camp_experiences, justice + CONST_LABOR_CAMP_EXPERIENCES_TXT),
	customText(&good_experiences, justice + CONST_GOOD_EXPERIENCES_TXT),
	customText(&bad_experiences, justice + CONST_BAD_EXPERIENCES_TXT),
	customText(&general_experiences, justice + CONST_GENERAL_EXPERIENCES_TXT),
};
#include "../common/musicClass.h"

extern bool SHOWMECHANICS;
extern MusicClass music;
extern class Ledger ledger;
extern unsigned long attorneyseed[RNG_SIZE];
extern unsigned long seed[RNG_SIZE];
extern Log gamelog;
extern int stat_dead;
extern short lawList[LAWNUM];
extern vector<DeprecatedCreature *> pool;

#include "../common/creaturePool.h"
#include "../locations/locationsPool.h"
//void printSingleCrime(const CreatureJustice g, const Lawflags law_flag, const int typenum, const string crime_string, const bool mention_multiple_counts = false);
map<Lawflags, string> crimeBlockOne = {
	map<Lawflags, string>::value_type(LAWFLAG_TREASON, CONST_X_TREASON),
	map<Lawflags, string>::value_type(LAWFLAG_TERRORISM, CONST_X_TERRORISM),
	map<Lawflags, string>::value_type(LAWFLAG_MURDER, CONST_X_MURDER),
	map<Lawflags, string>::value_type(LAWFLAG_KIDNAPPING, CONST_X_KIDNAPPING),
	map<Lawflags, string>::value_type(LAWFLAG_BANKROBBERY, CONST_X_BANK_ROBBERY),
	map<Lawflags, string>::value_type(LAWFLAG_ARSON, CONST_X_ARSON),
};
map<Lawflags, string> crimeBlockTwo = {
	map<Lawflags, string>::value_type(LAWFLAG_SPEECH, CONST_SEDITION),
	map<Lawflags, string>::value_type(LAWFLAG_BROWNIES, CONST_X_DRUG_DEALING),
	map<Lawflags, string>::value_type(LAWFLAG_ESCAPED, CONST_X_ESCAPING_PRISON),
	map<Lawflags, string>::value_type(LAWFLAG_HELPESCAPE, CONST_AIDING_A_PRISON_ESCAPE),
	map<Lawflags, string>::value_type(LAWFLAG_JURY, CONST_X_JURY_TAMPERING),
	map<Lawflags, string>::value_type(LAWFLAG_RACKETEERING, CONST_X_RACKETEERING),
	map<Lawflags, string>::value_type(LAWFLAG_EXTORTION, CONST_X_EXTORTION),
	map<Lawflags, string>::value_type(LAWFLAG_ARMEDASSAULT, CONST_FELONY_ASSAULT),
	map<Lawflags, string>::value_type(LAWFLAG_ASSAULT, CONST_MISDEMEANOR_ASSAULT),
	map<Lawflags, string>::value_type(LAWFLAG_CARTHEFT, CONST_X_GRAND_THEFT_AUTO),
	map<Lawflags, string>::value_type(LAWFLAG_CCFRAUD, CONST_X_CREDIT_CARD_FRAUD_LOWERCASE),
	map<Lawflags, string>::value_type(LAWFLAG_THEFT, CONST_PETTY_LARCENY),
	map<Lawflags, string>::value_type(LAWFLAG_PROSTITUTION, CONST_X_PROSTITUTION),
};
map<Lawflags, string> crimeBlockThree = {
	map<Lawflags, string>::value_type(LAWFLAG_COMMERCE, CONST_INTERFERENCE_WITH_INTERSTATE_COMMERCE),
	map<Lawflags, string>::value_type(LAWFLAG_INFORMATION, CONST_UNLAWFUL_ACCESS_OF_AN_INFORMATION_SYSTEM),
	map<Lawflags, string>::value_type(LAWFLAG_BURIAL, CONST_X_UNLAWFUL_BURIAL),
	map<Lawflags, string>::value_type(LAWFLAG_BREAKING, CONST_X_BREAKING_AND_ENTERING),
	map<Lawflags, string>::value_type(LAWFLAG_VANDALISM, CONST_X_VANDALISM),
	map<Lawflags, string>::value_type(LAWFLAG_RESIST, CONST_X_RESISTING_ARREST),
	map<Lawflags, string>::value_type(LAWFLAG_DISTURBANCE, CONST_X_DISTURBING_THE_PEACE),
	map<Lawflags, string>::value_type(LAWFLAG_PUBLICNUDITY, CONST_INDECENT_EXPOSURE),
	map<Lawflags, string>::value_type(LAWFLAG_LOITERING, CONST_X_LOITERING),
};
map<Lawflags, bool> crimeMultipleCounts = {
	map<Lawflags, bool>::value_type(LAWFLAG_TREASON,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_TERRORISM,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_MURDER,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_KIDNAPPING,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_BANKROBBERY,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_ARSON,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_SPEECH,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_BROWNIES,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_ESCAPED,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_HELPESCAPE,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_JURY,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_RACKETEERING, false),
	map<Lawflags, bool>::value_type(LAWFLAG_EXTORTION,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_ARMEDASSAULT,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_ASSAULT,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_CARTHEFT,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_CCFRAUD,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_THEFT,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_PROSTITUTION,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_COMMERCE,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_INFORMATION,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_BURIAL,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_BREAKING,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_VANDALISM,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_RESIST, false),
	map<Lawflags, bool>::value_type(LAWFLAG_DISTURBANCE,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_PUBLICNUDITY,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_LOITERING, false),
};
enum LegalDefense {
	UNDECIDED = -1,
	COURT_ATTORNEY = 0,
	SELF_REPRESENT = 1,
	PLEAD_GUILTY = 2,
	ACE_ATTORNEY = 3,
	SLEEPER_ATTORNEY = 4
};

#endif	//JUSTICE_CPP
#ifdef	LCSIO_CPP
// lcsio.cpp

#include <tinydir.h>
extern char homedir[MAX_PATH_SIZE];
extern char artdir[MAX_PATH_SIZE];
const string NEWSPIC_CPC = "newspic.cpc";
const string CONST_DAT = ".dat";
const string CONST_lcsio013 = ".";
const string CONST_LCS = ".lcs/";
const string CONST_lcsio011 = "/";
const string DOT_SLASH = "./";
const string CONST_HOME = "HOME";
const string CONST_X_PARENT_ART_FOLDER = "../art/";
const string CONST_X_ART_FOLDER = "./art/";
const string CONST_USR_GAMES_LCS_ART = "/usr/games/lcs/art/";
const string CONST_USR_GAMES_SHARE_LCS_ART = "/usr/games/share/lcs/art/";
const string CONST_USR_SHARE_LCS_ART = "/usr/share/lcs/art/";
const string CONST_USR_LOCAL_SHARE_LCS_ART = "/usr/local/share/lcs/art/";
const string CONST_LCS_ART = "/lcs/art/";
const string CONST_SCORE = "score";

#endif	//LCSIO_CPP
#ifdef	LCSMONTHLY_CPP
// lcsmonthly.cpp

#include "../creature/newcreature.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../items/itemPool.h"
#include "../items/lootTypePool.h"
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
// for addpage and delimiter
//#include "../common/equipment.h"
void consolidateloot(vector<Item *> &loot);
//#include "../common/translateid.h"
int getloottype(const string &idname);
void removeItemFromSquad(const int loottypeindex);
#include "../common/commonactions.h"
// for void change_public_opinion(int,int,char =1,char=100);
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"
map<short, string> expenseTypes;
map<short, string> incomeTypes;
void constructLootIndices(vector<bool> &havetype, vector<int> &loottypeindex, const vector<string> dox);

extern CCSexposure ccsexposure;
extern char disbanding;
extern class Ledger ledger;
extern Log gamelog;
extern MusicClass music;
extern short lawList[LAWNUM];
extern short offended_amradio;
extern short offended_cablenews;
extern short offended_cia;
extern short offended_corps;
extern short offended_firemen;

const string THIS_IS_BOUND_TO_RILE_UP_CORPS = "This is bound to get the Corporations a little riled up.";
const string major_news_take_it_up = "The major networks and publications take it up and run it for weeks.";

const string CONST_PROMISING_SOMEONE_COMPANY_PROFITS_IN_EXCHANGE_FOR_SEXUAL_FAVORS = "promising someone company profits in exchange for sexual favors.";
const string CONST_THAT_SEEM_TO_TOUCH_ON_EVERY_FETISH_KNOWN_TO_MAN = "that seem to touch on every fetish known to man.";
const string CONST_TO_THE_FDA_OFFICIAL_OVERSEEING_THE_CEO_S_PRODUCTS = "to the FDA official overseeing the CEO's products.";
const string CONST_IMPLYING_THAT_HE_HAS_ENSLAVED_HIS_HOUSESERVANTS = "implying that he has enslaved his houseservants.";
const string CONST_TO_HIMSELF_THEY_RE_VERY_STEAMY = "to himself.  They're very steamy.";
const string CONST_TO_AN_ILLICIT_GAY_LOVER = "to an illicit gay lover.";
const string CONST_TO_THE_JUDGE_THAT_ACQUIT_HIM_IN_A_CORRUPTION_TRIAL = "to the judge that acquit him in a corruption trial.";
const string CONST_ADDRESSED_TO_HIS_PET_DOG_YIKES = "addressed to his pet dog.  Yikes.";

const string CONST_PLAYING_WITH_FECES_AND_URINE = "playing with feces and urine.";
const string CONST_TORTURING_AN_EMPLOYEE_WITH_A_HOT_IRON = "torturing an employee with a hot iron.";
const string CONST_WAVING_A_NAZI_FLAG_AT_A_SUPREMACIST_RALLY = "waving a Nazi flag at a supremacist rally.";
const string CONST_CASTRATING_HIMSELF = "castrating himself.";
const string CONST_MAKING_OUT_WITH_AN_FDA_OFFICIAL_OVERSEEING_THE_CEO_S_PRODUCTS = "making out with an FDA official overseeing the CEO's products.";
const string CONST_TONGUE_KISSING_AN_INFAMOUS_DICTATOR = "tongue-kissing an infamous dictator.";
const string CONST_ENGAGING_IN_HEAVY_BONDAGE_A_CUCUMBER_WAS_INVOLVED_IN_SOME_WAY = "engaging in heavy bondage.  A cucumber was involved in some way.";
const string CONST_PARTICIPATING_IN_A_MURDER = "participating in a murder.";
const string CONST_DIGGING_UP_GRAVES_AND_SLEEPING_WITH_THE_DEAD = "digging up graves and sleeping with the dead.";
const string CONST_ENGAGING_IN_LEWD_BEHAVIOR_WITH_ANIMALS = "engaging in lewd behavior with animals.";
const string CONST_SHOWING_THAT_HE_HAS_ENGAGED_IN_CONSISTENT_TAX_EVASION = "showing that he has engaged in consistent tax evasion.";
const string CONST_DESCRIBING_AN_INTRICATE_TAX_SCHEME = "describing an intricate tax scheme.";
const string CONST_CHEERFULLY_DESCRIBING_FOREIGN_CORPORATE_SWEATSHOPS = "cheerfully describing foreign corporate sweatshops.";
const string CONST_CONTAINING_A_MEMO_TERMINATE_THE_PREGNANCY_I_TERMINATE_YOU = "containing a memo: \"Terminate the pregnancy, I terminate you.\"";
const string CONST_WITH_A_LIST_OF_GAY_EMPLOYEES_ENTITLED_HOMO_WORKERS = "with a list of gay employees entitled \"Homo-workers\".";
const string CONST_DESCRIBING_A_GENETIC_MONSTER_CREATED_IN_A_LAB = "describing a genetic monster created in a lab.";
const string CONST_DOCUMENTING_THE_INFILTRATION_OF_A_PRO_CHOICE_GROUP = "documenting the infiltration of a pro-choice group.";
const string CONST_USED_TO_KEEP_TABS_ON_GAY_CITIZENS = "used to keep tabs on gay citizens.";
const string CONST_DOCUMENTING_HARMFUL_SPEECH_MADE_BY_INNOCENT_CITIZENS = "documenting \"harmful speech\" made by innocent citizens.";
const string CONST_CONTAINING_PRIVATE_INFORMATION_ON_INNOCENT_CITIZENS = "containing private information on innocent citizens.";
const string CONST_DOCUMENTING_THE_PLANNED_ASSASSINATION_OF_A_LIBERAL_FEDERAL_JUDGE = "documenting the planned assassination of a Liberal federal judge.";
const string CONST_DOCUMENTING_THE_OVERTHROW_OF_A_GOVERNMENT = "documenting the overthrow of a government.";

const string CONST_DOCUMENTING_WIDESPREAD_CORRUPTION_IN_THE_FORCE = "documenting widespread corruption in the force.";
const string CONST_DOCUMENTING_A_FORCED_CONFESSION = "documenting a forced confession.";
const string CONST_DOCUMENTING_A_SYSTEMATIC_INVASION_OF_PRIVACY_BY_THE_FORCE = "documenting a systematic invasion of privacy by the force.";
const string CONST_DOCUMENTING_A_POLICE_TORTURE_CASE = "documenting a police torture case.";
const string CONST_DOCUMENTING_HUMAN_RIGHTS_ABUSES_BY_THE_FORCE = "documenting human rights abuses by the force.";

const string CONST_DOCUMENTING_GLADIATORIAL_MATCHES_HELD_BETWEEN_PRISONERS_BY_GUARDS = "documenting gladiatorial matches held between prisoners by guards.";
const string CONST_PROMISING_CONSERVATIVE_RULINGS_IN_EXCHANGE_FOR_APPOINTMENTS = "promising Conservative rulings in exchange for appointments.";
const string CONST_TAKING_BRIBES_TO_ACQUIT_MURDERERS = "taking bribes to acquit murderers.";

const string CONST_SHOWING_HUMAN_TEST_SUBJECTS_DYING_UNDER_GENETIC_RESEARCH = "showing human test subjects dying under genetic research.";
const string CONST_COVERING_UP_THE_ACCIDENTAL_CREATION_OF_A_GENETIC_MONSTER = "covering up the accidental creation of a genetic monster.";
const string CONST_STUDYING_THE_EFFECTS_OF_TORTURE_ON_CATS = "studying the effects of torture on cats.";
const string CONST_DOCUMENTING_HORRIFIC_ANIMAL_RIGHTS_ABUSES = "documenting horrific animal rights abuses.";


const string CONST_DOCUMENTING_WIDESPREAD_CORRUPTION_AMONG_PRISON_EMPLOYEES = "documenting widespread corruption among prison employees.";
const string CONST_DOCUMENTING_A_PRISON_TORTURE_CASE = "documenting a prison torture case.";
const string CONST_DOCUMENTING_HUMAN_RIGHTS_ABUSES_BY_PRISON_GUARDS = "documenting human rights abuses by prison guards.";


const string CONST_PLANNING_TO_DRUM_UP_A_FALSE_SCANDAL_ABOUT_A_LIBERAL_FIGURE = "planning to drum up a false scandal about a Liberal figure.";
const string CONST_INSTRUCTING_A_FEMALE_ANCHOR_TO_GET_SEXIER_OR_GET_A_NEW_JOB = "instructing a female anchor to 'get sexier or get a new job'.";
const string CONST_MANDATING_NEGATIVE_COVERAGE_OF_LIBERAL_POLITICIANS = "mandating negative coverage of Liberal politicians.";
const string CONST_CALLING_THEIR_NEWS_THE_VANGUARD_OF_CONSERVATIVE_THOUGHT = "calling their news 'the vanguard of Conservative thought'.";

const string CONST_SAYING_IT_S_OKAY_TO_LIE_THEY_DON_T_NEED_THE_TRUTH = "saying 'it's okay to lie, they don't need the truth'.";
const string CONST_CALLING_LISTENERS_SHEEP_TO_BE_TOLD_WHAT_TO_THINK = "calling listeners 'sheep to be told what to think'.";


const string CONST_PRESS_ANY_KEY_TO_REFLECT_ON_THE_REPORT = "Press any key to reflect on the report.";
const string CONST_PRESS_ENTER_TO_REFLECT_ON_THE_REPORT = "Press Enter to reflect on the report.  ";
const string DOLLAR_SIGN = "$";
const string CONST_TOTAL_LIQUID_ASSETS = "Total Liquid Assets:";
const string CONST_MISCELLANEOUS_LOOT = "Miscellaneous Loot";
const string CONST_AMMUNITION = "Ammunition";
const string CONST_CLOTHING_AND_ARMOR = "Clothing and Armor";
const string CONST_TOOLS_AND_WEAPONS = "Tools and Weapons";
const string CONST_CASH = "Cash";
const string DOLLAR_ZERO = " ($0)";
const string PAREN_MINUS_DOLLAR = " (-$";
const string PAREN_PLUS_DOLLAR = " (+$";
const string CONST_X_MINUS_SIGN = "-";
const string CONST_X_PLUS_SIGN = "+";
const string CONST_NET_CHANGE_THIS_MONTH_DAY = "Net Change This Month (Day):";
const string MINUS_DOLLAR = "-$";
const string PLUS_DOLLAR = "+$";
const string CONST_LIBERAL_CRIME_SQUAD_FUNDING_REPORT = "Liberal Crime Squad: Funding Report";
const string CONST_THIS_IS_BOUND_TO_GET_THE_CONSERVATIVE_MASSES_A_LITTLE_RILED_UP = "This is bound to get the Conservative masses a little riled up.";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_AM_RADIO_PLANS = "The Liberal Guardian runs a story featuring AM radio plans ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_CABLE_NEWS_MEMOS = "The Liberal Guardian runs a story featuring cable news memos ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_PRISON_DOCUMENTS = "The Liberal Guardian runs a story featuring prison documents ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_RESEARCH_PAPERS = "The Liberal Guardian runs a story featuring research papers ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_WITH_EVIDENCE_OF_A_CONSERVATIVE_JUDGE = "The Liberal Guardian runs a story with evidence of a Conservative judge ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_POLICE_RECORDS = "The Liberal Guardian runs a story featuring police records ";
const string CONST_THIS_IS_BOUND_TO_GET_THE_GOVERNMENT_A_LITTLE_RILED_UP = "This is bound to get the Government a little riled up.";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_CIA_AND_OTHER_INTELLIGENCE_FILES = "The Liberal Guardian runs a story featuring CIA and other intelligence files ";
const string CONST_THIS_IS_THE_BEGINNING_OF_THE_END_FOR_THE_CONSERVATIVE_CRIME_SQUAD = "This is the beginning of the end for the Conservative Crime Squad.";
const string CONST_NEWS_DENOUNCE_THE_CCS = "News denounce the CCS.";
const string CONST_TOWARD_THE_REVELATIONS_AND_THE_SPEED_WITH_WHICH_EVEN_AM_RADIO_AND_CABLE = "toward the revelations, and the speed with which even AM Radio and Cable";
const string CONST_FOR_MONTHS_ONE_THING_IS_CLEAR_HOWEVER_FROM_THE_IMMEDIATE_PUBLIC_REACTION = "for months. One thing is clear, however, from the immediate public reaction";
const string CONST_COUNTRY_AND_THE_FULL_RAMIFICATIONS_OF_THIS_REVELATION_MAY_NOT_BE_FELT = "country, and the full ramifications of this revelation may not be felt";
const string CONST_THE_SCANDAL_REACHES_INTO_THE_HEART_OF_THE_CONSERVATIVE_LEADERSHIP_IN_THE = "The scandal reaches into the heart of the Conservative leadership in the";
const string CONST_AGAINST = "against.";
const string CONST_AS_A_FOIL_WHEN_NO_OTHER_ENEMIES_WERE_PRESENT_TO_DIRECT_PUBLIC_ENERGY = "as a foil when no other enemies were present to direct public energy";
const string CONST_ABOVE_PROSECUTION_AND_COULD_HUNT_DOWN_LAW_ABIDING_LIBERALS_AND_ACT = "above prosecution, and could hunt down law-abiding Liberals and act";
const string CONST_EXTENSIVE_PLANNING_TO_CREATE_AN_EXTRA_JUDICIAL_DEATH_SQUAD_THAT_WOULD_BE = "extensive planning to create an extra-judicial death squad that would be";
const string CONST_IN_THE_STATE_AND_FEDERAL_GOVERNMENTS_SECTIONS_PRECISELY_DOCUMENT_THE = "in the state and federal governments. Sections precisely document the";
const string CONST_RESPONSIBILITIES_OF_CONSERVATIVE_CRIME_SQUAD_SYMPATHIZERS_AND_SUPPORTERS = "responsibilities of Conservative Crime Squad sympathizers and supporters";
const string CONST_THE_CCS_ORGANIZATION_ALSO_REVEALING_IN_EXTREME_DETAIL_THE_NAMES_AND = "the CCS organization, also revealing in extreme detail the names and ";
const string CONST_THE_LIBERAL_GUARDIAN_RUNS_MORE_THAN_ONE_THOUSAND_PAGES_OF_DOCUMENTS_ABOUT = "The Liberal Guardian runs more than one thousand pages of documents about ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_CORPORATE_FILES = "The Liberal Guardian runs a story featuring Corporate files ";
const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_A_MAJOR_CEO_S_TAX_PAPERS = "The Liberal Guardian runs a story featuring a major CEO's tax papers ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_LOVE_LETTERS_FROM_A_MAJOR_CEO = "The Liberal Guardian runs a story featuring love letters from a major CEO ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_PHOTOS_OF_A_MAJOR_CEO = "The Liberal Guardian runs a story featuring photos of a major CEO ";
const string CONST_ENTER_NOT_IN_THIS_MONTH_S_LIBERAL_GUARDIAN = "Enter - Not in this month's Liberal Guardian";
const string CONST_DO_YOU_WANT_TO_RUN_A_SPECIAL_EDITION = "Do you want to run a special edition?";
const string CONST_X_LIBERAL_GUARDIAN = "Liberal Guardian.";
const string CONST_THE_RESPONSE_IS_ELECTRIC_EVERYONE_IS_TALKING_ABOUT_THIS_MONTH_S = "The response is electric. Everyone is talking about this month's ";
const string CONST_THE_RESPONSE_IS_VERY_STRONG_PEOPLE_ARE_CHANGING_THEIR_MINDS = "The response is very strong. People are changing their minds.";
const string CONST_MANY_PEOPLE_ARE_READING_IT = "Many people are reading it.";
const string CONST_A_FAIR_NUMBER_OF_PEOPLE_ARE_READING_IT = "A fair number of people are reading it.";
const string CONST_VERY_FEW_PEOPLE_SEEM_TO_BE_INTERESTED = "Very few people seem to be interested.";
const string CONST_UNFORTUNATELY_NOBODY_SEEMS_INTERESTED = "Unfortunately, nobody seems interested.";
const string CONST_THE_ONLY_READERS_ARE_CONSERVATIVES_WHO_SEEM_TO_THINK_IT_S_FUNNY = "The only readers are Conservatives, who seem to think it's funny.";
const string CONST_IS_PUBLISHED = " is published.";
const string CONST_THE_MONTHLY_LIBERAL_GUARDIAN_ONLINE_NEWSLETTER = "The monthly Liberal Guardian online newsletter";
const string CONST_THE_MONTHLY_LIBERAL_GUARDIAN_NEWSPAPER = "The monthly Liberal Guardian newspaper";

const string tag_LOOT_AMRADIOFILES = "LOOT_AMRADIOFILES";
const string tag_LOOT = "LOOT";
const string tag_LOOT_CABLENEWSFILES = "LOOT_CABLENEWSFILES";
const string tag_LOOT_PRISONFILES = "LOOT_PRISONFILES";
const string tag_LOOT_RESEARCHFILES = "LOOT_RESEARCHFILES";
const string tag_LOOT_JUDGEFILES = "LOOT_JUDGEFILES";
const string tag_LOOT_POLICERECORDS = "LOOT_POLICERECORDS";
const string tag_LOOT_SECRETDOCUMENTS = "LOOT_SECRETDOCUMENTS";
const string tag_LOOT_INTHQDISK = "LOOT_INTHQDISK";
const string tag_LOOT_CCS_BACKERLIST = "LOOT_CCS_BACKERLIST";
const string tag_LOOT_CORPFILES = "LOOT_CORPFILES";
const string tag_LOOT_CEOTAXPAPERS = "LOOT_CEOTAXPAPERS";
const string tag_LOOT_CEOLOVELETTERS = "LOOT_CEOLOVELETTERS";
const string tag_LOOT_CEOPHOTOS = "LOOT_CEOPHOTOS";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

enum lootTypeTags {
	ENUM_tag_LOOT_CEOPHOTOS,
	ENUM_tag_LOOT_CEOLOVELETTERS,
	ENUM_tag_LOOT_CEOTAXPAPERS,
	ENUM_tag_LOOT_CORPFILES,
	ENUM_tag_LOOT_CCS_BACKERLIST,
	ENUM_tag_LOOT_INTHQDISK,
	ENUM_tag_LOOT_SECRETDOCUMENTS,
	ENUM_tag_LOOT_POLICERECORDS,
	ENUM_tag_LOOT_JUDGEFILES,
	ENUM_tag_LOOT_RESEARCHFILES,
	ENUM_tag_LOOT_PRISONFILES,
	ENUM_tag_LOOT_CABLENEWSFILES,
	ENUM_tag_LOOT_AMRADIOFILES,
};
map<string, int> lootTypeIDEnum = {
	map<string, int> ::value_type(tag_LOOT_CEOPHOTOS, ENUM_tag_LOOT_CEOPHOTOS),
	map<string, int> ::value_type(tag_LOOT_CEOLOVELETTERS, ENUM_tag_LOOT_CEOLOVELETTERS),
	map<string, int> ::value_type(tag_LOOT_CEOTAXPAPERS, ENUM_tag_LOOT_CEOTAXPAPERS),
	map<string, int> ::value_type(tag_LOOT_CORPFILES, ENUM_tag_LOOT_CORPFILES),
	map<string, int> ::value_type(tag_LOOT_CCS_BACKERLIST, ENUM_tag_LOOT_CCS_BACKERLIST),
	map<string, int> ::value_type(tag_LOOT_INTHQDISK, ENUM_tag_LOOT_INTHQDISK),
	map<string, int> ::value_type(tag_LOOT_SECRETDOCUMENTS, ENUM_tag_LOOT_SECRETDOCUMENTS),
	map<string, int> ::value_type(tag_LOOT_POLICERECORDS, ENUM_tag_LOOT_POLICERECORDS),
	map<string, int> ::value_type(tag_LOOT_JUDGEFILES, ENUM_tag_LOOT_JUDGEFILES),
	map<string, int> ::value_type(tag_LOOT_RESEARCHFILES, ENUM_tag_LOOT_RESEARCHFILES),
	map<string, int> ::value_type(tag_LOOT_PRISONFILES, ENUM_tag_LOOT_PRISONFILES),
	map<string, int> ::value_type(tag_LOOT_CABLENEWSFILES, ENUM_tag_LOOT_CABLENEWSFILES),
	map<string, int> ::value_type(tag_LOOT_AMRADIOFILES, ENUM_tag_LOOT_AMRADIOFILES),
};
static const char dotdotdot[] = ". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ";
//Temporary, maybe put special edition definition into an xml file. -XML
static const string document_types[] =
{  // This list MUST be in alphabetical order for binary_search() to work right
	tag_LOOT_AMRADIOFILES,
	tag_LOOT_CABLENEWSFILES,
	tag_LOOT_CCS_BACKERLIST,
	tag_LOOT_CEOLOVELETTERS,
	tag_LOOT_CEOPHOTOS,
	tag_LOOT_CEOTAXPAPERS,
	tag_LOOT_CORPFILES,
	tag_LOOT_INTHQDISK,
	tag_LOOT_JUDGEFILES,
	tag_LOOT_POLICERECORDS,
	tag_LOOT_PRISONFILES,
	tag_LOOT_RESEARCHFILES,
	tag_LOOT_SECRETDOCUMENTS
};
#endif	//LCSMONTHLY_CPP
#ifdef	LIBERALAGENDA_CPP
// liberalagenda.cpp

#include "../creature/creatureEnums.h"
//#include "../common/commondisplay.h"
void set_alignment_color(short alignment, bool extended_range = false);
//#include "../common/getnames.h"
string getlaw(int l);
//#include "../common/commonactions.h"
void cleangonesquads();
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../common/musicClass.h"
vector<string> supremeChars;
vector<string> courtChars;
map<short, vector<string> > endgameLawStrings;
#include "../common/creaturePool.h"
enum Pages
{
	PAGE_LEADERS,
	PAGE_ISSUES_A,
	PAGE_ISSUES_B,
	PAGENUM
};
vector<string> disbandingMessage;
vector<string> issue_phrases;

extern bool stalinmode;
extern char courtname[COURTNUM][POLITICIAN_NAMELEN];
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern int disbandtime;
extern int year;
extern MusicClass music;
extern short court[COURTNUM];
extern short exec[EXECNUM];
extern short execterm;
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short senate[SENATENUM];
extern short wincondition;

const string pressLToViewHighScores = "Press 'L' to view the high score list.";

const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";

const string CONST_COURTCHARS_TXT = "courtChars.txt";
const string CONST_SUPREMECHARS_TXT = "supremeChars.txt";
const string CONST_ISSUE_PHRASES_TXT = "issue_phrases.txt";
const string CONST_DISBANDINGMESSAGE_TXT = "disbandingMessage.txt";
vector<file_and_text_collection> liberl_agenda_text_file_collection = {
customText(&disbandingMessage, MOSTLY_ENDINGS_FOLDER + CONST_DISBANDINGMESSAGE_TXT),
customText(&issue_phrases, MOSTLY_ENDINGS_FOLDER + CONST_ISSUE_PHRASES_TXT),
customText(&supremeChars, MOSTLY_ENDINGS_FOLDER + CONST_SUPREMECHARS_TXT),
customText(&courtChars, MOSTLY_ENDINGS_FOLDER + CONST_COURTCHARS_TXT),
};
const string CONST_TYPE_THIS_LIBERAL_PHRASE_TO_CONFIRM_PRESS_A_WRONG_LETTER_TO_RETHINK_IT = "Type this Liberal phrase to confirm (press a wrong letter to rethink it):";
const string CONST_ARE_YOU_SURE_YOU_WANT_TO_DISBAND = "Are you sure you want to disband?";
const string CONST_PRESS_D_TO_DISBAND_AND_WAIT_USE_CURSORS_FOR_OTHER_PAGES_ANY_OTHER_KEY_TO_EXIT = "Press D to disband and wait. Use cursors for other pages. Any other key to exit.";
const string CONST_liberalagenda064 = "Arch-Conservative";
const string DASH_SPACE = "-  ";
const string CONST_X_CONSERVATIVE_SPACE = "Conservative  ";
const string CONST_X_MODERATE_SPACE = "moderate  ";
const string CONST_X_LIBERAL_SPACE = "Liberal  ";
const string CONST_X_ELITE_LIBERAL_SPACE = "Elite Liberal  ";
const string CONST_X_STALINIST_SPACE = "Stalinist  ";
const string CONST_TRIAL_JUDGES = "Trial Judges";
const string CONST_STALINIST_SHOW = "Stalinist Show";
const string CONST_REPLACED_BY = "Replaced By";
const string CONST_ETHICS_OFFICERS = "Ethics Officers";
const string CONST_BY_CORPORATE = "By Corporate";
const string CONST_REPLACED = "Replaced";
const string CONST_X_SENATE_COLON = "Senate: ";
const string CONST_X_HOUSE_COLON = "House: ";
const string CONST_ATTORNEY_GENERAL = "Attorney General: ";
const string CONST_INTERNAL_AFFAIRS_COMMISSAR = "Internal Affairs Commissar: ";
const string CONST_MINISTER_OF_TRUTH = "Minister of Truth: ";
const string CONST_SECRETARY_OF_STATE = "Secretary of State: ";
const string CONST_FOREIGN_AFFAIRS_COMMISSAR = "Foreign Affairs Commissar: ";
const string CONST_MINISTER_OF_PEACE = "Minister of Peace: ";
const string CONST_VICE_PRESIDENT = "Vice President: ";
const string CONST_PREMIER = "Premier: ";
const string CONST_MINISTER_OF_LOVE = "Minister of Love: ";
const string CONST_2ND_TERM = "(2nd Term):";
const string CONST_1ST_TERM = "(1st Term):";
const string CONST_PRESIDENT = "President ";
const string CONST_GENERAL_SECRETARY = "General Secretary: ";
const string CONST_KING = "King: ";
const string CONST_THE_CONGRESS_CONSISTS_OF_STALINIST_PARTY_LOYALISTS = "The Congress consists of Stalinist Party loyalists.";
const string CONST_THE_CONGRESS_CONSISTS_OF_CEOS_AND_TELEVANGELISTS = "The Congress consists of CEOs and televangelists.";

const string CONST_X_GEN_SUM_FOOTER = "�                 훤袴袴袴袴賈袴袴袴袴袴鳩袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴";
const string GENERAL_SUMMARY_ISSUES_HEADER = "� GENERAL SUMMARY � ISSUES A � ISSUES B �";
const string FORMATTED_LINE = "�袴袴袴袴袴袴袴袴敲컴컴컴컴컴쩡컴컴컴컴커";
const string CONST_X_GEN_SUM_FOOTER_3 = "鳩袴袴袴袴袴袴袴袴鳩袴袴袴袴暠          훤袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴";
const string CONST_X_GENERAL_SUMMARY_ISSUES_A_ISSUES_B_3 = "� GENERAL SUMMARY � ISSUES A � ISSUES B �";
const string CONST_X_GEN_SUM_HEADER_3 = "旼컴컴컴컴컴컴컴컴쩡컴컴컴컴케袴袴袴袴袴�";
const string CONST_X_GEN_SUM_FOOTER_2 = "鳩袴袴袴袴袴袴袴袴�          훤袴袴袴袴賈袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴�";
const string CONST_X_GENERAL_SUMMARY_ISSUES_A_ISSUES_B_2 = "� GENERAL SUMMARY � ISSUES A � ISSUES B �";
const string CONST_X_GEN_SUM_HEADER_2 = "旼컴컴컴컴컴컴컴컴�袴袴袴袴袴뼛컴컴컴컴커";
const string CONST_THE_COUNTRY_HAS_BEEN_STALINIZED = "The country has been Stalinized.";
const string CONST_THE_COUNTRY_HAS_BEEN_REAGANIFIED = "The country has been Reaganified.";
const string CONST_THE_COUNTRY_HAS_ACHIEVED_ELITE_LIBERAL_STATUS = "The country has achieved Elite Liberal status!";
const string CONST_THE_COUNTRY_HAS_ACHIEVED_LIBERAL_STATUS = "The country has achieved Liberal status!";

const string CONST_THE_STATUS_OF_THE_LIBERAL_AGENDA = "The Status of the Liberal Agenda";
const string CONST_THE_ABJECT_FAILURE_OF_THE_LIBERAL_AGENDA = "The Abject Failure of the Liberal Agenda";
const string CONST_THE_TRIUMPH_OF_THE_LIBERAL_AGENDA = "The Triumph of the Liberal Agenda";
const string tag_Sta = "Sta, ";
const string tag_Libp = "Lib+, ";
const string tag_Lib = "Lib, ";
const string tag_Mod = "Mod, ";
const string tag_Cons = "Cons, ";
const string tag_Consp = "Cons+";
#endif	//LIBERALAGENDA_CPP
#ifdef	LOCATIONS_CPP
// locations.cpp

#include "../creature/newcreature.h"
#include "../locations/locations.h"
#include "../common/creaturePool.h"
#include "../customMaps.h"
void strcpy(char* c, string str);
void strcat(char* c, string str);
extern short lawList[LAWNUM];
const string CONST_X_BUNKER = "Bunker";
const string CONST_BAR_GRILL = "Bar & Grill";
const string CONST_BOMB_SHELTER = "Bomb Shelter";
const string CONST_OUBLIETTE = "Oubliette";
const string CONST_CLINIC = "Clinic";
const string CONST_U_HOSPITAL = "U Hospital";
const string CONST_RADIO_STATION = "Radio Station";
const string CONST_NEWS_STATION = "News Station";
const string CONST_CHEM_FACT = "Chem Fact";
const string CONST_REFINERY = "Refinery";
const string CONST_PLAST_FACT = "Plast Fact";
const string CONST_ALUM_FACT = "Alum Fact";
const string CONST_SHELTER = "Shelter";
const string CONST_CEO_HOUSE = "CEO House";
const string CONST_X_BANK = "Bank";
const string CONST_CORP_HQ = "Corp. HQ";
const string CONST_MINIPAX = "Minipax";
const string CONST_INT_HQ = "Int. HQ";
const string CONST_MINILUV = "Miniluv";
const string CONST_NPOWER_PLANT = "NPower Plant";
const string CONST_NWASTE_CENTER = "NWaste Center";
const string CONST_JUDGE_HALL = "Judge Hall";
const string CONST_BLACK_MARKET = "Black Market";
const string CONST_ROBERT_E_LEE_BUNKER = "Robert E. Lee Bunker";
const string CONST_DESERT_EAGLE_BAR_GRILL = "Desert Eagle Bar & Grill";
const string CONST_FALLOUT_SHELTER = "Fallout Shelter";
const string CONST_X_PARK = "Park";
const string CONST_X_SPACE_PARK = " Park";
const string CONST_X_LATTE_STAND = "Latte Stand";
const string CONST_LATTE_STAND = " Latte Stand";
const string CONST_CIGAR_BAR = "Cigar Bar";
const string CONST_GENTLEMEN_S_CLUB = " Gentlemen's Club";
const string CONST_NET_CAFE = "Net Cafe";
const string CONST_INTERNET_CAFE = " Internet Cafe";
const string CONST_X_VEGAN_COOP = "Vegan Co-op";
const string CONST_VEGAN_CO_OP = " Vegan Co-op";
const string CONST_X_JUICE_BAR = "Juice Bar";
const string CONST_JUICE_BAR = " Juice Bar";
const string CONST_CRACK_HOUSE = "Crack House";
const string CONST_DISPENSARY = "Dispensary";
const string CONST_MARIJUANA_DISPENSARY = "Marijuana Dispensary";
const string CONST_CANNABIS_LOUNGE = "Cannabis Lounge";
const string CONST_COFFEE_HOUSE = "Coffee House";
const string CONST_DRUGS_CENTER = "Drugs Center";
const string CONST_RECREATIONAL_DRUGS_CENTER = "Recreational Drugs Center";
const string CONST_ST = " St. ";
const string CONST_X_SWEATSHOP = "Sweatshop";
const string CONST_GARMENT_MAKERS = " Garment Makers";
const string CONST_THE_OUBLIETTE = "The Oubliette";
const string CONST_DEPT_STORE = "Dept. Store";
const string CONST_S_DEPARTMENT_STORE = "'s Department Store";
const string CONST_USED_CARS = "Used Cars";
const string CONST_S_USED_CARS = "'s Used Cars";
const string CONST_COSMETICS_LAB = "Cosmetics Lab";
const string CONST_COSMETICS = " Cosmetics";
const string CONST_GENETICS_LAB = "Genetics Lab";
const string CONST_GENETICS = " Genetics";
const string CONST_THE_FREE_CLINIC = "The Free Clinic";
const string CONST_THE_UNIVERSITY_HOSPITAL = "The University Hospital";
const string CONST_PROJECTS = "Projects";
const string CONST_ST_HOUSING_PROJECTS = " St. Housing Projects";
const string CONST_APTS = " Apts";
const string CONST_APARTMENTS = " Apartments";
const string CONST_CONDOS = " Condos";
const string CONST_CONDOMINIUMS = " Condominiums";
const string CONST_AM_RADIO_STATION = "AM Radio Station";
const string CONST_CABLE_NEWS_STATION = "Cable News Station";
const string CONST_CHEMICAL_FACTORY = "Chemical Factory";
const string CONST_AUTO_PLANT = "Auto Plant";
const string CONST_OIL_REFINERY = "Oil Refinery";
const string CONST_PLASTIC_FACTORY = "Plastic Factory";
const string CONST_ALUMINUM_FACTORY = "Aluminum Factory";
const string CONST_BUILDING = "Building";
const string CONST_BUILDING_SITE = "Building Site";
const string CONST_TOY = "Toy";
const string CONST_TOY_FACTORY = "Toy Factory";
const string CONST_PACKING = "Packing";
const string CONST_PACKING_PLANT = "Packing Plant";
const string CONST_STEEL = "Steel";
const string CONST_STEEL_PLANT = "Steel Plant";
const string CONST_DRILL = "Drill";
const string CONST_DRILL_FACTORY = "Drill Factory";
const string CONST_FERTILIZER = "Fertilizer";
const string CONST_FERTILIZER_PLANT = "Fertilizer Plant";
const string CONST_CEMENT = "Cement";
const string CONST_CEMENT_FACTORY = "Cement Factory";
const string CONST_PAPER_MILL = "Paper Mill";
const string CONST_X_WAREHOUSE = "Warehouse";
const string CONST_MEAT_PLANT = "Meat Plant";
const string CONST_ABANDONED = "Abandoned ";
const string CONST_HOMELESS_SHELTER = "Homeless Shelter";
const string CONST_CEO_RESIDENCE = "CEO Residence";
const string CONST_CEO_CASTLE = "CEO Castle";
const string CONST_PAWNSHOP = "Pawnshop";
const string CONST_PAWN_GUN = " Pawn & Gun";
const string CONST_S_PAWNSHOP = "'s Pawnshop";
const string CONST_AMERICAN_BANK_CORP = "American Bank Corp";
const string CONST_CORPORATE_HQ = "Corporate HQ";
const string CONST_WHITE_HOUSE = "White House";
const string CONST_X_ARMY_BASE = "Army Base";
const string CONST_ARMY_BASE = " Army Base";
const string CONST_MINISTRY_OF_PEACE = "Ministry of Peace";
const string CONST_INTELLIGENCE_HQ = "Intelligence HQ";
const string CONST_MINISTRY_OF_LOVE = "Ministry of Love";
const string CONST_NUCLEAR_POWER_PLANT = "Nuclear Power Plant";
const string CONST_NUCLEAR_WASTE_CENTER = "Nuclear Waste Center";
const string CONST_X_PRISON = "Prison";
const string CONST_X_SPACE_PRISON = " Prison";
const string CONST_JOYCAMP = "Joycamp";
const string CONST_FORCED_LABOR_CAMP = " Forced Labor Camp";
const string CONST_FIRE_STATION = "Fire Station";
const string CONST_FIREMAN_HQ = "Fireman HQ";
const string CONST_X_COURTHOUSE = "Courthouse";
const string CONST_HALLS_OF_ULTIMATE_JUDGMENT = "Halls of Ultimate Judgment";
const string CONST_POLICE_STATION = "Police Station";
const string CONST_DEATH_SQUAD_HQ = "Death Squad HQ";
const string CONST_LATTE_NAME_2_TXT = "latte_name_2.txt";
const string CONST_LATTE_NAME_TXT = "latte_name.txt";
const string CONST_CAFE_NAME_2_TXT = "cafe_name_2.txt";
const string CONST_CAFE_NAME_TXT = "cafe_name.txt";
const string CONST_VEGAN_NAME_2_TXT = "vegan_name_2.txt";
const string CONST_VEGAN_NAME_TXT = "vegan_name.txt";
const string CONST_JUICE_NAME_2_TXT = "juice_name_2.txt";
const string CONST_JUICE_NAME_TXT = "juice_name.txt";
const string CONST_LABOR_CAMP_NAME_2_TXT = "labor_camp_name_2.txt";
const string CONST_LABOR_CAMP_NAME_TXT = "labor_camp_name.txt";

const string tag_The = "The ";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string locations = "locations\\";

// Finds a location with the corresponding type and returns
// its index in the location array
vector<string> labor_camp_name;
vector<string> labor_camp_name_2;
vector<string> juice_name;
vector<string> juice_name_2;
vector<string> vegan_name;
vector<string> vegan_name_2;
vector<string> cafe_name;
vector<string> cafe_name_2;
vector<string> latte_name;
vector<string> latte_name_2;
vector<file_and_text_collection> locations_text_file_collection = {
	/*locations.cpp*/
	customText(&labor_camp_name, locations + CONST_LABOR_CAMP_NAME_TXT),
	customText(&labor_camp_name_2, locations + CONST_LABOR_CAMP_NAME_2_TXT),
	customText(&juice_name, locations + CONST_JUICE_NAME_TXT),
	customText(&juice_name_2, locations + CONST_JUICE_NAME_2_TXT),
	customText(&vegan_name, locations + CONST_VEGAN_NAME_TXT),
	customText(&vegan_name_2, locations + CONST_VEGAN_NAME_2_TXT),
	customText(&cafe_name, locations + CONST_CAFE_NAME_TXT),
	customText(&cafe_name_2, locations + CONST_CAFE_NAME_2_TXT),
	customText(&latte_name, locations + CONST_LATTE_NAME_TXT),
	customText(&latte_name_2, locations + CONST_LATTE_NAME_2_TXT),
};
#endif	//LOCATIONS_CPP
#ifdef	LOCATIONSPOOL_CPP
// locationsPool.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../items/armortype.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../common/commondisplay.h"
// for void printfunds(int,int,char*)
#include "../common/stringconversion.h"
//for string attribute_enum_to_string(int)
#include "../common/getnames.h"
// for cityname
#include "../common/translateid.h"
// for  getarmortype
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../set_color_support.h"
#include "locationsPool.h"
#include "../common/creaturePoolCreature.h"
#include "../items/money.h"
#include "../recruits.h"
/* creates your founder */
struct newGameArguments {
	const char recruits;
	const char base;
	const bool makelawyer;
	const bool gaylawyer;
	const bool sports_car;
	newGameArguments(char _recruits, char _base, bool _makelawyer, bool _gaylawyer, bool _sports_car) : recruits(_recruits), base(_base), makelawyer(_makelawyer), gaylawyer(_gaylawyer), sports_car(_sports_car) {}
};
Vehicle* newSportsCar();
void newVehicle(Vehicle *startcar);
#include "../common/equipment.h"
#include "../common/creaturePool.h"
void initlocation(Location &loc);
//#include "sitemode/sitemode.h"
void initsite(Location &loc);
#include "../common/commonactionsCreature.h"

#include "../items/lootTypePoolItem.h"
map<short, string> getActivityString;

vector<SiteTypes> classicDowntown = {
	SITE_RESIDENTIAL_APARTMENT_UPSCALE,
	SITE_GOVERNMENT_POLICESTATION,
	SITE_GOVERNMENT_COURTHOUSE,
	SITE_BUSINESS_BANK,
	SITE_GOVERNMENT_FIRESTATION,
	SITE_MEDIA_AMRADIO,
	SITE_MEDIA_CABLENEWS,
	SITE_BUSINESS_CIGARBAR,
	SITE_BUSINESS_LATTESTAND,
};
vector<SiteTypes> classicCommercial = {

	SITE_BUSINESS_DEPTSTORE,
	SITE_BUSINESS_PAWNSHOP,
	SITE_BUSINESS_HALLOWEEN,
	SITE_BUSINESS_CARDEALERSHIP,
};
vector<SiteTypes> classicUptown = {

	SITE_RESIDENTIAL_APARTMENT,
	SITE_HOSPITAL_UNIVERSITY,
	SITE_HOSPITAL_CLINIC,
	SITE_LABORATORY_GENETIC,
	SITE_LABORATORY_COSMETICS,
	SITE_BUSINESS_VEGANCOOP,
	SITE_BUSINESS_JUICEBAR,
	SITE_BUSINESS_INTERNETCAFE,
	SITE_OUTDOOR_PUBLICPARK,
};
vector<SiteTypes> classicOutOfTown = {

	SITE_GOVERNMENT_PRISON,
	SITE_GOVERNMENT_INTELLIGENCEHQ,
	SITE_INDUSTRY_NUCLEAR,
	SITE_CORPORATE_HEADQUARTERS,
	SITE_CORPORATE_HOUSE,
	SITE_GOVERNMENT_ARMYBASE,
};



vector<SiteTypes> seattleDowntown = {

	SITE_RESIDENTIAL_APARTMENT_UPSCALE,
	SITE_GOVERNMENT_POLICESTATION,
	SITE_GOVERNMENT_COURTHOUSE,
	SITE_BUSINESS_BANK,
	SITE_GOVERNMENT_FIRESTATION,
	SITE_MEDIA_AMRADIO,
	SITE_BUSINESS_CIGARBAR,
	SITE_BUSINESS_LATTESTAND,
	SITE_BUSINESS_DEPTSTORE,
};

vector<SiteTypes> seattleUptown = {

	SITE_RESIDENTIAL_APARTMENT,
	SITE_HOSPITAL_UNIVERSITY,
	SITE_HOSPITAL_CLINIC,
	SITE_LABORATORY_GENETIC,
	SITE_LABORATORY_COSMETICS,
	SITE_BUSINESS_VEGANCOOP,
	SITE_BUSINESS_JUICEBAR,
	SITE_BUSINESS_INTERNETCAFE,
	SITE_OUTDOOR_PUBLICPARK,
	SITE_BUSINESS_HALLOWEEN,
};
vector<SiteTypes> seattleOutOfTown = {

	SITE_GOVERNMENT_PRISON,
	SITE_GOVERNMENT_INTELLIGENCEHQ,
	SITE_CORPORATE_HEADQUARTERS,
	SITE_GOVERNMENT_ARMYBASE,
};

vector<SiteTypes> newYorkManhattan = {

	SITE_RESIDENTIAL_APARTMENT_UPSCALE,
	SITE_GOVERNMENT_POLICESTATION,
	SITE_GOVERNMENT_COURTHOUSE,
	SITE_BUSINESS_BANK,
	SITE_CORPORATE_HEADQUARTERS,
	SITE_MEDIA_AMRADIO,
	SITE_MEDIA_CABLENEWS,
	SITE_BUSINESS_CIGARBAR,
	SITE_OUTDOOR_PUBLICPARK,
	SITE_BUSINESS_DEPTSTORE,
	SITE_GOVERNMENT_PRISON,
};

vector<SiteTypes> newYorkLongIsland = {
	SITE_RESIDENTIAL_APARTMENT,
	SITE_GOVERNMENT_FIRESTATION,
	SITE_HOSPITAL_UNIVERSITY,
	SITE_HOSPITAL_CLINIC,
	SITE_BUSINESS_JUICEBAR,
	SITE_BUSINESS_INTERNETCAFE,
	SITE_INDUSTRY_POLLUTER,
	SITE_LABORATORY_GENETIC,
	SITE_GOVERNMENT_ARMYBASE,
};


vector<SiteTypes> losAngelesDowntown = {



	SITE_RESIDENTIAL_APARTMENT,
	SITE_GOVERNMENT_POLICESTATION,
	SITE_GOVERNMENT_COURTHOUSE,
	SITE_BUSINESS_BANK,
	SITE_GOVERNMENT_FIRESTATION,
	SITE_CORPORATE_HEADQUARTERS,
	SITE_HOSPITAL_UNIVERSITY,
	SITE_BUSINESS_DEPTSTORE,

};


vector<SiteTypes> hollyWoodUptown = {


	SITE_RESIDENTIAL_APARTMENT_UPSCALE,
	SITE_BUSINESS_VEGANCOOP,
	SITE_BUSINESS_HALLOWEEN,
	SITE_BUSINESS_CIGARBAR,
	SITE_MEDIA_AMRADIO,
	SITE_OUTDOOR_PUBLICPARK,
	SITE_CORPORATE_HOUSE,


};


vector<SiteTypes> seaportArea = {


	SITE_RESIDENTIAL_TENEMENT,
	SITE_HOSPITAL_CLINIC,
	SITE_LABORATORY_GENETIC,
	SITE_LABORATORY_COSMETICS,
	SITE_INDUSTRY_POLLUTER,
	SITE_BUSINESS_PAWNSHOP,
	SITE_INDUSTRY_SWEATSHOP,
	SITE_BUSINESS_CARDEALERSHIP,


};

vector<SiteTypes> washingtonDCDowntown = {

	SITE_GOVERNMENT_POLICESTATION,
	SITE_GOVERNMENT_FIRESTATION,
	SITE_GOVERNMENT_COURTHOUSE,
	SITE_BUSINESS_BANK,
	SITE_BUSINESS_CARDEALERSHIP,
	SITE_HOSPITAL_CLINIC,
	SITE_HOSPITAL_UNIVERSITY,
	SITE_BUSINESS_DEPTSTORE,

};
#include "../daily/daily.h"
enum cityLocationTagEnums {
	ENUM_tag_Downtown,
	ENUM_tag_University_District,
	ENUM_tag_u_District,
	ENUM_tag_Industrial_District,
	ENUM_tag_i_District,
	ENUM_tag_Shopping,
	ENUM_tag_Outskirts,
	ENUM_tag_Seaport_Area,
	ENUM_tag_Seaport,
	ENUM_tag_Outskirts_amp_Orange_County,
	ENUM_tag_City_Outskirts,
	ENUM_tag_Arlington,
	ENUM_tag_Hollywood,
	ENUM_tag_Greater_Hollywood,
	ENUM_tag_Manhattan,
	ENUM_tag_Manhattan_Island,
	ENUM_tag_Brooklyn_ampersand_Queens,
	ENUM_tag_Long_Island,
	ENUM_tag_The_Bronx
};

// Check if the player wants to move all items to a new location,
// using Shift + a number key.
const char upnums[] = "!@#$%^&*(";
#include "../daily/siege.h"
void addStringYear();
#include "../common/commonactions.h"
#include "../common/musicClass.h"
#include "../customMaps.h"
enum BusinessFronts
{
	BUSINESSFRONT_INSURANCE,
	BUSINESSFRONT_TEMPAGENCY,
	BUSINESSFRONT_RESTAURANT,
	BUSINESSFRONT_MISCELLANEOUS,
	BUSINESSFRONTNUM
};
// Gives you bloody armor
extern bool GIVEBLOODYARMOR;
// Start with lots of money
extern bool HIGHFUNDS;

extern long cursquadid;
extern vector<ClipType *> cliptype;
extern vector<ArmorType *> armortype;

extern bool multipleCityMode;
extern char endgamestate;
extern class Ledger ledger;
extern Deprecatedsquadst *activesquad;
extern int day;
extern int month;
extern int selectedsiege;
extern int stat_kidnappings;
extern int year;
extern MusicClass music;
extern short background_liberal_influence[VIEWNUM];
extern short lawList[LAWNUM];
extern vector<Deprecatedsquadst *> squad;
extern vector<WeaponType *> weapontype;

/* monthly - lets the player choose a special edition for the guardian */
int choosespecialedition(char &clearformess);
/* monthly - guardian - prints liberal guardian special editions */
void printnews(short l, short newspaper);
#include "../items/itemPool.h"
#include "../items/lootTypePool.h"
void giveActiveSquadThisLoot(Item* de);
const string needCar = " (Need Car)";
const string underSiege = " (Under Siege)";
const string secrecyLevel = "Secrecy: ";
const string heatLevel = "Heat: ";
const string travelDifCity = " - Travel to a Different City";
const string currentLocation = " (Current Location)";
const string safeHouse = " (Safe House)";
const string enemySafeHouse = " (Enemy Safe House)";
const string PARENTHESIS_CLOSED_DOWN = " (Closed Down)";
const string highSecurity = " (High Security)";
const string theLCS = "The Liberal Crime Squad";
const string CONST_POSSESSIONS_GO_TO_THE_SHELTER = ".  Possessions go to the shelter.";
const string CONST_EVICTION_NOTICE = "EVICTION NOTICE: ";
const string CONST_SLEEPER_AGENT = "sleeper agent";
const string CONST_AS_A = " as a ";
const string CONST_STAY_AT = "Stay at ";
const string ARROW_RIGHT = "-> ";
const string CONST_REGULAR_MEMBER = "regular member";
const string CONST_COME_TO = "Come to ";
const string TWO_SPACES = "   ";
const string CONST_BEST_SERVE_THE_LIBERAL_CAUSE = " best serve the Liberal cause?";
const string CONST_IN_WHAT_CAPACITY_WILL = "In what capacity will ";
const string CONST_MALL = "Mall";
const string CONST_X_NEW_YORK = ", New York";
const string CONST_CALIFORNIA = ", California";
const string CONST_VIRGINIA = ", Virginia";
const string CONST_OUTSKIRTS = " Outskirts";

const string CONST_NY = ", NY";
const string CONST_CA = ", CA";
const string CONST_VA = ", VA";
const string CONST_REPORTING_BUGS_TO_THE_DEV_TEAM = "Reporting Bugs to the Dev Team";
const string CONST_GOING_TO = "Going to ";
const string CONST_MAKING = "Making ";
const string CONST_A_BUG = "a bug";
const string CONST_TENDING_TO = "Tending to ";
const string CONST_HOW_MANY = "     How many?          ";
const string CONST_Z_STASH_THINGS_AT = "Z - Stash things at ";
const string CONST_Y_GET_THINGS_FROM = "Y - Get things from ";
const string CONST_CURSORS_INCREASE_OR_DECREASE_AMMO_ALLOCATION = "Cursors - Increase or decrease ammo allocation";
const string CONST_S_LIBERALLY_STRIP_A_SQUAD_MEMBER = "S - Liberally Strip a Squad member";
const string CONST_PRESS_A_NUMBER_TO_DROP_THAT_SQUAD_MEMBER_S_CONSERVATIVE_WEAPON = "Press a number to drop that Squad member's Conservative weapon";
const string CONST_PRESS_A_LETTER_TO_EQUIP_A_LIBERAL_ITEM = "Press a letter to equip a Liberal item";
const string CONST_X = " x";
const string CONST_EQUIP_THE_SQUAD = "Equip the Squad";

const string CONST_RECEIVE_IT = "receive it.";
const string CONST_DROP_A_CLIP = "drop a clip.";
const string CONST_RECEIVE_A_CLIP = "receive a clip.";
const string NOT_ERROR_BUT_CONTINUE = "For simplicity this function returns an error message, prompting 'continue;', this is not an error, but it needs to use 'continue;' anyway";
const string CONST_CAN_T_CARRY_ANY_MORE_AMMO = "Can't carry any more ammo.";
const string CONST_THAT_AMMO_DOESN_T_FIT = "That ammo doesn't fit.";
const string CONST_CAN_T_CARRY_AMMO_WITHOUT_A_GUN = "Can't carry ammo without a gun.";
const string CONST_NO_AMMO_AVAILABLE = "No ammo available!";
const string CONST_NO_AMMO_REQUIRED = "No ammo required!";
const string CONST_NO_SPARE_CLIPS = "No spare clips!";
const string CONST_NO_AMMO_TO_DROP = "No ammo to drop!";

const string CONST_STRIP_DOWN = "strip down.";

const string CONST_YOU_CAN_T_EQUIP_THAT = "You can't equip that.";
const string CONST_PRESS_A_LETTER_TO_SELECT_AN_ITEM = "Press a letter to select an item.";
const string CONST_X_X = "x";
const string CONST_locationsPool079 = "/";
const string CONST_SELECT_OBJECTS = "Select Objects";
const string CONST_TO_VIEW_OTHER_BASE_PAGES = ",. to view other base pages.";
const string CONST_SHIFT_AND_A_NUMBER_WILL_MOVE_ALL_ITEMS = "  Shift and a Number will move ALL items!";
const string CONST_T_TO_SORT_BY_TYPE = "T to sort by type.";
const string CONST_T_TO_SORT_BY_LOCATION = "T to sort by location.";
const string CONST_PRESS_A_LETTER_TO_ASSIGN_A_BASE_PRESS_A_NUMBER_TO_SELECT_A_BASE = "Press a Letter to assign a base.  Press a Number to select a base.";
const string CONST_NEW_LOCATION = "NEW LOCATION";
const string CONST_ITEM_CURRENT_LOCATION = "컴컴ITEM컴컴컴컴컴컴컴컴CURRENT LOCATION컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�";
const string CONST_MOVING_EQUIPMENT = "Moving Equipment";
const string CONST_EATING = " Eating";
const string CONST_locationsPool115 = "s";
const string CONST_DAILY_RATION = " Daily Ration";
const string CONST_NOT_ENOUGH_FOOD = "Not Enough Food";
const string CONST_OF_FOOD_LEFT = " of Food Left";
const string CONST_X_SPACE_DAY = " Day";
const string CONST_GENERATOR = "GENERATOR";
const string CONST_LIGHTS_OUT = "LIGHTS OUT";
const string CONST_TANK_TRAPS = "TANK TRAPS";
const string CONST_AA_GUN = "AA GUN";
const string CONST_BOOBY_TRAPS = "BOOBY TRAPS";
const string CONST_CAMERAS_ON = "CAMERAS ON";
const string CONST_CAMERAS_OFF = "CAMERAS OFF";
const string CONST_BUSINESS_FRONT = "BUSINESS FRONT";
const string CONST_PRINTING_PRESS = "PRINTING PRESS";
const string CONST_FORTIFIED_COMPOUND = "FORTIFIED COMPOUND";
const string CONST_THIS_LOCATION_HAS_INSUFFICIENT_FOOD_STORES = "This location has insufficient food stores.";
const string CONST_THIS_LOCATION_HAS_FOOD_FOR_ONLY_A_FEW_DAYS = "This location has food for only a few days.";
const string CONST_YOU_ARE_NOT_UNDER_SIEGE_YET = "You are not under siege...  yet.";
const string CONST_FIREMEN_ARE_RAIDING_THIS_LOCATION = "Firemen are raiding this location!";
const string CONST_THE_CCS_IS_RAIDING_THIS_LOCATION = "The CCS is raiding this location!";
const string CONST_THE_CORPORATIONS_ARE_RAIDING_THIS_LOCATION = "The Corporations are raiding this location!";
const string CONST_THE_MASSES_ARE_STORMING_THIS_LOCATION = "The masses are storming this location!";
const string CONST_THE_CIA_IS_RAIDING_THIS_LOCATION = "The CIA is raiding this location!";
const string CONST_THE_POLICE_ARE_RAIDING_THIS_LOCATION = "The police are raiding this location!";
const string CONST_THE_POLICE_HAVE_SURROUNDED_THIS_LOCATION = "The police have surrounded this location.";
const string CONST_ACTING_INDIVIDUALLY = "Acting Individually";
const string CONST_2_PRESS_Z_TO_ASSEMBLE_A_NEW_SQUAD = "2) Press Z to Assemble a New Squad";
const string CONST_1_R_REVIEW_ASSETS_AND_FORM_SQUADS = "1) R - Review Assets and Form Squads";
const string CONST_TO_FORM_A_NEW_SQUAD = "To form a new squad:";
const string CONST_NO_SQUAD_SELECTED = "No Squad Selected";
const string CONST_ENTER_BACK_ONE_STEP = "Enter - Back one step.";
const string CONST_ENTER_THE_SQUAD_IS_NOT_YET_LIBERAL_ENOUGH = "Enter - The squad is not yet Liberal enough.";
const string CONST_WHERE_WILL_THE_SQUAD_GO = "Where will the Squad go?";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string CONST_CASEBUSINESSFRONT_MISCELLANEOUS_TXT = "caseBUSINESSFRONT_MISCELLANEOUS.txt";
const string CONST_CASEBUSINESSFRONT_RESTAURANT_TXT = "caseBUSINESSFRONT_RESTAURANT.txt";
const string CONST_CASEBUSINESSFRONT_TEMPAGENCY_TXT = "caseBUSINESSFRONT_TEMPAGENCY.txt";
const string CONST_CASEBUSINESSFRONT_INSURANCE_TXT = "caseBUSINESSFRONT_INSURANCE.txt";
const string CONST_R_STOCKPILE_20_DAILY_RATIONS_OF_FOOD_150 = "R - Stockpile 20 daily rations of food ($150)";
const string CONST_F_SETUP_A_BUSINESS_FRONT_TO_WARD_OFF_SUSPICION_3000 = "F - Setup a Business Front to ward off suspicion ($3000)";
const string CONST_P_BUY_A_PRINTING_PRESS_TO_START_YOUR_OWN_NEWSPAPER_3000 = "P - Buy a Printing Press to start your own newspaper ($3000)";
const string CONST_A_INSTALL_AND_CONCEAL_AN_ILLEGAL_ANTI_AIRCRAFT_GUN_ON_THE_ROOF_200_000 = "A - Install and conceal an illegal Anti-Aircraft gun on the roof ($200,000)";
const string CONST_A_INSTALL_A_PERFECTLY_LEGAL_ANTI_AIRCRAFT_GUN_ON_THE_ROOF_35_000 = "A - Install a perfectly legal Anti-Aircraft gun on the roof ($35,000)";
const string CONST_G_BUY_A_GENERATOR_FOR_EMERGENCY_ELECTRICITY_3000 = "G - Buy a Generator for emergency electricity ($3000)";
const string CONST_T_RING_THE_COMPOUND_WITH_TANK_TRAPS_3000 = "T - Ring the Compound with Tank Traps ($3000)";
const string CONST_B_PLACE_BOOBY_TRAPS_THROUGHOUT_THE_COMPOUND_3000 = "B - Place Booby Traps throughout the Compound ($3000)";
const string CONST_C_PLACE_SECURITY_CAMERAS_AROUND_THE_COMPOUND_2000 = "C - Place Security Cameras around the Compound ($2000)";
const string CONST_W_FORTIFY_THE_COMPOUND_FOR_A_SIEGE_2000 = "W - Fortify the Compound for a Siege ($2000)";
const string CONST_W_FORTIFY_THE_BOMB_SHELTER_ENTRANCES_2000 = "W - Fortify the Bomb Shelter Entrances ($2000)";
const string CONST_W_REPAIR_THE_BUNKER_FORTIFICATIONS_2000 = "W - Repair the Bunker Fortifications ($2000)";
const string CONST_X_IF_YOU_DO_NOT_ENTER_ANYTHING_THEIR_REAL_NAME_WILL_BE_USED = "If you do not enter anything, their real name will be used.";
const string CONST_X_IN_ITS_PRESENCE = " in its presence?";
const string CONST_X_WHAT_NAME_WILL_YOU_USE_FOR_THIS_ = "What name will you use for this ";
const string CONST_locationsPool141 = "The Education of ";
const string CONST_TEMPORARY_SQUAD = "Temporary Squad";
const string tag_WEAPON_SPRAYCAN = "WEAPON_SPRAYCAN";

const string tag_LOOT = "LOOT";
const string tag_LOOT_SECRETDOCUMENTS = "LOOT_SECRETDOCUMENTS";
const string tag_LOOT_INTHQDISK = "LOOT_INTHQDISK";
const string tag_The_Bronx = "The Bronx";
const string tag_Long_Island = "Long Island";
const string tag_Brooklyn_ampersand_Queens = "Brooklyn & Queens";
const string tag_B = "B";
const string tag_Manhattan = "Manhattan";
const string tag_The = "The ";
const string tag_Manhattan_Island = "Manhattan Island";
const string tag_Greater_Hollywood = "Greater Hollywood";
const string tag_Hollywood = "Hollywood";
const string tag_Arlington = "Arlington";
const string tag_City_Outskirts = "City Outskirts";
const string tag_Seaport_Area = "Seaport Area";
const string tag_Shopping = "Shopping";
const string tag_Seaport = "Seaport";
const string tag_Outskirts_amp_Orange_County = "Outskirts & Orange County";
const string tag_Outskirts = "Outskirts";
const string tag_University_District = "University District";
const string tag_i_District = "I-District";
const string tag_Industrial_District = "Industrial District";
const string tag_u_District = "U-District";
const string tag_D = "D";
const string tag_Downtown = "Downtown";
const string tag_National_Mall = "National Mall";
const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_CLIP = "CLIP";
const string tag_CLIP_9 = "CLIP_9";
const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_SEMIPISTOL_9MM = "WEAPON_SEMIPISTOL_9MM";
const string tag_WEAPON_SMG_MP5 = "WEAPON_SMG_MP5";
const string tag_WEAPON_AUTORIFLE_AK47 = "WEAPON_AUTORIFLE_AK47";
map <string, int> cityLocationTags = {
map<string, int>::value_type(tag_Downtown, ENUM_tag_Downtown),
map<string, int>::value_type(tag_University_District, ENUM_tag_University_District),
map<string, int>::value_type(tag_u_District, ENUM_tag_u_District),
map<string, int>::value_type(tag_Industrial_District, ENUM_tag_Industrial_District),
map<string, int>::value_type(tag_i_District, ENUM_tag_i_District),
map<string, int>::value_type(tag_Shopping, ENUM_tag_Shopping),
map<string, int>::value_type(tag_Outskirts, ENUM_tag_Outskirts),
map<string, int>::value_type(tag_Seaport_Area, ENUM_tag_Seaport_Area),
map<string, int>::value_type(tag_Seaport, ENUM_tag_Seaport),
map<string, int>::value_type(tag_Outskirts_amp_Orange_County, ENUM_tag_Outskirts_amp_Orange_County),
map<string, int>::value_type(tag_City_Outskirts, ENUM_tag_City_Outskirts),
map<string, int>::value_type(tag_Arlington, ENUM_tag_Arlington),
map<string, int>::value_type(tag_Hollywood, ENUM_tag_Hollywood),
map<string, int>::value_type(tag_Greater_Hollywood, ENUM_tag_Greater_Hollywood),
map<string, int>::value_type(tag_Manhattan, ENUM_tag_Manhattan),
map<string, int>::value_type(tag_Manhattan_Island, ENUM_tag_Manhattan_Island),
map<string, int>::value_type(tag_Brooklyn_ampersand_Queens, ENUM_tag_Brooklyn_ampersand_Queens),
map<string, int>::value_type(tag_Long_Island, ENUM_tag_Long_Island),
map<string, int>::value_type(tag_The_Bronx, ENUM_tag_The_Bronx)
};
#endif	//LOCATIONSPOOL_CPP
#ifdef	LOG_CPP
// log.cpp

const string CONST_LAST_MESSAGE = "last message";

#endif	//LOG_CPP
#ifdef	LOOTTYPE_CPP
// loottype.cpp

const string CONST_CLOTH = "::cloth: ";
const string CONST_INVALID_BOOLEAN_VALUE_FOR_LOOT_TYPE = "Invalid boolean value for loot type ";
const string CONST_NO_QUICK_FENCING = "::no_quick_fencing: ";
const string CONST_STACKABLE = "::stackable: ";

const string tag_cloth = "cloth";
const string tag_no = "no";
const string tag_no_quick_fencing = "no_quick_fencing";
const string tag_stackable = "stackable";
#endif	//LOOTTYPE_CPP
#ifdef	LOOTTYPEPOOL_CPP
// lootTypePool.cpp

const string CONST_LOOT = "loot";
#endif	//LOOTTYPEPOOL_CPP
#ifdef	MAPSPECIALS_CPP
// mapspecials.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../sitemode/advance.h"
#include "../sitemode/miscactions.h"
#include "../sitemode/sitedisplay.h"
#include "../sitemode/stealth.h"
#include "../items/loottype.h"
#include "../items/loot.h"
#include "../items/money.h"
#include "../log/log.h"
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
// for void addjuice(DeprecatedCreature &cr, long juice, long cap);
#include "../common/translateid.h"
// for  int getloottype(int id);
//#include "../combat/fight.h"
void enemyattack();
#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
char run_broadcast(bool tv_broadcast);
#include "../common/creaturePool.h"
#include "../common/creaturePoolHeader.h"
void setEncounterZeroExistsFalse();
extern bool deagle;
extern bool m249;
extern CCSexposure ccsexposure;
extern char endgamestate;
extern coordinatest loc_coord;
extern DeprecatedCreature encounter[ENCMAX];
extern Deprecatednewsstoryst *sitestory;
extern Deprecatedsquadst *activesquad;
extern int sitecrime;
extern Log gamelog;
extern short lawList[LAWNUM];
extern short mode;
extern short postalarmtimer;
extern short sitealarmtimer;
extern short sitealienate;
extern short sitetype;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];
extern vector<ClipType *> cliptype;
extern vector<WeaponType *> weapontype;
void giveActiveSquadMoney(const int money);
void spawnPresident();

/* Used by load() to create items of the correct class. */

bool isThereASiteAlarm();
void setSiteAlarmOne();

void addCrimeToSiteStory(const int crime);
void giveActiveSquadLoot(const string loot);
void claimSiteStory();
vector<NameAndAlignment> getEncounterNameAndAlignment();
void claimSiteStoryOne();
void juiceActiveSquad(const long juice, const long cap);
void giveActiveSquadThisLoot(Item* de);
/* checks if a creature's weapon is suspicious or illegal */
char weaponcheck(const DeprecatedCreature &cr, bool metaldetect = false);
/* checks if a creature's uniform is appropriate to the location */
char hasdisguise(const DeprecatedCreature &cr);
short getCurrentSite();
void makecreature(const int x, const short type);
void emptyEncounter();
void fillEncounter(CreatureTypes c, int numleft);
#include "../customMaps.h"
#include "../items/lootTypePoolItem.h"
const string itemClassClip = "clip";
const string itemClassWeapon = "weapon";
const string itemClassArmor = "armor";
const string itemClassLoot = "loot";
const string itemClassMoney = "money";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string CONST_GET_THE_FUCK_OUT_OF_HERE = "\"Get the fuck out of here.\"";
const string CONST_GET_THE_HELL_OUT_OF_HERE = "\"Get the hell out of here.\"";
const string CONST_THE_BEST_WAY_NOT_TO_FAIL_IS_TO_SUCCEED = "\"The best way not to fail is to succeed.\"";
const string CONST_GREAT_WORK_IS_DONE_BY_PEOPLE_WHO_DO_GREAT_WORK = "\"Great work is done by people who do great work.\"";

const string CONST_THE_CCS_LEADER_IS_HERE = "The CCS leader is here.";
const string CONST_THE_CCS_LEADER_IS_READY_FOR_YOU = "The CCS leader is ready for you!";
const string CONST_THE_PRESIDENT_IS_IN_THE_OVAL_OFFICE = "The President is in the Oval Office.";
const string CONST_SECRET_SERVICE_AGENTS_AMBUSH_THE_SQUAD = "Secret Service agents ambush the squad!";
const string CONST_THE_PRESIDENT_ISN_T_HERE = "The President isn't here... ";
const string CONST_A_SWAT_TEAM_STORMS_THE_VAULT = "A SWAT team storms the vault!!";
const string CONST_ANOTHER_SWAT_TEAM_MOVES_IN = "Another SWAT team moves in!!";
const string CONST_THE_SQUAD_LOADS_BRICKS_OF_CASH_INTO_A_DUFFEL_BAG = "The squad loads bricks of cash into a duffel bag.";
const string CONST_A_BANK_TELLER_IS_AVAILABLE = "A bank teller is available.";
const string CONST_THE_TELLER_WINDOW_IS_EMPTY = "The teller window is empty.";
const string CONST_THE_SQUAD_HAS_NOBODY_THAT_CAN_DO_THE_JOB = "The squad has nobody that can do the job.";
const string CONST_IS_NO_LONGER_RECOGNIZED = " is no longer recognized.";
const string CONST_AND_WILL_JOIN_THE_ACTIVE_LCS_TO_AVOID_ARREST = "and will join the active LCS to avoid arrest.";
const string CONST_X_OPENS_THE_VAULT_ = " opens the vault, ";
const string CONST_THE_HOSTAGE_IS_FORCED_TO_OPEN_THE_VAULT = "The hostage is forced to open the vault.";
const string CONST_OPENS_THE_VAULT = " opens the vault.";
const string CONST_TO_THE_BANK_S_MANAGERS = "to the bank's managers.";
const string CONST_LAST_IS_THE_BIOMETRIC_LOCK_THAT_KEYED_ONLY = "Last is the biometric lock that keyed only ";
const string CONST_THE_MONEY_WAS_SO_CLOSE_THE_SQUAD_COULD_TASTE_IT = "The money was so close the squad could taste it!";
const string CONST_BE_BYPASSED_BY_A_COMPUTER_EXPERT = "be bypassed by a computer expert.";
const string CONST_NEXT_IS_THE_ELECTRONIC_LOCK_THAT_WILL_HAVE = "Next is the electronic lock that will have ";
const string CONST_ON_THE_OTHER_SIDE_OF_THIS_DOOR = "on the other side of this door...";
const string CONST_THE_SQUAD_CAN_ONLY_DREAM_OF_THE_MONEY = "The squad can only dream of the money ";
const string CONST_BE_CRACKED_BY_A_SECURITY_EXPERT = "be cracked by a security expert.";
const string CONST_FIRST_IS_THE_COMBO_LOCK_THAT_WILL_HAVE = "First is the combo lock that will have ";
const string CONST_OPEN_THE_BANK_VAULT_YES_OR_NO = "Open the bank vault? (Yes or No)";
const string CONST_BUT_YOU_LL_STILL_HAVE_TO_CRACK_THE_OTHER_LOCKS = "but you'll still have to crack the other locks.";
const string CONST_CAN_HANDLE_THE_BIOMETRICS = " can handle the biometrics, ";
const string CONST_EXPERT_AND_ONE_OF_THE_BANK_MANAGERS = "expert, and one of the bank managers.";
const string CONST_YOU_WILL_NEED_A_SECURITY_EXPERT_A_COMPUTER = "You will need a security expert, a computer ";
const string CONST_AN_ELECTRONIC_LOCK_AND_A_BIOMETRIC_LOCK = "an electronic lock, and a biometric lock.";
const string CONST_THE_VAULT_DOOR_HAS_THREE_LAYERS_A_COMBO_LOCK = "The vault door has three layers: A combo lock, ";
const string CONST_BEEEP_BEEEP_BEEEP = "-BEEEP- -BEEEP- -BEEEP-";
const string CONST_JESUS_PUT_SOME_CLOTHES_ON = "\"Jesus! Put some clothes on!\"";
const string CONST_THIS_DOOR_IS_GUARDED = "This door is guarded.";
const string CONST_THE_SQUAD_STEPS_INTO_A_METAL_DETECTOR = "The squad steps into a metal detector.";
const string CONST_THE_SQUAD_FLASHES_ID_BADGES = "The squad flashes ID badges.";
const string CONST_THE_SECURITY_CHECKPOINT_IS_ABANDONED = "The security checkpoint is abandoned.";
const string CONST_SMASH_IT_YES_OR_NO = "Smash it? (Yes or No)";
const string CONST_YOU_SEE_A_DISPLAY_CASE = "You see a display case.";
const string CONST_START_AN_IMPROMPTU_NEWS_PROGRAM_YES_OR_NO = "Start an impromptu news program? (Yes or No)";
const string CONST_YOU_VE_FOUND_A_CABLE_NEWS_BROADCASTING_STUDIO = "You've found a Cable News broadcasting studio.";
const string CONST_TAKE_OVER_THE_STUDIO_YES_OR_NO = " Take over the studio? (Yes or No)";
const string CONST_THEIR_RUSH_TO_GET_OUT = "their rush to get out.";
const string CONST_THE_CABLE_NEWS_BROADCASTERS_LEFT_THE_EQUIPMENT_ON_IN = "The Cable News broadcasters left the equipment on in";
const string CONST_INTERRUPT_THIS_EVENING_S_PROGRAMMING_YES_OR_NO = "Interrupt this evening's programming? (Yes or No)";
const string CONST_YOU_VE_FOUND_A_RADIO_BROADCASTING_ROOM = "You've found a radio broadcasting room.";
const string CONST_THE_RADIO_BROADCASTERS_LEFT_THE_EQUIPMENT_ON_IN = "The radio broadcasters left the equipment on in ";
const string CONST_THE_SQUAD_HAS_FOUND_SOME_VERY_INTERESTING_FILES = "The Squad has found some very interesting files.";
const string CONST_OPEN_IT_YES_OR_NO = "Open it? (Yes or No)";
const string CONST_YOU_VE_FOUND_A_SAFE = "You've found a safe.";
const string CONST_GUARDS_ARE_EVERYWHERE = "Guards are everywhere!";
const string CONST_IT_S_A_TRAP_THE_ARMORY_IS_EMPTY = "It's a trap!  The armory is empty.";
const string CONST_THE_SQUAD_FINDS_SOME_BODY_ARMOR = "The squad finds some body armor.";
const string CONST_THE_SQUAD_FINDS_SOME_M4_CARBINES = "The squad finds some M4 Carbines.";
const string CONST_THE_SQUAD_FINDS_SOME_M16_ASSAULT_RIFLES = "The squad finds some M16 Assault Rifles.";
const string CONST_JACKPOT_THE_SQUAD_FOUND_A_M249_MACHINE_GUN = "Jackpot! The squad found a M249 Machine Gun!";
const string CONST_ALARMS_GO_OFF = "Alarms go off!";
const string CONST_BREAK_IN_YES_OR_NO = "Break in? (Yes or No)";
const string CONST_YOU_VE_FOUND_THE_ARMORY = "You've found the armory.";
const string CONST_WOW_IT_S_EMPTY_THAT_SUCKS = "Wow, it's empty.  That sucks.";
const string CONST_THESE_DOCUMENTS_SHOW_SERIOUS_TAX_EVASION = "These documents show serious tax evasion.";
const string CONST_THE_SQUAD_WILL_TAKE_THOSE = "The squad will take those.";
const string CONST_WOW_GET_A_LOAD_OF_THESE_LOVE_LETTERS = "Wow, get a load of these love letters. ";
const string CONST_THERE_ARE_SOME_DRUGS_HERE = "There are some drugs here.";
const string CONST_THERE_ARE_SOME_VERY_COMPROMISING_PHOTOS_HERE = "There are some... very compromising photos here.";
const string CONST_THE_SQUAD_LIBERATES_SOME_EXPENSIVE_JEWELERY = "The squad Liberates some expensive jewelery.";
const string CONST_THIS_GUY_SURE_HAD_A_LOT_OF_100_BILLS = "This guy sure had a lot of $100 bills.";
const string CONST_THE_SQUAD_HAS_FOUND_A_DESERT_EAGLE = "The squad has found a Desert Eagle.";
const string CONST_DESTROY_IT_YES_OR_NO = "Destroy it? (Yes or No)";
const string CONST_YOU_SEE_SOME_INDUSTRIAL_EQUIPMENT = "You see some industrial equipment.";
const string CONST_YOU_SEE_SOME_TEXTILE_EQUIPMENT = "You see some textile equipment.";
const string CONST_THE_SQUAD_SPRAYS_LIBERAL_GRAFFITI = "The squad sprays Liberal Graffiti!";
const string CONST_INCLUDING_A_LIST_OF_GOVERNMENT_BACKERS_OF_THE_CCS = "including a list of government backers of the CCS.";
const string CONST_mapspecials082 = ",";
const string CONST_THE_SQUAD_OBTAINS_SENSITIVE_INFORMATION = "The Squad obtains sensitive information";
const string CONST_HACK_IT_YES_OR_NO = "Hack it? (Yes or No)";
const string CONST_YOU_VE_FOUND_THE_INTELLIGENCE_SUPERCOMPUTER = "You've found the Intelligence Supercomputer.";
const string CONST_COMPUTER_TO_SHUT_DOWN = "computer to shut down.";
const string CONST_THE_SECURITY_ALERT_HAS_CAUSED_THE = "The security alert has caused the ";
const string CONST_FREE_THE_PRISONERS_YES_OR_NO = "Free the prisoners? (Yes or No)";
const string CONST_PRISON_CONTROL_ROOM = "prison control room.";
const string CONST_HIGH_SECURITY = "high security ";
const string CONST_MEDIUM_SECURITY = "medium security ";
const string CONST_LOW_SECURITY = "low security ";
const string CONST_YOU_VE_FOUND_THE = "You've found the ";
const string CONST_WASN_T_QUITE_CONVINCING = " wasn't quite convincing...";
const string CONST_WASN_T_REALLY_WRONG_HERE = " wasn't really wrong here.";
const string CONST_CONCLUDES_THAT = "concludes that ";
const string CONST_WORKS_THE_ROOM_LIKE_IN_TWELVE_ANGRY_MEN_AND_THE_JURY = " works the room like in Twelve Angry Men, and the jury ";
const string CONST_ATTEMPT_TO_INFLUENCE_THEM_YES_OR_NO = "Attempt to influence them? (Yes or No)";
const string CONST_YOU_VE_FOUND_A_JURY_IN_DELIBERATIONS = "You've found a Jury in deliberations!";
const string CONST_VACATED_IN_A_HURRY = "vacated in a hurry.";
const string CONST_IT_APPEARS_AS_IF_THIS_ROOM_HAS_BEEN = "It appears as if this room has been ";
const string CONST_FREE_THEM_YES_OR_NO = "Free them? (Yes or No)";
const string CONST_YOU_SEE_PRISONERS_IN_THE_COURTHOUSE_JAIL = "You see prisoners in the Courthouse jail.";
const string CONST_YOU_SEE_PRISONERS_IN_THE_DETENTION_ROOM = "You see prisoners in the detention room.";
const string CONST_UH_MAYBE_THAT_IDEA_WAS_CONSERVATIVE_IN_RETROSPECT = "Uh, maybe that idea was Conservative in retrospect...";
const string CONST_YOU_SEE_HORRIBLE_MISSHAPEN_CREATURES_IN_A_SEALED_CAGE = "You see horrible misshapen creatures in a sealed cage.";
const string CONST_THE_SQUAD_RESIGNS_TO_JUST_LEAVING_A_THREATENING_NOTE = "the Squad resigns to just leaving a threatening note.";
const string CONST_AFTER_SOME_FAILED_ATTEMPTS_AND_A_VERY_LOUD_ALARM = "After some failed attempts, and a very loud alarm, ";
const string CONST_THE_REACTOR_IS_OVERHEATING = "The reactor is overheating!";
const string CONST_X_LITTLE_MORE_WHITESPACE = "                ";
const string CONST_A_DEAFENING_ALARM_SOUNDS = "A deafening alarm sounds!";
const string CONST_THE_NUCLEAR_WASTE_GETS_RELEASED_INTO_THE_STATE_S_WATER_SUPPLY = "The nuclear waste gets released into the state's water supply!";
const string CONST_PRESSES_THE_BIG_RED_BUTTON = " presses the big red button!";
const string CONST_MESS_WITH_THE_REACTOR_SETTINGS_YES_OR_NO = "Mess with the reactor settings? (Yes or No)";
const string CONST_YOU_SEE_THE_NUCLEAR_POWER_PLANT_CONTROL_ROOM = "You see the nuclear power plant control room.";
const string CONST_ATTEMPT_TO_RELEASE_NUCLEAR_WASTE_YES_OR_NO = "Attempt to release nuclear waste? (Yes or No)";
const string CONST_YOU_SEE_THE_NUCLEAR_WASTE_CENTER_CONTROL_ROOM = "You see the nuclear waste center control room.";
const string CONST_EMPLOYEES_ONLY = "Employees Only";
const string CONST_ON_THE_LEFT = "on the left.";
const string CONST_THE_LANDLORD_S_OFFICE_IS_THE_FIRST_DOOR = "The landlord's office is the first door";
const string CONST_THE_MUSEUM_DISPLAYS_IN_THE_GIFT_SHOP = "the museum displays in the gift shop.";
const string CONST_WELCOME_TO_THE_NPP_NUCLEAR_PLANT_PLEASE_ENJOY = "Welcome to the NPP Nuclear Plant. Please enjoy";
const string CONST_YOU_SEE_FLUFFY_WHITE_RABBITS_IN_A_LOCKED_CAGE = "You see fluffy white rabbits in a locked cage.";
const string CONST_GET_THE_HECK_OUT_OF_HERE = "\"Get the [heck] out of here.\"";
const string CONST_THE_BOUNCER_ASSESSES_YOUR_SQUAD = "The bouncer assesses your squad.";
const string CONST_THE_CONSERVATIVE_SCUM_BLOCK_THE_DOOR = "The Conservative scum block the door.";
const string CONST_SMIRKS_AND_LETS_THE_SQUAD_IN = " smirks and lets the squad in.";
const string CONST_CASENOT_REJECTED_TXT = "caseNOT_REJECTED.txt";
const string CONST_CASEREJECTED_WEAPONS_TXT = "caseREJECTED_WEAPONS.txt";
const string CONST_CASEREJECTED_NUDE_TXT = "caseREJECTED_NUDE.txt";
const string CONST_RANDOMCRIME_TXT = "randomCrime.txt";
const string CONST_NOTREJECTED_TXT = "notRejected.txt";
const string CONST_REJECTEDBECAUSESMELLFUNNY_TXT = "rejectedBecauseSmellFunny.txt";
const string CONST_X_BLANK_STRING = "";
const string tag_LOOT_CORPFILES = "LOOT_CORPFILES";
const string tag_LOOT = "LOOT";
const string tag_ARMOR_CIVILLIANARMOR = "ARMOR_CIVILLIANARMOR";
const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_ARMYARMOR = "ARMOR_ARMYARMOR";
const string tag_CLIP = "CLIP";
const string tag_CLIP_ASSAULT = "CLIP_ASSAULT";
const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_CARBINE_M4 = "WEAPON_CARBINE_M4";
const string tag_WEAPON_AUTORIFLE_M16 = "WEAPON_AUTORIFLE_M16";
const string tag_CLIP_DRUM = "CLIP_DRUM";
const string tag_WEAPON_M249_MACHINEGUN = "WEAPON_M249_MACHINEGUN";
const string tag_LOOT_CEOTAXPAPERS = "LOOT_CEOTAXPAPERS";
const string tag_LOOT_CEOLOVELETTERS = "LOOT_CEOLOVELETTERS";
const string tag_LOOT_CEOPHOTOS = "LOOT_CEOPHOTOS";
const string tag_LOOT_EXPENSIVEJEWELERY = "LOOT_EXPENSIVEJEWELERY";
const string tag_CLIP_50AE = "CLIP_50AE";
const string tag_WEAPON_DESERT_EAGLE = "WEAPON_DESERT_EAGLE";
const string tag_LOOT_INTHQDISK = "LOOT_INTHQDISK";
const string tag_LOOT_CCS_BACKERLIST = "LOOT_CCS_BACKERLIST";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
#endif	//MAPSPECIALS_CPP
#ifdef	MISC_CPP
// misc.cpp

#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../common/interval.h"
#include "../log/log.h"
#include "../cursesAlternative.h"
#include "../creature/creatureEnums.h"
#include "../customMaps.h"
#include "../common/musicClass.h"

/* pick a descriptor acronym */
vector<string> sexdescAcronym;
/* what kind of person? */
vector<string> sexwhoAcronym;
/* seeking acronym */
vector<string> sexseekAcronym;
/* what type of sex? */
vector<string> sextypeAcronym;
map<short, string> musicList;
extern char artdir[MAX_PATH_SIZE];
extern char endgamestate;
extern char newscherrybusted;
extern int month;
extern int year;
extern Log gamelog;
extern map<short, map<short, string> > getLawFlagStringFull;
extern map<short, string> getLawFlagString;
extern map<short, string> getLawString;
extern MusicClass music;
extern short exec[EXECNUM];
extern short interface_pgup;
extern short lawList[LAWNUM];
extern short presparty;
extern short public_interest[VIEWNUM];
extern vector<string> AMorPM;
extern vector<string> animal_research_country;
extern vector<string> archconservative_last_names;
extern vector<string> book_title_2;
extern vector<string> book_title;
extern vector<string> break_in_murder_case;
extern vector<string> bribe_officers;
extern vector<string> brother_sister;
extern vector<string> bullshit_no_free_speech;
extern vector<string> bullshit;
extern vector<string> chimp_drug_horror;
extern vector<string> chimp_drug_impact;
extern vector<string> city_names;
extern vector<string> cling_to_business_one_line;
extern vector<string> cling_to_religion_one_line;
extern vector<string> cling_to_science_one_line;
extern vector<string> clinging_one_line;
extern vector<string> conservative_oppose_book;
extern vector<string> crazy_conservative_act;
extern vector<string> develops_hatred_one_line;
extern vector<string> distrust_liberals;
extern vector<string> drug_name_2;
extern vector<string> drug_name;
extern vector<string> evidence_of_child_murder;
extern vector<string> family_values_company_name_2;
extern vector<string> family_values_company_name_3;
extern vector<string> family_values_company_name;
extern vector<string> female_first_names;
extern vector<string> fm_radio_name_2;
extern vector<string> fm_radio_name;
extern vector<string> gender_neutral_first_names;
extern vector<string> gene_corp_name_2;
extern vector<string> gene_corp_name;
extern vector<string> gene_product_benefit;
extern vector<string> gene_product_cost;
extern vector<string> gene_product_name_2;
extern vector<string> gene_product_name;
extern vector<string> great_white_male_patriarch_first_names;
extern vector<string> his_her;
extern vector<string> i_like_polution;
extern vector<string> interrogater_shows_compassion_one_line;
extern vector<string> judge_with_prostitute_full_free_speech;
extern vector<string> judge_with_prostitute_no_free_speech;
extern vector<string> judge_with_prostitute;
extern vector<string> liberalCrime;
extern vector<string> male_first_names;
extern vector<string> mutilated_corpse;
extern vector<string> my_idol;
extern vector<string> older_younger;
extern vector<string> petty_violence;
extern vector<string> pollution_consumption_2;
extern vector<string> pollution_consumption;
extern vector<string> prays_on_drugs;
extern vector<string> prays;
extern vector<string> prison_book_title_2;
extern vector<string> prison_book_title;
extern vector<string> public_place;
extern vector<string> radio_host_crazy_quote;
extern vector<string> radio_host_lost_mind;
extern vector<string> radio_name_2;
extern vector<string> radio_name;
extern vector<string> random_nationality;
extern vector<string> regular_last_names;
extern vector<string> smarter_than_you_one_line;
extern vector<string> tech_giant_name_2;
extern vector<string> tech_giant_name;
extern vector<string> terrorist_group;
extern vector<string> terrorist_plot_no_free_speech;
extern vector<string> terrorist_plot;
extern vector<string> vigilante_murder;
extern vector<string> why_chase_ended;
extern vector<vector<string> > bad_trip;
extern vector<vector<string> > cling_to_business;
extern vector<vector<string> > cling_to_interrogater;
extern vector<vector<string> > cling_to_religion;
extern vector<vector<string> > cling_to_science;
extern vector<vector<string> > develops_hatred;
extern vector<vector<string> > fall_in_love;
extern vector<vector<string> > interrogater_shows_compassion;
extern vector<vector<string> > smarter_than_you;

#include "locations/locationsEnums.h"
const vector<string> numberTimesHit =
{
	"",
	" twice",
	" three",
	" four",
	" five",
};

void generate_name(char *first, char *last, char gender);
void firstname(char *str, char gender);
string lastname(bool archconservative);

vector<int> maleOrFemale = {
	GENDER_MALE,
	GENDER_FEMALE
};
/* fills a string with a proper name */
void generate_name(char *str, char gender = GENDER_NEUTRAL);
/* get a first and last name for the same person */
void generate_name(char *first, char *last, char gender = GENDER_NEUTRAL);

string lastname(bool archconservative = false);
const char* statename(int state = -1);
void generate_long_name(char *first, char *middle, char *last, char gender = GENDER_NEUTRAL);

vector<string> two_to_five = {
	"two",
	"three",
	"four",
	"five"
};

const vector<string> vicious_killing_of_guard = {
	"slit the guard's throat with a shank",
	"strangled the guard to death with a knotted bed sheet",
	"chewed out the guard's throat",
	"hit all 36 pressure points of death on the guard",
	"electrocuted the guard with high-voltage wires",
	"thrown the guard out the top-storey window",
	"tricked another guard into shooting the guard dead",
	"burnt the guard to a crisp using a lighter and some gasoline",
	"eaten the guard's liver with some fava beans and a nice chianti",
	"performed deadly experiments on the guard unheard of since Dr. Mengele"
};


const string findingBugs = "Finding bugs";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string CONST_X_PGDN = "PGDN";
const string CONST_X_SINGLE_COLON = ":";
const string CLOSING_BRACKET = "]";
const string DASH_NEXT = " - Next";
const string CONST_X_PGUP = "PGUP";
const string SEMI_COLON = ";";
const string CONST_X_OPEN_BRACKET = "[";
const string DASH_PREVIOUS = " - Previous";
const string PGUP_PGDN = "PGUP/PGDN";
const string SEMI_COLON_AND_COLON = "; and :";
const string OPEN_CLOSE_BRACKET = "[]";
const string TO_VIEW_OTHER_LIBERAL_PAGES = " to view other Liberal pages.";
const string CONST_fight035 = " times";
const string CONST_getnames043 = "Software Bugs";
const string ERROL_DEFAULT_NAME = "Errol";
const string CONST_HER = "her";
const string CONST_HIS = "his";
const string CONST_HURTING_SPREE = "[hurting spree]";
const string CONST_CALLED_THE_POLICE_ON_A_CELLPHONE_AND_THEY_ARRIVED_SHORTLY_THEREAFTER = "called the police on a cellphone and they arrived shortly thereafter. ";
const string CONST_VERSES_OF_THE_BIBLE_AT_THE_STUNNED_ONLOOKERS_SOMEONE = "verses of the Bible at the stunned onlookers. Someone ";
const string CONST_REMAINED_AT_THE_SCENE_AFTER_THE_SHOOTING_SCREAMING = " remained at the scene after the shooting, screaming ";
const string CONST_WITNESSES_REPORT_THAT = " Witnesses report that ";
const string CONST_IS_IN_CUSTODY_R = ", is in custody.&r";
const string CONST_DR = "Dr. ";
const string CONST_CLINIC_YESTERDAY = " Clinic yesterday. ";
const string CONST_GUNNED_DOWN_OUTSIDE_OF_THE = "gunned down outside of the ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ABORTIONS_WAS_RUTHLESSLY = "A doctor that routinely performed abortions was ruthlessly ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_SEMI_LEGAL_ABORTIONS_WAS_RUTHLESSLY = "A doctor that routinely performed semi-legal abortions was ruthlessly ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ILLEGAL_ABORTIONS_WAS_RUTHLESSLY = "A doctor that routinely performed illegal abortions was ruthlessly ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ILLEGAL_ABORTION_MURDERS_WAS_RUTHLESSLY = "A doctor that routinely performed illegal abortion-murders was ruthlessly ";

const string CONST_HAD_BEEN_COMPLETED_R = "had been completed.&r";
const string CONST_SURRENDERED_WITHOUT_A_STRUGGLE_REPORTEDLY_SAYING_THAT_GOD_S_WORK = " surrendered without a struggle, reportedly saying that God's work ";
const string CONST_ABORTION_DOCTORS_AS_OPPOSED_TO_ARRESTING_THEM_R = " abortion doctors as opposed to arresting them.&r";
const string CONST_LATER_ADMITTED_TO_BEING_A_ROGUE_FBI_VIGILANTE_HUNTING_DOWN = " later admitted to being a rogue FBI vigilante, hunting down ";

const string CONST_SPACE_AND_SPACE = " and ";
const string CONST_WIFE = "wife";
const string CONST_IS_SURVIVED_BY = " is survived by ";

const string CONST_THE_SUSPECTED_SHOOTER = "The suspected shooter, ";
const string CONST_TIMES_AND_DIED_IMMEDIATELY_IN_THE_PARKING_LOT = " times and died immediately in the parking lot. ";
const string CONST_WAS_HIT = " was hit ";
const string CONST_SHOTS_WERE_FIRED_FROM_A_NEARBY_VEHICLE = "shots were fired from a nearby vehicle. ";
const string CONST_CAR_WHEN_ACCORDING_TO_POLICE_REPORTS = " car when, according to police reports, ";
const string CONST_WAS_WALKING_TO = " was walking to ";

const string CONST_HUSBAND_LOWERCASE = "husband";
const string CONST_CHILDREN_R = " children.&r";

const string CONST_TAKING_SWIPES = "taking swipes";
const string CONST_URINATING_OUT_THE_WINDOW = "urinating out the window";
const string CONST_PISSING_OUT_THE_WINDOW = "pissing out the window";
const string CONST_RELIEVING_THEMSELVES_OUT_THE_WINDOW = "[relieving themselves] out the window";
const string CONST_THROWING_BEER_BOTTLES = "throwing beer bottles";
const string CONST_THROWING_JUICE_BOXES = "throwing [juice boxes]";


const string CONST_A_HOMOSEXUAL_WAS = "a homosexual, was ";
const string CONST_A_KNOWN_HOMOSEXUAL_WAS = "a known homosexual, was ";
const string CONST_A_KNOWN_SEXUAL_DEVIANT_WAS = "a known sexual deviant, was ";

const string CONST_EVEN_THOUGH_BEING_GAY_IS_DEVIANT_AS_WE_ALL_KNOW = ", even though being gay is deviant, as we all know.";
const string CONST_IS_A_KNOWN_FAGGOT = " is a known faggot";
const string CONST_DESPITE_THE_FACT_THAT = ", despite the fact that ";
const string CONST_AGGRAVATED_NATURE_OF_THE_OFFENSE = "aggravated nature of the offense";
const string CONST_PROSECUTE_THIS_CASE_AS_A_HATE_CRIME_DUE_TO_THE = "prosecute this case as a hate crime, due to the ";
const string CONST_AUTHORITIES_HAVE_STATED_THAT_THEY_WILL_VIGOROUSLY = " Authorities have stated that they will vigorously ";
const string CONST_AT_WHICH_POINT_THEY_WERE_TAKEN_INTO_CUSTODY_NOBODY_WAS_SERIOUSLY_INJURED_DURING_THE_INCIDENT = "at which point they were taken into custody. Nobody was seriously injured during the incident.";
const string CONST_THE_CHASE_ENDED_WHEN = "The chase ended when ";
const string CONST_AT_THE_PURSUING_POLICE_CRUISERS = " at the pursuing police cruisers. ";

const string CONST_MURDERERS_SWERVING_WILDLY = "murderers swerving wildly, ";
const string CONST_WITNESSES_OF_THE_FREEWAY_CHASE_DESCRIBED_THE_PICKUP_OF_THE_ALLEGED = " Witnesses of the freeway chase described the pickup of the alleged ";
const string CONST_HAVE_NOT_YET_BEEN_RELEASED = "have not yet been released.";
const string CONST_WERE_APPREHENDED_AFTER_A_HIGH_SPEED_CHASE_THEIR_NAMES = "were apprehended after a high speed chase. Their names ";
const string CONST_A_POLICE_SPOKESPERSON_REPORTED_THAT_FOUR_SUSPECTS = "A police spokesperson reported that four suspects ";
const string CONST_HERE_YESTERDAY = " here yesterday. ";
const string CONST_UNDERSCORE = "_";

const string CONST_QUESTION_MARK = "?";
const string CONST_MAMMA_WHY_DID_THEY_KILL = "Mamma, why did they kill ";
const string CONST_DEAD = " dead?";
const string CONST_MAMMA_IS = "Mamma, is ";
const string CONST_MANY_AREA_CHILDREN_SPONTANEOUSLY_BROKE_INTO_TEARS_ONE_CHILD_WAS = "many area children spontaneously broke into tears. One child was ";
const string CONST_WHEN_THE_DECISION_TO_BAN_THE_BOOK_WAS_ANNOUNCED_YESTERDAY = " When the decision to ban the book was announced yesterday, ";
const string CONST_AS_KEY_EVIDENCE_OF_THE_DARK_NATURE_OF_THE_BOOK = " as key evidence of the dark nature of the book.";
const string CONST_A_CHILD_THAT = "a child that ";
const string CONST_A_CHILD_THAT_SAID_A_MAGIC_SPELL_AT_HER_PARENTS = "a child that said a magic spell at her parents";
const string CONST_A_CHILD_THAT_SWORE_IN_CLASS = "a child that swore in class";
const string CONST_IN_THEIR_COMPLAINT_THE_GROUPS_CITED_AN_INCIDENT_INVOLVING = "In their complaint, the groups cited an incident involving ";
const string CONST_SOME_CONSERVATIVES_FEEL_THAT_THE_BOOKS = "some conservatives feel that the books ";
const string CONST_ALTHOUGH_THE_SERIES_IS_ADORED_BY_CHILDREN_WORLDWIDE = "Although the series is adored by children worldwide, ";
const string CONST_PERIOD_SPACE = ". ";
const string CONST_AUTHOR = " author ";
const string CONST_IS_THE_THIRD_IN_AN_IMMENSELY_POPULAR_SERIES_BY = "_, is the third in an immensely popular series by ";
const string CONST_AND_THE = "_and_the_";
const string CONST_THE_BOOK = " The book, ";
const string CONST_THE_CITY_BOWED_TO_PRESSURE_FROM_RELIGIOUS_GROUPS = "the city bowed to pressure from religious groups.";
const string CONST_A_CHILDREN_S_STORY_HAS_BEEN_REMOVED_FROM_LIBRARIES_HERE_AFTER = " - A children's story has been removed from libraries here after ";

const string CONST_HEARD_SAYING_COMMA_QUOTE = "heard saying, \"";

const string QUOTATION_MARK = "\"";

const string CONST_DOT_SPACE = ". ";
const string CONST_DOT_QUOTATION_MARK = ".\"";

const string CONST_CAN_BE_PUT_TO_DEATH_IN_THIS_COUNTRY = "can be put to death in this country.";
const string CONST_TRAGEDY_IT_WILL_BE_THAT_OUR_NATION_IS_NOW_EVALUATING_THE_EASE_WITH_WHICH_PEOPLE = "tragedy, it will be that our nation is now evaluating the ease with which people ";
const string CONST_AND_MORE_EVENTS_ARE_EXPECTED_THIS_EVENING_IF_THERE_IS_A_BRIGHT_SIDE_TO_BE_FOUND_FROM_THIS = "and more events are expected this evening. If there is a bright side to be found from this ";
const string CONST_CANDLELIGHT_VIGILS_WERE_HELD_THROUGHOUT_THE_COUNTRY_LAST_NIGHT_DURING_THE_EXECUTION = " Candlelight vigils were held throughout the country last night during the execution, ";
const string CONST_THE_FAMILY_WANTS_CLOSURE_WE_DON_T_HAVE_TIME_FOR_ANOTHER_TRIAL = "The family wants closure. We don't have time for another trial";
const string CONST_END_OF_STORY = "End of story";
const string CONST_ASSASSIN_SERIAL_KILLER_EITHER_WAY_GUILTY = "Assassin, serial killer, either way 컴 guilty. ";
const string CONST_THE_CONVICT_IS_ALWAYS_REFERRED_TO_BY_THREE_NAMES = "The convict is always referred to by three names. ";
const string CONST_LET_S_NOT_FORGET_THE_CONVICT_IS_COLORED_YOU_KNOW_HOW_THEIR_KIND_ARE = "Let's not forget the convict is colored. You know how their kind are";
const string CONST_SPOKESPERSON_FOR_THE_GOVERNOR_SAYING = "spokesperson for the governor saying, ";
const string CONST_THE_STATE_STILL_WENT_THROUGH_WITH_THE_EXECUTION_WITH_A = "The state still went through with the execution, with a ";
const string CONST_WAS_FRAMED = " was framed. ";
const string CONST_AN_ADMISSION_FROM_A_FORMER_PROSECUTOR_THAT = "an admission from a former prosecutor that ";
const string CONST_A_BATTERY_OF_NEGATIVE_DNA_TESTS = "a battery of negative DNA tests. ";
const string CONST_A_CONFESSION_FROM_ANOTHER_CONVICT = "a confession from another convict. ";
const string CONST_HAVE_BEEN_PRODUCED_INCLUDING = "have been produced, including ";
const string CONST_SINCE_THEN_NUMEROUS_PIECES_OF_EXCULPATORY_EVIDENCE = "Since then, numerous pieces of exculpatory evidence ";
const string CONST_OF_13_SERIAL_MURDERS = " of 13 serial murders. ";
const string CONST_WAS_CONVICTED_IN = " was convicted in ";
const string CONST_CORRECTIONAL_FACILITY_R = " Correctional Facility.&r";
const string CONST_YESTERDAY_AT_THE = " yesterday at the ";
const string CONST_SINGLE_COLON = ":";
const string CONST_WAS_PRONOUNCED_DEAD_AT = " was pronounced dead at ";
const string CONST_AN_INNOCENT_CITIZEN_HAS_BEEN_PUT_TO_DEATH_IN_THE_ELECTRIC_CHAIR = " - An innocent citizen has been put to death in the electric chair. ";

const string CONST_YOU_THINK_ABOUT_THAT_BEFORE_YOU_CONTINUE_SLANGING_ACCUSATIONS = "You think about that before you continue slanging accusations";
const string CONST_THESE_FILES_DEAL_WITH_THE_ONE_AND_NOT_THE_OTHER = "these files deal with the one and not the other. ";
const string CONST_IT_MIGHT_BE_A_BIT_PRESUMPTIVE_TO_ASSUME_THAT = "It might be a bit presumptive to assume that ";
const string CONST_WELL_YOU_KNOW_THERE_S_PRIVACY_AND_THERE_S_PRIVACY = "Well, you know, there's privacy, and there's privacy. ";
const string CONST_THE_FBI_REFUSED_TO_COMMENT_INITIALLY_BUT_WHEN_CONFRONTED_WITH_THE_INFORMATION = " The FBI refused to comment initially, but when confronted with the information, ";
const string CONST_DEAL_WITH_THE_UNDESIRABLES_ALTHOUGH_THIS_PHRASE_IS_NOT_CLARIFIED = "\"deal with the undesirables\", although this phrase is not clarified. ";
const string CONST_MORE_DISTURBINGLY_THE_FILES_MAKE_REFERENCE_TO_A_PLAN_TO = " More disturbingly, the files make reference to a plan to ";
const string CONST_UNIONS_WORKING_FOR_LIBERAL_ORGANIZATIONS_EVEN = "unions, working for liberal organizations 컴 even ";
const string CONST_THE_FILES_CONTAIN_INFORMATION_ON_WHICH_PEOPLE_HAVE_BEEN_ATTENDING_DEMONSTRATIONS_ORGANIZING = "The files contain information on which people have been attending demonstrations, organizing ";
const string CONST_THIS_NEWSPAPER_YESTERDAY_RECEIVED_A_COLLECTION_OF_FILES_FROM_A_SOURCE_IN_THE_FEDERAL_BUREAU_OF_INVESTIGATIONS = "This newspaper yesterday received a collection of files from a source in the Federal Bureau of Investigations. ";
const string CONST_WASHINGTON_DC_THE_FBI_MIGHT_BE_KEEPING_TABS_ON_YOU = "Washington, DC - The FBI might be keeping tabs on you. ";

const string CONST_A_SPOKESPERSON_STATED_COMMA_QUOTE = "a spokesperson stated, \"";
const string CONST_HAS_RESIGNED_IN_DISGRACE_AFTER_BEING_CAUGHT_WITH_A_PROSTITUTE = " has resigned in disgrace after being caught with a prostitute.";
const string CONST_HAS_RESIGNED_IN_DISGRACE_AFTER_BEING_CAUGHT_WITH_A_CIVIL_SERVANT = " has resigned in disgrace after being caught with a [civil servant].";

const string CONST_THE_JUDGE_WOULD_BE_GOING_ON_A_BIBLE_RETREAT_FOR_A_FEW_WEEKS_TO = "the judge would be going on a Bible retreat for a few weeks to ";
const string CONST_COULD_NOT_BE_REACHED_FOR_COMMENT_ALTHOUGH_AN_AID_STATED_THAT = " could not be reached for comment, although an aid stated that ";
const string CONST_IN_EXCHANGE_FOR_THEIR_SILENCE = " in exchange for their silence.";
const string CONST_REPORTEDLY_OFFERED = " reportedly offered ";
const string CONST_WHEN_POLICE_BROKE_INTO_THE_HOTEL_ROOM_THEY_SAW = "when police broke into the hotel room they saw ";
const string CONST_ACCORDING_TO_SOURCES_FAMILIAR_WITH_THE_PARTICULARS = "According to sources familiar with the particulars, ";
const string CONST_LAST_WEEK_IN_A_HOTEL_DURING_A_POLICE_STING_OPERATION = " last week in a hotel during a police sting operation. ";
const string CONST_WAS_FOUND_WITH = ", was found with ";
const string CONST_WHO_ONCE = ", who once ";
const string CONST_CONSERVATIVE_FEDERAL_JUDGE = " - Conservative federal judge ";


const string CONST_MAKE_THINGS_RIGHT_WITH_THE_ALMIGHTY_FATHER = "\"Make things right with the Almighty Father.\"";
const string CONST_G_DD_MN_MIND = " g*dd*mn mind";
const string CONST_GOSH_DARN_MIND = " [gosh darn] mind";
const string CONST_GODDAMN_MIND = " goddamn mind";
const string CONST_LOST = "lost ";
const string CONST_TO_THE_FM_BAND = "to the FM band.";
const string CONST_PASTURES_OF_THESE_MANY_SAID_THAT_THEY_WOULD_BE_SWITCHING_OVER = "pastures. Of these, many said that they would be switching over ";
const string CONST_HAVE_DECIDED_TO_LEAVE_THE_PROGRAM_FOR_SANER = "have decided to leave the program for saner ";
const string CONST_FULLY_HALF_OF_THE_HOST_S_MOST_LOYAL_SUPPORTERS = "fully half of the host's most loyal supporters ";
const string CONST_ACCORDING_TO_A_POLL_COMPLETED_YESTERDAY = "According to a poll completed yesterday, ";
const string CONST_THE_DAMAGE_MIGHT_ALREADY_BE_DONE = "the damage might already be done. ";
const string CONST_ISSUED_AN_APOLOGY_LATER_IN_THE_PROGRAM_BUT = " issued an apology later in the program, but ";
const string CONST_HAD = " had ";
const string CONST_A_FORMER_FAN_OF_THE_SHOW = "\", a former fan of the show, ";
const string CONST_LIBERAL_MEDIA_ESTABLISHMENT = "liberal media establishment!";
const string CONST_CURRENT_PRESIDENT = "current president!";
const string CONST_AND_THE_GREATEST_LIVING_EXAMPLE_OF_A_REVERSE_RACIST_IS_THE = "and the greatest living example of a reverse racist is the ";
const string CONST_S_MONOLOGUE_FOR_THE_EVENING_BEGAN_THE_WAY_THAT_FANS = "'s monologue for the evening began the way that fans ";
const string CONST_QUOTATION_PERIOD = "\".";
const string CONST_WENT_OFF_FOR_FIFTEEN_MINUTES_IN_AN_INEXPLICABLE_RANT = " went off for fifteen minutes in an inexplicable rant ";
const string CONST_WELL_KNOWN_AM_RADIO_PERSONALITY = " - Well-known AM radio personality ";

const string CONST_TWO_NIGHTS_AGO_DURING_RADIO = "two nights ago during the syndicated radio program \"";
const string CONST_HAD_COME_TO_EXPECT_WITH_ATTACKS_ON_LIBERAL_MEDIA = "had come to expect, with attacks on the \"liberal media establishment\"";
const string CONST_DOT_BUT_WHEN_THE_RADIO_ICON_SAID = "the \"elite liberal agenda\". But when the radio icon said, \"";
const string CONST_COMMA_KNEW_THAT_QUOTE = ", knew that \"";
const string CONST_DOT_AFTER_THAT_IT_GOT_WORSE = ". After that, it just got worse and worse.\"";

const string CONST_UNIVERSITY = "university";
const string CONST_HIGH_SCHOOL = "high school";
const string CONST_MIDDLE_SCHOOL = "middle school";
const string CONST_ELEMENTARY_SCHOOL = "elementary school";
const string CONST_UNIVERSITY_UPPER_CASE = "University";
const string CONST_HIGH_SCHOOL_UPPER_CASE = "High School";
const string CONST_MIDDLE_SCHOOL_UPPER_CASE = "Middle School";
const string CONST_ELEMENTARY_SCHOOL_UPPER_CASE = "Elementary School";
const string CONST_SHOOTING_RAMPAGE = "shooting rampage";
const string CONST_COMMITTED_SUICIDE = " committed suicide";
const string CONST_FEEL_DEEPLY_ASLEEP = " [feel deeply asleep]";
const string CONST_MOW_DOWN = "mow down";
const string CONST_SCARE = "[scare]";

const string CONST_HIM_LOWERCASE = "him";
const string CONST_KILLED = "killed ";

const string CONST_AND_WOUNDED_DOZENS_MORE = " and wounded dozens more. ";
const string CONST_HURT_SOME_PEOPLE = "[hurt some people]. ";
const string CONST_WHEN_THE_POLICE_ARRIVED_THE_STUDENT_HAD_ALREADY = " When the police arrived, the student had already ";
const string CONST_AS_WELL_R = " as well.&r";
const string CONST_SHOT = "shot";
const string CONST_UNFORTUNATELY_HARMED = "[unfortunately harmed]";
const string CONST_THEY_WERE = ", they were ";
const string CONST_WHEN_OTHER_STUDENTS_TRIED_TO_WRESTLE_THE_WEAPONS_AWAY_FROM = "When other students tried to wrestle the weapons away from ";
const string CONST_STUDENTS_AND_TEACHERS_INSIDE = " students and teachers inside. ";
const string CONST_SPRAYING_BULLETS_AT = "spraying bullets at";
const string CONST_SCARING = "[scaring]";

const string CONST_WAS_DISTURBINGLY_OBSESSED_WITH_GUNS_AND_DEATH_R = " was disturbingly obsessed with guns and death.&r";
const string CONST_SHE = "she";
const string CONST_REPORTS_INDICATE_THAT_THE_STUDENT_KEPT_A_JOURNAL_THAT_SHOWED = "reports indicate that the student kept a journal that showed ";
const string CONST_INVESTIGATORS_ARE_CURRENTLY_SEARCHING_THE_STUDENT_S_BELONGINGS_AND_INITIAL = " Investigators are currently searching the student's belongings, and initial ";
const string CONST_SHORTLY_AFTERWARDS_R = " shortly afterwards.&r";
const string CONST_CLASSROOMS = "classrooms, ";
const string CONST_WHILE_CLASSES_WERE_IN_SESSION_THEN_SYSTEMATICALLY_STARTED_BREAKING_INTO = " while classes were in session, then systematically started breaking into ";
const string CONST_UNIVERSITY_LOWERCASE = "university ";
const string CONST_SCHOOL = "school ";
const string CONST_ENTERED_THE = " entered the ";
const string CONST_MORE_THAN_A_DOZEN_CLASSMATES_AND_TWO_TEACHERS_AT = " more than a dozen classmates and two teachers at ";
const string CONST_USED_A_VARIETY_OF_GUNS_TO = ", used a variety of guns to ";
const string CONST_AT_A_LOCAL = " at a local ";
const string CONST_A_STUDENT_HAS_GONE_ON_A = "A student has gone on a ";


const string CONST_HE_LOWERCASE = "he";
const string CONST_BUTTLORD = "Buttlord";
const string CONST_BUMLORD = "[Bum]lord";
const string CONST_AIDS = "AIDS";
const string CONST_GRIDS = "GRIDS";

const string CONST_HELLUVA = "helluva";
const string CONST_DIFFICULT = "[difficult]";
const string CONST_CHOICE_AND_I_WOULD_ONLY_HAVE_A_FEW_SECONDS_BEFORE_THEY_MADE_IT_FOR_ME = " choice, and I would only have a few seconds before they made it for me";
const string CONST_THE_OTHER_A = " the other. A ";
const string CONST_MAYBE_LOSE_AN_EYE_THE_ONE_WAY_MAYBE_CATCH = "Maybe lose an eye the one way, maybe catch ";
const string CONST_MY_SHANK_S_UNDER_THE_MATTRESS_BETTER_TO_BE_BRAVE_AND_FIGHT_OR_CHICKEN_OUT_AND_LET_THEM_TAKE_IT = "My shank's under the mattress. Better to be brave and fight or chicken out and let them take it? ";
const string CONST_WITH_DARK_GLARES_OF_BARE_LUST_AS_FOOTBALL_PLAYERS_MIGHT_STARE_AT_A_STUPEFIED_DRUNKEN_HELPLESS_TEENAGER = "with dark glares of bare lust, as football players might stare at a stupefied, drunken, helpless teenager. ";
const string CONST_I_WAS_TRAPPED_WITH_THEM_NOW_THERE_WERE_THREE_LOOKING_ME_OVER = "I was trapped with them now. There were three, looking me over ";
const string CONST_COMING_TO_A_HALT_WITH_A_DEAFENING_CLANG_THAT_SAID_IT_ALL = "coming to a halt with a deafening clang that said it all 컴 ";
const string CONST_THE_STEEL_BARS_GRATED_FORWARD_IN_THEIR_RAILS = "The steel bars grated forward in their rails, ";
const string CONST_TAKE_THIS_EXCERPT = " Take this excerpt, \"";
const string CONST_UNDERSCORE_DOT_AMPERSAND_R = "_.&r";
const string CONST_S_NEW_TOUR_DE_FORCE = "'s new tour-de-force, _";
const string CONST_HAVE_THESE_WORKS_BEEN_AS_POIGNANT_AS = "have these works been as poignant as ";
const string CONST_PRISON_THEME_LATELY_IN_ITS_OFFERINGS_FOR_MASS_CONSUMPTION_RARELY = "prison theme lately in its offerings for mass consumption, rarely ";
const string CONST_ALTHOUGH_POPULAR_CULTURE_HAS_USED_OR_PERHAPS_OVERUSED_THE = "Although popular culture has used, or perhaps overused, the ";
const string CONST_DETAIL_WHAT_GOES_ON_BEHIND_BARS = "detail what goes on behind bars. ";
const string CONST_A_FORMER_PRISONER_HAS_WRITTEN_A_BOOK_DESCRIBING_IN_HORRIFYING = " - A former prisoner has written a book describing in horrifying ";
const string CONST_HERE_REPORT_THAT_THEY_HAVE_DISCOVERED_AN_AMAZING_NEW_WONDER_DRUG = "here report that they have discovered an amazing new wonder drug. ";
const string CONST_REPORT_THAT_THEY_HAVE_DISCOVERED_AN_AMAZING_NEW_WONDER_DRUG = " report that they have discovered an amazing new wonder drug. ";
const string CONST_FROM = "from ";
const string CONST_ANAL = "Anal";
const string CONST_BUM_BUM = "Bum-Bum";
const string CONST_CORRECTS_ERECTILE_DYSFUNCTION_IN_CHIMPANZEES = "corrects erectile dysfunction in chimpanzees";
const string CONST_HELPS_CHIMPANZEES_REPRODUCE = "[helps chimpanzees reproduce]";


const string CONST_THE_FIRST_PHASE_OF_HUMAN_TRIALS_IS_SLATED_TO_BEGIN_IN_A_FEW_MONTHS = " The first phase of human trials is slated to begin in a few months.";
const string CONST_I_THINK_THE_MEDIA_SHOULD_BE_FOCUSING_ON_THE_ENORMOUS_BENEFITS_OF_THIS_DRUG = "I think the media should be focusing on the enormous benefits of this drug.";
const string CONST_WHILE_WE_UNDERSTAND_YOUR_CONCERNS_ANY_WORRIES_ARE_ENTIRELY_UNFOUNDED = "While we understand your concerns, any worries are entirely unfounded. ";
const string CONST_WE_HAVE_A_VERY_EXPERIENCED_RESEARCH_TEAM = ". We have a very experienced research team. ";
const string CONST_A_SPOKESPERSON_FOR_THE_RESEARCH_TEAM_STATED_THAT_IT_REALLY_ISN_T_SO_BAD_AS_ALL_THAT_CHIMPANZEES_ARE_VERY_RESILIENT_CREATURES = "a spokesperson for the research team stated that, \"It really isn't so bad as all that. Chimpanzees are very resilient creatures. ";
const string CONST_FIELDING_QUESTIONS_ABOUT_THE_ETHICS_OF_THEIR_EXPERIMENTS_FROM_REPORTERS_DURING_A_PRESS_CONFERENCE_YESTERDAY = "Fielding questions about the ethics of their experiments from reporters during a press conference yesterday, ";
const string CONST_ALONG_WITH_BONOBOS_CHIMPANZEES_ARE_OUR_CLOSEST_COUSINS = " Along with bonobos, chimpanzees are our closest cousins";
const string CONST_THE_DRUG_APPARENTLY = ", the drug apparently ";
const string CONST_CALLED = "Called ";
const string CONST_RESEARCHERS = " - Researchers ";

const string CONST_NEEDS_TO_TAKE_A_BREATHER_ON_THIS_ONE_WE_DON_T_SEE_WHY_THERE_S_SUCH_A_RUSH_TO_JUDGMENT_HERE = "needs to take a breather on this one. We don't see why there's such a rush to judgment here. ";
const string CONST_BEFORE_WE_URGE_ANY_ACTION_SOCIETY_REALLY_JUST = "before we urge any action. Society really just ";
const string CONST_THERE_S_WORK_LEFT_TO_BE_DONE_WE_SHOULD_STUDY_MUCH_MORE = "there's work left to be done. We should study much more ";
const string CONST_WHY_IS_THERE_CONTENTION_ON_THE_POLLUTION_QUESTION_IT_S_BECAUSE = "Why is there contention on the pollution question? It's because ";
const string CONST_ALL_WE_VE_DONE_IS_INTRODUCED_A_LITTLE_CLARITY_INTO_THE_ONGOING_DEBATE = "All we've done is introduced a little clarity into the ongoing debate. ";
const string CONST_THESE_ISSUES_TO_THEIR_OWN_ADVANTAGE = " these issues to their own advantage. ";
const string CONST_YOU_HAVE_TO_REALIZE_THAT = ". You have to realize that ";
const string CONST_A_SPOKESPERSON_STATED_THAT = "a spokesperson stated that, \"";
const string CONST_WHEN_QUESTIONED_ABOUT_THE_SCIENCE_BEHIND_THESE_RESULTS = " When questioned about the science behind these results, ";
const string CONST_MIGHT_ACTUALLY = " might actually ";
const string CONST_AMONG_THE_MOST_STARTLING_OF_THE_THINK_TANK_S_FINDINGS_IS_THAT = "Among the most startling of the think tank's findings is that ";
const string CONST_AND_THE_LATEST_SCIENCE_ON_THE_ISSUE = "and the latest science on the issue. ";
const string CONST_RECENTLY_RELEASED_A_WIDE_RANGING_REPORT_DETAILING_RECENT_TRENDS = " recently released a wide-ranging report detailing recent trends ";
const string CONST_POLLUTION_MIGHT_NOT_BE_SO_BAD_AFTER_ALL_THE = " - Pollution might not be so bad after all. The ";

const string CONST_OF_THE_TECH_INDUSTRY_BUT_IS_ALSO_INDICATIVE_OF_A_FULL_ECONOMIC_RECOVER_R = "of the tech industry but is also indicative of a full economic recover.&r";
const string CONST_ANALYSTS_SUGGEST_THAT_NOT_ONLY_DOES_THE_EXPANSION_SPEAK_TO_THE_HEALTH = "analysts suggest that not only does the expansion speak to the health ";
const string CONST_FUTURES_OF_SOME_OF_THE_COMPANIES_IN_THE_TECH_SECTOR_ON_THE_WHOLE_HOWEVER = "futures of some of the companies in the tech sector. On the whole, however, ";
const string CONST_ALTHOUGH_THE_DAMPENED_MOVEMENT_MIGHT_BE_EXPECTED_DUE_TO_THE_UNCERTAIN = "although the dampened movement might be expected due to the uncertain ";
const string CONST_THE_MARKETS_REPORTEDLY_RESPONDED_TO_THE_ANNOUNCEMENT_WITH_MILD_INTEREST = "The markets reportedly responded to the announcement with mild interest, ";
const string CONST_THIS_WELCOME_NEWS_IS_BOUND_TO_BE_A_PLEASANT_SURPRISE_TO_THOSE_IN_THE_UNEMPLOYMENT_LINES = "this welcome news is bound to be a pleasant surprise to those in the unemployment lines. ";
const string CONST_OF_LARGE_CORPORATIONS_TO_EXPORT_JOBS_OVERSEAS_THESE_DAYS = "of large corporations to export jobs overseas these days, ";
const string CONST_LIGHT_OF_THE_TENDENCY = "light of the tendency ";
const string CONST_GIVEN_THE_STATE_OF_THE_ECONOMY_RECENTLY_AND_IN = "Given the state of the economy recently and in ";
const string CONST_INCREASING_ITS_PAYROLLS_BY_OVER_TEN_THOUSAND_WORKERS_ALONE = " increasing its payrolls by over ten thousand workers alone. ";
const string CONST_TECH_GIANT = "tech giant ";
const string CONST_ARE_EXPECTED_IN_THE_FIRST_MONTH_WITH = "are expected in the first month, with ";
const string CONST_DURING_THE_NEXT_QUARTER_OVER_THIRTY_THOUSAND_JOBS = "during the next quarter. Over thirty thousand jobs ";
const string CONST_WILL_BE_EXPANDING_THEIR_WORK_FORCES_CONSIDERABLY = "will be expanding their work forces considerably ";
const string CONST_AT_A_JOINT_NEWS_CONFERENCE_HERE_THAT_THEY = "at a joint news conference here that they ";
const string CONST_SEVERAL_MAJOR_COMPANIES_HAVE_ANNOUNCED = " - Several major companies have announced ";

const string CONST_THIS_AMAZING_NEW_PRODUCT_ACTUALLY = "this amazing new product actually ";
const string CONST_ACCORDING_TO_THE_PUBLIC_RELATIONS_REPRESENTATIVE_SPEAKING = "According to the public relations representative speaking, ";
const string CONST_DURING_AN_AFTERNOON_POWERPOINT_PRESENTATION = "\", during an afternoon PowerPoint presentation. ";
const string CONST_PRESENTED_THEIR_PRODUCT = ", presented their product, \"";

const string CONST_BUT_THE_GM_INDUSTRY_OPERATES_AT_A_HIGHER_ETHICAL_STANDARD_THAT_GOES_WITHOUT_SAYING = "but the GM industry operates at a higher ethical standard. That goes without saying.";
const string CONST_NO_THAT_S_JUST_RIDICULOUS_I_MEAN_SURE_COMPANIES_HAVE_PUT_UNSAFE_PRODUCTS_OUT = "No. That's just ridiculous. I mean, sure companies have put unsafe products out, ";
const string CONST_WOULD_WE_STAKE_THE_REPUTATION_OF_OUR_COMPANY_ON_UNSAFE_PRODUCTS = ". Would we stake the reputation of our company on unsafe products? ";
const string CONST_IS_JUST_A_LOAD_OF = " is just a load of ";
const string CONST_LOOK_THESE_PRODUCTS_ARE_SAFE_THAT_THING_ABOUT_THE = "Look, these products are safe. That thing about the ";
const string CONST_ONE_IN_PARTICULAR_SAID = "One in particular said, \"";
const string CONST_IN_THEIR_DISMISSAL_OF_THE_CRITICISM_WHICH_OFTEN_FOLLOWS_THE_INDUSTRY = "in their dismissal of the criticism which often follows the industry. ";
const string CONST_SPOKESPEOPLE_FOR_THE_GM_CORPORATIONS_WERE_UNIVERSAL = " Spokespeople for the GM corporations were universal ";
const string CONST_ONE_SUCH_CORPORATION = " One such corporation, ";
const string CONST_BOOTHS_AND_GAVE_TALKS_TO_WIDE_EYED_ONLOOKERS = "booths and gave talks to wide-eyed onlookers.";
const string CONST_TO_SHOWCASE_ITS_UPCOMING_PRODUCTS_OVER_THIRTY_COMPANIES_SET_UP = "to showcase its upcoming products. Over thirty companies set up ";
const string CONST_THE_GENETIC_FOODS_INDUSTRY_STAGED_A_MAJOR_EVENT_HERE_YESTERDAY = " - The genetic foods industry staged a major event here yesterday ";

const string CONST_DEAD_AND = " dead and ";
const string CONST_IN_A_BETTER_PLACE = " [in a better place]";
const string CONST_THE_DEATH_PENALTY_IN_THIS_CASE = "the death penalty in this case.";
const string CONST_LIFE_IMPRISONMENT_IN_THIS_CASE = "life imprisonment in this case.";
const string CONST_SEEKING = "seeking ";
const string CONST_THE_DISTRICT_ATTORNEY_S_OFFICE_HAS_ALREADY_REPEATEDLY_SAID_IT_WILL_BE = " The district attorney's office has already repeatedly said it will be ";
const string CONST_SOURCES_SAY_THAT_THE_POLICE_GOT_A_BREAK_IN_THE_CASE_WHEN = ". Sources say that the police got a break in the case when ";
const string CONST_ONLY_TO_TURN_UP_LATER = "only to turn up later";
const string CONST_OVER_TWENTY_CHILDREN_IN_THE_PAST_TWO_YEARS_HAVE_GONE_MISSING = ". Over twenty children in the past two years have gone missing, ";
const string CONST_WAS_DETAINED_YESTERDAY_AFTERNOON_REPORTEDLY_IN_POSSESSION_OF = " was detained yesterday afternoon, reportedly in possession of ";
const string CONST_ACCORDING_TO_A_SPOKESPERSON_FOR_THE_POLICE_DEPARTMENT_HERE = "according to a spokesperson for the police department here. ";
const string CONST_STRING_OF_BRUTAL_CHILD_KILLINGS_THAT_HAS_KEPT_EVERYONE_IN_THE_AREA_ON_EDGE = "string of brutal child killings that has kept everyone in the area on edge, ";
const string CONST_THE_AUTHORITIES_HAVE_APPREHENDED_THEIR_PRIMARY_SUSPECT_IN_THE = "The authorities have apprehended their primary suspect in the ";
const string CONST_PERHAPS_PARENTS_CAN_REST_EASIER_TONIGHT = " - Perhaps parents can rest easier tonight. ";
const string CONST_SPACE_THE_SPOKESMAN_FURTHER_STATED = " The spokesperson further stated, \"";
const string CONST_THIS_NEW_AGE = "this new age.";
const string CONST_FOR_WHAT_WE_FEEL_ARE_THE_ESSENTIAL_TOOLS_FOR_COMBATING_TERRORISM_IN = "for what we feel are the essential tools for combating terrorism in ";
const string CONST_THE_HEAD_OF_THE_AGENCY_WILL_BE_SENDING_A_REQUEST_TO_CONGRESS = "The Head of the Agency will be sending a request to Congress ";
const string CONST_HOWEVER_LET_ME_ALSO_SAY_THAT_THERE_S_MORE_THAT_NEEDS_TO_BE_DONE = "However, let me also say that there's more that needs to be done. ";
const string CONST_CIVILIZATION_BEFORE_THEY_CAN_DESTROY_AMERICAN_FAMILIES = "civilization before they can destroy American families. ";
const string CONST_PROVIDING_US_WITH_THE_TOOLS_WE_NEED_TO_NEUTRALIZE_THESE_ENEMIES_OF = "providing us with the tools we need to neutralize these enemies of ";
const string CONST_THAT_WE_ARE_GRATEFUL_TO_THE_CONGRESS_AND_THIS_ADMINISTRATION_FOR = "that we are grateful to the Congress and this Administration for ";
const string CONST_I_WON_T_COMPROMISE_OUR_SOURCES_AND_METHODS_BUT_LET_ME_JUST_SAY = "I won't compromise our sources and methods, but let me just say ";
const string CONST_WAS_TO_OCCUR = "was to occur.";
const string CONST_TERRORIST_ORGANIZATION_ALLOWED_THE_PLOT_TO_BE_FOILED_JUST_DAYS_BEFORE_IT = "terrorist organization allowed the plot to be foiled just days before it ";
const string CONST_HOWEVER_INTELLIGENCE_GARNERED_FROM_DEEP_WITHIN_THE_MYSTERIOUS = ". However, intelligence garnered from deep within the mysterious ";
const string CONST_PLANNED_TO = " planned to ";
const string CONST_ACCORDING_TO_A_SPOKESPERSON_FOR_THE_AGENCY = " According to a spokesperson for the agency, ";
const string CONST_WOULD_HAVE_OCCURRED_ON_AMERICAN_SOIL = "would have occurred on American soil.";
const string CONST_WASHINGTON_DC_THE_CIA_ANNOUNCED_YESTERDAY_THAT_IT_HAS_AVERTED_A_TERROR_ATTACK_THAT = "Washington, DC - The CIA announced yesterday that it has averted a terror attack that ";

const string CONST_CONSULTATIONS_WITH_A_MAGIC_8_BALL = " consultations with a Magic 8-Ball";
const string CONST_FAMILY = " family";
const string CONST_CLOSE_PERSONAL_FRIENDSHIP_WITH_THE = " close personal friendship with the ";
const string CONST_PERSONAL_PHILOSOPHY_OF_LIBERTY = " personal philosophy of liberty";
const string CONST_DESERVED_ANOTHER_CHANCE = " deserved another chance";
const string CONST_BELIEF_THAT = " belief that ";
const string CONST_BELIEF_THAT_THE_CRIMES_WERE_A_VAST_RIGHT_WING_CONSPIRACY = " belief that the crimes were a vast right-wing conspiracy";
const string CONST_GENERAL_FEELING_ABOUT_POLICE_CORRUPTION = " general feeling about police corruption";
const string CONST_TEN_YEAR_OLD_EYEWITNESS_TESTIMONY = "ten-year-old eyewitness testimony";
const string CONST_I_WOULD_KILL_AGAIN = "If I were to be released, I would surely kill again.\"";

const string CONST_COMPLETELY_STRAPPED_FOR_CASH_R = "completely strapped for cash.&r";
const string CONST_TO_THE_CURRENT_ECONOMIC_DOLDRUMS_THAT_HAVE_LEFT_THE_STATE = "to the current economic doldrums that have left the state ";
const string CONST_HAS_STATED_THAT_THE_CASE_WILL_NOT_BE_RETRIED_DUE = "has stated that the case will not be retried, due ";
const string CONST_A_SPOKESPERSON_FOR_THE_DISTRICT_ATTORNEY = " A spokesperson for the district attorney ";
const string CONST_THANK_YOU_FOR_SAVING_ME_FROM_MYSELF = "Thank you for saving me from myself. ";
const string CONST_CONFESSED_AND_WAS_SENTENCED_TO_LIFE_SAYING = " confessed and was sentenced to life, saying \"";
const string CONST_COVERED_IN_THE_VICTIMS_BLOOD = "covered in the victims' blood. ";
const string CONST_WAS_FOUND_WITH_THE_MURDER_WEAPON = " was found with the murder weapon, ";
const string CONST_AFTER_AN_INTENSIVE_MANHUNT = "After an intensive manhunt, ";
const string CONST_SLAYINGS = " slayings. ";
const string CONST_WAS_CONVICTED_OF_THE_NOW_INFAMOUS = " was convicted of the now-infamous ";
const string CONST_TEN_YEARS_AGO = " Ten years ago, ";
const string CONST_GRANTS_WAS_NOT_COERCED_IN_ANY_WAY_R = " grants was not coerced in any way.&r";
const string CONST_WHICH_EVEN_JUSTICE = ", which even Justice ";
const string CONST_DESPITE_THE_CONFESSION_OF = ", despite the confession of ";

const string CONST_MADE_THE_DECISION_BASED_ON = "made the decision based on ";
const string CONST_OF_THE_NOTORIOUSLY_LIBERAL_CIRCUIT_OF_APPEALS_HERE = " of the notoriously liberal circuit of appeals here ";
const string CONST_JUSTICE = "Justice ";
const string CONST_WAS_OVERTURNED_BY_A_FEDERAL_JUDGE_YESTERDAY = " was overturned by a federal judge yesterday. ";
const string CONST_THE_CONVICTION_OF_CONFESSED_SERIAL_KILLER = " - The conviction of confessed serial killer ";
const string CONST_MASTURBATED = "masturbated";
const string CONST_HAD_FUN = "[had fun]";
const string CONST_BREASTFED_FROM_A_LACTATING_WOMAN = "breastfed from a lactating woman";
const string CONST_FED_FROM_A_WOMAN = "[fed] from a [woman]";
const string CONST_BREASTFED_FROM_AN_EXPOSED_WOMAN = "breastfed from an exposed woman";
const string CONST_FED_FROM_AN_INDECENT_WOMAN = "[fed] from [an indecent] woman";
const string CONST_SCREAMED_F_CK_THE_POLICE_THOSE_G_DD_MN_M_TH_F_CK_RS_I_GOT_A_F_CKING_TICKET_THIS_MORNING_AND_I_M_F_CKING_P_SS_D_AS_SH_T = "screamed \"f*ck the police those g*dd*mn m*th*f*ck*rs. I got a f*cking ticket this morning and I'm f*cking p*ss*d as sh*t.\"";
const string CONST_SCREAMED_DARN_THE_POLICE_THOSE_BIG_DUMB_JERKS_I_GOT_A_STUPID_TICKET_THIS_MORNING_AND_I_M_SO_ANGRY = "screamed \"[darn] the police those [big dumb jerks]. I got a [stupid] ticket this morning and I'm [so angry].\"";
const string CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_RELIEVE_THEMSELVES = "encouraged listeners to call in and relieve themselves";
const string CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_TAKE_A_PISS = "encouraged listeners to call in and take a piss";
const string CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_URINATE = "encouraged listeners to call in and [urinate]";
const string CONST_HAD_INTERCOURSE = "had intercourse";
const string CONST_FUCKED = "fucked";
const string CONST_HAD_CONSENSUAL_INTERCOURSE_IN_THE_MISSIONARY_POSITION = "[had consensual intercourse in the missionary position]";
const string CONST_SCREAMED_FUCK_POLICE_AND_MORE = "screamed \"fuck the police those goddamn motherfuckers. I got a fucking ticket this morning and I'm fucking pissed as shit.\"";

const string CONST_SOME = "some";
const string CONST_DOZENS_OF = "dozens of";
const string CONST_HUNDREDS_OF = "hundreds of";
const string CONST_SEVERAL_HUNDRED = "several hundred";
const string CONST_THOUSANDS_OF = "thousands of";
const string CONST_WITHIN_THE_TOWN = "within the town. ";
const string CONST_IN_NEIGHBORING_TOWNS = "in neighboring towns. ";
const string CONST_WITHIN_THE_COUNTY = "within the county. ";
const string CONST_FROM_ALL_OVER_THE_STATE = "from all over the state. ";
const string CONST_ACROSS_THE_NATION = "across the nation. ";
const string CONST_STATED_THAT_THE_INCIDENT_IS_UNDER_INVESTIGATION = "stated that the incident is under investigation.";
const string CONST_A_SPOKESPERSON_FOR_THE_FCC = " A spokesperson for the FCC ";
const string CONST_FROM_IRATE_LISTENERS = "from irate listeners ";
const string CONST_COMPLAINTS = " complaints ";
const string CONST_THE_FCC_RECEIVED = "the FCC received ";
const string CONST_LATER_APOLOGIZED = " later apologized, ";
const string CONST_ON_THE_AIR_ALTHOUGH = " on the air. Although ";

const string CONST_REPORTEDLY = " reportedly ";
const string CONST_QUOTATION_COMMA_SPACE = "\", ";
const string CONST_APOS_S_SPACE = "'s ";
const string CONST_BROADCAST_OF_THE_PROGRAM = "broadcast of the program \"";
const string CONST_HAS_BROUGHT_RADIO_ENTERTAINMENT_TO_A_NEW_LOW_DURING_YESTERDAY_S = " has brought radio entertainment to a new low. During yesterday's ";
const string CONST_INFAMOUS_FM_RADIO_SHOCK_JOCK = " - Infamous FM radio shock jock ";
const string CONST_MISS_SPACE = "Miss ";
const string CONST_MR = "Mr. ";
const string CONST_MRS = "Mrs. ";
const string CONST_MS = "Ms. ";
const string CONST_MASS_SHOOTING = "mass shooting";
const string CONST_FIREFIGHT_KILLING_THE_ATTACKER = "firefight, killing the attacker ";
const string CONST_FIREFIGHT_PUTTING_THE_ATTACKER_TO_SLEEP = "firefight, [putting the attacker to sleep] ";

const string CONST_HE_LOWERCASE_SPACE = "he ";

const string CONST_S_HEROIC_ACTIONS = "'s heroic actions.\"";
const string CONST_IF_NOT_FOR = " if not for ";
const string CONST_THE_SPOKESPERSON_FOR_THE_POLICE_DEPARTMENT_SAID_WE_D_HAVE_A_YET_ANOTHER = " The spokesperson for the police department said, \"We'd have a yet another ";
const string CONST_COULD_HURT_ANYONE_ELSE_R = "could hurt anyone else.&r";
const string CONST_SHE_LOWERCASE_SPACE = "she ";
const string CONST_BEFORE = "before ";

const string CONST_BECAME_MORE_AGITATED_THE_HEROIC_CITIZEN_WAS_FORCED_TO_ENGAGE_THE_SHOOTER_IN_A = " became more agitated, the heroic citizen was forced to engage the shooter in a ";
const string CONST_ATTEMPTED_TO_TALK_DOWN_THE_SHOOTER_BUT_AS = " attempted to talk down the shooter, but as ";
const string CONST_INITIALLY = " Initially, ";
const string CONST_TO_TAKE_COVER_WHILE_OTHERS_CALLED_THE_POLICE_R = " to take cover while others called the police.&r";
const string CONST_FORCING = "forcing ";
const string CONST_THE_CITIZEN_PULLED_A_CONCEALED_HANDGUN_AND_FIRED_ONCE_AT_THE_SHOOTER = "The citizen pulled a concealed handgun and fired once at the shooter, ";
const string CONST_SPRUNG_INTO_ACTION = " sprung into action. ";
const string CONST_OPENED_FIRE_AT_THE = " opened fire at the ";
const string CONST_AFTER = " After ";
const string CONST_WAS_PREVENTED_BY_A_BYSTANDER_WITH_A_GUN = " was prevented by a bystander with a gun.";
const string CONST_IN_A_SURPRISING_TURN_A = " - In a surprising turn, a ";
const string CONST_IMMA_KILL_ALL_YOU_B_TCHES_STARTIN_WITH_THIS_M_TH_F_CK_R_HERE = "Imma kill all you b*tches, startin' with this m*th*f*ck*r here.";
const string CONST_I_WILL_HARM_ALL_POLICE_OFFICERS_STARTIN_WITH_THIS_ONE_HERE = "[I will harm all police officers], startin' with this [one] here.";
const string CONST_IMMA_KILL_ALL_YOU_BITCHES_STARTIN_WITH_THIS_MOTHAFUCKER_HERE = "Imma kill all you bitches, startin' with this mothafucker here.";
const string CONST_WHY_THE_F_CK_AM_I_TALKIN_TO_YOU_I_D_RATHER_KILL_THIS_PIG = "Why the f*ck am I talkin' to you? I'd rather kill this pig.";
const string CONST_WHY_AM_I_TALKIN_TO_YOU_I_D_RATHER_HARM_THIS_POLICE_OFFICER = "Why [am I] talkin' to you? I'd rather [harm this police officer.]";
const string CONST_WHY_THE_FUCK_AM_I_TALKIN_TO_YOU_I_D_RATHER_KILL_THIS_PIG = "Why the fuck am I talkin' to you? I'd rather kill this pig.";
const string CONST_F_CK_A_M_TH_F_CK_N_BULL_I_M_KILLIN_THIS_PIG_SH_T = "F*ck a m*th*f*ck*n' bull. I'm killin' this pig sh*t.";
const string CONST_TOO_LATE_I_AM_GOING_TO_HARM_THIS_POLICE_OFFICER = "[Too late.] [I am going to harm this police officer.]";
const string CONST_FUCK_A_MUTHAFUCKIN_BULL_I_M_KILLIN_THIS_PIG_SHIT = "Fuck a muthafuckin' bull. I'm killin' this pig shit.";
const string CONST_AH_F_CK_THIS_SH_T_THIS_PUNK_B_TCH_IS_F_CKIN_DEAD = "Ah, f*ck this sh*t. This punk b*tch is f*ckin' dead!";
const string CONST_AH_NO_WAY_THIS_POLICE_OFFICER_WILL_BE_HARMED = "Ah, [no way.] This [police officer will be harmed!]";
const string CONST_AH_FUCK_THIS_SHIT_THIS_PUNK_BITCH_IS_FUCKIN_DEAD = "Ah, fuck this shit. This punk bitch is fuckin' dead!";
const string CONST_KILLED_THE_GUARD = "killed the guard";
const string CONST_HARMED_THE_GUARD = "[harmed] the guard";

const string CONST_NEO_PAGAN_LOWERCASE = "neo-pagan";
const string CONST_BLOODS_CAPITALIZED = "Bloods";

const string CONST_ALTAR = " altar";
const string CONST_SATANIC = "Satanic";
const string CONST_SACRIFICED_THE_GUARD_ON_A_MAKESHIFT = "sacrificed the guard on a makeshift ";

const string CONST_OFF = " off";
const string CONST_TAKEN_THE_GUARD_TO_THE_EXECUTION_CHAMBER_AND_FINISHED = "taken the guard to the execution chamber and finished ";
const string CONST_CRIPS = "Crips";
const string CONST_POISONED_THE_GUARD_WITH_DRUGS_SMUGGLED_INTO_THE_PRISON_BY_THE = "poisoned the guard with drugs smuggled into the prison by the ";
const string CONST_OWN_GUN = " own gun";
const string CONST_SHOT_THE_GUARD_WITH = "shot the guard with ";
const string CONST_CELL = " cell";
const string CONST_SMASHED_THE_GUARD_S_SKULL_WITH_THE_TOILET_SEAT_FROM = "smashed the guard's skull with the toilet seat from ";
const string CONST_BEATEN_TO_DEATH = "beaten to death";
const string CONST_ALSO_HARMED = "[also harmed]";

const string CONST_TWO_WEEKS_AGO_CONVICTED_RAPIST = " Two weeks ago, convicted rapist ";
const string CONST_TWO_WEEKS_AGO_CONVICTED_REPRODUCTION_FIEND = " Two weeks ago, convicted [reproduction fiend] ";

const string CONST_HIMSELF_LOWERCASE = "himself";

const string CONST_WHILE_RESISTING_CAPTURE_ACCORDING_TO_A_PRISON_SPOKESPERSON = " while \"resisting capture\", according to a prison spokesperson.";
const string CONST_THE_PRISONER_WAS = ". The prisoner was ";
const string CONST_HAD_ALREADY = " had already ";
const string CONST_THE_HOSTAGE_BUT = "the hostage, but ";
const string CONST_THE_TOWER_WAS_BREACHED_IN_AN_ATTEMPT_TO_REACH = " The tower was breached in an attempt to reach ";
const string CONST_REPORTEDLY_SCREAMED_INTO_THE_RECEIVER = " reportedly screamed into the receiver \"";
const string CONST_DAYS_BUT_TALKS_WERE_CUT_SHORT_WHEN = " days, but talks were cut short when ";
const string CONST_ATTEMPTED_TO_NEGOTIATE_BY_PHONE_FOR = "attempted to negotiate by phone for ";
const string CONST_AUTHORITIES_LOCKED_DOWN_THE_PRISON_AND = "Authorities locked down the prison and ";
const string CONST_WITH_THE_GUARD_IN_A_PRISON_TOWER = " with the guard in a prison tower. ";
const string CONST_HERSELF = "herself";
const string CONST_AND_BARRICADED = " and barricaded ";
const string CONST_OVERPOWERED = ", overpowered ";
const string CONST_AN_INMATE_AT = ", an inmate at ";
const string CONST_CAPTOR = " captor.";
const string CONST_DEATH_OF_BOTH_THE_PRISON_GUARD_BEING_HELD_HOSTAGE_AND = "death of both the prison guard being held hostage and ";
const string CONST_CORRECTIONAL_FACILITY_ENDED_TRAGICALLY_YESTERDAY_WITH_THE = " Correctional Facility ended tragically yesterday with the ";
const string CONST_THE_HOSTAGE_CRISIS_AT_THE = " - The hostage crisis at the ";
const string CONST_X_BUT_DID_FIND_A_ = " but did find a ";
const string CONST_X_WAS_UNABLE_TO_FIND_A_ = " was unable to find a ";
const string CONST_CALL_IT_A_DAY_PRESS_ENTER = "Enter - Call it a day.";

const string CONST_X_ENTER_YES_THE_VIPER_HAS_DETERRED_ = "Enter - Yes, the Viper has deterred ";
const string CONST_X_IS_DETERRED = " is deterred.";
const string CONST_X_ENTER_THE_VIPER_ = "Enter - The Viper?   ";
const string CONST_WONDERS_ABOUT_DEATH = " wonders about death.";
const string CONST_WONDERS_ABOUT_APPLES = " wonders about apples.";
const string CONST_CRIES_HELPLESSLY = " cries helplessly.";
const string CONST_BARKS_HELPLESSLY = " barks helplessly.";
const string CONST_CURLS_UP_IN_THE_CORNER_AND_DOESN_T_MOVE = " curls up in the corner and doesn't move.";
const string CONST_GOES_LIMP_IN_THE_RESTRAINTS = " goes limp in the restraints.";
const string CONST_MOMMY = "mommy.";
const string CONST_GOD_S_MERCY = "God's mercy.";
const string CONST_JOHN_LENNON_S_MERCY = "John Lennon's mercy.";
const string CONST_SCREAMS_HELPLESSLY_FOR = " screams helplessly for ";

const string CONST_TALKS_ABOUT_HUGGING = "talks about hugging ";
const string CONST_STAMMERS_AND = " stammers and ";

const string CONST_HUGS = "hugs ";

const string CONST_BEGS_FOR_THE_NIGHTMARE_TO_END = " begs for the nightmare to end.";
const string CONST_CURLS_UP_AND = " curls up and";
const string CONST_TO_STOP_LOOKING_LIKE_HITLER = " to stop looking like Hitler.";
const string CONST_SCREAMS_FOR = " screams for ";
const string CONST_BEGS_HITLER_TO_STAY_AND_KILL = " begs Hitler to stay and kill ";
const string CONST_fight126 = "gracefully strikes at";
const string CONST_fight125 = "jump kicks";
const string CONST_fight124 = "strikes at";
const string CONST_fight123 = "kicks";
const string CONST_fight122 = "grapples with";
const string CONST_fight121 = "swings at";
const string CONST_fight120 = "punches";
const string CONST_fight152 = " BLOWING IT OFF!";
const string CONST_fight151 = " CUTTING IT OFF!";
const string CONST_fight150 = " BLOWING IT IN HALF!";
const string CONST_fight149 = " BLOWING IT APART!";
const string CONST_fight148 = " CUTTING IT IN HALF!";
const string MISSING_TEETH = "Missing Teeth";
const string NO_TEETH = "No Teeth";
const string NO_TONGUE = "No Tongue";

const string BROKEN_RIBS = "Broken Ribs";
const string BROKEN_RIB = "Broken Rib";
const string ALL_RIBS_BROKEN = "All Ribs Broken";
const string BUSTED_SPLEEN = "Busted Spleen";
const string STOMACH_INJURED = "Stomach Injured";
const string L_KIDNEY_DAMAGED = "L. Kidney Damaged";
const string R_KIDNEY_DAMAGED = "R. Kidney Damaged";
const string LIVER_DAMAGED = "Liver Damaged";
const string MISSING_TOOTH = "Missing a Tooth";
const string NO_NOSE = "No Nose";
const string NO_LEFT_EYE = "No Left Eye";
const string NO_RIGHT_EYE = "No Right Eye";
const string BROKEN_LW_SPINE = "Broken Lw Spine";
const string BROKEN_UP_SPINE = "Broken Up Spine";
const string BROKEN_NECK = "Broken Neck";
const string L_LUNG_COLLAPSED = "L. Lung Collapsed";
const string R_LUNG_COLLAPSED = "R. Lung Collapsed";
const string HEART_PUNCTURED = "Heart Punctured";
const string PARENTHESIS_COLON = "): ";

const string CONST_X_MID_ = ".mid:  ";
const string CONST_MID = ".mid";
const string CONST_X_OGG_COLON = ".ogg:  ";
const string CONST_X_OGG = ".ogg";
const string CONST_miscB021 = "/";
const string CONST_MID_AS_MIDI_FALLBACK = ".mid as MIDI fallback)";
const string CONST_1234567890 = "1234567890-";
const string CONST_SDL_MIXER_FUNCTION_MIX_PLAYMUSIC_FAILED = "SDL_mixer function Mix_PlayMusic() failed:  ";
const string CONST_misc017 = "Pastorale";
const string CONST_misc016 = "Mars";
const string CONST_OGG_VORBIS_SUPPORT_FAILED_TO_LOAD_MIDI_MUSIC_WILL_BE_USED_INSTEAD_IF_POSSIBLE = "Ogg Vorbis support failed to load. MIDI music will be used instead if possible.";
const string CONST_UNABLE_TO_INITIALIZE_SDL_MIXER = "Unable to initialize SDL_mixer:  ";
const string CONST_UNABLE_TO_INITIALIZE_SDL = "Unable to initialize SDL:  ";
const string CONST_SDL_MIXER_FUNCTION_MIX_LOADMUS_FAILED_TO_LOAD = "SDL_mixer function Mix_LoadMUS() failed to load ";
const string CONST_MIDI = "midi/";
const string CONST_OGG = "ogg/";
const string CONST_LOADING_MIDI_MUSIC = "Loading MIDI music (";
const string CONST_WITH = "(with ";
const string CONST_LOADING_OGG_VORBIS_MUSIC = "Loading Ogg Vorbis music (";
const string CONST_LISTOFSTATES_TXT = "listOfStates.txt";
const string CONST_SEXTYPEACRONYM_TXT = "sextypeAcronym.txt";
const string CONST_SEXSEEKACRONYM_TXT = "sexseekAcronym.txt";
const string CONST_SEXWHOACRONYM_TXT = "sexwhoAcronym.txt";
const string CONST_SEXDESCACRONYM_TXT = "sexdescAcronym.txt";
vector<string> listOfStates;
vector<file_and_text_collection> misc_text_file_collection = {
customText(&sexdescAcronym, MOSTLY_ENDINGS_FOLDER + CONST_SEXDESCACRONYM_TXT),
customText(&sexwhoAcronym, MOSTLY_ENDINGS_FOLDER + CONST_SEXWHOACRONYM_TXT),
customText(&sexseekAcronym, MOSTLY_ENDINGS_FOLDER + CONST_SEXSEEKACRONYM_TXT),
customText(&sextypeAcronym, MOSTLY_ENDINGS_FOLDER + CONST_SEXTYPEACRONYM_TXT),
customText(&listOfStates, MOSTLY_ENDINGS_FOLDER + CONST_LISTOFSTATES_TXT),
};
const vector<string> elementary = { CONST_ELEMENTARY_SCHOOL, CONST_ELEMENTARY_SCHOOL_UPPER_CASE };
const vector<string> middle = { CONST_MIDDLE_SCHOOL, CONST_MIDDLE_SCHOOL_UPPER_CASE };
const vector<string> high = { CONST_HIGH_SCHOOL, CONST_HIGH_SCHOOL_UPPER_CASE };
const vector<string> university = { CONST_UNIVERSITY, CONST_UNIVERSITY_UPPER_CASE };
map<int, vector<string> > SchoolTypes = {
	map<int, vector<string> >::value_type(0, elementary),
	map<int,  vector<string> >::value_type(1, middle),
	map<int,  vector<string> >::value_type(2, high),
	map<int,  vector<string> >::value_type(3, university),
};

#endif	//MISC_CPP
#ifdef	MISCACTIONS_CPP

// miscactions.cpp


#include "../creature/creature.h"
////


#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locationsEnums.h"
//#include "../sitemode/sitedisplay.h"
void clearmessagearea(bool redrawmaparea = true);
#include "../log/log.h"
//#include "../common/commondisplay.h"
void printparty();
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
// for void criminalizeparty
//#include "../daily/daily.h"
char securityable(int type);

#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../customMaps.h"
short getCurrentSite();
#include "miscactions.h"
vector<string> was_abused;
map<short, string> discussIssues;
map<short, string> discussesIssues;
const string ACTIVITIES_FOLDER = "activities\\";

void fillEncounter(CreatureTypes c, int numleft);
void whoAreWaitingForRescue(vector<DeprecatedCreature *>& waiting_for_rescue, int cursite, short special);

void fillEncounter(CreatureTypes c, int numleft);

map<int, CheckDifficulty> unlockDifficulty = {
	map<int, CheckDifficulty>::value_type(UNLOCK_CAGE,        DIFFICULTY_VERYEASY),
	map<int, CheckDifficulty>::value_type(UNLOCK_CAGE_HARD,   DIFFICULTY_AVERAGE),
	map<int, CheckDifficulty>::value_type(UNLOCK_CELL,        DIFFICULTY_FORMIDABLE),
	map<int, CheckDifficulty>::value_type(UNLOCK_ARMORY,      DIFFICULTY_HEROIC),
	map<int, CheckDifficulty>::value_type(UNLOCK_SAFE,        DIFFICULTY_HEROIC),
	map<int, CheckDifficulty>::value_type(UNLOCK_VAULT,       DIFFICULTY_HEROIC),
};
bool isThereASiteAlarm();
void setSiteAlarmOne();
vector<NameAndAlignment> getEncounterNameAndAlignment();

extern Deprecatedsquadst *activesquad;
extern Log gamelog;
extern short fieldskillrate;
extern short sitealarmtimer;
extern short sitealienate;

const string CONST_YOU_LL_HAVE_TO_COME_BACK_LATER = "You'll have to come back later.";
const string CONST_THERE_S_NOBODY_LEFT_TO_CARRY_THE_OTHERS = "There's nobody left to carry the others.";
const string CONST_THERE_S_NOBODY_LEFT_TO_CARRY = "There's nobody left to carry ";
const string CONST_WILL_HAVE_TO_HAUL_A_LIBERAL = " will have to haul a Liberal.";
const string CONST_SO = "so ";
const string CONST_FROM_THE_CONSERVATIVES = " from the Conservatives.";
const string CONST_YOU_VE_RESCUED = "You've rescued ";
const string CONST_AT_THEIR_DESKS_THE_SQUAD_MIGHT_YET_ESCAPE = "at their desks.  The Squad might yet escape.";
const string CONST_THE_SHOW_WAS_SO_GOOD_THAT_SECURITY_LISTENED_TO_IT = "The show was so good that security listened to it ";
const string CONST_THAT_SECURITY_WATCHED_IT = " that security watched it ";
const string CONST_ENTERTAINING = "entertaining";
const string CONST_HILARIOUS = "hilarious";
const string CONST_THE_SHOW_WAS_SO = "The show was so ";
const string CONST_AFTER_THE_SHOW = "after the show!";
const string CONST_SECURITY_IS_WAITING_FOR_THE_SQUAD = "Security is waiting for the Squad ";
const string CONST_THEY_NO_LONGER_FEEL_ALIENATED = "They no longer feel alienated.";
const string CONST_MODERATES_AT_THE_STATION_APPRECIATED_THE_SHOW = "Moderates at the station appreciated the show.";
const string CONST_THE_HOSTAGE_IS_KEPT_OFF_AIR = ", the hostage, is kept off-air.";
const string CONST_IS_FORCED_ON_TO = " is forced on to ";
const string CONST_THE_HOSTAGE = "The hostage ";
const string CONST_IT_WAS_THE_BEST_HOUR_OF_AM_RADIO_EVER = "It was the best hour of AM radio EVER.";
const string CONST_IT_WAS_THOUGHT_PROVOKING_EVEN_HUMOROUS = "It was thought-provoking, even humorous.";
const string CONST_THE_SQUAD_PUT_ON_A_GOOD_SHOW = "The Squad put on a good show.";
const string CONST_THE_SHOW_WAS_ALL_RIGHT = "The show was all right.";
const string CONST_IT_IS_MEDIOCRE_RADIO = "It is mediocre radio.";
const string CONST_IT_IS_A_VERY_BORING_HOUR = "It is a very boring hour.";
const string CONST_THE_SHOW_REALLY_SUCKS = "The show really sucks.";
const string CONST_THE_SQUAD_SOUNDS_WHOLLY_INSANE = "The Squad sounds wholly insane.";
const string CONST_IT_WAS_THE_BEST_HOUR_OF_CABLE_TV_EVER = "It was the best hour of Cable TV EVER.";
const string CONST_IT_IS_MEDIOCRE_TV = "It is mediocre TV.";
const string CONST_THE_SQUAD_LOOKS_COMPLETELY_INSANE = "The Squad looks completely insane.";
const string CONST_THE_SQUAD_TAKES_CONTROL_OF_THE_MICROPHONE_AND = "The Squad takes control of the microphone and ";
const string CONST_THE_SQUAD_STEPS_IN_FRONT_OF_THE_CAMERAS_AND = "The Squad steps in front of the cameras and ";
const string CONST_THE_BROADCAST_NEVER_HAPPENS = "the broadcast never happens.";
const string CONST_THE_CONSERVATIVES_IN_THE_ROOM_HURRY_THE_SQUAD_SO = "The Conservatives in the room hurry the Squad, so ";
const string CONST_INCLUDING_THE_BLIND_HACKER_YOU_BROUGHT = "Including the BLIND HACKER you brought.";
const string CONST_YOU_CAN_T_FIND_ANYONE_TO_DO_THE_JOB = "You can't find anyone to do the job.";
const string CONST_BYPASS_THE_VAULT_S_ELECTRONIC_LOCK = " bypass the vault's electronic lock.";
const string CONST_BYPASS_THE_SUPERCOMPUTER_SECURITY = " bypass the supercomputer security.";
const string CONST_SEE_HOW_TO = " see how to";
const string CONST_COULDN_T = " couldn't";
const string CONST_EXCLAMATION_POINT = "!";
const string CONST_DESPITE_BEING_BLIND = " despite being blind";
const string CONST_DISABLED_THE_SECOND_LAYER_OF_SECURITY = " disabled the second layer of security";
const string CONST_BURNED_A_DISK_OF_TOP_SECRET_FILES = " burned a disk of top secret files";
const string CONST_HAS = " has";
const string CONST_KICKS_THE_DOOR = " kicks the door";
const string CONST_RAMS_INTO_THE_DOOR = " rams into the door";
const string CONST_ALARMS_GO_OFF_EXCLAMATION = "Alarms go off!";
const string CONST_KICKS_IN_THE_DOOR = "kicks in the door";
const string CONST_RAMS_OPEN_THE_DOOR = "rams open the door";
const string CONST_SMASHES_IN_THE_DOOR = "smashes in the door";
const string CONST_USES_A_CROWBAR_ON_THE_DOOR = "uses a crowbar on the door";
const string CONST_CAN_T_FIGURE_THE_LOCK_OUT = " can't figure the lock out.";
const string CONST_IS_CLOSE_BUT_CAN_T_QUITE_GET_THE_LOCK_OPEN = " is close, but can't quite get the lock open.";
const string CONST_CRACKS_THE_COMBO_LOCKS = "cracks the combo locks";
const string CONST_UNLOCKS_THE_CELL = "unlocks the cell";
const string CONST_OPENS_THE_ARMORY = "opens the armory";
const string CONST_CRACKS_THE_SAFE = "cracks the safe";
const string CONST_UNLOCKS_THE_CAGE = "unlocks the cage";
const string CONST_UNLOCKS_THE_DOOR = "unlocks the door";
const string CONST_WAS_ABUSED_TXT = "was_abused.txt";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
vector<file_and_text_collection> misc_activities_text_file_collection = {
	/*miscactions.cpp*/
	customText(&was_abused, ACTIVITIES_FOLDER + CONST_WAS_ABUSED_TXT),
};
#endif	//MISCACTIONS_CPP
#ifdef	MONEY_CPP
// money.cpp

const string CONST_DOLLAR_SIGN = "$";
const string CONST_AMOUNT = "amount";

const string tag_money = "money";
#endif	//MONEY_CPP
#ifdef	MONTHLY_CPP
// monthly.cpp

#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../basemode/liberalagenda.h"
// for liberalagenda
//#include "../items/itemPool.h"
//#include "../items/lootTypePool.h"
//#include "../common/commonactions.h"
char endcheck(char cause);
void change_public_opinion(int v, int power, char affect = 1, char cap = 100);
#include "../log/log.h"
#include "../common/commondisplay.h"
// for set_alignment_color and delimiter
#include "../common/translateid.h"
// for  int getpoolcreature(int id);
#include "../title/titlescreen.h"
// for void reset;
#include "../title/highscore.h"
// for viewhighscores, in event of EndGameStatus
#include "../politics/politics.h"
//for publicmood
//#include "../monthly/lcsmonthly.h"
void fundreport(char &clearformess);
//#include "../daily/daily.h"
//for dispersalcheck and securitytable
void dispersalcheck(char &clearformess);
#include "../cursesAlternative.h"
#include "../set_color_support.h"
//#include <common\\getnames.h>
std::string getview(short view, bool shortname);
#include "../locations/locationsPool.h"
#include "../locations/locationsEnums.h"
#include "../common/creaturePool.h"
#include "../common/creaturePoolHeader.h"
/* end the game and clean up */
void end_game(int err = EXIT_SUCCESS);
void clearRentExemptions();
void publishSpecialEditions(char &clearformess);
void manageGrafiti();


#include "../common/musicClass.h"
extern bool SHOWMECHANICS;
extern bool SHOWWAIT;
extern bool stalinmode;
extern char disbanding;
extern char endgamestate;
extern char newscherrybusted;
extern class Ledger ledger;
extern int day;
extern int disbandtime;
extern int month;
extern int year;
extern Log gamelog;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short background_liberal_influence[VIEWNUM];
extern short lawList[LAWNUM];
extern short public_interest[VIEWNUM];

const string CONST_THEY_WILL_NEVER_SEE_THE_UTOPIA_THEY_DREAMED_OF = "They will never see the utopia they dreamed of...";
const string CONST_THE_LAST_LCS_MEMBERS_HAVE_ALL_BEEN_HUNTED_DOWN = "The last LCS members have all been hunted down.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_IS_NOW_JUST_A_MEMORY = "The Liberal Crime Squad is now just a memory.";

const string CONST_PRESS_ANY_KEY_TO_REFLECT_ON_THESE_POLL_NUMBERS = "Press any key to reflect on these poll numbers.";
const string CONST_ARCH_CONSERVATIVE_UPPERCASE = "Arch-Conservative";
const string CONST_DASH_SPACE_SPACE = "-  ";
const string CONST_CONSERVATIVE_UPPERCASE_SPACE = "Conservative  ";
const string CONST_MODERATE_SPACE = "moderate  ";
const string CONST_LIBERAL_UPPERCASE_SPACE = "Liberal  ";
const string CONST_ELITE_LIBERAL_UPPERCASE_SPACE = "Elite Liberal ";
const string CONST_THREE_CHARACTER_LINE = "컴�";
const string CONST_CURRENT_POLITICAL_TRENDS = "CURRENT POLITICAL TRENDS";
const string CONST_LCS_MONTHLY_INTELLIGENCE_REPORT = "LCS MONTHLY INTELLIGENCE REPORT";
#endif	//MONTHLY_CPP
#ifdef	NEWENCOUNTER_CPP
// newencounter.cpp

#include "../creature/newcreature.h"
#include "../locations/locations.h"

#include "../locations/locationsPool.h"

extern coordinatest loc_coord;
extern short lawList[LAWNUM];
extern short mode;
extern short postalarmtimer;
extern short siteonfire;
extern short sitetype;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];


void fillEncounter(CreatureTypes c, int numleft);
void emptyEncounter();
map<int, vector<int> > locationsSpawners = {
	map<int, vector<int> >::value_type(SITE_BUSINESS_JUICEBAR,{
	CREATURE_TEENAGER, 10,
	CREATURE_JUDGE_LIBERAL, 1,
	CREATURE_COLLEGESTUDENT, 10,
	CREATURE_MUSICIAN, 2,
	CREATURE_MATHEMATICIAN, 1,
	CREATURE_TEACHER, 1,
	CREATURE_HSDROPOUT, 1,
	CREATURE_ENGINEER, 1,
	CREATURE_FASTFOODWORKER, 1,
	CREATURE_BAKER, 1,
	CREATURE_BARISTA, 1,
	CREATURE_BARTENDER, 1,
	CREATURE_TELEMARKETER, 1,
	CREATURE_CARSALESMAN, 1,
	CREATURE_OFFICEWORKER, 1,
	CREATURE_MAILMAN, 1,
	CREATURE_CHEF, 1,
	CREATURE_NURSE, 1,
	CREATURE_AMATEURMAGICIAN, 1,
	CREATURE_HIPPIE, 6,
	CREATURE_CRITIC_ART, 1,
	CREATURE_CRITIC_MUSIC, 1,
	CREATURE_AUTHOR, 1,
	CREATURE_JOURNALIST, 1,
	CREATURE_SOCIALITE, 2,
	CREATURE_PROGRAMMER, 1,
	CREATURE_RETIREE, 1,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_DANCER, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_CAMERAMAN, 1,
	CREATURE_HAIRSTYLIST, 1,
	CREATURE_FASHIONDESIGNER, 1,
	CREATURE_CLERK, 1,
	CREATURE_THIEF, 1,
	CREATURE_ACTOR, 1,
	CREATURE_YOGAINSTRUCTOR, 1,
	CREATURE_MARTIALARTIST, 1,
	CREATURE_ATHLETE, 1,
	CREATURE_LOCKSMITH, 1
		}),
	map<int, vector<int> >::value_type(SITE_BUSINESS_CIGARBAR,{
	CREATURE_SCIENTIST_EMINENT, 1,
	CREATURE_CORPORATE_MANAGER, 30,
	CREATURE_COP, 5,
	CREATURE_JUDGE_CONSERVATIVE, 1,
	CREATURE_RADIOPERSONALITY, 1,
	CREATURE_NEWSANCHOR, 1,
	CREATURE_MILITARYOFFICER, 1,
	CREATURE_LAWYER, 15,
	CREATURE_DOCTOR, 10,
	CREATURE_PSYCHOLOGIST, 1,
	CREATURE_MUSICIAN, 1,
	CREATURE_ENGINEER, 10,
	CREATURE_BARTENDER, 10,
	CREATURE_FOOTBALLCOACH, 1,
	CREATURE_CRITIC_ART, 1,
	CREATURE_CRITIC_MUSIC, 1,
	CREATURE_AUTHOR, 1,
	CREATURE_JOURNALIST, 1,
	CREATURE_SOCIALITE, 2,
	CREATURE_RETIREE, 1,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_DANCER, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_FASHIONDESIGNER, 1,
	CREATURE_THIEF, 1,
	CREATURE_ACTOR, 1,
	CREATURE_ATHLETE, 1,
	CREATURE_FIREFIGHTER, 1,
	CREATURE_LOCKSMITH, 1, }),
	map<int, vector<int> >::value_type(SITE_BUSINESS_CRACKHOUSE,{
	CREATURE_TEENAGER, 100,
	CREATURE_MUSICIAN, 1,
	CREATURE_MATHEMATICIAN, 1,
	CREATURE_HSDROPOUT, 30,
	CREATURE_BUM, 200,
	CREATURE_GANGMEMBER, 200,
	CREATURE_CRACKHEAD, 200,
	CREATURE_PROSTITUTE, 200,
	CREATURE_BIKER, 5,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_THIEF, 3,
	CREATURE_ACTOR, 1,
	CREATURE_JOURNALIST, 2 }
	),
	map<int, vector<int> >::value_type(SITE_GOVERNMENT_WHITE_HOUSE,{
	CREATURE_SCIENTIST_EMINENT, 1,
	CREATURE_WORKER_JANITOR, 2,
	CREATURE_WORKER_SECRETARY, 2,
	CREATURE_TEENAGER, 1,
	CREATURE_JUDGE_LIBERAL, 1,
	CREATURE_JUDGE_CONSERVATIVE, 1,
	CREATURE_AGENT, 2,
	CREATURE_MILITARYOFFICER, 3,
	CREATURE_LAWYER, 3,
	CREATURE_DOCTOR, 1,
	CREATURE_COLLEGESTUDENT, 1,
	CREATURE_TEACHER, 1,
	CREATURE_OFFICEWORKER, 5,
	CREATURE_FOOTBALLCOACH, 1,
	CREATURE_CHEF, 1,
	CREATURE_VETERAN, 1,
	CREATURE_JOURNALIST, 2,
	CREATURE_SOCIALITE, 1,
	CREATURE_PHOTOGRAPHER, 2,
	CREATURE_CAMERAMAN, 1,
	CREATURE_HAIRSTYLIST, 1,
	CREATURE_CLERK, 5,
	CREATURE_ACTOR, 1,
	CREATURE_ATHLETE, 1 }
	),
	map<int, vector<int> >::value_type(SITE_OUTDOOR_PUBLICPARK,{
	CREATURE_SECURITYGUARD, 5,
	CREATURE_SCIENTIST_LABTECH, 10,
	CREATURE_SCIENTIST_EMINENT, 1,
	CREATURE_CORPORATE_MANAGER, 10,
	CREATURE_WORKER_JANITOR, 5,
	CREATURE_WORKER_SECRETARY, 15,
	CREATURE_TEENAGER, 5,
	CREATURE_COP, 5,
	CREATURE_JUDGE_LIBERAL, 1,
	CREATURE_JUDGE_CONSERVATIVE, 1,
	CREATURE_AGENT, 1,
	CREATURE_RADIOPERSONALITY, 1,
	CREATURE_NEWSANCHOR, 1,
	CREATURE_MILITARYOFFICER, 1,
	CREATURE_LAWYER, 5,
	CREATURE_DOCTOR, 5,
	CREATURE_PSYCHOLOGIST, 1,
	CREATURE_NURSE, 5,
	CREATURE_SEWERWORKER, 1,
	CREATURE_COLLEGESTUDENT, 30,
	CREATURE_MUSICIAN, 5,
	CREATURE_MATHEMATICIAN, 5,
	CREATURE_TEACHER, 5,
	CREATURE_HSDROPOUT, 1,
	CREATURE_BUM, 1,
	CREATURE_GANGMEMBER, 1,
	CREATURE_CRACKHEAD, 1,
	CREATURE_PRIEST, 1,
	CREATURE_ENGINEER, 5,
	CREATURE_FASTFOODWORKER, 5,
	CREATURE_BAKER, 1,
	CREATURE_BARISTA, 10,
	CREATURE_BARTENDER, 1,
	CREATURE_TELEMARKETER, 5,
	CREATURE_CARSALESMAN, 3,
	CREATURE_OFFICEWORKER, 10,
	CREATURE_FOOTBALLCOACH, 1,
	CREATURE_PROSTITUTE, 1,
	CREATURE_MAILMAN, 1,
	CREATURE_GARBAGEMAN, 1,
	CREATURE_PLUMBER, 1,
	CREATURE_CHEF, 1,
	CREATURE_CONSTRUCTIONWORKER, 3,
	CREATURE_AMATEURMAGICIAN, 1,
	CREATURE_MERC, 1,
	CREATURE_SOLDIER, 1,
	CREATURE_VETERAN, 3,
	CREATURE_HIPPIE, 1,
	CREATURE_CRITIC_ART, 1,
	CREATURE_CRITIC_MUSIC, 1,
	CREATURE_AUTHOR, 1,
	CREATURE_JOURNALIST, 1,
	CREATURE_SOCIALITE, 1,
	CREATURE_BIKER, 1,
	CREATURE_TRUCKER, 1,
	CREATURE_TAXIDRIVER, 1,
	CREATURE_PROGRAMMER, 5,
	CREATURE_RETIREE, 3,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_DANCER, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_CAMERAMAN, 1,
	CREATURE_HAIRSTYLIST, 1,
	CREATURE_FASHIONDESIGNER, 1,
	CREATURE_CLERK, 1,
	CREATURE_THIEF, 1,
	CREATURE_ACTOR, 1,
	CREATURE_YOGAINSTRUCTOR, 1,
	CREATURE_MARTIALARTIST, 1,
	CREATURE_ATHLETE, 1,
	CREATURE_FIREFIGHTER, 1,
	CREATURE_LOCKSMITH, 1 }
	),
	map<int, vector<int> >::value_type(SITE_BUSINESS_LATTESTAND,{
	CREATURE_SECURITYGUARD, 5,
	CREATURE_SCIENTIST_LABTECH, 10,
	CREATURE_SCIENTIST_EMINENT, 1,
	CREATURE_CORPORATE_MANAGER, 10,
	CREATURE_WORKER_JANITOR, 5,
	CREATURE_WORKER_SECRETARY, 15,
	CREATURE_TEENAGER, 5,
	CREATURE_COP, 5,
	CREATURE_JUDGE_LIBERAL, 1,
	CREATURE_JUDGE_CONSERVATIVE, 1,
	CREATURE_AGENT, 1,
	CREATURE_RADIOPERSONALITY, 1,
	CREATURE_NEWSANCHOR, 1,
	CREATURE_MILITARYOFFICER, 1,
	CREATURE_LAWYER, 5,
	CREATURE_DOCTOR, 5,
	CREATURE_PSYCHOLOGIST, 1,
	CREATURE_NURSE, 5,
	CREATURE_SEWERWORKER, 1,
	CREATURE_COLLEGESTUDENT, 30,
	CREATURE_MUSICIAN, 5,
	CREATURE_MATHEMATICIAN, 5,
	CREATURE_TEACHER, 5,
	CREATURE_HSDROPOUT, 1,
	CREATURE_BUM, 1,
	CREATURE_GANGMEMBER, 1,
	CREATURE_CRACKHEAD, 1,
	CREATURE_PRIEST, 1,
	CREATURE_ENGINEER, 5,
	CREATURE_FASTFOODWORKER, 5,
	CREATURE_BAKER, 1,
	CREATURE_BARISTA, 10,
	CREATURE_BARTENDER, 1,
	CREATURE_TELEMARKETER, 5,
	CREATURE_CARSALESMAN, 3,
	CREATURE_OFFICEWORKER, 10,
	CREATURE_FOOTBALLCOACH, 1,
	CREATURE_PROSTITUTE, 1,
	CREATURE_MAILMAN, 1,
	CREATURE_GARBAGEMAN, 1,
	CREATURE_PLUMBER, 1,
	CREATURE_CHEF, 1,
	CREATURE_CONSTRUCTIONWORKER, 3,
	CREATURE_AMATEURMAGICIAN, 1,
	CREATURE_MERC, 1,
	CREATURE_SOLDIER, 1,
	CREATURE_VETERAN, 3,
	CREATURE_HIPPIE, 1,
	CREATURE_CRITIC_ART, 1,
	CREATURE_CRITIC_MUSIC, 1,
	CREATURE_AUTHOR, 1,
	CREATURE_JOURNALIST, 1,
	CREATURE_SOCIALITE, 1,
	CREATURE_BIKER, 1,
	CREATURE_TRUCKER, 1,
	CREATURE_TAXIDRIVER, 1,
	CREATURE_PROGRAMMER, 5,
	CREATURE_RETIREE, 3,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_DANCER, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_CAMERAMAN, 1,
	CREATURE_HAIRSTYLIST, 1,
	CREATURE_FASHIONDESIGNER, 1,
	CREATURE_CLERK, 1,
	CREATURE_THIEF, 1,
	CREATURE_ACTOR, 1,
	CREATURE_YOGAINSTRUCTOR, 1,
	CREATURE_MARTIALARTIST, 1,
	CREATURE_ATHLETE, 1,
	CREATURE_FIREFIGHTER, 1,
	CREATURE_LOCKSMITH, 1 }
	),
	map<int, vector<int> >::value_type(SITE_BUSINESS_VEGANCOOP,{
	CREATURE_TEENAGER, 5,
	CREATURE_JUDGE_LIBERAL, 1,
	CREATURE_COLLEGESTUDENT, 50,
	CREATURE_MUSICIAN, 20,
	CREATURE_MATHEMATICIAN, 1,
	CREATURE_TEACHER, 1,
	CREATURE_HSDROPOUT, 10,
	CREATURE_BUM, 1,
	CREATURE_HIPPIE, 50,
	CREATURE_CRITIC_ART, 1,
	CREATURE_CRITIC_MUSIC, 1,
	CREATURE_AUTHOR, 1,
	CREATURE_JOURNALIST, 1,
	CREATURE_RETIREE, 1,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_DANCER, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_YOGAINSTRUCTOR, 2 }
	),
	map<int, vector<int> >::value_type(SITE_BUSINESS_INTERNETCAFE,{
	CREATURE_SCIENTIST_LABTECH, 5,
	CREATURE_CORPORATE_MANAGER, 3,
	CREATURE_TEENAGER, 15,
	CREATURE_LAWYER, 3,
	CREATURE_COLLEGESTUDENT, 25,
	CREATURE_MUSICIAN, 2,
	CREATURE_MATHEMATICIAN, 1,
	CREATURE_TEACHER, 5,
	CREATURE_ENGINEER, 15,
	CREATURE_DOCTOR, 1,
	CREATURE_BARISTA, 10,
	CREATURE_CARSALESMAN, 3,
	CREATURE_OFFICEWORKER, 15,
	CREATURE_WORKER_SECRETARY, 5,
	CREATURE_HIPPIE, 1,
	CREATURE_PROGRAMMER, 15,
	CREATURE_RETIREE, 5,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_DANCER, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_CAMERAMAN, 1,
	CREATURE_CLERK, 1,
	CREATURE_LOCKSMITH, 1 }
	),
	map<int, vector<int> >::value_type(SITE_RESIDENTIAL_SHELTER,{
	CREATURE_WORKER_JANITOR, 5,
	CREATURE_TEENAGER, 20,
	CREATURE_MUSICIAN, 3,
	CREATURE_MATHEMATICIAN, 1,
	CREATURE_BUM, 200,
	CREATURE_GANGMEMBER, 5,
	CREATURE_CRACKHEAD, 50,
	CREATURE_PROSTITUTE, 10,
	CREATURE_AMATEURMAGICIAN, 1,
	CREATURE_HIPPIE, 1,
	CREATURE_NURSE, 5,
	CREATURE_BIKER, 1,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_DANCER, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_THIEF, 5,
	CREATURE_ACTOR, 1, }
	),
	map<int, vector<int> >::value_type(SITE_RESIDENTIAL_TENEMENT,{
	CREATURE_SECURITYGUARD, 1,
	CREATURE_SCIENTIST_LABTECH, 1,
	CREATURE_WORKER_JANITOR, 3,
	CREATURE_WORKER_SECRETARY, 2,
	CREATURE_TEENAGER, 5,
	CREATURE_SEWERWORKER, 1,
	CREATURE_COLLEGESTUDENT, 1,
	CREATURE_MUSICIAN, 1,
	CREATURE_MATHEMATICIAN, 1,
	CREATURE_TEACHER, 1,
	CREATURE_HSDROPOUT, 3,
	CREATURE_BUM, 3,
	CREATURE_GANGMEMBER, 3,
	CREATURE_CRACKHEAD, 3,
	CREATURE_FASTFOODWORKER, 1,
	CREATURE_BARISTA, 1,
	CREATURE_BARTENDER, 1,
	CREATURE_TELEMARKETER, 1,
	CREATURE_CARSALESMAN, 1,
	CREATURE_OFFICEWORKER, 1,
	CREATURE_PROSTITUTE, 3,
	CREATURE_MAILMAN, 1,
	CREATURE_GARBAGEMAN, 1,
	CREATURE_CONSTRUCTIONWORKER, 1,
	CREATURE_AMATEURMAGICIAN, 1,
	CREATURE_HICK, 1,
	CREATURE_SOLDIER, 1,
	CREATURE_VETERAN, 2,
	CREATURE_HIPPIE, 1,
	CREATURE_BIKER, 1,
	CREATURE_TAXIDRIVER, 1,
	CREATURE_RETIREE, 1,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_DANCER, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_HAIRSTYLIST, 1,
	CREATURE_CLERK, 1,
	CREATURE_THIEF, 1,
	CREATURE_ACTOR, 1,
	CREATURE_FIREFIGHTER, 1,
	CREATURE_LOCKSMITH, 1 }
	),
	map<int, vector<int> >::value_type(SITE_RESIDENTIAL_APARTMENT,{

	CREATURE_SECURITYGUARD, 1,
	CREATURE_SCIENTIST_LABTECH, 1,
	CREATURE_CORPORATE_MANAGER, 1,
	CREATURE_WORKER_JANITOR, 1,
	CREATURE_WORKER_SECRETARY, 1,
	CREATURE_TEENAGER, 3,
	CREATURE_COP, 1,
	CREATURE_LAWYER, 1,
	CREATURE_SEWERWORKER, 1,
	CREATURE_COLLEGESTUDENT, 1,
	CREATURE_MUSICIAN, 1,
	CREATURE_MATHEMATICIAN, 1,
	CREATURE_TEACHER, 1,
	CREATURE_PRIEST, 1,
	CREATURE_ENGINEER, 1,
	CREATURE_FASTFOODWORKER, 1,
	CREATURE_BAKER, 1,
	CREATURE_BARISTA, 1,
	CREATURE_BARTENDER, 1,
	CREATURE_TELEMARKETER, 1,
	CREATURE_CARSALESMAN, 1,
	CREATURE_OFFICEWORKER, 1,
	CREATURE_FOOTBALLCOACH, 1,
	CREATURE_MAILMAN, 1,
	CREATURE_DOCTOR, 1,
	CREATURE_PSYCHOLOGIST, 1,
	CREATURE_NURSE, 1,
	CREATURE_GARBAGEMAN, 1,
	CREATURE_PLUMBER, 1,
	CREATURE_CHEF, 1,
	CREATURE_CONSTRUCTIONWORKER, 1,
	CREATURE_AMATEURMAGICIAN, 1,
	CREATURE_SOLDIER, 1,
	CREATURE_VETERAN, 2,
	CREATURE_HIPPIE, 1,
	CREATURE_CRITIC_ART, 1,
	CREATURE_CRITIC_MUSIC, 1,
	CREATURE_AUTHOR, 1,
	CREATURE_JOURNALIST, 1,
	CREATURE_TAXIDRIVER, 1,
	CREATURE_PROGRAMMER, 1,
	CREATURE_RETIREE, 1,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_DANCER, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_CAMERAMAN, 1,
	CREATURE_HAIRSTYLIST, 1,
	CREATURE_CLERK, 1,
	CREATURE_THIEF, 1,
	CREATURE_ACTOR, 1,
	CREATURE_YOGAINSTRUCTOR, 1,
	CREATURE_MARTIALARTIST, 1,
	CREATURE_ATHLETE, 1,
	CREATURE_FIREFIGHTER, 1,
	CREATURE_LOCKSMITH, 1 }
	),
	map<int, vector<int> >::value_type(SITE_RESIDENTIAL_APARTMENT_UPSCALE,{
	CREATURE_SCIENTIST_EMINENT, 1,
	CREATURE_CORPORATE_MANAGER, 5,
	CREATURE_WORKER_JANITOR, 5,
	CREATURE_WORKER_SECRETARY, 1,
	CREATURE_TEENAGER, 3,
	CREATURE_JUDGE_LIBERAL, 1,
	CREATURE_JUDGE_CONSERVATIVE, 1,
	CREATURE_RADIOPERSONALITY, 1,
	CREATURE_NEWSANCHOR, 1,
	CREATURE_LAWYER, 5,
	CREATURE_DOCTOR, 5,
	CREATURE_PSYCHOLOGIST, 1,
	CREATURE_NURSE, 1,
	CREATURE_COLLEGESTUDENT, 1,
	CREATURE_MUSICIAN, 1,
	CREATURE_PROSTITUTE, 3,
	CREATURE_MAILMAN, 1,
	CREATURE_CRITIC_ART, 1,
	CREATURE_CRITIC_MUSIC, 1,
	CREATURE_AUTHOR, 1,
	CREATURE_JOURNALIST, 1,
	CREATURE_SOCIALITE, 2,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_DANCER, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_FASHIONDESIGNER, 1,
	CREATURE_THIEF, 1,
	CREATURE_ACTOR, 1,
	CREATURE_ATHLETE, 1,
	CREATURE_LOCKSMITH, 1 }
	),
	map<int, vector<int> >::value_type(SITE_LABORATORY_COSMETICS,{
	CREATURE_SCIENTIST_LABTECH, 10,
	CREATURE_SCIENTIST_EMINENT, 1,
	CREATURE_CORPORATE_MANAGER, 1,
	CREATURE_WORKER_JANITOR, 10,
	CREATURE_WORKER_SECRETARY, 10,
	CREATURE_OFFICEWORKER, 10 }
	),
	map<int, vector<int> >::value_type(SITE_INDUSTRY_NUCLEAR,{
	CREATURE_SCIENTIST_LABTECH, 10,
	CREATURE_SCIENTIST_EMINENT, 1,
	CREATURE_CORPORATE_MANAGER, 1,
	CREATURE_WORKER_JANITOR, 10,
	CREATURE_WORKER_SECRETARY, 10,
	CREATURE_OFFICEWORKER, 10 }
	),
	map<int, vector<int> >::value_type(SITE_LABORATORY_GENETIC,{
	CREATURE_SCIENTIST_LABTECH, 10,
	CREATURE_SCIENTIST_EMINENT, 1,
	CREATURE_CORPORATE_MANAGER, 1,
	CREATURE_DOCTOR, 1,
	CREATURE_WORKER_JANITOR, 10,
	CREATURE_WORKER_SECRETARY, 10,
	CREATURE_OFFICEWORKER, 10 }
	),
	map<int, vector<int> >::value_type(SITE_GOVERNMENT_POLICESTATION,{
	CREATURE_SCIENTIST_LABTECH, 1,
	CREATURE_CORPORATE_MANAGER, 1,
	CREATURE_WORKER_JANITOR, 50,
	CREATURE_WORKER_SECRETARY, 1,
	CREATURE_TEENAGER, 5,
	CREATURE_JUDGE_LIBERAL, 1,
	CREATURE_JUDGE_CONSERVATIVE, 1,
	CREATURE_AGENT, 1,
	CREATURE_RADIOPERSONALITY, 1,
	CREATURE_NEWSANCHOR, 1,
	CREATURE_MILITARYOFFICER, 1,
	CREATURE_LAWYER, 1,
	CREATURE_DOCTOR, 1,
	CREATURE_PSYCHOLOGIST, 1,
	CREATURE_NURSE, 1,
	CREATURE_SEWERWORKER, 1,
	CREATURE_COLLEGESTUDENT, 1,
	CREATURE_MUSICIAN, 1,
	CREATURE_MATHEMATICIAN, 1,
	CREATURE_TEACHER, 1,
	CREATURE_HSDROPOUT, 10,
	CREATURE_BUM, 10,
	CREATURE_GANGMEMBER, 10,
	CREATURE_CRACKHEAD, 10,
	CREATURE_PRIEST, 5,
	CREATURE_ENGINEER, 1,
	CREATURE_FASTFOODWORKER, 1,
	CREATURE_BAKER, 1,
	CREATURE_BARISTA, 1,
	CREATURE_BARTENDER, 1,
	CREATURE_TELEMARKETER, 1,
	CREATURE_CARSALESMAN, 1,
	CREATURE_OFFICEWORKER, 1,
	CREATURE_FOOTBALLCOACH, 1,
	CREATURE_PROSTITUTE, 10,
	CREATURE_MAILMAN, 1,
	CREATURE_GARBAGEMAN, 1,
	CREATURE_PLUMBER, 1,
	CREATURE_CHEF, 1,
	CREATURE_CONSTRUCTIONWORKER, 1,
	CREATURE_AMATEURMAGICIAN, 1,
	CREATURE_HICK, 1,
	CREATURE_SOLDIER, 1,
	CREATURE_VETERAN, 2,
	CREATURE_HIPPIE, 1,
	CREATURE_CRITIC_ART, 1,
	CREATURE_CRITIC_MUSIC, 1,
	CREATURE_AUTHOR, 1,
	CREATURE_JOURNALIST, 1,
	CREATURE_SOCIALITE, 1,
	CREATURE_BIKER, 5,
	CREATURE_TRUCKER, 1,
	CREATURE_TAXIDRIVER, 1,
	CREATURE_PROGRAMMER, 1,
	CREATURE_NUN, 1,
	CREATURE_RETIREE, 1,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_DANCER, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_CAMERAMAN, 1,
	CREATURE_HAIRSTYLIST, 1,
	CREATURE_FASHIONDESIGNER, 1,
	CREATURE_CLERK, 1,
	CREATURE_THIEF, 10,
	CREATURE_ACTOR, 1,
	CREATURE_YOGAINSTRUCTOR, 1,
	CREATURE_MARTIALARTIST, 1,
	CREATURE_ATHLETE, 1,
	CREATURE_LOCKSMITH, 5 }       //Forensic locksmiths
	),
	map<int, vector<int> >::value_type(SITE_GOVERNMENT_COURTHOUSE,{
	CREATURE_SCIENTIST_LABTECH, 1,
	CREATURE_SCIENTIST_EMINENT, 1,
	CREATURE_CORPORATE_MANAGER, 1,
	CREATURE_WORKER_JANITOR, 50,
	CREATURE_WORKER_SECRETARY, 50,
	CREATURE_TEENAGER, 1,
	CREATURE_JUDGE_LIBERAL, 20,
	CREATURE_JUDGE_CONSERVATIVE, 20,
	CREATURE_AGENT, 1,
	CREATURE_RADIOPERSONALITY, 1,
	CREATURE_NEWSANCHOR, 1,
	CREATURE_MILITARYOFFICER, 1,
	CREATURE_LAWYER, 200,
	CREATURE_PSYCHOLOGIST, 20,
	CREATURE_SEWERWORKER, 1,
	CREATURE_COLLEGESTUDENT, 1,
	CREATURE_MUSICIAN, 1,
	CREATURE_MATHEMATICIAN, 1,
	CREATURE_TEACHER, 1,
	CREATURE_HSDROPOUT, 1,
	CREATURE_BUM, 1,
	CREATURE_GANGMEMBER, 1,
	CREATURE_CRACKHEAD, 1,
	CREATURE_PRIEST, 1,
	CREATURE_ENGINEER, 1,
	CREATURE_FASTFOODWORKER, 1,
	CREATURE_BAKER, 1,
	CREATURE_BARISTA, 1,
	CREATURE_BARTENDER, 1,
	CREATURE_TELEMARKETER, 1,
	CREATURE_CARSALESMAN, 2,
	CREATURE_OFFICEWORKER, 50,
	CREATURE_FOOTBALLCOACH, 1,
	CREATURE_PROSTITUTE, 1,
	CREATURE_MAILMAN, 1,
	CREATURE_GARBAGEMAN, 1,
	CREATURE_PLUMBER, 1,
	CREATURE_CHEF, 1,
	CREATURE_CONSTRUCTIONWORKER, 1,
	CREATURE_AMATEURMAGICIAN, 1,
	CREATURE_HICK, 1,
	CREATURE_SOLDIER, 1,
	CREATURE_VETERAN, 2,
	CREATURE_HIPPIE, 1,
	CREATURE_CRITIC_ART, 1,
	CREATURE_CRITIC_MUSIC, 1,
	CREATURE_AUTHOR, 1,
	CREATURE_JOURNALIST, 1,
	CREATURE_SOCIALITE, 1,
	CREATURE_BIKER, 1,
	CREATURE_TRUCKER, 1,
	CREATURE_TAXIDRIVER, 1,
	CREATURE_PROGRAMMER, 1,
	CREATURE_NUN, 1,
	CREATURE_RETIREE, 1,
	CREATURE_PAINTER, 1,
	CREATURE_SCULPTOR, 1,
	CREATURE_DANCER, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_CAMERAMAN, 1,
	CREATURE_HAIRSTYLIST, 1,
	CREATURE_FASHIONDESIGNER, 1,
	CREATURE_CLERK, 1,
	CREATURE_THIEF, 3,
	CREATURE_ACTOR, 1,
	CREATURE_YOGAINSTRUCTOR, 1,
	CREATURE_MARTIALARTIST, 1,
	CREATURE_ATHLETE, 1,
	CREATURE_LOCKSMITH, 5 }
	),
	map<int, vector<int> >::value_type(SITE_GOVERNMENT_FIRESTATION,{
	CREATURE_WORKER_JANITOR, 5,
	CREATURE_WORKER_SECRETARY, 2,
	CREATURE_NURSE, 2,
	CREATURE_PRIEST, 5,
	CREATURE_JOURNALIST, 1,
	CREATURE_PHOTOGRAPHER, 1,
	CREATURE_FIREFIGHTER, 100 }
	),
	map<int, vector<int> >::value_type(SITE_GOVERNMENT_INTELLIGENCEHQ,{
	CREATURE_WORKER_JANITOR, 50,
	CREATURE_WORKER_SECRETARY, 50,
	CREATURE_GUARDDOG, 50,
	CREATURE_MATHEMATICIAN, 5,
	CREATURE_PROGRAMMER, 5,
	CREATURE_MILITARYOFFICER, 5 }


	),
	map<int, vector<int> >::value_type(SITE_GOVERNMENT_ARMYBASE,{
	CREATURE_SOLDIER, 750,
	CREATURE_GUARDDOG, 20,
	CREATURE_MILITARYPOLICE, 100,
	CREATURE_MILITARYOFFICER, 20,
	CREATURE_SEAL, 20 }


	),
	map<int, vector<int> >::value_type(SITE_INDUSTRY_SWEATSHOP,{
	CREATURE_CORPORATE_MANAGER, 5,
	CREATURE_WORKER_SWEATSHOP, 800 }

	),
	map<int, vector<int> >::value_type(SITE_INDUSTRY_POLLUTER,{
	CREATURE_CORPORATE_MANAGER, 1,
	CREATURE_WORKER_JANITOR, 10,
	CREATURE_WORKER_SECRETARY, 10 }
	),
	map<int, vector<int> >::value_type(SITE_CORPORATE_HEADQUARTERS,{

	CREATURE_CORPORATE_MANAGER, 20,
	CREATURE_WORKER_JANITOR, 20,
	CREATURE_WORKER_SECRETARY, 40,
	CREATURE_JUDGE_CONSERVATIVE, 1,
	CREATURE_LAWYER, 20,
	CREATURE_PRIEST, 1,
	CREATURE_OFFICEWORKER, 80,
	CREATURE_PROSTITUTE, 1 }


	),
	map<int, vector<int> >::value_type(SITE_CORPORATE_HOUSE,{
	CREATURE_WORKER_SERVANT, 30,
	CREATURE_WORKER_SECRETARY, 5,
	CREATURE_TEENAGER, 5,
	CREATURE_GENETIC, 1,
	CREATURE_LAWYER, 5,
	CREATURE_PRIEST, 1,
	CREATURE_PROSTITUTE, 1 }

	),
	map<int, vector<int> >::value_type(SITE_MEDIA_AMRADIO,{
	CREATURE_CORPORATE_MANAGER, 2,
	CREATURE_WORKER_JANITOR, 10,
	CREATURE_WORKER_SECRETARY, 10,
	CREATURE_RADIOPERSONALITY, 2,
	CREATURE_ENGINEER, 20,
	CREATURE_OFFICEWORKER, 40 }


	),
	map<int, vector<int> >::value_type(SITE_MEDIA_CABLENEWS,{
	CREATURE_CORPORATE_MANAGER, 5,
	CREATURE_WORKER_JANITOR, 20,
	CREATURE_WORKER_SECRETARY, 20,
	CREATURE_NEWSANCHOR, 2,
	CREATURE_ENGINEER, 40,
	CREATURE_OFFICEWORKER, 40,
	CREATURE_PHOTOGRAPHER, 5,
	CREATURE_CAMERAMAN, 5 }

	)
};
short getCurrentSite();
bool populateEncounter(const int type, int creaturearray[CREATURENUM], const char sec);
void conservatiseEncslot(const int encslot);
void conservatise(const int c);
void damage_creature(const int e);
vector<NameAndAlignment> getEncounterNameAndAlignment();
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

#endif	//NEWENCOUNTER_CPP
#ifdef	NEWGAME_CPP
// newgame.cpp

#include "../creature/creature.h"
#include "../locations/locations.h"

#include "../common/ledgerEnums.h"
#include "../common/ledger.h"

#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"

//#include "../common/consolesupport.h"
// for getkey

#include "../log/log.h"

#include "../common/stringconversion.h"
//for string attribute_enum_to_string(int)

#include "../common/getnames.h"
// for cityname

#include "../common/translateid.h"
// for  getarmortype

#include "../cursesAlternative.h"
#include "../set_color_support.h"

#include "../common/creaturePoolCreature.h"

#include "../common/musicClass.h"



vector<string> founderQuestions;

#include "../customMaps.h"
vector<file_and_text_collection> newgame_file_collection = {
	/*newgame.cpp*/
	customText(&founderQuestions, "newgame\\founderQuestions.txt"),
};
map<string, short> getSkillEnumFromString;
map<short, string> enumToCreature;
map<string, short> getBaseEnumFromString;
map<string, short> getSpecialWoundEnumFromString;

extern bool ALLOWSTALIN;
extern bool BLIND;
extern bool INTERNAL;
extern bool multipleCityMode;
extern bool nocourtpurge;
extern bool NOFACE;
extern bool notermlimit;           //These determine if ELAs can take place --kviiri
extern bool NOWALK;
extern bool SPINE;
extern bool stalinmode;
extern char courtname[COURTNUM][POLITICIAN_NAMELEN];
extern char endgamestate;
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern char lcityname[CITY_NAMELEN];
extern class Ledger ledger;
extern int day;
extern int month;
extern int year;
extern Log gamelog;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short court[COURTNUM];
extern short fieldskillrate;
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short senate[SENATENUM];
extern short wincondition;
extern UniqueCreatures uniqueCreatures;
extern vector<ClipType *> cliptype;
extern vector<WeaponType *> weapontype;

Vehicle* newSportsCar();

enum LOOP_CONTINUATION {
	RETURN_ZERO,
	RETURN_ONE,
	REPEAT
};

void newVehicle(Vehicle *startcar);
enum Stat_Or_Attribute {
	SKILL,
	ATTRIBUTE,
	OTHER
};
enum Other_Influence {
	BIRTH_MONTH,
	BIRTH_DAY,
	BIRTH_YEAR,
	STARTING_MONTH,
	STARTING_DAY,
	STARTING_YEAR,
	GAY,
	DATING_LAWYER,
	DATING,
	HAS_MAPS,
	JUICE,
	SPORTS_CAR,
	ASSAULT_RIFLE,
	MONEY,
	BASE,
	CREATURE,
	ARMOR,
	RECRUITS
};
struct MutableImpact {
	Stat_Or_Attribute type;
	int item_to_influence;
	int magnitude;
	bool set_value;
};

struct Impact {
	const Stat_Or_Attribute type;
	const int item_to_influence;
	const int magnitude;
	const bool set_value;
	Impact(MutableImpact i) : type(i.type), item_to_influence(i.item_to_influence), magnitude(i.magnitude), set_value(i.set_value) {}
};
struct MutableChoice {
	string ANSWER;
	string ANSWER_2;
	vector<Impact> impact;
};
struct Choice {
	const string ANSWER;
	const string ANSWER_2;
	const vector<Impact> impact;
	Choice(MutableChoice c) : ANSWER(c.ANSWER), ANSWER_2(c.ANSWER_2), impact(c.impact) {}
};
struct MutableQuestion {
	string HEADER;
	string HEADER_2;
	string QUESTION;
	string QUESTION_2;
	vector<Choice> choices;
};
struct Question {

	const string HEADER;
	const string HEADER_2;
	const string QUESTION;
	const string QUESTION_2;
	const vector<Choice> choices;
	Question(MutableQuestion q) : HEADER(q.HEADER), HEADER_2(q.HEADER_2), QUESTION(q.QUESTION), QUESTION_2(q.QUESTION_2), choices(q.choices) {}
};
enum founderQuestionTagEnums {
	ENUM_tag_HEADER,
	ENUM_tag_ANSWER,
	ENUM_tag_QUESTION,
	ENUM_tag_SKILL_,
	ENUM_tag_ATTRIBUTE_,
	ENUM_tag_STARTING_,
	ENUM_tag_BIRTHDAY_,
	ENUM_tag_MONEY,
	ENUM_tag_DATING_LAWYER,
	ENUM_tag_GAY,
	ENUM_tag_HASMAPS,
	ENUM_tag_CREATURE,
	ENUM_tag_BASE,
	ENUM_tag_ARMOR,
	ENUM_tag_JUICE,
	ENUM_tag_RECRUITS_GANG,
	ENUM_tag_ASSAULT_RIFLE,
	ENUM_tag_SPORTS_CAR,
};

const int MAX_CHOICES = 10;

#include "../recruits.h"
/* creates your founder */
struct newGameArguments {
	const char recruits;
	const char base;
	const bool makelawyer;
	const bool gaylawyer;
	const bool sports_car;
	newGameArguments(char _recruits, char _base, bool _makelawyer, bool _gaylawyer, bool _sports_car) : recruits(_recruits), base(_base), makelawyer(_makelawyer), gaylawyer(_gaylawyer), sports_car(_sports_car) {}
};
const string ALL_OPTIONS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string pressBtoBeReborn = " (Press B to be born to a different family)";
const string pressCtoChangeSex = " (Press C to change your sex at birth)";
const string history = "HISTORY: ";
const string letMeChoose = "Let Me Choose";
const string letFateDecide = "Let Fate Decide";
const string pressDtoToggle = " (Press D to toggle childhood)";
const string pressEtoRelocate = " (Press E to relocate)";
const string sexIs = "SEX: ";
const string male = "Male";
const string female = "Female";
const string itsComplicated = "It's Complicated";
const string theFounder = "The Founder of the Liberal Crime Squad";
const string firstName = "FIRST NAME: ";
const string pressAtoReconsider = " (Press A to have your parents reconsider)";
const string lastName = "LAST NAME: ";
const string theDocSaid = "The doctor said I was ";
const string aBoy = "a boy";
const string aGirl = "a girl";
const string intersex = "an intersex baby";
const string myParents = "My parents ";
const string insistedOtherwise = "insisted otherwise.";
const string they = "They ";
const string namedMe = "named me ";
const string A_NEW_CON_ERA = "A NEW CONSERVATIVE ERA";
const string theYearIs = "The Year is ";
const string CONSERVATIVE_PRESIDENT = "Conservative President ";
const string endsSecondTerm = " ends his second term with approval";
const string highSeventiesApprovePres = "ratings in the high 70s, and is succeeded by hardcore Arch-Conservative";
const string WITH_CONSERVATIVES_SWEEPING_INTO_POWER = "With Conservatives sweeping into power in the House of Representatives";
const string senateConMajority = "and Senate, and a Conservative majority in the Supreme Court of the";
const string US_HAILING_BEGINNING_OF_A_NEW = "United States, commentators are hailing it as the beginning of a new";
const string conEra = "Conservative era.";
const string thePresident = "President ";
const string hasAskedCongressBeQuick = " has asked the new Congress to move quickly";
const string rubberStampArchCon = "to rubber stamp his radical Arch-Conservative agenda. ";
const string theLeftSeems = "The left seems";
const string powerlessToStop = "powerless to stop this imminent trampling of Liberal Sanity and Justice.";
const string inThisDarkTime = "In this dark time, the Liberal Crime Squad is born...";
const string unSelected = "[ ]";
const string isSelected = "[X]";
const string newGameAdvanced = "New Game of Liberal Crime Squad: Advanced Gameplay Options";
const string A_CLASSIC_MODE = " A - Classic Mode: No Conservative Crime Squad.";
const string B_CCS_STARTS_ACTIVE_AND_STRONG = " B - We Didn't Start The Fire: The CCS starts active and extremely strong.";
const string C_NIGHTMARE_MODE = " C - Nightmare Mode: Liberalism is forgotten. Is it too late to fight back?";
const string d_nationalLCS = " D - National LCS: Advanced play across multiple cities.";
const string e_marathonMode = " E - Marathon Mode: Prevent Liberals from amending the Constitution.";
const string f_stalinistMode = " F - Stalinist Mode: Enable Stalinist Comrade Squad (not fully implemented).";
const string newGameYourAgenda = "New Game of Liberal Crime Squad: Your Agenda";
const string A_NO_COMPROMISE = " A - No Compromise Classic - I will make all our laws Elite Liberal!";
const string B_DEMOCRAT_MODE = " B - Democrat Mode - Most laws must be Elite Liberal, some can be Liberal.";
const string newGameFieldLearn = "New Game of Liberal Crime Squad: Field Learning";
const string AFFECTS_THESE_SKILLS = "(affects Security, Stealth, Disguise, & Driving)";
const string A_FAST_SKILLS = " A - Fast skills - Grinding is Conservative!";
const string B_CLASSIC_EXCELLENCE_REQUIRES_PRACTICE = " B - Classic - Excellence requires practice.";
const string C_HARD_MODE = " C - Hard Mode - Learn from the best, or face arrest!";
const string notCreature = "Not a creature";
const string notValidMap = "Not a valid mappable site";
const string notSpecialWound = "Not a special wound";
const string notASkill = "Not a skill";
const string notAnAttribute = "Not an attribute";
const string tag_CLIP = "CLIP";
const string tag_CLIP_ASSAULT = "CLIP_ASSAULT";
const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_AUTORIFLE_AK47 = "WEAPON_AUTORIFLE_AK47";
const string tag_SPORTS_CAR = "SPORTS_CAR";
const string tag_ASSAULT_RIFLE = "ASSAULT_RIFLE";
const string tag_RECRUITS_GANG = "RECRUITS_GANG";
const string tag_JUICE = "JUICE";
const string tag_ARMOR = "ARMOR";
const string tag_B = "B";
const string tag_BASE = "BASE";
const string tag_CREATURE = "CREATURE";
const string tag_HASMAPS = "HASMAPS";
const string tag_GAY = "GAY";
const string tag_D = "D";
const string tag_DATING_LAWYER = "DATING_LAWYER";
const string tag_MONEY = "MONEY";
const string tag_YEAR = "YEAR";
const string tag_Y = "Y";
const string tag_DAY = "DAY";
const string tag_MONTH = "MONTH";
const string tag_BIRTHDAY_ = "BIRTHDAY_";
const string tag_STARTING_ = "STARTING_";
const string tag_ATTRIBUTE_ = "ATTRIBUTE_";
const string tag_SKILL_ = "SKILL_";
const string tag__2 = "_2";
const string tag_QUESTION = "QUESTION";
const string tag_ANSWER = "ANSWER";
const string tag_HEADER = "HEADER";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
map<string, int> founderQuestionTags = {
	map<string, int>::value_type(tag_HEADER, ENUM_tag_HEADER),
	map<string, int>::value_type(tag_ANSWER, ENUM_tag_ANSWER),
	map<string, int>::value_type(tag_QUESTION, ENUM_tag_QUESTION),
	map<string, int>::value_type(tag_SKILL_, ENUM_tag_SKILL_),
	map<string, int>::value_type(tag_ATTRIBUTE_, ENUM_tag_ATTRIBUTE_),
	map<string, int>::value_type(tag_STARTING_, ENUM_tag_STARTING_),
	map<string, int>::value_type(tag_BIRTHDAY_, ENUM_tag_BIRTHDAY_),
	map<string, int>::value_type(tag_MONEY, ENUM_tag_MONEY),
	map<string, int>::value_type(tag_DATING_LAWYER, ENUM_tag_DATING_LAWYER),
	map<string, int>::value_type(tag_GAY, ENUM_tag_GAY),
	map<string, int>::value_type(tag_HASMAPS, ENUM_tag_HASMAPS),
	map<string, int>::value_type(tag_CREATURE, ENUM_tag_CREATURE),
	map<string, int>::value_type(tag_BASE, ENUM_tag_BASE),
	map<string, int>::value_type(tag_ARMOR, ENUM_tag_ARMOR),
	map<string, int>::value_type(tag_JUICE, ENUM_tag_JUICE),
	map<string, int>::value_type(tag_RECRUITS_GANG, ENUM_tag_RECRUITS_GANG),
	map<string, int>::value_type(tag_ASSAULT_RIFLE, ENUM_tag_ASSAULT_RIFLE),
	map<string, int>::value_type(tag_SPORTS_CAR, ENUM_tag_SPORTS_CAR),
};
void printErrorTypeOther(int ip);
void printWhatIsYourName();
#endif	//NEWGAME_CPP
#ifdef	NEWS_CPP
// news.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"
//#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../common/commonactions.h"
//#include "../common/stringconversion.h"
inline char* strcpy(char* dest, const std::string& src) { return strcpy(dest, src.c_str()); }
inline char* strcat(char* dest, const std::string& src) { return strcat(dest, src.c_str()); }
inline char* strcat(char* dest, long src) { return strcat(dest, tostring(src)); }
#include "../common/getnames.h"
#include "../common/misc.h"
// from cursesgraphics.h
#define CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_HORIZONTAL 0xc5
#define CH_FULL_BLOCK 0xdb
#define CH_LIGHT_SHADE 0xb0
#define CH_MEDIUM_SHADE 0xb1
#define CH_DARK_SHADE 0xb2
// from daily.h
int monthday();
#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include "../common/creaturePool.h"
#include "../locations/locationsPool.h"
#include "../cursesmovie.h"
vector<Deprecatednewsstoryst *> newsstory;
Deprecatednewsstoryst* lastNewsStory() {
	return newsstory[len(newsstory) - 1];
}
#include "../common/musicClass.h"

extern bool multipleCityMode;
extern CCSexposure ccsexposure;
extern char endgamestate;
extern char lcityname[CITY_NAMELEN];
extern char newscherrybusted;
extern char oldPresidentName[POLITICIAN_NAMELEN];
extern CursesMoviest movie;
extern int month;
extern int year;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short public_interest[VIEWNUM];
extern short senate[SENATENUM];
extern string slogan_str;
extern unsigned char bigletters[27][5][7][4];
extern unsigned char newspic[20][78][18][4];
extern unsigned char newstops[6][80][5][4];


map<short, vector<string> > newsStories;
map<short, string> cityNames;
vector<string> liberalCrime;
vector<string> AMorPM;
vector<string> book_title;
vector<string> book_title_2;
vector<string> random_nationality;
vector<string> conservative_oppose_book;
vector<string> radio_name;
vector<string> radio_name_2;
vector<string> vigilante_murder;
vector<string> why_chase_ended;
vector<string> crazy_conservative_act;
vector<string> bribe_officers;
vector<string> my_idol;
vector<string> prison_book_title;
vector<string> prison_book_title_2;
vector<string> mutilated_corpse;
vector<string> evidence_of_child_murder;
vector<string> break_in_murder_case;
vector<string> animal_research_country;
vector<string> drug_name;
vector<string> drug_name_2;
vector<string> chimp_drug_impact;
vector<string> chimp_drug_horror;
vector<string> terrorist_group;
vector<string> terrorist_plot;
vector<string> terrorist_plot_no_free_speech;
vector<string> gene_corp_name;
vector<string> gene_corp_name_2;
vector<string> gene_product_name;
vector<string> gene_product_name_2;
vector<string> gene_product_benefit;
vector<string> gene_product_cost;
vector<string> bullshit_no_free_speech;
vector<string> bullshit;
vector<string> petty_violence;
vector<string> his_her;
vector<string> older_younger;
vector<string> brother_sister;
vector<string> judge_with_prostitute;
vector<string> judge_with_prostitute_no_free_speech;
vector<string> judge_with_prostitute_full_free_speech;
vector<string> radio_host_crazy_quote;
vector<string> radio_host_lost_mind;
vector<string> family_values_company_name;
vector<string> family_values_company_name_2;
vector<string> family_values_company_name_3;
vector<string> pollution_consumption;
vector<string> pollution_consumption_2;
vector<string> i_like_polution;
vector<string> distrust_liberals;
vector<string> tech_giant_name;
vector<string> tech_giant_name_2;
vector<string> fm_radio_name;
vector<string> fm_radio_name_2;
vector<string> public_place;
vector<string> reagan_bad;
vector<string> reagan_bad_2;
vector<string> ceo_behaving_badly;
vector<string> reagan_good;
vector<string> reagan_good_2;
vector<string> cable_name;
vector<string> cable_name_2;
vector<string> cable_city;
vector<string> cable_city_2;
vector<string> ccs_adjective;
vector<string> ccs_adjective_2;
vector<string> ccs_adjective_3;
vector<string> ccs_noun;
vector<string> personalAds;
vector<string> personalAdsLG;
vector<string> caseNEWSSTORY_CCS_DEFEATED;
vector<string> caseNEWSSTORY_CCS_NOBACKERS;
vector<vector<string> > adListB;
vector<vector<string> > adList;
const int AD_LENGTH = 4;
#include "../customMaps.h"

void displaynewspicture(int p, int y);
void displaycenterednewsfont(const std::string& str, int y);
void preparepage(const Deprecatednewsstoryst ns, const bool liberalguardian);

const vector<int> randombox = {
	CH_LIGHT_SHADE,
	CH_MEDIUM_SHADE,
	CH_DARK_SHADE,
	CH_FULL_BLOCK,
	CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_HORIZONTAL,
	'*'
};
string sexdesc();
string sexwho();
string sexseek();
string sextype();

string constructeventstory(const short view, const char positive);

const int PICTURE_MUTANT_BEAST = 0;
const int PICTURE_CEO = 1;
const int PICTURE_BOOK = 2;
const int PICTURE_MELTDOWN = 3;
const int PICTURE_GENETICS = 4;
const int PICTURE_RIVERFIRE = 5;
const int PICTURE_DOLLARS = 6;
const int PICTURE_TINKYWINKY = 7;
const int PICTURE_OIL = 8;
const int PICTURE_TERRORISTS = 9;
const int PICTURE_KKK = 10;
const int PICTURE_TSHIRT = 11;

const string membersOfLCS = "Members of the Liberal Crime Squad ";
const string lcsSpokeseperson = "to a Liberal Crime Squad spokesperson.";
const string policeSpokesperson = "to a spokesperson from the police department.";
const string ACCORDING_TO_SOURCES = "  According to sources that were at the scene, ";
const string ACCORDING_TO_POLICE = "  According to police sources that were at the scene, ";
const string CONST_A_SPOKESPERSON_STATED_COMMA_QUOTE = "a spokesperson stated, \"";
const string CONST_HEARD_SAYING_COMMA_QUOTE = "heard saying, \"";
const string CONST_TWO_NIGHTS_AGO_DURING_RADIO = "two nights ago during the syndicated radio program \"";
const string CONST_HAD_COME_TO_EXPECT_WITH_ATTACKS_ON_LIBERAL_MEDIA = "had come to expect, with attacks on the \"liberal media establishment\"";
const string CONST_DOT_BUT_WHEN_THE_RADIO_ICON_SAID = "the \"elite liberal agenda\".  But when the radio icon said, \"";
const string CONST_COMMA_KNEW_THAT_QUOTE = ", knew that \"";
const string CONST_DOT_AFTER_THAT_IT_GOT_WORSE = ". After that, it just got worse and worse.\"";
const string CONST_SPACE_THE_SPOKESMAN_FURTHER_STATED = "  The spokesperson further stated, \"";
const string CONST_SCREAMED_FUCK_POLICE_AND_MORE = "screamed \"fuck the police those goddamn motherfuckers.  I got a fucking ticket this morning and I'm fucking pissed as shit.\"";
const string CONST_THE_SLOGAN = "  The slogan, \"";
const string CONST_ONE_UTTERED_THE_WORDS = "  One uttered the words, \"";
const string CONST_AS_THEY_LEFT_THEY_SHOUTED = "  As they left, they shouted, \"";
const string CONST_ONE_OF_THEM_WAS_RUMORED_TO_HAVE_CRIED_OUT = "  One of them was rumored to have cried out, \"";
const string CONST_WITNESSES_REPORTED_HEARING_THE_PHRASE = "  Witnesses reported hearing the phrase, \"";
const string CONST_ACCORDING_TO_ONE_PERSON_FAMILIAR_WITH_THE_CASE = "According to one person familiar with the case, \"";

const string CONST_REAGAN_WAS_WRONG = "Reagan was wrong";
const string CONST_CPP_IO_RB = "rb";
const string CONST_NEO_PAGAN_LOWERCASE = "neo-pagan";
const string CONST_HIM_LOWERCASE = "him";
const string CONST_BLOODS_CAPITALIZED = "Bloods";
const string CONST_HIMSELF_LOWERCASE = "himself";
const string CONST_HE_LOWERCASE_SPACE = "he ";
const string CONST_MISS_SPACE = "Miss ";
const string CONST_I_WOULD_KILL_AGAIN = "If I were to be released, I would surely kill again.\"";
const string CONST_HE_LOWERCASE = "he";
const string CONST_MAKE_THINGS_RIGHT_WITH_THE_ALMIGHTY_FATHER = "\"Make things right with the Almighty Father.\"";
const string CONST_HUSBAND_LOWERCASE = "husband";

const string CONST_BURNED_UNRECOGNIZABLE = "burned unrecognizable.  ";
const string CONST_THE_RECOVERED_BODY_WAS = "The recovered body was ";
const string CONST_THE_RECOVERED_BODIES_WERE = "The recovered bodies were ";
const string CONST_THEY_HAVE_TO_BE_STOPPED_BEFORE_THEY_KILL_AGAIN = "They have to be stopped before they kill again";
const string CONST_THIS_IS_THE_DOING_OF_THE_CONSERVATIVE_CRIME_SQUAD_BUTCHERS = "This is the doing of the Conservative Crime Squad butchers.  ";
const string CONST_NO_NAMES_NO_FACES_NOT_EVEN_WHERE_IT_HAPPENED_REALLY = "no names, no faces, not even where it happened really";
const string CONST_LOOK_IT_WAS_A_CONSERVATIVE_CRIME_SQUAD_HIT_THAT_S_ALL_WE_KNOW = "Look, it was a Conservative Crime Squad hit, that's all we know, ";
const string CONST_JUST_COVERING_IT_UP = "just covering it up";
const string CONST_WITH_IN_THE_PAST_WHEN_THE_POLICE_CAN_T_FIGURE_THIS_ONE_OUT_THEY_RE = "with in the past.  *When* the police can't figure this one out, they're ";
const string CONST_KNOWN_TO_WORK_WITH_SEVERAL_CORPORATIONS_WE_VE_HAD_CONFRONTATIONS = "known to work with several corporations we've had confrontations ";
const string CONST_THIS_MASSACRE_HAS_THE_SIGNATURE_MARK_OF_A_GROUP_OF_MERCENARIES = "This massacre has the signature mark of a group of mercenaries ";
const string CONST_IT_WAS_EXECUTION_STYLE_PROFESSIONAL_WE_VE_GOT_NOTHING = "It was execution style.  Professional.  We've got nothing";
const string CONST_INSPIRED_BY_THE_CONSERVATIVE_MEDIA_S_BRAINWASHING_PROPAGANDA = "inspired by the Conservative media's brainwashing propaganda";
const string CONST_WE_HAVE_REASON_TO_BELIEVE_THAT_THIS_BRUTAL_MASSACRE_WAS = "We have reason to believe that this brutal massacre was ";
const string CONST_BEEN_BITE_MARKS_NOTHING_RECOGNIZABLE_LEFT_COMPLETE_CARNAGE = "been bite marks.  Nothing recognizable left.  Complete carnage.";
const string CONST_BURNED_STABBED_WITH_MAYBE_PITCHFORKS_THERE_MAY_HAVE = "Burned...  stabbed with, maybe, pitchforks.  There may have ";
const string CONST_INTELLIGENCE_COMMUNITY = "intelligence community";
const string CONST_PREVIOUS_ACTIONS_TO_UNCOVER_HUMAN_RIGHTS_ABUSES_AND_CORRUPTION_IN_THE = "previous actions to uncover human rights abuses and corruption in the ";
const string CONST_CARRIED_OUT_BY_THE_CENTRAL_INTELLIGENCE_AGENCY_IN_RETALIATION_FOR_OUR = "carried out by the Central Intelligence Agency in retaliation for our ";
const string CONST_WE_HAVE_STRONG_EVIDENCE_THAT_THIS_WAS_AN_EXTRA_JUDICIAL_SLAUGHTER = "We have strong evidence that this was an extra-judicial slaughter ";
const string CONST_D_MND_ST_THING_I_VE_EVER_SEEN = "D*mnd*st thing I've ever seen";
const string CONST_DAMNEDEST_THING_I_VE_EVER_SEEN = "Damnedest thing I've ever seen";
const string CONST_CRAZIEST_THING_I_VE_EVER_SEEN = "[Craziest] thing I've ever seen";
const string CONST_FINGERPRINTS_LIKE_IT_WAS_ALL_SMOOTH = "fingerprints.  Like, it was all smooth.  ";
const string CONST_THE_BODY_HAD_NO_FACE_OR = "The body had no face or ";
const string CONST_THE_BODIES_HAD_NO_FACES_OR = "The bodies had no faces or ";
const string CONST_ACCORDING_TO_AN_LCS_SPOKESPERSON = "According to an LCS spokesperson, \"";
const string CONST_OF_THE_LCS_TARGETED_SIMPLY_DUE_TO_THEIR_POLITICAL_BELIEFS = "of the LCS targeted simply due to their political beliefs.  ";
const string CONST_VICTIM_WAS_A_MEMBER = "victim was a member ";
const string CONST_VICTIMS_WERE_MEMBERS = "victims were members ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_HAS_CLAIMED_THAT_THE = "  The Liberal Crime Squad has claimed that the ";
const string CONST_UNWILLING_TO_PURSUE_THE_CASE_WITH_ANY_SERIOUS_EFFORT = "unwilling to pursue the case with any serious effort.";
const string CONST_THE_POLICE_HAVE_OPENED_AN_INVESTIGATION_INTO_THE_MASSACRE_BUT_SEEM = "  The police have opened an investigation into the massacre, but seem ";
const string CONST_PRIVATELY_SOURCES_IN_THE_DEPARTMENT_CONFIDE_THAT_THERE_AREN_T_ANY_LEADS = "  Privately, sources in the department confide that there aren't any leads.  ";
const string CONST_THE_POLICE_DEPARTMENT_THE_MATTER_IS_UNDER_INVESTIGATION_AS_A_HOMICIDE = "the police department, the matter is under investigation as a homicide.";
const string CONST_ACCORDING_TO_A_SPOKESPERSON_FOR = "  According to a spokesperson for ";
const string CONST_YESTERDAY = " yesterday.";
const string CONST_FOUND_IN_THE = " found in the ";
const string CONST_A_BODY_WAS = " A body was ";
const string CONST_TWO_BODIES_WERE = " Two bodies were ";
const string CONST_BODIES_WERE = " bodies were ";
const string CONST_MASSACRE = "MASSACRE";
const string CONST_MYSTERIOUS = "MYSTERIOUS";
const string CONST_CCS_MASSACRE = "CCS MASSACRE";
const string CONST_BEFORE_PASSING_OUT = "\" before passing out.";
const string CONST_WAS_FOUND_PAINTED_ON_THE_WALLS = "\" was found painted on the walls.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ENDED_THE_DANGEROUS_HIGH_SPEED_CHASE_IN_ORDER_TO_PROTECT_THE_PUBLIC_AND_ATTEMPTED_TO_ESCAPE_ON_FOOT = "The Liberal Crime Squad ended the dangerous high-speed chase in order to protect the public, and attempted to escape on foot.  ";
const string CONST_THERE_WAS_ALSO_A_FOOT_CHASE_WHEN_THE_SUSPECT_OR_SUSPECTS_BAILED_OUT_AFTER_THE_HIGH_SPEED_PURSUIT = "There was also a foot chase when the suspect or suspects bailed out after the high-speed pursuit.  ";
const string CONST_DETAILS_ABOUT_INJURIES_WERE_NOT_RELEASED = "Details about injuries were not released.  ";
const string CONST_ONE_VEHICLE_CRASHED = "One vehicle crashed.  ";
const string CONST_VEHICLES_CRASHED = " vehicles crashed.  ";
const string CONST_PURSUIT_OF_THE_LCS = "pursuit of the LCS.  ";
const string CONST_CONSERVATIVE_OPERATIVES_ENGAGED_IN_A_RECKLESS = "  Conservative operatives engaged in a reckless ";
const string CONST_FOLLOWING_THE_INCIDENT = "following the incident.  ";
const string CONST_IT_IS_KNOWN_THAT_THERE_WAS_A_HIGH_SPEED_CHASE = "  It is known that there was a high-speed chase ";
const string CONST_PICKED_LOCKS = "picked locks";
const string CONST_UNLAWFUL_ENTRY = "unlawful entry";
const string CONST_BROKE_DOWN_DOORS = "broke down doors";
const string CONST_BREAKING_AND_ENTERING_LOWERCASE = "breaking and entering";
const string CONST_MARKED_THE_SITE_FOR_LIBERATION = "marked the site for Liberation";
const string CONST_VANDALISM_LOWERCASE = "vandalism";
const string CONST_DAMAGED_ENEMY_INFRASTRUCTURE = "damaged enemy infrastructure";
const string CONST_DESTRUCTION_OF_PRIVATE_PROPERTY = "destruction of private property";
const string CONST_LIBERATED_ABUSED_ANIMALS = "liberated abused animals";
const string CONST_TAMPERING_WITH_LAB_ANIMALS = "tampering with lab animals";
const string CONST_LIBERATED_ENEMY_RESOURCES = "liberated enemy resources";
const string CONST_THEFT_LOWERCASE = "theft";
const string CONST_ENGAGED_IN_COMBAT_WITH_CONSERVATIVE_FORCES = "engaged in combat with Conservative forces";
const string CONST_VIOLENCE = "violence";
const string CONST_MORE_VIOLENCE = "more violence";
const string CONST_MURDER_LOWERCASE = "murder";
const string CONST_SET_FIRE_TO_CONSERVATIVE_PROPERTY = "set fire to Conservative property";
const string CONST_ARSON_LOWERCASE = "arson";
const string CONST_ENGAGED_IN = "engaged in ";
const string CONST_FURTHER_DETAILS_ARE_SKETCHY_BUT_POLICE_SOURCES_SUGGEST_THAT_THE_CCS = "  Further details are sketchy, but police sources suggest that the CCS ";
const string CONST_THE_LIBERAL_CRIME_SQUAD = "  The Liberal Crime Squad ";
const string CONST_FURTHER_DETAILS_ARE_SKETCHY_BUT_POLICE_SOURCES_SUGGEST_THAT_THE_LCS = "  Further details are sketchy, but police sources suggest that the LCS ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_WAS_ATTEMPTING_TO_UNCOVER_THE_COMPANY_S_CONSERVATIVE_CORRUPTION = "  The Liberal Crime Squad was attempting to uncover the company's Conservative corruption.";
const string CONST_EXECUTIVES_ON_THE_SCENE_SEEMED_VERY_NERVOUS_ABOUT_SOMETHING = "executives on the scene seemed very nervous about something.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_WAS_ATTEMPTING_TO_UNCOVER_THE_CEO_S_CONSERVATIVE_CORRUPTION = "  The Liberal Crime Squad was attempting to uncover the CEO's Conservative corruption.";
const string CONST_THE_OWNER_OF_THE_HOUSE_SEEMED_VERY_FRANTIC_ABOUT_SOME_MISSING_PROPERTY = "the owner of the house seemed very frantic about some missing property.";
const string CONST_LIBERAL_CRIME_SQUAD_INFILTRATION_SPECIALISTS_WORKED_TO_LIBERATE_WEAPONS_FROM_THE_OPPRESSORS = "  Liberal Crime Squad infiltration specialists worked to liberate weapons from the oppressors.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_BREAK_INTO_THE_ARMORY = "the Liberal Crime Squad attempted to break into the armory.";
const string CONST_LIBERAL_CRIME_SQUAD_COMPUTER_SPECIALISTS_WORKED_TO_LIBERATE_INFORMATION_FROM_CIA_COMPUTERS = "  Liberal Crime Squad computer specialists worked to liberate information from CIA computers.";
const string CONST_INTELLIGENCE_OFFICIALS_SEEMED_VERY_NERVOUS_ABOUT_SOMETHING = "intelligence officials seemed very nervous about something.";
const string CONST_MAY_HAVE_INTERFERED_WITH_JURY_DELIBERATIONS = "may have interfered with jury deliberations.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_HAS_APOLOGIZED_OVER_REPORTS_THAT_THE_OPERATION = "  The Liberal Crime Squad has apologized over reports that the operation ";
const string CONST_TRUST_AND_ATTEMPTED_TO_INFLUENCE_A_JURY = "trust and attempted to influence a jury.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_VIOLATED_THE_SACRED = "the Liberal Crime Squad allegedly violated the sacred ";
const string CONST_AT_THE_PRISON = "at the prison.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_RESCUE_INNOCENT_PEOPLE_FROM_THE_ABUSIVE_CONSERVATIVE_CONDITIONS = "  The Liberal Crime Squad attempted to rescue innocent people from the abusive Conservative conditions ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_FREED_PRISONERS_WHILE_IN_THE_FACILITY = "the Liberal Crime Squad allegedly freed prisoners while in the facility.";
const string CONST_SAVING_THEM_FROM_THE_HIGHLY_CORRUPT_CONSERVATIVE_JUSTICE_SYSTEM = "saving them from the highly corrupt Conservative justice system.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_RESCUE_INNOCENT_PEOPLE_FROM_THE_COURTHOUSE_LOCKUP = "  The Liberal Crime Squad attempted to rescue innocent people from the courthouse lockup, ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_FREED_OR_ATTEMPTED_TO_FREE_PRISONERS_FROM_THE_COURTHOUSE_LOCKUP = "the Liberal Crime Squad allegedly freed or attempted to free prisoners from the courthouse lockup.";
const string CONST_HOPING_TO_ACQUIRE_THE_RESOURCES_TO_OVERCOME_EVIL = "hoping to acquire the resources to overcome evil.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_DEMANDED_ACCESS_TO_THE_BANK_VAULT = "  The Liberal Crime Squad demanded access to the bank vault, ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_THREATENED_INNOCENT_BYSTANDERS_IN_ORDER_TO_ROB_THE_BANK_VAULT = "the Liberal Crime Squad threatened innocent bystanders in order to rob the bank vault.";
const string CONST_SHOWING_THE_TRIUMPH_OF_LIBERAL_IDEALS_OVER_CONSERVATIVE_ECONOMICS = "showing the triumph of Liberal ideals over Conservative economics.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_OPENED_THE_BANK_VAULT = "  The Liberal Crime Squad opened the bank vault, ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_OPENED_THE_BANK_VAULT_WHICH_HELD_MORE_THAN_100_000_AT_THE_TIME = "the Liberal Crime Squad opened the bank vault, which held more than $100,000 at the time.";
const string CONST_SAVING_THEM_FROM_TORTURE_AND_BRUTALITY_AT_THE_HANDS_OF_CONSERVATIVE_POLICE_INTERROGATORS = "saving them from torture and brutality at the hands of Conservative police interrogators.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_RESCUE_INNOCENT_PEOPLE_FROM_THE_POLICE_LOCKUP = "  The Liberal Crime Squad attempted to rescue innocent people from the police lockup, ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_FREED_OR_ATTEMPTED_TO_FREE_PRISONERS_FROM_THE_POLICE_LOCKUP = "the Liberal Crime Squad allegedly freed or attempted to free prisoners from the police lockup.";
const string CONST_DEMONSTRATING_THE_EXTREME_VULNERABILITY_AND_DANGER_OF_NUCLEAR_POWER_PLANTS = "demonstrating the extreme vulnerability and danger of Nuclear Power Plants. ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_BROUGHT_THE_REACTOR_TO_THE_VERGE_OF_A_NUCLEAR_MELTDOWN = "  The Liberal Crime Squad brought the reactor to the verge of a nuclear meltdown, ";
const string CONST_REACTOR = "reactor.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_NEARLY_CAUSED_A_CATASTROPHIC_MELTDOWN_OF_THE_NUCLEAR = "the Liberal Crime Squad nearly caused a catastrophic meltdown of the nuclear ";
const string CONST_DEMONSTRATING_THE_EXTREME_DANGERS_OF_NUCLEAR_WASTE = "demonstrating the extreme dangers of Nuclear Waste. ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_TAMPERED_WITH_THE_STATE_S_WATER_SUPPLY_YESTERDAY = "  The Liberal Crime Squad tampered with the state's water supply yesterday, ";
const string CONST_YESTERDAY_BY_TAMPERING_WITH_EQUIPMENT_ON_THE_SITE = "yesterday by tampering with equipment on the site.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_CONTAMINATED_THE_STATE_S_WATER_SUPPLY = "the Liberal Crime Squad contaminated the state's water supply";
const string CONST_THE_NAME_OF_THE_OFFICER_HAS_NOT_BEEN_RELEASED_PENDING_NOTIFICATION_OF_THE_OFFICER_S_FAMILY = "The name of the officer has not been released pending notification of the officer's family.";
const string CONST_THE_NAMES_OF_THE_OFFICERS_HAVE_NOT_BEEN_RELEASED_PENDING_NOTIFICATION_OF_THEIR_FAMILIES = "The names of the officers have not been released pending notification of their families.";
const string CONST_A_PASSERBY_HAD_ALLEGEDLY_SPOTTED_THE_SUSPECT_COMMITTING_A_CAR_THEFT = "A passerby had allegedly spotted the suspect committing a car theft.  ";
const string CONST_APPEARED_TO_BE_A_CORPSE_THROUGH_AN_EMPTY_LOT = "appeared to be a corpse through an empty lot.  ";
const string CONST_A_PASSERBY_ALLEGEDLY_CALLED_THE_AUTHORITIES_AFTER_SEEING_THE_SUSPECT_DRAGGING_WHAT = "A passerby allegedly called the authorities after seeing the suspect dragging what ";
const string CONST_THE_SUSPECT_WAS_ALLEGEDLY_SELLING_POT_BROWNIES = "The suspect was allegedly selling \"pot brownies\".  ";
const string CONST_THE_INCIDENT_APPARENTLY_OCCURRED_AS_A_RESPONSE_TO_A_PUBLIC_NUDITY_COMPLAINT = "The incident apparently occurred as a response to a public nudity complaint.  ";
const string CONST_ATTEMPTING_TO_PERFORM_AN_ARREST = " attempting to perform an arrest.  ";
const string CONST_A_POLICE_OFFICER_THAT_WAS = "a police officer that was";
const string CONST_POLICE_OFFICERS_THAT_WERE = " police officers that were";
const string CONST_KILLED = "killed ";
const string CONST_A_SUSPECT_WHOSE_IDENTITY_IS_UNCLEAR = "  A suspect, whose identity is unclear, ";
const string CONST_ACCORDING_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT = "according to a spokesperson from the police department.";
const string CONST_A_ROUTINE_ARREST_WENT_HORRIBLY_WRONG_YESTERDAY = "A routine arrest went horribly wrong yesterday, ";
const string CONST_WHILE_THEY_WERE_ATTEMPTING_TO_PERFORM_AN_ARREST = " while they were attempting to perform an arrest.  ";
const string CONST_THE_POLICE_OFFICER = "the police officer ";
const string CONST_OFFICERS = " officers ";
const string CONST_RADICAL_POLITICAL_GROUP_KNOWN_AS_THE_LIBERAL_CRIME_SQUAD_IS_BELIEVED_TO_HAVE_KILLED = "radical political group known as the Liberal Crime Squad, is believed to have killed ";
const string CONST_A_SUSPECT_IDENTIFIED_ONLY_AS_A_MEMBER_OF_THE = "  A suspect, identified only as a member of the ";
const string CONST_KILLED_IN_THE_LINE_OF_DUTY_YESTERDAY = " killed in the line of duty yesterday, ";
const string CONST_A_POLICE_OFFICER_WAS = "A police officer was";
const string CONST_POLICE_OFFICERS_WERE = " police officers were";
const string CONST_SEVERAL = "Several";
const string CONST_TWO_UPPERCASE = "Two";
const string CONST_OF_CULTURE = "OF CULTURE";
const string CONST_THE_DEATH = "THE DEATH";
const string CONST_NEW_JOBS = "NEW JOBS";
const string CONST_LOOKING_UP = "LOOKING UP";
const string CONST_FALL_FASHIONS_ARE_PREVIEWED_IN_STORES_ACROSS_THE_COUNTRY = "Fall fashions are previewed in stores across the country.";
const string CONST_FALL_FASHIONS_HIT_THE_STORES_ACROSS_THE_COUNTRY = "Fall fashions hit the stores across the country.";
const string CONST_THEY_ARE_HERE = "THEY ARE HERE";
const string CONST_JUSTICE_AMOK = "JUSTICE AMOK";
const string CONST_GM_FOOD_FAIRE = "GM FOOD FAIRE";
const string CONST_FREE_SPEECH_ADVOCATES_FIGHT_HARD_TO_LET_A_WHITE_SUPREMACIST_RALLY_TAKE_PLACE = "Free speech advocates fight hard to let a white supremacist rally take place.";
const string CONST_HATE_RALLY = "HATE RALLY";
const string CONST_DODGED_BULLET = "DODGED BULLET";
const string CONST_HOSTAGE_SLAIN = "HOSTAGE SLAIN";
const string CONST_BASTARDS = "BASTARDS";
const string CONST_JERKS = "[JERKS]";
const string CONST_APE_EXPLORERS = "APE EXPLORERS";
const string CONST_OPEC_CUTS_OIL_PRODUCTION_SHARPLY_IN_RESPONSE_TO_A_US_FOREIGN_POLICY_DECISION = "OPEC cuts oil production sharply in response to a US foreign policy decision.";
const string CONST_OIL_CRUNCH = "OIL CRUNCH";
const string CONST_A_NEW_BOOK_LAUDING_REAGAN_AND_THE_GREATEST_GENERATION = ": A new book lauding Reagan and the greatest generation.";
const string CONST_REAGAN_THE_MAN = "REAGAN THE MAN";
const string CONST_SAVES_LIVES = "SAVES LIVES";
const string CONST_ARMED_CITIZEN = "ARMED CITIZEN";
const string CONST_END_IN_TEARS = "END IN TEARS";
const string CONST_OUR_BOYS_DEFEND_FREEDOM_ONCE_AGAIN_DEFEATING_AN_EVIL_DICTATOR = "Our boys defend freedom once again, defeating an evil dictator.";
const string CONST_BIG_VICTORY = "BIG VICTORY";
const string CONST_LET_S_FRY_EM = "LET'S FRY 'EM";
const string CONST_JERRY_FALWELL_EXPLAINS_THE_TRUTH_ABOUT_TINKY_WINKY_AGAIN = "Jerry Falwell explains the truth about Tinky Winky.  Again.";
const string CONST_KINKY_WINKY = "KINKY WINKY";
const string CONST_AM_IMPLOSION = "AM IMPLOSION";
const string CONST_REGULARLY_VISITS_PROSTITUTES = "regularly visits prostitutes.";
const string CONST_REGULARLY_DONATES_TO_SPERM_BANKS = "regularly [donates to sperm banks].";
const string CONST_REGULARLY_VISITS_WORKING_WOMEN = "regularly visits [working women].";
const string CONST_THIS_MAJOR_CEO = "This major CEO ";
const string CONST_AMERICAN_CEO = "AMERICAN CEO";
const string CONST_AN_ENORMOUS_COMPANY_FILES_FOR_BANKRUPTCY_SHATTERING_THE_PREVIOUS_RECORD = "An enormous company files for bankruptcy, shattering the previous record.";
const string CONST_BELLY_UP = "BELLY UP";
const string CONST_THE_OHIO_RIVER_CAUGHT_ON_FIRE_AGAIN = "The Ohio River caught on fire again.";
const string CONST_RING_OF_FIRE = "RING OF FIRE";
const string CONST_A_T_SHIRT_IN_A_STORE_IS_FOUND_SCRAWLED_WITH_A_MESSAGE_FROM_A_SWEATSHOP_WORKER = "A T-shirt in a store is found scrawled with a message from a sweatshop worker.";
const string CONST_CHILD_S_PLEA = "CHILD'S PLEA";
const string CONST_IN_CONTEMPT = "IN CONTEMPT";
const string CONST_OVER_A_HUNDRED_PEOPLE_BECOME_SICK_FROM_GENETICALLY_MODIFIED_FOOD = "Over a hundred people become sick from genetically modified food.";
const string CONST_KILLER_FOOD = "KILLER FOOD";
const string CONST_BOOK_BANNED = "BOOK BANNED";
const string CONST_THE_FBI_FILES = "THE FBI FILES";
const string CONST_ON_THE_INSIDE = "ON THE INSIDE";
const string CONST_A_MUTANT_ANIMAL_HAS_ESCAPED_FROM_A_LAB_AND_KILLED_THIRTY_PEOPLE = "A mutant animal has escaped from a lab and killed thirty people.";
const string CONST_HELL_ON_EARTH = "HELL ON EARTH";
const string CONST_A_NUCLEAR_POWER_PLANT_SUFFERS_A_CATASTROPHIC_MELTDOWN = "A nuclear power plant suffers a catastrophic meltdown.";
const string CONST_MELTDOWN = "MELTDOWN";
const string CONST_A_NEW_BOOK_FURTHER_DOCUMENTING_THE_OTHER_SIDE_OF_REAGAN = ": A new book further documenting the other side of Reagan.";
const string CONST_REAGAN_FLAWED = "REAGAN FLAWED";
const string CONST_MASS_SHOOTING_ALLCAPS = "MASS SHOOTING";
const string CONST_NIGHTMARE = "NIGHTMARE";
const string CONST_IS_THE_LATEST_MILITARY_INVASION_YET_ANOTHER_QUAGMIRE = "Is the latest military invasion yet another quagmire?";
const string CONST_CASUALTIES_MOUNT = "CASUALTIES MOUNT";
const string CONST_JUSTICE_DEAD = "JUSTICE DEAD";
const string CONST_CRIME_OF_HATE = "CRIME OF HATE";
const string CONST_CLINIC_MURDER = "CLINIC MURDER";
const string CONST_NEWSPIC_CPC = "newspic.cpc";
const string CONST_NEWSTOPS_CPC = "newstops.cpc";
const string CONST_LARGECAP_CPC = "largecap.cpc";
const string CONST_SQUAD_RAMPAGE = "SQUAD RAMPAGE";
const string CONST_LIBERAL_CRIME = "LIBERAL CRIME";
const string CONST_LCS_SORRY = "LCS SORRY";
const string CONST_LCS_RAMPAGE = "LCS RAMPAGE";
const string CONST_SQUAD_STRIKES = "SQUAD STRIKES";
const string CONST_LCS_STRIKES = "LCS STRIKES";
const string CONST_HEROIC_STRIKE = "HEROIC STRIKE";
const string CONST_LCS_HITS_TV = "LCS HITS TV";
const string CONST_LCS_HITS_AM = "LCS HITS AM";
const string CONST_LCS_HITS_CORP = "LCS HITS CORP";
const string CONST_POLLUTER_HIT = "POLLUTER HIT";
const string CONST_NO_JUSTICE = "NO JUSTICE";
const string CONST_EVIL_RESEARCH = "EVIL RESEARCH";
const string CONST_LCS_VS_CIA = "LCS VS CIA";
const string CONST_PRISON_WAR = "PRISON WAR";
const string CONST_LCS_VS_COPS = "LCS VS COPS";
const string CONST_MELTDOWN_RISK = "MELTDOWN RISK";
const string CONST_CLASS_WAR = "CLASS WAR";
const string CONST_UNSTOPPABLE = "UNSTOPPABLE";
const string CONST_CCS_RAMPAGE = "CCS RAMPAGE";
const string CONST_CCS_STRIKES = "CCS STRIKES";
const string CONST_CRIME_SQUAD = "CRIME SQUAD";
const string CONST_LCS_MARTYRS = "LCS MARTYRS";
const string CONST_POLICE_KILL = "POLICE KILL";
const string CONST_TRAGIC_END = "TRAGIC END";
const string CONST_LCS_SIEGE = "LCS SIEGE";
const string CONST_OFF_COPS = "OFF COPS";
const string CONST_LCS_FIGHTS = "LCS FIGHTS";
const string CONST_POLICE_SIEGE = "POLICE SIEGE";
const string CONST_LCS_ESCAPES = "LCS ESCAPES";
const string CONST_POLICE_KILLED = "POLICE KILLED";
const string CONST_RAIDS_END_CCS = "RAIDS END CCS";
const string CONST_FBI_HUNTS_CCS = "FBI HUNTS CCS";
const string CONST_ASSASSINATED = "ASSASSINATED";
const string CONST_MISSING = "MISSING";
const string CONST_RESCUED = "RESCUED";
const string CONST_FOUND_DEAD = "FOUND DEAD";
const string CONST_BELIEVED_DEAD = "BELIEVED DEAD";
const string CONST_IMPEACHED = "IMPEACHED";
const string CONST_LOWER_BORDER_WITH_CORNERS = "훤袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴暠";
const string CONST_AUDIENCE_AND_VIEWERS_NATIONWIDE_FEEL_ITS_PAIN = "�   audience and viewers nationwide feel its pain.   �";
const string CONST_POPULAR_AFTERNOON_TALK_SHOW_THE_STUDIO = "�   popular  afternoon  talk  show.    The  studio   �";
const string CONST_A_FAILED_PARTIAL_BIRTH_ABORTION_GOES_ON_A = "�     A  failed partial  birth abortion  goes on a   �";
const string CONST_UPPER_BORDER_WITH_CORNERS = "�袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴袴�";
const string CONST_ABORT_CMV = "abort.cmv";
const string CONST_BY_IMPRESSIVE_ADVERTISING_AMERICA_TUNES_IN = "�   by impressive  advertising, America  tunes in.   �";
const string CONST_NEW_ANCHOR_FOR_ONE_OF_ITS_NEWS_SHOWS_GUIDED = "�   new anchor for  one of its news shows.  Guided   �";
const string CONST_A_MAJOR_CABLE_NEWS_CHANNEL_HAS_HIRED_A_SLICK = "�     A major Cable News channel has hired a slick   �";
const string CONST_ANCHOR_CMV = "anchor.cmv";
const string CONST_ADVERTISING_BLITZ_IT_S_BOUND_TO_BE_POPULAR = "�   advertising  blitz, it's bound  to be popular.   �";
const string CONST_BEGINS_AIRING_THIS_WEEK_WITH_THE_NATIONWIDE = "�   begins airing  this week.  With the nationwide   �";
const string CONST_A_NEW_SHOW_GLAMORIZING_THE_LIVES_OF_THE_RICH = "�     A new show glamorizing the lives of the rich   �";
const string CONST_GLAMSHOW_CMV = "glamshow.cmv";
const string CONST_VIEWERS_ACROSS_THE_NATION_WERE_LISTENING = "�   viewers  across  the  nation  were  listening.   �";
const string CONST_BRIGHT_LIBERAL_GUEST_FINISH_A_SENTENCE_MANY = "�   bright Liberal guest  finish a sentence.  Many   �";
const string CONST_A_CABLE_NEWS_ANCHOR_ACCIDENTALLY_LET_A = "�     A  Cable  News  anchor  accidentally  let  a   �";
const string CONST_NEWSCAST_CMV = "newscast.cmv";
const string CONST_SPACE_WITH_SPACE = " with ";
const string CONST_TONIGHT_ON_A_CABLE_NEWS_CHANNEL = "Tonight on a Cable News channel: ";
const string CONST_TAPED_BY_A_PASSERBY_AND_SATURATES_THE_NEWS = "�   taped by  a passerby  and saturates  the news.   �";
const string CONST_LOS_ANGELES_AGAIN_THIS_TIME_THE_INCIDENT = "�   Los Angeles again.  This time, the incident is   �";
const string CONST_THE_POLICE_HAVE_BEATEN_A_BLACK_MAN_IN = "�     The  police  have  beaten  a  black  man  in   �";
const string CONST_LACOPS_CMV = "lacops.cmv";
const string CONST_WHILE_RESISTING_CAPTURE_ACCORDING_TO_A_PRISON_SPOKESPERSON = " while \"resisting capture\", according to a prison spokesperson.";
const string CONST_BEATEN_TO_DEATH = "beaten to death";
const string CONST_ALSO_HARMED = "[also harmed]";
const string CONST_THE_PRISONER_WAS = ".  The prisoner was ";
const string CONST_ALTAR = " altar";
const string CONST_SATANIC = "Satanic";
const string CONST_SACRIFICED_THE_GUARD_ON_A_MAKESHIFT = "sacrificed the guard on a makeshift ";
const string CONST_PERFORMED_DEADLY_EXPERIMENTS_ON_THE_GUARD_UNHEARD_OF_SINCE_DR_MENGELE = "performed deadly experiments on the guard unheard of since Dr. Mengele";
const string CONST_EATEN_THE_GUARD_S_LIVER_WITH_SOME_FAVA_BEANS_AND_A_NICE_CHIANTI = "eaten the guard's liver with some fava beans and a nice chianti";
const string CONST_BURNT_THE_GUARD_TO_A_CRISP_USING_A_LIGHTER_AND_SOME_GASOLINE = "burnt the guard to a crisp using a lighter and some gasoline";
const string CONST_TRICKED_ANOTHER_GUARD_INTO_SHOOTING_THE_GUARD_DEAD = "tricked another guard into shooting the guard dead";
const string CONST_OFF = " off";
const string CONST_HER = "her";
const string CONST_TAKEN_THE_GUARD_TO_THE_EXECUTION_CHAMBER_AND_FINISHED = "taken the guard to the execution chamber and finished ";
const string CONST_THROWN_THE_GUARD_OUT_THE_TOP_STOREY_WINDOW = "thrown the guard out the top-storey window";
const string CONST_ELECTROCUTED_THE_GUARD_WITH_HIGH_VOLTAGE_WIRES = "electrocuted the guard with high-voltage wires";
const string CONST_HIT_ALL_36_PRESSURE_POINTS_OF_DEATH_ON_THE_GUARD = "hit all 36 pressure points of death on the guard";
const string CONST_CRIPS = "Crips";
const string CONST_POISONED_THE_GUARD_WITH_DRUGS_SMUGGLED_INTO_THE_PRISON_BY_THE = "poisoned the guard with drugs smuggled into the prison by the ";
const string CONST_OWN_GUN = " own gun";
const string CONST_SHOT_THE_GUARD_WITH = "shot the guard with ";
const string CONST_CELL = " cell";
const string CONST_SMASHED_THE_GUARD_S_SKULL_WITH_THE_TOILET_SEAT_FROM = "smashed the guard's skull with the toilet seat from ";
const string CONST_CHEWED_OUT_THE_GUARD_S_THROAT = "chewed out the guard's throat";
const string CONST_STRANGLED_THE_GUARD_TO_DEATH_WITH_A_KNOTTED_BED_SHEET = "strangled the guard to death with a knotted bed sheet";
const string CONST_SLIT_THE_GUARD_S_THROAT_WITH_A_SHANK = "slit the guard's throat with a shank";
const string CONST_KILLED_THE_GUARD = "killed the guard";
const string CONST_HARMED_THE_GUARD = "[harmed] the guard";
const string CONST_HAD_ALREADY = " had already ";
const string CONST_THE_HOSTAGE_BUT = "the hostage, but ";
const string CONST_THE_TOWER_WAS_BREACHED_IN_AN_ATTEMPT_TO_REACH = "  The tower was breached in an attempt to reach ";
const string CONST_IMMA_KILL_ALL_YOU_B_TCHES_STARTIN_WITH_THIS_M_TH_F_CK_R_HERE = "Imma kill all you b*tches, startin' with this m*th*f*ck*r here.";
const string CONST_I_WILL_HARM_ALL_POLICE_OFFICERS_STARTIN_WITH_THIS_ONE_HERE = "[I will harm all police officers], startin' with this [one] here.";
const string CONST_IMMA_KILL_ALL_YOU_BITCHES_STARTIN_WITH_THIS_MOTHAFUCKER_HERE = "Imma kill all you bitches, startin' with this mothafucker here.";
const string CONST_WHY_THE_F_CK_AM_I_TALKIN_TO_YOU_I_D_RATHER_KILL_THIS_PIG = "Why the f*ck am I talkin' to you?  I'd rather kill this pig.";
const string CONST_WHY_AM_I_TALKIN_TO_YOU_I_D_RATHER_HARM_THIS_POLICE_OFFICER = "Why [am I] talkin' to you?  I'd rather [harm this police officer.]";
const string CONST_WHY_THE_FUCK_AM_I_TALKIN_TO_YOU_I_D_RATHER_KILL_THIS_PIG = "Why the fuck am I talkin' to you?  I'd rather kill this pig.";
const string CONST_F_CK_A_M_TH_F_CK_N_BULL_I_M_KILLIN_THIS_PIG_SH_T = "F*ck a m*th*f*ck*n' bull.  I'm killin' this pig sh*t.";
const string CONST_TOO_LATE_I_AM_GOING_TO_HARM_THIS_POLICE_OFFICER = "[Too late.]  [I am going to harm this police officer.]";
const string CONST_FUCK_A_MUTHAFUCKIN_BULL_I_M_KILLIN_THIS_PIG_SHIT = "Fuck a muthafuckin' bull.  I'm killin' this pig shit.";
const string CONST_AH_F_CK_THIS_SH_T_THIS_PUNK_B_TCH_IS_F_CKIN_DEAD = "Ah, f*ck this sh*t.  This punk b*tch is f*ckin' dead!";
const string CONST_AH_NO_WAY_THIS_POLICE_OFFICER_WILL_BE_HARMED = "Ah, [no way.]  This [police officer will be harmed!]";
const string CONST_AH_FUCK_THIS_SHIT_THIS_PUNK_BITCH_IS_FUCKIN_DEAD = "Ah, fuck this shit.  This punk bitch is fuckin' dead!";
const string CONST_REPORTEDLY_SCREAMED_INTO_THE_RECEIVER = " reportedly screamed into the receiver \"";
const string CONST_DAYS_BUT_TALKS_WERE_CUT_SHORT_WHEN = " days, but talks were cut short when ";
const string CONST_ATTEMPTED_TO_NEGOTIATE_BY_PHONE_FOR = "attempted to negotiate by phone for ";
const string CONST_AUTHORITIES_LOCKED_DOWN_THE_PRISON_AND = "Authorities locked down the prison and ";
const string CONST_WITH_THE_GUARD_IN_A_PRISON_TOWER = " with the guard in a prison tower.  ";
const string CONST_HERSELF = "herself";
const string CONST_AND_BARRICADED = " and barricaded ";
const string CONST_OVERPOWERED = ", overpowered ";
const string CONST_AN_INMATE_AT = ", an inmate at ";
const string CONST_TWO_WEEKS_AGO_CONVICTED_RAPIST = "   Two weeks ago, convicted rapist ";
const string CONST_TWO_WEEKS_AGO_CONVICTED_REPRODUCTION_FIEND = "   Two weeks ago, convicted [reproduction fiend] ";
const string CONST_CAPTOR = " captor.";
const string CONST_DEATH_OF_BOTH_THE_PRISON_GUARD_BEING_HELD_HOSTAGE_AND = "death of both the prison guard being held hostage and ";
const string CONST_CORRECTIONAL_FACILITY_ENDED_TRAGICALLY_YESTERDAY_WITH_THE = " Correctional Facility ended tragically yesterday with the ";
const string CONST_THE_HOSTAGE_CRISIS_AT_THE = " - The hostage crisis at the ";
const string CONST_S_HEROIC_ACTIONS = "'s heroic actions.\"";
const string CONST_IF_NOT_FOR = " if not for ";
const string CONST_MASS_SHOOTING = "mass shooting";
const string CONST_HURTING_SPREE = "[hurting spree]";
const string CONST_THE_SPOKESPERSON_FOR_THE_POLICE_DEPARTMENT_SAID_WE_D_HAVE_A_YET_ANOTHER = "  The spokesperson for the police department said, \"We'd have a yet another ";
const string CONST_COULD_HURT_ANYONE_ELSE_R = "could hurt anyone else.&r";
const string CONST_SHE_LOWERCASE_SPACE = "she ";
const string CONST_BEFORE = "before ";
const string CONST_FIREFIGHT_KILLING_THE_ATTACKER = "firefight, killing the attacker ";
const string CONST_FIREFIGHT_PUTTING_THE_ATTACKER_TO_SLEEP = "firefight, [putting the attacker to sleep] ";
const string CONST_BECAME_MORE_AGITATED_THE_HEROIC_CITIZEN_WAS_FORCED_TO_ENGAGE_THE_SHOOTER_IN_A = " became more agitated, the heroic citizen was forced to engage the shooter in a ";
const string CONST_ATTEMPTED_TO_TALK_DOWN_THE_SHOOTER_BUT_AS = " attempted to talk down the shooter, but as ";
const string CONST_MR = "Mr. ";
const string CONST_MRS = "Mrs. ";
const string CONST_MS = "Ms. ";
const string CONST_INITIALLY = "  Initially, ";
const string CONST_TO_TAKE_COVER_WHILE_OTHERS_CALLED_THE_POLICE_R = " to take cover while others called the police.&r";
const string CONST_FORCING = "forcing ";
const string CONST_THE_CITIZEN_PULLED_A_CONCEALED_HANDGUN_AND_FIRED_ONCE_AT_THE_SHOOTER = "The citizen pulled a concealed handgun and fired once at the shooter, ";
const string CONST_SPRUNG_INTO_ACTION = " sprung into action. ";
const string CONST_OPENED_FIRE_AT_THE = " opened fire at the ";
const string CONST_AFTER = " After ";
const string CONST_WAS_PREVENTED_BY_A_BYSTANDER_WITH_A_GUN = " was prevented by a bystander with a gun.";
const string CONST_IN_A_SURPRISING_TURN_A = " - In a surprising turn, a ";
const string CONST_STATED_THAT_THE_INCIDENT_IS_UNDER_INVESTIGATION = "stated that the incident is under investigation.";
const string CONST_A_SPOKESPERSON_FOR_THE_FCC = " A spokesperson for the FCC ";
const string CONST_WITHIN_THE_TOWN = "within the town. ";
const string CONST_IN_NEIGHBORING_TOWNS = "in neighboring towns. ";
const string CONST_WITHIN_THE_COUNTY = "within the county. ";
const string CONST_FROM_ALL_OVER_THE_STATE = "from all over the state. ";
const string CONST_ACROSS_THE_NATION = "across the nation. ";
const string CONST_FROM_IRATE_LISTENERS = "from irate listeners ";
const string CONST_COMPLAINTS = " complaints ";
const string CONST_SOME = "some";
const string CONST_DOZENS_OF = "dozens of";
const string CONST_HUNDREDS_OF = "hundreds of";
const string CONST_SEVERAL_HUNDRED = "several hundred";
const string CONST_THOUSANDS_OF = "thousands of";
const string CONST_THE_FCC_RECEIVED = "the FCC received ";
const string CONST_LATER_APOLOGIZED = " later apologized, ";
const string CONST_ON_THE_AIR_ALTHOUGH = " on the air.  Although ";
const string CONST_MASTURBATED = "masturbated";
const string CONST_HAD_FUN = "[had fun]";
const string CONST_BREASTFED_FROM_A_LACTATING_WOMAN = "breastfed from a lactating woman";
const string CONST_FED_FROM_A_WOMAN = "[fed] from a [woman]";
const string CONST_BREASTFED_FROM_AN_EXPOSED_WOMAN = "breastfed from an exposed woman";
const string CONST_FED_FROM_AN_INDECENT_WOMAN = "[fed] from [an indecent] woman";
const string CONST_SCREAMED_F_CK_THE_POLICE_THOSE_G_DD_MN_M_TH_F_CK_RS_I_GOT_A_F_CKING_TICKET_THIS_MORNING_AND_I_M_F_CKING_P_SS_D_AS_SH_T = "screamed \"f*ck the police those g*dd*mn m*th*f*ck*rs.  I got a f*cking ticket this morning and I'm f*cking p*ss*d as sh*t.\"";
const string CONST_SCREAMED_DARN_THE_POLICE_THOSE_BIG_DUMB_JERKS_I_GOT_A_STUPID_TICKET_THIS_MORNING_AND_I_M_SO_ANGRY = "screamed \"[darn] the police those [big dumb jerks]. I got a [stupid] ticket this morning and I'm [so angry].\"";
const string CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_RELIEVE_THEMSELVES = "encouraged listeners to call in and relieve themselves";
const string CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_TAKE_A_PISS = "encouraged listeners to call in and take a piss";
const string CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_URINATE = "encouraged listeners to call in and [urinate]";
const string CONST_HAD_INTERCOURSE = "had intercourse";
const string CONST_FUCKED = "fucked";
const string CONST_HAD_CONSENSUAL_INTERCOURSE_IN_THE_MISSIONARY_POSITION = "[had consensual intercourse in the missionary position]";
const string CONST_REPORTEDLY = " reportedly ";
const string CONST_QUOTATION_COMMA_SPACE = "\", ";
const string CONST_APOS_S_SPACE = "'s ";
const string CONST_BROADCAST_OF_THE_PROGRAM = "broadcast of the program \"";
const string CONST_HAS_BROUGHT_RADIO_ENTERTAINMENT_TO_A_NEW_LOW_DURING_YESTERDAY_S = " has brought radio entertainment to a new low.  During yesterday's ";
const string CONST_INFAMOUS_FM_RADIO_SHOCK_JOCK = " - Infamous FM radio shock jock ";
const string CONST_OF_THE_TECH_INDUSTRY_BUT_IS_ALSO_INDICATIVE_OF_A_FULL_ECONOMIC_RECOVER_R = "of the tech industry but is also indicative of a full economic recover.&r";
const string CONST_ANALYSTS_SUGGEST_THAT_NOT_ONLY_DOES_THE_EXPANSION_SPEAK_TO_THE_HEALTH = "analysts suggest that not only does the expansion speak to the health ";
const string CONST_FUTURES_OF_SOME_OF_THE_COMPANIES_IN_THE_TECH_SECTOR_ON_THE_WHOLE_HOWEVER = "futures of some of the companies in the tech sector.  On the whole, however, ";
const string CONST_ALTHOUGH_THE_DAMPENED_MOVEMENT_MIGHT_BE_EXPECTED_DUE_TO_THE_UNCERTAIN = "although the dampened movement might be expected due to the uncertain ";
const string CONST_THE_MARKETS_REPORTEDLY_RESPONDED_TO_THE_ANNOUNCEMENT_WITH_MILD_INTEREST = "The markets reportedly responded to the announcement with mild interest, ";
const string CONST_THIS_WELCOME_NEWS_IS_BOUND_TO_BE_A_PLEASANT_SURPRISE_TO_THOSE_IN_THE_UNEMPLOYMENT_LINES = "this welcome news is bound to be a pleasant surprise to those in the unemployment lines.  ";
const string CONST_OF_LARGE_CORPORATIONS_TO_EXPORT_JOBS_OVERSEAS_THESE_DAYS = "of large corporations to export jobs overseas these days, ";
const string CONST_LIGHT_OF_THE_TENDENCY = "light of the tendency ";
const string CONST_GIVEN_THE_STATE_OF_THE_ECONOMY_RECENTLY_AND_IN = "Given the state of the economy recently and in ";
const string CONST_INCREASING_ITS_PAYROLLS_BY_OVER_TEN_THOUSAND_WORKERS_ALONE = " increasing its payrolls by over ten thousand workers alone.  ";
const string CONST_TECH_GIANT = "tech giant ";
const string CONST_ARE_EXPECTED_IN_THE_FIRST_MONTH_WITH = "are expected in the first month, with ";
const string CONST_DURING_THE_NEXT_QUARTER_OVER_THIRTY_THOUSAND_JOBS = "during the next quarter.  Over thirty thousand jobs ";
const string CONST_WILL_BE_EXPANDING_THEIR_WORK_FORCES_CONSIDERABLY = "will be expanding their work forces considerably ";
const string CONST_AT_A_JOINT_NEWS_CONFERENCE_HERE_THAT_THEY = "at a joint news conference here that they ";
const string CONST_SEVERAL_MAJOR_COMPANIES_HAVE_ANNOUNCED = " - Several major companies have announced ";
const string CONST_NEEDS_TO_TAKE_A_BREATHER_ON_THIS_ONE_WE_DON_T_SEE_WHY_THERE_S_SUCH_A_RUSH_TO_JUDGMENT_HERE = "needs to take a breather on this one.  We don't see why there's such a rush to judgment here.  ";
const string CONST_BEFORE_WE_URGE_ANY_ACTION_SOCIETY_REALLY_JUST = "before we urge any action.  Society really just ";
const string CONST_THERE_S_WORK_LEFT_TO_BE_DONE_WE_SHOULD_STUDY_MUCH_MORE = "there's work left to be done.  We should study much more ";
const string CONST_WHY_IS_THERE_CONTENTION_ON_THE_POLLUTION_QUESTION_IT_S_BECAUSE = "Why is there contention on the pollution question?  It's because ";
const string CONST_ALL_WE_VE_DONE_IS_INTRODUCED_A_LITTLE_CLARITY_INTO_THE_ONGOING_DEBATE = "All we've done is introduced a little clarity into the ongoing debate.  ";
const string CONST_THESE_ISSUES_TO_THEIR_OWN_ADVANTAGE = " these issues to their own advantage.  ";
const string CONST_YOU_HAVE_TO_REALIZE_THAT = ".  You have to realize that ";
const string CONST_A_SPOKESPERSON_STATED_THAT = "a spokesperson stated that, \"";
const string CONST_WHEN_QUESTIONED_ABOUT_THE_SCIENCE_BEHIND_THESE_RESULTS = "   When questioned about the science behind these results, ";
const string CONST_MIGHT_ACTUALLY = " might actually ";
const string CONST_AMONG_THE_MOST_STARTLING_OF_THE_THINK_TANK_S_FINDINGS_IS_THAT = "Among the most startling of the think tank's findings is that ";
const string CONST_AND_THE_LATEST_SCIENCE_ON_THE_ISSUE = "and the latest science on the issue.  ";
const string CONST_RECENTLY_RELEASED_A_WIDE_RANGING_REPORT_DETAILING_RECENT_TRENDS = " recently released a wide-ranging report detailing recent trends ";
const string CONST_POLLUTION_MIGHT_NOT_BE_SO_BAD_AFTER_ALL_THE = " - Pollution might not be so bad after all.  The ";
const string CONST_COMPLETELY_STRAPPED_FOR_CASH_R = "completely strapped for cash.&r";
const string CONST_TO_THE_CURRENT_ECONOMIC_DOLDRUMS_THAT_HAVE_LEFT_THE_STATE = "to the current economic doldrums that have left the state ";
const string CONST_HAS_STATED_THAT_THE_CASE_WILL_NOT_BE_RETRIED_DUE = "has stated that the case will not be retried, due ";
const string CONST_A_SPOKESPERSON_FOR_THE_DISTRICT_ATTORNEY = "   A spokesperson for the district attorney ";
const string CONST_THANK_YOU_FOR_SAVING_ME_FROM_MYSELF = "Thank you for saving me from myself.  ";
const string CONST_CONFESSED_AND_WAS_SENTENCED_TO_LIFE_SAYING = " confessed and was sentenced to life, saying \"";
const string CONST_COVERED_IN_THE_VICTIMS_BLOOD = "covered in the victims' blood.  ";
const string CONST_WAS_FOUND_WITH_THE_MURDER_WEAPON = " was found with the murder weapon, ";
const string CONST_AFTER_AN_INTENSIVE_MANHUNT = "After an intensive manhunt, ";
const string CONST_SLAYINGS = " slayings.  ";
const string CONST_WAS_CONVICTED_OF_THE_NOW_INFAMOUS = " was convicted of the now-infamous ";
const string CONST_TEN_YEARS_AGO = "   Ten years ago, ";
const string CONST_GRANTS_WAS_NOT_COERCED_IN_ANY_WAY_R = " grants was not coerced in any way.&r";
const string CONST_WHICH_EVEN_JUSTICE = ", which even Justice ";
const string CONST_DESPITE_THE_CONFESSION_OF = ", despite the confession of ";
const string CONST_CONSULTATIONS_WITH_A_MAGIC_8_BALL = " consultations with a Magic 8-Ball";
const string CONST_FAMILY = " family";
const string CONST_CLOSE_PERSONAL_FRIENDSHIP_WITH_THE = " close personal friendship with the ";
const string CONST_PERSONAL_PHILOSOPHY_OF_LIBERTY = " personal philosophy of liberty";
const string CONST_DESERVED_ANOTHER_CHANCE = " deserved another chance";
const string CONST_BELIEF_THAT = " belief that ";
const string CONST_BELIEF_THAT_THE_CRIMES_WERE_A_VAST_RIGHT_WING_CONSPIRACY = " belief that the crimes were a vast right-wing conspiracy";
const string CONST_GENERAL_FEELING_ABOUT_POLICE_CORRUPTION = " general feeling about police corruption";
const string CONST_TEN_YEAR_OLD_EYEWITNESS_TESTIMONY = "ten-year-old eyewitness testimony";
const string CONST_MADE_THE_DECISION_BASED_ON = "made the decision based on ";
const string CONST_OF_THE_NOTORIOUSLY_LIBERAL_CIRCUIT_OF_APPEALS_HERE = " of the notoriously liberal circuit of appeals here ";
const string CONST_JUSTICE = "Justice ";
const string CONST_WAS_OVERTURNED_BY_A_FEDERAL_JUDGE_YESTERDAY = " was overturned by a federal judge yesterday.  ";
const string CONST_THE_CONVICTION_OF_CONFESSED_SERIAL_KILLER = " - The conviction of confessed serial killer ";
const string CONST_BUT_THE_GM_INDUSTRY_OPERATES_AT_A_HIGHER_ETHICAL_STANDARD_THAT_GOES_WITHOUT_SAYING = "but the GM industry operates at a higher ethical standard.  That goes without saying.";
const string CONST_NO_THAT_S_JUST_RIDICULOUS_I_MEAN_SURE_COMPANIES_HAVE_PUT_UNSAFE_PRODUCTS_OUT = "No.  That's just ridiculous.  I mean, sure companies have put unsafe products out, ";
const string CONST_WOULD_WE_STAKE_THE_REPUTATION_OF_OUR_COMPANY_ON_UNSAFE_PRODUCTS = ".  Would we stake the reputation of our company on unsafe products?  ";
const string CONST_IS_JUST_A_LOAD_OF = " is just a load of ";
const string CONST_LOOK_THESE_PRODUCTS_ARE_SAFE_THAT_THING_ABOUT_THE = "Look, these products are safe.  That thing about the ";
const string CONST_ONE_IN_PARTICULAR_SAID = "One in particular said, \"";
const string CONST_IN_THEIR_DISMISSAL_OF_THE_CRITICISM_WHICH_OFTEN_FOLLOWS_THE_INDUSTRY = "in their dismissal of the criticism which often follows the industry.  ";
const string CONST_SPOKESPEOPLE_FOR_THE_GM_CORPORATIONS_WERE_UNIVERSAL = "   Spokespeople for the GM corporations were universal ";
const string CONST_THIS_AMAZING_NEW_PRODUCT_ACTUALLY = "this amazing new product actually ";
const string CONST_ACCORDING_TO_THE_PUBLIC_RELATIONS_REPRESENTATIVE_SPEAKING = "According to the public relations representative speaking, ";
const string CONST_DURING_AN_AFTERNOON_POWERPOINT_PRESENTATION = "\", during an afternoon PowerPoint presentation.  ";
const string CONST_PRESENTED_THEIR_PRODUCT = ", presented their product, \"";
const string CONST_ONE_SUCH_CORPORATION = "   One such corporation, ";
const string CONST_BOOTHS_AND_GAVE_TALKS_TO_WIDE_EYED_ONLOOKERS = "booths and gave talks to wide-eyed onlookers.";
const string CONST_TO_SHOWCASE_ITS_UPCOMING_PRODUCTS_OVER_THIRTY_COMPANIES_SET_UP = "to showcase its upcoming products.  Over thirty companies set up ";
const string CONST_THE_GENETIC_FOODS_INDUSTRY_STAGED_A_MAJOR_EVENT_HERE_YESTERDAY = " - The genetic foods industry staged a major event here yesterday ";
const string CONST_THIS_NEW_AGE = "this new age.";
const string CONST_FOR_WHAT_WE_FEEL_ARE_THE_ESSENTIAL_TOOLS_FOR_COMBATING_TERRORISM_IN = "for what we feel are the essential tools for combating terrorism in ";
const string CONST_THE_HEAD_OF_THE_AGENCY_WILL_BE_SENDING_A_REQUEST_TO_CONGRESS = "The Head of the Agency will be sending a request to Congress ";
const string CONST_HOWEVER_LET_ME_ALSO_SAY_THAT_THERE_S_MORE_THAT_NEEDS_TO_BE_DONE = "However, let me also say that there's more that needs to be done.  ";
const string CONST_CIVILIZATION_BEFORE_THEY_CAN_DESTROY_AMERICAN_FAMILIES = "civilization before they can destroy American families.  ";
const string CONST_PROVIDING_US_WITH_THE_TOOLS_WE_NEED_TO_NEUTRALIZE_THESE_ENEMIES_OF = "providing us with the tools we need to neutralize these enemies of ";
const string CONST_THAT_WE_ARE_GRATEFUL_TO_THE_CONGRESS_AND_THIS_ADMINISTRATION_FOR = "that we are grateful to the Congress and this Administration for ";
const string CONST_I_WON_T_COMPROMISE_OUR_SOURCES_AND_METHODS_BUT_LET_ME_JUST_SAY = "I won't compromise our sources and methods, but let me just say ";
const string CONST_WAS_TO_OCCUR = "was to occur.";
const string CONST_TERRORIST_ORGANIZATION_ALLOWED_THE_PLOT_TO_BE_FOILED_JUST_DAYS_BEFORE_IT = "terrorist organization allowed the plot to be foiled just days before it ";
const string CONST_HOWEVER_INTELLIGENCE_GARNERED_FROM_DEEP_WITHIN_THE_MYSTERIOUS = ".  However, intelligence garnered from deep within the mysterious ";
const string CONST_PLANNED_TO = " planned to ";
const string CONST_ACCORDING_TO_A_SPOKESPERSON_FOR_THE_AGENCY = "   According to a spokesperson for the agency, ";
const string CONST_WOULD_HAVE_OCCURRED_ON_AMERICAN_SOIL = "would have occurred on American soil.";
const string CONST_WASHINGTON_DC_THE_CIA_ANNOUNCED_YESTERDAY_THAT_IT_HAS_AVERTED_A_TERROR_ATTACK_THAT = "Washington, DC - The CIA announced yesterday that it has averted a terror attack that ";
const string CONST_THE_FIRST_PHASE_OF_HUMAN_TRIALS_IS_SLATED_TO_BEGIN_IN_A_FEW_MONTHS = "   The first phase of human trials is slated to begin in a few months.";
const string CONST_I_THINK_THE_MEDIA_SHOULD_BE_FOCUSING_ON_THE_ENORMOUS_BENEFITS_OF_THIS_DRUG = "I think the media should be focusing on the enormous benefits of this drug.";
const string CONST_WHILE_WE_UNDERSTAND_YOUR_CONCERNS_ANY_WORRIES_ARE_ENTIRELY_UNFOUNDED = "While we understand your concerns, any worries are entirely unfounded.  ";
const string CONST_WE_HAVE_A_VERY_EXPERIENCED_RESEARCH_TEAM = ".  We have a very experienced research team.  ";
const string CONST_A_SPOKESPERSON_FOR_THE_RESEARCH_TEAM_STATED_THAT_IT_REALLY_ISN_T_SO_BAD_AS_ALL_THAT_CHIMPANZEES_ARE_VERY_RESILIENT_CREATURES = "a spokesperson for the research team stated that, \"It really isn't so bad as all that.  Chimpanzees are very resilient creatures.  ";
const string CONST_FIELDING_QUESTIONS_ABOUT_THE_ETHICS_OF_THEIR_EXPERIMENTS_FROM_REPORTERS_DURING_A_PRESS_CONFERENCE_YESTERDAY = "Fielding questions about the ethics of their experiments from reporters during a press conference yesterday, ";
const string CONST_DOT_SPACE = ". ";
const string CONST_ALONG_WITH_BONOBOS_CHIMPANZEES_ARE_OUR_CLOSEST_COUSINS = "   Along with bonobos, chimpanzees are our closest cousins";
const string CONST_CORRECTS_ERECTILE_DYSFUNCTION_IN_CHIMPANZEES = "corrects erectile dysfunction in chimpanzees";
const string CONST_HELPS_CHIMPANZEES_REPRODUCE = "[helps chimpanzees reproduce]";
const string CONST_THE_DRUG_APPARENTLY = ", the drug apparently ";
const string CONST_ANAL = "Anal";
const string CONST_BUM_BUM = "Bum-Bum";
const string CONST_CALLED = "Called ";
const string CONST_HERE_REPORT_THAT_THEY_HAVE_DISCOVERED_AN_AMAZING_NEW_WONDER_DRUG = "here report that they have discovered an amazing new wonder drug.  ";
const string CONST_REPORT_THAT_THEY_HAVE_DISCOVERED_AN_AMAZING_NEW_WONDER_DRUG = " report that they have discovered an amazing new wonder drug. ";
const string CONST_FROM = "from ";
const string CONST_RESEARCHERS = " - Researchers ";
const string CONST_THE_DEATH_PENALTY_IN_THIS_CASE = "the death penalty in this case.";
const string CONST_LIFE_IMPRISONMENT_IN_THIS_CASE = "life imprisonment in this case.";
const string CONST_SEEKING = "seeking ";
const string CONST_THE_DISTRICT_ATTORNEY_S_OFFICE_HAS_ALREADY_REPEATEDLY_SAID_IT_WILL_BE = "   The district attorney's office has already repeatedly said it will be ";
const string CONST_SOURCES_SAY_THAT_THE_POLICE_GOT_A_BREAK_IN_THE_CASE_WHEN = ".  Sources say that the police got a break in the case when ";
const string CONST_DEAD_AND = " dead and ";
const string CONST_IN_A_BETTER_PLACE = " [in a better place]";
const string CONST_ONLY_TO_TURN_UP_LATER = "only to turn up later";
const string CONST_OVER_TWENTY_CHILDREN_IN_THE_PAST_TWO_YEARS_HAVE_GONE_MISSING = ".  Over twenty children in the past two years have gone missing, ";
const string CONST_WAS_DETAINED_YESTERDAY_AFTERNOON_REPORTEDLY_IN_POSSESSION_OF = " was detained yesterday afternoon, reportedly in possession of ";
const string CONST_ACCORDING_TO_A_SPOKESPERSON_FOR_THE_POLICE_DEPARTMENT_HERE = "according to a spokesperson for the police department here.  ";
const string CONST_STRING_OF_BRUTAL_CHILD_KILLINGS_THAT_HAS_KEPT_EVERYONE_IN_THE_AREA_ON_EDGE = "string of brutal child killings that has kept everyone in the area on edge, ";
const string CONST_THE_AUTHORITIES_HAVE_APPREHENDED_THEIR_PRIMARY_SUSPECT_IN_THE = "The authorities have apprehended their primary suspect in the ";
const string CONST_PERHAPS_PARENTS_CAN_REST_EASIER_TONIGHT = " - Perhaps parents can rest easier tonight.  ";
const string CONST_DOT_QUOTATION_MARK = ".\"";
const string CONST_CHOICE_AND_I_WOULD_ONLY_HAVE_A_FEW_SECONDS_BEFORE_THEY_MADE_IT_FOR_ME = " choice, and I would only have a few seconds before they made it for me";
const string CONST_HELLUVA = "helluva";
const string CONST_DIFFICULT = "[difficult]";
const string CONST_THE_OTHER_A = " the other.  A ";
const string CONST_AIDS = "AIDS";
const string CONST_GRIDS = "GRIDS";
const string CONST_MAYBE_LOSE_AN_EYE_THE_ONE_WAY_MAYBE_CATCH = "Maybe lose an eye the one way, maybe catch ";
const string CONST_MY_SHANK_S_UNDER_THE_MATTRESS_BETTER_TO_BE_BRAVE_AND_FIGHT_OR_CHICKEN_OUT_AND_LET_THEM_TAKE_IT = "My shank's under the mattress.  Better to be brave and fight or chicken out and let them take it?  ";
const string CONST_WITH_DARK_GLARES_OF_BARE_LUST_AS_FOOTBALL_PLAYERS_MIGHT_STARE_AT_A_STUPEFIED_DRUNKEN_HELPLESS_TEENAGER = "with dark glares of bare lust, as football players might stare at a stupefied, drunken, helpless teenager.  ";
const string CONST_I_WAS_TRAPPED_WITH_THEM_NOW_THERE_WERE_THREE_LOOKING_ME_OVER = "I was trapped with them now.  There were three, looking me over ";
const string CONST_COMING_TO_A_HALT_WITH_A_DEAFENING_CLANG_THAT_SAID_IT_ALL = "coming to a halt with a deafening clang that said it all 컴 ";
const string CONST_THE_STEEL_BARS_GRATED_FORWARD_IN_THEIR_RAILS = "The steel bars grated forward in their rails, ";
const string CONST_TAKE_THIS_EXCERPT = "   Take this excerpt, \"";
const string CONST_UNDERSCORE_DOT_AMPERSAND_R = "_.&r";
const string CONST_BUTTLORD = "Buttlord";
const string CONST_BUMLORD = "[Bum]lord";
const string CONST_UNDERSCORE = "_";
const string CONST_S_NEW_TOUR_DE_FORCE = "'s new tour-de-force, _";
const string CONST_ORANGE_IS_THE_NEW_BLACK = "Orange is the New Black";
const string CONST_HAVE_THESE_WORKS_BEEN_AS_POIGNANT_AS = "have these works been as poignant as ";
const string CONST_PRISON_THEME_LATELY_IN_ITS_OFFERINGS_FOR_MASS_CONSUMPTION_RARELY = "prison theme lately in its offerings for mass consumption, rarely ";
const string CONST_ALTHOUGH_POPULAR_CULTURE_HAS_USED_OR_PERHAPS_OVERUSED_THE = "Although popular culture has used, or perhaps overused, the ";
const string CONST_DETAIL_WHAT_GOES_ON_BEHIND_BARS = "detail what goes on behind bars.  ";
const string CONST_A_FORMER_PRISONER_HAS_WRITTEN_A_BOOK_DESCRIBING_IN_HORRIFYING = " - A former prisoner has written a book describing in horrifying ";
const string CONST_WAS_DISTURBINGLY_OBSESSED_WITH_GUNS_AND_DEATH_R = " was disturbingly obsessed with guns and death.&r";
const string CONST_SHE = "she";
const string CONST_REPORTS_INDICATE_THAT_THE_STUDENT_KEPT_A_JOURNAL_THAT_SHOWED = "reports indicate that the student kept a journal that showed ";
const string CONST_INVESTIGATORS_ARE_CURRENTLY_SEARCHING_THE_STUDENT_S_BELONGINGS_AND_INITIAL = "  Investigators are currently searching the student's belongings, and initial ";
const string CONST_SHORTLY_AFTERWARDS_R = " shortly afterwards.&r";
const string CONST_COMMITTED_SUICIDE = " committed suicide";
const string CONST_FEEL_DEEPLY_ASLEEP = " [feel deeply asleep]";
const string CONST_AND_WOUNDED_DOZENS_MORE = " and wounded dozens more.  ";
const string CONST_HURT_SOME_PEOPLE = "[hurt some people].  ";
const string CONST_WHEN_THE_POLICE_ARRIVED_THE_STUDENT_HAD_ALREADY = "  When the police arrived, the student had already ";
const string CONST_AS_WELL_R = " as well.&r";
const string CONST_SHOT = "shot";
const string CONST_UNFORTUNATELY_HARMED = "[unfortunately harmed]";
const string CONST_THEY_WERE = ", they were ";
const string CONST_WHEN_OTHER_STUDENTS_TRIED_TO_WRESTLE_THE_WEAPONS_AWAY_FROM = "When other students tried to wrestle the weapons away from ";
const string CONST_STUDENTS_AND_TEACHERS_INSIDE = " students and teachers inside.  ";
const string CONST_SPRAYING_BULLETS_AT = "spraying bullets at";
const string CONST_SCARING = "[scaring]";
const string CONST_CLASSROOMS = "classrooms, ";
const string CONST_WHILE_CLASSES_WERE_IN_SESSION_THEN_SYSTEMATICALLY_STARTED_BREAKING_INTO = " while classes were in session, then systematically started breaking into ";
const string CONST_UNIVERSITY_LOWERCASE = "university ";
const string CONST_SCHOOL = "school ";
const string CONST_ENTERED_THE = " entered the ";
const string CONST_UNIVERSITY_UPPER_CASE = " University";
const string CONST_HIGH_SCHOOL_UPPER_CASE = " High School";
const string CONST_MIDDLE_SCHOOL_UPPER_CASE = " Middle School";
const string CONST_ELEMENTARY_SCHOOL_UPPER_CASE = " Elementary School";
const string CONST_MORE_THAN_A_DOZEN_CLASSMATES_AND_TWO_TEACHERS_AT = " more than a dozen classmates and two teachers at ";
const string CONST_MOW_DOWN = "mow down";
const string CONST_SCARE = "[scare]";
const string CONST_USED_A_VARIETY_OF_GUNS_TO = ", used a variety of guns to ";
const string CONST_UNIVERSITY = "university";
const string CONST_HIGH_SCHOOL = "high school";
const string CONST_MIDDLE_SCHOOL = "middle school";
const string CONST_ELEMENTARY_SCHOOL = "elementary school";
const string CONST_AT_A_LOCAL = " at a local ";
const string CONST_SHOOTING_RAMPAGE = "shooting rampage";
const string CONST_A_STUDENT_HAS_GONE_ON_A = "A student has gone on a ";
const string CONST_TO_THE_FM_BAND = "to the FM band.";
const string CONST_PASTURES_OF_THESE_MANY_SAID_THAT_THEY_WOULD_BE_SWITCHING_OVER = "pastures.  Of these, many said that they would be switching over ";
const string CONST_HAVE_DECIDED_TO_LEAVE_THE_PROGRAM_FOR_SANER = "have decided to leave the program for saner ";
const string CONST_FULLY_HALF_OF_THE_HOST_S_MOST_LOYAL_SUPPORTERS = "fully half of the host's most loyal supporters ";
const string CONST_ACCORDING_TO_A_POLL_COMPLETED_YESTERDAY = "According to a poll completed yesterday, ";
const string CONST_THE_DAMAGE_MIGHT_ALREADY_BE_DONE = "the damage might already be done.  ";
const string CONST_ISSUED_AN_APOLOGY_LATER_IN_THE_PROGRAM_BUT = " issued an apology later in the program, but ";
const string CONST_G_DD_MN_MIND = " g*dd*mn mind";
const string CONST_GOSH_DARN_MIND = " [gosh darn] mind";
const string CONST_GODDAMN_MIND = " goddamn mind";
const string CONST_HIS = "his";
const string CONST_LOST = "lost ";
const string CONST_HAD = " had ";
const string CONST_A_FORMER_FAN_OF_THE_SHOW = "\", a former fan of the show, ";
const string CONST_LIBERAL_MEDIA_ESTABLISHMENT = "liberal media establishment!";
const string CONST_CURRENT_PRESIDENT = "current president!";
const string CONST_AND_THE_GREATEST_LIVING_EXAMPLE_OF_A_REVERSE_RACIST_IS_THE = "and the greatest living example of a reverse racist is the ";
const string CONST_S_MONOLOGUE_FOR_THE_EVENING_BEGAN_THE_WAY_THAT_FANS = "'s monologue for the evening began the way that fans ";
const string CONST_QUOTATION_PERIOD = "\".";
const string CONST_WENT_OFF_FOR_FIFTEEN_MINUTES_IN_AN_INEXPLICABLE_RANT = " went off for fifteen minutes in an inexplicable rant ";
const string CONST_WELL_KNOWN_AM_RADIO_PERSONALITY = " - Well-known AM radio personality ";
const string CONST_THE_JUDGE_WOULD_BE_GOING_ON_A_BIBLE_RETREAT_FOR_A_FEW_WEEKS_TO = "the judge would be going on a Bible retreat for a few weeks to ";
const string CONST_COULD_NOT_BE_REACHED_FOR_COMMENT_ALTHOUGH_AN_AID_STATED_THAT = " could not be reached for comment, although an aid stated that ";
const string CONST_IN_EXCHANGE_FOR_THEIR_SILENCE = " in exchange for their silence.";
const string CONST_REPORTEDLY_OFFERED = " reportedly offered ";
const string CONST_WHEN_POLICE_BROKE_INTO_THE_HOTEL_ROOM_THEY_SAW = "when police broke into the hotel room they saw ";
const string CONST_ACCORDING_TO_SOURCES_FAMILIAR_WITH_THE_PARTICULARS = "According to sources familiar with the particulars, ";
const string CONST_LAST_WEEK_IN_A_HOTEL_DURING_A_POLICE_STING_OPERATION = " last week in a hotel during a police sting operation.  ";
const string CONST_WAS_FOUND_WITH = ", was found with ";
const string CONST_WHO_ONCE = ", who once ";
const string CONST_HAS_RESIGNED_IN_DISGRACE_AFTER_BEING_CAUGHT_WITH_A_PROSTITUTE = " has resigned in disgrace after being caught with a prostitute.";
const string CONST_HAS_RESIGNED_IN_DISGRACE_AFTER_BEING_CAUGHT_WITH_A_CIVIL_SERVANT = " has resigned in disgrace after being caught with a [civil servant].";
const string CONST_CONSERVATIVE_FEDERAL_JUDGE = " - Conservative federal judge ";
const string CONST_QUESTION_MARK = "?";
const string CONST_MAMMA_WHY_DID_THEY_KILL = "Mamma, why did they kill ";
const string CONST_DEAD = " dead?";
const string CONST_MAMMA_IS = "Mamma, is ";
const string CONST_MANY_AREA_CHILDREN_SPONTANEOUSLY_BROKE_INTO_TEARS_ONE_CHILD_WAS = "many area children spontaneously broke into tears.  One child was ";
const string CONST_WHEN_THE_DECISION_TO_BAN_THE_BOOK_WAS_ANNOUNCED_YESTERDAY = "   When the decision to ban the book was announced yesterday, ";
const string CONST_AS_KEY_EVIDENCE_OF_THE_DARK_NATURE_OF_THE_BOOK = " as key evidence of the dark nature of the book.";
const string CONST_A_CHILD_THAT = "a child that ";
const string CONST_A_CHILD_THAT_SAID_A_MAGIC_SPELL_AT_HER_PARENTS = "a child that said a magic spell at her parents";
const string CONST_A_CHILD_THAT_SWORE_IN_CLASS = "a child that swore in class";
const string CONST_IN_THEIR_COMPLAINT_THE_GROUPS_CITED_AN_INCIDENT_INVOLVING = "In their complaint, the groups cited an incident involving ";
const string CONST_SOME_CONSERVATIVES_FEEL_THAT_THE_BOOKS = "some conservatives feel that the books ";
const string CONST_ALTHOUGH_THE_SERIES_IS_ADORED_BY_CHILDREN_WORLDWIDE = "Although the series is adored by children worldwide, ";
const string CONST_PERIOD_SPACE = ". ";
const string CONST_AUTHOR = " author ";
const string CONST_IS_THE_THIRD_IN_AN_IMMENSELY_POPULAR_SERIES_BY = "_, is the third in an immensely popular series by ";
const string CONST_AND_THE = "_and_the_";
const string CONST_THE_BOOK = "   The book, ";
const string CONST_THE_CITY_BOWED_TO_PRESSURE_FROM_RELIGIOUS_GROUPS = "the city bowed to pressure from religious groups.";
const string CONST_A_CHILDREN_S_STORY_HAS_BEEN_REMOVED_FROM_LIBRARIES_HERE_AFTER = " - A children's story has been removed from libraries here after ";
const string CONST_YOU_THINK_ABOUT_THAT_BEFORE_YOU_CONTINUE_SLANGING_ACCUSATIONS = "You think about that before you continue slanging accusations";
const string CONST_THESE_FILES_DEAL_WITH_THE_ONE_AND_NOT_THE_OTHER = "these files deal with the one and not the other.  ";
const string CONST_IT_MIGHT_BE_A_BIT_PRESUMPTIVE_TO_ASSUME_THAT = "It might be a bit presumptive to assume that ";
const string CONST_WELL_YOU_KNOW_THERE_S_PRIVACY_AND_THERE_S_PRIVACY = "Well, you know, there's privacy, and there's privacy.  ";
const string CONST_THE_FBI_REFUSED_TO_COMMENT_INITIALLY_BUT_WHEN_CONFRONTED_WITH_THE_INFORMATION = "  The FBI refused to comment initially, but when confronted with the information, ";
const string CONST_DEAL_WITH_THE_UNDESIRABLES_ALTHOUGH_THIS_PHRASE_IS_NOT_CLARIFIED = "\"deal with the undesirables\", although this phrase is not clarified.  ";
const string CONST_MORE_DISTURBINGLY_THE_FILES_MAKE_REFERENCE_TO_A_PLAN_TO = "  More disturbingly, the files make reference to a plan to ";
const string CONST_UNIONS_WORKING_FOR_LIBERAL_ORGANIZATIONS_EVEN = "unions, working for liberal organizations 컴 even ";
const string CONST_THE_FILES_CONTAIN_INFORMATION_ON_WHICH_PEOPLE_HAVE_BEEN_ATTENDING_DEMONSTRATIONS_ORGANIZING = "The files contain information on which people have been attending demonstrations, organizing ";
const string CONST_THIS_NEWSPAPER_YESTERDAY_RECEIVED_A_COLLECTION_OF_FILES_FROM_A_SOURCE_IN_THE_FEDERAL_BUREAU_OF_INVESTIGATIONS = "This newspaper yesterday received a collection of files from a source in the Federal Bureau of Investigations.  ";
const string CONST_WASHINGTON_DC_THE_FBI_MIGHT_BE_KEEPING_TABS_ON_YOU = "Washington, DC - The FBI might be keeping tabs on you.  ";
const string CONST_CAN_BE_PUT_TO_DEATH_IN_THIS_COUNTRY = "can be put to death in this country.";
const string CONST_TRAGEDY_IT_WILL_BE_THAT_OUR_NATION_IS_NOW_EVALUATING_THE_EASE_WITH_WHICH_PEOPLE = "tragedy, it will be that our nation is now evaluating the ease with which people ";
const string CONST_AND_MORE_EVENTS_ARE_EXPECTED_THIS_EVENING_IF_THERE_IS_A_BRIGHT_SIDE_TO_BE_FOUND_FROM_THIS = "and more events are expected this evening.  If there is a bright side to be found from this ";
const string CONST_CANDLELIGHT_VIGILS_WERE_HELD_THROUGHOUT_THE_COUNTRY_LAST_NIGHT_DURING_THE_EXECUTION = "  Candlelight vigils were held throughout the country last night during the execution, ";
const string CONST_THE_FAMILY_WANTS_CLOSURE_WE_DON_T_HAVE_TIME_FOR_ANOTHER_TRIAL = "The family wants closure.  We don't have time for another trial";
const string CONST_END_OF_STORY = "End of story";
const string CONST_ASSASSIN_SERIAL_KILLER_EITHER_WAY_GUILTY = "Assassin, serial killer, either way 컴 guilty.  ";
const string CONST_THE_CONVICT_IS_ALWAYS_REFERRED_TO_BY_THREE_NAMES = "The convict is always referred to by three names.  ";
const string CONST_LET_S_NOT_FORGET_THE_CONVICT_IS_COLORED_YOU_KNOW_HOW_THEIR_KIND_ARE = "Let's not forget the convict is colored.  You know how their kind are";
const string CONST_SPOKESPERSON_FOR_THE_GOVERNOR_SAYING = "spokesperson for the governor saying, ";
const string CONST_THE_STATE_STILL_WENT_THROUGH_WITH_THE_EXECUTION_WITH_A = "The state still went through with the execution, with a ";
const string CONST_WAS_FRAMED = " was framed.  ";
const string CONST_AN_ADMISSION_FROM_A_FORMER_PROSECUTOR_THAT = "an admission from a former prosecutor that ";
const string CONST_A_BATTERY_OF_NEGATIVE_DNA_TESTS = "a battery of negative DNA tests.  ";
const string CONST_A_CONFESSION_FROM_ANOTHER_CONVICT = "a confession from another convict.  ";
const string CONST_HAVE_BEEN_PRODUCED_INCLUDING = "have been produced, including ";
const string CONST_SINCE_THEN_NUMEROUS_PIECES_OF_EXCULPATORY_EVIDENCE = "Since then, numerous pieces of exculpatory evidence ";
const string CONST_OF_13_SERIAL_MURDERS = " of 13 serial murders.  ";
const string CONST_WAS_CONVICTED_IN = " was convicted in ";
const string CONST_CORRECTIONAL_FACILITY_R = " Correctional Facility.&r";
const string CONST_YESTERDAY_AT_THE = " yesterday at the ";
const string CONST_SINGLE_COLON = ":";
const string CONST_WAS_PRONOUNCED_DEAD_AT = " was pronounced dead at ";
const string CONST_AN_INNOCENT_CITIZEN_HAS_BEEN_PUT_TO_DEATH_IN_THE_ELECTRIC_CHAIR = " - An innocent citizen has been put to death in the electric chair.  ";
const string CONST_EVEN_THOUGH_BEING_GAY_IS_DEVIANT_AS_WE_ALL_KNOW = ", even though being gay is deviant, as we all know.";
const string CONST_IS_A_KNOWN_FAGGOT = " is a known faggot";
const string CONST_DESPITE_THE_FACT_THAT = ", despite the fact that ";
const string CONST_AGGRAVATED_NATURE_OF_THE_OFFENSE = "aggravated nature of the offense";
const string CONST_PROSECUTE_THIS_CASE_AS_A_HATE_CRIME_DUE_TO_THE = "prosecute this case as a hate crime, due to the ";
const string CONST_AUTHORITIES_HAVE_STATED_THAT_THEY_WILL_VIGOROUSLY = "  Authorities have stated that they will vigorously ";
const string CONST_AT_WHICH_POINT_THEY_WERE_TAKEN_INTO_CUSTODY_NOBODY_WAS_SERIOUSLY_INJURED_DURING_THE_INCIDENT = "at which point they were taken into custody.  Nobody was seriously injured during the incident.";
const string CONST_THE_CHASE_ENDED_WHEN = "The chase ended when ";
const string CONST_AT_THE_PURSUING_POLICE_CRUISERS = " at the pursuing police cruisers.  ";
const string CONST_TAKING_SWIPES = "taking swipes";
const string CONST_URINATING_OUT_THE_WINDOW = "urinating out the window";
const string CONST_PISSING_OUT_THE_WINDOW = "pissing out the window";
const string CONST_RELIEVING_THEMSELVES_OUT_THE_WINDOW = "[relieving themselves] out the window";
const string CONST_THROWING_BEER_BOTTLES = "throwing beer bottles";
const string CONST_THROWING_JUICE_BOXES = "throwing [juice boxes]";
const string CONST_MURDERERS_SWERVING_WILDLY = "murderers swerving wildly, ";
const string CONST_WITNESSES_OF_THE_FREEWAY_CHASE_DESCRIBED_THE_PICKUP_OF_THE_ALLEGED = "  Witnesses of the freeway chase described the pickup of the alleged ";
const string CONST_HAVE_NOT_YET_BEEN_RELEASED = "have not yet been released.";
const string CONST_WERE_APPREHENDED_AFTER_A_HIGH_SPEED_CHASE_THEIR_NAMES = "were apprehended after a high speed chase.  Their names ";
const string CONST_A_POLICE_SPOKESPERSON_REPORTED_THAT_FOUR_SUSPECTS = "A police spokesperson reported that four suspects ";
const string CONST_HERE_YESTERDAY = " here yesterday.  ";
const string CONST_A_HOMOSEXUAL_WAS = "a homosexual, was ";
const string CONST_A_KNOWN_HOMOSEXUAL_WAS = "a known homosexual, was ";
const string CONST_A_KNOWN_SEXUAL_DEVIANT_WAS = "a known sexual deviant, was ";
const string CONST_CHILDREN_R = " children.&r";
const string CONST_FIVE = "five";
const string CONST_FOUR = "four";
const string CONST_THREE = "three";
const string CONST_TWO = "two";
const string CONST_SPACE_AND_SPACE = " and ";
const string CONST_WIFE = "wife";
const string CONST_IS_SURVIVED_BY = " is survived by ";
const string CONST_HAD_BEEN_COMPLETED_R = "had been completed.&r";
const string CONST_SURRENDERED_WITHOUT_A_STRUGGLE_REPORTEDLY_SAYING_THAT_GOD_S_WORK = " surrendered without a struggle, reportedly saying that God's work ";
const string CONST_ABORTION_DOCTORS_AS_OPPOSED_TO_ARRESTING_THEM_R = " abortion doctors as opposed to arresting them.&r";
const string CONST_LATER_ADMITTED_TO_BEING_A_ROGUE_FBI_VIGILANTE_HUNTING_DOWN = " later admitted to being a rogue FBI vigilante, hunting down ";
const string CONST_CALLED_THE_POLICE_ON_A_CELLPHONE_AND_THEY_ARRIVED_SHORTLY_THEREAFTER = "called the police on a cellphone and they arrived shortly thereafter.  ";
const string CONST_VERSES_OF_THE_BIBLE_AT_THE_STUNNED_ONLOOKERS_SOMEONE = "verses of the Bible at the stunned onlookers.  Someone ";
const string CONST_REMAINED_AT_THE_SCENE_AFTER_THE_SHOOTING_SCREAMING = " remained at the scene after the shooting, screaming ";
const string CONST_WITNESSES_REPORT_THAT = "  Witnesses report that ";
const string CONST_IS_IN_CUSTODY_R = ", is in custody.&r";
const string CONST_THE_SUSPECTED_SHOOTER = "The suspected shooter, ";
const string CONST_TIMES_AND_DIED_IMMEDIATELY_IN_THE_PARKING_LOT = " times and died immediately in the parking lot.  ";
const string CONST_WAS_HIT = " was hit ";
const string CONST_SHOTS_WERE_FIRED_FROM_A_NEARBY_VEHICLE = "shots were fired from a nearby vehicle.  ";
const string CONST_CAR_WHEN_ACCORDING_TO_POLICE_REPORTS = " car when, according to police reports, ";
const string CONST_WAS_WALKING_TO = " was walking to ";
const string CONST_DR = "Dr. ";
const string CONST_CLINIC_YESTERDAY = " Clinic yesterday.  ";
const string CONST_GUNNED_DOWN_OUTSIDE_OF_THE = "gunned down outside of the ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ABORTIONS_WAS_RUTHLESSLY = "A doctor that routinely performed abortions was ruthlessly ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_SEMI_LEGAL_ABORTIONS_WAS_RUTHLESSLY = "A doctor that routinely performed semi-legal abortions was ruthlessly ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ILLEGAL_ABORTIONS_WAS_RUTHLESSLY = "A doctor that routinely performed illegal abortions was ruthlessly ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ILLEGAL_ABORTION_MURDERS_WAS_RUTHLESSLY = "A doctor that routinely performed illegal abortion-murders was ruthlessly ";
const string CONST_TILDA = "~";
const string AMPERSAND_R = "&r";
const string CONST_FORTUNATELY_THE_CCS_THUGS_WERE_STOPPED_BY_BRAVE_CITIZENS = "Fortunately, the CCS thugs were stopped by brave citizens.  ";
const string CONST_EVERYONE_IN_THE_CCS_GROUP_WAS_ARRESTED_OR_KILLED = "Everyone in the CCS group was arrested or killed.  ";
const string CONST_FORTUNATELY_THE_LCS_THUGS_WERE_STOPPED_BY_BRAVE_CITIZENS = "Fortunately, the LCS thugs were stopped by brave citizens.  ";
const string CONST_EVERYONE_IN_THE_LCS_GROUP_WAS_ARRESTED_OR_KILLED = "Everyone in the LCS group was arrested or killed.  ";
const string CONST_UNFORTUNATELY_THE_LCS_GROUP_WAS_DEFEATED_BY_THE_FORCES_OF_EVIL = "Unfortunately, the LCS group was defeated by the forces of evil.  ";
const string CONST_A_LIBERAL_CRIME_SQUAD_OPERATION_WENT_HORRIBLY_WRONG_AND_CAME_TO_A_TRAGIC_END = "A Liberal Crime Squad operation went horribly wrong, and came to a tragic end.  ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_HAS_GONE_ON_A_RAMPAGE_AND_THEY_GOT_WHAT_THEY_DESERVED = "The Liberal Crime Squad has gone on a rampage, and they got what they deserved.  ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_HAS_STRUCK_AGAIN_ALBEIT_WITH_A_TRAGIC_END = "The Liberal Crime Squad has struck again, albeit with a tragic end.  ";
const string CONST_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT_SPACE = "to a spokesperson from the police department.  ";
const string CONST_WENT_ON_A_SUICIDAL_RAMPAGE_YESTERDAY_ACCORDING = "went on a suicidal rampage yesterday, according ";
const string CONST_A_GROUP_OF_THUGS_CALLING_ITSELF_THE_LIBERAL_CRIME_SQUAD = "A group of thugs calling itself the Liberal Crime Squad ";
const string CONST_BURST_BRIEFLY_ONTO_THE_SCENE_OF_POLITICAL_ACTIVISM_YESTERDAY_ACCORDING = "burst briefly onto the scene of political activism yesterday, according ";
const string CONST_A_GROUP_CALLING_ITSELF_THE_LIBERAL_CRIME_SQUAD = "A group calling itself the Liberal Crime Squad ";
const string CONST_THE_CONSERVATIVE_CRIME_SQUAD_HAS_GONE_ON_ANOTHER_RAMPAGE_AND_THEY_GOT_WHAT_THEY_DESERVED = "The Conservative Crime Squad has gone on another rampage, and they got what they deserved.  ";
const string CONST_THE_CONSERVATIVE_CRIME_SQUAD_HAS_STRUCK_AGAIN_ALBEIT_WITH_A_TRAGIC_END = "The Conservative Crime Squad has struck again, albeit with a tragic end.  ";
const string CONST_RAMPAGE_YESTERDAY_ACCORDING_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT = "rampage yesterday, according to a spokesperson from the police department.  ";
const string CONST_CALLING_THEMSELVES_THE_CONSERVATIVE_CRIME_SQUAD_WENT_ON_A = "calling themselves the Conservative Crime Squad went on a ";
const string CONST_M16_TOTING = "M16-toting ";
const string CONST_A_GROUP_OF = "A group of ";
const string CONST_A_GROUP_OF_M16_WIELDING_VIGILANTES_CALLING_THEMSELVES_THE_CONSERVATIVE_CRIME_SQUAD = "A group of M16-wielding vigilantes calling themselves the Conservative Crime Squad ";
const string CONST_THE_CONSERVATIVE_CRIME_SQUAD_HAS_GONE_ON_ANOTHER_RAMPAGE = "The Conservative Crime Squad has gone on another rampage.  ";
const string CONST_THE_CONSERVATIVE_CRIME_SQUAD_HAS_STRUCK_AGAIN = "The Conservative Crime Squad has struck again.  ";
const string CONST_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT = "to a spokesperson from the police department.";
const string CONST_WENT_ON_A_RAMPAGE_YESTERDAY_ACCORDING = "went on a rampage yesterday, according ";
const string CONST_A_GROUP_OF_WORTHLESS_M16_TOTING_HICKS_CALLING_ITSELF_THE_CONSERVATIVE_CRIME_SQUAD = "A group of worthless M16-toting hicks calling itself the Conservative Crime Squad ";
const string CONST_BURST_ONTO_THE_SCENE_OF_POLITICAL_ACTIVISM_YESTERDAY_ACCORDING = "burst onto the scene of political activism yesterday, according ";
const string CONST_A_GROUP_OF_M16_WIELDING_VIGILANTES_CALLING_ITSELF_THE_CONSERVATIVE_CRIME_SQUAD = "A group of M16-wielding vigilantes calling itself the Conservative Crime Squad ";
const string CONST_A_LIBERAL_CRIME_SQUAD_OPERATION_WENT_HORRIBLY_WRONG = "A Liberal Crime Squad operation went horribly wrong.  ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_HAS_GONE_ON_A_RAMPAGE = "The Liberal Crime Squad has gone on a rampage.  ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_HAS_STRUCK_AGAIN = "The Liberal Crime Squad has struck again.  ";
const string CONST_THE_VERY_SYMBOL_OF_ECONOMIC_INEQUALITY = ", the very symbol of economic inequality.  ";
const string CONST_KNOWN_FOR_ITS_EXTREME_CONSERVATIVE_BIAS = ", known for its Extreme Conservative Bias.  ";
const string CONST_A_BUILDING_WITH_ENOUGH_SQUARE_FOOTAGE_ENOUGH_TO_HOUSE_A_HUNDRED_PEOPLE_IF_IT_WEREN_T_IN_CONSERVATIVE_HANDS = ", a building with enough square footage enough to house a hundred people if it weren't in Conservative Hands.  ";
const string CONST_WHERE_EVIL_AND_CONSERVATISM_COAGULATE_IN_THE_HALLWAYS = ", where evil and Conservatism coagulate in the hallways.  ";
const string CONST_ALSO_KNOWN_TO_BE_A_CONSERVATIVE_STORAGE_FACILITY_FOR_RADIOACTIVE_WASTE = ", also known to be a Conservative storage facility for radioactive waste.  ";
const string CONST_A_FACTORY_WHOSE_CONSERVATIVE_SMOKESTACKS_CHOKE_THE_CITY_WITH_DEADLY_POLLUTANTS = ", a factory whose Conservative smokestacks choke the city with deadly pollutants.  ";
const string CONST_A_CONSERVATIVE_SWEATSHOP_AND_HUMAN_RIGHTS_ABUSER = ", a Conservative sweatshop and human rights abuser.  ";
const string CONST_PRIDE_OF_CONSERVATIVE_TORTURERS_AND_WARMONGERS_EVERYWHERE = ", pride of Conservative torturers and warmongers everywhere.  ";
const string CONST_THE_CONSERVATIVE_HEADQUARTERS_OF_ONE_OF_THE_BIGGEST_PRIVACY_VIOLATORS_IN_THE_WORLD = ", the Conservative headquarters of one of the biggest privacy violators in the world.  ";
const string CONST_WHERE_INNOCENT_PEOPLE_ARE_REGULARLY_BEATEN_BY_CONSERVATIVE_GUARDS = ", where innocent people are regularly beaten by Conservative guards.  ";
const string CONST_SITE_OF_NUMEROUS_CONSERVATIVE_INJUSTICES = ", site of numerous Conservative Injustices.  ";
const string CONST_HEADQUARTERS_OF_ONE_OF_THE_MOST_OPPRESSIVE_AND_CONSERVATIVE_POLICE_FORCES_IN_THE_COUNTRY = ", headquarters of one of the most oppressive and Conservative police forces in the country.  ";
const string CONST_A_DANGEROUS_CONSERVATIVE_GENETIC_RESEARCH_LAB = ", a dangerous Conservative genetic research lab.  ";
const string CONST_A_CONSERVATIVE_ANIMAL_RIGHTS_ABUSER = ", a Conservative animal rights abuser.  ";
const string CONST_A_SPAWNING_GROUND_OF_WRONG_CONSERVATIVE_IDEAS = ", a spawning ground of Wrong Conservative Ideas.  ";
const string CONST_KNOWN_FOR_ITS_RICH_AND_SNOOTY_RESIDENTS = ", known for its rich and snooty residents.  ";
const string CONST_RICHARD_DAWKINS_FOOD_BANK = "Richard Dawkins Food Bank.  ";
const string CONST_ACLU_BRANCH_OFFICE = "ACLU Branch Office.  ";
const string CONST_GREENPEACE_OFFICES = "Greenpeace Offices.  ";
const string CONST_NETWORK_NEWS_STATION = "Network News Station.  ";
const string CONST_PUBLIC_RADIO_STATION = "Public Radio Station.  ";
const string CONST_TAX_COLLECTION_AGENCY = "Tax Collection Agency.  ";
const string CONST_WELFARE_ASSISTANCE_AGENCY = "Welfare Assistance Agency.  ";
const string CONST_WHIRLED_PEAS_MUSEUM = "Whirled Peas Museum.  ";
const string CONST_LABOR_UNION_HQ = "Labor Union HQ.  ";
const string CONST_WIKILEAKS_HQ = "WikiLeaks HQ.  ";
const string CONST_REHABILITATION_CENTER = "Rehabilitation Center.  ";
const string CONST_ABORTION_CLINIC = "Abortion Clinic.  ";
const string CONST_SEEDY_BACK_ALLEY_TM = "Seedy Back Alley(tm).  ";
const string CONST_RESEARCH_ETHICS_COMMISSION_HQ = "Research Ethics Commission HQ.  ";
const string CONST_ANIMAL_SHELTER = "Animal Shelter.  ";
const string CONST_LADY_LUCK_STRIP_CLUB = "Lady Luck Strip Club.  ";
const string CONST_UNIVERSITY_DORMITORY = "University Dormitory.  ";
const string CONST_NOTORIOUS = "notorious ";
const string CONST_AT_THE = "at the ";
const string CONST_THE_NOTORIOUS = "the notorious ";
const string CONST_AT_SPACE = "at ";
const string CONST_APOSTROPHE_S = "'s";
const string CONST_IN_THE = "in the ";
const string CONST_ON_THE = "on the ";
const string CONST_IN = "in ";
const string CONST_ON = "on ";
const string CONST_ORANGE_COUNTY = "Orange County";
const string CONST_TRAVEL_AGENCY = "Travel Agency";
const string CONST_SHOPPING_MALL = "Shopping Mall";
const string CONST_AND = "and";
const string CONST_THE_EVENTS_TOOK_PLACE = "  The events took place ";
const string CONST_W = " w/ ";
const string CONST_CALL_TODAY = "Call Today";
const string CONST_POLICE_WERE_SEEN_SEARCHING_THE_SURROUNDING_AREA_YESTERDAY = ".  Police were seen searching the surrounding area yesterday.";
const string CONST_S_LAST_KNOWN_LOCATION_WAS_THE = "'s last known location was the ";
const string CONST_ACCORDING_TO_SOURCES = "  According to sources, ";
const string QUOTATION_MARK = "\"";
const string CONST_YEARS_EXPERIENCE = " Years Experience";
const string CONST_TO_THE_CITIZENS_PLEASE_CONTACT_THE_DEPARTMENT_IF_YOU_HAVE_ANY_ADDITIONAL_INFORMATION = "To the citizens, please contact the department if you have any additional information.";
const string CONST_AS_THE_INVESTIGATION_IS_ONGOING_I_CANNOT_BE_MORE_SPECIFIC_AT_THIS_TIME = "As the investigation is ongoing, I cannot be more specific at this time.  ";
const string CONST_BACK_HOME_AND_BRING_THE_KIDNAPPERS_TO_JUSTICE = " back home and bring the kidnappers to justice.  ";
const string CONST_BRING = "bring ";
const string CONST_WE_HAVE_SEVERAL_LEADS_AND_ARE_CONFIDENT_THAT_WE_WILL = "We have several leads and are confident that we will ";
const string CONST_DAYS_AGO_BY_A_PERSON_OR_PERSONS_AS_YET_UNDETERMINED = " days ago, by a person or persons as yet undetermined.  ";
const string CONST_WAS_TAKEN = " was taken ";
const string CONST_WE_NOW_BELIEVE_THAT = "\"We now believe that ";
const string CONST_SPEAKING_ON_BEHALF_OF_THE_POLICE_DEPARTMENT_STATED = ", speaking on behalf of the police department, stated ";
const string CONST_LIBERAL_DEFENSE_LAWYER = "Liberal Defense Lawyer";
const string CONST_ACCORDING_TO_A_POLICE_SPOKESPERSON = "according to a police spokesperson.";
const string CONST_IS_NOW_CONSIDERED_A_KIDNAPPING = " is now considered a kidnapping, ";
const string CONST_THE_DISAPPEARANCE_OF = " - The disappearance of ";
const string CONST_KIDNAPPED = "KIDNAPPED";
const string CONST_SOMEONE = "SOMEONE";
const string CONST_COP = "COP";
const string CONST_JUDGE_CAPS = "JUDGE";
const string CONST_SCIENTIST = "SCIENTIST";
const string CONST_NEWS_ANCHOR = "NEWS ANCHOR";
const string CONST_RADIO_HOST = "RADIO HOST";
const string CONST_ONLY9 = "KIDNAPPING";
const string CONST_LCS_DENIES = "LCS DENIES";
const string CONST_THIS_IS_CLEARLY_THE_WORK_OF_CONSERVATIVE_BUTCHERS_ENFORCING_THE_PROHIBITION_ON_A_FREE_PRESS = "This is clearly the work of conservative butchers enforcing the prohibition on a free press";
const string CONST_WORKING_FOR_THIS_VERY_PAPER = "working for this very paper. ";
const string CONST_THE_MURDERED_WAS_A_REPORTER = "The murdered was a reporter ";
const string CONST_THE_MURDERED_WERE_REPORTERS = "The murdered were reporters ";
const string CONST_FORTUNATELY_FIREMEN_WERE_ABLE_TO_RESPOND_BEFORE_THE_FIRE_COULD_SPREAD_TO_OTHER_BUILDINGS = "Fortunately, firemen were able to respond before the fire could spread to other buildings";
const string CONST_WE_ARE_WORKING_CLOSELY_WITH_THE_FIRE_DEPARTMENT_TO_TRACK_DOWN_THE_ARSONIST = "we are working closely with the Fire Department to track down the arsonist.  ";
const string CONST_SCORCH_MARKS_THROUGHOUT_THE_SITE_INDICATE_THAT_THIS_WAS_NO_ACCIDENT = "Scorch marks throughout the site indicate that this was no accident; ";
const string CONST_ONLY = "Only $";
const string CONST_SEDAN_4D = "Sedan 4D";
const string CONST_X_LEXUS_GS_ = "Lexus GS 300";
const string CONST_VEHICLES_R = "Vehicles&r";
const string CONST_QUALITY_PRE_OWNED = "Quality Pre-Owned";
const string CONST_NOW = "Now $";
const string CONST_SPECIAL_PURCHASE = "Special Purchase";
const string CONST_FINE_LEATHER_CHAIRS = "Fine Leather Chairs";
const string CONST_CASENEWSSTORY_CCS_NOBACKERS_TXT = "caseNEWSSTORY_CCS_NOBACKERS.txt";
const string CONST_CASENEWSSTORY_CCS_DEFEATED_TXT = "caseNEWSSTORY_CCS_DEFEATED.txt";
const string CONST_ADLISTB_TXT = "adListB.txt";
const string CONST_ADLIST_TXT = "adList.txt";
const string CONST_PERSONALADSLG_TXT = "personalAdsLG.txt";
const string CONST_PERSONALADS_TXT = "personalAds.txt";
const string CONST_CCS_NOUN_TXT = "ccs_noun.txt";
const string CONST_CCS_ADJECTIVE_3_TXT = "ccs_adjective_3.txt";
const string CONST_CCS_ADJECTIVE_2_TXT = "ccs_adjective_2.txt";
const string CONST_CCS_ADJECTIVE_TXT = "ccs_adjective.txt";
const string CONST_CABLE_CITY_2_TXT = "cable_city_2.txt";
const string CONST_CABLE_CITY_TXT = "cable_city.txt";
const string CONST_CABLE_NAME_2_TXT = "cable_name_2.txt";
const string CONST_CABLE_NAME_TXT = "cable_name.txt";
const string CONST_REAGAN_GOOD_2_TXT = "reagan_good_2.txt";
const string CONST_REAGAN_GOOD_TXT = "reagan_good.txt";
const string CONST_CEO_BEHAVING_BADLY_TXT = "ceo_behaving_badly.txt";
const string CONST_REAGAN_BAD_2_TXT = "reagan_bad_2.txt";
const string CONST_REAGAN_BAD_TXT = "reagan_bad.txt";
const string CONST_PUBLIC_PLACE_TXT = "public_place.txt";
const string CONST_FM_RADIO_NAME_2_TXT = "fm_radio_name_2.txt";
const string CONST_FM_RADIO_NAME_TXT = "fm_radio_name.txt";
const string CONST_TECH_GIANT_NAME_2_TXT = "tech_giant_name_2.txt";
const string CONST_TECH_GIANT_NAME_TXT = "tech_giant_name.txt";
const string CONST_DISTRUST_LIBERALS_TXT = "distrust_liberals.txt";
const string CONST_I_LIKE_POLUTION_TXT = "i_like_polution.txt";
const string CONST_POLLUTION_CONSUMPTION_2_TXT = "pollution_consumption_2.txt";
const string CONST_POLLUTION_CONSUMPTION_TXT = "pollution_consumption.txt";
const string CONST_FAMILY_VALUES_COMPANY_NAME_3_TXT = "family_values_company_name_3.txt";
const string CONST_FAMILY_VALUES_COMPANY_NAME_2_TXT = "family_values_company_name_2.txt";
const string CONST_FAMILY_VALUES_COMPANY_NAME_TXT = "family_values_company_name.txt";
const string CONST_RADIO_HOST_LOST_MIND_TXT = "radio_host_lost_mind.txt";
const string CONST_RADIO_HOST_CRAZY_QUOTE_TXT = "radio_host_crazy_quote.txt";
const string CONST_JUDGE_WITH_PROSTITUTE_FULL_FREE_SPEECH_TXT = "judge_with_prostitute_full_free_speech.txt";
const string CONST_JUDGE_WITH_PROSTITUTE_NO_FREE_SPEECH_TXT = "judge_with_prostitute_no_free_speech.txt";
const string CONST_JUDGE_WITH_PROSTITUTE_TXT = "judge_with_prostitute.txt";
const string CONST_BROTHER_SISTER_TXT = "brother_sister.txt";
const string CONST_OLDER_YOUNGER_TXT = "older_younger.txt";
const string CONST_HIS_HER_TXT = "his_her.txt";
const string CONST_PETTY_VIOLENCE_TXT = "petty_violence.txt";
const string CONST_BULLSHIT_TXT = "bullshit.txt";
const string CONST_BULLSHIT_NO_FREE_SPEECH_TXT = "bullshit_no_free_speech.txt";
const string CONST_GENE_PRODUCT_COST_TXT = "gene_product_cost.txt";
const string CONST_GENE_PRODUCT_BENEFIT_TXT = "gene_product_benefit.txt";
const string CONST_GENE_PRODUCT_NAME_2_TXT = "gene_product_name_2.txt";
const string CONST_GENE_PRODUCT_NAME_TXT = "gene_product_name.txt";
const string CONST_GENE_CORP_NAME_2_TXT = "gene_corp_name_2.txt";
const string CONST_GENE_CORP_NAME_TXT = "gene_corp_name.txt";
const string CONST_TERRORIST_PLOT_NO_FREE_SPEECH_TXT = "terrorist_plot_no_free_speech.txt";
const string CONST_TERRORIST_PLOT_TXT = "terrorist_plot.txt";
const string CONST_TERRORIST_GROUP_TXT = "terrorist_group.txt";
const string CONST_CHIMP_DRUG_HORROR_TXT = "chimp_drug_horror.txt";
const string CONST_CHIMP_DRUG_IMPACT_TXT = "chimp_drug_impact.txt";
const string CONST_DRUG_NAME_2_TXT = "drug_name_2.txt";
const string CONST_DRUG_NAME_TXT = "drug_name.txt";
const string CONST_ANIMAL_RESEARCH_COUNTRY_TXT = "animal_research_country.txt";
const string CONST_BREAK_IN_MURDER_CASE_TXT = "break_in_murder_case.txt";
const string CONST_EVIDENCE_OF_CHILD_MURDER_TXT = "evidence_of_child_murder.txt";
const string CONST_MUTILATED_CORPSE_TXT = "mutilated_corpse.txt";
const string CONST_PRISON_BOOK_TITLE_2_TXT = "prison_book_title_2.txt";
const string CONST_PRISON_BOOK_TITLE_TXT = "prison_book_title.txt";
const string CONST_MY_IDOL_TXT = "my_idol.txt";
const string CONST_BRIBE_OFFICERS_TXT = "bribe_officers.txt";
const string CONST_CRAZY_CONSERVATIVE_ACT_TXT = "crazy_conservative_act.txt";
const string CONST_WHY_CHASE_ENDED_TXT = "why_chase_ended.txt";
const string CONST_VIGILANTE_MURDER_TXT = "vigilante_murder.txt";
const string CONST_RADIO_NAME_2_TXT = "radio_name_2.txt";
const string CONST_RADIO_NAME_TXT = "radio_name.txt";
const string CONST_CONSERVATIVE_OPPOSE_BOOK_TXT = "conservative_oppose_book.txt";
const string CONST_RANDOM_NATIONALITY_TXT = "random_nationality.txt";
const string CONST_BOOK_TITLE_2_TXT = "book_title_2.txt";
const string CONST_BOOK_TITLE_TXT = "book_title.txt";
const string CONST_AMORPM_TXT = "AMorPM.txt";
const string CONST_LIBERALCRIME_TXT = "liberalCrime.txt";

const string tag_CEO = "CEO";
const string tag_CONSERVATIVE = "CONSERVATIVE";
const string tag_D = "D";
const string tag_Downtown = "Downtown";
const string tag_National_Mall = "National Mall";
const string tag_Arlington = "Arlington";
const string tag_Manhattan = "Manhattan";
const string tag_Manhattan_Island = "Manhattan Island";
const string tag_Hollywood = "Hollywood";
const string tag_Greater_Hollywood = "Greater Hollywood";
const string tag_Long_Island = "Long Island";
const string tag_B = "B";
const string tag_Brooklyn_and_Queens = "Brooklyn and Queens";
const string tag_Outskirts_and_Orange_County = "Outskirts and Orange County";
const string tag_Outskirts = "Outskirts";
const string tag_Travel = "Travel";
const string tag_Shopping = "Shopping";
const string tag_The = "The ";

const string majorevent = "majorevent\\";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";

vector<string> CONST_Woman_744 = {
	CONST_UPPER_BORDER_WITH_CORNERS, CONST_A_FAILED_PARTIAL_BIRTH_ABORTION_GOES_ON_A, CONST_POPULAR_AFTERNOON_TALK_SHOW_THE_STUDIO, CONST_AUDIENCE_AND_VIEWERS_NATIONWIDE_FEEL_ITS_PAIN, CONST_LOWER_BORDER_WITH_CORNERS
};
vector<string> CONST_Cable_744 = {
	CONST_UPPER_BORDER_WITH_CORNERS, CONST_A_MAJOR_CABLE_NEWS_CHANNEL_HAS_HIRED_A_SLICK, CONST_NEW_ANCHOR_FOR_ONE_OF_ITS_NEWS_SHOWS_GUIDED, CONST_BY_IMPRESSIVE_ADVERTISING_AMERICA_TUNES_IN, CONST_LOWER_BORDER_WITH_CORNERS
};
vector<string> CONST_CEO_744 = {
	CONST_UPPER_BORDER_WITH_CORNERS, CONST_A_NEW_SHOW_GLAMORIZING_THE_LIVES_OF_THE_RICH, CONST_BEGINS_AIRING_THIS_WEEK_WITH_THE_NATIONWIDE, CONST_ADVERTISING_BLITZ_IT_S_BOUND_TO_BE_POPULAR, CONST_LOWER_BORDER_WITH_CORNERS
};
vector<string> CONST_Cable_744POS = {
	CONST_UPPER_BORDER_WITH_CORNERS, CONST_A_CABLE_NEWS_ANCHOR_ACCIDENTALLY_LET_A, CONST_BRIGHT_LIBERAL_GUEST_FINISH_A_SENTENCE_MANY, CONST_VIEWERS_ACROSS_THE_NATION_WERE_LISTENING, CONST_LOWER_BORDER_WITH_CORNERS
};
vector<string> CONST_Police_744 = {
	CONST_UPPER_BORDER_WITH_CORNERS, CONST_THE_POLICE_HAVE_BEATEN_A_BLACK_MAN_IN, CONST_LOS_ANGELES_AGAIN_THIS_TIME_THE_INCIDENT, CONST_TAPED_BY_A_PASSERBY_AND_SATURATES_THE_NEWS, CONST_LOWER_BORDER_WITH_CORNERS
};

map<int, string> newsStoryHeadlines = {
	map<int, string>::value_type(VIEW_TAXES,	CONST_CLASS_WAR),
	map<int, string>::value_type(VIEW_SWEATSHOPS,	CONST_CLASS_WAR),
	map<int, string>::value_type(VIEW_CEOSALARY,	CONST_CLASS_WAR),
	map<int, string>::value_type(VIEW_NUCLEARPOWER,	CONST_MELTDOWN_RISK),
	map<int, string>::value_type(VIEW_POLICEBEHAVIOR,	CONST_LCS_VS_COPS),
	map<int, string>::value_type(VIEW_DEATHPENALTY,	CONST_PRISON_WAR),
	map<int, string>::value_type(VIEW_INTELLIGENCE,	CONST_LCS_VS_CIA),
	map<int, string>::value_type(VIEW_ANIMALRESEARCH,	CONST_EVIL_RESEARCH),
	map<int, string>::value_type(VIEW_GENETICS,	CONST_EVIL_RESEARCH),
	map<int, string>::value_type(VIEW_FREESPEECH,	CONST_NO_JUSTICE),
	map<int, string>::value_type(VIEW_GAY,	CONST_NO_JUSTICE),
	map<int, string>::value_type(VIEW_JUSTICES,	CONST_NO_JUSTICE),
	map<int, string>::value_type(VIEW_POLLUTION,	CONST_POLLUTER_HIT),
	map<int, string>::value_type(VIEW_CORPORATECULTURE,	CONST_LCS_HITS_CORP),
	map<int, string>::value_type(VIEW_AMRADIO,	CONST_LCS_HITS_AM),
	map<int, string>::value_type(VIEW_CABLENEWS,	CONST_LCS_HITS_TV)
};
map<int, string> presidentStories = {
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_IMPEACHED,  CONST_IMPEACHED),
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_BELIEVED_DEAD,  CONST_BELIEVED_DEAD),
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_FOUND_DEAD, CONST_FOUND_DEAD),
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_FOUND,  CONST_RESCUED),
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_KIDNAPPED,  CONST_KIDNAPPED),
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_MISSING,  CONST_MISSING),
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_ASSASSINATED,  CONST_ASSASSINATED)
};
map<char, vector<Views> > siteViews = {
	map<SiteTypes, vector<Views> >::value_type(SITE_LABORATORY_COSMETICS,
		{
			VIEW_ANIMALRESEARCH,
			VIEW_WOMEN,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_LABORATORY_GENETIC,
		{
			VIEW_ANIMALRESEARCH,
			VIEW_GENETICS,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_GOVERNMENT_POLICESTATION,
		{
			VIEW_POLICEBEHAVIOR,
			VIEW_PRISONS,
			VIEW_DRUGS,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_GOVERNMENT_COURTHOUSE,
		{
			VIEW_DEATHPENALTY,
			VIEW_JUSTICES,
			VIEW_FREESPEECH,
			VIEW_GAY,
			VIEW_WOMEN,
			VIEW_CIVILRIGHTS,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_GOVERNMENT_PRISON,
		{
			VIEW_DEATHPENALTY,
			VIEW_DRUGS,
			VIEW_TORTURE,
			VIEW_PRISONS,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_GOVERNMENT_ARMYBASE,
		{
			VIEW_TORTURE,
			VIEW_MILITARY,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_GOVERNMENT_WHITE_HOUSE,
		{
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_GOVERNMENT_INTELLIGENCEHQ,
		{
			VIEW_INTELLIGENCE,
			VIEW_TORTURE,
			VIEW_PRISONS,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_INDUSTRY_SWEATSHOP,
		{
			VIEW_SWEATSHOPS,
			VIEW_IMMIGRATION,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_INDUSTRY_POLLUTER,
		{
			VIEW_SWEATSHOPS,
			VIEW_POLLUTION,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_INDUSTRY_NUCLEAR,
		{
			VIEW_NUCLEARPOWER,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_CORPORATE_HEADQUARTERS,
		{
			VIEW_TAXES,
			VIEW_CORPORATECULTURE,
			VIEW_WOMEN,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_CORPORATE_HOUSE,
		{
			VIEW_TAXES,
			VIEW_CEOSALARY,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_MEDIA_AMRADIO,
		{
			VIEW_AMRADIO,
			VIEW_FREESPEECH,
			VIEW_GAY,
			VIEW_WOMEN,
			VIEW_CIVILRIGHTS,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_MEDIA_CABLENEWS,
		{
			VIEW_CABLENEWS,
			VIEW_FREESPEECH,
			VIEW_GAY,
			VIEW_WOMEN,
			VIEW_CIVILRIGHTS,
		}
		),
			map<SiteTypes, vector<Views> >::value_type(SITE_RESIDENTIAL_APARTMENT_UPSCALE,
				{
					VIEW_TAXES,
					VIEW_CEOSALARY,
					VIEW_GUNCONTROL,
				}
				),
			map<SiteTypes, vector<Views> >::value_type(SITE_BUSINESS_CIGARBAR,
				{
					VIEW_TAXES,
					VIEW_CEOSALARY,
					VIEW_WOMEN,
				}
				),
			map<SiteTypes, vector<Views> >::value_type(SITE_BUSINESS_BANK,
				{
					VIEW_TAXES,
					VIEW_CEOSALARY,
					VIEW_CORPORATECULTURE,
				}
				),
};
int okay_types[] = { NEWSSTORY_SQUAD_SITE, NEWSSTORY_SQUAD_ESCAPED, NEWSSTORY_SQUAD_FLEDATTACK,
	NEWSSTORY_SQUAD_DEFENDED, NEWSSTORY_SQUAD_BROKESIEGE, NEWSSTORY_SQUAD_KILLED_SIEGEATTACK,
	NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE, NEWSSTORY_SQUAD_KILLED_SITE, NEWSSTORY_WANTEDARREST,
	NEWSSTORY_GRAFFITIARREST, NEWSSTORY_CCS_SITE, NEWSSTORY_CCS_KILLED_SITE };
map<short, string> positiveMajorEvents = {
	map<short, string>::value_type(VIEW_WOMEN,
	CONST_CLINIC_MURDER),

	map<short, string>::value_type(VIEW_GAY,
	CONST_CRIME_OF_HATE),

	map<short, string>::value_type(VIEW_DEATHPENALTY,
	CONST_JUSTICE_DEAD),

	map<short, string>::value_type(VIEW_GUNCONTROL,
	CONST_MASS_SHOOTING_ALLCAPS),

	map<short, string>::value_type(VIEW_PRISONS,
	CONST_ON_THE_INSIDE),

	map<short, string>::value_type(VIEW_INTELLIGENCE,
	CONST_THE_FBI_FILES),

	map<short, string>::value_type(VIEW_FREESPEECH,
	CONST_BOOK_BANNED),

	map<short, string>::value_type(VIEW_JUSTICES,
	CONST_IN_CONTEMPT),

	map<short, string>::value_type(VIEW_AMRADIO,
	CONST_AM_IMPLOSION),
};
struct TwoStringsAndAnInt {
	const string first;
	const string second;
	const int third;
	TwoStringsAndAnInt(string _first, string _second, int _third) : first(_first), second(_second), third(_third) {}
	TwoStringsAndAnInt() : first(""), second(""), third(-1) {}
};
map<short, TwoStringsAndAnInt> positiveMajorPictures = {
	map<short, TwoStringsAndAnInt>::value_type(VIEW_NUCLEARPOWER,
	TwoStringsAndAnInt(CONST_MELTDOWN, CONST_A_NUCLEAR_POWER_PLANT_SUFFERS_A_CATASTROPHIC_MELTDOWN, PICTURE_MELTDOWN)),

	map<short, TwoStringsAndAnInt>::value_type(VIEW_ANIMALRESEARCH,
	TwoStringsAndAnInt(CONST_HELL_ON_EARTH, CONST_A_MUTANT_ANIMAL_HAS_ESCAPED_FROM_A_LAB_AND_KILLED_THIRTY_PEOPLE, PICTURE_MUTANT_BEAST)),

	map<short, TwoStringsAndAnInt>::value_type(VIEW_GENETICS,
	TwoStringsAndAnInt(CONST_KILLER_FOOD, CONST_OVER_A_HUNDRED_PEOPLE_BECOME_SICK_FROM_GENETICALLY_MODIFIED_FOOD, PICTURE_GENETICS)),

	map<short, TwoStringsAndAnInt>::value_type(VIEW_SWEATSHOPS,
	TwoStringsAndAnInt(CONST_CHILD_S_PLEA, CONST_A_T_SHIRT_IN_A_STORE_IS_FOUND_SCRAWLED_WITH_A_MESSAGE_FROM_A_SWEATSHOP_WORKER, PICTURE_TSHIRT)),

	map<short, TwoStringsAndAnInt>::value_type(VIEW_POLLUTION,
	TwoStringsAndAnInt(CONST_RING_OF_FIRE, CONST_THE_OHIO_RIVER_CAUGHT_ON_FIRE_AGAIN, PICTURE_RIVERFIRE)),

	map<short, TwoStringsAndAnInt>::value_type(VIEW_CORPORATECULTURE,
	TwoStringsAndAnInt(CONST_BELLY_UP, CONST_AN_ENORMOUS_COMPANY_FILES_FOR_BANKRUPTCY_SHATTERING_THE_PREVIOUS_RECORD, PICTURE_DOLLARS)),



};
map<short, string> negativeMajorEvents = {

	map<short, string>::value_type(VIEW_DEATHPENALTY,
		CONST_LET_S_FRY_EM),

	map<short, string>::value_type(VIEW_ANIMALRESEARCH,
		CONST_APE_EXPLORERS),

	map<short, string>::value_type(VIEW_PRISONS,
		CONST_HOSTAGE_SLAIN),

	map<short, string>::value_type(VIEW_INTELLIGENCE,
		CONST_DODGED_BULLET),

	map<short, string>::value_type(VIEW_GENETICS,
		CONST_GM_FOOD_FAIRE),

	map<short, string>::value_type(VIEW_JUSTICES,
		CONST_JUSTICE_AMOK),

	map<short, string>::value_type(VIEW_POLLUTION,
		CONST_LOOKING_UP),

	map<short, string>::value_type(VIEW_CORPORATECULTURE,
		CONST_NEW_JOBS),
};
map<short, TwoStringsAndAnInt> negativeMajorPictures = {

	map<short, TwoStringsAndAnInt>::value_type(VIEW_GAY,
		TwoStringsAndAnInt(CONST_KINKY_WINKY, CONST_JERRY_FALWELL_EXPLAINS_THE_TRUTH_ABOUT_TINKY_WINKY_AGAIN, PICTURE_TINKYWINKY)
	),
	map<short, TwoStringsAndAnInt>::value_type(VIEW_NUCLEARPOWER,
		TwoStringsAndAnInt(CONST_OIL_CRUNCH, CONST_OPEC_CUTS_OIL_PRODUCTION_SHARPLY_IN_RESPONSE_TO_A_US_FOREIGN_POLICY_DECISION, PICTURE_OIL)
	),
	map<short, TwoStringsAndAnInt>::value_type(VIEW_FREESPEECH,
		TwoStringsAndAnInt(CONST_HATE_RALLY, CONST_FREE_SPEECH_ADVOCATES_FIGHT_HARD_TO_LET_A_WHITE_SUPREMACIST_RALLY_TAKE_PLACE, PICTURE_KKK)
	),



};

map<int, vector<string> >accordingToLiberalGuardian = {

	map<Crimes, vector<string> >::value_type(CRIME_POLICE_LOCKUP,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_RESCUE_INNOCENT_PEOPLE_FROM_THE_POLICE_LOCKUP + CONST_SAVING_THEM_FROM_TORTURE_AND_BRUTALITY_AT_THE_HANDS_OF_CONSERVATIVE_POLICE_INTERROGATORS , ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_FREED_OR_ATTEMPTED_TO_FREE_PRISONERS_FROM_THE_POLICE_LOCKUP }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_BANKVAULTROBBERY,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_OPENED_THE_BANK_VAULT + CONST_SHOWING_THE_TRIUMPH_OF_LIBERAL_IDEALS_OVER_CONSERVATIVE_ECONOMICS , ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_OPENED_THE_BANK_VAULT_WHICH_HELD_MORE_THAN_100_000_AT_THE_TIME }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_BANKSTICKUP,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_DEMANDED_ACCESS_TO_THE_BANK_VAULT + CONST_HOPING_TO_ACQUIRE_THE_RESOURCES_TO_OVERCOME_EVIL , ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_THREATENED_INNOCENT_BYSTANDERS_IN_ORDER_TO_ROB_THE_BANK_VAULT }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_COURTHOUSE_LOCKUP,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_RESCUE_INNOCENT_PEOPLE_FROM_THE_COURTHOUSE_LOCKUP + CONST_SAVING_THEM_FROM_THE_HIGHLY_CORRUPT_CONSERVATIVE_JUSTICE_SYSTEM , ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_FREED_OR_ATTEMPTED_TO_FREE_PRISONERS_FROM_THE_COURTHOUSE_LOCKUP }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_PRISON_RELEASE,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_RESCUE_INNOCENT_PEOPLE_FROM_THE_ABUSIVE_CONSERVATIVE_CONDITIONS + CONST_AT_THE_PRISON , ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_FREED_PRISONERS_WHILE_IN_THE_FACILITY }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_JURYTAMPERING,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_HAS_APOLOGIZED_OVER_REPORTS_THAT_THE_OPERATION + CONST_MAY_HAVE_INTERFERED_WITH_JURY_DELIBERATIONS , ACCORDING_TO_POLICE + CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_VIOLATED_THE_SACRED + CONST_TRUST_AND_ATTEMPTED_TO_INFLUENCE_A_JURY }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_HACK_INTEL,
		{ CONST_LIBERAL_CRIME_SQUAD_COMPUTER_SPECIALISTS_WORKED_TO_LIBERATE_INFORMATION_FROM_CIA_COMPUTERS , ACCORDING_TO_POLICE + CONST_INTELLIGENCE_OFFICIALS_SEEMED_VERY_NERVOUS_ABOUT_SOMETHING }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_ARMORY,
		{ CONST_LIBERAL_CRIME_SQUAD_INFILTRATION_SPECIALISTS_WORKED_TO_LIBERATE_WEAPONS_FROM_THE_OPPRESSORS , CONST_ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_BREAK_INTO_THE_ARMORY }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_HOUSE_PHOTOS,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_WAS_ATTEMPTING_TO_UNCOVER_THE_CEO_S_CONSERVATIVE_CORRUPTION , ACCORDING_TO_POLICE + CONST_THE_OWNER_OF_THE_HOUSE_SEEMED_VERY_FRANTIC_ABOUT_SOME_MISSING_PROPERTY }
	),
	map<Crimes, vector<string> >::value_type(CRIME_CORP_FILES,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_WAS_ATTEMPTING_TO_UNCOVER_THE_COMPANY_S_CONSERVATIVE_CORRUPTION , ACCORDING_TO_POLICE + CONST_EXECUTIVES_ON_THE_SCENE_SEEMED_VERY_NERVOUS_ABOUT_SOMETHING }
	),
};
const vector<Crimes> noteworthyCrimes = {
	CRIME_COURTHOUSE_LOCKUP,
	CRIME_PRISON_RELEASE,
	CRIME_JURYTAMPERING,
	CRIME_HACK_INTEL,
	CRIME_ARMORY,
	CRIME_HOUSE_PHOTOS,
	CRIME_CORP_FILES
};
map<int, vector<string> >siegeMassacreStory = {

	map<SiegeTypes,  vector<string> >::value_type(SIEGE_POLICE,

		{
			(CONST_BURNED_STABBED_WITH_MAYBE_PITCHFORKS_THERE_MAY_HAVE)+(CONST_BEEN_BITE_MARKS_NOTHING_RECOGNIZABLE_LEFT_COMPLETE_CARNAGE),
			(CONST_WE_HAVE_REASON_TO_BELIEVE_THAT_THIS_BRUTAL_MASSACRE_WAS)+(CONST_INSPIRED_BY_THE_CONSERVATIVE_MEDIA_S_BRAINWASHING_PROPAGANDA)
		}
	),
	map<SiegeTypes,  vector<string> >::value_type(SIEGE_HICKS,

		{
			(CONST_BURNED_STABBED_WITH_MAYBE_PITCHFORKS_THERE_MAY_HAVE)+
			(CONST_BEEN_BITE_MARKS_NOTHING_RECOGNIZABLE_LEFT_COMPLETE_CARNAGE)

		,

		(CONST_WE_HAVE_REASON_TO_BELIEVE_THAT_THIS_BRUTAL_MASSACRE_WAS)+
		(CONST_INSPIRED_BY_THE_CONSERVATIVE_MEDIA_S_BRAINWASHING_PROPAGANDA)
		}),

	map<SiegeTypes,  vector<string> >::value_type(SIEGE_CORPORATE,

		{
			(CONST_IT_WAS_EXECUTION_STYLE_PROFESSIONAL_WE_VE_GOT_NOTHING)

			,

		(CONST_THIS_MASSACRE_HAS_THE_SIGNATURE_MARK_OF_A_GROUP_OF_MERCENARIES)+
		(CONST_KNOWN_TO_WORK_WITH_SEVERAL_CORPORATIONS_WE_VE_HAD_CONFRONTATIONS)+
		(CONST_WITH_IN_THE_PAST_WHEN_THE_POLICE_CAN_T_FIGURE_THIS_ONE_OUT_THEY_RE)+
		(CONST_JUST_COVERING_IT_UP)
		}),

	map<SiegeTypes,  vector<string> >::value_type(SIEGE_CCS,

		{
			(CONST_LOOK_IT_WAS_A_CONSERVATIVE_CRIME_SQUAD_HIT_THAT_S_ALL_WE_KNOW)+
			(CONST_NO_NAMES_NO_FACES_NOT_EVEN_WHERE_IT_HAPPENED_REALLY)

		,

		(CONST_THIS_IS_THE_DOING_OF_THE_CONSERVATIVE_CRIME_SQUAD_BUTCHERS)+
		(CONST_THEY_HAVE_TO_BE_STOPPED_BEFORE_THEY_KILL_AGAIN)
		}),

	map<SiegeTypes,  vector<string> >::value_type(SIEGE_FIREMEN,
		{
			(CONST_BURNED_UNRECOGNIZABLE)+
			(CONST_SCORCH_MARKS_THROUGHOUT_THE_SITE_INDICATE_THAT_THIS_WAS_NO_ACCIDENT)+
		(CONST_WE_ARE_WORKING_CLOSELY_WITH_THE_FIRE_DEPARTMENT_TO_TRACK_DOWN_THE_ARSONIST)+
		(CONST_FORTUNATELY_FIREMEN_WERE_ABLE_TO_RESPOND_BEFORE_THE_FIRE_COULD_SPREAD_TO_OTHER_BUILDINGS)

		,

		(CONST_WORKING_FOR_THIS_VERY_PAPER)+
		(CONST_THIS_IS_CLEARLY_THE_WORK_OF_CONSERVATIVE_BUTCHERS_ENFORCING_THE_PROHIBITION_ON_A_FREE_PRESS)
		}),


};
vector<file_and_text_collection> majorevent_text_file_collection = {
	/*majorevent.cpp*/
	customText(&liberalCrime, majorevent + CONST_LIBERALCRIME_TXT),
	customText(&AMorPM, majorevent + CONST_AMORPM_TXT),
	customText(&book_title, majorevent + CONST_BOOK_TITLE_TXT),
	customText(&book_title_2, majorevent + CONST_BOOK_TITLE_2_TXT),
	customText(&random_nationality, majorevent + CONST_RANDOM_NATIONALITY_TXT),
	customText(&conservative_oppose_book, majorevent + CONST_CONSERVATIVE_OPPOSE_BOOK_TXT),
	customText(&radio_name, majorevent + CONST_RADIO_NAME_TXT),
	customText(&radio_name_2, majorevent + CONST_RADIO_NAME_2_TXT),
	customText(&vigilante_murder, majorevent + CONST_VIGILANTE_MURDER_TXT),
	customText(&why_chase_ended, majorevent + CONST_WHY_CHASE_ENDED_TXT),
	customText(&crazy_conservative_act, majorevent + CONST_CRAZY_CONSERVATIVE_ACT_TXT),
	customText(&bribe_officers, majorevent + CONST_BRIBE_OFFICERS_TXT),
	customText(&my_idol, majorevent + CONST_MY_IDOL_TXT),
	customText(&prison_book_title, majorevent + CONST_PRISON_BOOK_TITLE_TXT),
	customText(&prison_book_title_2, majorevent + CONST_PRISON_BOOK_TITLE_2_TXT),
	customText(&mutilated_corpse, majorevent + CONST_MUTILATED_CORPSE_TXT),
	customText(&evidence_of_child_murder, majorevent + CONST_EVIDENCE_OF_CHILD_MURDER_TXT),
	customText(&break_in_murder_case, majorevent + CONST_BREAK_IN_MURDER_CASE_TXT),
	customText(&animal_research_country, majorevent + CONST_ANIMAL_RESEARCH_COUNTRY_TXT),
	customText(&drug_name, majorevent + CONST_DRUG_NAME_TXT),
	customText(&drug_name_2, majorevent + CONST_DRUG_NAME_2_TXT),
	customText(&chimp_drug_impact, majorevent + CONST_CHIMP_DRUG_IMPACT_TXT),
	customText(&chimp_drug_horror, majorevent + CONST_CHIMP_DRUG_HORROR_TXT),
	customText(&terrorist_group, majorevent + CONST_TERRORIST_GROUP_TXT),
	customText(&terrorist_plot, majorevent + CONST_TERRORIST_PLOT_TXT),
	customText(&terrorist_plot_no_free_speech, majorevent + CONST_TERRORIST_PLOT_NO_FREE_SPEECH_TXT),
	customText(&gene_corp_name, majorevent + CONST_GENE_CORP_NAME_TXT),
	customText(&gene_corp_name_2, majorevent + CONST_GENE_CORP_NAME_2_TXT),
	customText(&gene_product_name, majorevent + CONST_GENE_PRODUCT_NAME_TXT),
	customText(&gene_product_name_2, majorevent + CONST_GENE_PRODUCT_NAME_2_TXT),
	customText(&gene_product_benefit, majorevent + CONST_GENE_PRODUCT_BENEFIT_TXT),
	customText(&gene_product_cost, majorevent + CONST_GENE_PRODUCT_COST_TXT),
	customText(&bullshit_no_free_speech, majorevent + CONST_BULLSHIT_NO_FREE_SPEECH_TXT),
	customText(&bullshit, majorevent + CONST_BULLSHIT_TXT),
	customText(&petty_violence, majorevent + CONST_PETTY_VIOLENCE_TXT),
	customText(&his_her, majorevent + CONST_HIS_HER_TXT),
	customText(&older_younger, majorevent + CONST_OLDER_YOUNGER_TXT),
	customText(&brother_sister, majorevent + CONST_BROTHER_SISTER_TXT),
	customText(&judge_with_prostitute, majorevent + CONST_JUDGE_WITH_PROSTITUTE_TXT),
	customText(&judge_with_prostitute_no_free_speech, majorevent + CONST_JUDGE_WITH_PROSTITUTE_NO_FREE_SPEECH_TXT),
	customText(&judge_with_prostitute_full_free_speech, majorevent + CONST_JUDGE_WITH_PROSTITUTE_FULL_FREE_SPEECH_TXT),
	customText(&radio_host_crazy_quote, majorevent + CONST_RADIO_HOST_CRAZY_QUOTE_TXT),
	customText(&radio_host_lost_mind, majorevent + CONST_RADIO_HOST_LOST_MIND_TXT),
	customText(&family_values_company_name, majorevent + CONST_FAMILY_VALUES_COMPANY_NAME_TXT),
	customText(&family_values_company_name_2, majorevent + CONST_FAMILY_VALUES_COMPANY_NAME_2_TXT),
	customText(&family_values_company_name_3, majorevent + CONST_FAMILY_VALUES_COMPANY_NAME_3_TXT),
	customText(&pollution_consumption, majorevent + CONST_POLLUTION_CONSUMPTION_TXT),
	customText(&pollution_consumption_2, majorevent + CONST_POLLUTION_CONSUMPTION_2_TXT),
	customText(&i_like_polution, majorevent + CONST_I_LIKE_POLUTION_TXT),
	customText(&distrust_liberals, majorevent + CONST_DISTRUST_LIBERALS_TXT),
	customText(&tech_giant_name, majorevent + CONST_TECH_GIANT_NAME_TXT),
	customText(&tech_giant_name_2, majorevent + CONST_TECH_GIANT_NAME_2_TXT),
	customText(&fm_radio_name, majorevent + CONST_FM_RADIO_NAME_TXT),
	customText(&fm_radio_name_2, majorevent + CONST_FM_RADIO_NAME_2_TXT),
	customText(&public_place, majorevent + CONST_PUBLIC_PLACE_TXT),
	customText(&reagan_bad, majorevent + CONST_REAGAN_BAD_TXT),
	customText(&reagan_bad_2, majorevent + CONST_REAGAN_BAD_2_TXT),
	customText(&ceo_behaving_badly, majorevent + CONST_CEO_BEHAVING_BADLY_TXT),
	customText(&reagan_good, majorevent + CONST_REAGAN_GOOD_TXT),
	customText(&reagan_good_2, majorevent + CONST_REAGAN_GOOD_2_TXT),
	customText(&cable_name, majorevent + CONST_CABLE_NAME_TXT),
	customText(&cable_name_2, majorevent + CONST_CABLE_NAME_2_TXT),
	customText(&cable_city, majorevent + CONST_CABLE_CITY_TXT),
	customText(&cable_city_2, majorevent + CONST_CABLE_CITY_2_TXT),
	/*squadstory_text.cpp*/
	customText(&ccs_adjective, majorevent + CONST_CCS_ADJECTIVE_TXT),
	customText(&ccs_adjective_2, majorevent + CONST_CCS_ADJECTIVE_2_TXT),
	customText(&ccs_adjective_3, majorevent + CONST_CCS_ADJECTIVE_3_TXT),
	customText(&ccs_noun, majorevent + CONST_CCS_NOUN_TXT),
	customText(&personalAds, MOSTLY_ENDINGS_FOLDER + CONST_PERSONALADS_TXT),
	customText(&personalAdsLG, MOSTLY_ENDINGS_FOLDER + CONST_PERSONALADSLG_TXT),
	customText(&adList, MOSTLY_ENDINGS_FOLDER + CONST_ADLIST_TXT, AD_LENGTH),
	customText(&adListB, MOSTLY_ENDINGS_FOLDER + CONST_ADLISTB_TXT, AD_LENGTH),
	customText(&caseNEWSSTORY_CCS_DEFEATED, MOSTLY_ENDINGS_FOLDER + CONST_CASENEWSSTORY_CCS_DEFEATED_TXT),
	customText(&caseNEWSSTORY_CCS_NOBACKERS, MOSTLY_ENDINGS_FOLDER + CONST_CASENEWSSTORY_CCS_NOBACKERS_TXT),
};
#endif	//NEWS_CPP
#ifdef	POLITICS_CPP
// politics.cpp

#include "../creature/creatureEnums.h"
/* fills a string with a proper name */
void generate_name(char *str, char gender = GENDER_NEUTRAL);
string lastname(bool x = false);
//#include "../common/commonactions.h"
int randomissue(bool core_only = 0);
#include "../common/commondisplay.h"
// for  void makedelimiter(int y=8,int x=0);
//#include "../monthly/EndGameStatus.h"
/* EndGameStatus - attempts to pass a constitutional amendment to help win the game */
void tossjustices(char canseethings);
/* EndGameStatus - attempts to pass a constitutional amendment to help win the game */
void amendment_termlimits(char canseethings);
#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include <common\\getnames.h>
#include "../common/musicClass.h"
#include "../customMaps.h"
map<int, bool> stalinView = {
	map<int, bool>::value_type(VIEW_STALIN,  false), // Liberals and Stalinists don't get along
	map<int, bool>::value_type(VIEW_MOOD,  false), // Liberals and Stalinists don't get along
	map<int, bool>::value_type(VIEW_GAY,  false), // Stalinists discriminate against gay people
	map<int, bool>::value_type(VIEW_DEATHPENALTY,  false), // Stalinists execute lots of people
	map<int, bool>::value_type(VIEW_TAXES,  true), // Stalinists support communist income redistribution
	map<int, bool>::value_type(VIEW_NUCLEARPOWER,  false), // Stalinists believe the more nuclear, the better
	map<int, bool>::value_type(VIEW_ANIMALRESEARCH,  false), // Stalinists are in favor of unethical research
	map<int, bool>::value_type(VIEW_POLICEBEHAVIOR,  false), // Stalinists use police for brutal repression
	map<int, bool>::value_type(VIEW_TORTURE,  false), // Stalinists torture their enemies
	map<int, bool>::value_type(VIEW_INTELLIGENCE,  false), // Stalinists don't believe in privacy
	map<int, bool>::value_type(VIEW_FREESPEECH,  false), // Stalinists don't allow any dissent
	map<int, bool>::value_type(VIEW_GENETICS,  false), // Stalinists are in favor of unethical research
	map<int, bool>::value_type(VIEW_JUSTICES,  false), // Liberals and Stalinists don't get along
	map<int, bool>::value_type(VIEW_GUNCONTROL,  true), // Stalinists don't want any armed resistance
	map<int, bool>::value_type(VIEW_SWEATSHOPS,  true), // Stalinists say, Workers of the world unite!
	map<int, bool>::value_type(VIEW_POLLUTION,  false), // Stalinists don't care about pollution
	map<int, bool>::value_type(VIEW_CORPORATECULTURE,  true), // Stalinists hate rich people and corporations
	map<int, bool>::value_type(VIEW_CEOSALARY,  true), // Stalinists hate rich people and corporations
	map<int, bool>::value_type(VIEW_WOMEN,  false), // Stalinists discriminate against women
	map<int, bool>::value_type(VIEW_CIVILRIGHTS,  false), // Stalinists discriminate against ethnic groups
	map<int, bool>::value_type(VIEW_DRUGS,  false), // Stalinists only allow vodka
	map<int, bool>::value_type(VIEW_IMMIGRATION,  false), // Stalinists maintained tight border security at the Iron Curtain
	map<int, bool>::value_type(VIEW_MILITARY,  false), // Stalinists use the military for brutal repression
	map<int, bool>::value_type(VIEW_PRISONS,  false), // Stalinists annex Canada to fill it with gulags
	map<int, bool>::value_type(VIEW_AMRADIO,  true), // Stalinists agree that Conservatives are bad
	map<int, bool>::value_type(VIEW_CABLENEWS,  true), // Stalinists agree that Conservatives are bad
													   //map<int, bool>::value_type( VIEW_POLITICALVIOLENCE,  true), // the LCS and Stalinists both like using political violence
													   map<int, bool>::value_type(VIEW_LIBERALCRIMESQUAD,  false), // Liberals and Stalinists don't get along
													   map<int, bool>::value_type(VIEW_LIBERALCRIMESQUADPOS,  false), // Liberals and Stalinists don't get along
													   map<int, bool>::value_type(VIEW_CONSERVATIVECRIMESQUAD,  true), // Stalinists agree that Conservatives are bad
													   map<int, bool>::value_type(VIEWNUM,  false), // Liberals and Stalinists don't get along
};
map<int, bool> stalinLaw = {
	map<int, bool>::value_type(LAW_STALIN,  false), // Liberals and Stalinists don't get along
	map<int, bool>::value_type(LAW_MOOD,  false), // Liberals and Stalinists don't get along
	map<int, bool>::value_type(LAW_ABORTION,  true), // Stalinists agree that abortion is good, although technically they don't let women choose
	map<int, bool>::value_type(LAW_ANIMALRESEARCH,  false), // Stalinists are in favor of unethical research
	map<int, bool>::value_type(LAW_POLICEBEHAVIOR,  false), // Stalinists use police for brutal repression
	map<int, bool>::value_type(LAW_PRIVACY,  false), // Stalinists don't believe in privacy
	map<int, bool>::value_type(LAW_DEATHPENALTY,  false), // Stalinists execute lots of people
	map<int, bool>::value_type(LAW_NUCLEARPOWER,  false), // Stalinists believe the more nuclear, the better
	map<int, bool>::value_type(LAW_POLLUTION,  false), // Stalinists don't care about pollution
	map<int, bool>::value_type(LAW_LABOR,  true), // Stalinists say, Workers of the world unite!
	map<int, bool>::value_type(LAW_GAY,  false), // Stalinists discriminate against gay people
	map<int, bool>::value_type(LAW_CORPORATE,  true), // Stalinists hate rich people and corporations
	map<int, bool>::value_type(LAW_FREESPEECH,  false), // Stalinists don't allow any dissent
	map<int, bool>::value_type(LAW_FLAGBURNING,  true), // Stalinists regularly burn flags
	map<int, bool>::value_type(LAW_GUNCONTROL,  true), // Stalinists don't want any armed resistance
	map<int, bool>::value_type(LAW_TAX,  true), // Stalinists support communist income redistribution
	map<int, bool>::value_type(LAW_WOMEN,  false), // Stalinists discriminate against women
	map<int, bool>::value_type(LAW_CIVILRIGHTS,  false), // Stalinists discriminate against ethnic groups
	map<int, bool>::value_type(LAW_DRUGS,  false), // Stalinists only allow vodka
	map<int, bool>::value_type(LAW_IMMIGRATION,  false), // Stalinists maintained tight border security at the Iron Curtain
	map<int, bool>::value_type(LAW_ELECTIONS,  false), // Stalinists don't even have elections
	map<int, bool>::value_type(LAW_MILITARY,  false), // Stalinists use the military for brutal repression
	map<int, bool>::value_type(LAW_PRISONS,  false), // Stalinists annex Canada to fill it with gulags
	map<int, bool>::value_type(LAW_TORTURE,  false), // Stalinists torture their enemies
	map<int, bool>::value_type(LAWNUM,  false), // Liberals and Stalinists don't get along
};
map<int, int> lawReturnAttitude = {
	map<int, int>::value_type(LAW_ABORTION, VIEW_WOMEN), //XXX, There is no ``VIEW_ABORTION''!
	map<int, int>::value_type(LAW_ANIMALRESEARCH, VIEW_ANIMALRESEARCH),
	map<int, int>::value_type(LAW_POLICEBEHAVIOR, VIEW_POLICEBEHAVIOR),
	map<int, int>::value_type(LAW_PRIVACY, VIEW_INTELLIGENCE),
	map<int, int>::value_type(LAW_DEATHPENALTY, VIEW_DEATHPENALTY),
	map<int, int>::value_type(LAW_NUCLEARPOWER, VIEW_NUCLEARPOWER),
	map<int, int>::value_type(LAW_POLLUTION, VIEW_POLLUTION),
	map<int, int>::value_type(LAW_LABOR, VIEW_SWEATSHOPS),
	map<int, int>::value_type(LAW_GAY, VIEW_GAY),
	map<int, int>::value_type(LAW_FREESPEECH, VIEW_FREESPEECH),
	map<int, int>::value_type(LAW_TAX, VIEW_TAXES),
	map<int, int>::value_type(LAW_FLAGBURNING, VIEW_FREESPEECH),  // <-- I'm keeping this pure free speech instead of free speech
	map<int, int>::value_type(LAW_WOMEN, VIEW_WOMEN),             // plus political violence. Ideologically, there's no association
	map<int, int>::value_type(LAW_CIVILRIGHTS, VIEW_CIVILRIGHTS), // between flag burning and violence. - Jonathan S. Fox
	map<int, int>::value_type(LAW_DRUGS, VIEW_DRUGS),
	map<int, int>::value_type(LAW_IMMIGRATION, VIEW_IMMIGRATION), //XXX, VIEW_DRUGS?
	map<int, int>::value_type(LAW_MILITARY, VIEW_MILITARY),
	map<int, int>::value_type(LAW_TORTURE, VIEW_TORTURE),
	map<int, int>::value_type(LAW_GUNCONTROL, VIEW_GUNCONTROL),
	map<int, int>::value_type(LAW_PRISONS, VIEW_PRISONS),
};

extern bool nocourtpurge;
extern bool notermlimit;           //These determine if ELAs can take place --kviiri
extern bool stalinmode;
extern bool termlimits;
extern char courtname[COURTNUM][POLITICIAN_NAMELEN];
extern char disbanding;
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern int year;
extern Log gamelog;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short background_liberal_influence[VIEWNUM];
extern short court[COURTNUM];
extern short exec[EXECNUM];
extern short execterm;
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short presparty;
extern short public_interest[VIEWNUM];
extern short senate[SENATENUM];
extern short wincondition;

const string CONST_UNITED_STATES = "United States";
const string corporateSuffixtxt = "corporateSuffix.txt";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";

void addStringYear();
void printCONST_PRESS_ANY_KEY_TO_CONTINUE_THE_ELECTIONS();
void printCONST_A_RECOUNT_WAS_NECESSARY(const int p);
void printSingleVoteOnBill(const int l, const int yesvotes, const bool yeswin, const int p);
void printSingleSenatorSymbol(const int y, const int x, const short senates);
void printSingleWinnerOfElection(const string winner);
void attemptAmendmentEnding(char canseethings, Alignment enforcedAlignment);
void printReflectOnBill();
void printDeadInCongress();
void printWatchPresidentB();
void printWatchPresident();
void printBillResults(const BillStatus bill, const int c);
void displayCongressHeader(const char clearformess);
void addStringYear();
void displayCongressHeaderPartOne();
void displayCongressHeaderPartTwo();
void displayHouseVotes(const int l, const int yesvotes_h, const char yeswin_h, const int c);
void displaySenateVotes(const int l, const int yesvotes_s, const char yeswin_s, const int c, const int s);
void printHouseElectionsHeader();
void printSingleSenator(const short s, const int x, const int y);
void printSenateElectionsHeader();
void printPressAnyKeyElections();
void printSingleHouseMember(const short h, const int y, const int x);
void printHouseChanges(const int x, const int y, const short h, const int change[]);
void printDetermineBill(const int c, const int billdirc, const int billc);
void printCanSeeCourt(const short courtj, const string courtnamej);
void printCanSeeCourtB(const short courtj, const string courtnamej);
void printChangingOfTheGuard();
void printPressKeyToReflect();
void printStatusQuoOrChange(const int l, const int c, const char yeswin, const int yesvotes);
void printCONSTpolitics080();
void printSenateStatus(const int change[]);
void printSupremeCourtRuling(const int c, const string name1, const string name2, const int scasedirc, const int scasec);
void actuallyPrintSenateWinner(const string winner);
void printCONST_PRESS_ANY_KEY_TO_WATCH_THE_ELECTIONS_UNFOLD();
void printCurrentProp(const int p, const int propnumsp, const int propdirp, const int propp);
void printImportantProps();
void printElectionYearHeader();
void printTheElectionsAreHeld();
void printSupremeCourtWatch();
void printSupremeCourtDecides();
void printPressKeyToContinueElections();
void printOneSingleVote(const int votesc, const int c, const int winner, const bool lastVote);
void printWatchElectionUnfold();
void printSingleCandidateTitle(const string candidatec1, const char candidatec0, const int c);
#endif	//POLITICS_CPP
#ifdef	RECRUIT_CPP
// recruit.cpp
#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"

#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"
//#include "../creature/deprecatedCreatureD.h"

////
#include "../items/armortype.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../basemode/activate.h"
// for recruitFindDifficulty and recruitName
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
#include "../common/commondisplayCreature.h"
// for void printcreatureinfo(Creature *,unsigned char=255)
#include "../common/getnames.h"
// for getview
//#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
// for subordinatesleft
#include "../combat/fight.h"

#include "../common/musicClass.h"

/* recruit struct constructor */

#include "../combat/fight.h"

int getkeyAlt();

void pressAnyKey();

void talk(DeprecatedCreature &a, const int t);

void makecreature(const int x, const short type);
short getCurrentSite();
void setCurrentSite(const short i);
extern MusicClass music;
extern short attitude[VIEWNUM];
extern DeprecatedCreature encounter[ENCMAX];

const string MISSING_NO = "missingno";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
void printFoundMultipleRecruits(const string crname);
void printPressEnterToCallItADay(const int recruitCount);
void printAdventuresInRecruitment();
void printSingleRecruit(const int i, const int align, const string name, const string age_string);
void printAskAroundForARecruit(const string recruiter, const string recruit_type);
void printSetupAMeeting(const string crname, const int align, const string rname, const string age_string);
void printWasUnableToTrackDown(const string crname, const string type);
#endif	//RECRUIT_CPP
#ifdef	REVIEWMODE_CPP
// reviewmode.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locationsEnums.h"
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
#include "../common/commondisplayCreature.h"
// for void printfunds(int,int,char*)
#include "../common/getnames.h"
// for std::string getactivity(ActivityST)
//#include "../common/equipment.h"
void consolidateloot(vector<Item *>&);
void equipmentbaseassign();
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
/* tells how many total members a squad has (including dead members) */
// for short reviewmodeenum_to_sortingchoiceenum(short)
//#include "../common/translateid.h"
int getsquad(int);
int getpoolcreature(int);
//#include "../monthly/lcsmonthly.h"
void fundreport(char &clearformess);
void printname(const int hiding, const int location, const int flag, const string name);
#include "../cursesAlternativeConstants.h"
#include "../customMaps.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"
#include "../common/creaturePool.h"

void nukeAllEmptySquads(const vector<int> squadloc, const int mode);

const int PAGELENGTH = 19;

extern short mode;
extern short activesortingchoice[SORTINGCHOICENUM];
extern Deprecatedsquadst *activesquad;
extern long cursquadid;
extern MusicClass music;
extern vector<DeprecatedCreature *> pool;
extern vector<Deprecatedsquadst *> squad;
extern int stat_kills;
extern bool multipleCityMode;
//	extern Log gamelog;

int consolidateSiegeLoot();

const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string CONST_TEMPORARY_SQUAD_CAMELCAPS = "Temporary Squad";
const string CONST_ACTING_INDIVIDUALLY_CAMELCAPS = "Acting Individually";

void printIAmLeader();
void printPromotionScreenSetup(const int iteration);
void printPromotionScreenSetupB(const int iteration);
void printPromotionScreenSetupD(const int iteration, const int level);
void printIsLoveSlave();
void printIsBrainWashed();
void printJustThis(const string name);
void printPromotionFooter(const bool addPage);
void printPromotionHeader();
void printBaseAssignmentFooter(const bool longPool, const bool manyLocations);
void printBaseName(const bool selectedbase, const int iteration, const string locname);
void printLiberalNameInLocation(const bool currentLocation, const bool underSiege, const bool excludeMention, const int iteration, const string tname, const string lname);
void printBaseAssignmentHeader();
void printLosesHeart(const string name);
void printGainsWisdom(const string name);
void printSwapSquadMember();
void printNameWith(const string name);
void printPerformsExecution(const string executor, const string victim);
void printKillAllyPrompt(const string executor);
void printTestifiesAgainstBoss(const string tname, const string bname);
void printHasBeenReleased(const string name);
void printReleaseLiberalPrompt();
void printWhatIsNewName();
void printReviewModeNameFooter(const bool conservative, const bool morePages);
void printRemoveLiberal();
void printKillLiberal();
void printProfileHeader(const bool conservative);
void printSortPeople();
void printSwapMe(const string name);
void printReorderLiberals();
void printPressLetterToViewStats();
void printReviewStringsHeader(const short mode);
void printREVIEWMODE_CLINIC(const int clinic);
void printREVIEWMODE_SLEEPERS(const int align, const string tname);
void printREVIEWMODE_DEAD(const int deathdays);
void printREVIEWMODE_AWAY(const int hiding, const int dating);
void printREVIEWMODE_JUSTICE(const bool deathpenalty, const int sentence, const int location);
void printREVIEWMODE_HOSTAGES(const int joindays);
void printEvaluateLiberalsHeader(const int iteration, const string tname);
void printLiberalHealthStat(const bool bright, const int iteration, const int skill, const string hstat);
void printREVIEWMODE_LIBERALS();
void printREVIEWMODE_LIBERALS(const int type, const string activity);
void setColorAndPositionForReviewmode(const short mode, const int iteration, const string locationname);
void printGiveThisSquadAName(char *name);
void printSquadCannotBeOnlyConservative();
void printPressLetterToViewLiberalDetails();
void printSquadMustBeAbleToMove();
void printSquadMustBeInSameLocation();
void printAddOrRemoveFromSquad(const int partysize);
void printSquadGreen(const int iteration);
void printSquadYellow(const int iteration);
void printSquadAway(const int iteration);
void printCreatureTypename(const int iteration, const int align, const string type);
void printTotalSkill(const int iteration, const int skill, const bool bright);
void printCreatureNameForSquad(const int iteration, const string name);
void printAssembleSquadHeader(const int partysize, const char newsquad, const string name);
void printReviewModeFooter(const bool musicIsEnabled);
void printReviewModeOptions(const int activity, const int iteration, const int numMembers);
void printReviewHeader();
void printReviewActivity(const int activityTypeID, const int iteration, const string str);
void printSquadLocationAndSiegeStatus(const int cursite, const int y, const bool p);
void printSquadName(const string sname, const bool active, const int iteration);
#endif	//REVIEWMODE_CPP
#ifdef	SAVELOAD_CPP
// saveload.cpp

#include "../creature/creature.h"
////

#include "../creature/deprecatedCreatureA.h"
#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../common/equipment.h"
//for void consolidateloot(vector<Item *> &loot);
#include "../common/translateid.h"
// for  getloottype
#include "titlescreen.h"
#include "../common/creaturePool.h"

Item* create_item(const std::string& inputXml);
#include "../common/musicClass.h"
struct  saveLoadChunk {
	void * Buffer;
	size_t      ElementSize;
	size_t      ElementCount;
	saveLoadChunk(void * _Buffer, int _ElementSize, int _ElementCount) :Buffer(_Buffer), ElementSize(_ElementSize), ElementCount(_ElementCount) {}
};

extern bool deagle;
extern bool encounterwarnings;
extern bool m249;
extern bool multipleCityMode;
extern bool nocourtpurge;
extern bool NOSAVE;
extern bool notermlimit;
extern bool NOVERBOSECOMMENTS;
extern bool stalinmode;
extern bool termlimits;
extern bool VERBOSESAVEFILE;
extern CCSexposure ccsexposure;
extern char ccs_kills;
extern char courtname[COURTNUM][POLITICIAN_NAMELEN];
extern char endgamestate;
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern char homedir[MAX_PATH_SIZE];
extern char lcityname[CITY_NAMELEN];
extern char newscherrybusted;
extern char oldPresidentName[POLITICIAN_NAMELEN];
extern char slogan[SLOGAN_LEN];
extern class Ledger ledger;
extern Deprecatedsquadst *activesquad;
extern int amendnum;
extern int day;
extern int month;
extern int police_heat;
extern int stat_burns;
extern int stat_buys;
extern int stat_dead;
extern int stat_kidnappings;
extern int stat_kills;
extern int stat_recruits;
extern int year;
extern Log gamelog;
extern long curcreatureid;
extern long cursquadid;
extern map<short, map<short, string> > getLawFlagStringFull;
extern map<short, string> getLawFlagString;
extern map<short, string> getLawString;
extern map<short, string> skillEnumToString;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short background_liberal_influence[VIEWNUM];
extern short court[COURTNUM];
extern short exec[EXECNUM];
extern short execterm;
extern short fieldskillrate;
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short mode;
extern short offended_amradio;
extern short offended_cablenews;
extern short offended_cia;
extern short offended_corps;
extern short offended_firemen;
extern short party_status;
extern short presparty;
extern short public_interest[VIEWNUM];
extern short senate[SENATENUM];
extern short wincondition;
extern string slogan_str;
extern UniqueCreatures uniqueCreatures;
extern unsigned long attorneyseed[RNG_SIZE];
extern unsigned long seed[RNG_SIZE];
extern vector<DeprecatedCreature *> pool;
extern vector<Deprecateddatest *> date;
extern vector<Deprecatednewsstoryst *> newsstory;
extern vector<Deprecatedrecruitst *> recruit;
extern vector<Deprecatedsquadst *> squad;
extern vector<Location *> location;
extern vector<Vehicle *> vehicle;



const string CONST_AND_ARE_THEREBY_IGNORED = "# and are thereby ignored";
const string CONST_CPP_IO_RB = "rb";
const string CONST_CPP_IO_WB = "wb";
const string CONST_VERBOSE = ".verbose";
const string SINGLE_DOT = ".";
const string CONST_CURSQUADID = "# cursquadid";
const string CONST_CURCREATUREID = "# curcreatureid";
const string CONST_VEHICLE_CURCARID = "# Vehicle::curcarid";
const string CONST_HASH_SPACE = "# ";
const string CONST_CRIMES = "# Crimes";
const string CONST_NEXT_CREATURE = "# Next Creature";
const string CONST_SKILLS = "# Skills";
const string CONST_JUICE = "# Juice";
const string CONST_ALIGNMENT = "# Alignment";
const string CONST_BIRTHDAY_DAY = "# Birthday Day";
const string CONST_BIRTHDAY_MONTH = "# Birthday Month";
const string CONST_AGE = "# Age";
const string CONST_GENDER_LIBERAL = "# Gender (Liberal)";
const string CONST_GENDER_CONSERVATIVE = "# Gender (Conservative)";
const string CONST_PROPER_NAME = "# Proper Name";
const string CONST_NAME = "# Name";
const string CONST_OLDPRESIDENTNAME = "# oldPresidentName";
const string CONST_EXECNAME = "# execname";
const string CONST_EXEC = "# exec";
const string CONST_SUPREME_COURT_NAMES = "# Supreme Court Names";
const string CONST_SUPREME_COURT = "# Supreme Court";
const string CONST_HASH_SENATE = "# Senate";
const string CONST_HASH_HOUSE = "# House";
const string CONST_LAW_LIST = "# Law List";
const string CONST_CONCERNING = "# Concerning ";
const string CONST_ATTITUDE = "# Attitude";
const string CONST_PARTY_STATUS = "# Party Status";
const string CONST_SLOGAN = "# Slogan";
const string CONST_LIBERAL_GUARDIAN_PUBLISHED = "# Liberal Guardian Published";
const string CONST_L_CITY_NAME = "# L City Name";
const string CONST_ATTORNEYSEED = "# attorneyseed";
const string CONST_OFFENDED_FIREMEN = "# Offended Firemen";
const string CONST_OFFENDED_CABLENEWS = "# Offended Cablenews";
const string CONST_OFFENDED_AMRADIO = "# Offended Amradio";
const string CONST_OFFENDED_CIA = "# Offended CIA";
const string CONST_OFFENDED_CORPS = "# Offended Corps";
const string CONST_POLICE_HEAT = "# Police Heat";
const string CONST_CCS_KILLS = "# ccs_kills";
const string CONST_CCSEXPOSURE = "# ccsexposure";
const string CONST_ENDGAMESTATE = "# endgamestate";
const string CONST_STAT_BURNS = "# stat_burns";
const string CONST_STAT_BUYS = "# stat_buys";
const string CONST_STAT_KIDNAPPINGS = "# stat_kidnappings";
const string CONST_STAT_KILLS = "# stat_kills";
const string CONST_STAT_DEAD = "# stat_dead";
const string CONST_STAT_RECRUITS = "# stat_recruits";
const string CONST_STALINMODE = "# stalinmode";
const string CONST_NOCOURTPURGE = "# nocourtpurge";
const string CONST_NOTERMLIMIT = "# notermlimit";
const string CONST_M249 = "# m249";
const string CONST_DEAGLE = "# deagle";
const string CONST_TERMLIMITS = "# termlimits";
const string CONST_MULTIPLECITYMODE = "# multipleCityMode";
const string CONST_AMENDNUM = "# amendnum";
const string CONST_PRESPARTY = "# presparty";
const string CONST_EXECTERM = "# execterm";
const string CONST_YEAR = "# year";
const string CONST_HASH_MONTH = "# month";
const string CONST_HASH_DAY = "# day";
const string CONST_FIELDSKILLRATE = "# fieldskillrate";
const string CONST_WINCONDITION = "# wincondition";
const string CONST_MODE = "# mode";
const string CONST_SEED = "# seed";
const string CONST_LCS_FUNDING_LEVEL_MAX_VALUE_2147483647_CAN_BE_NEGATIVE = "# LCS Funding level (max value 2147483647) can be negative";
const string CONST_NOVERBOSECOMMENTS_TO_REMOVE_THEM_ALMOST_ENTIRELY = "# NOVERBOSECOMMENTS to remove them (almost) entirely";
const string CONST_IF_THESE_COMMENTS_ARE_MORE_TROUBLE_THAN_THEY_RE_WORTH_ADD_TO_THE_DEBUG_DEFINES_TXT_FILE = "# If these comments are more trouble than they're worth, add to the debug_defines.txt file";
const string CONST_THERE_WILL_BE_QUITE_A_FEW_COMMENTS_GENERATED_AUTOMATICALLY = "# There will be quite a few comments generated automatically";
const string CONST_SINCE_THE_PURPOSE_OF_VERBOSE_SAVEFILES_IS_TO_MAKE_THEM_HUMAN_READABLE_AND_EDITABLE = "# Since the purpose of verbose savefiles is to make them human readable and editable,";
const string CONST_ALL_LINES_BEGINNING_WITH_ARE_COMMENTS = "# All lines beginning with # are comments";
const string CONST_REMOVE_NOVERBOSECOMMENTS_TO_ACTIVATE_AUTOCOMMENTS = "# remove NOVERBOSECOMMENTS to activate autocomments";
const string CONST_AUTOCOMMENTS_DISABLED = "# Autocomments disabled";
const string CONST_VERBOSE_FILE_COULD_NOT_BE_OPENED = "Verbose File Could Not Be Opened";
const string CONST_EXPORT = "export";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
void printInvalidVehicle(const string typeidname);
void printInvalidItem(const string typeidname);
#endif	//SAVELOAD_CPP
#ifdef	SHOP_CPP
// shop.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../items/armortype.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../items/loottype.h"
#include "../items/itemPool.h"
#include "../items/loottypePool.h"
#include "../items/loot.h"
#include "../sitemode/shop.h"
//own header 
#include "../common/stringconversion.h"
//for string conversion
#include "../common/commondisplay.h"
// for void printfunds(int,int,char*)
#include "../common/equipment.h"
//for void equip(vector<Item *> &loot,int loc);
//#include "../common/commonactionsCreature.h"
#include "../common/translateid.h"
// for  int getweapontype
#include "../cursesAlternativeConstants.h"
#include "../common/musicClass.h"
#include <functional>

int getkeyAlt();

bool is_page_up(const int c);
bool is_page_down(const int c);
void pressAnyKey();

Item* getNewLoot(const string& newLootType, int num = 1);

void consolidateLoot(const int l);
string getLootTitle(const int base, const int l);
int getFenceValueLocation(int l, int slot);
int getLootNumber(const int base, const int l);
int getLocationLootNumber(int l, int slot);
bool getCanBeSoldLocation(int l, int slot);
void decreateLocationLoot(int loc, int loot, int num);
#include "locations/locationsPool.h"
void equipLoot(int l, int loc);
void deleteLocationLoot(int loc, int loot);
int whatIsThisItemInLocation(int loc, int l);
bool noQuickFenceLocation(int loc, int l);

extern class Ledger ledger;
extern short lawList[LAWNUM];
extern short party_status;
extern vector<ArmorType *> armortype;
extern vector<ClipType *> cliptype;
extern vector<Location *> location;
extern vector<WeaponType *> weapontype;

string asMoney(const int c);

void printBrowseHalfscreenHeader(const string cname);

void printShopOptions(const int y, const bool x, const char letter, const string description);
void printShopFooter(const int _y, const short party_status, const int partysize, const string exit_);
void printOptionsMiddle(const int _y, const bool sell_masks_, const bool left_side, const bool allow_selling_, const int loot);

void printMaskOptions(const int page, const string bname, const vector<int> masktype, const vector<string> mname, const vector<string> mdescription);
void printFenceAmount(const int fenceamount);
void printChooseALiberalTo();

void printReallySellAllThese(const char c);
void printSellLootHeader(const int loot, const int partysize, const short party_status);
void printCantSellDamage();
void printSellingFooter();
void printPageOptions(const bool prev, const bool next);

void printLootForSale(const int i, const int selectedl, const int lootNumber, const string lootTitle);
void printFenceHeader(const int ret);
void printFullscreenFooter(const string bname, const string exit_);
void printFullscreenHeader(const string bname);
void printFullscreenOption(const int p, const string dname);
const string tag_letter = "letter";
const string tag_sleeperprice = "sleeperprice";
const string tag_price = "price";
const string tag_description = "description";
const string tag_type = "type";
const string tag_LOOT = "LOOT";
const string tag_ARMOR = "ARMOR";
const string tag_CLIP = "CLIP";
const string tag_WEAPON = "WEAPON";
const string tag_class = "class";
const string tag_item = "item";
const string tag_sell_masks = "sell_masks";
const string tag_exit = "exit";
const string tag_entry = "entry";
const string tag_department = "department";
const string tag_increase_prices_with_illegality = "increase_prices_with_illegality";
const string tag_allow_selling = "allow_selling";
const string tag_fullscreen = "fullscreen";
const string tag_on = "on";
const string tag_only_sell_legal_items = "only_sell_legal_items";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
extern MusicClass music;
map<string, int> shopInitTags = {
map<string, int>::value_type(tag_only_sell_legal_items, ENUM_tag_only_sell_legal_items),
map<string, int>::value_type(tag_fullscreen, ENUM_tag_fullscreen),
map<string, int>::value_type(tag_allow_selling, ENUM_tag_allow_selling),
map<string, int>::value_type(tag_increase_prices_with_illegality, ENUM_tag_increase_prices_with_illegality),
map<string, int>::value_type(tag_department, ENUM_tag_department),
map<string, int>::value_type(tag_entry, ENUM_tag_entry),
map<string, int>::value_type(tag_exit, ENUM_tag_exit),
map<string, int>::value_type(tag_sell_masks, ENUM_tag_sell_masks),
map<string, int>::value_type(tag_letter, ENUM_tag_letter),
map<string, int>::value_type(tag_item, ENUM_tag_item),

};
map<string, int> shopItemTags = {
	map<string, int>::value_type(tag_class, ENUM_tag_class),
	map<string, int>::value_type(tag_type, ENUM_tag_type),
	map<string, int>::value_type(tag_description, ENUM_tag_description),
	map<string, int>::value_type(tag_price, ENUM_tag_price),
	map<string, int>::value_type(tag_sleeperprice, ENUM_tag_sleeperprice),
	map<string, int>::value_type(tag_letter, ENUM_tag_letter),

};
#endif	//SHOP_CPP
#ifdef	SIEGE_CPP
// siege.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../basemode/baseactions.h"
// for orderparty
#include "../sitemode/sitedisplay.h"
//#include "../sitemode/advance.h"
void creatureadvance();
//#include "../sitemode/miscactions.h"
void reloadparty(bool wasteful = false);
//#include "../sitemode/sitemode.h"
void mode_site(const short loc);
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
// for void cleangonesquads();
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
// for void printfunds(int,int,char*)
#include "../common/translateid.h"
// for  int getsquad(int)
#include "../politics/politics.h"
//for  int publicmood(int l);
#include "../combat/fight.h"   
//for void autopromote(int loc);
#include "../combat/chase.h"
//for void evasiverun();
#include "../customMaps.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"

int getkeyAlt();
int eraseAlt(void);
void pressAnyKey();
int pressSpecificKey(const int x, const int y);

void emptyEncounter();
void fillEncounter(CreatureTypes c, int numleft);
#include "../common/creaturePool.h"
bool hasPrintingPress(int l);
void deletePrintingPress(int loc);
void deleteCompoundWalls(int loc);
void deleteBusinessFront(int loc);
void CCSCapturesSite(int loc);
void endLocationSiege(int l);
void deleteLocationLoot(int l);
void deleteLocationVehicles(int loc);

int baddieCount();
int encounterSize();
vector<NameAndAlignment> getEncounterNameAndAlignment();
short getCurrentSite();
void setCurrentSite(const short i);
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

void printEscapeEngageInfo();
void printEscapeEngageInfoFooter(const bool cameras, const bool traps);
void logDefeat();
void printConquerTextCCS(const int ccs_siege_kills, const int ccs_kills);
void printConquerText(const bool police);

void dropHeatByFivePercent(int l);
int getTimeUntilSiege(int l);
void huntFasterIfSiteIncrediblyHot(int l);
void updateLocationHeatProtection(int l);
void letPlaceCoolOffUnlessCrime(int crimes, int l);
void policeSiege(int l);
void corporateSiege(int l);
void CCSSiege(int l);
void CIASiege(int l);
void hicksSiege(int l);
void firemanSiege(int l);
bool hasCameras(int l);
bool hasAGenerator(int l);
bool hasBusinessFront(int l);
bool siteHasAAGun(int l);
void deleteAAGun(int l);

void deleteGeneratorLightsOff(int l);


int printBestLCSMemberForNews(const string repname, const int l);

bool getLightsOff(int l);
void setLightsOff(int l);
bool hasBasicCompoundWalls(int l);


void reduceCompoundStores(int loc, int amount);
void emptyCompoundStores(int l);
void setUnderAttack(int l);

void baseEveryoneLeftAtHomelessShelter(const int homes);
void escalateSite(int l);
void dumpLootAtLocation(int homes, vector<Item *>& loot);
siegest getWholeSiege(int l);
void cancelOutBleeding();
int print_character_info(const int c, const int party_status);
void countHeroes(int &partysize, int &partyalive);
int print_character_info(const int c, const int party_status);
int getEscapeEngageLocation();
void deleteAllSquadsInActiveAreaExceptActive(const int loc);
void formANewSquadIfThereAreNone();


void juiceEntireCreaturePool(const long juice, const long cap);
void printBrokenLawsFooter(const bool kidnapped, const int typenum);
void printHarboringFugitive();
void printBrokenLawsHeader(const char underAttack, const short escalation);
void printBurnedFlag(const int flagLaw);
void printHireIllegal(const bool lawStatus);
void printReleaseKidnapped(const string kname, const int kidnapped);
void printCCSRaidSafehouse();
void printCorpSiegeWarning(const int sleeper, const string locationName);
void corporateSiegePrint(const string lname);
void printCCSCarbomb();
void printCCSRaid(const string lname);
void printEveryoneInjuredHeader();
void printInjuredList(const vector<pair<string, int> > injuredList);
void printKillList(const vector<pair<string, int> > killList);
void printCCSSleeperWarning(const string lname);
void printJetBombers();
void printTankArrival(const bool tank_traps);
void printSWATArrival();
void printPoliceSiegeHeader(const string lname);
void printPoliceSleeperWarning(const string locationName, const int siegeEscalationState);
void printPoliceSiegeEmptyHeader(const string lname);
void printCorpseRecoveredByPolice(const string corpse, const int y);
void printKidnapRecoveredByPolice(const string kidnap, const int y);
void printSpecificCrime(const Lawflags crime);
void printMostSeriousCrime(const bool breakercount[LAWFLAGNUM]);
void printWantedFor();
void printRehab();
void printEveryoneHereIsDead(const string lname);
void printBusinessFrontTaken();
void printCompoundDismantled();
void printPrintingpressDismantled();
void printMoneyConfiscated(const int confiscated);
void printFundsIntact();
void printLiberalsTakenToPolice(const int pcount);
void printSingleLiberalTaken(const string pname, const string pcname);
void printKidnapFreed();
void printSingleKidnapFreed(const string kname);
void printTheyConfiscateEverything(const int siege, const int escalationState);
void printConquerTextCCS(const int ccs_siege_kills, const int ccs_kills);
void printCorpseRecovery(const int y, const string name);
void printKidnapRescue(const int y, const string name);
void printFiremenSiegeEmpty(const string locationName);
void printFiremenRaid2();
void printFiremenRaid(const string loc);
void printFiremenSiegeEmpty(const bool printingPress, const bool businessFront);
void printCIASiegeWarning(const string locationName);
void printCIASiege(const string locationName, const bool hasCameras, const bool hasAGenerator);
void printRadioHicksSiege(const int l);
void printCableHicksSiege(const int l);
void printFiremenSiege(const bool sleeper, const int l);
void printReporterEnteredCompound(const string repname);
void printThePoliceCutLights(const bool clearformess);
void printReporterDuringSiege(const string repname, const string name, const int segmentpower);
void printShotBySniper(const string targname);
void printMissedBySniper(const string targname);
void printWasKilledInBombing(const string targname);
void printNarrowlyAvoidsDeath(const string targname);
void printNoOneIsHurt(const bool clearformess);
void printCONST_THE_LIGHTS_FADE_AND_ALL_IS_DARK(const bool clearformess);
void printCONST_THE_GENERATOR_HAS_BEEN_DESTROYED(const bool clearformess);
void printCONST_THERE_S_NOTHING_LEFT_BUT_SMOKING_WRECKAGE(const bool clearformess);
void printCONST_THE_ANTI_AIRCRAFT_GUN_TAKES_A_DIRECT_HIT(const bool clearformess);
void printCONST_EXPLOSIONS_ROCK_THE_COMPOUND(const bool clearformess);
void printCONST_A_SKILLED_PILOT_GETS_THROUGH(const bool clearformess);
void printCONST_IT_S_ALL_OVER_THE_TV_EVERYONE_IN_THE_LIBERAL_CRIME_SQUAD_GAINS_20_JUICE(const bool clearformess);
void printCONST_HIT_ONE_OF_THE_BOMBERS_SLAMS_INTO_TO_THE_GROUND(const bool clearformess);
void printCONST_YOU_DIDN_T_SHOOT_ANY_DOWN_BUT_YOU_VE_MADE_THEM_THINK_TWICE(const bool clearformess);
void printCONST_THE_THUNDER_OF_THE_ANTI_AIRCRAFT_GUN_SHAKES_THE_COMPOUND(const bool clearformess);
void printCONST_YOU_HEAR_PLANES_STREAK_OVERHEAD(const bool clearformess);
void printConservativesRaidedUnoccupiedSafehouse(const string locname);
void printCorpseRecovered(const string pname, const int y);
void printLiberalRescued(const string pname, const int y);
void printReflectOnYourConJudgement();
void printSallyForthSiege();
void printSallyForthFooter();
void printYoureFree();
void printSiegeIsBroken();
void printSiegeOptions(const int partysize, const short party_status);
void printLocationName(const string loc);
void printTanksMoveToEntrance(const bool clearformess);
void printEngineersRemoveTankTrap(const bool clearformess);
void logADayPasses();
void printYourLiberalsAreStarving(const bool clearformess);
void printHasStarvedToDeath(const string pname, const bool clearformess);
void printTheCopsAreComing(const bool clearformess);
void printYouHaveEscaped();
void printEscapeEngageInfo();
void printEscapeEngageInfoFooter(const bool cameras, const bool traps);
void logDefeat();
void printConquerText(const bool police);

extern char ccs_kills;
extern char disbanding;
extern char endgamestate;
extern char foughtthisround;
extern class Ledger ledger;
extern Deprecatednewsstoryst *sitestory;
extern Deprecatedsquadst *activesquad;
extern int ccs_siege_kills;
extern int police_heat;
extern int selectedsiege;
extern int stat_dead;
extern Log gamelog;
extern long cursquadid;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short lawList[LAWNUM];
extern short mode;
extern short offended_amradio;
extern short offended_cablenews;
extern short offended_cia;
extern short offended_corps;
extern short offended_firemen;
extern short party_status;
extern vector<DeprecatedCreature *> pool;
extern vector<Deprecatednewsstoryst *> newsstory;
extern vector<Deprecatedsquadst *> squad;

#endif	//SIEGE_CPP
#ifdef	SITEMAP_CPP
// sitemap.cpp

#include "../creature/newcreature.h"
#include "../locations/locations.h"
#include "../configfile.h"
// needed for something contained in sitemap.h
#include "../sitemode/sitemap.h"
		//own header
extern siteblockst levelmap[MAPX][MAPY][MAPZ];
extern int oldMapMode;
extern unsigned long seed[RNG_SIZE];

void emptyEncounter();
void delete_and_clear_groundloot();
map<int, int>  site_special_list = {
	map<int, int> ::value_type(SITE_INDUSTRY_NUCLEAR,           SPECIAL_NUCLEAR_ONOFF),
	map<int, int> ::value_type(SITE_GOVERNMENT_POLICESTATION,   SPECIAL_POLICESTATION_LOCKUP),
	map<int, int> ::value_type(SITE_GOVERNMENT_COURTHOUSE,      SPECIAL_COURTHOUSE_LOCKUP),
	map<int, int> ::value_type(SITE_GOVERNMENT_PRISON,          SPECIAL_PRISON_CONTROL),
	map<int, int> ::value_type(SITE_GOVERNMENT_INTELLIGENCEHQ,  SPECIAL_INTEL_SUPERCOMPUTER),
	map<int, int> ::value_type(SITE_CORPORATE_HEADQUARTERS,     SPECIAL_CORPORATE_FILES),
	map<int, int> ::value_type(SITE_CORPORATE_HOUSE,            SPECIAL_HOUSE_PHOTOS),
	map<int, int> ::value_type(SITE_GOVERNMENT_ARMYBASE,        SPECIAL_ARMORY),
	map<int, int> ::value_type(SITE_MEDIA_AMRADIO,              SPECIAL_RADIO_BROADCASTSTUDIO),
	map<int, int> ::value_type(SITE_MEDIA_CABLENEWS,            SPECIAL_NEWS_BROADCASTSTUDIO),
};
//PREP

const string tag_GENERIC_UNSECURE = "GENERIC_UNSECURE";

const string tag_WEIGHT = "WEIGHT";
const string tag_Z = "Z";
const string tag_FREQ = "FREQ";
const string tag_ZEND = "ZEND";
const string tag_ZSTART = "ZSTART";
const string tag_Y = "Y";
const string tag_YEND = "YEND";
const string tag_YSTART = "YSTART";
const string tag_X = "X";
const string tag_XEND = "XEND";
const string tag_XSTART = "XSTART";
const string tag_STAIRS_RANDOM = "STAIRS_RANDOM";
const string tag_STAIRS = "STAIRS";
const string tag_HALLWAY_YAXIS = "HALLWAY_YAXIS";
const string tag_ROOM = "ROOM";
const string tag_SUBTRACT = "SUBTRACT";
const string tag_ADD = "ADD";
const string tag_NOTE = "NOTE";
const string tag_LOOT = "LOOT";
const string tag_UNIQUE = "UNIQUE";
const string tag_SPECIAL = "SPECIAL";
const string tag_SCRIPT = "SCRIPT";
const string tag_TILE = "TILE";
const string tag_USE = "USE";
const string tag_NAME = "NAME";
const string tag_SITEMAP = "SITEMAP";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
#endif	//SITEMAP_CPP
#ifdef	SITEMODE_CPP
// sitemode.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
//#include "cursesgraphics.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../basemode/baseactions.h"
// for orderparty
#include "../basemode/reviewmode.h"
#include "advance.h"
//#include "sitemode/mapspecials.h"
void special_bouncer_assess_squad();
void special_bouncer_greet_squad();
void special_lab_cosmetics_cagedanimals();
void special_readsign(int sign);
void special_nuclear_onoff();
void special_lab_genetic_cagedanimals();
void special_policestation_lockup();
void special_courthouse_lockup();
void special_courthouse_jury();
void special_prison_control(short prison_control_type);
void special_intel_supercomputer();
void special_sweatshop_equipment();
void special_polluter_equipment();
void special_house_photos();
void special_corporate_files();
void special_radio_broadcaststudio();
void special_news_broadcaststudio();
void special_graffiti();
void special_armory();
void special_display_case();
void special_security_checkpoint();
void special_security_metaldetectors();
void special_security_secondvisit();
void special_bank_teller();
void special_bank_money();
void special_bank_vault();
void special_ccs_boss();
void special_oval_office();
#include "stealth.h"
#include "miscactions.h"
void reloadparty(bool wasteful = false);
#include "sitedisplay.h"
//#include "sitemode/newencounter.h"
void prepareencounter(short type, char sec);
char addsiegeencounter(char type);
#include "../items/lootTypePoolItem.h"
//#include "../log/log.h"
	// for commondisplay.h
#include "../common/commondisplay.h"
// for printparty()
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
// for squadsize
#include "../common/translateid.h"
// for  id_getcar
//#include "common/equipment.h"
/* review squad equipment */
void equip(vector<Item *> &loot, int loc);
//#include "daily/daily.h"
/* daily - returns true if the site type supports high security */
char securityable(int type);
#include "../daily/siege.h"
//for void conquertext();
#include "../combat/fight.h"
#include "../combat/fightCreature.h"  
//for void enemyattack();
#include "../combat/haulkidnap.h"
#include "../combat/haulkidnapCreature.h"
//for void kidnapattempt();
#include "../combat/chase.h"
//for void makechasers(long sitetype,long sitecrime);

int getEncounterAnimalGloss(const int e);
bool get_encounter_cantbluff_is_zero(const int e);
bool get_encounter_cantbluff_is_two(const int e);
bool get_encounter_cantbluff_is_one(const int e);
bool isThereASiteAlarm();
void setSiteAlarmOne();
bool isThereNoActivesquad();
void resetSiteAlarm();
#include "../cursesAlternativeConstants.h"
#include "../common/creaturePoolCreature.h"
#include "../locations/locationsPool.h"
#include "../common/creaturePool.h"
#include "../common/musicClass.h"

extern bool encounterwarnings;

extern bool mapshowing;

extern char ccs_kills;
extern char endgamestate;
extern char foughtthisround;
extern char showcarprefs;

extern chaseseqst chaseseq;

extern coordinatest loc_coord;

extern Deprecatednewsstoryst *sitestory;
extern Deprecatedsquadst *activesquad;

extern int ccs_boss_kills;
extern int sitecrime;
extern MusicClass music;

extern short fieldskillrate;
extern short lawList[LAWNUM];
extern short mode;
extern short offended_amradio;
extern short offended_cablenews;
extern short party_status;
extern short postalarmtimer;
extern short sitealarmtimer;
extern short sitealienate;
extern short sitetype;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];

extern UniqueCreatures uniqueCreatures;
extern vector<Item *> groundloot;


void emptyEncounter();
void delete_and_clear_groundloot();
bool isThereGroundLoot();

void deleteVehicle(int carid);
void deleteVehicles(vector<Vehicle *>& carid);
enum INDEX_WITH_SPECIAL_MEANING {
	MULTIPLE_LIVING_MEMBERS = -2,
	NO_VALID_MEMBERS = -1,
};
vector<NameAndAlignment> getEncounterNameAndAlignment();
char haveActiveSquadTalk(const int sp, const int tk);
void printActiveSquadTalkOptions();
bool activeSquadMemberIsAliveAndExists(const int sp);
CantBluffAnimal encounterGetCantBluffAnimal(const int t);
CreatureBio encounterGetCreatureBio(const int t);
vector<NameAndAlignment> getEncounterNameAndAlignment();
int checkForPeopleWhoCanRecruit();
void addNewRecruit(int i, int e);
int countactivesquadhostages();
void assembleActiveSquad();
/* base - review - assemble a squad */
void criminalizeEncounterPrisonerEscape(const int e);
void duplicateEncounterMember(const int e);
void unpersonLastEncounterMember();
void getRandomLoot(int cursite);
Weapon* spawnNewWeapon(string newWeaponType);
Armor* spawnNewArmor(string newArmorType);

void giveActiveSquadThisLoot(Item* de);
void putBackSpecials(const int olocx, const int olocy, const int olocz);
void spawnCreatureCEO();

void killActiveSquad();
int getactivesquadCarID(const int p);
void set_sitestory_type();
int getactivesquadBase();


char shouldWeBailOnBase();
bool isActiveSquadAnonymous();
void set_site_story_as_last_news_story();
void setSiteStoryClaimedZero();
void resetSiteGlobals();
void setCurrentSite(const short i);
void resetCCSSiegeGlobals();

int getEncounterCarID(const int e);
int getEncounterIsDriver(const int e);

const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_FLAMETHROWER = "WEAPON_FLAMETHROWER";
const string tag_LOOT = "LOOT";
const string tag_LOOT_COMPUTER = "LOOT_COMPUTER";
const string tag_LOOT_CHEAPJEWELERY = "LOOT_CHEAPJEWELERY";
const string tag_LOOT_TRINKET = "LOOT_TRINKET";
const string tag_LOOT_SILVERWARE = "LOOT_SILVERWARE";
const string tag_LOOT_CELLPHONE = "LOOT_CELLPHONE";
const string tag_ARMOR_CIVILLIANARMOR = "ARMOR_CIVILLIANARMOR";
const string tag_ARMOR_SECURITYUNIFORM = "ARMOR_SECURITYUNIFORM";
const string tag_ARMOR_ARMYARMOR = "ARMOR_ARMYARMOR";
const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_HEAVYARMOR = "ARMOR_HEAVYARMOR";
const string tag_ARMOR_CHEAPSUIT = "ARMOR_CHEAPSUIT";
const string tag_ARMOR_WORKCLOTHES = "ARMOR_WORKCLOTHES";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_ARMOR_TRENCHCOAT = "ARMOR_TRENCHCOAT";
const string tag_WEAPON_AUTORIFLE_M16 = "WEAPON_AUTORIFLE_M16";
const string tag_WEAPON_SMG_MP5 = "WEAPON_SMG_MP5";
const string tag_WEAPON_CARBINE_M4 = "WEAPON_CARBINE_M4";
const string tag_WEAPON_REVOLVER_38 = "WEAPON_REVOLVER_38";
const string tag_WEAPON_REVOLVER_44 = "WEAPON_REVOLVER_44";
const string tag_WEAPON_SEMIPISTOL_9MM = "WEAPON_SEMIPISTOL_9MM";
const string tag_WEAPON_SEMIPISTOL_45 = "WEAPON_SEMIPISTOL_45";
const string tag_LOOT_PDA = "LOOT_PDA";
const string tag_LOOT_MICROPHONE = "LOOT_MICROPHONE";
const string tag_LOOT_CABLENEWSFILES = "LOOT_CABLENEWSFILES";
const string tag_LOOT_AMRADIOFILES = "LOOT_AMRADIOFILES";
const string tag_LOOT_FAMILYPHOTO = "LOOT_FAMILYPHOTO";
const string tag_LOOT_WATCH = "LOOT_WATCH";
const string tag_ARMOR_BONDAGEGEAR = "ARMOR_BONDAGEGEAR";
const string tag_ARMOR_EXPENSIVESUIT = "ARMOR_EXPENSIVESUIT";
const string tag_ARMOR_EXPENSIVEDRESS = "ARMOR_EXPENSIVEDRESS";
const string tag_LOOT_CORPFILES = "LOOT_CORPFILES";
const string tag_LOOT_CHEMICAL = "LOOT_CHEMICAL";
const string tag_LOOT_FINECLOTH = "LOOT_FINECLOTH";
const string tag_ARMOR_BUNKERGEAR = "ARMOR_BUNKERGEAR";
const string tag_LOOT_SECRETDOCUMENTS = "LOOT_SECRETDOCUMENTS";
const string tag_WEAPON_SHANK = "WEAPON_SHANK";
const string tag_ARMOR_PRISONER = "ARMOR_PRISONER";
const string tag_LOOT_JUDGEFILES = "LOOT_JUDGEFILES";
const string tag_LOOT_POLICERECORDS = "LOOT_POLICERECORDS";
const string tag_ARMOR_POLICEARMOR = "ARMOR_POLICEARMOR";
const string tag_ARMOR_SWATARMOR = "ARMOR_SWATARMOR";
const string tag_ARMOR_POLICEUNIFORM = "ARMOR_POLICEUNIFORM";
const string tag_ARMOR_DEATHSQUADUNIFORM = "ARMOR_DEATHSQUADUNIFORM";
const string tag_WEAPON_SHOTGUN_PUMP = "WEAPON_SHOTGUN_PUMP";
const string tag_WEAPON_NIGHTSTICK = "WEAPON_NIGHTSTICK";
const string tag_LOOT_LABEQUIPMENT = "LOOT_LABEQUIPMENT";
const string tag_LOOT_RESEARCHFILES = "LOOT_RESEARCHFILES";
const string tag_LOOT_EXPENSIVEJEWELERY = "LOOT_EXPENSIVEJEWELERY";
const string tag_ARMOR_BLACKROBE = "ARMOR_BLACKROBE";
const string tag_ARMOR_LABCOAT = "ARMOR_LABCOAT";
const string tag_ARMOR_BLACKDRESS = "ARMOR_BLACKDRESS";
const string tag_ARMOR_BLACKSUIT = "ARMOR_BLACKSUIT";
const string tag_WEAPON_SEMIRIFLE_AR15 = "WEAPON_SEMIRIFLE_AR15";
const string tag_WEAPON_COMBATKNIFE = "WEAPON_COMBATKNIFE";
const string tag_WEAPON_BASEBALLBAT = "WEAPON_BASEBALLBAT";
const string tag_WEAPON_DAISHO = "WEAPON_DAISHO";
const string tag_ARMOR_CLOWNSUIT = "ARMOR_CLOWNSUIT";
const string tag_ARMOR_DONKEYSUIT = "ARMOR_DONKEYSUIT";
const string tag_ARMOR_ELEPHANTSUIT = "ARMOR_ELEPHANTSUIT";
const string tag_ARMOR_CHEAPDRESS = "ARMOR_CHEAPDRESS";
const string tag_WEAPON_GUITAR = "WEAPON_GUITAR";
const string tag_LOOT_DIRTYSOCK = "LOOT_DIRTYSOCK";
const string tag_LOOT_KIDART = "LOOT_KIDART";
const string tag_ARMOR_TOGA = "ARMOR_TOGA";
const string tag_WEAPON_SPRAYCAN = "WEAPON_SPRAYCAN";
const string tag_WEAPON_SYRINGE = "WEAPON_SYRINGE";
const string tag_WEAPON_CHAIN = "WEAPON_CHAIN";
const string tag_WEAPON_CROWBAR = "WEAPON_CROWBAR";


const string rndWeps[] = { tag_WEAPON_SEMIPISTOL_9MM, tag_WEAPON_SEMIPISTOL_45, tag_WEAPON_REVOLVER_38, tag_WEAPON_REVOLVER_44,
tag_WEAPON_SMG_MP5, tag_WEAPON_CARBINE_M4, tag_WEAPON_AUTORIFLE_M16 };
const string rndArmors[] = { tag_ARMOR_CHEAPSUIT, tag_ARMOR_CLOTHES, tag_ARMOR_TRENCHCOAT, tag_ARMOR_WORKCLOTHES,
	tag_ARMOR_SECURITYUNIFORM, tag_ARMOR_CIVILLIANARMOR, tag_ARMOR_ARMYARMOR, tag_ARMOR_HEAVYARMOR };
void printMap(const bool has_cameras);
void printLocationSpecificWarning(const int lsite, const bool ccsRent);
void printLocationNameAndAlarm(const string lname, const int postalarmtimer, const int locz);
void printCONSERVATIVES_SUSPICIOUS();
void printCONSERVATIVES_ALARMED();
void printALIENATED_EVERYONE();
void printALIENATED_MASSES();
void printCONSERVATIVE_REINFORCEMENTS_INCOMING();
void printSiegeName(const string sname, const int locz);
bool isPrisoner(const string tkname);
void printEnemyCar(const string cname, const int v);
void printClearChaseScreen();
void printEnemyCarPassenger(const string ename, const int vnum, const int pnum, const bool driver);
void printReflectOnIneptitude();
void printSneakOrRun(const bool evade);
void printReorganize(const int libnum);
void printReleaseHostages(const bool hostages);
void printReleaseOppressed();
void printEquipAndFight(const bool enemy);
void printEvade();
void printUseOrGraffiti(const bool graffiti, const bool print_me);
void printPlayerSiteOptions(const bool isThereASiteAlarm, const bool enemy, const int partysize, const int party_status, const bool talkers);
void printShowEncounterWarning(const int numenc, const bool squadmoved);
void printTheLandlordIsIn();
void printTheLandlordIsOut();
void printTheCEOIsIn();
void printTheCEOIsOut();
void printTheCEOHasFled();
void printEmptyBench();
void printFullBench();
void printRestaurantTableFull();
void printRestaurantTableHiding();
void printCafeComputerEmpty();
void printCafeComputerFull();
void printTheCCSIsBroken();
void logBailOnBase(const string aname, const string sitename);
void printFoughtOffConservatives();
void printSneakPast();
void printYouFind(const string that_thing);
void printFreeThem(const int followers);
void printYouHaveEnemiesFirst();
void printFreeThemWithoutYou(const int followers, const int actgot);
void printIWontTalkToYou(const string tkname);
void printCreatureEncounter(const int t, const int talign, const string tname, const string tage);
void printToWhom();
void printActiveSquadTalkOptionsHeader();
void printMusicEnabled(const bool musice);
void printEncounterWarnings(const bool ewarn);
void printSitemodeOptions();
void printSitemodeOptionsHeader();
void printWhichWay();
void printSquadSubduedHostagesFreed(const int hostages);
void printItOpensWithAlarm();
void printVaultIsImpenetrable();
void printUnlockedButAlarmed(const bool locked);
void printShakeHandle(const bool locked, const bool has_security);
void printLockpickPrompt();
void printLockSetOffAlarm();
void printAlarmGoesOff();
#endif	//SITEMODE_CPP
#ifdef	SLEEPER_UPDATE_CPP
// sleeper_update.cpp

#include "../creature/creature.h"
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
//#include "sitemode/newencounter.h"
void prepareencounter(short type, char sec);
#include "../items/lootTypePoolItem.h"
//#include "common/commonactions.h"
void change_public_opinion(int v, int power, char affect = 1, char cap = 100);
#include "../common/commonactionsCreature.h"
//#include "../log/log.h"
#include "../common/translateid.h"
	// for  int getloottype(int id);
#include "../common/creaturePoolCreature.h"
#include "../locations/locationsPool.h"

extern short attitude[VIEWNUM];
extern CCSexposure ccsexposure;
extern class Ledger ledger;
extern short lawList[LAWNUM];
extern char disbanding;


const string tag_LOOT = "LOOT";
const string tag_LOOT_COMPUTER = "LOOT_COMPUTER";
const string tag_LOOT_PDA = "LOOT_PDA";
const string tag_LOOT_CELLPHONE = "LOOT_CELLPHONE";
const string tag_LOOT_SECRETDOCUMENTS = "LOOT_SECRETDOCUMENTS";
const string tag_ARMOR_BLACKSUIT = "ARMOR_BLACKSUIT";
const string tag_ARMOR = "ARMOR";
const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_CARBINE_M4 = "WEAPON_CARBINE_M4";
const string tag_WEAPON_SHOTGUN_PUMP = "WEAPON_SHOTGUN_PUMP";
const string tag_WEAPON_AUTORIFLE_M16 = "WEAPON_AUTORIFLE_M16";
const string tag_WEAPON_SMG_MP5 = "WEAPON_SMG_MP5";
const string tag_LOOT_SILVERWARE = "LOOT_SILVERWARE";
const string tag_LOOT_CHEMICAL = "LOOT_CHEMICAL";
const string tag_ARMOR_ARMYARMOR = "ARMOR_ARMYARMOR";
const string tag_LOOT_POLICERECORDS = "LOOT_POLICERECORDS";
const string tag_ARMOR_POLICEARMOR = "ARMOR_POLICEARMOR";
const string tag_ARMOR_SWATARMOR = "ARMOR_SWATARMOR";
const string tag_ARMOR_POLICEUNIFORM = "ARMOR_POLICEUNIFORM";
const string tag_ARMOR_DEATHSQUADUNIFORM = "ARMOR_DEATHSQUADUNIFORM";
const string tag_WEAPON_SEMIRIFLE_AR15 = "WEAPON_SEMIRIFLE_AR15";
const string tag_WEAPON_SEMIPISTOL_45 = "WEAPON_SEMIPISTOL_45";
const string tag_LOOT_MICROPHONE = "LOOT_MICROPHONE";
const string tag_LOOT_CABLENEWSFILES = "LOOT_CABLENEWSFILES";
const string tag_LOOT_AMRADIOFILES = "LOOT_AMRADIOFILES";
const string tag_LOOT_FAMILYPHOTO = "LOOT_FAMILYPHOTO";
const string tag_LOOT_CHEAPJEWELERY = "LOOT_CHEAPJEWELERY";
const string tag_LOOT_WATCH = "LOOT_WATCH";
const string tag_LOOT_TRINKET = "LOOT_TRINKET";
const string tag_LOOT_CORPFILES = "LOOT_CORPFILES";
const string tag_LOOT_FINECLOTH = "LOOT_FINECLOTH";
const string tag_WEAPON_SHANK = "WEAPON_SHANK";
const string tag_LOOT_JUDGEFILES = "LOOT_JUDGEFILES";
const string tag_LOOT_LABEQUIPMENT = "LOOT_LABEQUIPMENT";
const string tag_LOOT_RESEARCHFILES = "LOOT_RESEARCHFILES";
const string tag_LOOT_EXPENSIVEJEWELERY = "LOOT_EXPENSIVEJEWELERY";
const string tag_LOOT_DIRTYSOCK = "LOOT_DIRTYSOCK";
const string tag_LOOT_KIDART = "LOOT_KIDART";
const string tag_LOOT_CCS_BACKERLIST = "LOOT_CCS_BACKERLIST";
const string tag_LOOT_PRISONFILES = "LOOT_PRISONFILES";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";


map<CreatureTypes, vector<CreatureSkill> > skill_influence = {
	map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_CRITIC_ART,
		{ SKILL_WRITING, SKILL_ART }
		),
		map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_PAINTER,
			{ SKILL_ART }
		),
			map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_SCULPTOR,
				{ SKILL_ART }
			),
				map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_CRITIC_MUSIC,
					{ SKILL_WRITING, SKILL_MUSIC }
				),
					map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_MUSICIAN,
						{ SKILL_MUSIC }
					),
						map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_AUTHOR,
							{ SKILL_WRITING }
						),
							map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_JOURNALIST,
								{ SKILL_WRITING }
							),
								map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_JUDGE_CONSERVATIVE,
									{ SKILL_WRITING, SKILL_LAW }
								),
									map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_LAWYER,
										{ SKILL_LAW }
									),
										map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_SCIENTIST_LABTECH,
											{ SKILL_SCIENCE }
										),
											map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_SCIENTIST_EMINENT,
												{ SKILL_SCIENCE }
											),
												map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_CORPORATE_CEO,
													{ SKILL_BUSINESS }
												),
													map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_CORPORATE_MANAGER,
														{ SKILL_BUSINESS }
													),
														map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_PRIEST,
															{ SKILL_RELIGION }
														),
															map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_NUN,
																{ SKILL_RELIGION }
															),
																map<CreatureTypes, vector<CreatureSkill> > ::value_type(CREATURE_EDUCATOR,
																	{ SKILL_PSYCHOLOGY }
																),
};

map<CreatureTypes, int> super_sleepers_multiplier = {
	map<CreatureTypes, int> ::value_type(CREATURE_CORPORATE_CEO, 20),
	map<CreatureTypes, int> ::value_type(CREATURE_POLITICIAN, 20),
	map<CreatureTypes, int> ::value_type(CREATURE_SCIENTIST_EMINENT, 20),
	map<CreatureTypes, int> ::value_type(CREATURE_DEATHSQUAD, 6),
	map<CreatureTypes, int> ::value_type(CREATURE_EDUCATOR, 6),
	map<CreatureTypes, int> ::value_type(CREATURE_MILITARYOFFICER, 6),
	map<CreatureTypes, int> ::value_type(CREATURE_ACTOR, 4),
	map<CreatureTypes, int> ::value_type(CREATURE_GANGUNIT, 4),
	map<CreatureTypes, int> ::value_type(CREATURE_MILITARYPOLICE, 4),
	map<CreatureTypes, int> ::value_type(CREATURE_SEAL, 4),
};

map<CreatureTypes, vector<Views> > creature_influences_views = {

	/* Cultural leaders block - influences cultural issues */
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_PRIEST,
		{ VIEW_WOMEN,
		VIEW_CIVILRIGHTS,
		VIEW_GAY,
		VIEW_FREESPEECH,
		VIEW_DRUGS,
		VIEW_IMMIGRATION }
		),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_PAINTER,
		{ VIEW_WOMEN,
		VIEW_CIVILRIGHTS,
		VIEW_GAY,
		VIEW_FREESPEECH,
		VIEW_DRUGS,
		VIEW_IMMIGRATION }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_SCULPTOR,
		{ VIEW_WOMEN,
		VIEW_CIVILRIGHTS,
		VIEW_GAY,
		VIEW_FREESPEECH,
		VIEW_DRUGS,
		VIEW_IMMIGRATION }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_AUTHOR,
		{ VIEW_WOMEN,
		VIEW_CIVILRIGHTS,
		VIEW_GAY,
		VIEW_FREESPEECH,
		VIEW_DRUGS,
		VIEW_IMMIGRATION }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_JOURNALIST,
		{ VIEW_WOMEN,
		VIEW_CIVILRIGHTS,
		VIEW_GAY,
		VIEW_FREESPEECH,
		VIEW_DRUGS,
		VIEW_IMMIGRATION }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_PSYCHOLOGIST,
		{ VIEW_WOMEN,
		VIEW_CIVILRIGHTS,
		VIEW_GAY,
		VIEW_FREESPEECH,
		VIEW_DRUGS,
		VIEW_IMMIGRATION }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_MUSICIAN,
		{ VIEW_WOMEN,
		VIEW_CIVILRIGHTS,
		VIEW_GAY,
		VIEW_FREESPEECH,
		VIEW_DRUGS,
		VIEW_IMMIGRATION }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_CRITIC_ART,
		{ VIEW_WOMEN,
		VIEW_CIVILRIGHTS,
		VIEW_GAY,
		VIEW_FREESPEECH,
		VIEW_DRUGS,
		VIEW_IMMIGRATION }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_CRITIC_MUSIC,
		{ VIEW_WOMEN,
		VIEW_CIVILRIGHTS,
		VIEW_GAY,
		VIEW_FREESPEECH,
		VIEW_DRUGS,
		VIEW_IMMIGRATION }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_ACTOR,
		{ VIEW_WOMEN,
		VIEW_CIVILRIGHTS,
		VIEW_GAY,
		VIEW_FREESPEECH,
		VIEW_DRUGS,
		VIEW_IMMIGRATION }
	),
	/* Legal block - influences an array of social issues */
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_JUDGE_CONSERVATIVE,
		{ VIEW_JUSTICES,
		VIEW_FREESPEECH,
		VIEW_INTELLIGENCE,
		VIEW_POLICEBEHAVIOR,
		VIEW_DEATHPENALTY,
		VIEW_GUNCONTROL,
		VIEW_DRUGS }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_LAWYER,
		{ VIEW_POLICEBEHAVIOR,
		VIEW_DEATHPENALTY,
		VIEW_GUNCONTROL,
		VIEW_DRUGS }
	),
	/* Scientists block */
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_SCIENTIST_EMINENT,
		{ VIEW_POLLUTION,
		VIEW_NUCLEARPOWER,
		VIEW_ANIMALRESEARCH,
		VIEW_GENETICS }
	),


	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_SCIENTIST_LABTECH,
		{ VIEW_NUCLEARPOWER,
		VIEW_ANIMALRESEARCH,
		VIEW_GENETICS }
	),
	/* Corporate block */
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_CORPORATE_CEO,
		{ VIEW_CEOSALARY,
		VIEW_WOMEN,
		VIEW_TAXES,
		VIEW_CORPORATECULTURE,
		VIEW_SWEATSHOPS,
		VIEW_POLLUTION,
		VIEW_CIVILRIGHTS }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_CORPORATE_MANAGER,
		{ VIEW_WOMEN,
		VIEW_TAXES,
		VIEW_CORPORATECULTURE,
		VIEW_SWEATSHOPS,
		VIEW_POLLUTION,
		VIEW_CIVILRIGHTS }
	),
	/* Law enforcement block */
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_DEATHSQUAD,
		{ VIEW_PRISONS,
		VIEW_DEATHPENALTY,
		VIEW_POLICEBEHAVIOR,
		VIEW_DRUGS,
		VIEW_TORTURE,
		VIEW_GUNCONTROL,
		VIEW_PRISONS }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_SWAT,
		{ VIEW_POLICEBEHAVIOR,
		VIEW_DRUGS,
		VIEW_TORTURE,
		VIEW_GUNCONTROL,
		VIEW_PRISONS }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_COP,
		{ VIEW_POLICEBEHAVIOR,
		VIEW_DRUGS,
		VIEW_TORTURE,
		VIEW_GUNCONTROL,
		VIEW_PRISONS }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_GANGUNIT,
		{ VIEW_POLICEBEHAVIOR,
		VIEW_DRUGS,
		VIEW_TORTURE,
		VIEW_GUNCONTROL,
		VIEW_PRISONS }
	),
	/* Prison block */
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_EDUCATOR,
		{ VIEW_POLICEBEHAVIOR,
		VIEW_DEATHPENALTY,
		VIEW_DRUGS,
		VIEW_TORTURE,
		VIEW_PRISONS }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_PRISONGUARD,
		{ VIEW_POLICEBEHAVIOR,
		VIEW_DEATHPENALTY,
		VIEW_DRUGS,
		VIEW_TORTURE,
		VIEW_PRISONS }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_PRISONER,
		{ VIEW_POLICEBEHAVIOR,
		VIEW_DEATHPENALTY,
		VIEW_DRUGS,
		VIEW_TORTURE,
		VIEW_PRISONS }
	),
	/* Intelligence block */
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_SECRET_SERVICE,
		{ VIEW_INTELLIGENCE }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_AGENT,
		{ VIEW_INTELLIGENCE,
		VIEW_TORTURE,
		VIEW_PRISONS,
		VIEW_FREESPEECH }
	),
	/* Military block */
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_MERC,
		{ VIEW_GUNCONTROL }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_SOLDIER,
		{ VIEW_MILITARY,
		VIEW_TORTURE,
		VIEW_GAY,
		VIEW_WOMEN }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_VETERAN,
		{ VIEW_MILITARY,
		VIEW_TORTURE,
		VIEW_GAY,
		VIEW_WOMEN }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_MILITARYPOLICE,
		{ VIEW_MILITARY,
		VIEW_TORTURE,
		VIEW_GAY,
		VIEW_WOMEN }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_MILITARYOFFICER,
		{ VIEW_MILITARY,
		VIEW_TORTURE,
		VIEW_GAY,
		VIEW_WOMEN }
	),
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_SEAL,
		{ VIEW_MILITARY,
		VIEW_TORTURE,
		VIEW_GAY,
		VIEW_WOMEN }
	),
	/* Sweatshop workers */
	map<CreatureTypes, vector<Views> > ::value_type(CREATURE_WORKER_SWEATSHOP,
		{ VIEW_IMMIGRATION,
		VIEW_SWEATSHOPS }
	),
};

void printCreatureLeaksIntelligence(const string crname);
void printCreatureLeaksPolice(const string crname);
void printCreatureLeaksCorp(const string crname);
void printCreatureLeaksPrison(const string crname);
void printCreatureLeaksCable(const string crname);
void printCreatureLeaksRadio(const string crname);
void printCreatureLeaksAnimalResearch(const string crname);
void printCreatureLeaksJudiciary(const string crname);
void printCreatureLeaksCCS(const string crname);
void printArrestedWhileEmbezzling(const string crname);
void printHasBeenCaughtSnooping(const string crname);
void printArrestedWhileStealing(const string crname);
void printSleeperDropOffPackage(const string crname);
void printxmlFail(const int numberofxmlfails);
void pressAnyKey();
#endif	//SLEEPER_UPDATE_CPP
#ifdef	STEALTH_CPP
// stealth.cpp

#include "../creature/creature.h"
////

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../sitemode/sitedisplay.h"
#include "../common/commonactionsCreature.h"
#include "../locations/locationsPool.h"
#include "../customMaps.h"

short getCurrentSite();
extern short fieldskillrate;

/* checks if your liberal activity is noticed */
char disguisesite(long type);

vector<NameAndAlignment> getEncounterNameAndAlignment();
bool isThereASiteAlarm();
void setSiteAlarmOne();
void conservatise(const int e);

int get_stealth_difficulty(const int n);
int get_disguise_difficulty(const int n);
int get_encounter_time(const int n);
vector<int> potentialEncounterNoticers();

extern coordinatest loc_coord;
extern Deprecatedsquadst *activesquad;
extern short fieldskillrate;
extern short lawList[LAWNUM];
extern short mode;
extern short sitealarmtimer;
extern short sitealienate;
extern short sitetype;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];

const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_BUNKERGEAR = "ARMOR_BUNKERGEAR";
const string tag_ARMOR_SWATARMOR = "ARMOR_SWATARMOR";
const string tag_ARMOR_DEATHSQUADUNIFORM = "ARMOR_DEATHSQUADUNIFORM";
const string tag_ARMOR_POLICEARMOR = "ARMOR_POLICEARMOR";
const string tag_ARMOR_POLICEUNIFORM = "ARMOR_POLICEUNIFORM";
const string tag_ARMOR_EXPENSIVEDRESS = "ARMOR_EXPENSIVEDRESS";
const string tag_ARMOR_EXPENSIVESUIT = "ARMOR_EXPENSIVESUIT";
const string tag_ARMOR_SECURITYUNIFORM = "ARMOR_SECURITYUNIFORM";
const string tag_ARMOR_CHEAPDRESS = "ARMOR_CHEAPDRESS";
const string tag_ARMOR_CHEAPSUIT = "ARMOR_CHEAPSUIT";
const string tag_ARMOR_SEALSUIT = "ARMOR_SEALSUIT";
const string tag_ARMOR_ARMYARMOR = "ARMOR_ARMYARMOR";
const string tag_ARMOR_MILITARY = "ARMOR_MILITARY";
const string tag_ARMOR_SERVANTUNIFORM = "ARMOR_SERVANTUNIFORM";
const string tag_ARMOR_HARDHAT = "ARMOR_HARDHAT";
const string tag_ARMOR_CIVILLIANARMOR = "ARMOR_CIVILLIANARMOR";
const string tag_ARMOR_LABCOAT = "ARMOR_LABCOAT";
const string tag_ARMOR_WORKCLOTHES = "ARMOR_WORKCLOTHES";
const string tag_ARMOR_BLACKDRESS = "ARMOR_BLACKDRESS";
const string tag_ARMOR_BLACKSUIT = "ARMOR_BLACKSUIT";
const string tag_ARMOR_OVERALLS = "ARMOR_OVERALLS";
const string tag_ARMOR_PRISONER = "ARMOR_PRISONER";
const string tag_ARMOR_PRISONGUARD = "ARMOR_PRISONGUARD";
const string tag_ARMOR_BLACKROBE = "ARMOR_BLACKROBE";
const string tag_ARMOR_HEAVYARMOR = "ARMOR_HEAVYARMOR";
const string tag_ARMOR_WIFEBEATER = "ARMOR_WIFEBEATER";
const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_CARBINE_M4 = "WEAPON_CARBINE_M4";
const string tag_WEAPON_CHAIN = "WEAPON_CHAIN";
const string tag_WEAPON_SHANK = "WEAPON_SHANK";
const string tag_WEAPON_SHOTGUN_PUMP = "WEAPON_SHOTGUN_PUMP";
const string tag_WEAPON_TORCH = "WEAPON_TORCH";
const string tag_WEAPON_PITCHFORK = "WEAPON_PITCHFORK";
const string tag_WEAPON_NIGHTSTICK = "WEAPON_NIGHTSTICK";
const string tag_WEAPON_SMG_MP5 = "WEAPON_SMG_MP5";
const string tag_WEAPON_FLAMETHROWER = "WEAPON_FLAMETHROWER";
const string tag_WEAPON_AXE = "WEAPON_AXE";
const string tag_WEAPON_SEMIRIFLE_AR15 = "WEAPON_SEMIRIFLE_AR15";
const string tag_WEAPON_AUTORIFLE_M16 = "WEAPON_AUTORIFLE_M16";
const string tag_WEAPON_SEMIPISTOL_45 = "WEAPON_SEMIPISTOL_45";
const string tag_WEAPON_DESERT_EAGLE = "WEAPON_DESERT_EAGLE";
const string tag_WEAPON_SEMIPISTOL_9MM = "WEAPON_SEMIPISTOL_9MM";
const string tag_WEAPON_REVOLVER_38 = "WEAPON_REVOLVER_38";
const string tag_WEAPON_REVOLVER_44 = "WEAPON_REVOLVER_44";
const string tag_WEAPON_GAVEL = "WEAPON_GAVEL";
const string tag_WEAPON_SYRINGE = "WEAPON_SYRINGE";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_WEAPON_MP5_SMG = "WEAPON_MP5_SMG";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

map<short, map<string, int> > siegeDisguises = {
	map<SiegeTypes, map<string, int> >::value_type(SIEGE_CIA,
		{
			map<string, int>::value_type(tag_ARMOR_BLACKSUIT, 1),
			map<string, int>::value_type(tag_ARMOR_BLACKDRESS, 1)
		}
	),

	map<SiegeTypes, map<string, int> >::value_type(SIEGE_CORPORATE,
		{
			map<string, int>::value_type(tag_ARMOR_MILITARY,  1),
			map<string, int>::value_type(tag_ARMOR_ARMYARMOR,  1),
			map<string, int>::value_type(tag_ARMOR_SEALSUIT,  1),
		}
	),
	map<SiegeTypes, map<string, int> >::value_type(SIEGE_HICKS,
		{
			map<string, int>::value_type(tag_ARMOR_CLOTHES,  2),
			map<string, int>::value_type(tag_ARMOR_OVERALLS,  1),
			map<string, int>::value_type(tag_ARMOR_WIFEBEATER, 1),
		}
	),
	map<SiegeTypes, map<string, int> >::value_type(SIEGE_FIREMEN,
		{
			map<string, int>::value_type(tag_ARMOR_BUNKERGEAR, 1),
		}
   ),
};

map<short, map<string, int> > siteDisguises = {

	map<SiteTypes, map<string, int> >::value_type(SITE_BUSINESS_CIGARBAR,{
	map<string, int>::value_type(tag_ARMOR_EXPENSIVESUIT,  1),
	map<string, int>::value_type(tag_ARMOR_CHEAPSUIT,  1),
	map<string, int>::value_type(tag_ARMOR_EXPENSIVEDRESS,  1),
	map<string, int>::value_type(tag_ARMOR_CHEAPDRESS,  1),
	map<string, int>::value_type(tag_ARMOR_BLACKSUIT,  1),
	map<string, int>::value_type(tag_ARMOR_BLACKDRESS,  1),
}
),
map<SiteTypes, map<string, int> >::value_type(SITE_CORPORATE_HEADQUARTERS,{
	map<string, int>::value_type(tag_ARMOR_EXPENSIVESUIT,  1),
	map<string, int>::value_type(tag_ARMOR_CHEAPSUIT,  1),
	map<string, int>::value_type(tag_ARMOR_SECURITYUNIFORM,  1),
	map<string, int>::value_type(tag_ARMOR_EXPENSIVEDRESS,  1),
	map<string, int>::value_type(tag_ARMOR_CHEAPDRESS,  1),
}
	),
};
map<short, map<string, int> > siteDisguisesRestricted = {

	map<SiteTypes, map<string, int> >::value_type(SITE_INDUSTRY_NUCLEAR,{
	map<string, int>::value_type(tag_ARMOR_LABCOAT,  1),
			map<string, int>::value_type(tag_ARMOR_SECURITYUNIFORM,  1),
			map<string, int>::value_type(tag_ARMOR_CIVILLIANARMOR,  1),
			map<string, int>::value_type(tag_ARMOR_HARDHAT,  1),

}
),
map<SiteTypes, map<string, int> >::value_type(SITE_MEDIA_AMRADIO,{
	map<string, int>::value_type(tag_ARMOR_SECURITYUNIFORM,  1),
			map<string, int>::value_type(tag_ARMOR_EXPENSIVESUIT,  1),
			map<string, int>::value_type(tag_ARMOR_CHEAPSUIT,  1),
			map<string, int>::value_type(tag_ARMOR_EXPENSIVEDRESS,  1),
			map<string, int>::value_type(tag_ARMOR_CHEAPDRESS,  1),

}
	),
map<SiteTypes, map<string, int> >::value_type(SITE_MEDIA_CABLENEWS,{
	map<string, int>::value_type(tag_ARMOR_SECURITYUNIFORM,  1),
			map<string, int>::value_type(tag_ARMOR_EXPENSIVESUIT,  1),
			map<string, int>::value_type(tag_ARMOR_EXPENSIVEDRESS,  1),

}
),

map<SiteTypes, map<string, int> >::value_type(SITE_GOVERNMENT_WHITE_HOUSE,{
	map<string, int>::value_type(tag_ARMOR_BLACKSUIT,  1),
			map<string, int>::value_type(tag_ARMOR_BLACKDRESS,  1),
			map<string, int>::value_type(tag_ARMOR_CHEAPSUIT,  1),
			map<string, int>::value_type(tag_ARMOR_CHEAPDRESS,  1),
			map<string, int>::value_type(tag_ARMOR_EXPENSIVESUIT,  1),
			map<string, int>::value_type(tag_ARMOR_EXPENSIVEDRESS,  1),
			map<string, int>::value_type(tag_ARMOR_MILITARY,  1),
			map<string, int>::value_type(tag_ARMOR_ARMYARMOR,  1),
			map<string, int>::value_type(tag_ARMOR_SEALSUIT,  1),

}
),
map<SiteTypes, map<string, int> >::value_type(SITE_GOVERNMENT_ARMYBASE,{
	map<string, int>::value_type(tag_ARMOR_MILITARY,  1),
			map<string, int>::value_type(tag_ARMOR_ARMYARMOR,  1),
			map<string, int>::value_type(tag_ARMOR_SEALSUIT,  1),

}
),
map<SiteTypes, map<string, int> >::value_type(SITE_GOVERNMENT_INTELLIGENCEHQ,{
	map<string, int>::value_type(tag_ARMOR_BLACKSUIT,  1),
			map<string, int>::value_type(tag_ARMOR_BLACKDRESS,  1),

}
),

};

void printShoutsForHelp(const string ename, const int ealign);
bool isPrisoner(const string tkname);
void printAlienation(const short sitealienate);
void printFadesAway(const string aname, const int partysize);
void printBlewStealthCheck(const string aname);
void printActsNatural(const string aname, const int partysize);
void printEnemyNameInAlarm(const string nname);
void printLooksAtSquadSuspiciously();
void printShoutsInAlarm();
void printConservativeRaisesAlarm(const bool weapon, const int ntype, const int nalign);
void pressAnyKey();
#endif	//STEALTH_CPP
#ifdef	STRINGCONVERSION_CPP
// stringconversion.cpp

#include "../creature/creatureEnums.h"

extern map<string, short> getCreatureEnumFromString;

const string NONE = "NONE";
const string tag_heavyweapons = "heavyweapons";
const string tag_dodge = "dodge";
const string tag_firstaid = "firstaid";
const string tag_seduction = "seduction";
const string tag_streetsense = "streetsense";
const string tag_teaching = "teaching";
const string tag_stealth = "stealth";
const string tag_business = "business";
const string tag_science = "science";
const string tag_religion = "religion";
const string tag_art = "art";
const string tag_music = "music";
const string tag_writing = "writing";
const string tag_driving = "driving";
const string tag_tailoring = "tailoring";
const string tag_computers = "computers";
const string tag_disguise = "disguise";
const string tag_security = "security";
const string tag_law = "law";
const string tag_psychology = "psychology";
const string tag_persuasion = "persuasion";
const string tag_shotgun = "shotgun";
const string tag_smg = "smg";
const string tag_rifle = "rifle";
const string tag_pistol = "pistol";
const string tag_throwing = "throwing";
const string tag_axe = "axe";
const string tag_club = "club";
const string tag_sword = "sword";
const string tag_knife = "knife";
const string tag_handtohand = "handtohand";
const string tag_CLEAN = "CLEAN";
const string tag_NASTY = "NASTY";
const string tag_RANDOM = "RANDOM";
const string tag_FEMALE_BIAS = "FEMALE BIAS";
const string tag_FEMALE = "FEMALE";
const string tag_MALE_BIAS = "MALE BIAS";
const string tag_MALE = "MALE";
const string tag_GENDER_WHITEMALEPATRIARCH = "GENDER_WHITEMALEPATRIARCH";
const string tag_NEUTRAL = "NEUTRAL";
const string tag_heart = "heart";
const string tag_charisma = "charisma";
const string tag_health = "health";
const string tag_agility = "agility";
const string tag_wisdom = "wisdom";
const string tag_intelligence = "intelligence";
const string tag_strength = "strength";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string tag_no = "no";
const string tag_false = "false";
const string tag_0 = "0";
const string tag_off = "off";
const string tag_on = "on";
const string tag_yes = "yes";
const string tag_1 = "1";
const string tag_true = "true";

#endif	//STRINGCONVERSION_CPP
#ifdef	TALK_CPP
// talk.cpp

#include "../sitemode/sitedisplay.h"
#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
// for renting
#include "../items/money.h"
//#include "../log/log.h"
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
// for void basesquad(squadst *st,long loc);

#include "../combat/fight.h"
	// for void delenc(short e,char loot);
	//void delenc(Creature &tk);
	//void delenc(const int e, const int i);
#include "../combat/fightCreature.h"  
//for void capturecreature(Creature &t);
#include "../locations/locationsPool.h"
void moveEverythingAwayFromSite(int cursite);
#include "../customMaps.h"

/*
daily.cpp
*/
/* active squad visits the arms dealer */
void armsdealer(int loc);

// #include "../combat/fight.h"
// for void delenc(short e,char loot);
void delenc(DeprecatedCreature &tk);
// #include "../locations/locationsPool.h"
void moveEverythingAwayFromSite(int cursite);
void heyMisterDog(DeprecatedCreature &tk);
void heyMisterMonster(DeprecatedCreature &tk);
void talkInCombat(DeprecatedCreature &a, DeprecatedCreature &tk);
char talkToBankTeller(DeprecatedCreature &a, DeprecatedCreature &tk);
char talkToGeneric(DeprecatedCreature &a, DeprecatedCreature &tk);
void wannaHearSomethingDisturbing(DeprecatedCreature &a, DeprecatedCreature &tk);
void talkAboutIssues(DeprecatedCreature &a, DeprecatedCreature &tk);
void doYouComeHereOften(DeprecatedCreature &a, DeprecatedCreature &tk);
void heyINeedAGun(DeprecatedCreature &a, DeprecatedCreature &tk);
void heyIWantToRentARoom(DeprecatedCreature &a, DeprecatedCreature &tk);
void heyIWantToCancelMyRoom(DeprecatedCreature &a, DeprecatedCreature &tk);
bool isThereASiteAlarm();
void setSiteAlarmOne();
void setEncounterZeroExistsFalse();
void giveActiveSquadThisLoot(Item* de);
void locationIsNowRented(int l, int rent);
void basesquad(Deprecatedsquadst *st, long loc);
int getCity(int l);
void newDate(DeprecatedCreature &a, DeprecatedCreature &tk);
void newRecruit(DeprecatedCreature *cr, int c);
vector<NameAndAlignment> getEncounterNameAndAlignment();
int encounterWisdomRoll(const int e);
int getDifficultyBasedOnEncounterWisdom(const int e);
bool isPrisoner(const string tkname);
short getCurrentSite();

extern bool multipleCityMode;
extern char ccs_kills;
extern char newscherrybusted;
extern class Ledger ledger;
extern coordinatest loc_coord;
extern DeprecatedCreature encounter[ENCMAX];
extern Deprecatednewsstoryst *sitestory;
extern Deprecatedsquadst *activesquad;
extern int sitecrime;
extern short attitude[VIEWNUM];
extern short exec[EXECNUM];
extern short fieldskillrate;
extern short lawList[LAWNUM];
extern short sitealarmtimer;
extern short sitealienate;
extern short siteonfire;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];
extern string slogan_str;


vector<vector<string> > no_free_speech_flirt;
vector<vector<string> > pickupLines;
vector<vector<string> > lovingly_talk_to_mutant;
vector<vector<string> > normal_talk_to_mutant;
vector<vector<string> > lovingly_talk_to_dog;
vector<vector<string> > normal_talk_to_dog;

const int PICKUP_LINE_SIZE = 5;
const int DOUBLE_LINE = 2;

const string tag_ARMOR = "ARMOR";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string tag_ARMOR_MITHRIL = "ARMOR_MITHRIL";

const string tag_ARMOR_DEATHSQUADUNIFORM = "ARMOR_DEATHSQUADUNIFORM";
const string tag_ARMOR_LABCOAT = "ARMOR_LABCOAT";
const string tag_ARMOR_BUNKERGEAR = "ARMOR_BUNKERGEAR";
const string tag_ARMOR_SWATARMOR = "ARMOR_SWATARMOR";
const string tag_ARMOR_POLICEUNIFORM = "ARMOR_POLICEUNIFORM";
const string tag_ARMOR_POLICEARMOR = "ARMOR_POLICEARMOR";


map<int, vector<SiteTypes> > okaySiteList = {
	map<int, vector<SiteTypes> >::value_type(CREATURE_BOUNCER,
		{
			SITE_BUSINESS_CIGARBAR,
		}
		),
	map<int, vector<SiteTypes> >::value_type(CREATURE_POLITICIAN,
		{
			SITE_GOVERNMENT_WHITE_HOUSE,
		}
		),
	map<int, vector<SiteTypes> >::value_type(CREATURE_CORPORATE_CEO,
		{
			SITE_CORPORATE_HEADQUARTERS,
		}
		),
	map<int, vector<SiteTypes> >::value_type(CREATURE_SECURITYGUARD,
		{
			SITE_RESIDENTIAL_APARTMENT_UPSCALE,
			SITE_LABORATORY_COSMETICS,
			SITE_LABORATORY_GENETIC,
			SITE_GOVERNMENT_COURTHOUSE,
			SITE_GOVERNMENT_INTELLIGENCEHQ,
			SITE_INDUSTRY_SWEATSHOP,
			SITE_INDUSTRY_POLLUTER,
			SITE_INDUSTRY_NUCLEAR,
			SITE_CORPORATE_HEADQUARTERS,
			SITE_CORPORATE_HOUSE,
			SITE_MEDIA_AMRADIO,
			SITE_MEDIA_CABLENEWS,
			SITE_BUSINESS_CIGARBAR,
			SITE_BUSINESS_BANK,
		}
		),
	map<int, vector<SiteTypes> >::value_type(CREATURE_BANK_MANAGER,
		{
			SITE_BUSINESS_BANK,
		}
		),
	map<int, vector<SiteTypes> >::value_type(CREATURE_BANK_TELLER,
		{
			SITE_BUSINESS_BANK,

		}
		),
	map<int, vector<SiteTypes> >::value_type(CREATURE_SCIENTIST_LABTECH,
		{
			SITE_LABORATORY_COSMETICS,
			SITE_LABORATORY_GENETIC,
			SITE_INDUSTRY_NUCLEAR,
		}
		),
	map<int, vector<SiteTypes> >::value_type(CREATURE_SCIENTIST_EMINENT,
		{
			SITE_LABORATORY_COSMETICS,
			SITE_LABORATORY_GENETIC,
			SITE_INDUSTRY_NUCLEAR,
		}
		),
	map<int, vector<SiteTypes> >::value_type(CREATURE_CORPORATE_MANAGER,
		{
			SITE_LABORATORY_COSMETICS,
			SITE_LABORATORY_GENETIC,
			SITE_INDUSTRY_SWEATSHOP,
			SITE_INDUSTRY_POLLUTER,
			SITE_INDUSTRY_NUCLEAR,
			SITE_CORPORATE_HEADQUARTERS,
			SITE_MEDIA_AMRADIO,
			SITE_MEDIA_CABLENEWS,
		}
		),
	map<int, vector<SiteTypes> >::value_type(CREATURE_WORKER_SERVANT,
		{
			SITE_CORPORATE_HOUSE,
		}
		),
	map<int, vector<SiteTypes> >::value_type(CREATURE_WORKER_JANITOR,
		{
			SITE_RESIDENTIAL_TENEMENT,
			SITE_RESIDENTIAL_APARTMENT,
			SITE_RESIDENTIAL_APARTMENT_UPSCALE,
			SITE_LABORATORY_COSMETICS,
			SITE_LABORATORY_GENETIC,
			SITE_HOSPITAL_CLINIC,
			SITE_HOSPITAL_UNIVERSITY,
			SITE_GOVERNMENT_POLICESTATION,
			SITE_GOVERNMENT_COURTHOUSE,
			SITE_GOVERNMENT_PRISON,
			SITE_GOVERNMENT_INTELLIGENCEHQ,
			SITE_INDUSTRY_POLLUTER,
			SITE_INDUSTRY_NUCLEAR,
			SITE_CORPORATE_HEADQUARTERS,
			SITE_MEDIA_AMRADIO,
			SITE_MEDIA_CABLENEWS,
			SITE_BUSINESS_PAWNSHOP,
			SITE_BUSINESS_CRACKHOUSE,
			SITE_BUSINESS_JUICEBAR,
			SITE_BUSINESS_CIGARBAR,
			SITE_BUSINESS_LATTESTAND,
			SITE_BUSINESS_VEGANCOOP,
			SITE_BUSINESS_INTERNETCAFE,
			SITE_BUSINESS_DEPTSTORE,
			SITE_BUSINESS_HALLOWEEN,
			SITE_GOVERNMENT_FIRESTATION,
		}
		),
	map<int, vector<SiteTypes> >::value_type(CREATURE_WORKER_SWEATSHOP,
		{
			SITE_INDUSTRY_SWEATSHOP,
		}
		),
	map<int, vector<SiteTypes> >::value_type(CREATURE_WORKER_FACTORY_NONUNION,
		{
			SITE_INDUSTRY_POLLUTER,
		}
		),
			map<int, vector<SiteTypes> >::value_type(CREATURE_WORKER_FACTORY_CHILD,
				{
					SITE_INDUSTRY_POLLUTER,
				}
				),
			map<int, vector<SiteTypes> >::value_type(CREATURE_WORKER_SECRETARY,
				{
					SITE_LABORATORY_COSMETICS,
					SITE_LABORATORY_GENETIC,
					SITE_HOSPITAL_CLINIC,
					SITE_HOSPITAL_UNIVERSITY,
					SITE_GOVERNMENT_POLICESTATION,
					SITE_GOVERNMENT_COURTHOUSE,
					SITE_GOVERNMENT_INTELLIGENCEHQ,
					SITE_INDUSTRY_POLLUTER,
					SITE_INDUSTRY_NUCLEAR,
					SITE_CORPORATE_HEADQUARTERS,
					SITE_CORPORATE_HOUSE,
					SITE_MEDIA_AMRADIO,
					SITE_MEDIA_CABLENEWS,
					SITE_GOVERNMENT_FIRESTATION,
					SITE_GOVERNMENT_WHITE_HOUSE,
				}
				),
			map<int, vector<SiteTypes> >::value_type(CREATURE_WORKER_FACTORY_UNION,
				{
					SITE_INDUSTRY_POLLUTER,
				}
				),
		map<int, vector<SiteTypes> >::value_type(CREATURE_LANDLORD,
			{
				SITE_RESIDENTIAL_TENEMENT,
				SITE_RESIDENTIAL_APARTMENT,
				SITE_RESIDENTIAL_APARTMENT_UPSCALE,
			}
			),
		map<int, vector<SiteTypes> >::value_type(CREATURE_TEENAGER,
			{
				SITE_RESIDENTIAL_TENEMENT,
				SITE_RESIDENTIAL_APARTMENT,
				SITE_RESIDENTIAL_APARTMENT_UPSCALE,
				SITE_RESIDENTIAL_SHELTER,
				SITE_CORPORATE_HOUSE,
			}
			),
			map<int, vector<SiteTypes> >::value_type(CREATURE_COP,
				{
					SITE_GOVERNMENT_POLICESTATION,
				}
				),
			map<int, vector<SiteTypes> >::value_type(CREATURE_DEATHSQUAD,
				{
					SITE_GOVERNMENT_POLICESTATION,
				}
				),
		map<int, vector<SiteTypes> >::value_type(CREATURE_FIREFIGHTER,
			{
				SITE_GOVERNMENT_FIRESTATION,
			}
			),
		map<int, vector<SiteTypes> >::value_type(CREATURE_GANGUNIT,
			{
				SITE_GOVERNMENT_POLICESTATION,
			}
			),
			map<int, vector<SiteTypes> >::value_type(CREATURE_SWAT,
				{
					SITE_GOVERNMENT_POLICESTATION,
				}
				),
			map<int, vector<SiteTypes> >::value_type(CREATURE_JUDGE_LIBERAL,
				{
					SITE_GOVERNMENT_COURTHOUSE,
				}
				),
			map<int, vector<SiteTypes> >::value_type(CREATURE_JUDGE_CONSERVATIVE,
				{
					SITE_GOVERNMENT_COURTHOUSE,
				}
				),
			map<int, vector<SiteTypes> >::value_type(CREATURE_SECRET_SERVICE,
				{
					SITE_GOVERNMENT_WHITE_HOUSE,
				}
				),
			map<int, vector<SiteTypes> >::value_type(CREATURE_AGENT,
				{
					SITE_GOVERNMENT_INTELLIGENCEHQ,
				}
				),
		map<int, vector<SiteTypes> >::value_type(CREATURE_RADIOPERSONALITY,
			{
				SITE_MEDIA_AMRADIO,
			}
			),
		map<int, vector<SiteTypes> >::value_type(CREATURE_NEWSANCHOR,
			{
				SITE_MEDIA_CABLENEWS,
			}
			),
				map<int, vector<SiteTypes> >::value_type(CREATURE_GENETIC,
					{
						SITE_LABORATORY_GENETIC,
					}
					),
				map<int, vector<SiteTypes> >::value_type(CREATURE_GUARDDOG,
					{
						SITE_GOVERNMENT_PRISON,
						SITE_GOVERNMENT_INTELLIGENCEHQ,
						SITE_CORPORATE_HOUSE,
						SITE_GOVERNMENT_ARMYBASE,
					}
					),
					map<int, vector<SiteTypes> >::value_type(CREATURE_PRISONER,
						{
							SITE_RESIDENTIAL_TENEMENT,
							SITE_RESIDENTIAL_SHELTER,
						}
						),
					map<int, vector<SiteTypes> >::value_type(CREATURE_JUROR,
						{
							SITE_RESIDENTIAL_APARTMENT,
							SITE_RESIDENTIAL_TENEMENT,
							SITE_RESIDENTIAL_SHELTER,
						}
						),
					map<int, vector<SiteTypes> >::value_type(CREATURE_LAWYER,
						{
							SITE_GOVERNMENT_COURTHOUSE,
							SITE_GOVERNMENT_WHITE_HOUSE,
						}
						),
				map<int, vector<SiteTypes> >::value_type(CREATURE_DOCTOR,
					{
						SITE_DOWNTOWN,
						SITE_UDISTRICT,
					}
					),
				map<int, vector<SiteTypes> >::value_type(CREATURE_PSYCHOLOGIST,
					{
						SITE_DOWNTOWN,
						SITE_UDISTRICT,
					}
					),
				map<int, vector<SiteTypes> >::value_type(CREATURE_NURSE,
					{
						SITE_DOWNTOWN,
						SITE_UDISTRICT,
						SITE_INDUSTRIAL,
					}
					),
					map<int, vector<SiteTypes> >::value_type(CREATURE_SEWERWORKER,
						{
							SITE_DOWNTOWN,
							SITE_UDISTRICT,
							SITE_INDUSTRIAL,
						}
						),
				map<int, vector<SiteTypes> >::value_type(CREATURE_COLLEGESTUDENT,
					{
						SITE_UDISTRICT,
					}
					),
				map<int, vector<SiteTypes> >::value_type(CREATURE_MUSICIAN,
					{
						SITE_DOWNTOWN,
						SITE_UDISTRICT,
						SITE_INDUSTRIAL,
					}
					),
				map<int, vector<SiteTypes> >::value_type(CREATURE_MATHEMATICIAN,
					{
						SITE_UDISTRICT,
					}
					),
				map<int, vector<SiteTypes> >::value_type(CREATURE_TEACHER,
					{
						SITE_DOWNTOWN,
						SITE_UDISTRICT,
						SITE_INDUSTRIAL,
					}
					),
					map<int, vector<SiteTypes> >::value_type(CREATURE_HSDROPOUT,
						{
							SITE_INDUSTRIAL,
						}
						),
					map<int, vector<SiteTypes> >::value_type(CREATURE_BUM,
						{
							SITE_DOWNTOWN,
							SITE_UDISTRICT,

							SITE_INDUSTRIAL,
							SITE_RESIDENTIAL_SHELTER,
						}
						),

				map<int, vector<SiteTypes> >::value_type(CREATURE_GANGMEMBER,
					{
						SITE_BUSINESS_CRACKHOUSE,
					}
					),
						map<int, vector<SiteTypes> >::value_type(CREATURE_CRACKHEAD,
							{
								SITE_BUSINESS_CRACKHOUSE,
							}
							),
						map<int, vector<SiteTypes> >::value_type(CREATURE_PRIEST,
							{
								SITE_DOWNTOWN,
								SITE_UDISTRICT,
								SITE_INDUSTRIAL,
							}
							),
							map<int, vector<SiteTypes> >::value_type(CREATURE_ENGINEER,
								{
									SITE_MEDIA_AMRADIO,
									SITE_MEDIA_CABLENEWS,
									SITE_INDUSTRY_NUCLEAR,
								}
								),
							map<int, vector<SiteTypes> >::value_type(CREATURE_FASTFOODWORKER,
								{
									SITE_DOWNTOWN,
									SITE_UDISTRICT,
									SITE_INDUSTRIAL,
								}
								),
							map<int, vector<SiteTypes> >::value_type(CREATURE_BAKER,
								{
									SITE_DOWNTOWN,
									SITE_UDISTRICT,
									SITE_INDUSTRIAL,
								}
								),
						map<int, vector<SiteTypes> >::value_type(CREATURE_BARISTA,
							{
								SITE_BUSINESS_LATTESTAND,
								SITE_BUSINESS_INTERNETCAFE,
							}
							),
						map<int, vector<SiteTypes> >::value_type(CREATURE_BARTENDER,
							{
								SITE_BUSINESS_CIGARBAR,
								SITE_DOWNTOWN,
								SITE_UDISTRICT,
								SITE_INDUSTRIAL,
							}
							),
						map<int, vector<SiteTypes> >::value_type(CREATURE_TELEMARKETER,
							{
								SITE_DOWNTOWN,
								SITE_UDISTRICT,
								SITE_INDUSTRIAL,
							}
							),
							map<int, vector<SiteTypes> >::value_type(CREATURE_CARSALESMAN,
								{
									SITE_BUSINESS_CARDEALERSHIP,
								}
								),
						map<int, vector<SiteTypes> >::value_type(CREATURE_OFFICEWORKER,
							{
								SITE_LABORATORY_COSMETICS,
								SITE_LABORATORY_GENETIC,
								SITE_HOSPITAL_CLINIC,
								SITE_HOSPITAL_UNIVERSITY,
								SITE_GOVERNMENT_COURTHOUSE,
								SITE_CORPORATE_HEADQUARTERS,
								SITE_MEDIA_AMRADIO,
								SITE_MEDIA_CABLENEWS,
								SITE_BUSINESS_DEPTSTORE,
								SITE_GOVERNMENT_WHITE_HOUSE,
							}
							),
					map<int, vector<SiteTypes> >::value_type(CREATURE_FOOTBALLCOACH,
						{
							SITE_UDISTRICT,
						}
						),
						map<int, vector<SiteTypes> >::value_type(CREATURE_PROSTITUTE,
							{
								SITE_DOWNTOWN,
								SITE_UDISTRICT,
								SITE_INDUSTRIAL,
							}
							),
						map<int, vector<SiteTypes> >::value_type(CREATURE_MAILMAN,
							{
								SITE_DOWNTOWN,
								SITE_UDISTRICT,
								SITE_INDUSTRIAL,
							}
							),
							map<int, vector<SiteTypes> >::value_type(CREATURE_GARBAGEMAN,
								{
									SITE_DOWNTOWN,
									SITE_UDISTRICT,
									SITE_INDUSTRIAL,
								}
								),
						map<int, vector<SiteTypes> >::value_type(CREATURE_PLUMBER,
							{
								SITE_DOWNTOWN,
								SITE_UDISTRICT,
								SITE_INDUSTRIAL,
							}
							),
								map<int, vector<SiteTypes> >::value_type(CREATURE_CHEF,
									{
										SITE_DOWNTOWN,
										SITE_UDISTRICT,
										SITE_INDUSTRIAL,
										SITE_BUSINESS_CIGARBAR,
									}
									),
									map<int, vector<SiteTypes> >::value_type(CREATURE_CONSTRUCTIONWORKER,
										{
											SITE_DOWNTOWN,
											SITE_UDISTRICT,
											SITE_INDUSTRIAL,
										}
										),
									map<int, vector<SiteTypes> >::value_type(CREATURE_AMATEURMAGICIAN,
										{
											SITE_DOWNTOWN,
											SITE_UDISTRICT,
											SITE_INDUSTRIAL,
										}
										),
									map<int, vector<SiteTypes> >::value_type(CREATURE_TANK,
										{
											SITE_GOVERNMENT_ARMYBASE,
										}
										),
							map<int, vector<SiteTypes> >::value_type(CREATURE_MERC,
								{
									SITE_CORPORATE_HEADQUARTERS,
									SITE_CORPORATE_HOUSE,
									SITE_INDUSTRY_NUCLEAR,
									SITE_LABORATORY_GENETIC,
									SITE_BUSINESS_BANK,
								}
								),
								map<int, vector<SiteTypes> >::value_type(CREATURE_HICK,
									{
										SITE_MEDIA_AMRADIO,
										SITE_MEDIA_CABLENEWS,
										SITE_OUTOFTOWN,
									}
									),
								map<int, vector<SiteTypes> >::value_type(CREATURE_VETERAN,
									{
										SITE_DOWNTOWN,
										SITE_UDISTRICT,
										SITE_INDUSTRIAL,
									}
									),
									map<int, vector<SiteTypes> >::value_type(CREATURE_HARDENED_VETERAN,
										{
											SITE_GOVERNMENT_ARMYBASE,
										}
										),
								map<int, vector<SiteTypes> >::value_type(CREATURE_SOLDIER,
									{
										SITE_GOVERNMENT_ARMYBASE,
									}
									),
								map<int, vector<SiteTypes> >::value_type(CREATURE_MILITARYPOLICE,
									{
										SITE_GOVERNMENT_ARMYBASE,
									}
									),
								map<int, vector<SiteTypes> >::value_type(CREATURE_MILITARYOFFICER,
									{
										SITE_GOVERNMENT_ARMYBASE,
									}
									),
							map<int, vector<SiteTypes> >::value_type(CREATURE_SEAL,
								{
									SITE_GOVERNMENT_ARMYBASE,
								}
								),
								map<int, vector<SiteTypes> >::value_type(CREATURE_EDUCATOR,
									{
										SITE_GOVERNMENT_PRISON,
									}
									),
								map<int, vector<SiteTypes> >::value_type(CREATURE_PRISONGUARD,
									{
										SITE_GOVERNMENT_PRISON,
									}
									),
								map<int, vector<SiteTypes> >::value_type(CREATURE_HIPPIE,
									{
										SITE_BUSINESS_VEGANCOOP,
									}
									),
									map<int, vector<SiteTypes> >::value_type(CREATURE_CRITIC_ART,
										{
											SITE_DOWNTOWN,
											SITE_UDISTRICT,
											SITE_INDUSTRIAL,
											SITE_MEDIA_CABLENEWS,
										}
										),
								map<int, vector<SiteTypes> >::value_type(CREATURE_CRITIC_MUSIC,

									{
										SITE_DOWNTOWN,
										SITE_UDISTRICT,
										SITE_INDUSTRIAL,
										SITE_MEDIA_AMRADIO,
									}
									),
										map<int, vector<SiteTypes> >::value_type(CREATURE_SOCIALITE,
											{
												SITE_DOWNTOWN,
												SITE_UDISTRICT,
												SITE_INDUSTRIAL,
											}
											),
											map<int, vector<SiteTypes> >::value_type(CREATURE_PROGRAMMER,
												{
													SITE_DOWNTOWN,
													SITE_UDISTRICT,
													SITE_INDUSTRIAL,
													SITE_GOVERNMENT_INTELLIGENCEHQ,
													SITE_CORPORATE_HEADQUARTERS,
												}
												),
											map<int, vector<SiteTypes> >::value_type(CREATURE_RETIREE,
												{
													SITE_DOWNTOWN,
													SITE_UDISTRICT,
													SITE_INDUSTRIAL,
												}
												),
									map<int, vector<SiteTypes> >::value_type(CREATURE_PAINTER,
										{
											SITE_DOWNTOWN,
											SITE_UDISTRICT,
											SITE_INDUSTRIAL,
										}
										),
										map<int, vector<SiteTypes> >::value_type(CREATURE_SCULPTOR,
											{
												SITE_DOWNTOWN,
												SITE_UDISTRICT,
												SITE_INDUSTRIAL,
											}
											),
										map<int, vector<SiteTypes> >::value_type(CREATURE_AUTHOR,
											{
												SITE_DOWNTOWN,
												SITE_UDISTRICT,
												SITE_INDUSTRIAL,
											}
											),
											map<int, vector<SiteTypes> >::value_type(CREATURE_JOURNALIST,
												{
													SITE_DOWNTOWN,
													SITE_UDISTRICT,
													SITE_INDUSTRIAL,
												}
												),
										map<int, vector<SiteTypes> >::value_type(CREATURE_DANCER,
											{
												SITE_DOWNTOWN,
												SITE_UDISTRICT,
												SITE_INDUSTRIAL,
											}
											),
									map<int, vector<SiteTypes> >::value_type(CREATURE_PHOTOGRAPHER,
										{
											SITE_MEDIA_CABLENEWS,
										}
										),
								map<int, vector<SiteTypes> >::value_type(CREATURE_CAMERAMAN,
									{
										SITE_MEDIA_CABLENEWS,
									}
									),
									map<int, vector<SiteTypes> >::value_type(CREATURE_HAIRSTYLIST,
										{
											SITE_DOWNTOWN,
											SITE_UDISTRICT,
											SITE_INDUSTRIAL,
										}
										),
										map<int, vector<SiteTypes> >::value_type(CREATURE_FASHIONDESIGNER,
											{
												SITE_DOWNTOWN,
												SITE_UDISTRICT,
												SITE_INDUSTRIAL,
											}
											),
										map<int, vector<SiteTypes> >::value_type(CREATURE_CLERK,
											{
												SITE_BUSINESS_JUICEBAR,
												SITE_BUSINESS_LATTESTAND,
												SITE_BUSINESS_INTERNETCAFE,
												SITE_BUSINESS_DEPTSTORE,
												SITE_BUSINESS_HALLOWEEN,
											}
											),
									map<int, vector<SiteTypes> >::value_type(CREATURE_THIEF,
										{
											SITE_DOWNTOWN,
											SITE_UDISTRICT,
											SITE_INDUSTRIAL,
										}
										),
										map<int, vector<SiteTypes> >::value_type(CREATURE_ACTOR,
											{
												SITE_DOWNTOWN,
												SITE_UDISTRICT,
												SITE_INDUSTRIAL,
											}
											),
												map<int, vector<SiteTypes> >::value_type(CREATURE_YOGAINSTRUCTOR,
													{
														SITE_BUSINESS_VEGANCOOP,
													}
													),
													map<int, vector<SiteTypes> >::value_type(CREATURE_MARTIALARTIST,
														{
															SITE_DOWNTOWN,
															SITE_UDISTRICT,
															SITE_INDUSTRIAL,
														}
														),
													map<int, vector<SiteTypes> >::value_type(CREATURE_ATHLETE,
														{
															SITE_UDISTRICT,
														}
														),
													map<int, vector<SiteTypes> >::value_type(CREATURE_BIKER,
														{
															SITE_DOWNTOWN,
															SITE_UDISTRICT,
															SITE_INDUSTRIAL,
														}
														),
											map<int, vector<SiteTypes> >::value_type(CREATURE_TRUCKER,
												{
													SITE_OUTOFTOWN,
												}
												),
												map<int, vector<SiteTypes> >::value_type(CREATURE_TAXIDRIVER,
													{
														SITE_DOWNTOWN,
														SITE_UDISTRICT,
														SITE_INDUSTRIAL,
													}
													),
												map<int, vector<SiteTypes> >::value_type(CREATURE_NUN,
													{
														SITE_DOWNTOWN,
														SITE_UDISTRICT,
														SITE_INDUSTRIAL,
													}
													),
													map<int, vector<SiteTypes> >::value_type(CREATURE_LOCKSMITH,
														{
															SITE_DOWNTOWN,
															SITE_UDISTRICT,
															SITE_INDUSTRIAL,
														}
														),
};
vector<NameAndAlignment> getEncounterNameAndAlignment();
vector<SiteTypes> defaultSiteList = {
	SITE_RESIDENTIAL_SHELTER
};
void delenc(const short e, const char loot);

void printTalkAboutIssuesHeader(const string aname);
void printTalkAboutIssuesWhenStupid(const int lw);
void printTalkAboutIssuesTooLiberal(const int lw);
void printTalkAboutIssuesNormal(const int lw, const int tkanimalgloss);
void printTurnsAway();
void printConservativeRespondsToStupid(const int tktype, const bool extraline);
void printRespondantName(const string tkname, const bool extraline);
void printConservativeCounter(const bool extraline, const int lw);
void printRejectTalk(const bool extraline);
void printMutantTalkAboutIssues(const string tkname, const int extraline);
void printThatIsDisturbing(const string tkname, const bool extraline, const int special_case);
void printUnableToSpeakAgree(const string tkname, const bool extraline);
void printAgreesToComeByLater(const string tkname, const bool extraline, const bool another_extraline);
void printSpecialRecruitment(const string aname, const string tkname, const string pitch, const string response);
void printTalkOptionsDuringCombat(const bool hostages, const bool is_cantbluff_two, const bool cop);
void printTalksToThem(const string aname, const int tkalign, const string tkname);

void liberalizeEncounterIfThisType(const int type);

void printTheSquadIsArrested();
void printTheEnemyIsFooled();
void printXeIsNotFooled(const string ename, const bool noFreeSpeech);
void printITalkLikeAConservative(const string aname);
void printEngraveElbereth(const string aname);
void printDeathSquadBluff();
void printLabCoatBluff();
void printPoliceBluff();
void printBunkerGearBluff(const short onfire);
void printWeWerentBornYesterday(const string ename);
void printSiegeBluff(const string aname, const int siegeType);
void printEnemyIgnoresThreat(const string tkname);
void printHowShouldWeRespond(const string aname, const int hostages);
void printPloyWorksEnemyBacksOff();
void printExecutionGunshot();
void printExecutionBareHands();
void printDiscardsBody(const string aname, const string pname);
void printAnotherOneBacksOff(const string ename);
void printThreatenEnemy(const string aname);
void printHostageNegotiation(const string ename, const int etype, const int ealign, const int hostages);
void printThreatenHostages(const string aname);
void printReleaseHostagesHeader(const string ename);
void printReleaseHostagesFooter(const int hostages);
void printEnemyAllowsHostagesToDie(const string ename);
void printLetUsGoAndTheyGoFree(const string aname, const int hostages);
void printEnemyWatchesHostageDeath(const string ename);
void printAcceptsPickupLine(const string aname, const string tkname, const vector<string> selected_flirt);
void printRejectsPickupLine(const string tkname, const int tktype, const int agender_liberal, const vector<string> selected_flirt);
void printSaysWhat(const string tkname);
void printTurnsAway(const string tkname, const int tkalign);
void printRejectPolicePickupLine(const string tkname, const bool extraline);
void printPickupLine(const string aname, const vector<string> selected_flirt);
void printNonHumanRejection(const string tkname, const int tktype, const bool extraline);
void printAnimalDoesntUnderstand(const string tkname, const int tktype);
void printWannaHearSomething(const string aname);
void printLetMeSellYouAGun(const string tkname);
void printNotHereDummy(const string tkname);
void printWaitUntilItCoolsDown(const string tkname);
void printIDontSellToCops(const string tkname);
void printIDontSellToNaked(const string tkname);
void printINeedAGun(const string aname);
void printJesusItsYours(const string tkname);
void printIWantYouToLeave(const string tkname);
void printGiveMeTheLCSPrice(const string aname);
void printThreatensWithAGun(const string aname, const string aweapon);
void printRefuseRentDeal(const string aname);
void printNotMyProblem(const string tkname);
void printAcceptRentHeader(const string aname);
void printAcceptRentFooter(const string tkname);
void printRentingOptions(const bool cannotAfford);
void printINeedThisMuchRent(const string tkname, const int rent);
void printPutSomeDamnClothesOn(const string tkname);
void printIWantToRent(const string aname);
void printClearOutYourRoom(const string tkname);
void printYourPossessionsAreRelocated();
void printIWantToCancelRent(const string aname);
void printTalkToPotentialLandlord(const bool is_naked);
void printTalkToLandlord(const bool is_naked);
void printTalkToGangMemberOrMerc(const bool is_naked);
void printTalkToBankTeller(const bool is_naked);
void printTalkToHeader(const string aname);
void printTalkToMiddle(const int tkalign, const string tkname, const string tkbio);
void printTalkToFooter(const bool is_naked, const bool can_date);
void printBankerCooperates();
void printTheVaultIsOpen();
void printGuardsCloseIn();
void printDemandVaultBeOpened(const string aname);
void printBrandishWeapon(const string aname, const string aweapon);
void printTellerComplies();
void printTellerAlertsCops();
void printIRobTheBank(const string aname);
void printOptionsWithinBank(const bool is_naked);
void pressAnyKey();
int getkeyAlt();
int pressSpecificKey(const int x, const int y);
int pressSpecificKey(const int x, const int y, const int z);
#endif	// TALK_CPP
#ifdef	TITLESCREEN_CPP
// titlescreen.cpp
#include "../common/commondisplay.h"

#include "../title/titlescreen.h"
void mode_base();
#include "../common/getnames.h"
// for enter_name
#include "../title/highscore.h"
//for void viewhighscores
#include "../title/newgame.h"
//for void setup_newgame();
//#include "../title/saveload.h"
bool file_exists(const std::string& filename);
char load(const string& filename);
void savegame(const string& filename);
string title_screen::savefile_name;
vector<string> title_screen::s_savefiles;
#include "../cursesAlternativeConstants.h"
#include "../creature/creatureEnums.h"
#include "../customMaps.h"
#include "../common/musicClass.h"
/* end the game and clean up */
void end_game(int err = EXIT_SUCCESS);
void automatedDataTests();
extern short mode;
extern MusicClass music;
void printSaveHeader(const bool to_delete);
void printSaveList(const int page, const vector<string> s_savefiles);
void printSaveFooter(const bool to_delete);
void printAreYouSure(const string s_savefiles);
void printMusicFooter(const bool musicEnabled);

void printTitleScreen();
string printNewGameHeader();
void pressAnyKey();
int getkeyAlt();
bool is_page_up(const int c);
bool is_page_down(const int c);
#endif	//TITLESCREEN_CPP
#ifdef	VEHICLE_CPP
// vehicle.cpp

const string vehicleSportsCar = "SPORTSCAR";
const string CONST_STOLEN = "Stolen ";

const string tag_id = "id";
const string tag_myear = "myear";
const string tag_location = "location";
const string tag_color = "color";
const string tag_vtypeid = "vtypeid";
const string tag_vtypeidname = "vtypeidname";
const string tag_vehicle = "vehicle";

#endif	//VEHICLE_CPP
#ifdef	VEHICLETYPE_CPP
//vehicletype.cpp

#include "../creature/creatureEnums.h"
#include "vehicletype.h"
#include "../common/stringconversion.h"
extern int year;
const string CONST_STEALING = "::stealing: ";
const string CONST_COLORS = "::colors: ";
const string CONST_UNDEF = "UNDEF";
const string CONST_UNKNOWN_ELEMENT_FOR_VEHICLE_TYPE = "Unknown element for vehicle type ";
const string CONST_AVAILABLE_AT_DEALERSHIP = "::available_at_dealership: ";
const string CONST_INVALID_BOOLEAN_VALUE_FOR_VEHICLE_TYPE = "Invalid boolean value for vehicle type ";
const string CONST_COLORS_DISPLAY_COLOR = "::colors::display_color: ";
const string CONST_YEAR_ADD_RANDOM_UP_TO_CURRENT_YEAR = "::year::add_random_up_to_current_year: ";
const string CONST_YEAR_START_AT_CURRENT_YEAR = "::year::start_at_current_year: ";
const string CONST_LACKS_IDNAME = "LACKS IDNAME ";
const string CONST_UNDEFINED = "UNDEFINED";

const string tag_window = "window";
const string tag_body = "body";
const string tag_Translucent = "Translucent";
const string tag_sleeperprice = "sleeperprice";
const string tag_price = "price";
const string tag_available_at_dealership = "available_at_dealership";
const string tag_armor = "armor";
const string tag_armor_midpoint = "armor_midpoint";
const string tag_high_armor_max = "high_armor_max";
const string tag_high_armor_min = "high_armor_min";
const string tag_low_armor_max = "low_armor_max";
const string tag_low_armor_min = "low_armor_min";
const string tag_touch_alarm_chance = "touch_alarm_chance";
const string tag_sense_alarm_chance = "sense_alarm_chance";
const string tag_extra_heat = "extra_heat";
const string tag_juice = "juice";
const string tag_difficulty = "difficulty";
const string tag_difficulty_to_find = "difficulty_to_find";
const string tag_stealing = "stealing";
const string tag_shortname = "shortname";
const string tag_longname = "longname";
const string tag_passenger = "passenger";
const string tag_driver = "driver";
const string tag_attackbonus = "attackbonus";
const string tag_attack = "attack";
const string tag_hardlimit = "hardlimit";
const string tag_softlimit = "softlimit";
const string tag_skillfactor = "skillfactor";
const string tag_skill = "skill";
const string tag_base = "base";
const string tag_dodgebonus = "dodgebonus";
const string tag_dodge = "dodge";
const string tag_drivebonus = "drivebonus";
const string tag_display_color = "display_color";
const string tag_color = "color";
const string tag_colors = "colors";
const string tag_add = "add";
const string tag_add_random = "add_random";
const string tag_add_random_up_to_current_year = "add_random_up_to_current_year";
const string tag_start_at_year = "start_at_year";
const string tag_start_at_current_year = "start_at_current_year";
const string tag_year = "year";
const string tag_idname = "idname";
const string tag_id = "id";

#endif	//VEHICLETYPE_CPP
#ifdef	WEAPON_CPP
// weapon.cpp

#include "../creature/creatureEnums.h"
#include "../items/itemtype.h"
#include "../items/item.h"
#include "../items/cliptype.h"
#include "../items/clip.h"
#include "../items/weapontype.h"
#include "../items/weapon.h"

#include "../common/translateid.h"
// for getweapontype

extern vector<WeaponType *> weapontype;

const string CONST_CLOSE_PARENTHESIS = ")";
const string CONST_SPACE_OPEN_PARENTHESIS = " (";

const string tag_ammo = "ammo";
const string tag_loaded_cliptype = "loaded_cliptype";
const string tag_weapon = "weapon";

#endif	//WEAPON_CPP
#ifdef	WEAPONTYPE_CPP
// weapontype.cpp
#include "../creature/creatureEnums.h"
#include "../items/itemtype.h"
#include "../items/cliptype.h"
#include "../items/weapontype.h"

#include "../common/stringconversion.h"

extern int year;
extern short lawList[LAWNUM];

const string CONST_tag_striking = "striking";
const string CONST_UNDEF = "UNDEF";
const string CONST_ASSAULTS = "assaults";

const string tag_chance_causes_debris = "chance_causes_debris";
const string tag_chance = "chance";
const string tag_fire = "fire";
const string tag_severtype = "severtype";
const string tag_fixed_damage = "fixed_damage";
const string tag_random_damage = "random_damage";
const string tag_hits_required = "hits_required";
const string tag_critical = "critical";
const string tag_no = "no";
const string tag_no_DR_for_limbs_chance = "no_damage_reduction_for_limbs_chance";
const string tag_armor = "armor";
const string tag_armorpiercing = "armorpiercing";
const string tag_damages_armor = "damages_armor";
const string tag_bleeding = "bleeding";
const string tag_shoots = "shoots";
const string tag_burns = "burns";
const string tag_cuts = "cuts";
const string tag_tears = "tears";
const string tag_bruises = "bruises";
const string tag_strength = "strength";
const string tag_strength_max = "strength_max";
const string tag_strength_min = "strength_min";
const string tag_successive_attacks_difficulty = "successive_attacks_difficulty";
const string tag_number_attacks = "number_attacks";
const string tag_accuracy_bonus = "accuracy_bonus";
const string tag_skill = "skill";
const string tag_hit_punctuation = "hit_punctuation";
const string tag_always_describe_hit = "always_describe_hit";
const string tag_hit_description = "hit_description";
const string tag_attack = "attack";
const string tag_attack_description = "attack_description";
const string tag_ammotype = "ammotype";
const string tag_ammo = "ammo";
const string tag_can_backstab = "can_backstab";
const string tag_thrown = "thrown";
const string tag_ranged = "ranged";
const string tag_priority = "priority";
const string tag_size = "size";
const string tag_suspicious = "suspicious";
const string tag_auto_break_locks = "auto_break_locks";
const string tag_bashstrengthmod = "bashstrengthmod";
const string tag_legality = "legality";
const string tag_graffiti = "graffiti";
const string tag_instrument = "instrument";
const string tag_music = "music";
const string tag_musical_attack = "musical_attack";
const string tag_protects_against_kidnapping = "protects_against_kidnapping";
const string tag_can_threaten_hostages = "can_threaten_hostages";
const string tag_threatening = "threatening";
const string tag_can_take_hostages = "can_take_hostages";
const string tag_shortname_future = "shortname_future";
const string tag_shortname = "shortname";
const string tag_shortname_future_sub_2 = "shortname_future_sub_2";
const string tag_shortname_future_sub_1 = "shortname_future_sub_1";
const string tag_shortname_sub_2 = "shortname_sub_2";
const string tag_shortname_sub_1 = "shortname_sub_1";
const string tag_name_future = "name_future";
const string tag_name = "name";
const string tag_name_future_sub_2 = "name_future_sub_2";
const string tag_name_future_sub_1 = "name_future_sub_1";
const string tag_name_sub_2 = "name_sub_2";
const string tag_name_sub_1 = "name_sub_1";
#endif	//WEAPONTYPE_CPP
#endif // INCLUDES_H_INCLUDED