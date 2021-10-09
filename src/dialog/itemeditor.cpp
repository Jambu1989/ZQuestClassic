#include "itemeditor.h"
#include "info.h"
#include "../zsys.h"
#include <gui/builder.h>

extern zquestheader header;
extern bool saved;
extern char *item_string[];
extern itemdata *itemsbuf;
void call_item_editor(int index)
{
	ItemEditorDialog(index).show();
}

static const GUI::ListData PFlagTypeList
{
	{ "Disabled", 0 },
	{ "Set To These", 1 },
	{ "Add These", 2 },
	{ "Subtract These", 3 },
	{ "Limit To These", 4 }
};

//Sets the Item Editor Field Names
ItemNameInfo inameinf[]=
{
	//itemclass                       power                                     misc1                                       misc2                                           misc3                                   misc4                                   misc5                              misc6                              misc7                              misc8                              misc9                                        misc10                                  flag1                                   flag2                                   flag3                                                                   flag4                                   flag5                                   wpn1 (Sprites[0])                            wpn2 (Sprites[1])                               wpn3 (Sprites[2])                               wpn4 (Sprites[3])                               wpn5 (Sprites[4])                               wpn6 (Sprites[5])                               wpn7 (Sprites[6])                               wpn8 (Sprites[7])                               wpn9 (Sprites[8])                               wpn10 (Sprites[9])                              action sound                               flag6,                                          flag7,                                                                            flag8,                                          flag9,                                                      flag10,                                         flag11.                                         flag12,                                         flag13,                                         flag14,                                         flag15,                                         flag16               },
	{ itype_fairy,                    NULL,                                     (char *)"HP Regained:",                     (char *)"MP Regained:",                         (char *)"Step Speed:",                  NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"HP. R. Is Percent",            (char *)"MP. R. Is Percent",            NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Item Drop Sound:",                NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_triforcepiece,            NULL,                                     (char *)"Cutscene MIDI:",                   (char *)"Cutscene Type (0-1):",                 (char *)"Second Collect Sound:",                                   (char *)"Custom Cutscene Duration",                                   (char *)"Custom Refill Frame",                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Side Warp Out",                NULL,                                   (char *)"Removes Sword Jinxes",                                         (char *)"Removes Item Jinxes",          NULL,NULL,NULL,NULL,                                                                                    NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           (char *)"Don't Dismiss Messages",                                                       (char *)"Cutscene Interrupts Action Script",                                           (char *)"Don't Affect Music",                                           (char *)"No Cutscene", (char *)"Run Action Script on Collection",                                   (char *)"Play Second Sound Effect",                                        (char *)"Don't Play MIDI",                                          (char *)"Constant Script"                 },
	{ itype_shield,                   NULL,                                     (char *)"Block Flags:",                     (char *)"Reflect Flags:",                       NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"De/Reflection Sound:",            NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_agony,                    (char *)"Sensitivity:",                   (char *)"Vibration Frequency",              NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_wealthmedal,              NULL,                                     (char *)"Discount Amount:",                 NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"D. A. Is Percent",             NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_cbyrna,                   (char *)"Beam Damage:",                   (char *)"Beam Speed Divisor:",              (char *)"Orbit Radius:",                        (char *)"Number Of Beams:",             (char *)"Melee Damage:",                NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        (char *)"Slash Sound:",                 (char *)"Penetrates Enemies",           (char *)"Invincible Player",            (char *)"No Melee Attack",                                              (char *)"Can Slash",                    NULL,                                   (char *)"Stab Sprite:",                      (char *)"Slash Sprite:",                        (char *)"Beam Sprite:",                         (char *)"Sparkle Sprite:",                      (char *)"Damaging Sparkle Sprite:",             NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Orbit Sound:",                    (char *)"Melee Weapons Use Magic Cost",         (char *)"Doesn't Pick Up Dropped Items",                                          (char *)"Flip Right-Facing Slash",              NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_whispring,                (char *)"Jinx Divisor:",                  (char *)"Jinx Type:",                       NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Perm. Jinx Are Temp.",         NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_ladder,                   (char *)"Four-Way:",                      NULL,                                       NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Can Ladder Over Pitfalls",     NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_magickey,                 (char *)"Dungeon Level:",                 NULL,                                       NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Lesser D. Levels Also",        NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_wallet,                   (char *)"Infinite Supply:",               (char *)"Increase Amount:",                 (char *)"Delay Duration:",                      NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_quiver,                   (char *)"Infinite Supply:",               (char *)"Increase Amount:",                 (char *)"Delay Duration:",                      NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_bombbag,                  (char *)"Infinite Supply:",               (char *)"Increase Amount:",                 (char *)"Delay Duration:",                      NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Super Bombs Also",             NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_quakescroll2,             (char *)"Damage Multiplier:",             (char *)"Stun Duration:",                   (char *)"Stun Radius:",                         NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Quake Sound:",                    NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_quakescroll,              (char *)"Damage Multiplier:",             (char *)"Stun Duration:",                   (char *)"Stun Radius:",                         NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Quake Sound:",                    NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_perilscroll,              NULL,                                     (char *)"Maximum Hearts:",                  NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_spinscroll2,              (char *)"Damage Multiplier:",             (char *)"Number of Spins:",                 NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Spinning Sound:",                 NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_spinscroll,               (char *)"Damage Multiplier:",             (char *)"Number of Spins:",                 NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Spinning Sound:",                 NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_clock,                    NULL,                                     (char *)"Duration (0 = Infinite):",         NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_magicring,                (char *)"Infinite Magic:",                (char *)"Increase Amount:",                 (char *)"Delay Duration:",                      NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_heartring,                NULL,                                     (char *)"Increase Amount:",                 (char *)"Delay Duration:",                      NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	//itemclass                       power                                     misc1                                       misc2                                           misc3                                   misc4                                   misc5                              misc6                              misc7                              misc8                              misc9                                        misc10                                  flag1                                   flag2                                   flag3                                                                   flag4                                   flag5                                   wpn1                                         wpn2                                            wpn3                                            wpn4                                            wpn5                                            wpn6                                            wpn7                                            wpn8                                            wpn9                                            wpn10                                           action sound                               flag6,                                          flag7,                                                                            flag8,                                          flag9,                                                      flag10,                                         flag11.                                         flag12,                                         flag13,                                         flag14,                                         flag15,                                         flag16               },
	{ itype_chargering,               NULL,                                     (char *)"Charging Duration:",               (char *)"Magic C. Duration:",                   NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_hoverboots,               NULL,                                     (char *)"Hover Duration:",                  NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Timer only resets on landing", NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   (char *)"Halo Sprite:",                      NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Hovering Sound:",                 NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_rocs,                     (char *)"Jump Power:",                    (char *)"Extra Jumps:",                     NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Jump is Power/100",            NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Jumping Sound:",                  NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_sbomb,                    (char *)"Damage:",                        (char *)"Fuse Duration (0 = Remote):",      (char *)"Max. On Screen:",                      (char *)"Damage to Player:",            NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   (char *)"Explosion Hurts Player",       NULL,                                                                   NULL,                                   NULL,                                   (char *)"Bomb Sprite:",                      (char *)"Explosion Sprite:",                    NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Explosion Sound:",                NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_bomb,                     (char *)"Damage:",                        (char *)"Fuse Duration (0 = Remote):",      (char *)"Max. On Screen:",                      (char *)"Damage to Player:",            NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Use 1.92 Timing",              (char *)"Explosion Hurts Player",       NULL,                                                                   NULL,                                   NULL,                                   (char *)"Bomb Sprite:",                      (char *)"Explosion Sprite:",                    NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Explosion Sound:",                NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_nayruslove,               NULL,                                     (char *)"Duration:",                        NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Rocket Flickers",              (char *)"Translucent Rocket",           (char *)"Translucent Shield",                                           (char *)"Shield Flickers",              NULL,                                   (char *)"Left Rocket Sprite:",               (char *)"L. Rocket Return Sprite:",             (char *)"L. Rocket Sparkle Sprite:",            (char *)"L. Return Sparkle Sprite:",            (char *)"Shield Sprite (2x2, Over):",           (char *)"Right Rocket Sprite:",                 (char *)"R. Rocket Return Sprite:",             (char *)"R. Rocket Sparkle Sprite:",            (char *)"R. Return Sparkle Sprite:",            (char *)"Shield Sprite (2x2, Under):",          (char *)"Shield Sound:",                   NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_faroreswind,              NULL,                                     (char *)"Warp Animation (0-2):",            NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Wind Sound:",                     NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_dinsfire,                 (char *)"Damage:",                        (char *)"Number of Flames:",                (char *)"Circle Width:",                        NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   (char *)"Don't Provide Light",          (char *)"Falls in Sideview",                                            NULL,                                   (char *)"Temporary Light",              (char *)"Rocket Up Sprite:",                 (char *)"Rocket Down Sprite:",                  (char *)"R. Up Sparkle Sprite:",                (char *)"R. Down Sparkle Sprite:",              (char *)"Flame Sprite:",                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Ring Sound:",                     NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_hammer,                   (char *)"Damage:",                        NULL,                                       NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   (char *)"No Melee Attack",                                              NULL,                                   NULL,                                   (char *)"Hammer Sprite:",                    (char *)"Smack Sprite:",                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Pound Sound:",                    NULL,                                           (char *)"Doesn't Pick Up Dropped Items",                                          NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_lens,                     NULL,                                     (char *)"Lens Width:",                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Show Hints",                   (char *)"Hide Secret Combos",           (char *)"No X-Ray for Items",                                           (char *)"Show Raft Paths",              (char *)"Show Invis. Enemies",          NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Activation Sound:",               NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_hookshot,                 (char *)"Damage:",                        (char *)"Chain Length:",                    (char *)"Chain Links:",                         (char *)"Block Flags:",                 (char *)"Reflect Flags:",               NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Handle Damage",             (char *)"Allow Diagonal",               NULL,                                                                   (char *)"Pick Up Anything",             (char *)"Drags Items",                  (char *)"Tip Sprite:",                       (char *)"Chain Sprite (H):",                    (char *)"Chain Sprite (V):",                    (char *)"Handle Sprite:",                       (char *)"Diagonal Tip Sprite:",                 (char *)"Diagonal Handle Sprite:",              (char *)"Diagonal Chain Sprite:",               NULL,                                           NULL,                                           NULL,                                           (char *)"Firing Sound:",                   (char *)"Reflects Enemy Projectiles",           (char *)"Picks Up Keys",  NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_boots,                    (char *)"Damage Combo Level:",            NULL,                                       NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Not Solid Combos",             (char *)"Iron",                         NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_bracelet,                 (char *)"Push Combo Level:",              NULL,                                       NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Once Per Screen",              NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_book,                     (char *)"M. Damage:",                     (char *)"W. Damage:",                       (char*)"Wand Sound",                                           (char*)"Special Step",                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Fire Magic",                   (char *)"Override Wand Damagex",                (char *)"Fire Doesn't Hurt Player",                                     (char *)"Override Wand SFX",                                   (char *)"Temporary Light",              (char *)"Magic Sprite:",                     (char *)"Projectile Sprite:",                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Firing Sound:",                   (char *)"Replace Wand Weapon",                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_ring,                     (char *)"Damage Divisor:",                (char *)"Player Sprite Pal:",               NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Affects Damage Combos",        (char *)"Divisor is Percentage Multiplier", NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_wand,                     (char *)"Damage:",                        (char *)"M. Damage",                        (char *)"W. Type:",                             (char *)"W. Speed:",                    (char *)"W. Range:",                    (char *)"Move Effect:",            (char *)"Mvt Arg1:",               (char *)"Mvt Arg2:",               (char *)"No. of Clones:",          (char *)"Clone Pattern:",                    (char *)"Slash Sound:",                 (char *)"Allow Magic w/o Book",         (char *)"Wand Moves",                   (char *)"No Melee Attack",                                              (char *)"Can Slash",                    (char *)"Quick",                        (char *)"Stab Sprite:",                      (char *)"Slash Sprite:",                        (char *)"Projectile Sprite:",                   (char *)"Projectile Misc:",                     NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Firing Sound:",                   (char *)"Melee Weapons Use Magic Cost",         (char *)"Doesn't Pick Up Dropped Items",                                          (char *)"Flip Right-Facing Slash",              (char *)"Light Torches",                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_bait,                     NULL,                                     (char *)"Duration:",                        NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   (char *)"Bait Sprite:",                      NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Baiting Sound:",                  NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_potion,                   NULL,                                     (char *)"HP Regained:",                     (char *)"MP Regained:",                         NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"HP R. Is Percent",             (char *)"MP R. Is Percent",             (char *)"Removes Sword Jinxes",                                         (char *)"Removes Item Jinxes",          NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_whistle,                  NULL,                                     (char *)"Whirlwind Direction:",             (char *)"Warp Ring:",                           NULL,                                   NULL,                                   (char *)"Weapon Damage",           NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"One W.Wind Per Scr.",          (char *)"Has Damage",                   (char *)"Whirlwinds Reflect off Prism/Mirror Combos",                   NULL,                                   NULL,                                   (char *)"Whirlwind Sprite:",                 NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Music Sound:",                    NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_candle,                   (char *)"Damage:",                        (char *)"Damage to Player:",                NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Once Per Screen",              (char *)"Don't Provide Light",          (char *)"Fire Doesn't Hurt Player",                                     (char *)"Can Slash",                    (char *)"Temporary Light",              (char *)"Stab Sprite:",                      (char *)"Slash Sprite:",                        (char *)"Flame Sprite:",                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Firing Sound:",                   NULL,                                           NULL,                                                                             (char *)"Flip Right-Facing Slash",              NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_arrow,                    (char *)"Damage:",                        (char *)"Duration (0 = Infinite):",         NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Penetrate Enemies",            (char *)"Allow Item Pickup",            NULL,                                                                   (char *)"Pick Up Anything",             NULL,                                   (char *)"Arrow Sprite:",                     (char *)"Sparkle Sprite:",                      (char *)"Damaging Sparkle Sprite:",             NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Firing Sound:",                   NULL,                                           (char *)"Picks Up Keys",    NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_brang,                    (char *)"Damage:",                        (char *)"Range (0 = Infinite):",            NULL,                                           (char *)"Block Flags:",                 (char *)"Reflect Flags:",               NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"Corrected Animation",          (char *)"Directional Sprites",          (char *)"Do Not Return",                                                (char *)"Pick Up Anything",             (char *)"Drags Items",                  (char *)"Boomerang Sprite:",                 (char *)"Sparkle Sprite:",                      (char *)"Damaging Sparkle Sprite:",             NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Spinning Sound:",                 (char *)"Reflects Enemy Projectiles",           (char *)"Picks Up Keys", (char *)"Triggers 'Fire(Any)'",                 NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_sword,                    (char *)"Damage:",                        (char *)"Beam Hearts:",                     (char *)"Beam Damage:",                         NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"B.H. Is Percent",              (char *)"B.D. Is Percent",              (char *)"B. Penetrates Enemies",                                        (char *)"Can Slash",                    (char *)"Quick",                        (char *)"Stab Sprite:",                      (char *)"Slash Sprite:",                        (char *)"Beam Sprite:",                         NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char*)"Slash/Stab Sound",                 (char *)"Melee Weapons Use Magic Cost",         (char *)"Doesn't Pick Up Dropped Items",                                          (char *)"Flip Right-Facing Slash",              (char *)"Sword Beams Reflect off Prism/Mirror Combos",      (char *)"Walk slowly while charging",           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_whimsicalring,            (char *)"Damage Bonus:",                  (char *)"Chance (1 in n):",                 NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Whimsy Sound:",                   NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_perilring,                (char *)"Damage Divisor:",                (char *)"Maximum Hearts:",                  NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   (char *)"Divisor is Percentage Multiplier", NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_stompboots,               (char *)"Damage:",                        NULL,                                       NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_bow,                      (char *)"Arrow Speed:",                   NULL,                                       NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_script1,                  (char *)"W. Power:",                      (char *)"Step Speed:",                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Gfx Flip",                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_script2,                  (char *)"W. Power:",                      (char *)"Step Speed:",                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Gfx Flip",                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_script3,                  (char *)"W. Power:",                      (char *)"Step Speed:",                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Gfx Flip",                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_script4,                  (char *)"W. Power:",                      (char *)"Step Speed:",                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Gfx Flip",                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_script5,                  (char *)"W. Power:",                      (char *)"Step Speed:",                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Gfx Flip",                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_script6,                  (char *)"W. Power:",                      (char *)"Step Speed:",                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Gfx Flip",                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_script7,                  (char *)"W. Power:",                      (char *)"Step Speed:",                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Gfx Flip",                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_script8,                  (char *)"W. Power:",                      (char *)"Step Speed:",                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Gfx Flip",                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_script9,                  (char *)"W. Power:",                      (char *)"Step Speed:",                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Gfx Flip",                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_script10,                 (char *)"W. Power:",                      (char *)"Step Speed:",                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Gfx Flip",                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_custom1,                 NULL,                      NULL,                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_custom2,                 NULL,                      NULL,                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                 NULL,                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_custom3,                 NULL,                      NULL,                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                  NULL,                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_custom4,                 NULL,                      NULL,                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_custom5,                 NULL,                      NULL,                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_custom6,                 NULL,                      NULL,                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_custom7,                 NULL,                      NULL,                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_custom8,                 NULL,                     NULL,                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_custom9,                 NULL,                      NULL,                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_custom10,                NULL,                      NULL,                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_icerod,                  (char *)"W. Power:",                      (char *)"Step Speed:",                      NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Gfx Flip",                  NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_flippers,                 NULL,                                     (char *)"Dive Length:",                     (char *)"Dive Cooldown:",                       NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   (char *)"No Diving",                    (char *)"Cancellable Diving",           (char *)"Can Swim in Lava",                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	{ itype_raft,                    NULL,                      (char *)"Speed Modifier:", NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                  NULL,           NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           (char *)"Constant Script"                 },
	//itemclass                       power                                     misc1                                       misc2                                           misc3                                   misc4                                   misc5                              misc6                              misc7                              misc8                              misc9                                        misc10                                  flag1                                   flag2                                   flag3                                                                   flag4                                   flag5                                   wpn1                                         wpn2                                            wpn3                                            wpn4                                            wpn5                                            wpn6                                            wpn7                                            wpn8                                            wpn9                                            wpn10                                           action sound                               flag6,                                          flag7,                                                                            flag8,                                          flag9,                                                      flag10,                                         flag11.                                         flag12,                                         flag13,                                         flag14,                                         flag15,                                         flag16               },
	{ itype_atkring,                 NULL,                                     "Bonus Damage",                              "Damage Multiplier",                            NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL                 },
	{ itype_lantern,                 NULL,                                     "Shape",                                     "Range",                                        NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL                 },
	{ -1,                             NULL,                                     NULL,                                       NULL,                                           NULL,                                   NULL,                                   NULL,                              NULL,                              NULL,                              NULL,                              NULL,                                        NULL,                                   NULL,                                   NULL,                                   NULL,                                                                   NULL,                                   NULL,                                   NULL,                                        NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                      NULL,                                           NULL,                                                                             NULL,                                           NULL,                                                       NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL,                                           NULL                 }
};

ItemNameInfo defInfo =
{
	-1, "Power:", "Attributes[0]:", "Attributes[1]:", "Attributes[2]:",
	"Attributes[3]:", "Attributes[4]:","Attributes[5]:","Attributes[6]:",
	"Attributes[7]:","Attributes[8]:","Attributes[9]:", "Flags[0]",
	"Flags[1]", "Flags[2]", "Flags[3]", "Flags[4]", "Sprites[0]:",
	"Sprites[1]:","Sprites[2]:","Sprites[3]:","Sprites[4]:","Sprites[5]:",
	"Sprites[6]:","Sprites[7]:","Sprites[8]:","Sprites[9]:","UseSound",
	"Flags[5]", "Flags[6]", "Flags[7]", "Flags[8]", "Flags[9]", "Flags[10]",
	"Flags[11]","Flags[12]","Flags[13]", "Flags[14]","Constant Script"
};

std::map<int, ItemNameInfo *> *inamemap = NULL;

std::map<int, ItemNameInfo *> *getItemNameMap()
{
	if(inamemap == NULL)
	{
		inamemap = new std::map<int, ItemNameInfo *>();
		
		for(int i=0;; i++)
		{
			ItemNameInfo *inf = &inameinf[i];
			
			if(inf->iclass == -1)
				break;
				
			(*inamemap)[inf->iclass] = inf;
		}
	}
	
	return inamemap;
}

ItemEditorDialog::ItemEditorDialog(int index):
	local_itemref(itemsbuf[index]), itemname(item_string[index]), index(index),
	list_items(GUI::ListData::itemclass(true)),
	list_counters(GUI::ListData::counters()),
	list_sprites(GUI::ListData::miscsprites())
{}
//{

#define ATTR_WID 6_em
#define ATTR_LAB_WID 12_em
#define ACTION_LAB_WID 6_em
#define ACTION_FIELD_WID 6_em
#define FLAGS_WID 18_em

#define NUM_FIELD(member,_min,_max,wid) \
TextField( \
	type = GUI::TextField::type::INT_DECIMAL, width = wid, \
	low = _min, high = _max, val = local_itemref.member, \
	onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val) \
	{ \
		local_itemref.member = val; \
	})

#define ATTRIB_FIELD(member, index) \
Row( \
	l_attribs[index] = Label(textAlign = 2, width = ATTR_LAB_WID), \
	TextField(maxLength = 11, \
		type = GUI::TextField::type::INT_DECIMAL, width = ATTR_WID, \
		val = local_itemref.member, \
		onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val) \
		{ \
			local_itemref.member = val; \
		}) \
)

#define FLAG_CHECK(index, bit) \
l_flags[index] = Checkbox( \
	width = FLAGS_WID, \
	checked = (local_itemref.flags & bit), \
	onToggleFunc = [&](bool state) \
	{ \
		SETFLAG(local_itemref.flags,bit,state); \
	} \
)

#define SPRITE_DROP(ind, mem) \
Rows<2>( \
	Label(text = ("Sprites["#ind"]:"), hAlign = 1.0), \
	DropDownList( \
		maxwidth = 14_em, \
		data = list_sprites, \
		selectedValue = local_itemref.mem, \
		onSelectFunc = [&](int val) \
		{ \
			local_itemref.mem = val; \
		} \
	) \
)

//}

std::shared_ptr<GUI::Widget> ItemEditorDialog::view()
{
	using namespace GUI::Builder;
	using namespace GUI::Props;
	
	char titlebuf[256];
	sprintf(titlebuf, "Item Editor (%d): %s", index, itemname.c_str());
	window = Window(
		title = titlebuf,
		onEnter = message::OK,
		onClose = message::CANCEL,
		Column(
			Row(
				Rows<2>(padding = 0_px,
					Label(text = "Name:"),
					TextField(
						//width = 8_em,
						maxLength = 63,
						text = itemname,
						onValChangedFunc = [&](GUI::TextField::type,std::string_view str,int)
						{
							itemname = str;
							char buf[256];
							sprintf(buf, "Item Editor (%d): %s", index, itemname.c_str());
							window->setTitle(buf);
						}
					),
					Label(text = "Type:"),
					DropDownList(data = list_items,
						selectedValue = local_itemref.family,
						onSelectionChanged = message::ITEMCLASS
					)
				),
				Column(vAlign = 0.0, hAlign = 0.0, padding = 0_px,
					Checkbox(
						hAlign = 0.0,
						checked = (local_itemref.flags & ITEM_GAMEDATA),
						text = "Equipment Item",
						onToggleFunc = [&](bool state)
						{
							SETFLAG(local_itemref.flags,ITEM_GAMEDATA,state);
						}
					)
				)
			),
			TabPanel(
				TabRef(name = "Data", TabPanel(
					TabRef(name = "Attrib", Column(
						Columns<6>(padding = 0_px,
							Row(
								Label(width=ATTR_LAB_WID,textAlign=2,text="Level:"),
								NUM_FIELD(fam_type, 1, 255, ATTR_WID)
							),
							ATTRIB_FIELD(misc1,0),
							ATTRIB_FIELD(misc2,1),
							ATTRIB_FIELD(misc3,2),
							ATTRIB_FIELD(misc4,3),
							ATTRIB_FIELD(misc5,4),
							Row(
								l_power = Label(width=ATTR_LAB_WID,textAlign=2),
								NUM_FIELD(power, 0, 255, ATTR_WID)
							),
							ATTRIB_FIELD(misc6,5),
							ATTRIB_FIELD(misc7,6),
							ATTRIB_FIELD(misc8,7),
							ATTRIB_FIELD(misc9,8),
							ATTRIB_FIELD(misc10,9)
						)
					)),
					TabRef(name = "Flags", Row(
						Columns<9>(padding = 0_px,
							Checkbox(
								width = FLAGS_WID,
								checked = (local_itemref.flags & ITEM_EDIBLE),
								text = "Can Be Eaten By Enemies",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.flags,ITEM_EDIBLE,state);
								}
							),
							FLAG_CHECK(0,ITEM_FLAG1),
							FLAG_CHECK(1,ITEM_FLAG2),
							FLAG_CHECK(2,ITEM_FLAG3),
							FLAG_CHECK(3,ITEM_FLAG4),
							FLAG_CHECK(4,ITEM_FLAG5),
							FLAG_CHECK(5,ITEM_FLAG6),
							FLAG_CHECK(6,ITEM_FLAG7),
							FLAG_CHECK(7,ITEM_FLAG8),
							Checkbox(
								width = FLAGS_WID,
								checked = (local_itemref.flags & ITEM_SIDESWIM_DISABLED),
								text = "Disabled In Sideview Water",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.flags,ITEM_SIDESWIM_DISABLED,state);
								}
							),
							FLAG_CHECK(8,ITEM_FLAG9),
							FLAG_CHECK(9,ITEM_FLAG10),
							FLAG_CHECK(10,ITEM_FLAG11),
							FLAG_CHECK(11,ITEM_FLAG12),
							FLAG_CHECK(12,ITEM_FLAG13),
							FLAG_CHECK(13,ITEM_FLAG14),
							FLAG_CHECK(14,ITEM_FLAG15),
							FLAG_CHECK(15,ITEM_FLAG16)
						)
					)),
					TabRef(name = "Action", Columns<4>(
						Row(
							Label(text = "Cost:", textAlign = 2, width = ACTION_LAB_WID),
							TextField(
								val = local_itemref.magic,
								type = GUI::TextField::type::INT_DECIMAL,
								width = ACTION_FIELD_WID, high = 255,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.magic = val;
								}
							)
						),
						DropDownList(
							maxwidth = ACTION_FIELD_WID+ACTION_LAB_WID+4_spx,
							data = list_counters,
							selectedValue = local_itemref.cost_counter,
							onSelectFunc = [&](int val)
							{
								local_itemref.cost_counter = val;
							}
						),
						Row(
							Label(text = "Timer:", textAlign = 2, width = ACTION_LAB_WID),
							TextField(
								val = local_itemref.magiccosttimer,
								type = GUI::TextField::type::INT_DECIMAL,
								width = ACTION_FIELD_WID, high = 255,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.magiccosttimer = val;
								}
							)
						),
						Row(
							l_sfx = Label(textAlign = 2, width = ACTION_LAB_WID),
							TextField(
								val = local_itemref.usesound,
								type = GUI::TextField::type::INT_DECIMAL,
								width = ACTION_FIELD_WID, high = 255,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.usesound = val;
								}
							)
						),
						Checkbox(
							hAlign = 0.0,
							checked = (local_itemref.flags & ITEM_DOWNGRADE),
							text = "Remove Item When Used",
							onToggleFunc = [&](bool state)
							{
								SETFLAG(local_itemref.flags,ITEM_DOWNGRADE,state);
							}
						),
						Checkbox(
							hAlign = 0.0,
							checked = (local_itemref.flags & ITEM_VALIDATEONLY),
							text = "Only Validate Cost",
							onToggleFunc = [&](bool state)
							{
								SETFLAG(local_itemref.flags,ITEM_VALIDATEONLY,state);
							}
						)
					)),
					TabRef(name = "Pickup", Column(
						Rows<4>(
							//
							Label(text = "Counter:", hAlign = 1.0),
							DropDownList(
								maxwidth = 10_em,
								data = list_counters,
								selectedValue = local_itemref.count,
								onSelectFunc = [&](int val)
								{
									local_itemref.count = val;
								}
							),_d,_d,
							//
							Label(text = "Increase By:", hAlign = 1.0),
							TextField(
								val = ((local_itemref.amount & 0x4000) ? -1 : 1)*(local_itemref.amount & 0x3FFF),
								type = GUI::TextField::type::INT_DECIMAL,
								fitParent = true, high = 65535,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.amount &= 0x8000;
									local_itemref.amount |= ((val&0x3FFF)|(val<0?0x4000:0));
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.amount & 0x8000),
								text = "Gradual",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.amount,0x8000,state);
								}
							),_d,
							//
							Label(text = "Increase Max:", hAlign = 1.0),
							TextField(
								val = local_itemref.setmax,
								type = GUI::TextField::type::INT_DECIMAL,
								fitParent = true, low = -32768, high = 32767,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.setmax = val;
								}
							),
							Label(text = "But Not Above:", hAlign = 1.0),
							TextField(
								val = local_itemref.max,
								type = GUI::TextField::type::INT_DECIMAL,
								fitParent = true, high = 65535,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.max = val;
								}
							),
							//
							Label(text = "Sound:", hAlign = 1.0),
							TextField(
								val = local_itemref.playsound,
								type = GUI::TextField::type::INT_DECIMAL,
								fitParent = true, high = 255,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.playsound = val;
								}
							),_d,_d,
							//
							Label(text = "Hearts Required:", hAlign = 1.0),
							TextField(
								val = local_itemref.pickup_hearts,
								type = GUI::TextField::type::INT_DECIMAL,
								fitParent = true, high = 255,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.pickup_hearts = val;
								}
							),_d,_d
						),
						Column(
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.flags & ITEM_KEEPOLD),
								text = "Keep Lower Level Items",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.flags,ITEM_KEEPOLD,state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.flags & ITEM_GAINOLD),
								text = "Gain All Lower Level Items",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.flags,ITEM_GAINOLD,state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.flags & ITEM_COMBINE),
								text = "Upgrade When Collected Twice",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.flags,ITEM_COMBINE,state);
								}
							)
						),
						Row(
							Label(text = "String:"),
							TextField(
								val = local_itemref.pstring,
								type = GUI::TextField::type::INT_DECIMAL,
								fitParent = true, high = 65535,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.pstring = val;
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup_string_flags & itemdataPSTRING_ALWAYS),
								text = "Always",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup_string_flags,itemdataPSTRING_ALWAYS,state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup_string_flags & itemdataPSTRING_IP_HOLDUP),
								text = "Only Held",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup_string_flags,itemdataPSTRING_IP_HOLDUP,state);
								}
							)
						)
					)),
					TabRef(name = "P. Flags", Column(
						Row(
							Label(text = "Flag Behavior:"),
							DropDownList(
								maxwidth = 10_em,
								data = PFlagTypeList,
								selectedValue = local_itemref.pickupflag,
								onSelectFunc = [&](int val)
								{
									local_itemref.pickupflag = val;
								}
							)
						),
						Columns<8>(
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<0)),
								text = "Large Collision Rectangle (INTERNAL)",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<0),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<1)),
								text = "Hold Up Item",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<1),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<2)),
								text = "Sets Screen State ST_ITEM",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<2),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<3)),
								text = "Dummy Item",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<3),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<4)),
								text = "Shop Item (INTERNAL)",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<4),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<5)),
								text = "Pay for Info (INTERNAL)",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<5),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<6)),
								text = "Item Fades",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<6),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<7)),
								text = "Enemy Carries Item",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<7),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<8)),
								text = "Item Disappears",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<8),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<9)),
								text = "Big Triforce (INTERNAL)",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<9),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<10)),
								text = "Invisible",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<10),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<11)),
								text = "Triggers Screen State ST_SP_ITEM",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<11),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<12)),
								text = "Triggers Screen Secrets",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<12),state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<13)),
								text = "Always Grabbable",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.pickup,(1<<13),state);
								}
							),
							Checkbox(
								disabled = true,
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<14)),
								text = "--",
								onToggleFunc = [&](bool state)
								{
									//SETFLAG(local_itemref.pickup,(1<<14),state);
								}
							),
							Checkbox(
								disabled = true,
								hAlign = 0.0,
								checked = (local_itemref.pickup & (1<<15)),
								text = "--",
								onToggleFunc = [&](bool state)
								{
									//SETFLAG(local_itemref.pickup,(1<<15),state);
								}
							)
						)
					))
				)),
				TabRef(name = "Graphics", TabPanel(
					TabRef(name = "GFX", Row(
						Rows<2>(
							Label(text = "Flash CSet:", hAlign = 1.0),
							TextField(
								val = (local_itemref.csets>>4),
								type = GUI::TextField::type::INT_DECIMAL,
								width = ACTION_FIELD_WID, high = 16,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.csets &= 0x0F;
									local_itemref.csets |= val<<4;
								}
							),
							Label(text = "Animation Frames:", hAlign = 1.0),
							TextField(
								val = local_itemref.frames,
								type = GUI::TextField::type::INT_DECIMAL,
								width = ACTION_FIELD_WID, high = 255,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.frames = val;
								}
							),
							Label(text = "Animation Speed:", hAlign = 1.0),
							TextField(
								val = local_itemref.speed,
								type = GUI::TextField::type::INT_DECIMAL,
								width = ACTION_FIELD_WID, high = 255,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.speed = val;
								}
							),
							Label(text = "Initial Delay:", hAlign = 1.0),
							TextField(
								val = local_itemref.delay,
								type = GUI::TextField::type::INT_DECIMAL,
								width = ACTION_FIELD_WID, high = 255,
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.delay = val;
								}
							),
							Label(text = "Player Tile Modifier:", hAlign = 1.0),
							TextField(
								val = local_itemref.ltm,
								type = GUI::TextField::type::INT_DECIMAL,
								width = ACTION_FIELD_WID, low = (0-(NEWMAXTILES-1)), high = (NEWMAXTILES-1),
								onValChangedFunc = [&](GUI::TextField::type,std::string_view,int val)
								{
									local_itemref.ltm = val;
								}
							)
						),
						Column(
							SelTileSwatch(
								tile = local_itemref.tile,
								cset = (local_itemref.csets & 0x0F),
								onSelectFunc = [&](int t, int c)
								{
									local_itemref.tile = t;
									local_itemref.csets &= 0xF0;
									local_itemref.csets |= c&0x0F;
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.misc & 1),
								text = "Flash",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.misc,1,state);
								}
							),
							Checkbox(
								hAlign = 0.0,
								checked = (local_itemref.misc & 2),
								text = "2-Hand",
								onToggleFunc = [&](bool state)
								{
									SETFLAG(local_itemref.misc,2,state);
								}
							),
							DummyWidget() //!TODO Animated Preview
						)
					)),
					TabRef(name = "Sprites", Columns<5>(
						SPRITE_DROP(0,wpn),
						SPRITE_DROP(1,wpn2),
						SPRITE_DROP(2,wpn3),
						SPRITE_DROP(3,wpn4),
						SPRITE_DROP(4,wpn5),
						SPRITE_DROP(5,wpn6),
						SPRITE_DROP(6,wpn7),
						SPRITE_DROP(7,wpn8),
						SPRITE_DROP(8,wpn9),
						SPRITE_DROP(9,wpn10)
					)),
					TabRef(name = "Size", DummyWidget()),
					TabRef(name = "Weapon Size", DummyWidget())
				)),
				TabRef(name = "Scripts", TabPanel(
					TabRef(name = "Item", DummyWidget()),
					TabRef(name = "Weapon", DummyWidget())
				))
			),
			Row(
				vAlign = 1.0,
				spacing = 2_em,
				Button(
					focused = true,
					text = "OK",
					onClick = message::OK),
				Button(
					text = "Cancel",
					onClick = message::CANCEL)
			)
		)
	);
	loadItemClass();
	return window;
}

void ItemEditorDialog::loadItemClass()
{
	std::map<int, ItemNameInfo *> *nmap = getItemNameMap();
	std::map<int, ItemNameInfo *>::iterator it = nmap->find(local_itemref.family);
	ItemNameInfo *inf = NULL;
	
	if(it != nmap->end())
		inf = it->second;
	
	#define __SET(obj, mem) \
	obj->setText(inf ? (inf->mem ? inf->mem : defInfo.mem) : defInfo.mem);
	
	__SET(l_power, power);
	
	__SET(l_attribs[0], misc1);
	__SET(l_attribs[1], misc2);
	__SET(l_attribs[2], misc3);
	__SET(l_attribs[3], misc4);
	__SET(l_attribs[4], misc5);
	__SET(l_attribs[5], misc6);
	__SET(l_attribs[6], misc7);
	__SET(l_attribs[7], misc8);
	__SET(l_attribs[8], misc9);
	__SET(l_attribs[9], misc10);
	
	__SET(l_flags[0], flag1);
	__SET(l_flags[1], flag2);
	__SET(l_flags[2], flag3);
	__SET(l_flags[3], flag4);
	__SET(l_flags[4], flag5);
	__SET(l_flags[5], flag6);
	__SET(l_flags[6], flag7);
	__SET(l_flags[7], flag8);
	__SET(l_flags[8], flag9);
	__SET(l_flags[9], flag10);
	__SET(l_flags[10], flag11);
	__SET(l_flags[11], flag12);
	__SET(l_flags[12], flag13);
	__SET(l_flags[13], flag14);
	__SET(l_flags[14], flag15);
	__SET(l_flags[15], flag16);
	
	__SET(l_sfx, actionsnd);
}

bool ItemEditorDialog::handleMessage(const GUI::DialogMessage<message>& msg)
{
	switch(msg.message)
	{
		case message::ITEMCLASS:
		{
			local_itemref.family = int(msg.argument);
			loadItemClass();
			return false;
		}
		case message::OK:
			saved = false;
			itemsbuf[index] = local_itemref;
			strcpy(item_string[index], itemname.c_str());
			return true;

		case message::CANCEL:
		default:
			return true;
	}
}
