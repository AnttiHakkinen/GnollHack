/* GnollHack 4.0 matcomps.c */
/* Copyright (c) Janne Gustafsson 2019.                           */
/* GnollHack may be freely redistributed.  See license for details. */

#include "hack.h"

struct materialcomponentlist matlists[] =
{
	{STRANGE_OBJECT,
	"",
	STRANGE_OBJECT,
	1,
	{NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_WISH,
	"Diamond, ruby, unicorn horn",
	STRANGE_OBJECT,
	1,
	{
		{DIAMOND, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
		{RUBY, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
 		{UNICORN_HORN, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
		NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}
	},

	{SPE_TIME_STOP,
	"Sapphire",
	STRANGE_OBJECT,
	2,
	{{SAPPHIRE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_ARMAGEDDON,
		"Black pearl, skull, deathly bone dagger",
		STRANGE_OBJECT,
		1,
		{
			{BLACK_PEARL, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED},
			{HUMAN_SKULL, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{BONE_DAGGER, NOT_APPLICABLE, 1, MATCOMP_DEATH_ENCHANTMENT_REQUIRED | MATCOMP_NOT_SPENT | MATCOMP_NOT_CURSED},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{SPE_BLACK_BLADE_OF_DISASTER,
	"Black opal, jet stone",
	STRANGE_OBJECT,
	2,
	{{BLACK_OPAL, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED}, {JET, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_DISINTEGRATE,
	"Black opal",
	STRANGE_OBJECT,
	2,
	{{BLACK_OPAL, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_IDENTIFY,
	"Jade stone",
	STRANGE_OBJECT,
	2,
	{{JADE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_TOUCH_OF_DEATH,
		"Human skull, death cap",
		STRANGE_OBJECT,
		1,
		{
			{HUMAN_SKULL, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{DEATH_CAP, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{SPE_FINGER_OF_DEATH,
		"Human skull, death cap, bone",
		STRANGE_OBJECT,
		1,
		{
			{HUMAN_SKULL, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			{DEATH_CAP, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			{BONE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{SPE_DEATHSPELL,
		"Human skull, death cap, sporal powder",
		STRANGE_OBJECT,
		1,
		{
			{HUMAN_SKULL, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			{DEATH_CAP, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{SPE_POLYMORPH,
	"Spider silk, bat guano",
	STRANGE_OBJECT,
	1,
	{{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, {CLUMP_OF_BAT_GUANO, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_FULL_HEALING,
		"Ginseng, healing mushroom, powder",
		STRANGE_OBJECT,
		1,
		{
			{GINSENG_ROOT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{HEALING_MUSHROOM, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{SPE_DIG,
	"Bat guano",
	STRANGE_OBJECT,
	3,
	{{CLUMP_OF_BAT_GUANO, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_MAGIC_MAPPING,
	"Feather, bat guano",
	STRANGE_OBJECT,
	1,
	{{FEATHER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, {CLUMP_OF_BAT_GUANO, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_CREATE_FAMILIAR,
	"Spider silk",
	STRANGE_OBJECT,
	1,
	{{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, {HOLY_SYMBOL, NOT_APPLICABLE, 1, MATCOMP_NOT_SPENT}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_BLESS,
	"Spider silk, holy symbol",
	STRANGE_OBJECT,
	1,
	{{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED}, {HOLY_SYMBOL, NOT_APPLICABLE, 1, MATCOMP_NOT_SPENT | MATCOMP_NOT_CURSED}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_ENCHANT_WEAPON,
	"Garnet stone",
	STRANGE_OBJECT,
	1,
	{{GARNET, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_ENCHANT_ARMOR,
	"Jasper stone",
	STRANGE_OBJECT,
	1,
	{{JASPER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_PROTECT_WEAPON,
	"Fluorite stone",
	STRANGE_OBJECT,
	1,
	{{FLUORITE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_PROTECT_ARMOR,
	"Agate stone",
	STRANGE_OBJECT,
	1,
	{{AGATE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{SPE_NEGATE_UNDEATH,
	"Clove of garlic, holy symbol",
	STRANGE_OBJECT,
	2,
	{{CLOVE_OF_GARLIC, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED}, {HOLY_SYMBOL, NOT_APPLICABLE, 1, MATCOMP_NOT_SPENT | MATCOMP_NOT_CURSED}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP}},

	{ SPE_NEGATE_MAGIC_RESISTANCE,
		"Nugget of orichalcum ore",
		STRANGE_OBJECT,
		2,
		{
			{NUGGET_OF_ORICHALCUM_ORE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		} 
	},

	{ SPE_TELEPORT_AWAY,
		"Heap of sporal powder",
		STRANGE_OBJECT,
		5,
		{
			{HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_BANISH_DEMON,
	"Silver arrow, holy symbol",
	STRANGE_OBJECT,
	2,
	{{SILVER_ARROW, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED}, {HOLY_SYMBOL, NOT_APPLICABLE, 1, MATCOMP_NOT_SPENT | MATCOMP_NOT_CURSED}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_RESURRECTION,
	"Garlic, ginseng, holy symbol",
	STRANGE_OBJECT,
	1,
	{{CLOVE_OF_GARLIC, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED}, {GINSENG_ROOT, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED}, {HOLY_SYMBOL, NOT_APPLICABLE, 1, MATCOMP_NOT_SPENT | MATCOMP_NOT_CURSED}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_GLOBE_OF_INVULNERABILITY,
	"Pearl",
	STRANGE_OBJECT,
	2,
	{{PEARL, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_DIVINE_INTERVENTION,
	"Blessed pearl, spider silk",
	STRANGE_OBJECT,
	1,
	{{PEARL, NOT_APPLICABLE, 1, MATCOMP_BLESSED_REQUIRED}, {THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_CANCELLATION,
	"Nugget of orichalcum ore",
	STRANGE_OBJECT,
	2,
	{{NUGGET_OF_ORICHALCUM_ORE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_CALL_DEMOGORGON,
	"Cursed ape corpse, mandrake",
	STRANGE_OBJECT,
	1,
	{{CORPSE, PM_APE, 1, MATCOMP_CURSED_REQUIRED}, {MANDRAKE_ROOT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_WATER_BREATHING,
	"Pearl",
	STRANGE_OBJECT,
	5,
	{{PEARL, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_WATER_WALKING,
	"Raven feather",
	STRANGE_OBJECT,
	5,
	{{FEATHER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_SLEEP,
		"Thread of spider silk",
		STRANGE_OBJECT,
		1,
		{
			{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		} 
	},

	{ SPE_MASS_SLEEP,
		"Spider silk, sporal powder",
		STRANGE_OBJECT,
		1,
		{
			{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		} 
	},

	{ SPE_FEAR,
	"Mandrake root",
	STRANGE_OBJECT,
	5,
	{{MANDRAKE_ROOT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_MASS_FEAR,
	"Mandrake root, sporal powder",
	STRANGE_OBJECT,
	5,
	{{MANDRAKE_ROOT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},  {HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_CHARM_MONSTER,
	"Magic mushroom",
	STRANGE_OBJECT,
	5,
	{{MAGIC_MUSHROOM, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_SPHERE_OF_CHARMING,
	"Magic mushroom, sporal powder",
	STRANGE_OBJECT,
	5,
	{{MAGIC_MUSHROOM, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, {HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_MASS_CHARM,
	"Magic mushroom, 2 heaps of powder",
	STRANGE_OBJECT,
	5,
	{{MAGIC_MUSHROOM, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, {HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 2, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_DOMINATE_MONSTER,
	"Magic mushroom, wolfsbane",
	STRANGE_OBJECT,
	1,
	{{MAGIC_MUSHROOM, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, {SPRIG_OF_WOLFSBANE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP} },

	{ SPE_SPHERE_OF_DOMINATION,
	"Magic mushroom, wolfsbane, powder",
	STRANGE_OBJECT,
	1,
		{
			{MAGIC_MUSHROOM, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{SPRIG_OF_WOLFSBANE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_MASS_DOMINATION,
	"Magic mushroom, wolfsbane, 2 powder",
	STRANGE_OBJECT,
	1,
		{
			{MAGIC_MUSHROOM, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{SPRIG_OF_WOLFSBANE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 2, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},


	{ SPE_CREATE_GOLD_GOLEM,
	"200 gold pieces, spider silk",
	STRANGE_OBJECT,
	1,
		{
			{GOLD_PIECE, NOT_APPLICABLE, 200, MATCOMP_NO_FLAGS},
			{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CREATE_GLASS_GOLEM,
	"One piece of each type of glass",
	STRANGE_OBJECT,
	1,
		{
			{LAST_GEM + 1, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{LAST_GEM + 2, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{LAST_GEM + 3, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{LAST_GEM + 4, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			{LAST_GEM + 5, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{LAST_GEM + 6, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{LAST_GEM + 7, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{LAST_GEM + 8, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CREATE_GEMSTONE_GOLEM,
	"Jade, agate, obsidian, fluorite",
	STRANGE_OBJECT,
	1,
		{
			{JADE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{AGATE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{OBSIDIAN, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{FLUORITE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CREATE_CLAY_GOLEM,
	"10 clay pebbles, spider silk",
	STRANGE_OBJECT,
	1,
		{
			{CLAY_PEBBLE, NOT_APPLICABLE, 10, MATCOMP_BLESSED_REQUIRED}, 
			{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CREATE_STONE_GOLEM,
	"10 stone pebbles, spider silk",
	STRANGE_OBJECT,
	1,
		{
			{STONE_PEBBLE, NOT_APPLICABLE, 10, MATCOMP_NO_FLAGS},
			{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CREATE_IRON_GOLEM,
	"3 nuggets of iron, spider silk",
	STRANGE_OBJECT,
	1,
		{
			{NUGGET_OF_IRON_ORE, NOT_APPLICABLE, 3, MATCOMP_NO_FLAGS}, 
			{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		} 
	},

	{ SPE_CREATE_SILVER_GOLEM,
	"3 nuggets of silver, spider silk",
	STRANGE_OBJECT,
	1,
		{
			{NUGGET_OF_SILVER_ORE, NOT_APPLICABLE, 3, MATCOMP_NO_FLAGS},
			{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CREATE_PAPER_GOLEM,
	"Blank scroll, spider silk",
	STRANGE_OBJECT,
	1,
		{
			{SCR_BLANK_PAPER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CREATE_WOOD_GOLEM,
	"Piece of wood, spider silk",
	STRANGE_OBJECT,
	1,
		{
			{PIECE_OF_WOOD, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS}, 
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		} 
	},

	{ SPE_CREATE_MONSTER,
	"Spider silk",
	STRANGE_OBJECT,
	1,
		{
			{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_HEAVENLY_WARRIOR,
	"Opal",
	STRANGE_OBJECT,
	2,
		{
			{OPAL, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_GUARDIAN_ANGEL,
	"Opal, feather",
	STRANGE_OBJECT,
	2,
		{
			{OPAL, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED},
			{FEATHER, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CALL_HIERARCH_MODRON,
	"Modronite cube",
	STRANGE_OBJECT,
	2,
		{
			{MODRONITE_CUBE, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_DIVINE_MOUNT,
	"Opal, apple",
	STRANGE_OBJECT,
	2,
		{
			{OPAL, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED},
			{APPLE, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_HEAVENLY_ARMY,
	"Blessed opal",
	STRANGE_OBJECT,
	1,
		{
			{OPAL, NOT_APPLICABLE, 1, MATCOMP_BLESSED_REQUIRED},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_TOUCH_OF_PETRIFICATION,
	"10 rocks, 2 clumps of bat guano",
	STRANGE_OBJECT,
	1,
		{
			{ROCK, NOT_APPLICABLE, 10, MATCOMP_NO_FLAGS},
			{CLUMP_OF_BAT_GUANO, NOT_APPLICABLE, 2, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_FLESH_TO_STONE,
	"15 rocks, 3 clumps of bat guano",
	STRANGE_OBJECT,
	1,
		{
			{ROCK, NOT_APPLICABLE, 15, MATCOMP_NO_FLAGS},
			{CLUMP_OF_BAT_GUANO, NOT_APPLICABLE, 3, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_COLD_ENCHANT_ITEM,
	"Nugget of iron ore",
	STRANGE_OBJECT,
	2,
		{
			{NUGGET_OF_IRON_ORE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_FIRE_ENCHANT_ITEM,
	"Pinch of sulfurous ash",
	STRANGE_OBJECT,
	2,
		{
			{PINCH_OF_SULFUROUS_ASH, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_LIGHTNING_ENCHANT_ITEM,
	"Nugget of copper ore",
	STRANGE_OBJECT,
	2,
		{
			{NUGGET_OF_COPPER_ORE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_DEATH_ENCHANT_ITEM,
	"Human skull, mandrake root",
	STRANGE_OBJECT,
	1,
		{
			{HUMAN_SKULL, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{MANDRAKE_ROOT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_TELEPATHY,
	"Panther cap",
	STRANGE_OBJECT,
	3,
		{
			{PANTHER_CAP, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_DETECT_TRAPS,
	"Bat guano",
	STRANGE_OBJECT,
	1,
		{
			{CLUMP_OF_BAT_GUANO, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_MIRROR_IMAGE,
	"White glass, mirror",
	STRANGE_OBJECT,
	3,
		{
			{LAST_GEM + 1, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{MIRROR, NOT_APPLICABLE, 1, MATCOMP_NOT_SPENT},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_MASS_CONFLICT,
	"Wolfsbane, mandrake, sporal powder",
	STRANGE_OBJECT,
	1,
		{
			{SPRIG_OF_WOLFSBANE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{MANDRAKE_ROOT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_STINKING_CLOUD,
	"Bat guano, egg",
	STRANGE_OBJECT,
	3,
		{
			{CLUMP_OF_BAT_GUANO, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{EGG, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CALL_GHOUL,
	"Bat guano, corpse",
	STRANGE_OBJECT,
	1,
		{
			{CLUMP_OF_BAT_GUANO, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{CORPSE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_GREAT_YENDORIAN_SUMMONING,
	"Jacinth stone, sporal powder",
	STRANGE_OBJECT,
	1,
		{
			{JACINTH, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_HASTE_SELF,
	"Heap of sporal powder",
	STRANGE_OBJECT,
	1,
		{
			{HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_LIGHT,
	"Tallow candle",
	STRANGE_OBJECT,
	2,
		{
			{TALLOW_CANDLE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_HEALING,
	"Ginseng root",
	STRANGE_OBJECT,
	5,
		{
			{GINSENG_ROOT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_EXTRA_HEALING,
	"Ginseng root, sporal power",
	STRANGE_OBJECT,
	3,
		{
			{GINSENG_ROOT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_GREATER_HEALING,
	"Ginseng, healing mushroom",
	STRANGE_OBJECT,
	2,
		{
			{GINSENG_ROOT, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED},
			{HEALING_MUSHROOM, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_REMOVE_CURSE,
	"Ginseng root, mandrake root",
	STRANGE_OBJECT,
	1,
		{
			{GINSENG_ROOT, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED},
			{MANDRAKE_ROOT, NOT_APPLICABLE, 1, MATCOMP_NOT_CURSED},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_MAGIC_ARROW,
	"Arrow",
	STRANGE_OBJECT,
	10,
		{
			{ARROW, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_MAGIC_MISSILE,
	"Dart",
	STRANGE_OBJECT,
	10,
		{
			{DART, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_FORCE_BOLT,
	"Crossbow bolt",
	STRANGE_OBJECT,
	10,
		{
			{CROSSBOW_BOLT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_LIGHTNING_BOLT,
	"Nugget of copper ore",
	STRANGE_OBJECT,
	10,
		{
			{NUGGET_OF_COPPER_ORE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_THUNDERSTORM,
	"Nugget of copper ore, sporal powder",
	STRANGE_OBJECT,
	5,
		{
			{NUGGET_OF_COPPER_ORE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},


	{ SPE_FIRE_BOLT,
	"Pinch of sulfurous ash",
	STRANGE_OBJECT,
	10,
		{
			{PINCH_OF_SULFUROUS_ASH, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},
		
	{ SPE_FIREBALL,
	"Pinch of sulfurous ash, piece of wood",
	STRANGE_OBJECT,
	5,
		{
			{PINCH_OF_SULFUROUS_ASH, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{PIECE_OF_WOOD, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_FIRE_STORM,
	"Sulfurous ash, wood, feather",
	STRANGE_OBJECT,
	3,
		{
			{PINCH_OF_SULFUROUS_ASH, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{PIECE_OF_WOOD, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{FEATHER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_METEOR_SWARM,
	"2 pinches of sulfurous ash, 4 rocks",
	STRANGE_OBJECT,
	1,
		{
			{PINCH_OF_SULFUROUS_ASH, NOT_APPLICABLE, 2, MATCOMP_NO_FLAGS},
			{ROCK, NOT_APPLICABLE, 4, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_DETECT_TREASURE,
	"Nugget of gold ore",
	STRANGE_OBJECT,
	2,
		{
			{NUGGET_OF_GOLD_ORE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CONE_OF_COLD,
	"Nugget of iron ore",
	STRANGE_OBJECT,
	3,
		{
			{NUGGET_OF_IRON_ORE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_ICE_STORM,
	"Nugget of iron ore, feather",
	STRANGE_OBJECT,
	3,
		{
			{NUGGET_OF_IRON_ORE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{FEATHER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_DETECT_MONSTERS,
	"Bat guano",
	STRANGE_OBJECT,
	3,
		{
			{CLUMP_OF_BAT_GUANO, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_MAGE_ARMOR,
	"Jade stone",
	STRANGE_OBJECT,
	5,
		{
			{JADE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CONFUSE_MONSTER,
	"Sprig of wolfsbane",
	STRANGE_OBJECT,
	3,
		{
			{SPRIG_OF_WOLFSBANE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_WIZARD_LOCK,
	"Thread of spider silk",
	STRANGE_OBJECT,
	5,
		{
			{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_KNOCK,
	"Piece of wood",
	STRANGE_OBJECT,
	5,
		{
			{PIECE_OF_WOOD, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION_FROM_CURSES,
	"Blessed clove of garlic",
	STRANGE_OBJECT,
	5,
		{
			{CLOVE_OF_GARLIC, NOT_APPLICABLE, 1, MATCOMP_BLESSED_REQUIRED},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION_FROM_LIGHTNING,
	"Pinch of sulfurous ash",
	STRANGE_OBJECT,
	5,
		{
			{PINCH_OF_SULFUROUS_ASH, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION_FROM_COLD,
	"Feather",
	STRANGE_OBJECT,
	5,
		{
			{FEATHER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION_FROM_FIRE,
	"Clump of bat guano",
	STRANGE_OBJECT,
	5,
		{
			{CLUMP_OF_BAT_GUANO, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION_FROM_ACID,
	"Bone",
	STRANGE_OBJECT,
	5,
		{
			{BONE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION,
	"Nugget of iron ore",
	STRANGE_OBJECT,
	5,
		{
			{NUGGET_OF_IRON_ORE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION_FROM_LYCANTHROPY,
	"Sprig of wolfsbane",
	STRANGE_OBJECT,
	5,
		{
			{SPRIG_OF_WOLFSBANE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION_FROM_DEATH_MAGIC,
	"Human skull",
	STRANGE_OBJECT,
	5,
		{
			{HUMAN_SKULL, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION_FROM_DISINTEGRATION,
	"Pinch of sulfurous ash",
	STRANGE_OBJECT,
	5,
		{
			{PINCH_OF_SULFUROUS_ASH, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION_FROM_PETRIFICATION,
	"Lizard corpse",
	STRANGE_OBJECT,
	5,
		{
			{CORPSE, PM_LIZARD, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION_FROM_SICKNESS,
	"Ginseng root",
	STRANGE_OBJECT,
	5,
		{
			{GINSENG_ROOT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_TURN_UNDEAD,
	"Clove of garlic",
	STRANGE_OBJECT,
	5,
		{
			{CLOVE_OF_GARLIC, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_INVISIBILITY,
	"Piece of black glass",
	STRANGE_OBJECT,
	3,
		{
			{LAST_GEM + 7, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_ANIMATE_WATER,
	"Potion of water",
	STRANGE_OBJECT,
	5,
		{
			{POT_WATER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_ANIMATE_FIRE,
	"Pinch of sulfurous ash",
	STRANGE_OBJECT,
	5,
		{
			{PINCH_OF_SULFUROUS_ASH, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_ANIMATE_EARTH,
	"5 rocks",
	STRANGE_OBJECT,
	1,
		{
			{ROCK, NOT_APPLICABLE, 5, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_ANIMATE_AIR,
	"Feather",
	STRANGE_OBJECT,
	5,
		{
			{FEATHER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CURE_SICKNESS,
	"Ginseng root",
	STRANGE_OBJECT,
	3,
		{
			{GINSENG_ROOT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_DETECT_FOOD,
	"Bone",
	STRANGE_OBJECT,
	2,
		{
			{BONE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_CURE_BLINDNESS,
	"Ginseng root",
	STRANGE_OBJECT,
	5,
		{
			{GINSENG_ROOT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_DETECT_UNSEEN,
	"Heap of sporal powder",
	STRANGE_OBJECT,
	3,
		{
			{HEAP_OF_SPORAL_POWDER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_FORBID_SUMMONING,
	"Spider silk, garlic",
	STRANGE_OBJECT,
	5,
		{
			{THREAD_OF_SPIDER_SILK, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{CLOVE_OF_GARLIC, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_FAITHFUL_HOUND,
	"Bone, tripe ration",
	STRANGE_OBJECT,
	1,
		{
			{BONE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{TRIPE_RATION, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_LEVITATION,
	"Feather",
	STRANGE_OBJECT,
	5,
		{
			{FEATHER, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION_FROM_POISON,
	"Sprig of wolfsbane",
	STRANGE_OBJECT,
	5,
		{
			{SPRIG_OF_WOLFSBANE, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_PROTECTION_FROM_LIFE_DRAINING,
	"Clove of garlic",
	STRANGE_OBJECT,
	3,
		{
			{CLOVE_OF_GARLIC, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_SLOW_MONSTER,
	"Clump of bat guano",
	STRANGE_OBJECT,
	5,
		{
			{CLUMP_OF_BAT_GUANO, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP,
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

	{ SPE_STONE_TO_FLESH,
	"Ginseng, garlic",
	STRANGE_OBJECT,
	3,
		{
			{GINSENG_ROOT, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			{CLOVE_OF_GARLIC, NOT_APPLICABLE, 1, MATCOMP_NO_FLAGS},
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},



	/* Array terminator, uses spellsgained */
	{STRANGE_OBJECT,
	"",
	STRANGE_OBJECT,
	0,
		{
			NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP, NO_MATCOMP
		}
	},

};


void matcomps_init();

/* dummy routine used to force linkage */
void
matcomps_init()
{
    return;
}

/*matcomps.c*/
