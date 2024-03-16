	//Special Dummy vars
	//char[] apFriends = new char[4];
	//char *apFriends[4] = {}; //Array für die Namen der spieler mit denen der bot teamt (maximal 5 freunde)
	//char m_Dummy_friend[128]; // eigentlich brauchste das dann auch nicht mehr
	int m_Dummy_FriendID; // das wird jetzt benutzt um zu wissen ob der dummy einen freund hat oder nicht


	//dummymode 99 vars (the special one)
	//general
	int m_Dummy_feelingsdiff;

	int m_Dummy_happyness;
	int m_Dummy_sadness;
	int m_Dummy_boredness;
	int m_Dummy_hypeness;
	int m_Dummy_scaredness;
	int m_Dummy_shockedness;
	int m_Dummy_suprisedness;

	int m_Dummy_pain;
	int m_Dummy_adrenalin;

	//brain

	//future (hope/plans/ideas)

	//future (fear)
	//char m_Dummy_future_fear_what[1024];				//what scares the bot in the future
	//char m_Dummy_future_fear_why_happen[1024];			//what makes the bot think this will or coudl happen
	//char m_Dummy_future_fear_why_fear[1024];			//why is this scary for the bot
	//int m_Dummy_future_fear_strength;					//how scared is the bot 
	//int m_Dummy_future_fear_probability;				//how high is the chance that this coudl really happen

	//future (realistic prediction)



	
	//dummymode 32 vars
	bool m_Dummy_32reset;
	int m_Dummy_32dir;
	bool m_Dummy_32fire;
	bool m_Dummy_32jump;
	bool m_Dummy_32hook;
	bool m_Dummy_32kill;
	//bool m_Dummy_32dummy; //moved to player.h
	int m_Dummy_32balance; //0 off 1 on 2 left 3 right
	int m_Dummy_32weapon;
	//int m_Dummy_32look; //moved to player.h

	int m_Dummy_32script_s1_x; //Dummy Dummymode 32 user created script step1 x coordinate
	int m_Dummy_32script_s1_y;

	//TickTimeScrips
	int m_Dummy_32tick;
	int m_Dummy_32fire0_start;
	int m_Dummy_32fire0_stop;


	//dummymode 31 vars (ChillBlock5 police guard)
	bool m_Dummy_SpawnAnimation;
	int m_Dummy_SpawnAnimation_delay;
	bool m_Dummy_GetSpeed;
	bool m_Dummy_GotStuck;
	bool m_Dummy_ClosestPolice;
	int m_Dummy_dmm31;
	int m_Dummy_AttackMode;

	//dummymode 24 vars
	bool m_Dummy_survival_time;
	bool m_Dummy_chat;



	//dummy 102 vars (blmapTouchUp)
	bool m_Dummy_swinghook; //activates the swing hook on toplane
	bool m_Dummy_rocket_pos; //swaps direction
	bool m_Dummy_swapdir; //swaps direction
	bool m_Dummy_found_pos;
	int m_Dummy_quickystyle;

	//dummy 29 vars !!!!! also use 18 vars in 29 xD
	int m_DummyFreezeBlockTrick;
	int m_Dummy_trick_panic_check_delay;
	bool m_Dummy_start_hook;
	bool m_Dummy_speedright;  //used to go right from the left side of the freeze if there is enoigh speed
	bool m_Dummy_trick3_panic_check;
	bool m_Dummy_trick3_panic;
	bool m_Dummy_trick3_start_count;
	bool m_Dummy_trick3_panic_left;
	bool m_Dummy_trick4_hasstartpos;
	bool m_Dummy_lock_bored;             //tricky way to keep the bored bool activatet
	bool m_Dummy_doBalance;
	bool m_Dummy_AttackedOnSpawn;
	bool m_Dummy_bored_shootin;
	bool m_Dummy_bored_cuz_nothing_happens;
	bool m_Dummy_movement_to_block_area_style_window;  //yep dis is too long
	bool m_Dummy_planned_movment; // belongs to:   m_Dummy_movement_to_block_area_style_window

	//dummy 19 vars
	int m_DummyDriveDuration = 0;

	//dummymmode 26 vars

	int m_Dummy_panic_correction;		//corrects the aim of the flybot in emergencys


	//dummymode 25 vars
	bool m_Dummy_nn_touched_by_humans;	//check for interaction with players
	bool m_Dummy_nn_ready;				//is used to hardcode a start pos
	int m_Dummy_nn_ready_time;			//check how long it takes

/*	float m_Dummy_nn_latest_Distance;
	float m_Dummy_nn_highest_Distance;
	float m_Dummy_nn_latest_fitness;
	float m_Dummy_nn_highest_fitness;
	int m_Dummy_nn_time;
	int m_Dummy_nn_Tick;*/		

	bool m_Dummy_nn_write;

	//dummymode 100 vars
	bool m_Dummy_isSpawnArea;			//is used at start and to swap direction 
	bool m_Dummy_100hook;
	bool m_Dummy_1002p_hook;
	int m_Dummy_100downstyle;
	int m_Dummy_1002p_state;

	//dummymode 23 vars

	bool m_Dummy_help_emergency;		//activate if boot falls of platform while helping
	bool m_Dummy_help_no_emergency;		//this is just used to check if the bot planned to be in this situation. this bool is just used for not activating m_Dummy_help_emergency
	bool m_Dummy_hook_mate_after_hammer;//after unfreezing a mate with hammer hold him with hook
	bool m_Dummy_help_before_fly;		//to help at the mate if he gets freeze before the hammerfly started
	bool m_Dummy_2p_panic_while_helping;//if the bot falls of the platform while helping at the 2p part
	bool m_Dummy_panic_balance;			//hammerhit part struggle -> balance
	bool m_Dummy_mate_failed;			//a ´var which toggles the dummy_2p_state value -2
	bool m_Dummy_hh_hook;				//check for hook in hammerhit at end
	bool m_Dummy_collected_weapons;		//ob er nochmal zu den waffen hochfliegen muss
	bool m_Dummy_mate_collected_weapons;//ob auch der race mate waffen hat
	bool m_Dummy_rjumped2;				//ob der dummy grad den rj2 hinter sich hat
	bool m_Dummy_dd_hook;               //hier hookt er im 2p part                          nvm i renamed in 2p not dd      ignore -> [CARE USED OLD VAR FROM OLD SYSTEM FOR NEW SYSTEM CHECK THIS STUFF IF USE OLD SYSTEM AGIAN!!!!]
	bool m_Dummy_dd_helphook;			//just a helphook bool ... used for start and stoop hooking while helping at the dummydrag part
	bool m_Dummy_2p_hook;				//same as m_Dummy_dd_hook but in new sys 
	bool m_Dummy_2p_hook_grabbed;		// for better resetting if part failed
	int m_Dummy_2p_state;				//Maybe cool stuff comign with it
	int m_Dummy_mode23;                 //yes dummymode23 has his own modes o.O
	int m_Dummy_nothing_happens_counter;// counts all the nonaction lol
	int m_Dummy_panic_weapon;			// if the bot has panic (nothing happens -> panic mate coudl get bored)  change the wepaon to this var value
	int m_Dummy_sent_chat_msg;			// 0 == noMsgDisTick 1 == MsgDisTick              [to send a chat message just 1 time]
	int m_Dummy_mate_help_mode;			//how the bot shoudl help
	int m_Dummy_movement_mode23;		//a movement mode for mode23
	//int m_Dummy_rj_fails_counter;		//the hammerfly and weapon check sometimes causes fails and the dummy tries to rocketjump but is not abel to do it. this counter is used to detect this problem and kill the bot is detected

	//bool m_Dummy_2p_hammer1;			//Check if he did the first hammer

	//bool m_Dummy_rj_ready;				//check if the bot has the perfect position to make the rocketjump

	//notstand vars fuer mode 18 (also used in 29)
	bool m_Dummy_jumped;				//gesprungen wenn der notstand ausgetufen wird
	bool m_Dummy_hooked;				//gehookt wenn der notstand ausgerufen wird
	bool m_Dummy_moved_left;			//nach links gelaufen wenn der notstand ausgerufen wird
	bool m_Dummy_hook_delay;			//hook delay wenn der notstand ausgerufen wurde
	bool m_Dummy_ruled;					//ob der dummy in diesem leben schonmal am ruler spot war
	bool m_Dummy_pushing;				//ob er jemand grad beim wayblocken aus seinem wb spot schiebt
	bool m_Dummy_emergency;				// Notsand
	bool m_Dummy_wb_hooked;				//ob er grad vom wayblockspot wen wayblockig hookt
	bool m_Dummy_left_freeze_full;		//wenn jemand schon in die linke freeze wand geblockt wurde
	bool m_Dummy_happy;                 //wenn er sich auf seinem lieblings wb spot befindet
	bool m_Dummy_get_speed;             //im tunnel anlauf holen wenn ausgebremst                     WARNING THIS VAR IS ALSO USED IN DUMMYMODE == 26
	bool m_Dummy_bored;					//wenn dem bot langweilig wird wechselt er die wayblock taktik
	bool m_Dummy_special_defend;        //dummy_mode18 mode bool
	bool m_Dummy_special_defend_attack; //sub var für m_Dummy_special_defend die abfrägt ob der bot schon angreifen soll

	int m_Dummy_bored_counter;          //zähl hoch bis dem dummy lw wird

	int m_Dummy_mode18;                 //yes dummymode18 has his own modes o.O
	//bool mode18_main_init;              //yep one of the randomesteztes booleans in ze world
