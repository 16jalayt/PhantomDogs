#pragma once

#include <string>

#include "Button.h"
#include "Movie.h"
#include "SDL_ptr.h"
#include "sprite.h"

//CurrentScene is static.
//Use to reference class functions.

class Scene
{
public:
	~Scene();
	Scene();
	void SetHeader(std::string name, std::string sceneFile);
	Sprite_ptr bk;
	//BinkPlayback_ptr bkFMV;
	SDL_Texture_ptr bkFMV;
	std::vector<Sprite_ptr> ovls;
	std::vector<Button_ptr> hots;
	std::vector<Movie_ptr> fmvs;
	std::string sceneFile;
	std::string sceneName;

	void Draw();
	void Run();
	void EventProc(SDL_Event event);
	void setBkg(std::string fileName);
	void AddSprite(Sprite_ptr sprite);
	void AddHotzone(Button_ptr hot);
	void AddMovie(Movie_ptr fmv);
	void AddMusic(std::string sound, int channel, int loop, int chan1, int chan2);
	void AddSound(std::string sound, int channel, int loop, int chan1, int chan2);
	static void AddSound(std::string sound, int channel, int loop, int chan1, int chan2, int scene);
	static void AddSound(std::string sound, int channel, int loop, int chan1, int chan2, std::string scene);

protected:
};
using Scene_ptr = std::shared_ptr<Scene>;

extern Scene_ptr currentScene;
extern Scene_ptr nextScene;
extern bool sceneChangeFlag;
extern bool sceneReloadFlag;
extern std::string sceneChangeName;
extern std::string prevScene;
//extern int sceneNum;
extern bool flags[];
const std::string flagDesc[576] = { "EV_Generic0", "EV_Generic1", "EV_Generic2", "EV_Generic3", "EV_Generic4", "EV_Generic5", "EV_Generic6", "EV_Generic7", "EV_Generic8", "EV_Generic9", "EV_Generic10", "EV_Generic11", "EV_Generic12", "EV_Generic13", "EV_Generic14", "EV_Generic15", "EV_Generic16", "EV_Generic17", "EV_Generic18", "EV_Generic19", "EV_Generic20", "EV_Generic21", "EV_Generic22", "EV_Generic23", "EV_Generic24", "EV_Generic25", "EV_Generic26", "EV_Generic27", "EV_Generic28", "EV_Generic29", "EV_Generic30", "EV_TimeForEndgame", "EV_PlayerWonGame", "EV_StopPlayerScrolling", "EV_Easter_Eggs", "EV_Bail_Level01", "EV_Bail_Level02", "EV_Bail_Level03", "EV_BG_Said_Attack", "EV_BG_Said_Creepy", "EV_BG_Said_Emily_Motive", "EV_BG_Said_Fight", "EV_BG_Said_Found_Map", "EV_BG_Said_Fresh", "EV_BG_Said_Get_Tested", "EV_BG_Said_Getting_Tested", "EV_BG_Said_Gold_Motive", "EV_BG_Said_Got_Results", "EV_BG_Said_Got_Tested", "EV_BG_Said_Graves", "EV_BG_Said_Hardy", "EV_BG_Said_Hole_Heist", "EV_BG_Said_JA_Has_Motive", "EV_BG_Said_Message", "EV_BG_Said_No_Red", "EV_BG_Said_Paintings_Clue", "EV_BG_Said_Paper", "EV_BG_Said_Poison", "EV_BG_Said_Prints", "EV_BG_Said_Ranger", "EV_BG_Said_Red_Fanatic", "EV_BG_Said_Red_Grump", "EV_BG_Said_Scare_Sally", "EV_BG_Said_Used_To", "EV_BG_Said_Vampire", "EV_BG_Said_Wolves", "EV_Bird_Flies", "EV_Broke_Toolbox", "EV_Bucket_Full", "EV_Clock01", "EV_Clock02", "EV_Clock03", "EV_Clock04", "EV_Clock05", "EV_Clock06", "EV_Clock07", "EV_Clock08", "EV_Clock09", "EV_Clock10", "EV_Clock11", "EV_Clock12", "EV_Day", "EV_Day_Needed", "EV_Dog_Unstuck", "EV_DogI_Pos01", "EV_DogI_Pos02", "EV_DogI_Pos03", "EV_DogI_Pos04", "EV_DogL_Pos01", "EV_DogL_Pos02", "EV_DogL_Pos03", "EV_DogL_Pos04", "EV_DogV_Pos01", "EV_DogV_Pos02", "EV_DogV_Pos03", "EV_DogV_Pos04", "EV_DogX_Pos01", "EV_DogX_Pos02", "EV_DogX_Pos03", "EV_DogX_Pos04", "EV_Drain_Grate_Open", "EV_Drain_Open", "EV_EG_Said_Barter", "EV_EG_Said_Camos", "EV_EG_Said_Daddy_Joe", "EV_EG_Said_Dogs_Back", "EV_EG_Said_Drummer", "EV_EG_Said_Good_Job", "EV_EG_Said_Howl", "EV_EG_Said_Jeff_Motive", "EV_EG_Said_Last_Time", "EV_EG_Said_Newspaper", "EV_EG_Said_No_Gold", "EV_EG_Said_No_Waldo", "EV_EG_Said_Pasta", "EV_EG_Said_Pin", "EV_EG_Said_Player", "EV_EG_Said_Prints", "EV_EG_Said_Red", "EV_EG_Said_Sandpaper", "EV_EG_Said_Squeaky", "EV_EG_Said_Stack", "EV_EG_Said_Test", "EV_EG_Said_Tucker", "EV_EG_Said_Viv_Picture", "EV_EG_Said_Wells", "EV_Emily_Chase01", "EV_Emily_Chase02", "EV_Emily_Chase03", "EV_Emily_Chase04", "EV_Emily_Chase05", "EV_Emily_Chase06", "EV_Emily_Chase07", "EV_Emily_Chase08", "EV_Emily_Chase09", "EV_Emily_Chase10", "EV_Emily_Chase11", "EV_Emily_Chase12", "EV_Emily_Chase13", "EV_Emily_Chase14", "EV_Emily_Chase15", "EV_Emily_Chase16", "EV_Emily_Chase17", "EV_Emily_Chase18", "EV_Emily_Chase19", "EV_Emily_Chase20", "EV_Fixed_Flashlight", "EV_FJ_Said_Easy", "EV_FJ_Said_Fortune", "EV_FJ_Said_Grandfather", "EV_FJ_Said_Habit", "EV_FJ_Said_Inscriptions", "EV_FJ_Said_Inside_Out", "EV_FJ_Said_Motive", "EV_FJ_Said_No_Running", "EV_FJ_Said_No_See_Speakeasy", "EV_FJ_Said_Nothing", "EV_FJ_Said_Rain", "EV_FJ_Said_Ranger", "EV_FJ_Said_Sandwich", "EV_FJ_Said_Smart_Perp", "EV_Gave_Sample", "EV_Gold_Grate_Open", "EV_Heard_Bird1", "EV_Heard_Bird2", "EV_Heard_Bird3", "EV_Heard_Bird4", "EV_Heard_Bird5", "EV_Heard_Bird6", "EV_Heard_Squeaking", "EV_Intake_Closed", "EV_JA_Said_Apology", "EV_JA_Said_Busy", "EV_JA_Said_Care", "EV_JA_Said_Cemetery", "EV_JA_Said_Denies", "EV_JA_Said_Diet", "EV_JA_Said_Dog_Prob", "EV_JA_Said_Dog_Run", "EV_JA_Said_Dogs_Trained", "EV_JA_Said_Emily_Motive", "EV_JA_Said_Gang_Gone", "EV_JA_Said_Gold_Rumor", "EV_JA_Said_Grandfather", "EV_JA_Said_Just_Dogs", "EV_JA_Said_Kit", "EV_JA_Said_Lie", "EV_JA_Said_Litter", "EV_JA_Said_Motive", "EV_JA_Said_Museum", "EV_JA_Said_Mystery", "EV_JA_Said_Newspaper", "EV_JA_Said_No_Gold", "EV_JA_Said_No_Waldo", "EV_JA_Said_Not", "EV_JA_Said_Please", "EV_JA_Said_PO", "EV_JA_Said_Red_Motive", "EV_JA_Said_Results", "EV_JA_Said_Sample", "EV_JA_Said_Son", "EV_JA_Said_Speakeasy_Sealed", "EV_JA_Said_Thanks", "EV_JA_Said_Tourists", "EV_JA_Said_Viv_Picture", "EV_JA_Said_WA_Grandfather", "EV_JA_Said_When_Arrested", "EV_JA_Said_Will_Do", "EV_JA_Said_Yogi", "EV_JA_Said_Yogi_Innocent", "EV_Jeff_Discovers_Vivian", "EV_Left_Msg01", "EV_Mailed_Letter", "EV_Map_Marked_L", "EV_Map_Marked_V", "EV_Map_Marked_X", "EV_Met_BG", "EV_Met_EG_Shop", "EV_Met_Eustacia", "EV_Met_FJ", "EV_Met_JA", "EV_Met_RKB", "EV_Met_RKF", "EV_Met_Sally", "EV_Met_Vivian", "EV_Missed_Bait01", "EV_Missed_Bait02", "EV_Missed_Bait03", "EV_Missed_Bait04", "EV_Missed_Bait05", "EV_Missed_Bait06", "EV_Missed_Cardinal", "EV_Missed_Goldfinch", "EV_Missed_Jay", "EV_Missed_Robin", "EV_Missed_Tanager", "EV_Night", "EV_Night_Needed", "EV_Placed_Bucket", "EV_Placed_Screw_As_Peg", "EV_Placed_Wheel", "EV_Placed_Wheel_Drain", "EV_Placed_Wheel_Gold", "EV_Red_Said_Ran_Out", "EV_Red_Said_Test", "EV_Red_Said_Thanks", "EV_Red_Took_Spark1", "EV_Red_Took_Spark2", "EV_Red_Took_Spark3", "EV_RK_Available", "EV_RK_Said_Attacked_House", "EV_RK_Said_Bucket", "EV_RK_Said_Early", "EV_RK_Said_Forget01", "EV_RK_Said_Forget02", "EV_RK_Said_Muffs", "EV_RK_Said_No_Gold", "EV_RK_Said_Old_Map", "EV_RK_Said_Quid", "EV_RK_Said_Ruth", "EV_RK_Said_Sally_Attacked", "EV_RK_Said_Sandpaper", "EV_RK_Said_Scares_Birds", "EV_RK_Said_Test", "EV_Said_Comment01", "EV_Said_Comment02", "EV_Said_Comment03", "EV_Said_Comment04", "EV_Said_Comment05", "EV_Said_Comment06", "EV_Said_Comment07", "EV_Said_Comment08", "EV_Said_Comment09", "EV_Said_Comment10", "EV_Said_Comment11", "EV_Said_Comment12", "EV_Said_Comment13", "EV_Said_Comment14", "EV_Said_Comment15", "EV_Said_Comment16", "EV_Said_Comment17", "EV_Said_Comment18", "EV_Said_Comment19", "EV_Said_Comment20", "EV_Said_Engine", "EV_Sally_Said_Kit", "EV_Sally_Said_Tasks", "EV_Sample_Time1", "EV_Sample_Time2", "EV_Saw_Archive_Lucy", "EV_Saw_Archive_Waldo", "EV_Saw_Article_Lucy", "EV_Saw_Cemetery", "EV_Saw_Clock", "EV_Saw_Dog_Iggy", "EV_Saw_Dog_Levers", "EV_Saw_Dog_Lucy", "EV_Saw_Dog_Vitus", "EV_Saw_Dog_Xander_Bad", "EV_Saw_Dog_Xander_Good", "EV_Saw_Dredge_Law", "EV_Saw_Five_Birds", "EV_Saw_Flashlight_Die", "EV_Saw_Ghost_Cine1", "EV_Saw_Gold_Bar_Story", "EV_Saw_Hawk", "EV_Saw_Hidden_Door", "EV_Saw_Malone_Arrest", "EV_Saw_Newspaper_Malone", "EV_Saw_Newspaper_WA", "EV_Saw_Poem", "EV_Saw_Prime_Info", "EV_Saw_Prints", "EV_Saw_Safe", "EV_Saw_Spark_Gone", "EV_Saw_Speakeasy", "EV_Saw_Speakers", "EV_Saw_Squeak_Note", "EV_Saw_Tomb_Dogs", "EV_Saw_Tomb_Lock", "EV_Saw_Tomb_Malone", "EV_Saw_Tomb_Waldo", "EV_Saw_Tool_Shed", "EV_Saw_WA_Journal", "EV_Saw_Water_Note", "EV_Saw_Yogi", "EV_Screw1_Minus", "EV_Screw1_Out", "EV_Screw1_Plus", "EV_Screw1_Zero", "EV_Screw2_Minus", "EV_Screw2_Out", "EV_Screw2_Plus", "EV_Screw2_Zero", "EV_Screw3_Minus", "EV_Screw3_Out", "EV_Screw3_Plus", "EV_Screw3_Zero", "EV_Screw4_Minus", "EV_Screw4_Out", "EV_Screw4_Plus", "EV_Screw4_Zero", "EV_ScrewLoose0", "EV_ScrewLoose1", "EV_ScrewLoose2", "EV_ScrewLoose3", "EV_ScrewLoose4", "EV_ScrewLoose5", "EV_Sent_Photo", "EV_Shed_Fire_Near_Bug", "EV_Shed_Fire_Pos01", "EV_Shed_Fire_Pos02", "EV_Shed_Fire_Pos03", "EV_Shed_Fire_Pos04", "EV_Shed_Fire_Pos05", "EV_Shed_Fire_PosA", "EV_Shed_Fire_PosB", "EV_Shed_Fire_PosC", "EV_Shed_Fire_PosD", "EV_Shed_Gnome_Land", "EV_Shed_Gnome_Move", "EV_Shed_Jack_Pos01", "EV_Shed_Jack_Pos02", "EV_Shed_Jack_Pos03", "EV_Shed_Lost", "EV_Shed_Rake_Fire", "EV_Shed_Rake_Move", "EV_Shed_Twine_Fire", "EV_SM_Said_Arsenic", "EV_SM_Said_Break", "EV_SM_Said_Cemetery", "EV_SM_Said_Dog_Levers", "EV_SM_Said_Dread", "EV_SM_Said_EG_Irks", "EV_SM_Said_Ex", "EV_SM_Said_Flashlight", "EV_SM_Said_JA_Dislikes", "EV_SM_Said_Joke", "EV_SM_Said_Kit", "EV_SM_Said_Name", "EV_SM_Said_No_Plug", "EV_SM_Said_No_Sandpaper", "EV_SM_Said_Outdoor", "EV_SM_Said_Prime", "EV_SM_Said_Red", "EV_SM_Said_RK", "EV_SM_Said_See_EG", "EV_SM_Said_Speakeasy", "EV_SM_Said_Tasks", "EV_SM_Said_Three", "EV_SM_Said_Tool_Shed", "EV_Sneezed", "EV_Solved_Bail", "EV_Solved_Bait", "EV_Solved_Birds", "EV_Solved_Board01", "EV_Solved_Board02", "EV_Solved_Board03", "EV_Solved_Boards", "EV_Solved_Cardinal", "EV_Solved_Cassette", "EV_Solved_Dog_Levers", "EV_Solved_Fire", "EV_Solved_Floor", "EV_Solved_Gold_Door", "EV_Solved_Goldfinch", "EV_Solved_Hawk", "EV_Solved_Historical", "EV_Solved_Jay", "EV_Solved_Prime", "EV_Solved_Robin", "EV_Solved_Roman", "EV_Solved_Safe", "EV_Solved_Screws", "EV_Solved_Shed_Escape", "EV_Solved_Spark", "EV_Solved_Spigot", "EV_Solved_Spigot_Switch", "EV_Solved_Stack", "EV_Solved_Tanager", "EV_Solved_Tomb", "EV_Solved_Tomb_Lock", "EV_Solved_Toolbox", "EV_Solved_Tumbler", "EV_Solved_Water_Sample", "EV_Took_Board01", "EV_Took_Board02", "EV_Took_Board03", "EV_Took_Bucket", "EV_Took_Camo", "EV_Took_Package", "EV_Took_Screwdriver", "EV_Took_Spark", "EV_Took_Tape", "EV_Took_Toolbox_Key", "EV_Took_Viv_Photo", "EV_Took_Wheel", "EV_TookBait01", "EV_TookBait02", "EV_TookBait03", "EV_TookBait04", "EV_TookBait05", "EV_TookBait06", "EV_TookBait07", "EV_TookBait08", "EV_TookBait09", "EV_TookBait10", "EV_TookBait11", "EV_TookBait12", "EV_Tool_Shed_Fire", "EV_Tree_Block1", "EV_Tried_Bail", "EV_Tried_Bird_Task", "EV_Tried_Engine", "EV_Tried_Floor", "EV_Tried_Historical", "EV_Tried_Levers", "EV_Tried_Pump", "EV_Tried_Roman", "EV_Tried_Safe", "EV_Tried_Screws", "EV_Tried_Spark", "EV_Tried_Spigot", "EV_Tried_Spigot_Switch", "EV_Tried_Stack", "EV_Tried_Tomb", "EV_Tried_Tomb_Lock", "EV_Tried_Toolbox", "EV_Tried_Tumbler", "EV_Viv_Package_Available", "EV_Viv_Said_Baldo", "EV_Viv_Said_Cruise", "EV_Viv_Said_EA_Hi", "EV_Viv_Said_Gold", "EV_Viv_Said_Iggy", "EV_Viv_Said_Lucy_Boat", "EV_Viv_Said_Map", "EV_Viv_Said_Mathias", "EV_Viv_Said_Paintings", "EV_Viv_Said_Send_Key", "EV_Viv_Said_Speakeasy", "EV_Viv_Said_Superstitious", "EV_Viv_Said_Tomb_Lock", "EV_Viv_Said_Trusted", "EV_Viv_Said_Tunnels", "EV_Viv_Said_Unlucky", "EV_Viv_Said_Vitus_Tree", "EV_Viv_Said_Willy", "EV_Viv_Said_Willy_Safe", "EV_Viv_Said_Xander", "EV_VW_Said_Send_Photo", "EV_Well_Door_Unlocked", "EV_Well_Empty", "EV_Wheels_Unlocked", "EV_Yogi_Available", "EV_Skip", "EV_Skip", "EV_Skip", "EV_Skip", "EV_Skip", "EV_Skip", "EV_Empty1", "EV_Empty2", "EV_Empty3", "EV_Empty4", "EV_Empty5", "EV_Empty6", "EV_Empty7", "EV_Empty8", "EV_Empty9", "EV_Empty10", "EV_Empty11", "EV_Empty12", "EV_Empty13", "EV_Empty14", "EV_Empty15", "EV_Empty16", "EV_Empty17", "EV_Empty18", "EV_Empty19", "EV_Empty20", "EV_Empty21", "EV_Empty22", "EV_Empty23", "EV_Empty24", "EV_Empty25", "EV_Empty26", "EV_Empty27", "EV_Empty28", "EV_Empty29", "EV_Empty30", "EV_Empty31", "EV_Empty32", "EV_Empty33", "EV_Empty34", "EV_Empty35", "EV_Empty36", "EV_Empty37", "EV_Empty38", "EV_Empty39", "EV_Empty40", "EV_Empty41", "EV_Empty42", "EV_Empty43", "EV_Empty44", "EV_Empty45", "EV_Empty46", "EV_Empty47", "EV_Empty48", "EV_Empty49", "EV_Empty50", "EV_Empty51", "EV_Empty52", "EV_Empty53", "EV_Empty54", "EV_Empty55", "EV_Empty56", "EV_Empty57", "EV_Empty58", "EV_Empty59", "EV_Empty60", "EV_Empty61", "EV_Empty62", "EV_Empty63", "EV_Empty64", "EV_Empty65", "EV_Empty66", "EV_Empty67", "EV_Empty68", "EV_Empty69", "EV_Empty70", "EV_Empty71", "EV_Empty72", "EV_Empty73", "EV_Empty74", "EV_Empty75" };
//extern std::string flagDesc[];
//extern bool firstLoad;

//For internal use. Call Loader::loadScene instead
void _ChangeScene(std::string sceneName);
//For internal use. Call Loader::loadScene instead
void _LoadScene(std::string sceneName);
void ReloadScene();