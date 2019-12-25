/* GnollHack 4.0	skills.h	$NHDT-Date: 1547255911 2019/01/12 01:18:31 $  $NHDT-Branch: GnollHack-3.6.2-beta01 $:$NHDT-Revision: 1.15 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985-1999. */
/*-Copyright (c) Pasi Kallinen, 2017. */
/* GnollHack may be freely redistributed.  See license for details. */

#ifndef SKILLS_H
#define SKILLS_H

/* Much of this code was taken from you.h.  It is now
 * in a separate file so it can be included in objects.c.
 */

enum p_skills {
    /* Code to denote that no skill is applicable */
    P_NONE = 0,

/* Weapon Skills -- Stephen White
 * Order matters and are used in macros.
 * Positive values denote hand-to-hand weapons or launchers.
 * Negative values denote ammunition or missiles.
 * Update weapon.c if you amend any skills.
 * Also used for oc_subtyp.
 */
 /*
    P_KNIFE              =  2,
	P_SHORT_SWORD        =  5,
	P_BROAD_SWORD        =  6,
	P_LONG_SWORD         =  7,
	P_TWO_HANDED_SWORD   =  8,
	P_SCIMITAR           =  9,
	P_SABER              = 10,
	P_MACE               = 12,
	P_MORNING_STAR       = 13,
	P_HAMMER			 = 15,
	P_TRIDENT            = 19,
	P_LANCE              = 20,
	P_DART               = 24,
	P_SHURIKEN			 = 25,
	P_BOOMERANG			 = 26,
	P_UNICORN_HORN       = 28,
	*/

    P_DAGGER             =  1,
    P_AXE                =  2,
    P_PICK_AXE           =  3,
    P_SWORD				 =  4,
    P_BLUDGEONING_WEAPON =  5, /* Heavy-shafted bludgeon */
    P_FLAIL              =  6, /* Two pieces hinged or chained together */
    P_QUARTERSTAFF       =  7, /* Long-shafted bludgeon */
    P_POLEARM            =  8, /* attack two or three steps away */
    P_SPEAR              =  9, /* includes javelin */
    P_BOW                = 10, /* launchers */
    P_SLING              = 11,
    P_CROSSBOW           = 12,
    P_THROWN_WEAPON      = 13, /* hand-thrown missiles */
    P_WHIP               = 14, /* flexible, one-handed */

    /* Spell Skills added by Larry Stewart-Zerba */
    P_ARCANE_SPELL       = 15,
	P_CLERIC_SPELL		 = 16,
	P_HEALING_SPELL      = 17,
    P_DIVINATION_SPELL   = 18,
	P_ABJURATION_SPELL	 = 19,
    P_MOVEMENT_SPELL     = 20,
    P_TRANSMUTATION_SPELL= 21,
	P_ENCHANTMENT_SPELL  = 22,
	P_CONJURATION_SPELL  = 23,
	P_NECROMANCY_SPELL	 = 24,

    /* Other types of combat */
    P_BARE_HANDED_COMBAT = 25, /* actually weaponless; gloves are ok */
	P_MARTIAL_ARTS		 = 26, /* actually weaponless; gloves are ok */
	P_TWO_WEAPON_COMBAT  = 27, /* pair of weapons, one in each hand */

	/* Non-combat skills */
	P_RIDING			 = 28,	/* how well you control your steed */
	P_DISARM_TRAP		 = 29,	/* disarming traps */
	
	P_NUM_SKILLS         = 30
};

//#define P_MARTIAL_ARTS P_BARE_HANDED_COMBAT /* Role distinguishes */

#define P_FIRST_WEAPON P_DAGGER
#define P_LAST_WEAPON P_WHIP

#define P_FIRST_SPELL P_ARCANE_SPELL
#define P_LAST_SPELL P_NECROMANCY_SPELL

#define P_FIRST_H_TO_H P_BARE_HANDED_COMBAT
#define P_LAST_H_TO_H P_TWO_WEAPON_COMBAT

#define P_FIRST_NONCOMBAT P_RIDING
#define P_LAST_NONCOMBAT P_DISARM_TRAP

/*
 * These are the standard weapon skill levels.  It is important that
 * the lowest "valid" skill be be 1.  The code calculates the
 * previous amount to practice by calling  practice_needed_to_advance()
 * with the current skill-1.  To work out for the UNSKILLED case,
 * a value of 0 needed.
 */
enum skill_levels {
    P_ISRESTRICTED = 0, /* unskilled and can't be advanced */
    P_UNSKILLED    = 1, /* unskilled so far but can be advanced */
    /* Skill levels Basic/Advanced/Expert had long been used by
       Heroes of Might and Magic (tm) and its sequels... */
    P_BASIC        = 2,
    P_SKILLED      = 3,
    P_EXPERT       = 4,
	P_MASTER	   = 5,		/* Martial arts only */
	P_GRAND_MASTER = 6		/* Martial arts only */
};

#define is_magic_skill(skill) ((skill) >= P_ARCANE_SPELL && (skill) <= P_NECROMANCY_SPELL)
#define is_martial_arts_skill(skill) ((skill) == P_MARTIAL_ARTS)
#define practice_needed_to_advance_for_normal_skill(level) ((level) * (level) * 20)
#define practice_needed_to_advance_for_martial_arts_skill(level) practice_needed_to_advance_for_normal_skill(level + 3)
#define practice_needed_to_advance(skill, level) (is_martial_arts_skill(skill) ? practice_needed_to_advance_for_martial_arts_skill(level) : ((is_magic_skill(skill) ? 3 : 1) * practice_needed_to_advance_for_normal_skill(level)))

/* The hero's skill in various weapons. */
struct skills {
    xchar skill;
    xchar max_skill;
    unsigned short advance;
};

#define P_SKILL(type) (u.weapon_skills[type].skill)
#define P_MAX_SKILL(type) (u.weapon_skills[type].max_skill)
#define P_ADVANCE(type) (u.weapon_skills[type].advance)
#define P_RESTRICTED(type) (u.weapon_skills[type].skill == P_ISRESTRICTED)

#define P_SKILL_LIMIT 60 /* Max number of skill advancements */

/* These roles qualify for a martial arts bonus */
#define martial_bonus() (P_SKILL(P_MARTIAL_ARTS) >= P_BASIC) // (Role_if(PM_SAMURAI) || Role_if(PM_MONK))


/* Initial skill matrix structure; used in u_init.c and weapon.c */
struct def_skill {
    xchar skill;
    xchar sklvl;
};

#endif /* SKILLS_H */
