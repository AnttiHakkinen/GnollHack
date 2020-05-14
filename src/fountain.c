/* GnollHack 4.0	fountain.c	$NHDT-Date: 1544442711 2018/12/10 11:51:51 $  $NHDT-Branch: GnollHack-3.6.2-beta01 $:$NHDT-Revision: 1.60 $ */
/*      Copyright Scott R. Turner, srt@ucla, 10/27/86 */
/* GnollHack may be freely redistributed.  See license for details. */

/* Code for drinking from fountains. */

#include "hack.h"

STATIC_DCL void NDECL(dowatersnakes);
STATIC_DCL void NDECL(dowaterdemon);
STATIC_DCL void NDECL(dowaternymph);
STATIC_PTR void FDECL(gush, (int, int, genericptr_t));
STATIC_DCL void NDECL(dofindgem);

/* used when trying to dip in or drink from fountain or sink or pool while
   levitating above it, or when trying to move downwards in that state */
void
floating_above(what)
const char *what;
{
    const char *umsg = "are floating high above the %s.";

    if (u.utrap && (u.utraptype == TT_INFLOOR || u.utraptype == TT_LAVA)) {
        /* when stuck in floor (not possible at fountain or sink location,
           so must be attempting to move down), override the usual message */
        umsg = "are trapped in the %s.";
        what = surface(u.ux, u.uy); /* probably redundant */
    }
    You(umsg, what);
}

/* Fountain of snakes! */
STATIC_OVL void
dowatersnakes()
{
    register int num = rn1(5, 2);
    struct monst *mtmp;

    if (!(mvitals[PM_WATER_MOCCASIN].mvflags & G_GONE)) {
        if (!Blind)
            pline("An endless stream of %s pours forth!",
                  Hallucination ? makeplural(rndmonnam(NULL)) : "snakes");
        else
            You_hear("%s hissing!", something);
        while (num-- > 0)
            if ((mtmp = makemon(&mons[PM_WATER_MOCCASIN], u.ux, u.uy,
                                NO_MM_FLAGS)) != 0
                && t_at(mtmp->mx, mtmp->my))
                (void) mintrap(mtmp);
    } else
        pline_The("fountain bubbles furiously for a moment, then calms.");
}

/* Water demon */
STATIC_OVL void
dowaterdemon()
{
    struct monst *mtmp;

    if (!(mvitals[PM_WATER_DEMON].mvflags & G_GONE)) {
        if ((mtmp = makemon(&mons[PM_WATER_DEMON], u.ux, u.uy,
                            NO_MM_FLAGS)) != 0) {
            if (!Blind)
                You("unleash %s!", a_monnam(mtmp));
            else
                You_feel("the presence of evil.");

            /* Give those on low levels a (slightly) better chance of survival
             */
            if (rnd(100) > (80 + level_difficulty())) {
                pline("Grateful for %s release, %s grants you a wish!",
                      mhis(mtmp), mhe(mtmp));
                /* give a wish and discard the monster (mtmp set to null) */
                mongrantswish(&mtmp);
            } else if (t_at(mtmp->mx, mtmp->my))
                (void) mintrap(mtmp);
        }
    } else
        pline_The("fountain bubbles furiously for a moment, then calms.");
}

/* Water Nymph */
STATIC_OVL void
dowaternymph()
{
    register struct monst *mtmp;

    if (!(mvitals[PM_WATER_NYMPH].mvflags & G_GONE)
        && (mtmp = makemon(&mons[PM_WATER_NYMPH], u.ux, u.uy,
                           NO_MM_FLAGS)) != 0) {
        if (!Blind)
            You("attract %s!", a_monnam(mtmp));
        else
            You_hear("a seductive voice.");
        mtmp->msleeping = 0;
        if (t_at(mtmp->mx, mtmp->my))
            (void) mintrap(mtmp);
    } else if (!Blind)
        pline("A large bubble rises to the surface and pops.");
    else
        You_hear("a loud pop.");
}

/* Gushing forth along LOS from (u.ux, u.uy) */
void
dogushforth(drinking)
int drinking;
{
    int madepool = 0;

    do_clear_area(u.ux, u.uy, 7, gush, (genericptr_t) &madepool);
    if (!madepool) {
        if (drinking)
            Your("thirst is quenched.");
        else
            pline("Water sprays all over you.");
    }
}

STATIC_PTR void
gush(x, y, poolcnt)
int x, y;
genericptr_t poolcnt;
{
    register struct monst *mtmp;
    register struct trap *ttmp;

    if (((x + y) % 2) || (x == u.ux && y == u.uy)
        || (rn2(1 + distmin(u.ux, u.uy, x, y))) || (levl[x][y].typ != ROOM)
        || (sobj_at(BOULDER, x, y)) || nexttodoor(x, y))
        return;

    if ((ttmp = t_at(x, y)) != 0 && !delfloortrap(ttmp))
        return;

    if (!((*(int *) poolcnt)++))
        pline("Water gushes forth from the overflowing fountain!");

    /* Put a pool at x, y */
    levl[x][y].typ = POOL, levl[x][y].flags = 0;
    /* No kelp! */
    del_engr_at(x, y);
    water_damage_chain(level.objects[x][y], TRUE);

    if ((mtmp = m_at(x, y)) != 0)
        (void) minliquid(mtmp);
    else
        newsym(x, y);
}

/* Find a gem in the sparkling waters. */
STATIC_OVL void
dofindgem()
{
    if (!Blind)
        You("spot a gem in the sparkling waters!");
    else
        You_feel("a gem here!");
    (void) mksobj_at(rnd_class(DILITHIUM_CRYSTAL, LUCKSTONE - 1), u.ux, u.uy,
                     FALSE, FALSE);
    SET_FOUNTAIN_LOOTED(u.ux, u.uy);
    newsym(u.ux, u.uy);
    exercise(A_WIS, TRUE); /* a discovery! */
}

void
dryup(x, y, isyou)
xchar x, y;
boolean isyou;
{
	int ftyp = (levl[x][y].fountaintype & FOUNTAIN_TYPE_MASK);

    if (IS_FOUNTAIN(levl[x][y].typ)
        && (!rn2(ftyp == FOUNTAIN_POWER ? 2 : ftyp == FOUNTAIN_MAGIC ? 3 : 4) || FOUNTAIN_IS_WARNED(x, y)))
	{
        if (isyou && in_town(x, y) && !FOUNTAIN_IS_WARNED(x, y))
		{
            struct monst *mtmp;

            SET_FOUNTAIN_WARNED(x, y);
            /* Warn about future fountain use. */
            for (mtmp = fmon; mtmp; mtmp = mtmp->nmon) {
                if (DEADMONSTER(mtmp))
                    continue;
                if (is_watch(mtmp->data) && couldsee(mtmp->mx, mtmp->my)
                    && is_peaceful(mtmp)) {
                    if (!Deaf) {
                        pline("%s yells:", Amonnam(mtmp));
                        verbalize("Hey, stop using that fountain!");
                    } else {
                        pline("%s earnestly %s %s %s!",
                              Amonnam(mtmp),
                              nolimbs(mtmp->data) ? "shakes" : "waves",
                              mhis(mtmp),
                              nolimbs(mtmp->data)
                                      ? mbodypart(mtmp, HEAD)
                                      : makeplural(mbodypart(mtmp, ARM)));
                    }
                    break;
                }
            }
            /* You can see or hear this effect */
            if (!mtmp)
                pline_The("flow reduces to a trickle.");
            return;
        }
        if (isyou && wizard) {
            if (yn_query("Dry up fountain?") == 'n')
                return;
        }
        /* replace the fountain with ordinary floor */
        levl[x][y].typ = ROOM, levl[x][y].flags = 0;
        levl[x][y].blessedftn = 0;
        if (cansee(x, y))
            pline_The("fountain dries up!");
        /* The location is seen if the hero/monster is invisible
           or felt if the hero is blind. */
        newsym(x, y);
        level.flags.nfountains--;
        if (isyou && in_town(x, y))
            (void) angry_guards(FALSE);
    }
}

void
drinkfountain()
{
    /* What happens when you drink from a fountain? */
    register boolean mgkftn = (levl[u.ux][u.uy].blessedftn == 1);
    register int fate = rnd(30);

	register int zlevel;
	zlevel = level_difficulty();
	boolean fountain_blessed = levl[u.ux][u.uy].blessedftn;
	int ftyp = (levl[u.ux][u.uy].fountaintype & FOUNTAIN_TYPE_MASK);

	if (Levitation && !Levitation_control) 
	{
        floating_above("fountain");
        return;
    }

	if (ftyp == FOUNTAIN_HEALING || ftyp == FOUNTAIN_POWER)
	{
		healup(d(6 + 2 * fountain_blessed, 4), fountain_blessed ? 1 : 0,
			!!fountain_blessed, !fountain_blessed, FALSE, FALSE, FALSE);

		if (ftyp == FOUNTAIN_HEALING)
		{
			pline("The water makes you feel better.");
			if (!FOUNTAIN_IS_KNOWN(u.ux, u.uy))
			{
				pline("That was a fountain of healing.");
				SET_FOUNTAIN_KNOWN(u.ux, u.uy);
			}
		}

	}
	if (ftyp == FOUNTAIN_MANA || ftyp == FOUNTAIN_POWER)
	{
		int num = d(3, 6);
		int numxtra = 1;

		if (fountain_blessed)
		{
			num = num * 2;
			u.ubaseenmax += numxtra;
		}
		u.uen += num;
		updatemaxen();
		if (u.uenmax <= 0)
			u.uenmax = 0;
		if (u.uen > u.uenmax)
			u.uen = u.uenmax;
		else if (u.uen <= 0)
			u.uen = 0;
		context.botl = 1;

		if (ftyp == FOUNTAIN_MANA)
		{
			pline("The water makes magical energies course through your body.");
			if (!FOUNTAIN_IS_KNOWN(u.ux, u.uy))
			{
				pline("That was a fountain of mana.");
				SET_FOUNTAIN_KNOWN(u.ux, u.uy);
			}
		}
	}
	if (ftyp == FOUNTAIN_POWER)
	{
		pline("The water fills your body with new energy.");
		if (!FOUNTAIN_IS_KNOWN(u.ux, u.uy))
		{
			pline("That was a fountain of power.");
			SET_FOUNTAIN_KNOWN(u.ux, u.uy);
		}
	}

	if (ftyp == FOUNTAIN_WATER)
	{
		pline_The("tasty spring water refreshes you.");
		u.uhunger += rnd(10); /* don't choke on water */
		update_hunger_status(FALSE);
		if (!FOUNTAIN_IS_KNOWN(u.ux, u.uy))
		{
			pline("That was a fountain of spring water.");
			SET_FOUNTAIN_KNOWN(u.ux, u.uy);
		}
	}

	if (ftyp == FOUNTAIN_POISON)
	{
		pline_The("water tastes foul! It was poisoned!");
		if (Poison_resistance) 
		{
			pline("However, you are unaffected!");
		}
		else
		{
			losestr(rn1(4, 2));
			losehp(adjust_damage(rnd(10), (struct monst*)0, &youmonst, AD_DRST, FALSE), "poisonous water", KILLED_BY);
		}
		if (!FOUNTAIN_IS_KNOWN(u.ux, u.uy))
		{
			pline("That was a fountain of poison.");
			SET_FOUNTAIN_KNOWN(u.ux, u.uy);
		}
	}

	/* Exit if not normal NetHack / magic fountain */
	if (ftyp > FOUNTAIN_MAGIC)
		return;


	/* Normal NetHack magic fountain here */
    if (mgkftn && u.uluck >= 0 && fate >= 10) {
        int i, ii, littleluck = (u.uluck < 4);

        pline("Wow!  The water makes you feel great!");
        /* blessed restore ability */
        for (ii = 0; ii < A_MAX; ii++)
            if (ABASE(ii) < AMAX(ii)) {
                ABASE(ii) = AMAX(ii);
                context.botl = 1;
            }
        /* gain ability, blessed if "natural" luck is high */
        i = rn2(A_MAX); /* start at a random attribute */
        for (ii = 0; ii < A_MAX; ii++) {
            if (adjattrib(i, 1, littleluck ? -1 : 0) && littleluck)
                break;
            if (++i >= A_MAX)
                i = 0;
        }
        display_nhwindow(WIN_MESSAGE, FALSE);
        pline("A wisp of vapor escapes the fountain...");
        exercise(A_WIS, TRUE);
        levl[u.ux][u.uy].blessedftn = 0;
		if (!FOUNTAIN_IS_KNOWN(u.ux, u.uy))
		{
			pline("That was an enchanted magic fountain.");
			SET_FOUNTAIN_KNOWN(u.ux, u.uy);
		}
		return;
    }

    if (fate < 10) {
        pline_The("cool draught refreshes you.");
        u.uhunger += rnd(10); /* don't choke on water */
        update_hunger_status(FALSE);
        if (mgkftn)
            return;
    } else {
        switch (fate) {
        case 19: /* Self-knowledge */
			pline_The("water tingles in your mouth.");
			You_feel("self-knowledgeable...");
            display_nhwindow(WIN_MESSAGE, FALSE);
            enlightenment(MAGICENLIGHTENMENT, ENL_GAMEINPROGRESS);
            exercise(A_WIS, TRUE);
            pline_The("feeling subsides.");
            break;
        case 20: /* Foul water */
            pline_The("water is foul!  You gag and vomit.");
            morehungry(rn1(20, 11));
            vomit();
            break;
        case 21: /* Poisonous */
            pline_The("water is contaminated!");
            if (Poison_resistance) {
                pline("Perhaps it is runoff from the nearby %s farm.",
                      fruitname(FALSE));
                losehp(adjust_damage(rnd(4), (struct monst*)0, &youmonst, AD_DRST, FALSE), "unrefrigerated sip of juice", KILLED_BY_AN);
                break;
            }
            losestr(rn1(4, 3));
            losehp(adjust_damage(rnd(10), (struct monst*)0, &youmonst, AD_DRST, FALSE), "contaminated water", KILLED_BY);
            exercise(A_CON, FALSE);
            break;
        case 22: /* Fountain of snakes! */
			pline_The("water tastes a bit slimy.");
			if (zlevel > 8) {
				dowatersnakes();
			}
			else
			{
				You_hear("a snake hissing.");
			}
			break;
        case 23: /* Water demon */
			pline_The("water tastes bitter.");
			if (zlevel > 12) {
				if (item_prevents_summoning(PM_WATER_DEMON)) 
				{
					pline("You have a passing sensation of relief.");
				}
				else
				{
					dowaterdemon();
				}
			}
			else
			{
				You("feel as if something evil is watching you.");
			}
			break;
        case 24: /* Curse an item */ {
            register struct obj *obj;

            pline("This water's no good!");
            morehungry(rn1(20, 11));
            exercise(A_CON, FALSE);
            for (obj = invent; obj; obj = obj->nobj)
                if (!rn2(5))
                    curse(obj);
            break;
        }
        case 25: /* See invisible */
			pline_The("water is tasteless.");
			if (Blind) {
                if (Invisible) {
                    You("feel transparent.");
                } else {
                    You("feel very self-conscious.");
                    pline("Then it passes.");
                }
            } else {
                You_see("an image of someone stalking you.");
                pline("But it disappears.");
            }
            HSee_invisible |= FROM_ACQUIRED;
            newsym(u.ux, u.uy);
            exercise(A_WIS, TRUE);
            break;
        case 26: /* See Monsters */
			pline_The("water tingles in your mouth.");
			(void) monster_detect((struct obj *) 0, 0);
            exercise(A_WIS, TRUE);
            break;
        case 27: /* Find a gem in the sparkling waters. */
			pline_The("water is hard.");
			if (!FOUNTAIN_IS_LOOTED(u.ux, u.uy)) {
                dofindgem();
                break;
            }
            /*FALLTHRU*/
        case 28: /* Water Nymph */
			pline_The("water tastes very sweet.");
			if (zlevel > 4) {
				dowaternymph();
			}
			else
			{
				if (Blind) {
					You("feel as if somebody is watching you.");
					pline("But then it passes disappears.");
				}
				else {
					You_see("an image of someone stalking you.");
					pline("But it disappears.");
				}
			}
			break;
        case 29: /* Scare */
        {
            register struct monst *mtmp;

            pline("This %s gives you bad breath!",
                  hliquid("water"));
            for (mtmp = fmon; mtmp; mtmp = mtmp->nmon) {
                if (DEADMONSTER(mtmp))
                    continue;
                monflee(mtmp, 0, FALSE, FALSE);
            }
            break;
        }
        case 30: /* Gushing forth in this room */
			pline_The("water suddenly starts bubbling.");
			dogushforth(TRUE);
            break;
        default:
            pline("This tepid %s is tasteless.",
                  hliquid("water"));
            break;
        }

		if (!FOUNTAIN_IS_KNOWN(u.ux, u.uy))
		{
			pline("That was a magic fountain.");
			SET_FOUNTAIN_KNOWN(u.ux, u.uy);
		}

    }
    dryup(u.ux, u.uy, TRUE);
}

void
dipfountain(obj)
register struct obj *obj;
{
    if (Levitation && !Levitation_control)
	{
        floating_above("fountain");
        return;
    }

	register int zlevel;
	zlevel = level_difficulty();
	boolean nowaterdamage = FALSE;
	boolean nodryup = FALSE;
	boolean effecthappened = FALSE;

	int ftyp = (levl[u.ux][u.uy].fountaintype & FOUNTAIN_TYPE_MASK);

    /* Don't grant Excalibur when there's more than one object.  */
    /* (quantity could be > 1 if merged daggers got polymorphed) */
    if ((ftyp != FOUNTAIN_POISON)
		&& obj->oclass == WEAPON_CLASS && objects[obj->otyp].oc_subtyp == WEP_LONG_SWORD && !is_demon_obj(obj)
		&& obj->quan == 1L && u.ulevel >= 5 && !rn2(6)
        && !obj->oartifact
        && !exist_artifact(LONG_SWORD, artiname(ART_EXCALIBUR)))
	{
        if (u.ualign.type != A_LAWFUL) 
		{
            /* Ha!  Trying to cheat her. */
            pline("A freezing mist rises from the %s and envelopes the sword.",
                  hliquid("water"));
            pline_The("fountain disappears!");
            curse(obj);
            if (obj->enchantment > -6 && !rn2(3))
                obj->enchantment--;
            obj->oerodeproof = FALSE;
            exercise(A_WIS, FALSE);
        } 
		else 
		{
            /* The lady of the lake acts! - Eric Backus */
            /* Be *REAL* nice */
            pline(
              "From the murky depths, a hand reaches up to bless the sword.");
            pline("As the hand retreats, the fountain disappears!");
			obj->otyp = LONG_SWORD;
            obj = oname(obj, artiname(ART_EXCALIBUR));
            discover_artifact(ART_EXCALIBUR);
            bless(obj);
            obj->oeroded = obj->oeroded2 = 0;
            obj->oerodeproof = TRUE;
            exercise(A_WIS, TRUE);
        }
        update_inventory();
        levl[u.ux][u.uy].typ = ROOM, levl[u.ux][u.uy].flags = 0;
        newsym(u.ux, u.uy);
        level.flags.nfountains--;
        if (in_town(u.ux, u.uy))
            (void) angry_guards(FALSE);
        return;
    } 

	if (ftyp == FOUNTAIN_HEALING)
	{
		boolean identified = FALSE;
		if (obj && is_weapon(obj) && is_poisonable(obj) && obj->opoisoned)
		{
			pline("A coating wears off %s.", the(xname(obj)));
			obj->opoisoned = 0;
			identified = TRUE;
			effecthappened = TRUE;
		}
		else if (obj && (obj->otyp == POT_SICKNESS || obj->otyp == POT_POISON))
		{
			if (carried(obj))
			{
				if(objects[obj->otyp].oc_name_known)
					pline("%s purified.", Yobjnam2(obj, "are"));
				else 
					pline("%s.", Yobjnam2(obj, "clear"));
			}
			obj->otyp = POT_WATER;
			obj->dknown = 0;
			obj->blessed = obj->cursed = 0;
			obj->odiluted = 0;
			if (carried(obj))
				update_inventory();
			identified = TRUE;
			nowaterdamage = TRUE;
			effecthappened = TRUE;
		}
		else if (obj && obj->oclass == POTION_CLASS)
		{
			int oldotyp = obj->otyp;
			char oldnameturns[BUFSZ];
			strcpy(oldnameturns, Tobjnam(obj, "turn"));
			char oldnameare[BUFSZ];
			strcpy(oldnameare, Tobjnam(obj, "are"));
			unsigned int olddiluted = obj->odiluted;

			switch (obj->otyp)
			{
			case POT_GAIN_ENERGY:
			case POT_EXTRA_HEALING:
				obj->otyp = POT_EXTRA_HEALING;
				break;
			case POT_GREATER_ENERGY:
			case POT_GREATER_HEALING:
				obj->otyp = POT_GREATER_HEALING;
				break;
			case POT_FULL_ENERGY:
			case POT_FULL_HEALING:
				obj->otyp = POT_FULL_HEALING;
				break;
			default:
				obj->otyp = POT_HEALING;
				break;
			}
			obj->dknown = 0;
			obj->odiluted = 0;
			nowaterdamage = TRUE;

			if (obj->otyp != oldotyp)
			{
				identified = TRUE;
				effecthappened = TRUE;
				pline("%s imbued with healing energies of the fountain.", oldnameare);
				pline("%s into %s.", oldnameturns, doname(obj));
			}
			else if (obj->odiluted != olddiluted)
			{
				effecthappened = TRUE;
				pline("%s undiluted.", Tobjnam(obj, "become"));
			}

			if (carried(obj))
			{
				update_inventory();
			}

		}

		if (identified)
		{
			if (!FOUNTAIN_IS_KNOWN(u.ux, u.uy))
			{
				pline("That was a fountain of healing.");
				SET_FOUNTAIN_KNOWN(u.ux, u.uy);
			}
		}
	}
	else if (ftyp == FOUNTAIN_MANA)
	{
		boolean identified = FALSE;

		if (obj && objects[obj->otyp].oc_charged)
		{
			recharge(obj, 0, TRUE);
			identified = TRUE;
			nowaterdamage = TRUE;
			effecthappened = TRUE;
		}
		else if (obj && obj->oclass == POTION_CLASS)
		{
			int oldotyp = obj->otyp;
			char oldnameturns[BUFSZ];
			strcpy(oldnameturns, Tobjnam(obj, "turn"));
			char oldnameare[BUFSZ];
			strcpy(oldnameare, Tobjnam(obj, "are"));
			unsigned int olddiluted = obj->odiluted;

			switch (obj->otyp)
			{
			case POT_EXTRA_HEALING:
			case POT_GREATER_HEALING:
			case POT_GREATER_ENERGY:
				obj->otyp = POT_GREATER_ENERGY;
				break;
			case POT_FULL_HEALING:
			case POT_FULL_ENERGY:
				obj->otyp = POT_FULL_ENERGY;
				break;
			default:
				obj->otyp = POT_GAIN_ENERGY;
				break;
			}
			obj->dknown = 0;
			obj->odiluted = 0;
			nowaterdamage = TRUE;

			if (obj->otyp != oldotyp)
			{
				identified = TRUE;
				effecthappened = TRUE;
				pline("%s imbued with magical energies of the fountain.", oldnameare);
				pline("%s into %s.", oldnameturns, doname(obj));
			}
			else if (obj->odiluted != olddiluted)
			{
				effecthappened = TRUE;
				pline("%s undiluted.", Tobjnam(obj, "become"));
			}

			if (carried(obj))
			{
				update_inventory();
			}

		}

		if (identified)
		{
			if (!FOUNTAIN_IS_KNOWN(u.ux, u.uy))
			{
				pline("That was a fountain of mana.");
				SET_FOUNTAIN_KNOWN(u.ux, u.uy);
			}
		}
	}
	else if (ftyp == FOUNTAIN_POWER)
	{
		boolean identified = FALSE;

		if (obj && objects[obj->otyp].oc_charged)
		{
			recharge(obj, 0, TRUE);
			identified = TRUE;
			nowaterdamage = TRUE;
			effecthappened = TRUE;
		}
		else if (obj && obj->oclass == POTION_CLASS)
		{
			int oldotyp = obj->otyp;
			char oldnameturns[BUFSZ];
			strcpy(oldnameturns, Tobjnam(obj, "turn"));
			char oldnameare[BUFSZ];
			strcpy(oldnameare, Tobjnam(obj, "are"));
			unsigned int olddiluted = obj->odiluted;

			switch (obj->otyp)
			{
			case POT_GAIN_ENERGY:
				obj->otyp = POT_GREATER_ENERGY;
				break;
			case POT_GREATER_ENERGY:
			case POT_FULL_ENERGY:
				obj->otyp = POT_FULL_ENERGY;
				break;
			case POT_HEALING:
				obj->otyp = POT_EXTRA_HEALING;
				break;
			case POT_EXTRA_HEALING:
				obj->otyp = POT_GREATER_HEALING;
				break;
			case POT_GREATER_HEALING:
			case POT_FULL_HEALING:
				obj->otyp = POT_FULL_HEALING;
				break;
			case POT_RESTORE_ABILITY:
			case POT_GAIN_ABILITY:
				obj->otyp = POT_GAIN_ABILITY;
				break;
			case POT_GAIN_LEVEL:
				obj->otyp = POT_GAIN_LEVEL;
				break;
			default:
				obj->otyp = POT_ENLIGHTENMENT;
				break;
			}
			obj->dknown = 0;
			obj->odiluted = 0;
			nowaterdamage = TRUE;

			if (obj->otyp != oldotyp)
			{
				identified = TRUE;
				effecthappened = TRUE;
				pline("%s empowered by the energies of the fountain.", oldnameare);
				pline("%s into %s.", oldnameturns, doname(obj));
			}
			else if (obj->odiluted != olddiluted)
			{
				effecthappened = TRUE;
				pline("%s undiluted.", Tobjnam(obj, "become"));
			}

			if (carried(obj))
			{
				update_inventory();
			}

		}

		if (identified)
		{
			if (!FOUNTAIN_IS_KNOWN(u.ux, u.uy))
			{
				pline("That was a fountain of power.");
				SET_FOUNTAIN_KNOWN(u.ux, u.uy);
			}
		}
	}
	else if (ftyp == FOUNTAIN_WATER)
	{
		if (!rn2(2))
		{ /* no dryup */
			nodryup = TRUE;
		}
	}
	else if (ftyp == FOUNTAIN_POISON)
	{
		int oldotyp = obj->otyp;
		char oldnameturns[BUFSZ];
		strcpy(oldnameturns, Tobjnam(obj, "turn"));
		char oldnamestart[BUFSZ];
		strcpy(oldnamestart, Tobjnam(obj, "start"));
		unsigned int olddiluted = obj->odiluted;

		nowaterdamage = TRUE;
		boolean identified = FALSE;

		if (obj && is_weapon(obj) && is_poisonable(obj) && !obj->opoisoned)
		{
			pline("The fountain forms a coating on %s.", the(xname(obj)));
			obj->opoisoned = TRUE;
			identified = TRUE;
			effecthappened = TRUE;
		}
		else if (obj && obj->oclass == POTION_CLASS)
		{
			obj->otyp = POT_POISON;
			obj->dknown = 0;
			obj->odiluted = 0;

			if (obj->otyp != oldotyp)
			{
				identified = TRUE;
				effecthappened = TRUE;
				pline("%s to smell foul.", oldnamestart);
				pline("%s into %s.", oldnameturns, doname(obj));
			}
			else if (obj->odiluted != olddiluted)
			{
				effecthappened = TRUE;
				pline("%s undiluted.", Tobjnam(obj, "become"));
			}

			if (carried(obj))
				update_inventory();
			identified = TRUE;
			effecthappened = TRUE;
		}
		else if (obj && obj->oclass == SCROLL_CLASS)
			nowaterdamage = FALSE;

		if (identified)
		{
			if (!FOUNTAIN_IS_KNOWN(u.ux, u.uy))
			{
				pline("That was a fountain of poison.");
				SET_FOUNTAIN_KNOWN(u.ux, u.uy);
			}
		}
	}
	else
	{
		boolean identified = TRUE;
		effecthappened = TRUE;
		switch (rnd(30))
		{
		default:
			identified = FALSE;
			effecthappened = FALSE;
			break;
		case 16: /* Curse the item */
			if (!obj->cursed)
			{
				curse(obj);
				if (!Blind)
					pline("%s %s for a moment.", Tobjnam(obj, "glows"), hcolor(NH_BLACK));
				else
				{
					identified = FALSE;
					effecthappened = FALSE;	/* This is just apparently so */
				}
			}
			else
			{
				identified = FALSE;
				effecthappened = FALSE;
			}
			break;
		case 17:
		case 18:
		case 19:
		case 20: /* Uncurse the item */
			if (obj->cursed) 
			{
				if (!Blind)
					pline_The("%s glows for a moment.", hliquid("water"));
				uncurse(obj);
			} 
			else 
			{
				pline("A feeling of loss comes over you.");
			}
			break;
		case 21: /* Water Demon */
			if(zlevel > 12) { 
				if (item_prevents_summoning(PM_WATER_DEMON))
				{
					pline("You have a passing sensation of relief.");
				}
				else
				{
					dowaterdemon();
				}
			} else
			{
				You("feel as if something evil is watching you."); 
			}
			break;
		case 22: /* Water Nymph */
			if (zlevel > 4) {
				dowaternymph();
			}
			else
			{
				if (Blind) {
						You("feel as if somebody is watching you.");
						pline("But then it passes disappears.");
				}
				else {
					You_see("an image of someone stalking you.");
					pline("But it disappears.");
				}
			}
			break;
		case 23: /* an Endless Stream of Snakes */
			if (zlevel > 8) {
				dowatersnakes();
			}
			else
			{
				You_hear("a snake hissing.");
			}
			break;
		case 24: /* Find a gem */
			if (!FOUNTAIN_IS_LOOTED(u.ux, u.uy)) {
				dofindgem();
				break;
			}
			/*FALLTHRU*/
		case 25: /* Water gushes forth */
			dogushforth(FALSE);
			break;
		case 26: /* Strange feeling */
			pline("A strange tingling runs up your %s.", body_part(ARM));
			break;
		case 27: /* Strange feeling */
			You_feel("a sudden chill.");
			break;
		case 28: /* Strange feeling */
			pline("An urge to take a bath overwhelms you.");
			{
				long money = money_cnt(invent);
				struct obj *otmp;
				if (money > 10) {
					/* Amount to lose.  Might get rounded up as fountains don't
					 * pay change... */
					money = somegold(money) / 10;
					for (otmp = invent; otmp && money > 0; otmp = otmp->nobj)
						if (otmp->oclass == COIN_CLASS) {
							int denomination = objects[otmp->otyp].oc_cost;
							long coin_loss =
								(money + denomination - 1) / denomination;
							coin_loss = min(coin_loss, otmp->quan);
							otmp->quan -= coin_loss;
							money -= coin_loss * denomination;
							if (!otmp->quan)
								delobj(otmp);
						}
					You("lost some of your money in the fountain!");
					CLEAR_FOUNTAIN_LOOTED(u.ux, u.uy);
					exercise(A_WIS, FALSE);
				}
			}
			break;
		case 29: /* You see coins */
			/* We make fountains have more coins the closer you are to the
			 * surface.  After all, there will have been more people going
			 * by.  Just like a shopping mall!  Chris Woodbury  */

			if (FOUNTAIN_IS_LOOTED(u.ux, u.uy))
				break;
			SET_FOUNTAIN_LOOTED(u.ux, u.uy);
			(void) mkgold((long) (rnd((dunlevs_in_dungeon(&u.uz) - dunlev(&u.uz)
									   + 1) * 2) + 5),
						  u.ux, u.uy);
			if (!Blind)
				pline("Far below you, you see coins glistening in the %s.",
					  hliquid("water"));
			exercise(A_WIS, TRUE);
			newsym(u.ux, u.uy);
			break;
		}

		if (identified && !FOUNTAIN_IS_KNOWN(u.ux, u.uy))
		{
			pline("That was a magic fountain.");
			SET_FOUNTAIN_KNOWN(u.ux, u.uy);
		}

	}

	if (!nowaterdamage)
	{
		int er = water_damage(obj, NULL, TRUE);

		if (er != ER_NOTHING)
			effecthappened = TRUE;
#if 0
		if (obj->otyp == POT_ACID && er != ER_DESTROYED)
		{ /* Acid and water don't mix */
			useup(obj);
			nodryup = TRUE;
		}
		else if (er != ER_NOTHING && ftyp == FOUNTAIN_MAGIC && !rn2(2))
		{ /* no further effect */
			nodryup = TRUE;
		}
#endif
	}

	if(!effecthappened)
		pline("Nothing much happens.");

    update_inventory();

	if(!nodryup)
	    dryup(u.ux, u.uy, TRUE);
}

const char* get_fountain_name(x, y)
int x, y;
{
	if (!isok(x, y))
		return "invalid coordinates";

	if (!IS_FOUNTAIN(levl[x][y].typ))
		return "a non-fountain";

	int ftyp = (levl[x][y].fountaintype & FOUNTAIN_TYPE_MASK);

	return FOUNTAIN_IS_KNOWN(x, y) ? (ftyp > FOUNTAIN_MAGIC ? fountain_type_text(ftyp) : levl[x][y].blessedftn ? "enchanted magic fountain" : "magic fountain") : defsyms[S_fountain].explanation;
}


const char* fountain_type_text(ftyp)
int ftyp;
{
	switch (ftyp)
	{
	case FOUNTAIN_MAGIC:
		return "magic fountain";
		break;
	case FOUNTAIN_HEALING:
		return "fountain of healing";
		break;
	case FOUNTAIN_MANA:
		return "fountain of mana";
		break;
	case FOUNTAIN_POWER:
		return "fountain of power";
		break;
	case FOUNTAIN_WATER:
		return "fountain of spring water";
		break;
	case FOUNTAIN_POISON:
		return "fountain of poison";
		break;
	default:
		return "fountain";
		break;
	}
}

void
breaksink(x, y)
int x, y;
{
    if (cansee(x, y) || (x == u.ux && y == u.uy))
        pline_The("pipes break!  Water spurts out!");
    level.flags.nsinks--;
    levl[x][y].typ = FOUNTAIN, levl[x][y].looted = 0;
	levl[x][y].fountaintype &= ~FOUNTAIN_TYPE_MASK;
	levl[x][y].fountaintype |= FOUNTAIN_WATER;
	levl[x][y].blessedftn = 0;
    SET_FOUNTAIN_LOOTED(x, y);
    level.flags.nfountains++;
    newsym(x, y);
}

void
drinksink()
{
    struct obj *otmp;
    struct monst *mtmp;

    if (Levitation && !Levitation_control) 
	{
        floating_above("sink");
        return;
    }
    switch (rn2(20)) {
    case 0:
        You("take a sip of very cold %s.", hliquid("water"));
        break;
    case 1:
        You("take a sip of very warm %s.", hliquid("water"));
        break;
    case 2:
        You("take a sip of scalding hot %s.", hliquid("water"));
        if (Fire_resistance)
            pline("It seems quite tasty.");
        else
            losehp(adjust_damage(rnd(6), (struct monst*)0, &youmonst, AD_FIRE, FALSE), "sipping boiling water", KILLED_BY);
        /* boiling water burns considered fire damage */
        break;
    case 3:
        if (mvitals[PM_SEWER_RAT].mvflags & G_GONE)
            pline_The("sink seems quite dirty.");
        else {
            mtmp = makemon(&mons[PM_SEWER_RAT], u.ux, u.uy, NO_MM_FLAGS);
            if (mtmp)
                pline("Eek!  There's %s in the sink!",
                      (Blind || !canspotmon(mtmp)) ? "something squirmy"
                                                   : a_monnam(mtmp));
        }
        break;
    case 4:
        do {
            otmp = mkobj(POTION_CLASS, FALSE, FALSE);
            if (otmp->otyp == POT_WATER) {
                obfree(otmp, (struct obj *) 0);
                otmp = (struct obj *) 0;
            }
        } while (!otmp);
        otmp->cursed = otmp->blessed = 0;
        pline("Some %s liquid flows from the faucet.",
              Blind ? "odd" : hcolor(OBJ_DESCR(objects[otmp->otyp])));
        otmp->dknown = !(Blind || Hallucination);
        otmp->quan++;       /* Avoid panic upon useup() */
        otmp->fromsink = 1; /* kludge for docall() */
        (void) dopotion(otmp);
        obfree(otmp, (struct obj *) 0);
        break;
    case 5:
        if (!(levl[u.ux][u.uy].looted & S_LRING)) {
            You("find a ring in the sink!");
            (void) mkobj_at(RING_CLASS, u.ux, u.uy, TRUE);
            levl[u.ux][u.uy].looted |= S_LRING;
            exercise(A_WIS, TRUE);
            newsym(u.ux, u.uy);
        } else
            pline("Some dirty %s backs up in the drain.", hliquid("water"));
        break;
    case 6:
        breaksink(u.ux, u.uy);
        break;
    case 7:
        pline_The("%s moves as though of its own will!", hliquid("water"));
        if ((mvitals[PM_WATER_ELEMENTAL].mvflags & G_GONE)
            || !makemon(&mons[PM_WATER_ELEMENTAL], u.ux, u.uy, NO_MM_FLAGS))
            pline("But it quiets down.");
        break;
    case 8:
        pline("Yuk, this %s tastes awful.", hliquid("water"));
        more_experienced(1, 0);
        newexplevel();
        break;
    case 9:
        pline("Gaggg... this tastes like sewage!  You vomit.");
        morehungry(rn1(30 - ACURR(A_CON), 11));
        vomit();
        break;
    case 10:
        pline("This %s contains toxic wastes!", hliquid("water"));
        if (!Unchanging) {
            You("undergo a freakish metamorphosis!");
            polyself(0);
        }
        break;
    /* more odd messages --JJB */
    case 11:
        You_hear("clanking from the pipes...");
        break;
    case 12:
        You_hear("snatches of song from among the sewers...");
        break;
    case 19:
        if (Hallucination) {
            pline("From the murky drain, a hand reaches up... --oops--");
            break;
        }
        /*FALLTHRU*/
    default:
        You("take a sip of %s %s.",
            rn2(3) ? (rn2(2) ? "cold" : "warm") : "hot",
            hliquid("water"));
    }
}

void
init_fountains()
{
	/*Initialize fountain variations */
	for (int i = 0; i < FOUNTAIN_WATER; i++)
	{
		context.used_fountain_variation[i] = i;
	}

	/* Water always looks like water, so it is not shuffled */
	for (int i = 0; i < FOUNTAIN_POISON - 1; i++)
	{
		int new_i = i + rn2(FOUNTAIN_POISON - i);
		int saved_value = context.used_fountain_variation[i];
		context.used_fountain_variation[i] = context.used_fountain_variation[new_i];
		context.used_fountain_variation[new_i] = saved_value;
	}

}

/*fountain.c*/
