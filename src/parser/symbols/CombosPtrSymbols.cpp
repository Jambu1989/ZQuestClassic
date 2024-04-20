#include "SymbolDefs.h"

CombosPtrSymbols CombosPtrSymbols::singleton = CombosPtrSymbols();

static AccessorTable CombosTable[] =
{
	//name,                       tag,            rettype,   var,               funcFlags,  params,optparams
	//Only as 'this->' in combo scripts
	{ "getX",                       0,         ZTID_FLOAT,   COMBOXR,                   0,  { ZTID_COMBOS },{} },
	{ "setX",                       0,          ZTID_VOID,   COMBOXR,           FL_RDONLY,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getY",                       0,         ZTID_FLOAT,   COMBOYR,                   0,  { ZTID_COMBOS },{} },
	{ "setY",                       0,          ZTID_VOID,   COMBOYR,           FL_RDONLY,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getPos",                     0,         ZTID_FLOAT,   COMBOPOSR,                 0,  { ZTID_COMBOS },{} },
	{ "setPos",                     0,          ZTID_VOID,   COMBOPOSR,         FL_RDONLY,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLayer",                   0,         ZTID_FLOAT,   COMBOLAYERR,               0,  { ZTID_COMBOS },{} },
	{ "setLayer",                   0,          ZTID_VOID,   COMBOLAYERR,       FL_RDONLY,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	//
	{ "getInitD[]",                 0,       ZTID_UNTYPED,   COMBODATAINITD,            0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "setInitD[]",                 0,          ZTID_VOID,   COMBODATAINITD,            0,  { ZTID_COMBOS, ZTID_FLOAT, ZTID_UNTYPED },{} },
	{ "getID",                      0,         ZTID_FLOAT,   COMBODATAID,               0,  { ZTID_COMBOS },{} },
	{ "setID",                      0,          ZTID_VOID,   COMBODATAID,       FL_RDONLY,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getOriginalTile",            0,         ZTID_FLOAT,   COMBODOTILE,               0,  { ZTID_COMBOS },{} },
	{ "setOriginalTile",            0,          ZTID_VOID,   COMBODOTILE,               0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getFrame",                   0,         ZTID_FLOAT,   COMBODFRAME,               0,  { ZTID_COMBOS },{} },
	{ "setFrame",                   0,          ZTID_VOID,   COMBODFRAME,               0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getAClk",                    0,         ZTID_FLOAT,   COMBODACLK,                0,  { ZTID_COMBOS },{} },
	{ "setAClk",                    0,          ZTID_VOID,   COMBODACLK,                0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTile",                    0,         ZTID_FLOAT,   COMBODTILE,                0,  { ZTID_COMBOS },{} },
	{ "setTile",                    0,          ZTID_VOID,   COMBODTILE,                0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getScript",                  0,         ZTID_FLOAT,   COMBODATASCRIPT,           0,  { ZTID_COMBOS },{} },
	{ "setScript",                  0,          ZTID_VOID,   COMBODATASCRIPT,           0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getASpeed",                  0,         ZTID_FLOAT,   COMBODASPEED,              0,  { ZTID_COMBOS },{} },
	{ "setASpeed",                  0,          ZTID_VOID,   COMBODASPEED,              0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getFlip",                    0,         ZTID_FLOAT,   COMBODFLIP,                0,  { ZTID_COMBOS },{} },
	{ "setFlip",                    0,          ZTID_VOID,   COMBODFLIP,                0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getWalk",                    0,         ZTID_FLOAT,   COMBODWALK,                0,  { ZTID_COMBOS },{} },
	{ "setWalk",                    0,          ZTID_VOID,   COMBODWALK,                0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getEffect",                  0,         ZTID_FLOAT,   COMBODEFFECT,              0,  { ZTID_COMBOS },{} },
	{ "setEffect",                  0,          ZTID_VOID,   COMBODEFFECT,              0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getType",                    0,         ZTID_FLOAT,   COMBODTYPE,                0,  { ZTID_COMBOS },{} },
	{ "setType",                    0,          ZTID_VOID,   COMBODTYPE,                0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getCSet",                    0,         ZTID_FLOAT,   COMBODCSET,          FL_DEPR,  { ZTID_COMBOS },{},0,"Use ->CSet2 instead!" },
	{ "setCSet",                    0,          ZTID_VOID,   COMBODCSET,          FL_DEPR,  { ZTID_COMBOS, ZTID_FLOAT },{},0,"Use ->CSet2 instead!" },
	{ "getCSet2",                   0,         ZTID_FLOAT,   COMBODCSET,                0,  { ZTID_COMBOS },{} },
	{ "setCSet2",                   0,          ZTID_VOID,   COMBODCSET,                0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getCSet2Flags",              0,         ZTID_FLOAT,   COMBODCSET2FLAGS,          0,  { ZTID_COMBOS },{} },
	{ "setCSet2Flags",              0,          ZTID_VOID,   COMBODCSET2FLAGS,          0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getFrames",                  0,         ZTID_FLOAT,   COMBODFRAMES,              0,  { ZTID_COMBOS },{} },
	{ "setFrames",                  0,          ZTID_VOID,   COMBODFRAMES,              0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getNextData",                0,         ZTID_FLOAT,   COMBODNEXTD,               0,  { ZTID_COMBOS },{} },
	{ "setNextData",                0,          ZTID_VOID,   COMBODNEXTD,               0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getNextCSet",                0,         ZTID_FLOAT,   COMBODNEXTC,               0,  { ZTID_COMBOS },{} },
	{ "setNextCSet",                0,          ZTID_VOID,   COMBODNEXTC,               0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getFlag",                    0,         ZTID_FLOAT,   COMBODFLAG,                0,  { ZTID_COMBOS },{} },
	{ "setFlag",                    0,          ZTID_VOID,   COMBODFLAG,                0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getSkipAnimX",               0,         ZTID_FLOAT,   COMBODSKIPANIM,            0,  { ZTID_COMBOS },{} },
	{ "setSkipAnimX",               0,          ZTID_VOID,   COMBODSKIPANIM,            0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getSkipAnimY",               0,         ZTID_FLOAT,   COMBODAKIMANIMY,           0,  { ZTID_COMBOS },{} },
	{ "setSkipAnimY",               0,          ZTID_VOID,   COMBODAKIMANIMY,           0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getAnimFlags",               0,         ZTID_FLOAT,   COMBODANIMFLAGS,           0,  { ZTID_COMBOS },{} },
	{ "setAnimFlags",               0,          ZTID_VOID,   COMBODANIMFLAGS,           0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getAttributes[]",            0,         ZTID_FLOAT,   COMBODATTRIBUTES,          0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "setAttributes[]",            0,          ZTID_VOID,   COMBODATTRIBUTES,          0,  { ZTID_COMBOS, ZTID_FLOAT, ZTID_UNTYPED },{} },
	{ "getAttribytes[]",            0,         ZTID_FLOAT,   COMBODATTRIBYTES,          0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "setAttribytes[]",            0,          ZTID_VOID,   COMBODATTRIBYTES,          0,  { ZTID_COMBOS, ZTID_FLOAT, ZTID_UNTYPED },{} },
	{ "getAttrishorts[]",           0,         ZTID_FLOAT,   COMBODATTRISHORTS,         0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "setAttrishorts[]",           0,          ZTID_VOID,   COMBODATTRISHORTS,         0,  { ZTID_COMBOS, ZTID_FLOAT, ZTID_UNTYPED },{} },
	{ "getTrigFlags[]",             0,          ZTID_BOOL,   COMBODTRIGGERFLAGS2,       0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "setTrigFlags[]",             0,          ZTID_VOID,   COMBODTRIGGERFLAGS2,       0,  { ZTID_COMBOS, ZTID_FLOAT, ZTID_BOOL },{} },
	{ "getFlags[]",                 0,          ZTID_BOOL,   COMBODUSRFLAGARR,          0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "setFlags[]",                 0,          ZTID_VOID,   COMBODUSRFLAGARR,          0,  { ZTID_COMBOS, ZTID_FLOAT, ZTID_BOOL },{} },
	{ "getGenFlags[]",              0,          ZTID_BOOL,   COMBODGENFLAGARR,          0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "setGenFlags[]",              0,          ZTID_VOID,   COMBODGENFLAGARR,          0,  { ZTID_COMBOS, ZTID_FLOAT, ZTID_BOOL },{} },
	{ "getTrigButton[]",            0,          ZTID_BOOL,   COMBODTRIGGERBUTTON,       0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "setTrigButton[]",            0,          ZTID_VOID,   COMBODTRIGGERBUTTON,       0,  { ZTID_COMBOS, ZTID_FLOAT, ZTID_BOOL },{} },
	{ "getTrigLevel",               0,         ZTID_FLOAT,   COMBODTRIGGERLEVEL,        0,  { ZTID_COMBOS },{} },
	{ "setTrigLevel",               0,          ZTID_VOID,   COMBODTRIGGERLEVEL,        0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigItem",                0,         ZTID_FLOAT,   COMBODTRIGGERITEM,         0,  { ZTID_COMBOS },{} },
	{ "setTrigItem",                0,          ZTID_VOID,   COMBODTRIGGERITEM,         0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigTimer",               0,         ZTID_FLOAT,   COMBODTRIGGERTIMER,        0,  { ZTID_COMBOS },{} },
	{ "setTrigTimer",               0,          ZTID_VOID,   COMBODTRIGGERTIMER,        0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigSFX",                 0,         ZTID_FLOAT,   COMBODTRIGGERSFX,          0,  { ZTID_COMBOS },{} },
	{ "setTrigSFX",                 0,          ZTID_VOID,   COMBODTRIGGERSFX,          0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigChange",              0,         ZTID_FLOAT,   COMBODTRIGGERCHANGECMB,    0,  { ZTID_COMBOS },{} },
	{ "setTrigChange",              0,          ZTID_VOID,   COMBODTRIGGERCHANGECMB,    0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigProximity",           0,         ZTID_FLOAT,   COMBODTRIGGERPROX,         0,  { ZTID_COMBOS },{} },
	{ "setTrigProximity",           0,          ZTID_VOID,   COMBODTRIGGERPROX,         0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigLightBeam",           0,         ZTID_FLOAT,   COMBODTRIGGERLIGHTBEAM,    0,  { ZTID_COMBOS },{} },
	{ "setTrigLightBeam",           0,          ZTID_VOID,   COMBODTRIGGERLIGHTBEAM,    0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigCounter",             0,         ZTID_FLOAT,   COMBODTRIGGERCTR,          0,  { ZTID_COMBOS },{} },
	{ "setTrigCounter",             0,          ZTID_VOID,   COMBODTRIGGERCTR,          0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigCtrAmount",           0,         ZTID_FLOAT,   COMBODTRIGGERCTRAMNT,      0,  { ZTID_COMBOS },{} },
	{ "setTrigCtrAmount",           0,          ZTID_VOID,   COMBODTRIGGERCTRAMNT,      0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigCooldown",            0,         ZTID_FLOAT,   COMBODTRIGGERCOOLDOWN,     0,  { ZTID_COMBOS },{} },
	{ "setTrigCooldown",            0,          ZTID_VOID,   COMBODTRIGGERCOOLDOWN,     0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigCopycat",             0,         ZTID_FLOAT,   COMBODTRIGGERCOPYCAT,      0,  { ZTID_COMBOS },{} },
	{ "setTrigCopycat",             0,          ZTID_VOID,   COMBODTRIGGERCOPYCAT,      0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigSpawnItemPickup",     0,         ZTID_FLOAT,   COMBODTRIGITEMPICKUP,      0,  { ZTID_COMBOS },{} },
	{ "setTrigSpawnItemPickup",     0,          ZTID_VOID,   COMBODTRIGITEMPICKUP,      0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigExState",             0,         ZTID_FLOAT,   COMBODTRIGEXSTATE,         0,  { ZTID_COMBOS },{} },
	{ "setTrigExState",             0,          ZTID_VOID,   COMBODTRIGEXSTATE,         0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigExDoorDir",           0,         ZTID_FLOAT,   COMBODTRIGEXDOORDIR,       0,  { ZTID_COMBOS },{} },
	{ "setTrigExDoorDir",           0,          ZTID_VOID,   COMBODTRIGEXDOORDIR,       0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigExDoorIndex",         0,         ZTID_FLOAT,   COMBODTRIGEXDOORIND,       0,  { ZTID_COMBOS },{} },
	{ "setTrigExDoorIndex",         0,          ZTID_VOID,   COMBODTRIGEXDOORIND,       0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigSpawnEnemy",          0,         ZTID_FLOAT,   COMBODTRIGSPAWNENEMY,      0,  { ZTID_COMBOS },{} },
	{ "setTrigSpawnEnemy",          0,          ZTID_VOID,   COMBODTRIGSPAWNENEMY,      0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigSpawnItem",           0,         ZTID_FLOAT,   COMBODTRIGSPAWNITEM,       0,  { ZTID_COMBOS },{} },
	{ "setTrigSpawnItem",           0,          ZTID_VOID,   COMBODTRIGSPAWNITEM,       0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigCSetChange",          0,         ZTID_FLOAT,   COMBODTRIGCSETCHANGE,      0,  { ZTID_COMBOS },{} },
	{ "setTrigCSetChange",          0,          ZTID_VOID,   COMBODTRIGCSETCHANGE,      0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigLevelState",          0,         ZTID_FLOAT,   COMBODTRIGGERLSTATE,       0,  { ZTID_COMBOS },{} },
	{ "setTrigLevelState",          0,          ZTID_VOID,   COMBODTRIGGERLSTATE,       0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigGlobalState",         0,         ZTID_FLOAT,   COMBODTRIGGERGSTATE,       0,  { ZTID_COMBOS },{} },
	{ "setTrigGlobalState",         0,          ZTID_VOID,   COMBODTRIGGERGSTATE,       0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigGStateTimer",         0,         ZTID_FLOAT,   COMBODTRIGGERGTIMER,       0,  { ZTID_COMBOS },{} },
	{ "setTrigGStateTimer",         0,          ZTID_VOID,   COMBODTRIGGERGTIMER,       0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigGenScript",           0,         ZTID_FLOAT,   COMBODTRIGGERGENSCRIPT,    0,  { ZTID_COMBOS },{} },
	{ "setTrigGenScript",           0,          ZTID_VOID,   COMBODTRIGGERGENSCRIPT,    0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigGroup",               0,         ZTID_FLOAT,   COMBODTRIGGERGROUP,        0,  { ZTID_COMBOS },{} },
	{ "setTrigGroup",               0,          ZTID_VOID,   COMBODTRIGGERGROUP,        0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigGroupVal",            0,         ZTID_FLOAT,   COMBODTRIGGERGROUPVAL,     0,  { ZTID_COMBOS },{} },
	{ "setTrigGroupVal",            0,          ZTID_VOID,   COMBODTRIGGERGROUPVAL,     0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	
	{ "getTrigLItems",              0,         ZTID_FLOAT,   COMBODTRIGLITEMS,          0,  { ZTID_COMBOS },{} },
	{ "setTrigLItems",              0,          ZTID_VOID,   COMBODTRIGLITEMS,          0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigDMapLvl",             0,         ZTID_FLOAT,   COMBODTRIGDMAPLVL,         0,  { ZTID_COMBOS },{} },
	{ "setTrigDMapLvl",             0,          ZTID_VOID,   COMBODTRIGDMAPLVL,         0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigTintR",               0,         ZTID_FLOAT,   COMBODTRIGTINTR,           0,  { ZTID_COMBOS },{} },
	{ "setTrigTintR",               0,          ZTID_VOID,   COMBODTRIGTINTR,           0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigTintG",               0,         ZTID_FLOAT,   COMBODTRIGTINTG,           0,  { ZTID_COMBOS },{} },
	{ "setTrigTintG",               0,          ZTID_VOID,   COMBODTRIGTINTG,           0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigTintB",               0,         ZTID_FLOAT,   COMBODTRIGTINTB,           0,  { ZTID_COMBOS },{} },
	{ "setTrigTintB",               0,          ZTID_VOID,   COMBODTRIGTINTB,           0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigLvlPal",              0,         ZTID_FLOAT,   COMBODTRIGLVLPAL,          0,  { ZTID_COMBOS },{} },
	{ "setTrigLvlPal",              0,          ZTID_VOID,   COMBODTRIGLVLPAL,          0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigBossPal",             0,         ZTID_FLOAT,   COMBODTRIGBOSSPAL,         0,  { ZTID_COMBOS },{} },
	{ "setTrigBossPal",             0,          ZTID_VOID,   COMBODTRIGBOSSPAL,         0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigQuakeTimer",          0,         ZTID_FLOAT,   COMBODTRIGQUAKETIME,       0,  { ZTID_COMBOS },{} },
	{ "setTrigQuakeTimer",          0,          ZTID_VOID,   COMBODTRIGQUAKETIME,       0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigWavyTimer",           0,         ZTID_FLOAT,   COMBODTRIGWAVYTIME,        0,  { ZTID_COMBOS },{} },
	{ "setTrigWavyTimer",           0,          ZTID_VOID,   COMBODTRIGWAVYTIME,        0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigSwordJinx",           0,         ZTID_FLOAT,   COMBODTRIGSWORDJINX,       0,  { ZTID_COMBOS },{} },
	{ "setTrigSwordJinx",           0,          ZTID_VOID,   COMBODTRIGSWORDJINX,       0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigItemJinx",            0,         ZTID_FLOAT,   COMBODTRIGITEMJINX,        0,  { ZTID_COMBOS },{} },
	{ "setTrigItemJinx",            0,          ZTID_VOID,   COMBODTRIGITEMJINX,        0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigStun",                0,         ZTID_FLOAT,   COMBODTRIGSTUN,            0,  { ZTID_COMBOS },{} },
	{ "setTrigStun",                0,          ZTID_VOID,   COMBODTRIGSTUN,            0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigBunny",               0,         ZTID_FLOAT,   COMBODTRIGBUNNY,           0,  { ZTID_COMBOS },{} },
	{ "setTrigBunny",               0,          ZTID_VOID,   COMBODTRIGBUNNY,           0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTrigPushTime",            0,         ZTID_FLOAT,   COMBODTRIGPUSHTIME,        0,  { ZTID_COMBOS },{} },
	{ "setTrigPushTime",            0,          ZTID_VOID,   COMBODTRIGPUSHTIME,        0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	
	
	{ "getLiftGFXCombo",            0,         ZTID_FLOAT,   COMBODLIFTGFXCOMBO,        0,  { ZTID_COMBOS },{} },
	{ "setLiftGFXCombo",            0,          ZTID_VOID,   COMBODLIFTGFXCOMBO,        0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftGFXCSet",             0,         ZTID_FLOAT,   COMBODLIFTGFXCCSET,        0,  { ZTID_COMBOS },{} },
	{ "setLiftGFXCSet",             0,          ZTID_VOID,   COMBODLIFTGFXCCSET,        0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftUnderCombo",          0,         ZTID_FLOAT,   COMBODLIFTUNDERCMB,        0,  { ZTID_COMBOS },{} },
	{ "setLiftUnderCombo",          0,          ZTID_VOID,   COMBODLIFTUNDERCMB,        0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftUnderCSet",           0,         ZTID_FLOAT,   COMBODLIFTUNDERCS,         0,  { ZTID_COMBOS },{} },
	{ "setLiftUnderCSet",           0,          ZTID_VOID,   COMBODLIFTUNDERCS,         0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftDamage",              0,         ZTID_FLOAT,   COMBODLIFTDAMAGE,          0,  { ZTID_COMBOS },{} },
	{ "setLiftDamage",              0,          ZTID_VOID,   COMBODLIFTDAMAGE,          0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftLevel",               0,         ZTID_FLOAT,   COMBODLIFTLEVEL,           0,  { ZTID_COMBOS },{} },
	{ "setLiftLevel",               0,          ZTID_VOID,   COMBODLIFTLEVEL,           0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftItem",                0,         ZTID_FLOAT,   COMBODLIFTITEM,            0,  { ZTID_COMBOS },{} },
	{ "setLiftItem",                0,          ZTID_VOID,   COMBODLIFTITEM,            0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftFlags[]",             0,          ZTID_BOOL,   COMBODLIFTFLAGS,           0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "setLiftFlags[]",             0,          ZTID_VOID,   COMBODLIFTFLAGS,           0,  { ZTID_COMBOS, ZTID_FLOAT, ZTID_BOOL },{} },
	{ "getLiftGFXType",             0,         ZTID_FLOAT,   COMBODLIFTGFXTYPE,         0,  { ZTID_COMBOS },{} },
	{ "setLiftGFXType",             0,          ZTID_VOID,   COMBODLIFTGFXTYPE,         0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftGFXSprite",           0,         ZTID_FLOAT,   COMBODLIFTGFXSPRITE,       0,  { ZTID_COMBOS },{} },
	{ "setLiftGFXSprite",           0,          ZTID_VOID,   COMBODLIFTGFXSPRITE,       0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftSFX",                 0,         ZTID_FLOAT,   COMBODLIFTSFX,             0,  { ZTID_COMBOS },{} },
	{ "setLiftSFX",                 0,          ZTID_VOID,   COMBODLIFTSFX,             0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftBreakSprite",         0,         ZTID_FLOAT,   COMBODLIFTBREAKSPRITE,     0,  { ZTID_COMBOS },{} },
	{ "setLiftBreakSprite",         0,          ZTID_VOID,   COMBODLIFTBREAKSPRITE,     0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftBreakSFX",            0,         ZTID_FLOAT,   COMBODLIFTBREAKSFX,        0,  { ZTID_COMBOS },{} },
	{ "setLiftBreakSFX",            0,          ZTID_VOID,   COMBODLIFTBREAKSFX,        0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftHeight",              0,         ZTID_FLOAT,   COMBODLIFTHEIGHT,          0,  { ZTID_COMBOS },{} },
	{ "setLiftHeight",              0,          ZTID_VOID,   COMBODLIFTHEIGHT,          0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftTime",                0,         ZTID_FLOAT,   COMBODLIFTTIME,            0,  { ZTID_COMBOS },{} },
	{ "setLiftTime",                0,          ZTID_VOID,   COMBODLIFTTIME,            0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getLiftWeaponItem",          0,         ZTID_FLOAT,   COMBODLIFTWEAPONITEM,      0,  { ZTID_COMBOS },{} },
	{ "setLiftWeaponItem",          0,          ZTID_VOID,   COMBODLIFTWEAPONITEM,      0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	
	//Undocumented intentionally
	{ "getTriggerButton[]",         0, "getTrigButton[]",         0 },
	{ "setTriggerButton[]",         0, "setTrigButton[]",         0 },
	{ "getTriggerLevel",            0, "getTrigLevel",            0 },
	{ "setTriggerLevel",            0, "setTrigLevel",            0 },
	{ "getTriggerItem",             0, "getTrigItem",             0 },
	{ "setTriggerItem",             0, "setTrigItem",             0 },
	{ "getTriggerTimer",            0, "getTrigTimer",            0 },
	{ "setTriggerTimer",            0, "setTrigTimer",            0 },
	{ "getTriggerSFX",              0, "getTrigSFX",              0 },
	{ "setTriggerSFX",              0, "setTrigSFX",              0 },
	{ "getTriggerChange",           0, "getTrigChange",           0 },
	{ "setTriggerChange",           0, "setTrigChange",           0 },
	{ "getTriggerProximity",        0, "getTrigProximity",        0 },
	{ "setTriggerProximity",        0, "setTrigProximity",        0 },
	{ "getTriggerLightBeam",        0, "getTrigLightBeam",        0 },
	{ "setTriggerLightBeam",        0, "setTrigLightBeam",        0 },
	{ "getTriggerCounter",          0, "getTrigCounter",          0 },
	{ "setTriggerCounter",          0, "setTrigCounter",          0 },
	{ "getTriggerCtrAmount",        0, "getTrigCtrAmount",        0 },
	{ "setTriggerCtrAmount",        0, "setTrigCtrAmount",        0 },
	{ "setTriggerCooldown",         0, "setTrigCooldown",         0 },
	{ "getTriggerCopycat",          0, "getTrigCopycat",          0 },
	{ "setTriggerCopycat",          0, "setTrigCopycat",          0 },
	{ "getTriggerSpawnItemPickup",  0, "getTrigSpawnItemPickup",  0 },
	{ "setTriggerSpawnItemPickup",  0, "setTrigSpawnItemPickup",  0 },
	{ "getTriggerExState",          0, "getTrigExState",          0 },
	{ "setTriggerExState",          0, "setTrigExState",          0 },
	{ "getTriggerExDoorDir",        0, "getTrigExDoorDir",        0 },
	{ "setTriggerExDoorDir",        0, "setTrigExDoorDir",        0 },
	{ "getTriggerExDoorIndex",      0, "getTrigExDoorIndex",      0 },
	{ "setTriggerExDoorIndex",      0, "setTrigExDoorIndex",      0 },
	{ "getTriggerSpawnEnemy",       0, "getTrigSpawnEnemy",       0 },
	{ "setTriggerSpawnEnemy",       0, "setTrigSpawnEnemy",       0 },
	{ "getTriggerSpawnItem",        0, "getTrigSpawnItem",        0 },
	{ "setTriggerSpawnItem",        0, "setTrigSpawnItem",        0 },
	{ "getTriggerCSetChange",       0, "getTrigCSetChange",       0 },
	{ "setTriggerCSetChange",       0, "setTrigCSetChange",       0 },
	{ "getTriggerLevelState",       0, "getTrigLevelState",       0 },
	{ "setTriggerLevelState",       0, "setTrigLevelState",       0 },
	{ "getTriggerGlobalState",      0, "getTrigGlobalState",      0 },
	{ "setTriggerGlobalState",      0, "setTrigGlobalState",      0 },
	{ "getTriggerGStateTimer",      0, "getTrigGStateTimer",      0 },
	{ "setTriggerGStateTimer",      0, "setTrigGStateTimer",      0 },
	{ "getTriggerGenScript",        0, "getTrigGenScript",        0 },
	{ "setTriggerGenScript",        0, "setTrigGenScript",        0 },
	{ "getTriggerGroup",            0, "getTrigGroup",            0 },
	{ "setTriggerGroup",            0, "setTrigGroup",            0 },
	{ "getTriggerGroupVal",         0, "getTrigGroupVal",         0 },
	{ "setTriggerGroupVal",         0, "setTrigGroupVal",         0 },
	{ "getTriggerLItems",           0, "getTrigLItems",           0 },
	{ "setTriggerLItems",           0, "setTrigLItems",           0 },
	{ "getTriggerDMapLvl",          0, "getTrigDMapLvl",          0 },
	{ "setTriggerDMapLvl",          0, "setTrigDMapLvl",          0 },
	{ "getTriggerTintR",            0, "getTrigTintR",            0 },
	{ "setTriggerTintR",            0, "setTrigTintR",            0 },
	{ "getTriggerTintG",            0, "getTrigTintG",            0 },
	{ "setTriggerTintG",            0, "setTrigTintG",            0 },
	{ "getTriggerTintB",            0, "getTrigTintB",            0 },
	{ "setTriggerTintB",            0, "setTrigTintB",            0 },
	{ "getTriggerLvlPal",           0, "getTrigLvlPal",           0 },
	{ "setTriggerLvlPal",           0, "setTrigLvlPal",           0 },
	{ "getTriggerBossPal",          0, "getTrigBossPal",          0 },
	{ "setTriggerBossPal",          0, "setTrigBossPal",          0 },
	{ "getTriggerQuakeTimer",       0, "getTrigQuakeTimer",       0 },
	{ "setTriggerQuakeTimer",       0, "setTrigQuakeTimer",       0 },
	{ "getTriggerWavyTimer",        0, "getTrigWavyTimer",        0 },
	{ "setTriggerWavyTimer",        0, "setTrigWavyTimer",        0 },
	{ "getTriggerSwordJinx",        0, "getTrigSwordJinx",        0 },
	{ "setTriggerSwordJinx",        0, "setTrigSwordJinx",        0 },
	{ "getTriggerItemJinx",         0, "getTrigItemJinx",         0 },
	{ "setTriggerItemJinx",         0, "setTrigItemJinx",         0 },
	{ "getTriggerStun",             0, "getTrigStun",             0 },
	{ "setTriggerStun",             0, "setTrigStun",             0 },
	{ "getTriggerBunny",            0, "getTrigBunny",            0 },
	{ "setTriggerBunny",            0, "setTrigBunny",            0 },
	{ "getTriggerPushTime",         0, "getTrigPushTime",         0 },
	{ "setTriggerPushTime",         0, "setTrigPushTime",         0 },
	
	{ "_getPosX",                   0,         ZTID_FLOAT,   COMBOXR,            FL_DEPR,  { ZTID_COMBOS },{},0,"Use [X] instead!" },
	{ "_getPosY",                   0,         ZTID_FLOAT,   COMBOYR,            FL_DEPR,  { ZTID_COMBOS },{},0,"Use [Y] instead!" },
	{ "_getPos",                    0,         ZTID_FLOAT,   COMBOPOSR,          FL_DEPR,  { ZTID_COMBOS },{},0,"Use [Pos] instead!" },
	{ "_getLayer",                  0,         ZTID_FLOAT,   COMBOLAYERR,        FL_DEPR,  { ZTID_COMBOS },{},0,"Use [Layer] instead!" },

	{ "getSkipAnim",                0,         ZTID_FLOAT,   COMBODSKIPANIM,            0,  { ZTID_COMBOS },{} },
	{ "setSkipAnim",                0,          ZTID_VOID,   COMBODSKIPANIM,            0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getUserFlags",               0,         ZTID_FLOAT,   COMBODUSRFLAGS,            0,  { ZTID_COMBOS },{} },
	{ "setUserFlags",               0,          ZTID_VOID,   COMBODUSRFLAGS,            0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getExpansion[]",             0,         ZTID_FLOAT,   COMBODEXPANSION,           0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "setExpansion[]",             0,          ZTID_VOID,   COMBODEXPANSION,           0,  { ZTID_COMBOS, ZTID_FLOAT, ZTID_UNTYPED },{} },
	{ "getNextTimer",               0,         ZTID_FLOAT,   COMBODNEXTTIMER,           0,  { ZTID_COMBOS },{} },
	{ "setNextTimer",               0,          ZTID_VOID,   COMBODNEXTTIMER,           0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "getTriggerFlags[]",          0,         ZTID_FLOAT,   COMBODTRIGGERFLAGS,        0,  { ZTID_COMBOS, ZTID_FLOAT },{} },
	{ "setTriggerFlags[]",          0,          ZTID_VOID,   COMBODTRIGGERFLAGS,        0,  { ZTID_COMBOS, ZTID_FLOAT, ZTID_UNTYPED },{} },
	
	{ "",                           0,          ZTID_VOID,   -1,                        0,  {},{} }
};

CombosPtrSymbols::CombosPtrSymbols()
{
	table = CombosTable;
	refVar = REFCOMBODATA; //NUL;
}

void CombosPtrSymbols::generateCode()
{}

