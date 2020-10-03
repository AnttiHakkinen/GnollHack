
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "lev_comp.y"

/* NetHack 3.6  lev_comp.y	$NHDT-Date: 1543371691 2018/11/28 02:21:31 $  $NHDT-Branch: NetHack-3.6.2-beta01 $:$NHDT-Revision: 1.22 $ */
/*      Copyright (c) 1989 by Jean-Christophe Collet */
/* NetHack may be freely redistributed.  See license for details. */

/*
 * This file contains the Level Compiler code
 * It may handle special mazes & special room-levels
 */

/* In case we're using bison in AIX.  This definition must be
 * placed before any other C-language construct in the file
 * excluding comments and preprocessor directives (thanks IBM
 * for this wonderful feature...).
 *
 * Note: some cpps barf on this 'undefined control' (#pragma).
 * Addition of the leading space seems to prevent barfage for now,
 * and AIX will still see the directive.
 */
#ifdef _AIX
 #pragma alloca         /* keep leading space! */
#endif

#define SPEC_LEV    /* for USE_OLDARGS (sp_lev.h) */
#include "hack.h"
#include "sp_lev.h"

#define ERR             (-1)
/* many types of things are put in chars for transference to NetHack.
 * since some systems will use signed chars, limit everybody to the
 * same number for portability.
 */
#define MAX_OF_TYPE     128

#define MAX_NESTED_IFS   20
#define MAX_SWITCH_CASES 20

#define New(type) \
        (type *) memset((genericptr_t) alloc(sizeof (type)), 0, sizeof (type))
#define NewTab(type, size)      (type **) alloc(sizeof (type *) * size)
#define Free(ptr)               free((genericptr_t) ptr)

extern void VDECL(lc_error, (const char *, ...));
extern void VDECL(lc_warning, (const char *, ...));
extern void FDECL(yyerror, (const char *));
extern void FDECL(yywarning, (const char *));
extern int NDECL(yylex);
int NDECL(yyparse);

extern int FDECL(get_floor_type, (CHAR_P));
extern int FDECL(get_room_type, (char *));
extern int FDECL(get_trap_type, (char *));
extern int FDECL(get_monster_id, (char *,CHAR_P));
extern int FDECL(get_object_id, (char *,CHAR_P));
extern boolean FDECL(check_monster_char, (CHAR_P));
extern boolean FDECL(check_object_char, (CHAR_P));
extern char FDECL(what_map_char, (CHAR_P));
extern void FDECL(scan_map, (char *, sp_lev *));
extern void FDECL(add_opcode, (sp_lev *, int, genericptr_t));
extern genericptr_t FDECL(get_last_opcode_data1, (sp_lev *, int));
extern genericptr_t FDECL(get_last_opcode_data2, (sp_lev *, int, int));
extern boolean FDECL(check_subrooms, (sp_lev *));
extern boolean FDECL(write_level_file, (char *,sp_lev *));
extern struct opvar *FDECL(set_opvar_int, (struct opvar *, long));
extern void VDECL(add_opvars, (sp_lev *, const char *, ...));
extern void FDECL(start_level_def, (sp_lev * *, char *));

extern struct lc_funcdefs *FDECL(funcdef_new, (long,char *));
extern void FDECL(funcdef_free_all, (struct lc_funcdefs *));
extern struct lc_funcdefs *FDECL(funcdef_defined, (struct lc_funcdefs *,
                                                   char *, int));
extern char *FDECL(funcdef_paramtypes, (struct lc_funcdefs *));
extern char *FDECL(decode_parm_str, (char *));

extern struct lc_vardefs *FDECL(vardef_new, (long,char *));
extern void FDECL(vardef_free_all, (struct lc_vardefs *));
extern struct lc_vardefs *FDECL(vardef_defined, (struct lc_vardefs *,
                                                 char *, int));

extern void NDECL(break_stmt_start);
extern void FDECL(break_stmt_end, (sp_lev *));
extern void FDECL(break_stmt_new, (sp_lev *, long));

extern void FDECL(splev_add_from, (sp_lev *, sp_lev *));

extern void FDECL(check_vardef_type, (struct lc_vardefs *, char *, long));
extern void FDECL(vardef_used, (struct lc_vardefs *, char *));
extern struct lc_vardefs *FDECL(add_vardef_type, (struct lc_vardefs *,
                                                  char *, long));

extern int FDECL(reverse_jmp_opcode, (int));

struct coord {
    long x;
    long y;
};

struct forloopdef {
    char *varname;
    long jmp_point;
};
static struct forloopdef forloop_list[MAX_NESTED_IFS];
static short n_forloops = 0;


sp_lev *splev = NULL;

static struct opvar *if_list[MAX_NESTED_IFS];

static short n_if_list = 0;

unsigned int max_x_map, max_y_map;
int obj_containment = 0;

int in_container_obj = 0;

/* integer value is possibly an inconstant value (eg. dice notation
   or a variable) */
int is_inconstant_number = 0;

int in_switch_statement = 0;
static struct opvar *switch_check_jump = NULL;
static struct opvar *switch_default_case = NULL;
static struct opvar *switch_case_list[MAX_SWITCH_CASES];
static long switch_case_value[MAX_SWITCH_CASES];
int n_switch_case_list = 0;

int allow_break_statements = 0;
struct lc_breakdef *break_list = NULL;

extern struct lc_vardefs *vardefs; /* variable definitions */


struct lc_vardefs *function_tmp_var_defs = NULL;
extern struct lc_funcdefs *function_definitions;
struct lc_funcdefs *curr_function = NULL;
struct lc_funcdefs_parm * curr_function_param = NULL;
int in_function_definition = 0;
sp_lev *function_splev_backup = NULL;

extern int fatal_error;
extern int got_errors;
extern int line_number;
extern const char *fname;

extern char curr_token[512];



/* Line 189 of yacc.c  */
#line 223 "lev_comp.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CHAR = 258,
     INTEGER = 259,
     BOOLEAN = 260,
     PERCENT = 261,
     SPERCENT = 262,
     MINUS_INTEGER = 263,
     PLUS_INTEGER = 264,
     MAZE_GRID_ID = 265,
     SOLID_FILL_ID = 266,
     MINES_ID = 267,
     ROGUELEV_ID = 268,
     MESSAGE_ID = 269,
     MAZE_ID = 270,
     LEVEL_ID = 271,
     LEV_INIT_ID = 272,
     TILESET_ID = 273,
     GEOMETRY_ID = 274,
     NOMAP_ID = 275,
     OBJECT_ID = 276,
     COBJECT_ID = 277,
     MONSTER_ID = 278,
     TRAP_ID = 279,
     DOOR_ID = 280,
     DRAWBRIDGE_ID = 281,
     object_ID = 282,
     monster_ID = 283,
     terrain_ID = 284,
     MAZEWALK_ID = 285,
     WALLIFY_ID = 286,
     REGION_ID = 287,
     SPECIAL_REGION_ID = 288,
     SPECIAL_LEVREGION_ID = 289,
     SPECIAL_REGION_TYPE = 290,
     NAMING_ID = 291,
     NAMING_TYPE = 292,
     FILLING = 293,
     IRREGULAR = 294,
     JOINED = 295,
     ALTAR_ID = 296,
     ANVIL_ID = 297,
     NPC_ID = 298,
     LADDER_ID = 299,
     STAIR_ID = 300,
     NON_DIGGABLE_ID = 301,
     NON_PASSWALL_ID = 302,
     ROOM_ID = 303,
     PORTAL_ID = 304,
     TELEPRT_ID = 305,
     BRANCH_ID = 306,
     LEV = 307,
     MINERALIZE_ID = 308,
     CORRIDOR_ID = 309,
     GOLD_ID = 310,
     ENGRAVING_ID = 311,
     FOUNTAIN_ID = 312,
     THRONE_ID = 313,
     MODRON_PORTAL_ID = 314,
     POOL_ID = 315,
     SINK_ID = 316,
     NONE = 317,
     RAND_CORRIDOR_ID = 318,
     DOOR_STATE = 319,
     LIGHT_STATE = 320,
     CURSE_TYPE = 321,
     ENGRAVING_TYPE = 322,
     KEYTYPE_ID = 323,
     LEVER_ID = 324,
     DIRECTION = 325,
     RANDOM_TYPE = 326,
     RANDOM_TYPE_BRACKET = 327,
     A_REGISTER = 328,
     ALIGNMENT = 329,
     LEFT_OR_RIGHT = 330,
     CENTER = 331,
     TOP_OR_BOT = 332,
     ALTAR_TYPE = 333,
     UP_OR_DOWN = 334,
     ACTIVE_OR_INACTIVE = 335,
     MODRON_PORTAL_TYPE = 336,
     NPC_TYPE = 337,
     FOUNTAIN_TYPE = 338,
     SPECIAL_OBJECT_TYPE = 339,
     CMAP_TYPE = 340,
     FLOOR_TYPE = 341,
     FLOOR_TYPE_ID = 342,
     FLOOR_ID = 343,
     FLOOR_MAIN_TYPE = 344,
     FLOOR_MAIN_TYPE_ID = 345,
     ELEMENTAL_ENCHANTMENT_TYPE = 346,
     EXCEPTIONALITY_TYPE = 347,
     EXCEPTIONALITY_ID = 348,
     ELEMENTAL_ENCHANTMENT_ID = 349,
     ENCHANTMENT_ID = 350,
     CHARGES_ID = 351,
     SPECIAL_QUALITY_ID = 352,
     SPEFLAGS_ID = 353,
     SUBROOM_ID = 354,
     NAME_ID = 355,
     FLAGS_ID = 356,
     FLAG_TYPE = 357,
     MON_ATTITUDE = 358,
     MON_ALERTNESS = 359,
     SUBTYPE_ID = 360,
     MON_APPEARANCE = 361,
     ROOMDOOR_ID = 362,
     IF_ID = 363,
     ELSE_ID = 364,
     TERRAIN_ID = 365,
     HORIZ_OR_VERT = 366,
     REPLACE_TERRAIN_ID = 367,
     LOCATION_SUBTYPE_ID = 368,
     DOOR_SUBTYPE = 369,
     EXIT_ID = 370,
     SHUFFLE_ID = 371,
     QUANTITY_ID = 372,
     BURIED_ID = 373,
     LOOP_ID = 374,
     FOR_ID = 375,
     TO_ID = 376,
     SWITCH_ID = 377,
     CASE_ID = 378,
     BREAK_ID = 379,
     DEFAULT_ID = 380,
     ERODED_ID = 381,
     TRAPPED_STATE = 382,
     RECHARGED_ID = 383,
     INVIS_ID = 384,
     GREASED_ID = 385,
     INDESTRUCTIBLE_ID = 386,
     FEMALE_ID = 387,
     WAITFORU_ID = 388,
     CANCELLED_ID = 389,
     REVIVED_ID = 390,
     AVENGE_ID = 391,
     FLEEING_ID = 392,
     BLINDED_ID = 393,
     PARALYZED_ID = 394,
     STUNNED_ID = 395,
     CONFUSED_ID = 396,
     SEENTRAPS_ID = 397,
     ALL_ID = 398,
     MONTYPE_ID = 399,
     OBJTYPE_ID = 400,
     TERTYPE_ID = 401,
     TERTYPE2_ID = 402,
     LEVER_EFFECT_TYPE = 403,
     SWITCHABLE_ID = 404,
     CONTINUOUSLY_USABLE_ID = 405,
     TARGET_ID = 406,
     TRAPTYPE_ID = 407,
     EFFECT_FLAG_ID = 408,
     GRAVE_ID = 409,
     ERODEPROOF_ID = 410,
     FUNCTION_ID = 411,
     MSG_OUTPUT_TYPE = 412,
     COMPARE_TYPE = 413,
     UNKNOWN_TYPE = 414,
     rect_ID = 415,
     fillrect_ID = 416,
     line_ID = 417,
     randline_ID = 418,
     grow_ID = 419,
     selection_ID = 420,
     flood_ID = 421,
     rndcoord_ID = 422,
     circle_ID = 423,
     ellipse_ID = 424,
     filter_ID = 425,
     complement_ID = 426,
     gradient_ID = 427,
     GRADIENT_TYPE = 428,
     LIMITED = 429,
     HUMIDITY_TYPE = 430,
     STRING = 431,
     MAP_ID = 432,
     NQSTRING = 433,
     VARSTRING = 434,
     CFUNC = 435,
     CFUNC_INT = 436,
     CFUNC_STR = 437,
     CFUNC_COORD = 438,
     CFUNC_REGION = 439,
     VARSTRING_INT = 440,
     VARSTRING_INT_ARRAY = 441,
     VARSTRING_STRING = 442,
     VARSTRING_STRING_ARRAY = 443,
     VARSTRING_VAR = 444,
     VARSTRING_VAR_ARRAY = 445,
     VARSTRING_COORD = 446,
     VARSTRING_COORD_ARRAY = 447,
     VARSTRING_REGION = 448,
     VARSTRING_REGION_ARRAY = 449,
     VARSTRING_MAPCHAR = 450,
     VARSTRING_MAPCHAR_ARRAY = 451,
     VARSTRING_MONST = 452,
     VARSTRING_MONST_ARRAY = 453,
     VARSTRING_OBJ = 454,
     VARSTRING_OBJ_ARRAY = 455,
     VARSTRING_SEL = 456,
     VARSTRING_SEL_ARRAY = 457,
     METHOD_INT = 458,
     METHOD_INT_ARRAY = 459,
     METHOD_STRING = 460,
     METHOD_STRING_ARRAY = 461,
     METHOD_VAR = 462,
     METHOD_VAR_ARRAY = 463,
     METHOD_COORD = 464,
     METHOD_COORD_ARRAY = 465,
     METHOD_REGION = 466,
     METHOD_REGION_ARRAY = 467,
     METHOD_MAPCHAR = 468,
     METHOD_MAPCHAR_ARRAY = 469,
     METHOD_MONST = 470,
     METHOD_MONST_ARRAY = 471,
     METHOD_OBJ = 472,
     METHOD_OBJ_ARRAY = 473,
     METHOD_SEL = 474,
     METHOD_SEL_ARRAY = 475,
     DICE = 476
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 151 "lev_comp.y"

    long    i;
    char    *map;
    struct {
        long room;
        long wall;
        long door;
    } corpos;
    struct {
        long area;
        long x1;
        long y1;
        long x2;
        long y2;
    } lregn;
    struct {
        long x;
        long y;
    } crd;
    struct {
        long ter;
        long lit;
    } terr;
    struct {
        long height;
        long width;
    } sze;
    struct {
        long die;
        long num;
    } dice;
    struct {
        long cfunc;
        char *varstr;
    } meth;



/* Line 214 of yacc.c  */
#line 519 "lev_comp.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 531 "lev_comp.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1180

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  239
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  180
/* YYNRULES -- Number of rules.  */
#define YYNRULES  469
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1031

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   476

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   234,   238,     2,
     178,   179,   232,   230,   176,   231,   236,   233,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   177,     2,
       2,   235,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   180,     2,   181,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   182,   237,   183,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    11,    15,    19,    25,
      31,    37,    41,    58,    62,    63,    66,    67,    70,    71,
      74,    76,    78,    79,    83,    87,    89,    90,    93,    97,
      99,   101,   103,   105,   107,   109,   111,   113,   115,   117,
     119,   121,   123,   125,   127,   129,   131,   133,   135,   137,
     139,   141,   143,   145,   147,   149,   151,   153,   155,   157,
     159,   161,   163,   165,   167,   169,   171,   173,   175,   177,
     179,   181,   183,   185,   187,   189,   191,   193,   195,   197,
     199,   201,   203,   205,   207,   209,   211,   213,   215,   217,
     219,   221,   223,   225,   227,   229,   231,   233,   235,   237,
     239,   241,   243,   245,   247,   249,   251,   253,   257,   261,
     267,   271,   277,   283,   289,   293,   297,   303,   309,   315,
     323,   331,   339,   345,   347,   351,   353,   357,   359,   363,
     365,   369,   371,   375,   377,   381,   383,   387,   388,   389,
     398,   403,   405,   406,   408,   410,   416,   420,   421,   422,
     432,   433,   436,   437,   443,   444,   449,   451,   454,   456,
     463,   464,   468,   469,   476,   477,   482,   483,   488,   490,
     491,   496,   500,   502,   506,   510,   516,   522,   530,   535,
     536,   549,   550,   565,   566,   569,   575,   577,   583,   585,
     591,   593,   599,   601,   612,   619,   621,   623,   625,   627,
     629,   633,   635,   637,   638,   642,   646,   650,   654,   656,
     664,   670,   672,   674,   676,   678,   682,   683,   689,   694,
     695,   699,   701,   703,   705,   707,   710,   712,   714,   716,
     718,   720,   724,   728,   732,   734,   736,   740,   742,   744,
     746,   750,   754,   755,   761,   764,   765,   769,   771,   775,
     777,   781,   785,   787,   789,   793,   795,   797,   799,   803,
     805,   807,   809,   813,   817,   821,   825,   829,   833,   837,
     839,   845,   853,   859,   868,   870,   874,   880,   886,   894,
     902,   909,   915,   916,   919,   925,   929,   941,   948,   949,
     953,   955,   959,   963,   967,   971,   973,   975,   979,   983,
     987,   991,   995,   999,  1001,  1003,  1005,  1007,  1011,  1015,
    1017,  1023,  1033,  1039,  1043,  1047,  1053,  1063,  1069,  1075,
    1076,  1089,  1090,  1092,  1100,  1104,  1112,  1118,  1124,  1130,
    1136,  1140,  1146,  1154,  1164,  1166,  1168,  1170,  1172,  1174,
    1175,  1178,  1180,  1184,  1186,  1188,  1190,  1191,  1195,  1197,
    1198,  1202,  1204,  1206,  1208,  1210,  1212,  1214,  1216,  1218,
    1220,  1222,  1226,  1228,  1230,  1235,  1237,  1239,  1244,  1246,
    1248,  1253,  1255,  1260,  1266,  1268,  1272,  1274,  1278,  1280,
    1282,  1287,  1297,  1299,  1301,  1306,  1308,  1314,  1316,  1318,
    1323,  1325,  1327,  1333,  1335,  1337,  1339,  1344,  1346,  1348,
    1354,  1356,  1358,  1360,  1364,  1366,  1368,  1372,  1374,  1379,
    1383,  1387,  1391,  1395,  1399,  1403,  1405,  1407,  1411,  1413,
    1417,  1418,  1420,  1422,  1424,  1426,  1430,  1431,  1433,  1435,
    1438,  1441,  1446,  1453,  1458,  1465,  1472,  1479,  1486,  1489,
    1496,  1505,  1514,  1525,  1540,  1543,  1545,  1549,  1551,  1555,
    1557,  1559,  1561,  1563,  1565,  1567,  1569,  1571,  1573,  1575,
    1577,  1579,  1581,  1583,  1585,  1587,  1589,  1591,  1593,  1604
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     240,     0,    -1,    -1,   241,    -1,   242,    -1,   242,   241,
      -1,   243,   250,   252,    -1,    16,   177,   184,    -1,    15,
     177,   184,   176,     3,    -1,    17,   177,    11,   176,   350,
      -1,    17,   177,    10,   176,     3,    -1,    17,   177,    13,
      -1,    17,   177,    12,   176,     3,   176,     3,   176,     5,
     176,     5,   176,   380,   176,   249,   248,    -1,    18,   177,
     410,    -1,    -1,   176,   174,    -1,    -1,   176,   387,    -1,
      -1,   176,     3,    -1,     5,    -1,    71,    -1,    -1,   101,
     177,   251,    -1,   102,   176,   251,    -1,   102,    -1,    -1,
     254,   252,    -1,   182,   252,   183,    -1,   295,    -1,   244,
      -1,   245,    -1,   364,    -1,   363,    -1,   361,    -1,   362,
      -1,   365,    -1,   366,    -1,   339,    -1,   297,    -1,   260,
      -1,   259,    -1,   353,    -1,   309,    -1,   331,    -1,   368,
      -1,   369,    -1,   341,    -1,   342,    -1,   343,    -1,   367,
      -1,   275,    -1,   285,    -1,   287,    -1,   291,    -1,   289,
      -1,   272,    -1,   282,    -1,   268,    -1,   271,    -1,   334,
      -1,   344,    -1,   316,    -1,   332,    -1,   319,    -1,   325,
      -1,   354,    -1,   349,    -1,   337,    -1,   296,    -1,   355,
      -1,   356,    -1,   357,    -1,   358,    -1,   302,    -1,   300,
      -1,   348,    -1,   352,    -1,   351,    -1,   335,    -1,   336,
      -1,   338,    -1,   330,    -1,   333,    -1,   194,    -1,   196,
      -1,   198,    -1,   200,    -1,   202,    -1,   204,    -1,   206,
      -1,   208,    -1,   210,    -1,   193,    -1,   195,    -1,   197,
      -1,   199,    -1,   201,    -1,   203,    -1,   205,    -1,   207,
      -1,   209,    -1,   255,    -1,   256,    -1,   187,    -1,   187,
      -1,   256,    -1,   116,   177,   255,    -1,   257,   235,   399,
      -1,   257,   235,   165,   177,   408,    -1,   257,   235,   398,
      -1,   257,   235,   415,   177,   392,    -1,   257,   235,   414,
     177,   394,    -1,   257,   235,   413,   177,   396,    -1,   257,
     235,   387,    -1,   257,   235,   390,    -1,   257,   235,   182,
     266,   183,    -1,   257,   235,   182,   265,   183,    -1,   257,
     235,   182,   264,   183,    -1,   257,   235,   415,   177,   182,
     263,   183,    -1,   257,   235,   414,   177,   182,   262,   183,
      -1,   257,   235,   413,   177,   182,   261,   183,    -1,   257,
     235,   182,   267,   183,    -1,   397,    -1,   261,   176,   397,
      -1,   395,    -1,   262,   176,   395,    -1,   393,    -1,   263,
     176,   393,    -1,   391,    -1,   264,   176,   391,    -1,   388,
      -1,   265,   176,   388,    -1,   399,    -1,   266,   176,   399,
      -1,   398,    -1,   267,   176,   398,    -1,    -1,    -1,   156,
     186,   178,   269,   403,   179,   270,   253,    -1,   186,   178,
     406,   179,    -1,   115,    -1,    -1,     6,    -1,     6,    -1,
     180,   399,   158,   399,   181,    -1,   180,   399,   181,    -1,
      -1,    -1,   122,   276,   180,   386,   181,   277,   182,   278,
     183,    -1,    -1,   279,   278,    -1,    -1,   123,   411,   177,
     280,   252,    -1,    -1,   125,   177,   281,   252,    -1,   124,
      -1,   236,   236,    -1,   121,    -1,   120,   258,   235,   399,
     283,   399,    -1,    -1,   284,   286,   253,    -1,    -1,   119,
     180,   386,   181,   288,   253,    -1,    -1,   274,   177,   290,
     254,    -1,    -1,   108,   274,   292,   293,    -1,   253,    -1,
      -1,   253,   294,   109,   253,    -1,    14,   177,   398,    -1,
      63,    -1,    63,   177,   411,    -1,    63,   177,    71,    -1,
      54,   177,   298,   176,   298,    -1,    54,   177,   298,   176,
     411,    -1,   178,     4,   176,    70,   176,   313,   179,    -1,
     371,   273,   176,   380,    -1,    -1,    99,   177,   299,   176,
     306,   176,   308,   372,   375,   377,   301,   253,    -1,    -1,
      48,   177,   299,   176,   305,   176,   307,   176,   308,   372,
     375,   377,   303,   253,    -1,    -1,   176,     5,    -1,   178,
       4,   176,     4,   179,    -1,    71,    -1,   178,     4,   176,
       4,   179,    -1,    71,    -1,   178,   317,   176,   318,   179,
      -1,    71,    -1,   178,     4,   176,     4,   179,    -1,    71,
      -1,   107,   177,   310,   176,   379,   176,   311,   176,   313,
     314,    -1,    25,   177,   379,   176,   408,   314,    -1,     5,
      -1,    71,    -1,   312,    -1,    71,    -1,    70,    -1,    70,
     237,   312,    -1,     4,    -1,    71,    -1,    -1,   314,   176,
     315,    -1,   113,   177,   114,    -1,    68,   177,   396,    -1,
      97,   177,     4,    -1,    20,    -1,    19,   177,   317,   176,
     318,   304,   185,    -1,    19,   177,   387,   304,   185,    -1,
      75,    -1,    76,    -1,    77,    -1,    76,    -1,    23,   177,
     321,    -1,    -1,    23,   177,   321,   320,   253,    -1,   394,
     176,   387,   322,    -1,    -1,   322,   176,   323,    -1,   398,
      -1,   103,    -1,   104,    -1,   382,    -1,   106,   398,    -1,
     132,    -1,   129,    -1,   134,    -1,   135,    -1,   136,    -1,
     137,   177,   386,    -1,   138,   177,   386,    -1,   139,   177,
     386,    -1,   140,    -1,   141,    -1,   142,   177,   324,    -1,
     133,    -1,   184,    -1,   143,    -1,   184,   237,   324,    -1,
      21,   177,   327,    -1,    -1,    22,   177,   327,   326,   253,
      -1,   396,   328,    -1,    -1,   328,   176,   329,    -1,    66,
      -1,   144,   177,   394,    -1,   412,    -1,   100,   177,   398,
      -1,   117,   177,   386,    -1,   118,    -1,    65,    -1,   126,
     177,   386,    -1,   155,    -1,    64,    -1,   127,    -1,   128,
     177,   386,    -1,   129,    -1,   130,    -1,   387,    -1,    94,
     177,    91,    -1,    93,   177,    92,    -1,    95,   177,   386,
      -1,    96,   177,   386,    -1,    97,   177,   386,    -1,    98,
     177,   386,    -1,    68,   177,   396,    -1,   131,    -1,    24,
     177,   370,   176,   387,    -1,    26,   177,   387,   176,    70,
     176,   379,    -1,    30,   177,   387,   176,    70,    -1,    30,
     177,   387,   176,    70,   176,     5,   248,    -1,    31,    -1,
      31,   177,   408,    -1,    44,   177,   387,   176,    79,    -1,
      45,   177,   387,   176,    79,    -1,    45,   177,   417,   176,
     417,   176,    79,    -1,    49,   177,   417,   176,   417,   176,
     184,    -1,    50,   177,   417,   176,   417,   340,    -1,    51,
     177,   417,   176,   417,    -1,    -1,   176,    79,    -1,    57,
     177,   408,   176,    83,    -1,    58,   177,   408,    -1,    59,
     177,   387,   176,   151,   177,   387,   176,    81,   176,    80,
      -1,    69,   177,   387,   176,   148,   345,    -1,    -1,   345,
     176,   346,    -1,    80,    -1,   144,   177,   394,    -1,   145,
     177,   396,    -1,   146,   177,   350,    -1,   147,   177,   350,
      -1,   149,    -1,   150,    -1,   151,   177,   387,    -1,   152,
     177,   370,    -1,   113,   177,   347,    -1,    87,   177,   378,
      -1,   153,   177,     4,    -1,    97,   177,     4,    -1,     4,
      -1,    81,    -1,   114,    -1,    83,    -1,    61,   177,   408,
      -1,    60,   177,   408,    -1,     3,    -1,   178,     3,   176,
     380,   179,    -1,   112,   177,   390,   176,   392,   176,   392,
     176,     7,    -1,   110,   177,   408,   176,   392,    -1,    46,
     177,   390,    -1,    47,   177,   390,    -1,    36,   177,   184,
     176,    37,    -1,    36,   177,   184,   176,    37,   176,   144,
     177,   394,    -1,    33,   177,   390,   176,    35,    -1,    34,
     177,   417,   176,    35,    -1,    -1,    32,   177,   390,   176,
     380,   176,   371,   372,   375,   377,   359,   360,    -1,    -1,
     253,    -1,    41,   177,   387,   176,   381,   176,   383,    -1,
      42,   177,   387,    -1,    88,   177,   408,   176,    89,   176,
      86,    -1,   105,   177,   408,   176,     4,    -1,    43,   177,
      82,   176,   387,    -1,   154,   177,   387,   176,   398,    -1,
     154,   177,   387,   176,    71,    -1,   154,   177,   387,    -1,
      55,   177,   399,   176,   387,    -1,    56,   177,   387,   176,
     416,   176,   398,    -1,    53,   177,   386,   176,   386,   176,
     386,   176,   386,    -1,    53,    -1,   184,    -1,    71,    -1,
     184,    -1,    71,    -1,    -1,   176,   373,    -1,   374,    -1,
     374,   176,   373,    -1,    38,    -1,    39,    -1,    40,    -1,
      -1,    90,   177,   376,    -1,    89,    -1,    -1,    87,   177,
     378,    -1,    86,    -1,    64,    -1,    71,    -1,    65,    -1,
      71,    -1,    74,    -1,   384,    -1,    71,    -1,    74,    -1,
     384,    -1,    73,   177,    71,    -1,    78,    -1,    71,    -1,
      73,   180,     4,   181,    -1,   184,    -1,   195,    -1,   196,
     180,   399,   181,    -1,   399,    -1,   388,    -1,   167,   178,
     408,   179,    -1,   199,    -1,   200,   180,   399,   181,    -1,
     178,     4,   176,     4,   179,    -1,    71,    -1,    72,   389,
     181,    -1,   175,    -1,   175,   176,   389,    -1,   391,    -1,
     201,    -1,   202,   180,   399,   181,    -1,   178,     4,   176,
       4,   176,     4,   176,     4,   179,    -1,   393,    -1,   203,
      -1,   204,   180,   399,   181,    -1,     3,    -1,   178,     3,
     176,   380,   179,    -1,   395,    -1,   205,    -1,   206,   180,
     399,   181,    -1,   184,    -1,     3,    -1,   178,     3,   176,
     184,   179,    -1,    71,    -1,   397,    -1,   207,    -1,   208,
     180,   399,   181,    -1,   184,    -1,     3,    -1,   178,     3,
     176,   184,   179,    -1,    71,    -1,    84,    -1,   385,    -1,
     398,   236,   385,    -1,     4,    -1,   409,    -1,   178,     8,
     179,    -1,   193,    -1,   194,   180,   399,   181,    -1,   399,
     230,   399,    -1,   399,   231,   399,    -1,   399,   232,   399,
      -1,   399,   233,   399,    -1,   399,   234,   399,    -1,   178,
     399,   179,    -1,   189,    -1,   190,    -1,   257,   177,   400,
      -1,   401,    -1,   402,   176,   401,    -1,    -1,   402,    -1,
     399,    -1,   398,    -1,   404,    -1,   405,   176,   404,    -1,
      -1,   405,    -1,   387,    -1,   160,   390,    -1,   161,   390,
      -1,   162,   387,   176,   387,    -1,   163,   387,   176,   387,
     176,   399,    -1,   164,   178,   408,   179,    -1,   164,   178,
     312,   176,   408,   179,    -1,   170,   178,     7,   176,   408,
     179,    -1,   170,   178,   408,   176,   408,   179,    -1,   170,
     178,   392,   176,   408,   179,    -1,   166,   387,    -1,   168,
     178,   387,   176,   399,   179,    -1,   168,   178,   387,   176,
     399,   176,    38,   179,    -1,   169,   178,   387,   176,   399,
     176,   399,   179,    -1,   169,   178,   387,   176,   399,   176,
     399,   176,    38,   179,    -1,   172,   178,   173,   176,   178,
     399,   231,   399,   246,   179,   176,   387,   247,   179,    -1,
     171,   407,    -1,   209,    -1,   178,   408,   179,    -1,   407,
      -1,   407,   238,   408,    -1,   229,    -1,    85,    -1,     4,
      -1,     8,    -1,     9,    -1,     4,    -1,     8,    -1,     9,
      -1,     4,    -1,   409,    -1,    27,    -1,    21,    -1,    28,
      -1,    23,    -1,    29,    -1,   110,    -1,    67,    -1,    71,
      -1,   418,    -1,    52,   178,     4,   176,     4,   176,     4,
     176,     4,   179,    -1,   178,     4,   176,     4,   176,     4,
     176,     4,   179,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   283,   283,   284,   287,   288,   291,   314,   319,   341,
     354,   366,   372,   401,   408,   411,   418,   422,   429,   432,
     439,   440,   444,   447,   454,   458,   465,   468,   474,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   559,   560,   561,   564,   565,   568,   584,   590,
     596,   602,   608,   614,   620,   626,   632,   642,   652,   662,
     672,   682,   692,   704,   709,   716,   721,   728,   733,   740,
     744,   750,   755,   762,   766,   772,   776,   783,   805,   782,
     819,   874,   881,   884,   890,   897,   901,   910,   914,   909,
     977,   978,   982,   981,   995,   994,  1009,  1019,  1020,  1023,
    1061,  1060,  1095,  1094,  1125,  1124,  1157,  1156,  1182,  1193,
    1192,  1220,  1226,  1231,  1236,  1243,  1250,  1259,  1267,  1279,
    1278,  1302,  1301,  1323,  1326,  1332,  1342,  1348,  1357,  1363,
    1368,  1374,  1379,  1385,  1396,  1402,  1403,  1406,  1407,  1410,
    1414,  1420,  1421,  1425,  1431,  1439,  1444,  1449,  1457,  1464,
    1472,  1480,  1481,  1484,  1485,  1488,  1493,  1492,  1506,  1513,
    1520,  1528,  1533,  1539,  1545,  1551,  1557,  1562,  1567,  1572,
    1577,  1582,  1587,  1592,  1597,  1602,  1607,  1613,  1620,  1629,
    1633,  1646,  1655,  1654,  1672,  1682,  1688,  1696,  1702,  1707,
    1712,  1717,  1722,  1727,  1732,  1737,  1742,  1753,  1759,  1764,
    1769,  1774,  1779,  1784,  1789,  1794,  1799,  1804,  1809,  1814,
    1821,  1827,  1856,  1861,  1869,  1875,  1881,  1888,  1895,  1905,
    1915,  1930,  1941,  1944,  1950,  1956,  1962,  1968,  1975,  1981,
    1989,  1995,  2000,  2005,  2010,  2015,  2021,  2027,  2032,  2037,
    2042,  2047,  2052,  2059,  2059,  2059,  2059,  2062,  2068,  2074,
    2079,  2086,  2093,  2099,  2105,  2111,  2115,  2121,  2127,  2138,
    2137,  2169,  2172,  2178,  2185,  2191,  2197,  2203,  2209,  2213,
    2218,  2225,  2231,  2238,  2242,  2249,  2257,  2260,  2270,  2274,
    2277,  2283,  2287,  2294,  2298,  2302,  2309,  2312,  2318,  2325,
    2328,  2334,  2340,  2341,  2344,  2345,  2348,  2349,  2350,  2356,
    2357,  2358,  2364,  2365,  2368,  2377,  2382,  2389,  2400,  2406,
    2410,  2414,  2421,  2431,  2438,  2442,  2448,  2452,  2460,  2464,
    2471,  2481,  2494,  2498,  2505,  2515,  2524,  2535,  2539,  2546,
    2556,  2567,  2576,  2586,  2592,  2596,  2603,  2613,  2624,  2633,
    2643,  2647,  2654,  2655,  2661,  2665,  2669,  2673,  2681,  2690,
    2694,  2698,  2702,  2706,  2710,  2713,  2720,  2729,  2762,  2763,
    2766,  2767,  2770,  2774,  2781,  2788,  2799,  2802,  2810,  2814,
    2818,  2822,  2826,  2831,  2835,  2839,  2844,  2849,  2854,  2858,
    2863,  2868,  2872,  2876,  2881,  2885,  2892,  2898,  2902,  2908,
    2915,  2916,  2919,  2920,  2921,  2924,  2928,  2932,  2936,  2942,
    2943,  2946,  2947,  2950,  2951,  2954,  2955,  2958,  2962,  2988
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "INTEGER", "BOOLEAN", "PERCENT",
  "SPERCENT", "MINUS_INTEGER", "PLUS_INTEGER", "MAZE_GRID_ID",
  "SOLID_FILL_ID", "MINES_ID", "ROGUELEV_ID", "MESSAGE_ID", "MAZE_ID",
  "LEVEL_ID", "LEV_INIT_ID", "TILESET_ID", "GEOMETRY_ID", "NOMAP_ID",
  "OBJECT_ID", "COBJECT_ID", "MONSTER_ID", "TRAP_ID", "DOOR_ID",
  "DRAWBRIDGE_ID", "object_ID", "monster_ID", "terrain_ID", "MAZEWALK_ID",
  "WALLIFY_ID", "REGION_ID", "SPECIAL_REGION_ID", "SPECIAL_LEVREGION_ID",
  "SPECIAL_REGION_TYPE", "NAMING_ID", "NAMING_TYPE", "FILLING",
  "IRREGULAR", "JOINED", "ALTAR_ID", "ANVIL_ID", "NPC_ID", "LADDER_ID",
  "STAIR_ID", "NON_DIGGABLE_ID", "NON_PASSWALL_ID", "ROOM_ID", "PORTAL_ID",
  "TELEPRT_ID", "BRANCH_ID", "LEV", "MINERALIZE_ID", "CORRIDOR_ID",
  "GOLD_ID", "ENGRAVING_ID", "FOUNTAIN_ID", "THRONE_ID",
  "MODRON_PORTAL_ID", "POOL_ID", "SINK_ID", "NONE", "RAND_CORRIDOR_ID",
  "DOOR_STATE", "LIGHT_STATE", "CURSE_TYPE", "ENGRAVING_TYPE",
  "KEYTYPE_ID", "LEVER_ID", "DIRECTION", "RANDOM_TYPE",
  "RANDOM_TYPE_BRACKET", "A_REGISTER", "ALIGNMENT", "LEFT_OR_RIGHT",
  "CENTER", "TOP_OR_BOT", "ALTAR_TYPE", "UP_OR_DOWN", "ACTIVE_OR_INACTIVE",
  "MODRON_PORTAL_TYPE", "NPC_TYPE", "FOUNTAIN_TYPE", "SPECIAL_OBJECT_TYPE",
  "CMAP_TYPE", "FLOOR_TYPE", "FLOOR_TYPE_ID", "FLOOR_ID",
  "FLOOR_MAIN_TYPE", "FLOOR_MAIN_TYPE_ID", "ELEMENTAL_ENCHANTMENT_TYPE",
  "EXCEPTIONALITY_TYPE", "EXCEPTIONALITY_ID", "ELEMENTAL_ENCHANTMENT_ID",
  "ENCHANTMENT_ID", "CHARGES_ID", "SPECIAL_QUALITY_ID", "SPEFLAGS_ID",
  "SUBROOM_ID", "NAME_ID", "FLAGS_ID", "FLAG_TYPE", "MON_ATTITUDE",
  "MON_ALERTNESS", "SUBTYPE_ID", "MON_APPEARANCE", "ROOMDOOR_ID", "IF_ID",
  "ELSE_ID", "TERRAIN_ID", "HORIZ_OR_VERT", "REPLACE_TERRAIN_ID",
  "LOCATION_SUBTYPE_ID", "DOOR_SUBTYPE", "EXIT_ID", "SHUFFLE_ID",
  "QUANTITY_ID", "BURIED_ID", "LOOP_ID", "FOR_ID", "TO_ID", "SWITCH_ID",
  "CASE_ID", "BREAK_ID", "DEFAULT_ID", "ERODED_ID", "TRAPPED_STATE",
  "RECHARGED_ID", "INVIS_ID", "GREASED_ID", "INDESTRUCTIBLE_ID",
  "FEMALE_ID", "WAITFORU_ID", "CANCELLED_ID", "REVIVED_ID", "AVENGE_ID",
  "FLEEING_ID", "BLINDED_ID", "PARALYZED_ID", "STUNNED_ID", "CONFUSED_ID",
  "SEENTRAPS_ID", "ALL_ID", "MONTYPE_ID", "OBJTYPE_ID", "TERTYPE_ID",
  "TERTYPE2_ID", "LEVER_EFFECT_TYPE", "SWITCHABLE_ID",
  "CONTINUOUSLY_USABLE_ID", "TARGET_ID", "TRAPTYPE_ID", "EFFECT_FLAG_ID",
  "GRAVE_ID", "ERODEPROOF_ID", "FUNCTION_ID", "MSG_OUTPUT_TYPE",
  "COMPARE_TYPE", "UNKNOWN_TYPE", "rect_ID", "fillrect_ID", "line_ID",
  "randline_ID", "grow_ID", "selection_ID", "flood_ID", "rndcoord_ID",
  "circle_ID", "ellipse_ID", "filter_ID", "complement_ID", "gradient_ID",
  "GRADIENT_TYPE", "LIMITED", "HUMIDITY_TYPE", "','", "':'", "'('", "')'",
  "'['", "']'", "'{'", "'}'", "STRING", "MAP_ID", "NQSTRING", "VARSTRING",
  "CFUNC", "CFUNC_INT", "CFUNC_STR", "CFUNC_COORD", "CFUNC_REGION",
  "VARSTRING_INT", "VARSTRING_INT_ARRAY", "VARSTRING_STRING",
  "VARSTRING_STRING_ARRAY", "VARSTRING_VAR", "VARSTRING_VAR_ARRAY",
  "VARSTRING_COORD", "VARSTRING_COORD_ARRAY", "VARSTRING_REGION",
  "VARSTRING_REGION_ARRAY", "VARSTRING_MAPCHAR", "VARSTRING_MAPCHAR_ARRAY",
  "VARSTRING_MONST", "VARSTRING_MONST_ARRAY", "VARSTRING_OBJ",
  "VARSTRING_OBJ_ARRAY", "VARSTRING_SEL", "VARSTRING_SEL_ARRAY",
  "METHOD_INT", "METHOD_INT_ARRAY", "METHOD_STRING", "METHOD_STRING_ARRAY",
  "METHOD_VAR", "METHOD_VAR_ARRAY", "METHOD_COORD", "METHOD_COORD_ARRAY",
  "METHOD_REGION", "METHOD_REGION_ARRAY", "METHOD_MAPCHAR",
  "METHOD_MAPCHAR_ARRAY", "METHOD_MONST", "METHOD_MONST_ARRAY",
  "METHOD_OBJ", "METHOD_OBJ_ARRAY", "METHOD_SEL", "METHOD_SEL_ARRAY",
  "DICE", "'+'", "'-'", "'*'", "'/'", "'%'", "'='", "'.'", "'|'", "'&'",
  "$accept", "file", "levels", "level", "level_def", "lev_init",
  "tileset_detail", "opt_limited", "opt_coord_or_var", "opt_fillchar",
  "walled", "flags", "flag_list", "levstatements", "stmt_block",
  "levstatement", "any_var_array", "any_var", "any_var_or_arr",
  "any_var_or_unk", "shuffle_detail", "variable_define", "encodeobj_list",
  "encodemonster_list", "mapchar_list", "encoderegion_list",
  "encodecoord_list", "integer_list", "string_list", "function_define",
  "$@1", "$@2", "function_call", "exitstatement", "opt_percent",
  "comparestmt", "switchstatement", "$@3", "$@4", "switchcases",
  "switchcase", "$@5", "$@6", "breakstatement", "for_to_span",
  "forstmt_start", "forstatement", "$@7", "loopstatement", "$@8",
  "chancestatement", "$@9", "ifstatement", "$@10", "if_ending", "$@11",
  "message", "random_corridors", "corridor", "corr_spec", "room_begin",
  "subroom_def", "$@12", "room_def", "$@13", "roomfill", "room_pos",
  "subroom_pos", "room_align", "room_size", "door_detail", "secret",
  "door_wall", "dir_list", "door_pos", "door_infos", "door_info",
  "map_definition", "h_justif", "v_justif", "monster_detail", "$@14",
  "monster_desc", "monster_infos", "monster_info", "seen_trap_mask",
  "object_detail", "$@15", "object_desc", "object_infos", "object_info",
  "trap_detail", "drawbridge_detail", "mazewalk_detail", "wallify_detail",
  "ladder_detail", "stair_detail", "stair_region", "portal_region",
  "teleprt_region", "branch_region", "teleprt_detail", "fountain_detail",
  "throne_detail", "modron_portal_detail", "lever_detail", "lever_infos",
  "lever_info", "valid_subtype", "sink_detail", "pool_detail",
  "terrain_type", "replace_terrain_detail", "terrain_detail",
  "diggable_detail", "passwall_detail", "naming_detail",
  "special_region_detail", "special_levregion_detail", "region_detail",
  "@16", "region_detail_end", "altar_detail", "anvil_detail",
  "floor_detail", "subtype_detail", "npc_detail", "grave_detail",
  "gold_detail", "engraving_detail", "mineralize", "trap_name",
  "room_type", "optroomregionflags", "roomregionflags", "roomregionflag",
  "optfloormaintype", "floormaintype", "optfloortype", "floortype",
  "door_state", "light_state", "alignment", "alignment_prfx", "altar_type",
  "a_register", "string_or_var", "integer_or_var", "coord_or_var",
  "encodecoord", "humidity_flags", "region_or_var", "encoderegion",
  "mapchar_or_var", "mapchar", "monster_or_var", "encodemonster",
  "object_or_var", "encodeobj", "string_expr", "math_expr_var",
  "func_param_type", "func_param_part", "func_param_list",
  "func_params_list", "func_call_param_part", "func_call_param_list",
  "func_call_params_list", "ter_selection_x", "ter_selection", "dice",
  "tileset_number", "all_integers", "all_ints_push", "objectid",
  "monsterid", "terrainid", "engraving_type", "lev_region", "region", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,    44,    58,    40,    41,
      91,    93,   123,   125,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
      43,    45,    42,    47,    37,    61,    46,   124,    38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   239,   240,   240,   241,   241,   242,   243,   243,   244,
     244,   244,   244,   245,   246,   246,   247,   247,   248,   248,
     249,   249,   250,   250,   251,   251,   252,   252,   253,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   257,   257,   257,   258,   258,   259,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   261,   261,   262,   262,   263,   263,   264,
     264,   265,   265,   266,   266,   267,   267,   269,   270,   268,
     271,   272,   273,   273,   274,   274,   274,   276,   277,   275,
     278,   278,   280,   279,   281,   279,   282,   283,   283,   284,
     286,   285,   288,   287,   290,   289,   292,   291,   293,   294,
     293,   295,   296,   296,   296,   297,   297,   298,   299,   301,
     300,   303,   302,   304,   304,   305,   305,   306,   306,   307,
     307,   308,   308,   309,   309,   310,   310,   311,   311,   312,
     312,   313,   313,   314,   314,   315,   315,   315,   316,   316,
     316,   317,   317,   318,   318,   319,   320,   319,   321,   322,
     322,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   323,   323,   323,   323,   324,   324,
     324,   325,   326,   325,   327,   328,   328,   329,   329,   329,
     329,   329,   329,   329,   329,   329,   329,   329,   329,   329,
     329,   329,   329,   329,   329,   329,   329,   329,   329,   329,
     330,   331,   332,   332,   333,   333,   334,   335,   336,   337,
     338,   339,   340,   340,   341,   342,   343,   344,   345,   345,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   347,   347,   347,   347,   348,   349,   350,
     350,   351,   352,   353,   354,   355,   355,   356,   357,   359,
     358,   360,   360,   361,   362,   363,   364,   365,   366,   366,
     366,   367,   368,   369,   369,   370,   370,   371,   371,   372,
     372,   373,   373,   374,   374,   374,   375,   375,   376,   377,
     377,   378,   379,   379,   380,   380,   381,   381,   381,   382,
     382,   382,   383,   383,   384,   385,   385,   385,   386,   387,
     387,   387,   387,   388,   388,   388,   389,   389,   390,   390,
     390,   391,   392,   392,   392,   393,   393,   394,   394,   394,
     395,   395,   395,   395,   396,   396,   396,   397,   397,   397,
     397,   397,   398,   398,   399,   399,   399,   399,   399,   399,
     399,   399,   399,   399,   399,   400,   400,   401,   402,   402,
     403,   403,   404,   404,   405,   405,   406,   406,   407,   407,
     407,   407,   407,   407,   407,   407,   407,   407,   407,   407,
     407,   407,   407,   407,   407,   407,   407,   408,   408,   409,
     410,   410,   411,   411,   411,   412,   412,   412,   412,   413,
     413,   414,   414,   415,   415,   416,   416,   417,   417,   418
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     3,     3,     5,     5,
       5,     3,    16,     3,     0,     2,     0,     2,     0,     2,
       1,     1,     0,     3,     3,     1,     0,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     5,
       3,     5,     5,     5,     3,     3,     5,     5,     5,     7,
       7,     7,     5,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     0,     0,     8,
       4,     1,     0,     1,     1,     5,     3,     0,     0,     9,
       0,     2,     0,     5,     0,     4,     1,     2,     1,     6,
       0,     3,     0,     6,     0,     4,     0,     4,     1,     0,
       4,     3,     1,     3,     3,     5,     5,     7,     4,     0,
      12,     0,    14,     0,     2,     5,     1,     5,     1,     5,
       1,     5,     1,    10,     6,     1,     1,     1,     1,     1,
       3,     1,     1,     0,     3,     3,     3,     3,     1,     7,
       5,     1,     1,     1,     1,     3,     0,     5,     4,     0,
       3,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     3,     3,     3,     1,     1,     3,     1,     1,     1,
       3,     3,     0,     5,     2,     0,     3,     1,     3,     1,
       3,     3,     1,     1,     3,     1,     1,     1,     3,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     1,
       5,     7,     5,     8,     1,     3,     5,     5,     7,     7,
       6,     5,     0,     2,     5,     3,    11,     6,     0,     3,
       1,     3,     3,     3,     3,     1,     1,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     3,     3,     1,
       5,     9,     5,     3,     3,     5,     9,     5,     5,     0,
      12,     0,     1,     7,     3,     7,     5,     5,     5,     5,
       3,     5,     7,     9,     1,     1,     1,     1,     1,     0,
       2,     1,     3,     1,     1,     1,     0,     3,     1,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     4,     1,     1,     4,     1,     1,
       4,     1,     4,     5,     1,     3,     1,     3,     1,     1,
       4,     9,     1,     1,     4,     1,     5,     1,     1,     4,
       1,     1,     5,     1,     1,     1,     4,     1,     1,     5,
       1,     1,     1,     3,     1,     1,     3,     1,     4,     3,
       3,     3,     3,     3,     3,     1,     1,     3,     1,     3,
       0,     1,     1,     1,     1,     3,     0,     1,     1,     2,
       2,     4,     6,     4,     6,     6,     6,     6,     2,     6,
       8,     8,    10,    14,     2,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,    10,     9
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     0,     3,     4,    22,     0,     0,     1,
       5,     0,    26,     0,     7,     0,   144,     0,     0,     0,
       0,   208,     0,     0,     0,     0,     0,     0,     0,   274,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   334,     0,     0,     0,     0,
       0,     0,     0,     0,   172,     0,     0,     0,     0,     0,
       0,     0,     0,   141,     0,     0,     0,   147,   156,     0,
       0,     0,     0,   104,    93,    84,    94,    85,    95,    86,
      96,    87,    97,    88,    98,    89,    99,    90,   100,    91,
     101,    92,    30,    31,     6,    26,   102,   103,     0,    41,
      40,    58,    59,    56,     0,    51,    57,   160,    52,    53,
      55,    54,    29,    69,    39,    75,    74,    43,    62,    64,
      65,    82,    44,    63,    83,    60,    79,    80,    68,    81,
      38,    47,    48,    49,    61,    76,    67,    78,    77,    42,
      66,    70,    71,    72,    73,    34,    35,    33,    32,    36,
      37,    50,    45,    46,     0,    25,    23,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   166,
       0,     0,     0,     0,   105,   106,     0,     0,     0,     0,
     404,     0,   407,     0,   449,     0,   405,   426,    27,     0,
     164,     0,     8,     0,   365,   366,     0,   402,   171,     0,
       0,     0,    11,   451,   450,    13,   374,     0,   211,   212,
       0,     0,   371,     0,     0,   183,   369,   398,   400,   401,
       0,   397,   395,     0,   241,   245,   394,   242,   391,   393,
       0,   390,   388,     0,   215,     0,   387,   336,   335,     0,
     352,   353,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   445,   428,   447,
     275,     0,   379,     0,     0,   378,     0,     0,     0,     0,
     467,     0,     0,   324,     0,     0,     0,     0,     0,   313,
     314,   338,   337,     0,   142,     0,     0,     0,     0,   368,
       0,     0,     0,     0,     0,   285,     0,   308,   307,   454,
     452,   453,   174,   173,     0,     0,     0,     0,   195,   196,
       0,     0,     0,     0,   107,     0,     0,     0,   330,   137,
       0,     0,     0,     0,   146,     0,     0,     0,     0,     0,
     423,   422,   424,   427,     0,   460,   462,   459,   461,   463,
     464,     0,     0,     0,   114,   115,   110,   108,     0,     0,
       0,     0,    26,   161,    24,     0,     0,     0,     0,     0,
     376,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     244,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     429,   430,     0,     0,     0,   438,     0,     0,     0,   444,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   143,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   168,   167,     0,     0,   162,
       0,     0,     0,   420,   406,   414,     0,     0,   409,   410,
     411,   412,   413,     0,   140,     0,   404,     0,     0,     0,
       0,   131,   129,   135,   133,     0,     0,     0,   165,     0,
       0,   403,    10,   309,     0,     9,     0,     0,   375,     0,
       0,     0,   214,   213,   183,   184,   210,     0,     0,     0,
     243,     0,     0,   217,   219,   270,   203,     0,   272,     0,
       0,   199,     0,     0,     0,     0,   385,     0,     0,   383,
       0,     0,   382,     0,     0,   446,   448,     0,     0,   354,
     355,     0,   317,     0,     0,   318,   315,   358,     0,   356,
       0,   357,   327,   276,     0,   277,     0,   186,     0,     0,
       0,     0,   282,   281,     0,     0,   175,   176,   331,   465,
     466,     0,   284,     0,   288,     0,   188,     0,     0,   326,
       0,     0,     0,   312,     0,     0,   158,     0,     0,   148,
     329,   328,     0,   418,   421,     0,   408,   145,   425,   109,
       0,     0,   118,     0,   117,     0,   116,     0,   122,     0,
     113,     0,   112,     0,   111,    28,   367,     0,     0,   377,
     370,     0,   372,     0,     0,   396,   457,   455,   456,   256,
     253,   247,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   252,     0,   257,     0,   259,   260,   269,     0,   255,
     246,   261,   458,   249,     0,   389,   218,   194,     0,     0,
     431,     0,     0,     0,   433,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   380,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   178,     0,     0,   280,     0,
       0,     0,     0,   287,     0,     0,     0,     0,     0,     0,
     163,   157,   159,     0,     0,     0,   138,     0,   130,   132,
     134,   136,     0,   123,     0,   125,     0,   127,     0,     0,
     373,   209,   399,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   392,     0,     0,   271,    18,
       0,   200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   339,     0,     0,     0,     0,   363,   362,   323,
     278,     0,   190,     0,     0,   279,   283,     0,     0,   332,
       0,     0,   325,     0,   192,     0,   339,   198,     0,   197,
     170,     0,   150,   415,   416,   417,   419,     0,     0,   121,
       0,   120,     0,   119,     0,     0,   268,   263,   262,   264,
     265,   266,   267,   250,   251,   254,   258,   248,     0,   359,
     222,   223,     0,   227,   226,   237,   228,   229,   230,     0,
       0,     0,   234,   235,     0,   220,   224,   360,   221,     0,
       0,     0,   204,     0,   273,   432,   434,     0,   439,     0,
     435,     0,   384,   437,   436,     0,     0,     0,   346,     0,
       0,     0,   364,     0,     0,     0,     0,   201,   202,     0,
       0,   290,     0,     0,     0,     0,     0,     0,     0,   295,
     296,     0,     0,     0,   289,     0,     0,   346,     0,     0,
       0,     0,     0,   150,   139,   124,   126,   128,   310,     0,
       0,   225,     0,     0,     0,     0,     0,     0,     0,    19,
       0,     0,   386,     0,     0,   343,   344,   345,   340,   341,
       0,   349,     0,     0,   316,   185,     0,   339,   333,   177,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   187,     0,   349,   203,   311,     0,   154,   149,   151,
       0,   361,   231,   232,   233,   239,   238,   236,   206,   207,
     205,   440,     0,   441,   410,     0,     0,     0,     0,   319,
       0,     0,     0,   346,     0,   351,   300,   302,   303,   304,
     306,   305,   299,   291,   292,   293,   294,   297,   298,   301,
       0,   179,   193,   152,    26,     0,     0,     0,     0,     0,
     381,   342,   348,   347,     0,   321,     0,   469,   189,   349,
     286,   191,     0,    26,   155,     0,   240,   442,    15,     0,
     350,   322,   320,   468,   181,   180,   153,     0,     0,     0,
       0,    16,   182,    20,    21,    18,     0,     0,    12,    17,
     443
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    92,    93,   989,  1027,   834,
    1025,    12,   156,    94,   383,    95,    96,    97,    98,   206,
      99,   100,   712,   714,   716,   477,   478,   479,   480,   101,
     463,   787,   102,   103,   439,   104,   105,   207,   703,   882,
     883,  1003,   984,   106,   588,   107,   108,   221,   109,   585,
     110,   381,   111,   341,   456,   581,   112,   113,   114,   321,
     313,   115,  1002,   116,  1019,   397,   559,   578,   764,   776,
     117,   340,   778,   522,   859,   657,   832,   118,   244,   504,
     119,   404,   264,   656,   825,   947,   120,   401,   254,   400,
     650,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   688,   131,   132,   133,   134,   693,   874,   972,   135,
     136,   495,   137,   138,   139,   140,   141,   142,   143,   144,
     995,  1012,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   269,   314,   848,   908,   909,   911,   993,   959,   966,
     272,   541,   550,   826,   759,   551,   227,   318,   288,   246,
     391,   294,   295,   531,   532,   265,   266,   255,   256,   360,
     319,   785,   593,   594,   595,   362,   363,   364,   289,   421,
     216,   235,   333,   653,   378,   379,   380,   571,   299,   300
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -820
static const yytype_int16 yypact[] =
{
      68,   -83,   -70,   109,  -820,    68,    36,    11,    19,  -820,
    -820,   -48,   873,   -21,  -820,    89,  -820,    63,    67,    72,
      96,  -820,   122,   136,   146,   150,   162,   164,   183,   193,
     207,   216,   223,   225,   226,   229,   230,   232,   233,   234,
     236,   237,   239,   240,   243,   244,   256,   264,   270,   272,
     275,   285,   287,   289,   290,   300,   316,   325,   327,   328,
      58,   338,   339,  -820,   341,    13,   679,  -820,  -820,   345,
     195,    21,    93,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,   873,  -820,  -820,   220,  -820,
    -820,  -820,  -820,  -820,   346,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,   475,   318,  -820,   -93,   333,    61,
     307,    59,    59,    97,   -31,    60,   -16,   -16,   559,   -88,
     -88,   -14,   342,   -16,   -16,   446,   -16,   276,   -88,   -88,
     -19,   -14,   -14,   -14,    21,   353,    21,   -16,   559,   559,
     -16,   559,   559,    88,   -16,   559,   -19,   559,    81,  -820,
     559,   -88,   769,    21,  -820,  -820,   297,   365,   -16,   368,
    -820,    40,  -820,   367,  -820,   227,  -820,    35,  -820,   442,
    -820,   366,  -820,    89,  -820,  -820,   370,  -820,   315,   383,
     384,   390,  -820,  -820,  -820,  -820,  -820,   400,  -820,  -820,
     398,   573,  -820,   407,   402,   418,  -820,  -820,  -820,  -820,
     592,  -820,  -820,   416,  -820,  -820,  -820,  -820,  -820,  -820,
     594,  -820,  -820,   419,   420,   427,  -820,  -820,  -820,   430,
    -820,  -820,   435,   436,   437,   -88,   -88,   -16,   -16,   438,
     -16,   441,   443,   449,   559,   450,   619,  -820,  -820,   377,
    -820,   618,  -820,   452,   453,  -820,   457,   456,   635,   464,
    -820,   473,   479,  -820,   481,   482,   655,   484,   486,  -820,
    -820,  -820,  -820,   487,   658,   489,   491,   493,   494,   278,
     668,   497,    86,   504,   505,  -820,   506,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,   508,   510,   511,   512,  -820,  -820,
     521,   366,   522,   523,  -820,   519,    21,    21,   525,  -820,
     526,   324,    21,    21,  -820,    21,    21,    21,    21,    21,
     315,   278,  -820,   562,   560,  -820,  -820,  -820,  -820,  -820,
    -820,   563,    85,    16,  -820,  -820,   315,   278,   564,   567,
     570,   873,   873,  -820,  -820,    21,   -93,   745,    28,   748,
     576,   572,   559,   578,    21,   213,   751,   580,   581,    21,
     591,   366,   593,    21,   366,   -16,   -16,   559,   696,   704,
    -820,  -820,   600,   601,   320,  -820,   -16,   -16,   546,  -820,
     620,   616,   559,   623,    21,    41,   757,   792,   624,   777,
     776,   181,   -16,   735,   639,   737,   -14,     7,  -820,   641,
     -14,   -14,   -14,    21,   649,    26,   -16,    44,   743,   676,
     681,   741,     8,   827,    60,   723,  -820,    79,    79,  -820,
     -55,   657,   -24,   750,  -820,  -820,   352,   359,   120,   120,
    -820,  -820,  -820,    35,  -820,   559,   663,   -44,   -43,   -35,
     -29,  -820,  -820,   315,   278,    14,   102,    23,  -820,   665,
     444,  -820,  -820,  -820,   837,  -820,   673,   400,  -820,   662,
     846,   502,  -820,  -820,   418,  -820,  -820,   667,   530,   301,
    -820,   670,   590,  -820,  -820,  -820,  -820,   680,   682,   -16,
     -16,   615,   683,   678,   685,   686,  -820,   687,   401,  -820,
     675,   691,  -820,   693,   694,  -820,  -820,   867,   603,  -820,
    -820,   697,  -820,   699,   877,  -820,   701,  -820,   703,  -820,
     709,  -820,  -820,  -820,   896,  -820,   725,  -820,   898,   734,
      41,   736,   749,  -820,   759,   841,  -820,  -820,  -820,  -820,
    -820,   762,  -820,   763,  -820,   765,  -820,   909,   786,  -820,
     788,   830,   963,  -820,   794,   366,  -820,   732,    21,  -820,
    -820,   315,   797,  -820,   800,   803,  -820,  -820,  -820,  -820,
     980,   808,  -820,     2,  -820,    21,  -820,   -93,  -820,    24,
    -820,    57,  -820,    54,  -820,  -820,  -820,   811,   987,  -820,
    -820,   812,  -820,   809,   817,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,   821,   822,   823,   824,   825,   826,   828,   829,
     831,  -820,   832,  -820,   833,  -820,  -820,  -820,   834,  -820,
    -820,  -820,  -820,  -820,   835,  -820,   836,   839,    60,   999,
    -820,   840,   937,   559,  -820,    21,    21,   559,   842,    21,
     559,   559,   843,   844,  -820,   -19,  1009,   847,   875,  1013,
     119,   -34,   943,   848,     9,  -820,   849,   946,  -820,    21,
     850,   -93,   -16,   852,   944,   855,    10,   261,   366,    79,
    -820,  -820,   278,   853,   197,   750,  -820,   -13,  -820,  -820,
     278,   315,    94,  -820,   117,  -820,   139,  -820,    41,   856,
    -820,  -820,  -820,    59,   942,   945,    21,    21,    21,    21,
     -93,    21,    21,    21,    97,  -820,   669,     4,  -820,   861,
      21,  -820,   859,   125,   204,   860,    41,   613,   862,   863,
      21,  1036,   868,   869,  1039,   870,   865,  -820,  -820,  -820,
    -820,  1044,  -820,   274,   874,  -820,  -820,   876,    64,   315,
     878,   501,  -820,  1045,  -820,  1047,   868,  -820,   879,  -820,
    -820,   880,    -2,  -820,  -820,  -820,  -820,   366,    24,  -820,
      57,  -820,    54,  -820,   882,  1052,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,   315,  -820,  -820,  -820,  -820,   160,  -820,
    -820,  -820,   -93,  -820,  -820,  -820,  -820,  -820,  -820,   881,
     885,   886,  -820,  -820,   887,  -820,  -820,  -820,   315,   888,
     907,   908,  -820,  1083,  -820,   278,  -820,  1049,  -820,    21,
    -820,   910,  -820,  -820,  -820,   462,   912,   336,  1000,  1087,
     916,    97,  -820,   914,   918,    10,    21,  -820,  -820,   917,
    1014,  -820,   920,   921,   922,   923,   924,   925,   926,  -820,
    -820,   927,   928,   929,  -820,   930,   931,  1000,    64,  1101,
     317,   933,   932,    -2,  -820,  -820,  -820,  -820,  -820,   935,
    1041,   315,    21,    21,    21,   -74,    59,  1109,  1002,  -820,
     938,   192,  -820,    21,  1110,  -820,  -820,  -820,  -820,   947,
     941,  1032,   948,  1116,  -820,  -820,   213,   868,  -820,  -820,
     949,  1035,  1118,    55,    97,    59,    28,    28,   -16,   -31,
    1122,  -820,  1123,  1032,  -820,  -820,   951,  -820,  -820,  -820,
    1124,  -820,  -820,  -820,  -820,  -820,   893,  -820,  -820,  -820,
    -820,  -820,  1093,  -820,   263,   953,   336,  1046,   956,  -820,
    1130,   957,   958,  1000,  1058,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
     960,  -820,   839,  -820,   873,   964,   -74,   962,   968,   965,
    -820,  -820,  -820,  -820,  1035,   366,   966,  -820,  -820,  1032,
    -820,  -820,   366,   873,  -820,    41,  -820,  -820,  -820,   967,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,   970,   -16,   366,
      99,   971,  -820,  -820,  -820,   861,   -16,   969,  -820,  -820,
    -820
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -820,  -820,  1144,  -820,  -820,  -820,  -820,  -820,  -820,   126,
    -820,  -820,   934,   -95,  -334,   771,   952,  1084,  -449,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  1095,  -820,  -820,  -820,   273,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,   708,
     972,  -820,  -820,  -820,  -820,   654,  -820,  -820,  -820,   304,
    -820,  -820,  -820,  -563,   282,   228,  -820,  -820,   403,   245,
    -820,  -820,  -820,  -820,  -820,   177,  -820,  -820,  1003,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -538,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,   235,   492,  -743,   214,  -820,  -819,  -820,  -817,   175,
    -433,  -557,  -820,  -820,  -820,   439,   785,  -190,  -158,  -367,
     677,   -52,  -362,  -434,  -585,  -474,  -574,  -481,  -568,  -156,
     -61,  -820,   467,  -820,  -820,   700,  -820,  -820,   892,  -146,
     671,  -820,  -440,  -820,  -820,  -820,  -820,  -820,  -106,  -820
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -217
static const yytype_int16 yytable[] =
{
     218,   228,   245,   685,   610,   567,   481,   455,   273,   274,
     215,   482,   612,   345,   592,   302,   303,   247,   305,   307,
     210,   580,   290,   583,   584,   210,   526,   247,   717,   323,
     329,   493,   326,   877,   330,   331,   334,   715,   297,   210,
     267,   713,   324,   325,   210,   327,   328,   590,   350,   335,
     348,   337,   311,   614,   342,   236,   237,   526,   933,   968,
     258,   374,   247,   376,    16,   233,   586,   510,   857,   945,
     513,   308,   829,   236,   237,   315,   316,   317,   557,   576,
     762,   774,   526,     1,     2,   248,   338,   236,   237,   476,
     291,   224,   329,   350,     7,   248,   330,   331,   249,   741,
     258,   830,   225,   226,  1023,   258,   539,     8,   249,     9,
     946,   569,   540,   292,   293,   570,   981,   831,   296,   412,
     413,   880,   415,   881,   270,   322,   309,   310,   259,    15,
     248,   271,   601,   603,   779,   858,   969,    11,   970,   602,
     604,   605,   754,   249,   999,   720,   234,   607,   606,   343,
     351,   240,   339,   268,   608,   154,   361,   461,   377,   332,
     224,   794,   241,   751,   298,   312,   720,   375,   259,   971,
    1024,   225,   226,   259,   963,   355,   356,   357,   358,   359,
     241,   587,  1014,   242,   243,   558,   577,   763,   775,   841,
     757,   155,   250,   203,   372,    13,   609,   758,   251,   211,
     224,   582,   250,    14,   320,   613,   494,   887,   251,   212,
     213,   225,   226,   211,   212,   213,   886,   483,   211,   224,
     885,   252,   253,   410,   411,   738,   529,   530,   212,   213,
     225,   226,   582,   212,   213,   260,   709,   250,    71,   708,
     157,   261,   796,   251,   158,   214,   499,   514,   515,   159,
     214,   700,   547,   564,   548,   549,   592,   582,   524,   525,
     807,   516,   446,   211,   214,   781,   252,   253,   523,   214,
     788,   217,   533,   160,   552,   260,   536,   789,   212,   213,
     260,   261,   529,   530,   611,   460,   261,   489,   568,   502,
     503,   466,   467,   790,   468,   469,   470,   471,   472,   161,
     791,   837,   262,   263,   838,   626,   591,   262,   263,   627,
     628,   351,   484,   162,   214,   792,   355,   356,   357,   358,
     359,   329,   793,   163,   490,   330,   331,   164,   297,   599,
     556,   521,   777,   501,   561,   562,   563,   890,   508,   165,
     679,   166,   512,   229,   230,   231,   232,   236,   237,   238,
     239,   651,   357,   358,   359,   355,   356,   357,   358,   359,
     167,   660,   661,   538,   780,   629,   630,   631,   952,   632,
     168,   953,   236,   237,   905,   906,   907,   914,   236,   237,
     839,   209,   238,   239,   169,   353,   783,   784,   975,   976,
     521,   236,   237,   170,   633,   634,   635,   636,   637,   638,
     171,   639,   172,   173,   668,   393,   174,   175,   354,   176,
     177,   178,   361,   179,   180,   948,   181,   182,   640,   641,
     183,   184,   355,   356,   357,   358,   359,   642,   643,   644,
     645,   646,   647,   185,   355,   356,   357,   358,   359,   988,
     936,   186,   -14,   240,   974,   648,   210,   187,  1017,   188,
     973,   711,   189,   884,   306,   219,   649,   355,   356,   357,
     358,   359,   190,   365,   191,   366,   192,   193,   240,   367,
     368,   369,   236,   237,   240,   242,   243,   194,   222,   241,
     275,   276,   277,   278,   279,   241,   280,   240,   281,   282,
     283,   284,   285,   195,   223,   357,   358,   359,   286,   767,
     242,   243,   196,   465,   197,   198,   242,   243,   355,   356,
     357,   358,   359,   236,   237,   200,   201,   742,   202,   242,
     243,   745,   208,   220,   748,   749,   301,   702,   304,   287,
     214,   320,   346,   596,   770,   769,   799,   800,   801,   802,
     597,   804,   805,   806,   710,   347,   349,   352,   382,   526,
     385,   386,   370,   527,   355,   356,   357,   358,   359,   387,
     388,   275,   276,   277,   278,   279,   389,   280,   240,   281,
     282,   283,   284,   285,   803,   390,   392,   393,   395,   286,
     828,   861,   355,   356,   357,   358,   359,   394,   862,   355,
     356,   357,   358,   359,   396,   398,   399,   402,   863,   403,
     242,   243,  -216,   405,   743,   744,   406,   371,   747,   240,
     287,   407,   408,   409,   864,   422,   414,   236,   237,   416,
     372,   417,   423,   393,   373,   616,   224,   418,   420,   425,
     236,   237,   424,   426,   427,   212,   213,   225,   226,   428,
     429,   242,   243,   292,   293,   865,   866,   867,   868,   430,
     869,   870,   871,   872,   873,   431,   891,   432,   433,   434,
     435,  1011,   436,   437,   438,   440,   918,   441,  1015,   442,
     443,   214,   444,   445,   355,   356,   357,   358,   359,   835,
     447,   448,   449,   622,   450,  1022,   451,   452,   453,   845,
     236,   237,   355,   903,   357,   358,   359,   454,   457,   458,
     459,   462,   942,   943,   944,   464,   275,   276,   277,   278,
     279,   625,   280,   240,   281,   282,   283,   284,   285,   275,
     276,   277,   278,   279,   528,   280,   240,   281,   282,   283,
     284,   285,   355,   356,   357,   358,   359,   286,   473,   474,
     475,   485,   808,   809,   486,   242,   243,   487,   492,   529,
     530,   496,   497,   498,   500,   287,   505,   507,   242,   243,
     355,   356,   357,   358,   359,   506,   517,   509,   287,   511,
     977,   655,   810,   811,   518,   812,   519,   520,   901,   275,
     276,   277,   278,   279,   674,   280,   240,   281,   282,   283,
     284,   285,   542,   534,   842,   535,   543,   286,   813,   537,
     544,   814,   815,   816,   817,   818,   819,   820,   821,   822,
     823,   824,   545,   546,   553,   554,   555,   560,   242,   243,
     355,   356,   357,   358,   359,   565,   572,   573,   287,   574,
     575,   579,  -169,   355,   356,   357,   358,   359,   589,   600,
     617,   620,   954,   355,   356,   357,   358,   359,   615,   618,
     621,   624,   662,   224,   654,   669,   658,   664,   659,   663,
    1021,   665,   666,   667,   225,   226,   204,   670,  1029,   671,
     672,   673,    74,   675,    76,   676,    78,   678,    80,    16,
      82,   677,    84,   679,    86,   680,    88,    17,    90,  1004,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
     681,   682,   683,    28,    29,    30,    31,    32,  1016,    33,
     684,   690,   686,   695,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,   687,    45,    46,    47,    48,
      49,    50,    51,    52,    53,   689,    54,    73,   691,   698,
     692,   694,    55,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    56,   696,    75,   697,    77,   668,    79,   701,    81,
     699,    83,    57,    85,   704,    87,   705,    89,    58,    91,
      59,    60,   706,    61,   707,    62,   291,   718,    63,    64,
     719,   720,    65,    66,   721,    67,   722,    68,   723,   724,
     725,   726,   727,   728,   739,   729,   730,   521,   731,   732,
     733,   734,   736,   753,   735,   737,   740,   756,   746,   755,
     751,   750,   760,   754,   761,   766,   768,    69,   771,    70,
     772,   773,   795,   765,   797,   782,   798,   833,   836,   840,
     846,   843,   844,   850,   847,   849,   852,   851,   853,   875,
     855,   876,   856,    71,   860,   878,   879,   889,   892,    72,
      73,   888,   893,   894,   895,   896,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,   897,   898,   899,   900,   904,   902,
     910,   912,   913,   915,   916,   920,   919,   921,   922,   923,
     924,   925,   926,   927,   928,   929,   930,   932,   935,   931,
     937,   940,   941,   949,   955,   938,   950,   951,   957,   958,
     961,   965,   967,   956,   960,   964,   979,   980,   983,   985,
     986,   987,   990,   994,   996,   992,   997,   998,  1000,  1001,
    1005,  1007,  1008,  1018,  1009,  1013,  1020,  1026,  1030,    10,
     205,  1028,   488,   566,   344,   199,   939,   384,   623,   917,
     934,   962,   982,  1006,   978,   257,   854,   752,   336,  1010,
     991,   491,   786,   598,   619,   827,   419,     0,     0,     0,
     652
};

static const yytype_int16 yycheck[] =
{
      95,   157,   160,   560,   485,   445,   373,   341,   166,   167,
      71,   373,   486,   203,   463,   173,   174,     3,   176,   177,
       4,   454,   168,   457,   458,     4,     3,     3,   613,   187,
       4,     3,   190,   776,     8,     9,   194,   611,    52,     4,
      71,   609,   188,   189,     4,   191,   192,    71,     8,   195,
     208,   197,    71,   487,   200,    71,    72,     3,   877,     4,
       3,   219,     3,   219,     6,     4,   121,   401,     4,   143,
     404,   177,    68,    71,    72,   181,   182,   183,    71,    71,
      71,    71,     3,    15,    16,    71,     5,    71,    72,     4,
     178,   184,     4,     8,   177,    71,     8,     9,    84,   662,
       3,    97,   195,   196,     5,     3,    65,   177,    84,     0,
     184,    67,    71,   201,   202,    71,   933,   113,   170,   277,
     278,   123,   280,   125,    64,   186,   178,   179,    71,   177,
      71,    71,   176,   176,   697,    71,    81,   101,    83,   183,
     183,   176,   176,    84,   963,   179,    85,   176,   183,   201,
     211,   167,    71,   184,   183,   176,   217,   347,   219,    71,
     184,   718,   178,   176,   178,   184,   179,   219,    71,   114,
      71,   195,   196,    71,   917,   230,   231,   232,   233,   234,
     178,   236,   999,   199,   200,   178,   178,   178,   178,   746,
      71,   102,   178,   180,   178,   184,   182,    78,   184,   178,
     184,   178,   178,   184,   178,   182,   178,   792,   184,   193,
     194,   195,   196,   178,   193,   194,   790,   373,   178,   184,
     788,   207,   208,   275,   276,   658,   203,   204,   193,   194,
     195,   196,   178,   193,   194,   178,   603,   178,   180,   601,
     177,   184,   723,   184,   177,   229,   392,   405,   406,   177,
     229,   585,    71,   443,    73,    74,   705,   178,   416,   417,
     734,   407,   176,   178,   229,   699,   207,   208,   414,   229,
     176,   178,   418,   177,   432,   178,   422,   183,   193,   194,
     178,   184,   203,   204,   182,   346,   184,   382,   446,    76,
      77,   352,   353,   176,   355,   356,   357,   358,   359,   177,
     183,   176,   205,   206,   179,     4,   462,   205,   206,     8,
       9,   372,   373,   177,   229,   176,   230,   231,   232,   233,
     234,     4,   183,   177,   385,     8,     9,   177,    52,   475,
     436,    70,    71,   394,   440,   441,   442,   177,   399,   177,
     180,   177,   403,    10,    11,    12,    13,    71,    72,    75,
      76,   509,   232,   233,   234,   230,   231,   232,   233,   234,
     177,   519,   520,   424,   698,    64,    65,    66,   176,    68,
     177,   179,    71,    72,    38,    39,    40,   851,    71,    72,
     176,   186,    75,    76,   177,   158,   189,   190,   926,   927,
      70,    71,    72,   177,    93,    94,    95,    96,    97,    98,
     177,   100,   177,   177,     3,     4,   177,   177,   181,   177,
     177,   177,   473,   177,   177,   896,   177,   177,   117,   118,
     177,   177,   230,   231,   232,   233,   234,   126,   127,   128,
     129,   130,   131,   177,   230,   231,   232,   233,   234,   176,
     880,   177,   179,   167,   925,   144,     4,   177,  1005,   177,
     924,   607,   177,   787,   178,   235,   155,   230,   231,   232,
     233,   234,   177,    21,   177,    23,   177,   177,   167,    27,
      28,    29,    71,    72,   167,   199,   200,   177,     3,   178,
     160,   161,   162,   163,   164,   178,   166,   167,   168,   169,
     170,   171,   172,   177,   176,   232,   233,   234,   178,   689,
     199,   200,   177,   179,   177,   177,   199,   200,   230,   231,
     232,   233,   234,    71,    72,   177,   177,   663,   177,   199,
     200,   667,   177,   177,   670,   671,   184,   588,    82,   209,
     229,   178,   235,   181,   692,   691,   726,   727,   728,   729,
     181,   731,   732,   733,   605,   180,   178,   180,   182,     3,
     180,   236,   110,     7,   230,   231,   232,   233,   234,   176,
     176,   160,   161,   162,   163,   164,   176,   166,   167,   168,
     169,   170,   171,   172,   730,   175,   178,     4,   176,   178,
     736,    80,   230,   231,   232,   233,   234,   180,    87,   230,
     231,   232,   233,   234,   176,     3,   180,     3,    97,   180,
     199,   200,   182,   176,   665,   666,   176,   165,   669,   167,
     209,   176,   176,   176,   113,   238,   178,    71,    72,   178,
     178,   178,     4,     4,   182,   181,   184,   178,   178,   176,
      71,    72,   180,   176,   178,   193,   194,   195,   196,     4,
     176,   199,   200,   201,   202,   144,   145,   146,   147,   176,
     149,   150,   151,   152,   153,   176,   812,   176,   176,     4,
     176,   995,   176,   176,     6,   176,   856,   176,  1002,   176,
     176,   229,     4,   176,   230,   231,   232,   233,   234,   740,
     176,   176,   176,   181,   176,  1019,   176,   176,   176,   750,
      71,    72,   230,   231,   232,   233,   234,   176,   176,   176,
     181,   176,   892,   893,   894,   179,   160,   161,   162,   163,
     164,   181,   166,   167,   168,   169,   170,   171,   172,   160,
     161,   162,   163,   164,   178,   166,   167,   168,   169,   170,
     171,   172,   230,   231,   232,   233,   234,   178,   176,   179,
     177,   177,    73,    74,   177,   199,   200,   177,     3,   203,
     204,     3,   176,   181,   176,   209,     5,   176,   199,   200,
     230,   231,   232,   233,   234,   185,    70,   176,   209,   176,
     928,   181,   103,   104,    70,   106,   176,   176,   839,   160,
     161,   162,   163,   164,   181,   166,   167,   168,   169,   170,
     171,   172,    35,   173,   181,   179,     4,   178,   129,   176,
     176,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,    35,    37,    79,   176,    79,   176,   199,   200,
     230,   231,   232,   233,   234,   176,    83,   151,   209,   148,
      89,     4,   109,   230,   231,   232,   233,   234,   181,   176,
       3,   179,   903,   230,   231,   232,   233,   234,   183,   176,
       4,   184,   237,   184,   184,   180,   176,   179,   176,   176,
    1018,   176,   176,   176,   195,   196,   187,   176,  1026,   176,
     176,     4,   193,   176,   195,   176,   197,   176,   199,     6,
     201,     4,   203,   180,   205,   176,   207,    14,   209,   984,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       4,   176,     4,    30,    31,    32,    33,    34,  1003,    36,
     176,    70,   176,     4,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,   176,    53,    54,    55,    56,
      57,    58,    59,    60,    61,   176,    63,   187,   176,   109,
     177,   176,    69,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,    88,   176,   194,   176,   196,     3,   198,   236,   200,
     176,   202,    99,   204,   177,   206,   176,   208,   105,   210,
     107,   108,   179,   110,     4,   112,   178,   176,   115,   116,
       3,   179,   119,   120,   185,   122,   179,   124,   177,   177,
     177,   177,   177,   177,     5,   177,   177,    70,   177,   177,
     177,   177,   176,     4,   179,   176,   176,     4,   176,   144,
     176,   178,    79,   176,   176,    79,   176,   154,   176,   156,
      86,   176,   176,   184,    92,   182,    91,   176,   179,   179,
       4,   179,   179,     4,   176,   176,   181,   177,     4,     4,
     176,     4,   176,   180,   176,   176,   176,     5,   177,   186,
     187,   179,   177,   177,   177,   177,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   177,   177,     3,    38,   176,   179,
      90,     4,   176,   179,   176,    81,   179,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   176,     7,   179,
     177,   176,    71,     4,     4,   183,   114,   179,   177,    87,
       4,    86,     4,   176,   176,   176,     4,     4,   177,     5,
     237,    38,   179,   177,     4,    89,   179,   179,    80,   179,
     176,   179,   174,   176,   179,   179,   176,   176,   179,     5,
      66,  1025,   381,   445,   202,    60,   883,   223,   504,   855,
     878,   916,   934,   986,   929,   162,   763,   675,   196,   994,
     956,   386,   705,   473,   497,   736,   284,    -1,    -1,    -1,
     509
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,    15,    16,   240,   241,   242,   243,   177,   177,     0,
     241,   101,   250,   184,   184,   177,     6,    14,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    30,    31,
      32,    33,    34,    36,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    63,    69,    88,    99,   105,   107,
     108,   110,   112,   115,   116,   119,   120,   122,   124,   154,
     156,   180,   186,   187,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   244,   245,   252,   254,   255,   256,   257,   259,
     260,   268,   271,   272,   274,   275,   282,   284,   285,   287,
     289,   291,   295,   296,   297,   300,   302,   309,   316,   319,
     325,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   341,   342,   343,   344,   348,   349,   351,   352,   353,
     354,   355,   356,   357,   358,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   176,   102,   251,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   274,
     177,   177,   177,   180,   187,   256,   258,   276,   177,   186,
       4,   178,   193,   194,   229,   399,   409,   178,   252,   235,
     177,   286,     3,   176,   184,   195,   196,   385,   398,    10,
      11,    12,    13,     4,    85,   410,    71,    72,    75,    76,
     167,   178,   199,   200,   317,   387,   388,     3,    71,    84,
     178,   184,   207,   208,   327,   396,   397,   327,     3,    71,
     178,   184,   205,   206,   321,   394,   395,    71,   184,   370,
      64,    71,   379,   387,   387,   160,   161,   162,   163,   164,
     166,   168,   169,   170,   171,   172,   178,   209,   387,   407,
     408,   178,   201,   202,   390,   391,   390,    52,   178,   417,
     418,   184,   387,   387,    82,   387,   178,   387,   417,   390,
     390,    71,   184,   299,   371,   417,   417,   417,   386,   399,
     178,   298,   399,   387,   408,   408,   387,   408,   408,     4,
       8,     9,    71,   411,   387,   408,   299,   408,     5,    71,
     310,   292,   408,   390,   255,   386,   235,   180,   387,   178,
       8,   399,   180,   158,   181,   230,   231,   232,   233,   234,
     398,   399,   404,   405,   406,    21,    23,    27,    28,    29,
     110,   165,   178,   182,   387,   390,   398,   399,   413,   414,
     415,   290,   182,   253,   251,   180,   236,   176,   176,   176,
     175,   389,   178,     4,   180,   176,   176,   304,     3,   180,
     328,   326,     3,   180,   320,   176,   176,   176,   176,   176,
     390,   390,   387,   387,   178,   387,   178,   178,   178,   407,
     178,   408,   238,     4,   180,   176,   176,   178,     4,   176,
     176,   176,   176,   176,     4,   176,   176,   176,     6,   273,
     176,   176,   176,   176,     4,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   253,   293,   176,   176,   181,
     399,   386,   176,   269,   179,   179,   399,   399,   399,   399,
     399,   399,   399,   176,   179,   177,     4,   264,   265,   266,
     267,   388,   391,   398,   399,   177,   177,   177,   254,   252,
     399,   385,     3,     3,   178,   350,     3,   176,   181,   408,
     176,   399,    76,    77,   318,     5,   185,   176,   399,   176,
     253,   176,   399,   253,   387,   387,   408,    70,    70,   176,
     176,    70,   312,   408,   387,   387,     3,     7,   178,   203,
     204,   392,   393,   408,   173,   179,   408,   176,   399,    65,
      71,   380,    35,     4,   176,    35,    37,    71,    73,    74,
     381,   384,   387,    79,   176,    79,   417,    71,   178,   305,
     176,   417,   417,   417,   386,   176,   298,   411,   387,    67,
      71,   416,    83,   151,   148,    89,    71,   178,   306,     4,
     379,   294,   178,   392,   392,   288,   121,   236,   283,   181,
      71,   398,   257,   401,   402,   403,   181,   181,   404,   408,
     176,   176,   183,   176,   183,   176,   183,   176,   183,   182,
     396,   182,   394,   182,   392,   183,   181,     3,   176,   389,
     179,     4,   181,   304,   184,   181,     4,     8,     9,    64,
      65,    66,    68,    93,    94,    95,    96,    97,    98,   100,
     117,   118,   126,   127,   128,   129,   130,   131,   144,   155,
     329,   387,   409,   412,   184,   181,   322,   314,   176,   176,
     387,   387,   237,   176,   179,   176,   176,   176,     3,   180,
     176,   176,   176,     4,   181,   176,   176,     4,   176,   180,
     176,     4,   176,     4,   176,   380,   176,   176,   340,   176,
      70,   176,   177,   345,   176,     4,   176,   176,   109,   176,
     253,   236,   399,   277,   177,   176,   179,     4,   391,   388,
     399,   398,   261,   397,   262,   395,   263,   393,   176,     3,
     179,   185,   179,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   179,   176,   176,   379,     5,
     176,   312,   408,   399,   399,   408,   176,   399,   408,   408,
     178,   176,   371,     4,   176,   144,     4,    71,    78,   383,
      79,   176,    71,   178,   307,   184,    79,   386,   176,   398,
     387,   176,    86,   176,    71,   178,   308,    71,   311,   312,
     253,   392,   182,   189,   190,   400,   401,   270,   176,   183,
     176,   183,   176,   183,   380,   176,   396,    92,    91,   386,
     386,   386,   386,   398,   386,   386,   386,   394,    73,    74,
     103,   104,   106,   129,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   323,   382,   384,   398,    68,
      97,   113,   315,   176,   248,   399,   179,   176,   179,   176,
     179,   380,   181,   179,   179,   399,     4,   176,   372,   176,
       4,   177,   181,     4,   317,   176,   176,     4,    71,   313,
     176,    80,    87,    97,   113,   144,   145,   146,   147,   149,
     150,   151,   152,   153,   346,     4,     4,   372,   176,   176,
     123,   125,   278,   279,   253,   397,   395,   393,   179,     5,
     177,   398,   177,   177,   177,   177,   177,   177,   177,     3,
      38,   399,   179,   231,   176,    38,    39,    40,   373,   374,
      90,   375,     4,   176,   394,   179,   176,   308,   386,   179,
      81,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   179,   176,   375,   313,     7,   411,   177,   183,   278,
     176,    71,   386,   386,   386,   143,   184,   324,   396,     4,
     114,   179,   176,   179,   399,     4,   176,   177,    87,   377,
     176,     4,   318,   372,   176,    86,   378,     4,     4,    81,
      83,   114,   347,   394,   396,   350,   350,   387,   370,     4,
       4,   377,   314,   177,   281,     5,   237,    38,   176,   246,
     179,   373,    89,   376,   177,   359,     4,   179,   179,   375,
      80,   179,   301,   280,   252,   176,   324,   179,   174,   179,
     378,   253,   360,   179,   377,   253,   252,   380,   176,   303,
     176,   387,   253,     5,    71,   249,   176,   247,   248,   387,
     179
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:

/* Line 1455 of yacc.c  */
#line 292 "lev_comp.y"
    {
			if (fatal_error > 0) {
				(void) fprintf(stderr,
              "%s: %d errors detected for level \"%s\". No output created!\n",
					       fname, fatal_error, (yyvsp[(1) - (3)].map));
				fatal_error = 0;
				got_errors++;
			} else if (!got_errors) {
				if (!write_level_file((yyvsp[(1) - (3)].map), splev)) {
                                    lc_error("Can't write output file for '%s'!",
                                             (yyvsp[(1) - (3)].map));
				    exit(EXIT_FAILURE);
				}
			}
			Free((yyvsp[(1) - (3)].map));
			Free(splev);
			splev = NULL;
			vardef_free_all(vardefs);
			vardefs = NULL;
		  ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 315 "lev_comp.y"
    {
		      start_level_def(&splev, (yyvsp[(3) - (3)].map));
		      (yyval.map) = (yyvsp[(3) - (3)].map);
		  ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 320 "lev_comp.y"
    {
		      start_level_def(&splev, (yyvsp[(3) - (5)].map));
		      if ((yyvsp[(5) - (5)].i) == -1) {
			  add_opvars(splev, "iiiiiiiio",
				     VA_PASS9(LVLINIT_MAZEGRID, HWALL, 0,0,
					      0,0,0,0, SPO_INITLEVEL));
		      } else {
			  int bg = (int)what_map_char((char) (yyvsp[(5) - (5)].i));

			  add_opvars(splev, "iiiiiiiio",
				     VA_PASS9(LVLINIT_SOLIDFILL, bg, 0, 0,
					      0,0,0,0, SPO_INITLEVEL));
		      }
		      add_opvars(splev, "io",
				 VA_PASS2(MAZELEVEL, SPO_LEVEL_FLAGS));
		      max_x_map = COLNO-1;
		      max_y_map = ROWNO;
		      (yyval.map) = (yyvsp[(3) - (5)].map);
		  ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 342 "lev_comp.y"
    {
		      int filling = (int) (yyvsp[(5) - (5)].terr).ter;

		      if (filling == INVALID_TYPE || filling >= MAX_TYPE)
			  lc_error("INIT_MAP: Invalid fill char type.");
		      add_opvars(splev, "iiiiiiiio",
				 VA_PASS9(LVLINIT_SOLIDFILL, filling,
                                          0, (int) (yyvsp[(5) - (5)].terr).lit,
                                          0,0,0,0, SPO_INITLEVEL));
		      max_x_map = COLNO-1;
		      max_y_map = ROWNO;
		  ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 355 "lev_comp.y"
    {
		      int filling = (int) what_map_char((char) (yyvsp[(5) - (5)].i));

		      if (filling == INVALID_TYPE || filling >= MAX_TYPE)
			  lc_error("INIT_MAP: Invalid fill char type.");
                      add_opvars(splev, "iiiiiiiio",
				 VA_PASS9(LVLINIT_MAZEGRID, filling, 0,0,
					  0,0,0,0, SPO_INITLEVEL));
		      max_x_map = COLNO-1;
		      max_y_map = ROWNO;
		  ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 367 "lev_comp.y"
    {
		      add_opvars(splev, "iiiiiiiio",
				 VA_PASS9(LVLINIT_ROGUE,0,0,0,
					  0,0,0,0, SPO_INITLEVEL));
		  ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 373 "lev_comp.y"
    {
                      int fg = (int) what_map_char((char) (yyvsp[(5) - (16)].i)),
                          bg = (int) what_map_char((char) (yyvsp[(7) - (16)].i));
                      int smoothed = (int) (yyvsp[(9) - (16)].i),
                          joined = (int) (yyvsp[(11) - (16)].i),
                          lit = (int) (yyvsp[(13) - (16)].i),
                          walled = (int) (yyvsp[(15) - (16)].i),
                          filling = (int) (yyvsp[(16) - (16)].i);

		      if (fg == INVALID_TYPE || fg >= MAX_TYPE)
			  lc_error("INIT_MAP: Invalid foreground type.");
		      if (bg == INVALID_TYPE || bg >= MAX_TYPE)
			  lc_error("INIT_MAP: Invalid background type.");
		      if (joined && fg != CORR && fg != ROOM && fg != GRASS && fg != GROUND)
			  lc_error("INIT_MAP: Invalid foreground type for joined map.");

		      if (filling == INVALID_TYPE)
			  lc_error("INIT_MAP: Invalid fill char type.");

		      add_opvars(splev, "iiiiiiiio",
				 VA_PASS9(LVLINIT_MINES, filling, walled, lit,
					  joined, smoothed, bg, fg,
					  SPO_INITLEVEL));
			max_x_map = COLNO-1;
			max_y_map = ROWNO;
		  ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 402 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2((int)(yyvsp[(3) - (3)].i), SPO_TILESET));
		  ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 408 "lev_comp.y"
    {
		      (yyval.i) = 0;
		  ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 412 "lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(2) - (2)].i);
		  ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 418 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_COPY));
		      (yyval.i) = 0;
		  ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 423 "lev_comp.y"
    {
		      (yyval.i) = 1;
		  ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 429 "lev_comp.y"
    {
		      (yyval.i) = -1;
		  ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 433 "lev_comp.y"
    {
		      (yyval.i) = what_map_char((char) (yyvsp[(2) - (2)].i));
		  ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 444 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2(0, SPO_LEVEL_FLAGS));
		  ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 448 "lev_comp.y"
    {
		      add_opvars(splev, "io",
                                 VA_PASS2((int) (yyvsp[(3) - (3)].i), SPO_LEVEL_FLAGS));
		  ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 455 "lev_comp.y"
    {
		      (yyval.i) = ((yyvsp[(1) - (3)].i) | (yyvsp[(3) - (3)].i));
		  ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 459 "lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(1) - (1)].i);
		  ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 465 "lev_comp.y"
    {
		      (yyval.i) = 0;
		  ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 469 "lev_comp.y"
    {
		      (yyval.i) = 1 + (yyvsp[(2) - (2)].i);
		  ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 475 "lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(2) - (3)].i);
		  ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 569 "lev_comp.y"
    {
		      struct lc_vardefs *vd;

		      if ((vd = vardef_defined(vardefs, (yyvsp[(3) - (3)].map), 1))) {
			  if (!(vd->var_type & SPOVAR_ARRAY))
			      lc_error("Trying to shuffle non-array variable '%s'",
                                       (yyvsp[(3) - (3)].map));
		      } else
                          lc_error("Trying to shuffle undefined variable '%s'",
                                   (yyvsp[(3) - (3)].map));
		      add_opvars(splev, "so", VA_PASS2((yyvsp[(3) - (3)].map), SPO_SHUFFLE_ARRAY));
		      Free((yyvsp[(3) - (3)].map));
		  ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 585 "lev_comp.y"
    {
		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (3)].map), SPOVAR_INT);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[(1) - (3)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (3)].map));
		  ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 591 "lev_comp.y"
    {
		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (5)].map), SPOVAR_SEL);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[(1) - (5)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (5)].map));
		  ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 597 "lev_comp.y"
    {
		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (3)].map), SPOVAR_STRING);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[(1) - (3)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (3)].map));
		  ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 603 "lev_comp.y"
    {
		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (5)].map), SPOVAR_MAPCHAR);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[(1) - (5)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (5)].map));
		  ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 609 "lev_comp.y"
    {
		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (5)].map), SPOVAR_MONST);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[(1) - (5)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (5)].map));
		  ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 615 "lev_comp.y"
    {
		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (5)].map), SPOVAR_OBJ);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[(1) - (5)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (5)].map));
		  ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 621 "lev_comp.y"
    {
		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (3)].map), SPOVAR_COORD);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[(1) - (3)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (3)].map));
		  ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 627 "lev_comp.y"
    {
		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (3)].map), SPOVAR_REGION);
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[(1) - (3)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (3)].map));
		  ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 633 "lev_comp.y"
    {
		      int n_items = (int) (yyvsp[(4) - (5)].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (5)].map),
                                                SPOVAR_INT | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[(1) - (5)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (5)].map));
		  ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 643 "lev_comp.y"
    {
		      int n_items = (int) (yyvsp[(4) - (5)].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (5)].map),
                                                SPOVAR_COORD | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[(1) - (5)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (5)].map));
		  ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 653 "lev_comp.y"
    {
                      int n_items = (int) (yyvsp[(4) - (5)].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (5)].map),
                                                SPOVAR_REGION | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[(1) - (5)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (5)].map));
		  ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 663 "lev_comp.y"
    {
                      int n_items = (int) (yyvsp[(6) - (7)].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (7)].map),
                                                SPOVAR_MAPCHAR | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[(1) - (7)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (7)].map));
		  ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 673 "lev_comp.y"
    {
		      int n_items = (int) (yyvsp[(6) - (7)].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (7)].map),
                                                SPOVAR_MONST | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[(1) - (7)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (7)].map));
		  ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 683 "lev_comp.y"
    {
                      int n_items = (int) (yyvsp[(6) - (7)].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (7)].map),
                                                SPOVAR_OBJ | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[(1) - (7)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (7)].map));
		  ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 693 "lev_comp.y"
    {
                      int n_items = (int) (yyvsp[(4) - (5)].i);

		      vardefs = add_vardef_type(vardefs, (yyvsp[(1) - (5)].map),
                                                SPOVAR_STRING | SPOVAR_ARRAY);
		      add_opvars(splev, "iso",
				 VA_PASS3(n_items, (yyvsp[(1) - (5)].map), SPO_VAR_INIT));
		      Free((yyvsp[(1) - (5)].map));
		  ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 705 "lev_comp.y"
    {
		      add_opvars(splev, "O", VA_PASS1((yyvsp[(1) - (1)].i)));
		      (yyval.i) = 1;
		  ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 710 "lev_comp.y"
    {
		      add_opvars(splev, "O", VA_PASS1((yyvsp[(3) - (3)].i)));
		      (yyval.i) = 1 + (yyvsp[(1) - (3)].i);
		  ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 717 "lev_comp.y"
    {
		      add_opvars(splev, "M", VA_PASS1((yyvsp[(1) - (1)].i)));
		      (yyval.i) = 1;
		  ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 722 "lev_comp.y"
    {
		      add_opvars(splev, "M", VA_PASS1((yyvsp[(3) - (3)].i)));
		      (yyval.i) = 1 + (yyvsp[(1) - (3)].i);
		  ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 729 "lev_comp.y"
    {
		      add_opvars(splev, "m", VA_PASS1((yyvsp[(1) - (1)].i)));
		      (yyval.i) = 1;
		  ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 734 "lev_comp.y"
    {
		      add_opvars(splev, "m", VA_PASS1((yyvsp[(3) - (3)].i)));
		      (yyval.i) = 1 + (yyvsp[(1) - (3)].i);
		  ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 741 "lev_comp.y"
    {
		      (yyval.i) = 1;
		  ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 745 "lev_comp.y"
    {
		      (yyval.i) = 1 + (yyvsp[(1) - (3)].i);
		  ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 751 "lev_comp.y"
    {
		      add_opvars(splev, "c", VA_PASS1((yyvsp[(1) - (1)].i)));
		      (yyval.i) = 1;
		  ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 756 "lev_comp.y"
    {
		      add_opvars(splev, "c", VA_PASS1((yyvsp[(3) - (3)].i)));
		      (yyval.i) = 1 + (yyvsp[(1) - (3)].i);
		  ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 763 "lev_comp.y"
    {
		      (yyval.i) = 1;
		  ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 767 "lev_comp.y"
    {
		      (yyval.i) = 1 + (yyvsp[(1) - (3)].i);
		  ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 773 "lev_comp.y"
    {
		      (yyval.i) = 1;
		  ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 777 "lev_comp.y"
    {
		      (yyval.i) = 1 + (yyvsp[(1) - (3)].i);
		  ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 783 "lev_comp.y"
    {
		      struct lc_funcdefs *funcdef;

		      if (in_function_definition)
			  lc_error("Recursively defined functions not allowed (function %s).", (yyvsp[(2) - (3)].map));

		      in_function_definition++;

		      if (funcdef_defined(function_definitions, (yyvsp[(2) - (3)].map), 1))
			  lc_error("Function '%s' already defined once.", (yyvsp[(2) - (3)].map));

		      funcdef = funcdef_new(-1, (yyvsp[(2) - (3)].map));
		      funcdef->next = function_definitions;
		      function_definitions = funcdef;
		      function_splev_backup = splev;
		      splev = &(funcdef->code);
		      Free((yyvsp[(2) - (3)].map));
		      curr_function = funcdef;
		      function_tmp_var_defs = vardefs;
		      vardefs = NULL;
		  ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 805 "lev_comp.y"
    {
		      /* nothing */
		  ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 809 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2(0, SPO_RETURN));
		      splev = function_splev_backup;
		      in_function_definition--;
		      curr_function = NULL;
		      vardef_free_all(vardefs);
		      vardefs = function_tmp_var_defs;
		  ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 820 "lev_comp.y"
    {
		      struct lc_funcdefs *tmpfunc;

		      tmpfunc = funcdef_defined(function_definitions, (yyvsp[(1) - (4)].map), 1);
		      if (tmpfunc) {
			  int l;
			  int nparams = (int) strlen((yyvsp[(3) - (4)].map));
			  char *fparamstr = funcdef_paramtypes(tmpfunc);

			  if (strcmp((yyvsp[(3) - (4)].map), fparamstr)) {
			      char *tmps = strdup(decode_parm_str(fparamstr));

			      lc_error("Function '%s' requires params '%s', got '%s' instead.",
                                       (yyvsp[(1) - (4)].map), tmps, decode_parm_str((yyvsp[(3) - (4)].map)));
			      Free(tmps);
			  }
			  Free(fparamstr);
			  Free((yyvsp[(3) - (4)].map));
			  if (!(tmpfunc->n_called)) {
			      /* we haven't called the function yet, so insert it in the code */
			      struct opvar *jmp = New(struct opvar);

			      set_opvar_int(jmp, splev->n_opcodes+1);
			      add_opcode(splev, SPO_PUSH, jmp);
                              /* we must jump past it first, then CALL it, due to RETURN. */
			      add_opcode(splev, SPO_JMP, NULL);

			      tmpfunc->addr = splev->n_opcodes;

			      { /* init function parameter variables */
				  struct lc_funcdefs_parm *tfp = tmpfunc->params;
				  while (tfp) {
				      add_opvars(splev, "iso",
						 VA_PASS3(0, tfp->name,
							  SPO_VAR_INIT));
				      tfp = tfp->next;
				  }
			      }

			      splev_add_from(splev, &(tmpfunc->code));
			      set_opvar_int(jmp,
                                            splev->n_opcodes - jmp->vardata.l);
			  }
			  l = (int) (tmpfunc->addr - splev->n_opcodes - 2);
			  add_opvars(splev, "iio",
				     VA_PASS3(nparams, l, SPO_CALL));
			  tmpfunc->n_called++;
		      } else {
			  lc_error("Function '%s' not defined.", (yyvsp[(1) - (4)].map));
		      }
		      Free((yyvsp[(1) - (4)].map));
		  ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 875 "lev_comp.y"
    {
		      add_opcode(splev, SPO_EXIT, NULL);
		  ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 881 "lev_comp.y"
    {
		      (yyval.i) = 100;
		  ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 885 "lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(1) - (1)].i);
		  ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 891 "lev_comp.y"
    {
		      /* val > rn2(100) */
		      add_opvars(splev, "iio",
				 VA_PASS3((int) (yyvsp[(1) - (1)].i), 100, SPO_RN2));
		      (yyval.i) = SPO_JG;
                  ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 898 "lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(3) - (5)].i);
                  ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 902 "lev_comp.y"
    {
		      /* boolean, explicit foo != 0 */
		      add_opvars(splev, "i", VA_PASS1(0));
		      (yyval.i) = SPO_JNE;
                  ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 910 "lev_comp.y"
    {
		      is_inconstant_number = 0;
		  ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 914 "lev_comp.y"
    {
		      struct opvar *chkjmp;

		      if (in_switch_statement > 0)
			  lc_error("Cannot nest switch-statements.");

		      in_switch_statement++;

		      n_switch_case_list = 0;
		      switch_default_case = NULL;

		      if (!is_inconstant_number)
			  add_opvars(splev, "o", VA_PASS1(SPO_RN2));
		      is_inconstant_number = 0;

		      chkjmp = New(struct opvar);
		      set_opvar_int(chkjmp, splev->n_opcodes+1);
		      switch_check_jump = chkjmp;
		      add_opcode(splev, SPO_PUSH, chkjmp);
		      add_opcode(splev, SPO_JMP, NULL);
		      break_stmt_start();
		  ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 937 "lev_comp.y"
    {
		      struct opvar *endjump = New(struct opvar);
		      int i;

		      set_opvar_int(endjump, splev->n_opcodes+1);

		      add_opcode(splev, SPO_PUSH, endjump);
		      add_opcode(splev, SPO_JMP, NULL);

		      set_opvar_int(switch_check_jump,
			     splev->n_opcodes - switch_check_jump->vardata.l);

		      for (i = 0; i < n_switch_case_list; i++) {
			  add_opvars(splev, "oio",
				     VA_PASS3(SPO_COPY,
					      switch_case_value[i], SPO_CMP));
			  set_opvar_int(switch_case_list[i],
			 switch_case_list[i]->vardata.l - splev->n_opcodes-1);
			  add_opcode(splev, SPO_PUSH, switch_case_list[i]);
			  add_opcode(splev, SPO_JE, NULL);
		      }

		      if (switch_default_case) {
			  set_opvar_int(switch_default_case,
			 switch_default_case->vardata.l - splev->n_opcodes-1);
			  add_opcode(splev, SPO_PUSH, switch_default_case);
			  add_opcode(splev, SPO_JMP, NULL);
		      }

		      set_opvar_int(endjump, splev->n_opcodes - endjump->vardata.l);

		      break_stmt_end(splev);

		      add_opcode(splev, SPO_POP, NULL); /* get rid of the value in stack */
		      in_switch_statement--;


		  ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 982 "lev_comp.y"
    {
		      if (n_switch_case_list < MAX_SWITCH_CASES) {
			  struct opvar *tmppush = New(struct opvar);

			  set_opvar_int(tmppush, splev->n_opcodes);
			  switch_case_value[n_switch_case_list] = (yyvsp[(2) - (3)].i);
			  switch_case_list[n_switch_case_list++] = tmppush;
		      } else lc_error("Too many cases in a switch.");
		  ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 992 "lev_comp.y"
    {
		  ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 995 "lev_comp.y"
    {
		      struct opvar *tmppush = New(struct opvar);

		      if (switch_default_case)
			  lc_error("Switch default case already used.");

		      set_opvar_int(tmppush, splev->n_opcodes);
		      switch_default_case = tmppush;
		  ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1005 "lev_comp.y"
    {
		  ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1010 "lev_comp.y"
    {
		      if (!allow_break_statements)
			  lc_error("Cannot use BREAK outside a statement block.");
		      else {
			  break_stmt_new(splev, splev->n_opcodes);
		      }
		  ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1024 "lev_comp.y"
    {
		      char buf[256], buf2[256];

		      if (n_forloops >= MAX_NESTED_IFS) {
			  lc_error("FOR: Too deeply nested loops.");
			  n_forloops = MAX_NESTED_IFS - 1;
		      }

		      /* first, define a variable for the for-loop end value */
		      Sprintf(buf, "%s end", (yyvsp[(2) - (6)].map));
		      /* the value of which is already in stack (the 2nd math_expr) */
		      add_opvars(splev, "iso", VA_PASS3(0, buf, SPO_VAR_INIT));

		      vardefs = add_vardef_type(vardefs, (yyvsp[(2) - (6)].map), SPOVAR_INT);
		      /* define the for-loop variable. value is in stack (1st math_expr) */
		      add_opvars(splev, "iso", VA_PASS3(0, (yyvsp[(2) - (6)].map), SPO_VAR_INIT));

		      /* calculate value for the loop "step" variable */
		      Sprintf(buf2, "%s step", (yyvsp[(2) - (6)].map));
		      /* end - start */
		      add_opvars(splev, "vvo",
				 VA_PASS3(buf, (yyvsp[(2) - (6)].map), SPO_MATH_SUB));
		      /* sign of that */
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_SIGN));
		      /* save the sign into the step var */
		      add_opvars(splev, "iso",
				 VA_PASS3(0, buf2, SPO_VAR_INIT));

		      forloop_list[n_forloops].varname = strdup((yyvsp[(2) - (6)].map));
		      forloop_list[n_forloops].jmp_point = splev->n_opcodes;

		      n_forloops++;
		      Free((yyvsp[(2) - (6)].map));
		  ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1061 "lev_comp.y"
    {
		      /* nothing */
		      break_stmt_start();
		  ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1066 "lev_comp.y"
    {
                      int l;
		      char buf[256], buf2[256];

		      n_forloops--;
		      Sprintf(buf, "%s step", forloop_list[n_forloops].varname);
		      Sprintf(buf2, "%s end", forloop_list[n_forloops].varname);
		      /* compare for-loop var to end value */
		      add_opvars(splev, "vvo",
				 VA_PASS3(forloop_list[n_forloops].varname,
					  buf2, SPO_CMP));
		      /* var + step */
		      add_opvars(splev, "vvo",
				VA_PASS3(buf, forloop_list[n_forloops].varname,
					 SPO_MATH_ADD));
		      /* for-loop var = (for-loop var + step) */
		      add_opvars(splev, "iso",
				 VA_PASS3(0, forloop_list[n_forloops].varname,
					  SPO_VAR_INIT));
		      /* jump back if compared values were not equal */
                      l = (int) (forloop_list[n_forloops].jmp_point
                                 - splev->n_opcodes - 1);
		      add_opvars(splev, "io", VA_PASS2(l, SPO_JNE));
		      Free(forloop_list[n_forloops].varname);
		      break_stmt_end(splev);
		  ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1095 "lev_comp.y"
    {
		      struct opvar *tmppush = New(struct opvar);

		      if (n_if_list >= MAX_NESTED_IFS) {
			  lc_error("LOOP: Too deeply nested conditionals.");
			  n_if_list = MAX_NESTED_IFS - 1;
		      }
		      set_opvar_int(tmppush, splev->n_opcodes);
		      if_list[n_if_list++] = tmppush;

		      add_opvars(splev, "o", VA_PASS1(SPO_DEC));
		      break_stmt_start();
		  ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1109 "lev_comp.y"
    {
		      struct opvar *tmppush;

		      add_opvars(splev, "oio", VA_PASS3(SPO_COPY, 0, SPO_CMP));

		      tmppush = (struct opvar *) if_list[--n_if_list];
		      set_opvar_int(tmppush,
                                    tmppush->vardata.l - splev->n_opcodes-1);
		      add_opcode(splev, SPO_PUSH, tmppush);
		      add_opcode(splev, SPO_JG, NULL);
		      add_opcode(splev, SPO_POP, NULL); /* discard count */
		      break_stmt_end(splev);
		  ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1125 "lev_comp.y"
    {
		      struct opvar *tmppush2 = New(struct opvar);

		      if (n_if_list >= MAX_NESTED_IFS) {
			  lc_error("IF: Too deeply nested conditionals.");
			  n_if_list = MAX_NESTED_IFS - 1;
		      }

		      add_opcode(splev, SPO_CMP, NULL);

		      set_opvar_int(tmppush2, splev->n_opcodes+1);

		      if_list[n_if_list++] = tmppush2;

		      add_opcode(splev, SPO_PUSH, tmppush2);

		      add_opcode(splev, reverse_jmp_opcode( (yyvsp[(1) - (2)].i) ), NULL);

		  ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1145 "lev_comp.y"
    {
		      if (n_if_list > 0) {
			  struct opvar *tmppush;

			  tmppush = (struct opvar *) if_list[--n_if_list];
			  set_opvar_int(tmppush,
                                        splev->n_opcodes - tmppush->vardata.l);
		      } else lc_error("IF: Huh?!  No start address?");
		  ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1157 "lev_comp.y"
    {
		      struct opvar *tmppush2 = New(struct opvar);

		      if (n_if_list >= MAX_NESTED_IFS) {
			  lc_error("IF: Too deeply nested conditionals.");
			  n_if_list = MAX_NESTED_IFS - 1;
		      }

		      add_opcode(splev, SPO_CMP, NULL);

		      set_opvar_int(tmppush2, splev->n_opcodes+1);

		      if_list[n_if_list++] = tmppush2;

		      add_opcode(splev, SPO_PUSH, tmppush2);

		      add_opcode(splev, reverse_jmp_opcode( (yyvsp[(2) - (2)].i) ), NULL);

		  ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1177 "lev_comp.y"
    {
		     /* do nothing */
		  ;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1183 "lev_comp.y"
    {
		      if (n_if_list > 0) {
			  struct opvar *tmppush;

			  tmppush = (struct opvar *) if_list[--n_if_list];
			  set_opvar_int(tmppush,
                                        splev->n_opcodes - tmppush->vardata.l);
		      } else lc_error("IF: Huh?!  No start address?");
		  ;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1193 "lev_comp.y"
    {
		      if (n_if_list > 0) {
			  struct opvar *tmppush = New(struct opvar);
			  struct opvar *tmppush2;

			  set_opvar_int(tmppush, splev->n_opcodes+1);
			  add_opcode(splev, SPO_PUSH, tmppush);

			  add_opcode(splev, SPO_JMP, NULL);

			  tmppush2 = (struct opvar *) if_list[--n_if_list];

			  set_opvar_int(tmppush2,
                                      splev->n_opcodes - tmppush2->vardata.l);
			  if_list[n_if_list++] = tmppush;
		      } else lc_error("IF: Huh?!  No else-part address?");
		  ;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1211 "lev_comp.y"
    {
		      if (n_if_list > 0) {
			  struct opvar *tmppush;
			  tmppush = (struct opvar *) if_list[--n_if_list];
			  set_opvar_int(tmppush, splev->n_opcodes - tmppush->vardata.l);
		      } else lc_error("IF: Huh?! No end address?");
		  ;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1221 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_MESSAGE));
		  ;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1227 "lev_comp.y"
    {
		      add_opvars(splev, "iiiiiio",
			      VA_PASS7(-1,  0, -1, -1, -1, -1, SPO_CORRIDOR));
		  ;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1232 "lev_comp.y"
    {
		      add_opvars(splev, "iiiiiio",
			      VA_PASS7(-1, (yyvsp[(3) - (3)].i), -1, -1, -1, -1, SPO_CORRIDOR));
		  ;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1237 "lev_comp.y"
    {
		      add_opvars(splev, "iiiiiio",
			      VA_PASS7(-1, -1, -1, -1, -1, -1, SPO_CORRIDOR));
		  ;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1244 "lev_comp.y"
    {
		      add_opvars(splev, "iiiiiio",
				 VA_PASS7((yyvsp[(3) - (5)].corpos).room, (yyvsp[(3) - (5)].corpos).door, (yyvsp[(3) - (5)].corpos).wall,
					  (yyvsp[(5) - (5)].corpos).room, (yyvsp[(5) - (5)].corpos).door, (yyvsp[(5) - (5)].corpos).wall,
					  SPO_CORRIDOR));
		  ;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1251 "lev_comp.y"
    {
		      add_opvars(splev, "iiiiiio",
				 VA_PASS7((yyvsp[(3) - (5)].corpos).room, (yyvsp[(3) - (5)].corpos).door, (yyvsp[(3) - (5)].corpos).wall,
					  -1, -1, (long)(yyvsp[(5) - (5)].i),
					  SPO_CORRIDOR));
		  ;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1260 "lev_comp.y"
    {
			(yyval.corpos).room = (yyvsp[(2) - (7)].i);
			(yyval.corpos).wall = (yyvsp[(4) - (7)].i);
			(yyval.corpos).door = (yyvsp[(6) - (7)].i);
		  ;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1268 "lev_comp.y"
    {
		      if (((yyvsp[(2) - (4)].i) < 100) && ((yyvsp[(1) - (4)].i) == OROOM))
			  lc_error("Only typed rooms can have a chance.");
		      else {
			  add_opvars(splev, "iii",
				     VA_PASS3((long)(yyvsp[(1) - (4)].i), (long)(yyvsp[(2) - (4)].i), (long)(yyvsp[(4) - (4)].i)));
		      }
                  ;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1279 "lev_comp.y"
    {
		      long rflags = (yyvsp[(8) - (10)].i);
		      long flmt = (long)(yyvsp[(9) - (10)].i);
		      long flt = (long)(yyvsp[(10) - (10)].i);

		      if (rflags == -1) rflags = (1 << 0);
		      if (flmt == -1) flmt = ROOM;
		      if (flt == -1) flt = 0;

		      add_opvars(splev, "iiiiiiiiio",
				 VA_PASS10(flt, flmt, rflags, ERR, ERR,
					  (yyvsp[(5) - (10)].crd).x, (yyvsp[(5) - (10)].crd).y, (yyvsp[(7) - (10)].sze).width, (yyvsp[(7) - (10)].sze).height,
					  SPO_SUBROOM));
		      break_stmt_start();
		  ;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1295 "lev_comp.y"
    {
		      break_stmt_end(splev);
		      add_opcode(splev, SPO_ENDROOM, NULL);
		  ;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1302 "lev_comp.y"
    {
		      long rflags = (yyvsp[(10) - (12)].i);
		      long flmt = (long)(yyvsp[(11) - (12)].i);
		      long flt = (long)(yyvsp[(12) - (12)].i);

		      if (rflags == -1) rflags = (1 << 0);

		      add_opvars(splev, "iiiiiiiiio",
				 VA_PASS10(flt, flmt, rflags,
					  (yyvsp[(7) - (12)].crd).x, (yyvsp[(7) - (12)].crd).y, (yyvsp[(5) - (12)].crd).x, (yyvsp[(5) - (12)].crd).y,
					  (yyvsp[(9) - (12)].sze).width, (yyvsp[(9) - (12)].sze).height, SPO_ROOM));
		      break_stmt_start();
		  ;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1316 "lev_comp.y"
    {
		      break_stmt_end(splev);
		      add_opcode(splev, SPO_ENDROOM, NULL);
		  ;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1323 "lev_comp.y"
    {
			(yyval.i) = 1;
		  ;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1327 "lev_comp.y"
    {
			(yyval.i) = (yyvsp[(2) - (2)].i);
		  ;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1333 "lev_comp.y"
    {
			if ( (yyvsp[(2) - (5)].i) < 1 || (yyvsp[(2) - (5)].i) > 5 ||
			    (yyvsp[(4) - (5)].i) < 1 || (yyvsp[(4) - (5)].i) > 5 ) {
			    lc_error("Room positions should be between 1-5: (%li,%li)!", (yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].i));
			} else {
			    (yyval.crd).x = (yyvsp[(2) - (5)].i);
			    (yyval.crd).y = (yyvsp[(4) - (5)].i);
			}
		  ;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1343 "lev_comp.y"
    {
			(yyval.crd).x = (yyval.crd).y = ERR;
		  ;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1349 "lev_comp.y"
    {
			if ( (yyvsp[(2) - (5)].i) < 0 || (yyvsp[(4) - (5)].i) < 0) {
			    lc_error("Invalid subroom position (%li,%li)!", (yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].i));
			} else {
			    (yyval.crd).x = (yyvsp[(2) - (5)].i);
			    (yyval.crd).y = (yyvsp[(4) - (5)].i);
			}
		  ;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1358 "lev_comp.y"
    {
			(yyval.crd).x = (yyval.crd).y = ERR;
		  ;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1364 "lev_comp.y"
    {
		      (yyval.crd).x = (yyvsp[(2) - (5)].i);
		      (yyval.crd).y = (yyvsp[(4) - (5)].i);
		  ;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1369 "lev_comp.y"
    {
		      (yyval.crd).x = (yyval.crd).y = ERR;
		  ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1375 "lev_comp.y"
    {
			(yyval.sze).width = (yyvsp[(2) - (5)].i);
			(yyval.sze).height = (yyvsp[(4) - (5)].i);
		  ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1380 "lev_comp.y"
    {
			(yyval.sze).height = (yyval.sze).width = ERR;
		  ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1386 "lev_comp.y"
    {
			/* ERR means random here */
			if ((yyvsp[(7) - (10)].i) == ERR && (yyvsp[(9) - (10)].i) != ERR) {
			    lc_error("If the door wall is random, so must be its pos!");
			} else {
			    add_opvars(splev, "iiiio",
				       VA_PASS5((long)(yyvsp[(9) - (10)].i), (long)(yyvsp[(5) - (10)].i), (long)(yyvsp[(3) - (10)].i),
						(long)(yyvsp[(7) - (10)].i), SPO_ROOM_DOOR));
			}
		  ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1397 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2((long)(yyvsp[(3) - (6)].i), SPO_DOOR));
		  ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1411 "lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(1) - (1)].i);
		  ;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1415 "lev_comp.y"
    {
		      (yyval.i) = ((yyvsp[(1) - (3)].i) | (yyvsp[(3) - (3)].i));
		  ;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1425 "lev_comp.y"
    {
		      struct opvar *stopit = New(struct opvar);
		      set_opvar_int(stopit, SP_D_V_END);
		      add_opcode(splev, SPO_PUSH, stopit);
		      (yyval.i) = 0x00;
		  ;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1432 "lev_comp.y"
    {
		      if (( (yyvsp[(1) - (3)].i) & (yyvsp[(3) - (3)].i) ))
			  lc_error("DOOR extra info '%s' defined twice.", curr_token);
		      (yyval.i) = ( (yyvsp[(1) - (3)].i) | (yyvsp[(3) - (3)].i) );
		  ;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1440 "lev_comp.y"
    {	
		      add_opvars(splev, "ii", VA_PASS2((yyvsp[(3) - (3)].i), SP_D_V_SUBTYPE));
		      (yyval.i) = 0x0001;
		  ;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1445 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_D_V_KEY_TYPE));
		      (yyval.i) = 0x0002;
		  ;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1450 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2((yyvsp[(3) - (3)].i), SP_D_V_SPECIAL_QUALITY));
		      (yyval.i) = 0x0004;
		  ;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1458 "lev_comp.y"
    {
		      add_opvars(splev, "ciisiio",
				 VA_PASS7(0, 0, 1, (char *) 0, 0, 0, SPO_MAP));
		      max_x_map = COLNO-1;
		      max_y_map = ROWNO;
		  ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1465 "lev_comp.y"
    {
		      add_opvars(splev, "cii",
				 VA_PASS3(SP_COORD_PACK(((yyvsp[(3) - (7)].i)), ((yyvsp[(5) - (7)].i))),
					  1, (int) (yyvsp[(6) - (7)].i)));
		      scan_map((yyvsp[(7) - (7)].map), splev);
		      Free((yyvsp[(7) - (7)].map));
		  ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1473 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(2, (int) (yyvsp[(4) - (5)].i)));
		      scan_map((yyvsp[(5) - (5)].map), splev);
		      Free((yyvsp[(5) - (5)].map));
		  ;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1489 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2(0, SPO_MONSTER));
		  ;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1493 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2(1, SPO_MONSTER));
		      in_container_obj++;
		      break_stmt_start();
		  ;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1499 "lev_comp.y"
    {
		     break_stmt_end(splev);
		     in_container_obj--;
		     add_opvars(splev, "o", VA_PASS1(SPO_END_MONINVENT));
		 ;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1507 "lev_comp.y"
    {
		      /* nothing */
		  ;}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1513 "lev_comp.y"
    {
		      struct opvar *stopit = New(struct opvar);

		      set_opvar_int(stopit, SP_M_V_END);
		      add_opcode(splev, SPO_PUSH, stopit);
		      (yyval.i) = 0x00000000;
		  ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1521 "lev_comp.y"
    {
		      if (( (yyvsp[(1) - (3)].i) & (yyvsp[(3) - (3)].i) ))
			  lc_error("MONSTER extra info defined twice.");
		      (yyval.i) = ( (yyvsp[(1) - (3)].i) | (yyvsp[(3) - (3)].i) );
		  ;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1529 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_M_V_NAME));
		      (yyval.i) = 0x00000001;
		  ;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1534 "lev_comp.y"
    {
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[(1) - (1)].i), SP_M_V_PEACEFUL));
		      (yyval.i) = 0x00000002;
		  ;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1540 "lev_comp.y"
    {
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[(1) - (1)].i), SP_M_V_ASLEEP));
		      (yyval.i) = 0x00000004;
		  ;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1546 "lev_comp.y"
    {
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[(1) - (1)].i), SP_M_V_ALIGN));
		      (yyval.i) = 0x00000008;
		  ;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1552 "lev_comp.y"
    {
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[(1) - (2)].i), SP_M_V_APPEAR));
		      (yyval.i) = 0x00000010;
		  ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1558 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_FEMALE));
		      (yyval.i) = 0x00000020;
		  ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1563 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_INVIS));
		      (yyval.i) = 0x00000040;
		  ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1568 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_CANCELLED));
		      (yyval.i) = 0x00000080;
		  ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1573 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_REVIVED));
		      (yyval.i) = 0x00000100;
		  ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1578 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_AVENGE));
		      (yyval.i) = 0x00000200;
		  ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1583 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_M_V_FLEEING));
		      (yyval.i) = 0x00000400;
		  ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1588 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_M_V_BLINDED));
		      (yyval.i) = 0x00000800;
		  ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1593 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_M_V_PARALYZED));
		      (yyval.i) = 0x00001000;
		  ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1598 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_STUNNED));
		      (yyval.i) = 0x00002000;
		  ;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1603 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_CONFUSED));
		      (yyval.i) = 0x00004000;
		  ;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1608 "lev_comp.y"
    {
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[(3) - (3)].i), SP_M_V_SEENTRAPS));
		      (yyval.i) = 0x00008000;
		  ;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1614 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_M_V_WAITFORU));
		      (yyval.i) = 0x00010000;
		  ;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 1621 "lev_comp.y"
    {
		      int token = get_trap_type((yyvsp[(1) - (1)].map));

		      if (token == ERR || token == 0)
			  lc_error("Unknown trap type '%s'!", (yyvsp[(1) - (1)].map));
                      Free((yyvsp[(1) - (1)].map));
		      (yyval.i) = (1L << (token - 1));
		  ;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 1630 "lev_comp.y"
    {
		      (yyval.i) = (long) ~0;
		  ;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 1634 "lev_comp.y"
    {
		      int token = get_trap_type((yyvsp[(1) - (3)].map));
		      if (token == ERR || token == 0)
			  lc_error("Unknown trap type '%s'!", (yyvsp[(1) - (3)].map));

		      if ((1L << (token - 1)) & (yyvsp[(3) - (3)].i))
			  lc_error("Monster seen_traps, trap '%s' listed twice.", (yyvsp[(1) - (3)].map));
                      Free((yyvsp[(1) - (3)].map));
		      (yyval.i) = ((1L << (token - 1)) | (yyvsp[(3) - (3)].i));
		  ;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 1647 "lev_comp.y"
    {
		      int cnt = 0;

		      if (in_container_obj)
                          cnt |= SP_OBJ_CONTENT;
		      add_opvars(splev, "io", VA_PASS2(cnt, SPO_OBJECT));
		  ;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 1655 "lev_comp.y"
    {
		      int cnt = SP_OBJ_CONTAINER;

		      if (in_container_obj)
                          cnt |= SP_OBJ_CONTENT;
		      add_opvars(splev, "io", VA_PASS2(cnt, SPO_OBJECT));
		      in_container_obj++;
		      break_stmt_start();
		  ;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 1665 "lev_comp.y"
    {
		     break_stmt_end(splev);
		     in_container_obj--;
		     add_opcode(splev, SPO_POP_CONTAINER, NULL);
		 ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 1673 "lev_comp.y"
    {
		      if (( (yyvsp[(2) - (2)].i) & 0x4000) && in_container_obj)
                          lc_error("Object cannot have a coord when contained.");
		      else if (!( (yyvsp[(2) - (2)].i) & 0x4000) && !in_container_obj)
                          lc_error("Object needs a coord when not contained.");
		  ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 1682 "lev_comp.y"
    {
		      struct opvar *stopit = New(struct opvar);
		      set_opvar_int(stopit, SP_O_V_END);
		      add_opcode(splev, SPO_PUSH, stopit);
		      (yyval.i) = 0x00;
		  ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 1689 "lev_comp.y"
    {
		      if (( (yyvsp[(1) - (3)].i) & (yyvsp[(3) - (3)].i) ))
			  lc_error("OBJECT extra info '%s' defined twice.", curr_token);
		      (yyval.i) = ( (yyvsp[(1) - (3)].i) | (yyvsp[(3) - (3)].i) );
		  ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 1697 "lev_comp.y"
    {
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[(1) - (1)].i), SP_O_V_CURSE));
		      (yyval.i) = 0x0001;
		  ;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 1703 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_CORPSENM));
		      (yyval.i) = 0x0002;
		  ;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 1708 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_SPE));
		      (yyval.i) = 0x0004;
		  ;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 1713 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_NAME));
		      (yyval.i) = 0x0008;
		  ;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 1718 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_QUAN));
		      (yyval.i) = 0x0010;
		  ;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 1723 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_O_V_BURIED));
		      (yyval.i) = 0x0020;
		  ;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 1728 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2((int) (yyvsp[(1) - (1)].i), SP_O_V_LIT));
		      (yyval.i) = 0x0040;
		  ;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 1733 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_ERODED));
		      (yyval.i) = 0x0080;
		  ;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 1738 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(-1, SP_O_V_ERODED));
		      (yyval.i) = 0x0080;
		  ;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 1743 "lev_comp.y"
    {
		      if ((yyvsp[(1) - (1)].i) == D_LOCKED) {
			  add_opvars(splev, "ii", VA_PASS2(1, SP_O_V_LOCKED));
			  (yyval.i) = 0x0100;
		      } else if ((yyvsp[(1) - (1)].i) == D_BROKEN) {
			  add_opvars(splev, "ii", VA_PASS2(1, SP_O_V_BROKEN));
			  (yyval.i) = 0x0200;
		      } else
			  lc_error("DOOR state can only be locked or broken.");
		  ;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 1754 "lev_comp.y"
    {
		      add_opvars(splev, "ii",
                                 VA_PASS2((int) (yyvsp[(1) - (1)].i), SP_O_V_TRAPPED));
		      (yyval.i) = 0x0400;
		  ;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 1760 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_RECHARGED));
		      (yyval.i) = 0x0800;
		  ;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 1765 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_O_V_INVIS));
		      (yyval.i) = 0x1000;
		  ;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 1770 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_O_V_GREASED));
		      (yyval.i) = 0x2000;
		  ;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 1775 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_COORD));
		      (yyval.i) = 0x4000;
		  ;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 1780 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2((int)(yyvsp[(3) - (3)].i), SP_O_V_ELEMENTAL_ENCHANTMENT));
		      (yyval.i) = 0x8000;
		  ;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 1785 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2((int)(yyvsp[(3) - (3)].i), SP_O_V_EXCEPTIONALITY));
		      (yyval.i) = 0x10000;
		  ;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 1790 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_ENCHANTMENT));
		      (yyval.i) = 0x20000;
		  ;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 1795 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_CHARGES));
		      (yyval.i) = 0x40000;
		  ;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 1800 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_SPECIAL_QUALITY));
		      (yyval.i) = 0x80000;
		  ;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 1805 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_SPEFLAGS));
		      (yyval.i) = 0x100000;
		  ;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 1810 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_O_V_KEY_TYPE));
		      (yyval.i) = 0x200000;
		  ;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 1815 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2(1, SP_O_V_INDESTRUCTIBLE));
		      (yyval.i) = 0x400000;
		  ;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 1822 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2((int) (yyvsp[(3) - (5)].i), SPO_TRAP));
		  ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 1828 "lev_comp.y"
    {
		       long dir, state = 0;

		       /* convert dir from a DIRECTION to a DB_DIR */
		       dir = (yyvsp[(5) - (7)].i);
		       switch (dir) {
		       case W_NORTH: dir = DB_NORTH; break;
		       case W_SOUTH: dir = DB_SOUTH; break;
		       case W_EAST:  dir = DB_EAST;  break;
		       case W_WEST:  dir = DB_WEST;  break;
		       default:
			   lc_error("Invalid drawbridge direction.");
			   break;
		       }

		       if ( (yyvsp[(7) - (7)].i) == D_ISOPEN )
			   state = 1;
		       else if ( (yyvsp[(7) - (7)].i) == D_CLOSED )
			   state = 0;
		       else if ( (yyvsp[(7) - (7)].i) == -1 )
			   state = -1;
		       else
			   lc_error("A drawbridge can only be open, closed or random!");
		       add_opvars(splev, "iio",
				  VA_PASS3(state, dir, SPO_DRAWBRIDGE));
		   ;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 1857 "lev_comp.y"
    {
		      add_opvars(splev, "iiio",
				 VA_PASS4((int) (yyvsp[(5) - (5)].i), 1, 0, SPO_MAZEWALK));
		  ;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 1862 "lev_comp.y"
    {
		      add_opvars(splev, "iiio",
				 VA_PASS4((int) (yyvsp[(5) - (8)].i), (int) (yyvsp[(7) - (8)].i),
					  (int) (yyvsp[(8) - (8)].i), SPO_MAZEWALK));
		  ;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 1870 "lev_comp.y"
    {
		      add_opvars(splev, "rio",
				 VA_PASS3(SP_REGION_PACK(-1,-1,-1,-1),
					  0, SPO_WALLIFY));
		  ;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 1876 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2(1, SPO_WALLIFY));
		  ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 1882 "lev_comp.y"
    {
		      add_opvars(splev, "io",
				 VA_PASS2((int) (yyvsp[(5) - (5)].i), SPO_LADDER));
		  ;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 1889 "lev_comp.y"
    {
		      add_opvars(splev, "io",
				 VA_PASS2((int) (yyvsp[(5) - (5)].i), SPO_STAIR));
		  ;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 1896 "lev_comp.y"
    {
		      add_opvars(splev, "iiiii iiiii iiso",
				 VA_PASS14((yyvsp[(3) - (7)].lregn).x1, (yyvsp[(3) - (7)].lregn).y1, (yyvsp[(3) - (7)].lregn).x2, (yyvsp[(3) - (7)].lregn).y2, (yyvsp[(3) - (7)].lregn).area,
					   (yyvsp[(5) - (7)].lregn).x1, (yyvsp[(5) - (7)].lregn).y1, (yyvsp[(5) - (7)].lregn).x2, (yyvsp[(5) - (7)].lregn).y2, (yyvsp[(5) - (7)].lregn).area,
				     (long) (((yyvsp[(7) - (7)].i)) ? LR_UPSTAIR : LR_DOWNSTAIR),
					   0, (char *) 0, SPO_LEVREGION));
		  ;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 1906 "lev_comp.y"
    {
		      add_opvars(splev, "iiiii iiiii iiso",
				 VA_PASS14((yyvsp[(3) - (7)].lregn).x1, (yyvsp[(3) - (7)].lregn).y1, (yyvsp[(3) - (7)].lregn).x2, (yyvsp[(3) - (7)].lregn).y2, (yyvsp[(3) - (7)].lregn).area,
					   (yyvsp[(5) - (7)].lregn).x1, (yyvsp[(5) - (7)].lregn).y1, (yyvsp[(5) - (7)].lregn).x2, (yyvsp[(5) - (7)].lregn).y2, (yyvsp[(5) - (7)].lregn).area,
					   LR_PORTAL, 0, (yyvsp[(7) - (7)].map), SPO_LEVREGION));
		      Free((yyvsp[(7) - (7)].map));
		  ;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 1916 "lev_comp.y"
    {
		      long rtyp = 0;
		      switch((yyvsp[(6) - (6)].i)) {
		      case -1: rtyp = LR_TELE; break;
		      case  0: rtyp = LR_DOWNTELE; break;
		      case  1: rtyp = LR_UPTELE; break;
		      }
		      add_opvars(splev, "iiiii iiiii iiso",
				 VA_PASS14((yyvsp[(3) - (6)].lregn).x1, (yyvsp[(3) - (6)].lregn).y1, (yyvsp[(3) - (6)].lregn).x2, (yyvsp[(3) - (6)].lregn).y2, (yyvsp[(3) - (6)].lregn).area,
					   (yyvsp[(5) - (6)].lregn).x1, (yyvsp[(5) - (6)].lregn).y1, (yyvsp[(5) - (6)].lregn).x2, (yyvsp[(5) - (6)].lregn).y2, (yyvsp[(5) - (6)].lregn).area,
					   rtyp, 0, (char *)0, SPO_LEVREGION));
		  ;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 1931 "lev_comp.y"
    {
		      add_opvars(splev, "iiiii iiiii iiso",
				 VA_PASS14((yyvsp[(3) - (5)].lregn).x1, (yyvsp[(3) - (5)].lregn).y1, (yyvsp[(3) - (5)].lregn).x2, (yyvsp[(3) - (5)].lregn).y2, (yyvsp[(3) - (5)].lregn).area,
					   (yyvsp[(5) - (5)].lregn).x1, (yyvsp[(5) - (5)].lregn).y1, (yyvsp[(5) - (5)].lregn).x2, (yyvsp[(5) - (5)].lregn).y2, (yyvsp[(5) - (5)].lregn).area,
					   (long) LR_BRANCH, 0,
					   (char *) 0, SPO_LEVREGION));
		  ;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 1941 "lev_comp.y"
    {
			(yyval.i) = -1;
		  ;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 1945 "lev_comp.y"
    {
			(yyval.i) = (yyvsp[(2) - (2)].i);
		  ;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 1951 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2((int)(yyvsp[(5) - (5)].i), SPO_FOUNTAIN));
		  ;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 1957 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_THRONE));
		  ;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 1963 "lev_comp.y"
    {
		      add_opvars(splev, "iio", VA_PASS3((int) (yyvsp[(9) - (11)].i), (int) (yyvsp[(11) - (11)].i), SPO_MODRON_PORTAL));
		  ;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 1969 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2((int) (yyvsp[(5) - (6)].i), SPO_LEVER));
		  ;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 1975 "lev_comp.y"
    {
		      struct opvar *stopit = New(struct opvar);
		      set_opvar_int(stopit, SP_L_V_END);
		      add_opcode(splev, SPO_PUSH, stopit);
		      (yyval.i) = 0x00;
		  ;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 1982 "lev_comp.y"
    {
		      if (( (yyvsp[(1) - (3)].i) & (yyvsp[(3) - (3)].i) ))
			  lc_error("LEVER extra info '%s' defined twice.", curr_token);
		      (yyval.i) = ( (yyvsp[(1) - (3)].i) | (yyvsp[(3) - (3)].i) );
		  ;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 1990 "lev_comp.y"
    {	
		      add_opvars(splev, "ii",
				 VA_PASS2((int) (yyvsp[(1) - (1)].i), SP_L_V_ACTIVE));
		      (yyval.i) = 0x0001;
		  ;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 1996 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_L_V_MONSTER));
		      (yyval.i) = 0x0002;
		  ;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 2001 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_L_V_OBJECT));
		      (yyval.i) = 0x0004;
		  ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 2006 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2((int)(yyvsp[(3) - (3)].terr).ter, SP_L_V_TERRAIN));
		      (yyval.i) = 0x0008;
		  ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 2011 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2((int)(yyvsp[(3) - (3)].terr).ter, SP_L_V_TERRAIN2));
		      (yyval.i) = 0x0010;
		  ;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 2016 "lev_comp.y"
    {	
		      add_opvars(splev, "ii",
				 VA_PASS2(1, SP_L_V_SWITCHABLE));
		      (yyval.i) = 0x0020;
		  ;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 2022 "lev_comp.y"
    {	
		      add_opvars(splev, "ii",
				 VA_PASS2(1, SP_L_V_CONTINUOUS));
		      (yyval.i) = 0x0040;
		  ;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 2028 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1(SP_L_V_COORD));
		      (yyval.i) = 0x0080;
		  ;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 2033 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2((yyvsp[(3) - (3)].i), SP_L_V_TRAP));
		      (yyval.i) = 0x0100;
		  ;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 2038 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2((yyvsp[(3) - (3)].i), SP_L_V_SUBTYPE));
		      (yyval.i) = 0x0200;
		  ;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 2043 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2((yyvsp[(3) - (3)].i), SP_L_V_CATEGORY));
		      (yyval.i) = 0x0400;
		  ;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 2048 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2((yyvsp[(3) - (3)].i), SP_L_V_EFFECT_FLAG));
		      (yyval.i) = 0x0800;
		  ;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 2053 "lev_comp.y"
    {
		      add_opvars(splev, "ii", VA_PASS2((yyvsp[(3) - (3)].i), SP_L_V_SPECIAL_QUALITY));
		      (yyval.i) = 0x1000;
		  ;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 2063 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_SINK));
		  ;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 2069 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_POOL));
		  ;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 2075 "lev_comp.y"
    {
		      (yyval.terr).lit = -2;
		      (yyval.terr).ter = what_map_char((char) (yyvsp[(1) - (1)].i));
		  ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 2080 "lev_comp.y"
    {
		      (yyval.terr).lit = (yyvsp[(4) - (5)].i);
		      (yyval.terr).ter = what_map_char((char) (yyvsp[(2) - (5)].i));
		  ;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 2087 "lev_comp.y"
    {
		      add_opvars(splev, "io",
				 VA_PASS2((yyvsp[(9) - (9)].i), SPO_REPLACETERRAIN));
		  ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 2094 "lev_comp.y"
    {
		     add_opvars(splev, "o", VA_PASS1(SPO_TERRAIN));
		 ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 2100 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_NON_DIGGABLE));
		  ;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 2106 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_NON_PASSWALL));
		  ;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 2112 "lev_comp.y"
    {
		      add_opvars(splev, "Miso", VA_PASS4(-1, (yyvsp[(5) - (5)].i), (yyvsp[(3) - (5)].map), SPO_NAMING));
		  ;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 2116 "lev_comp.y"
    {
		      add_opvars(splev, "iso", VA_PASS3((yyvsp[(5) - (9)].i), (yyvsp[(3) - (9)].map), SPO_NAMING));
		  ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 2122 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2((yyvsp[(5) - (5)].i), SPO_SPECIAL_REGION));
		  ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 2128 "lev_comp.y"
    {
		      add_opvars(splev, "iiiii iiiii iiso",
				 VA_PASS14((yyvsp[(3) - (5)].lregn).x1, (yyvsp[(3) - (5)].lregn).y1, (yyvsp[(3) - (5)].lregn).x2, (yyvsp[(3) - (5)].lregn).y2, (yyvsp[(3) - (5)].lregn).area,
					   0, 0, 0, 0, 1,
					   (yyvsp[(5) - (5)].i) == REGION_SPECIAL_LEVEL_SEEN ? (long) LR_SPECIAL_MAP_SEEN : (long) LR_SPECIAL_MAP_NAME_REVEALED, 0,
					   (char *) 0, SPO_LEVREGION));
		  ;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 2138 "lev_comp.y"
    {
		      long irr;
		      long rt = (yyvsp[(7) - (10)].i);
		      long rflags = (yyvsp[(8) - (10)].i);
		      long flmt = (long)(yyvsp[(9) - (10)].i);
		      long flt = (long)(yyvsp[(10) - (10)].i);

		      if (rflags == -1) rflags = (1 << 0);
		      if (flmt == -1) flmt = ROOM;
		      if (flt == -1) flt = 0;

		      if (!(rflags & 1)) rt += MAXRTYPE+1;
		      irr = ((rflags & 2) != 0);
		      add_opvars(splev, "iiiiio",
				 VA_PASS6((long)(yyvsp[(5) - (10)].i), rt, rflags, flmt, flt, SPO_REGION));
		      (yyval.i) = (irr || (rflags & 1) || rt != OROOM);
		      break_stmt_start();
		  ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 2157 "lev_comp.y"
    {
		      break_stmt_end(splev);
			  add_opcode(splev, SPO_ENDROOM, NULL);
		      /*if ( $<i>9 ||  $<i>10 ||  $<i>11 ) {
			  	add_opcode(splev, SPO_ENDROOM, NULL);
		       } else if ( $<i>12 )
			  	lc_error("Cannot use lev statements in non-permanent REGION");
		      */
		  ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 2169 "lev_comp.y"
    {
		      (yyval.i) = 0;
		  ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2173 "lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(1) - (1)].i);
		  ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 2179 "lev_comp.y"
    {
		      add_opvars(splev, "iio",
				 VA_PASS3((long)(yyvsp[(7) - (7)].i), (long)(yyvsp[(5) - (7)].i), SPO_ALTAR));
		  ;}
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 2186 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_ANVIL));
		  ;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 2192 "lev_comp.y"
    {
		      add_opvars(splev, "iio", VA_PASS3((int)(yyvsp[(7) - (7)].i), (int)(yyvsp[(5) - (7)].i), SPO_FLOOR));
		  ;}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 2198 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2((int)(yyvsp[(5) - (5)].i), SPO_SUBTYPE));
		  ;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 2204 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2((int)(yyvsp[(3) - (5)].i), SPO_NPC));
		  ;}
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 2210 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2(2, SPO_GRAVE));
		  ;}
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 2214 "lev_comp.y"
    {
		      add_opvars(splev, "sio",
				 VA_PASS3((char *)0, 1, SPO_GRAVE));
		  ;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 2219 "lev_comp.y"
    {
		      add_opvars(splev, "sio",
				 VA_PASS3((char *)0, 0, SPO_GRAVE));
		  ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 2226 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_GOLD));
		  ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 2232 "lev_comp.y"
    {
		      add_opvars(splev, "io",
				 VA_PASS2((long)(yyvsp[(5) - (7)].i), SPO_ENGRAVING));
		  ;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 2239 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_MINERALIZE));
		  ;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 2243 "lev_comp.y"
    {
		      add_opvars(splev, "iiiio",
				 VA_PASS5(-1L, -1L, -1L, -1L, SPO_MINERALIZE));
		  ;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 2250 "lev_comp.y"
    {
			int token = get_trap_type((yyvsp[(1) - (1)].map));
			if (token == ERR)
			    lc_error("Unknown trap type '%s'!", (yyvsp[(1) - (1)].map));
			(yyval.i) = token;
			Free((yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2261 "lev_comp.y"
    {
			int token = get_room_type((yyvsp[(1) - (1)].map));
			if (token == ERR) {
			    lc_warning("Unknown room type \"%s\"!  Making ordinary room...", (yyvsp[(1) - (1)].map));
				(yyval.i) = OROOM;
			} else
				(yyval.i) = token;
			Free((yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 2274 "lev_comp.y"
    {
			(yyval.i) = -1;
		  ;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 2278 "lev_comp.y"
    {
			(yyval.i) = (yyvsp[(2) - (2)].i);
		  ;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 2284 "lev_comp.y"
    {
			(yyval.i) = (yyvsp[(1) - (1)].i);
		  ;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 2288 "lev_comp.y"
    {
			(yyval.i) = (yyvsp[(1) - (3)].i) | (yyvsp[(3) - (3)].i);
		  ;}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 2295 "lev_comp.y"
    {
		      (yyval.i) = ((yyvsp[(1) - (1)].i) << 0);
		  ;}
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 2299 "lev_comp.y"
    {
		      (yyval.i) = ((yyvsp[(1) - (1)].i) << 1);
		  ;}
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 2303 "lev_comp.y"
    {
		      (yyval.i) = ((yyvsp[(1) - (1)].i) << 2);
		  ;}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 2309 "lev_comp.y"
    {
			(yyval.i) = ROOM;
		  ;}
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 2313 "lev_comp.y"
    {
			(yyval.i) = (yyvsp[(3) - (3)].i);
		  ;}
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 2319 "lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(1) - (1)].i);
		  ;}
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 2325 "lev_comp.y"
    {
			(yyval.i) = 0;
		  ;}
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 2329 "lev_comp.y"
    {
			(yyval.i) = (yyvsp[(3) - (3)].i);
		  ;}
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 2335 "lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(1) - (1)].i);
		  ;}
    break;

  case 358:

/* Line 1455 of yacc.c  */
#line 2351 "lev_comp.y"
    {
			(yyval.i) = - MAX_REGISTERS - 1;
		  ;}
    break;

  case 361:

/* Line 1455 of yacc.c  */
#line 2359 "lev_comp.y"
    {
			(yyval.i) = - MAX_REGISTERS - 1;
		  ;}
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 2369 "lev_comp.y"
    {
			if ( (yyvsp[(3) - (4)].i) >= 3 )
				lc_error("Register Index overflow!");
			else
				(yyval.i) = - (yyvsp[(3) - (4)].i) - 1;
		  ;}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 2378 "lev_comp.y"
    {
		      add_opvars(splev, "s", VA_PASS1((yyvsp[(1) - (1)].map)));
		      Free((yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 2383 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (1)].map), SPOVAR_STRING);
		      vardef_used(vardefs, (yyvsp[(1) - (1)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (1)].map)));
		      Free((yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 2390 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (4)].map),
                                        SPOVAR_STRING | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[(1) - (4)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (4)].map)));
		      Free((yyvsp[(1) - (4)].map));
		  ;}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 2401 "lev_comp.y"
    {
		      /* nothing */
		  ;}
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 2407 "lev_comp.y"
    {
		      add_opvars(splev, "c", VA_PASS1((yyvsp[(1) - (1)].i)));
		  ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2411 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_RNDCOORD));
		  ;}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 2415 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (1)].map), SPOVAR_COORD);
		      vardef_used(vardefs, (yyvsp[(1) - (1)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (1)].map)));
		      Free((yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 2422 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (4)].map),
                                        SPOVAR_COORD | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[(1) - (4)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (4)].map)));
		      Free((yyvsp[(1) - (4)].map));
		  ;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2432 "lev_comp.y"
    {
		      if ((yyvsp[(2) - (5)].i) < 0 || (yyvsp[(4) - (5)].i) < 0 || (yyvsp[(2) - (5)].i) >= COLNO || (yyvsp[(4) - (5)].i) >= ROWNO)
                          lc_error("Coordinates (%li,%li) out of map range!",
                                   (yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].i));
		      (yyval.i) = SP_COORD_PACK((yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].i));
		  ;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2439 "lev_comp.y"
    {
		      (yyval.i) = SP_COORD_PACK_RANDOM(0);
		  ;}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2443 "lev_comp.y"
    {
		      (yyval.i) = SP_COORD_PACK_RANDOM((yyvsp[(2) - (3)].i));
		  ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2449 "lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(1) - (1)].i);
		  ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2453 "lev_comp.y"
    {
		      if (((yyvsp[(1) - (3)].i) & (yyvsp[(3) - (3)].i)))
			  lc_warning("Humidity flag used twice.");
		      (yyval.i) = ((yyvsp[(1) - (3)].i) | (yyvsp[(3) - (3)].i));
		  ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2461 "lev_comp.y"
    {
		      /* nothing */
		  ;}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 2465 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (1)].map), SPOVAR_REGION);
		      vardef_used(vardefs, (yyvsp[(1) - (1)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (1)].map)));
		      Free((yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 2472 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (4)].map),
                                        SPOVAR_REGION | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[(1) - (4)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (4)].map)));
		      Free((yyvsp[(1) - (4)].map));
		  ;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 2482 "lev_comp.y"
    {
		      long r = SP_REGION_PACK((yyvsp[(2) - (9)].i), (yyvsp[(4) - (9)].i), (yyvsp[(6) - (9)].i), (yyvsp[(8) - (9)].i));

		      if ((yyvsp[(2) - (9)].i) > (yyvsp[(6) - (9)].i) || (yyvsp[(4) - (9)].i) > (yyvsp[(8) - (9)].i))
			  lc_error("Region start > end: (%ld,%ld,%ld,%ld)!",
                                   (yyvsp[(2) - (9)].i), (yyvsp[(4) - (9)].i), (yyvsp[(6) - (9)].i), (yyvsp[(8) - (9)].i));

		      add_opvars(splev, "r", VA_PASS1(r));
		      (yyval.i) = r;
		  ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2495 "lev_comp.y"
    {
		      add_opvars(splev, "m", VA_PASS1((yyvsp[(1) - (1)].i)));
		  ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2499 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (1)].map), SPOVAR_MAPCHAR);
		      vardef_used(vardefs, (yyvsp[(1) - (1)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (1)].map)));
		      Free((yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2506 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (4)].map),
                                        SPOVAR_MAPCHAR | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[(1) - (4)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (4)].map)));
		      Free((yyvsp[(1) - (4)].map));
		  ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2516 "lev_comp.y"
    {
		      if (what_map_char((char) (yyvsp[(1) - (1)].i)) != INVALID_TYPE)
			  (yyval.i) = SP_MAPCHAR_PACK(what_map_char((char) (yyvsp[(1) - (1)].i)), -2);
		      else {
			  lc_error("Unknown map char type '%c'!", (yyvsp[(1) - (1)].i));
			  (yyval.i) = SP_MAPCHAR_PACK(STONE, -2);
		      }
		  ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2525 "lev_comp.y"
    {
		      if (what_map_char((char) (yyvsp[(2) - (5)].i)) != INVALID_TYPE)
			  (yyval.i) = SP_MAPCHAR_PACK(what_map_char((char) (yyvsp[(2) - (5)].i)), (yyvsp[(4) - (5)].i));
		      else {
			  lc_error("Unknown map char type '%c'!", (yyvsp[(2) - (5)].i));
			  (yyval.i) = SP_MAPCHAR_PACK(STONE, (yyvsp[(4) - (5)].i));
		      }
		  ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2536 "lev_comp.y"
    {
		      add_opvars(splev, "M", VA_PASS1((yyvsp[(1) - (1)].i)));
		  ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2540 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (1)].map), SPOVAR_MONST);
		      vardef_used(vardefs, (yyvsp[(1) - (1)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (1)].map)));
		      Free((yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2547 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (4)].map),
                                        SPOVAR_MONST | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[(1) - (4)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (4)].map)));
		      Free((yyvsp[(1) - (4)].map));
		  ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2557 "lev_comp.y"
    {
                      long m = get_monster_id((yyvsp[(1) - (1)].map), (char)0);
                      if (m == ERR) {
                          lc_error("Unknown monster \"%s\"!", (yyvsp[(1) - (1)].map));
                          (yyval.i) = -1;
                      } else
                          (yyval.i) = SP_MONST_PACK(m,
                                         def_monsyms[(int) mons[m].mlet].sym);
                      Free((yyvsp[(1) - (1)].map));
                  ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2568 "lev_comp.y"
    {
                        if (check_monster_char((char) (yyvsp[(1) - (1)].i)))
                            (yyval.i) = SP_MONST_PACK(-1, (yyvsp[(1) - (1)].i));
                        else {
                            lc_error("Unknown monster class '%c'!", (yyvsp[(1) - (1)].i));
                            (yyval.i) = -1;
                        }
                  ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2577 "lev_comp.y"
    {
                      long m = get_monster_id((yyvsp[(4) - (5)].map), (char) (yyvsp[(2) - (5)].i));
                      if (m == ERR) {
                          lc_error("Unknown monster ('%c', \"%s\")!", (yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].map));
                          (yyval.i) = -1;
                      } else
                          (yyval.i) = SP_MONST_PACK(m, (yyvsp[(2) - (5)].i));
                      Free((yyvsp[(4) - (5)].map));
                  ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2587 "lev_comp.y"
    {
                      (yyval.i) = -1;
                  ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2593 "lev_comp.y"
    {
		      add_opvars(splev, "O", VA_PASS1((yyvsp[(1) - (1)].i)));
		  ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2597 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (1)].map), SPOVAR_OBJ);
		      vardef_used(vardefs, (yyvsp[(1) - (1)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (1)].map)));
		      Free((yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2604 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (4)].map),
                                        SPOVAR_OBJ | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[(1) - (4)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (4)].map)));
		      Free((yyvsp[(1) - (4)].map));
		  ;}
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 2614 "lev_comp.y"
    {
		      long m = get_object_id((yyvsp[(1) - (1)].map), (char)0);
		      if (m == ERR) {
			  lc_error("Unknown object \"%s\"!", (yyvsp[(1) - (1)].map));
			  (yyval.i) = -1;
		      } else
                          /* obj class != 0 to force generation of a specific item */
                          (yyval.i) = SP_OBJ_PACK(m, 1);
                      Free((yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2625 "lev_comp.y"
    {
			if (check_object_char((char) (yyvsp[(1) - (1)].i)))
			    (yyval.i) = SP_OBJ_PACK(-1, (yyvsp[(1) - (1)].i));
			else {
			    lc_error("Unknown object class '%c'!", (yyvsp[(1) - (1)].i));
			    (yyval.i) = -1;
			}
		  ;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2634 "lev_comp.y"
    {
		      long m = get_object_id((yyvsp[(4) - (5)].map), (char) (yyvsp[(2) - (5)].i));
		      if (m == ERR) {
			  lc_error("Unknown object ('%c', \"%s\")!", (yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].map));
			  (yyval.i) = -1;
		      } else
			  (yyval.i) = SP_OBJ_PACK(m, (yyvsp[(2) - (5)].i));
                      Free((yyvsp[(4) - (5)].map));
		  ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2644 "lev_comp.y"
    {
		      (yyval.i) = OBJECT_SPECIAL_CREATE_TYPE_RANDOM;
		  ;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2648 "lev_comp.y"
    {
  			  (yyval.i) = (yyvsp[(1) - (1)].i);
		  ;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 2654 "lev_comp.y"
    { ;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2656 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_ADD));
		  ;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 2662 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1((yyvsp[(1) - (1)].i)));
		  ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2666 "lev_comp.y"
    {
		      is_inconstant_number = 1;
		  ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2670 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1((yyvsp[(2) - (3)].i)));
		  ;}
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 2674 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (1)].map), SPOVAR_INT);
		      vardef_used(vardefs, (yyvsp[(1) - (1)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (1)].map)));
		      Free((yyvsp[(1) - (1)].map));
		      is_inconstant_number = 1;
		  ;}
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 2682 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (4)].map),
					SPOVAR_INT | SPOVAR_ARRAY);
		      vardef_used(vardefs, (yyvsp[(1) - (4)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (4)].map)));
		      Free((yyvsp[(1) - (4)].map));
		      is_inconstant_number = 1;
		  ;}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2691 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_ADD));
		  ;}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 2695 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_SUB));
		  ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2699 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_MUL));
		  ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2703 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_DIV));
		  ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2707 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_MATH_MOD));
		  ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2710 "lev_comp.y"
    { ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2714 "lev_comp.y"
    {
		      if (!strcmp("int", (yyvsp[(1) - (1)].map)) || !strcmp("integer", (yyvsp[(1) - (1)].map))) {
			  (yyval.i) = (int)'i';
		      } else
			  lc_error("Unknown function parameter type '%s'", (yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2721 "lev_comp.y"
    {
		      if (!strcmp("str", (yyvsp[(1) - (1)].map)) || !strcmp("string", (yyvsp[(1) - (1)].map))) {
			  (yyval.i) = (int)'s';
		      } else
			  lc_error("Unknown function parameter type '%s'", (yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2730 "lev_comp.y"
    {
		      struct lc_funcdefs_parm *tmp = New(struct lc_funcdefs_parm);

		      if (!curr_function) {
			  lc_error("Function parameters outside function definition.");
		      } else if (!tmp) {
			  lc_error("Could not alloc function params.");
		      } else {
			  long vt = SPOVAR_NULL;

			  tmp->name = strdup((yyvsp[(1) - (3)].map));
			  tmp->parmtype = (char) (yyvsp[(3) - (3)].i);
			  tmp->next = curr_function->params;
			  curr_function->params = tmp;
			  curr_function->n_params++;
			  switch (tmp->parmtype) {
			  case 'i':
                              vt = SPOVAR_INT;
                              break;
			  case 's':
                              vt = SPOVAR_STRING;
                              break;
			  default:
                              lc_error("Unknown func param conversion.");
                              break;
			  }
			  vardefs = add_vardef_type( vardefs, (yyvsp[(1) - (3)].map), vt);
		      }
		      Free((yyvsp[(1) - (3)].map));
		  ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2771 "lev_comp.y"
    {
			      (yyval.i) = (int)'i';
			  ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 2775 "lev_comp.y"
    {
			      (yyval.i) = (int)'s';
			  ;}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 2782 "lev_comp.y"
    {
			      char tmpbuf[2];
			      tmpbuf[0] = (char) (yyvsp[(1) - (1)].i);
			      tmpbuf[1] = '\0';
			      (yyval.map) = strdup(tmpbuf);
			  ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2789 "lev_comp.y"
    {
			      long len = strlen( (yyvsp[(1) - (3)].map) );
			      char *tmp = (char *) alloc(len + 2);
			      sprintf(tmp, "%c%s", (char) (yyvsp[(3) - (3)].i), (yyvsp[(1) - (3)].map) );
			      Free( (yyvsp[(1) - (3)].map) );
			      (yyval.map) = tmp;
			  ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2799 "lev_comp.y"
    {
			      (yyval.map) = strdup("");
			  ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2803 "lev_comp.y"
    {
			      char *tmp = strdup( (yyvsp[(1) - (1)].map) );
			      Free( (yyvsp[(1) - (1)].map) );
			      (yyval.map) = tmp;
			  ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 2811 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_POINT));
		  ;}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 2815 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_RECT));
		  ;}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 2819 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_FILLRECT));
		  ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2823 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_LINE));
		  ;}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 2827 "lev_comp.y"
    {
		      /* randline (x1,y1),(x2,y2), roughness */
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_RNDLINE));
		  ;}
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 2832 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2(W_ANY, SPO_SEL_GROW));
		  ;}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 2836 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2((yyvsp[(3) - (6)].i), SPO_SEL_GROW));
		  ;}
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 2840 "lev_comp.y"
    {
		      add_opvars(splev, "iio",
			     VA_PASS3((yyvsp[(3) - (6)].i), SPOFILTER_PERCENT, SPO_SEL_FILTER));
		  ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 2845 "lev_comp.y"
    {
		      add_opvars(splev, "io",
			       VA_PASS2(SPOFILTER_SELECTION, SPO_SEL_FILTER));
		  ;}
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 2850 "lev_comp.y"
    {
		      add_opvars(splev, "io",
				 VA_PASS2(SPOFILTER_MAPCHAR, SPO_SEL_FILTER));
		  ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 2855 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_FLOOD));
		  ;}
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 2859 "lev_comp.y"
    {
		      add_opvars(splev, "oio",
				 VA_PASS3(SPO_COPY, 1, SPO_SEL_ELLIPSE));
		  ;}
    break;

  case 440:

/* Line 1455 of yacc.c  */
#line 2864 "lev_comp.y"
    {
		      add_opvars(splev, "oio",
				 VA_PASS3(SPO_COPY, (yyvsp[(7) - (8)].i), SPO_SEL_ELLIPSE));
		  ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 2869 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2(1, SPO_SEL_ELLIPSE));
		  ;}
    break;

  case 442:

/* Line 1455 of yacc.c  */
#line 2873 "lev_comp.y"
    {
		      add_opvars(splev, "io", VA_PASS2((yyvsp[(9) - (10)].i), SPO_SEL_ELLIPSE));
		  ;}
    break;

  case 443:

/* Line 1455 of yacc.c  */
#line 2877 "lev_comp.y"
    {
		      add_opvars(splev, "iio",
				 VA_PASS3((yyvsp[(9) - (14)].i), (yyvsp[(3) - (14)].i), SPO_SEL_GRADIENT));
		  ;}
    break;

  case 444:

/* Line 1455 of yacc.c  */
#line 2882 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_COMPLEMENT));
		  ;}
    break;

  case 445:

/* Line 1455 of yacc.c  */
#line 2886 "lev_comp.y"
    {
		      check_vardef_type(vardefs, (yyvsp[(1) - (1)].map), SPOVAR_SEL);
		      vardef_used(vardefs, (yyvsp[(1) - (1)].map));
		      add_opvars(splev, "v", VA_PASS1((yyvsp[(1) - (1)].map)));
		      Free((yyvsp[(1) - (1)].map));
		  ;}
    break;

  case 446:

/* Line 1455 of yacc.c  */
#line 2893 "lev_comp.y"
    {
		      /* nothing */
		  ;}
    break;

  case 447:

/* Line 1455 of yacc.c  */
#line 2899 "lev_comp.y"
    {
		      /* nothing */
		  ;}
    break;

  case 448:

/* Line 1455 of yacc.c  */
#line 2903 "lev_comp.y"
    {
		      add_opvars(splev, "o", VA_PASS1(SPO_SEL_ADD));
		  ;}
    break;

  case 449:

/* Line 1455 of yacc.c  */
#line 2909 "lev_comp.y"
    {
		      add_opvars(splev, "iio",
				 VA_PASS3((yyvsp[(1) - (1)].dice).num, (yyvsp[(1) - (1)].dice).die, SPO_DICE));
		  ;}
    break;

  case 455:

/* Line 1455 of yacc.c  */
#line 2925 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1((yyvsp[(1) - (1)].i)));
		  ;}
    break;

  case 456:

/* Line 1455 of yacc.c  */
#line 2929 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1((yyvsp[(1) - (1)].i)));
		  ;}
    break;

  case 457:

/* Line 1455 of yacc.c  */
#line 2933 "lev_comp.y"
    {
		      add_opvars(splev, "i", VA_PASS1((yyvsp[(1) - (1)].i)));
		  ;}
    break;

  case 458:

/* Line 1455 of yacc.c  */
#line 2937 "lev_comp.y"
    {
		      /* nothing */
		  ;}
    break;

  case 467:

/* Line 1455 of yacc.c  */
#line 2959 "lev_comp.y"
    {
			(yyval.lregn) = (yyvsp[(1) - (1)].lregn);
		  ;}
    break;

  case 468:

/* Line 1455 of yacc.c  */
#line 2963 "lev_comp.y"
    {
			if ((yyvsp[(3) - (10)].i) <= 0 || (yyvsp[(3) - (10)].i) >= COLNO)
			    lc_error(
                          "Region (%ld,%ld,%ld,%ld) out of level range (x1)!",
                                     (yyvsp[(3) - (10)].i), (yyvsp[(5) - (10)].i), (yyvsp[(7) - (10)].i), (yyvsp[(9) - (10)].i));
			else if ((yyvsp[(5) - (10)].i) < 0 || (yyvsp[(5) - (10)].i) >= ROWNO)
			    lc_error(
                          "Region (%ld,%ld,%ld,%ld) out of level range (y1)!",
                                     (yyvsp[(3) - (10)].i), (yyvsp[(5) - (10)].i), (yyvsp[(7) - (10)].i), (yyvsp[(9) - (10)].i));
			else if ((yyvsp[(7) - (10)].i) <= 0 || (yyvsp[(7) - (10)].i) >= COLNO)
			    lc_error(
                          "Region (%ld,%ld,%ld,%ld) out of level range (x2)!",
                                     (yyvsp[(3) - (10)].i), (yyvsp[(5) - (10)].i), (yyvsp[(7) - (10)].i), (yyvsp[(9) - (10)].i));
			else if ((yyvsp[(9) - (10)].i) < 0 || (yyvsp[(9) - (10)].i) >= ROWNO)
			    lc_error(
                          "Region (%ld,%ld,%ld,%ld) out of level range (y2)!",
                                     (yyvsp[(3) - (10)].i), (yyvsp[(5) - (10)].i), (yyvsp[(7) - (10)].i), (yyvsp[(9) - (10)].i));
			(yyval.lregn).x1 = (yyvsp[(3) - (10)].i);
			(yyval.lregn).y1 = (yyvsp[(5) - (10)].i);
			(yyval.lregn).x2 = (yyvsp[(7) - (10)].i);
			(yyval.lregn).y2 = (yyvsp[(9) - (10)].i);
			(yyval.lregn).area = 1;
		  ;}
    break;

  case 469:

/* Line 1455 of yacc.c  */
#line 2989 "lev_comp.y"
    {
/* This series of if statements is a hack for MSC 5.1.  It seems that its
   tiny little brain cannot compile if these are all one big if statement. */
			if ((yyvsp[(2) - (9)].i) < 0 || (yyvsp[(2) - (9)].i) > (int) max_x_map)
			    lc_error(
                            "Region (%ld,%ld,%ld,%ld) out of map range (x1)!",
                                     (yyvsp[(2) - (9)].i), (yyvsp[(4) - (9)].i), (yyvsp[(6) - (9)].i), (yyvsp[(8) - (9)].i));
			else if ((yyvsp[(4) - (9)].i) < 0 || (yyvsp[(4) - (9)].i) > (int) max_y_map)
			    lc_error(
                            "Region (%ld,%ld,%ld,%ld) out of map range (y1)!",
                                     (yyvsp[(2) - (9)].i), (yyvsp[(4) - (9)].i), (yyvsp[(6) - (9)].i), (yyvsp[(8) - (9)].i));
			else if ((yyvsp[(6) - (9)].i) < 0 || (yyvsp[(6) - (9)].i) > (int) max_x_map)
			    lc_error(
                            "Region (%ld,%ld,%ld,%ld) out of map range (x2)!",
                                     (yyvsp[(2) - (9)].i), (yyvsp[(4) - (9)].i), (yyvsp[(6) - (9)].i), (yyvsp[(8) - (9)].i));
			else if ((yyvsp[(8) - (9)].i) < 0 || (yyvsp[(8) - (9)].i) > (int) max_y_map)
			    lc_error(
                            "Region (%ld,%ld,%ld,%ld) out of map range (y2)!",
                                     (yyvsp[(2) - (9)].i), (yyvsp[(4) - (9)].i), (yyvsp[(6) - (9)].i), (yyvsp[(8) - (9)].i));
			(yyval.lregn).area = 0;
			(yyval.lregn).x1 = (yyvsp[(2) - (9)].i);
			(yyval.lregn).y1 = (yyvsp[(4) - (9)].i);
			(yyval.lregn).x2 = (yyvsp[(6) - (9)].i);
			(yyval.lregn).y2 = (yyvsp[(8) - (9)].i);
		  ;}
    break;



/* Line 1455 of yacc.c  */
#line 6730 "lev_comp.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 3017 "lev_comp.y"


/*lev_comp.y*/

