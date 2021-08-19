/* GnollHack 4.0    sit.c    $NHDT-Date: 1544442714 2018/12/10 11:51:54 $  $NHDT-Branch: GnollHack-3.6.2-beta01 $:$NHDT-Revision: 1.59 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Robert Patrick Rankin, 2012. */
/* GnollHack may be freely redistributed.  See license for details. */

#include "hack.h"

/* take away the hero's money */
void
take_gold()
{
    struct obj *otmp, *nobj;
    int lost_money = 0;

    for (otmp = invent; otmp; otmp = nobj) {
        nobj = otmp->nobj;
        if (otmp->oclass == COIN_CLASS) {
            lost_money = 1;
            remove_worn_item(otmp, FALSE);
            delobj(otmp);
        }
    }
    if (!lost_money) {
        You_feel("a strange sensation.");
    } else {
        You("notice you have no money!");
        context.botl = 1;
    }
}

/* #sit command */
int
dosit()
{
    static const char sit_message[] = "sit on the %s.";
    register struct trap *trap = t_at(u.ux, u.uy);
    register int typ = levl[u.ux][u.uy].typ;

    if (u.usteed) {
        You("are already sitting on %s.", mon_nam(u.usteed));
        return 0;
    }
    if (u.uundetected && is_hider(youmonst.data) && u.umonnum != PM_TRAPPER)
        u.uundetected = 0; /* no longer on the ceiling */

    if (!can_reach_floor(FALSE)) {
        if (u.uswallow)
            There("are no seats in here!");
        else if (Levitation)
            You("tumble in place.");
        else
            You("are sitting on air.");
        return 0;
    } else if (u.ustuck && !sticks(youmonst.data)) {
        /* holding monster is next to hero rather than beneath, but
           hero is in no condition to actually sit at has/her own spot */
        if (humanoid(u.ustuck->data))
            pline("%s won't offer %s lap.", Monnam(u.ustuck), mhis(u.ustuck));
        else
            pline("%s has no lap.", Monnam(u.ustuck));
        return 0;
    } else if (is_pool(u.ux, u.uy) && !Underwater) { /* water walking */
        goto in_water;
    }

    if (OBJ_AT(u.ux, u.uy)
        /* ensure we're not standing on the precipice */
        && !uteetering_at_seen_pit(trap)) {
        register struct obj *obj;

        obj = level.objects[u.ux][u.uy];
        if (youmonst.data->mlet == S_DRAGON && obj->oclass == COIN_CLASS) {
            You("coil up around your %shoard.",
                (obj->quan + money_cnt(invent) < u.ulevel * 1000) ? "meager "
                                                                  : "");
        } else {
            You("sit on %s.", the(xname(obj)));
            if (!(Is_box(obj) || objects[obj->otyp].oc_material == MAT_CLOTH))
                pline("It's not very comfortable...");
        }
    } else if (trap != 0 || (u.utrap && (u.utraptype >= TT_LAVA))) {
        if (u.utrap) {
            exercise(A_WIS, FALSE); /* you're getting stuck longer */
            if (u.utraptype == TT_BEARTRAP) {
                You_cant("sit down with your %s in the bear trap.",
                         body_part(FOOT));
                u.utrap++;
            } else if (u.utraptype == TT_PIT) {
                if (trap && trap->ttyp == SPIKED_PIT) {
                    play_player_ouch_sound(MONSTER_OUCH_SOUND_OUCH);
                    You("sit down on a spike.  Ouch!");
                    losehp(adjust_damage(rn2(2), (struct monst*)0, &youmonst, AD_PHYS, ADFLAGS_NONE),
                           "sitting on an iron spike", KILLED_BY);
                    exercise(A_STR, FALSE);
                } else
                    You("sit down in the pit.");
                u.utrap += rn2(5);
            } else if (u.utraptype == TT_WEB) {
                You("sit in the spider web and get entangled further!");
                u.utrap += rn1(10, 5);
            } else if (u.utraptype == TT_LAVA) {
                /* Must have fire resistance or they'd be dead already */
                You("sit in the %s!", hliquid("lava"));
                if (Slimed)
                    burn_away_slime();
                u.utrap += rnd(4);
                losehp(adjust_damage(d(2, 10), (struct monst*)0, &youmonst, AD_PHYS, ADFLAGS_NONE), "sitting in lava",
                       KILLED_BY); /* lava damage */
            } else if (u.utraptype == TT_INFLOOR
                       || u.utraptype == TT_BURIEDBALL) {
                You_cant("maneuver to sit!");
                u.utrap++;
            }
        } else {
            You("sit down.");
            dotrap(trap, VIASITTING);
        }
    }
    else if ((Underwater || Is_waterlevel(&u.uz)))
    {
        if (Is_waterlevel(&u.uz))
            There("are no cushions floating nearby.");
        else
            You("sit down on the muddy bottom.");
    } 
    else if (is_pool(u.ux, u.uy))
    {
    in_water:
        You("sit in the %s.", hliquid("water"));
        if (!rn2(10) && uarm)
            (void) water_damage(uarm, "armor", TRUE);
        if (!rn2(10) && uarmf && uarmf->otyp != WATER_WALKING_BOOTS)
            (void) water_damage(uarm, "armor", TRUE);
    } 
    else if (IS_SINK(typ))
    {
        You(sit_message, defsyms[S_sink].explanation);
        Your("%s gets wet.", humanoid(youmonst.data) ? "rump" : "underside");
    } 
    else if (IS_ALTAR(typ)) 
    {
        You(sit_message, defsyms[S_altar].explanation);
        altar_wrath(u.ux, u.uy);
    }
    else if (IS_ANVIL(typ))
    {
        You(sit_message, defsyms[S_altar].explanation);
        pline("The anvil feels cold.");
    }
    else if (IS_GRAVE(typ))
    {
        You(sit_message, defsyms[S_grave].explanation);
    } 
    else if (IS_SIGNPOST(typ))
    {
        You("sit in the front of the %s.", defsyms[S_signpost].explanation);
    }
    else if (IS_BRAZIER(typ))
    {
        /* must be WWalking */
        You("sit in the %s.", defsyms[S_brazier].explanation);
        if (levl[u.ux][u.uy].lamplit)
        {
            burn_away_slime();
            if (likes_fire(youmonst.data) || Fire_immunity)
            {
                pline_The("fire feels warm.");
                return 1;
            }
            pline_The("fire burns you!");
            int dmg = d(3, 6);
            play_sfx_sound(SFX_MONSTER_ON_FIRE);
            display_u_being_hit(HIT_ON_FIRE, dmg, 0UL);
            losehp(adjust_damage(dmg, (struct monst*)0, &youmonst, AD_FIRE, ADFLAGS_NONE), /* lava damage */
                "sitting in a brazier", KILLED_BY);
        }
        else
        {
            pline("That was quite uncomfortable.");
        }
    }
    else if (typ == STAIRS)
    {
        You(sit_message, "stairs");
    } 
    else if (typ == LADDER) 
    {
        You(sit_message, "ladder");
    }
    else if (is_lava(u.ux, u.uy))
    {
        /* must be WWalking */
        You(sit_message, hliquid("lava"));
        burn_away_slime();
        if (likes_lava(youmonst.data) || Fire_immunity)
        {
            pline_The("%s feels warm.", hliquid("lava"));
            return 1;
        }
        pline_The("%s burns you!", hliquid("lava"));
        losehp(adjust_damage(d(10, 10), (struct monst*)0, &youmonst, AD_FIRE, ADFLAGS_NONE), /* lava damage */
               "sitting on lava", KILLED_BY);
    } 
    else if (is_ice(u.ux, u.uy))
    {
        You(sit_message, defsyms[S_ice].explanation);
        if (!Cold_immunity)
            pline_The("ice feels cold.");
    } 
    else if (typ == DRAWBRIDGE_DOWN) 
    {
        You(sit_message, "drawbridge");
    } 
    else if (IS_THRONE(typ))
    {
        You(sit_message, defsyms[S_throne].explanation);
        if (rnd(6) > 4) 
        {
            switch (rnd(13)) 
            {
            case 1:
                play_sfx_sound(SFX_LOSE_ABILITY);
                (void) adjattrib(rn2(A_MAX), -rn1(4, 3), FALSE);
                losehp(adjust_damage(rnd(10), (struct monst*)0, &youmonst, AD_MAGM, ADFLAGS_NONE), "cursed throne", KILLED_BY_AN);
                break;
            case 2:
                play_sfx_sound(SFX_GAIN_ABILITY);
                (void) adjattrib(rn2(A_MAX), 1, FALSE);
                break;
            case 3:
                play_sfx_sound(SFX_ELECTRIC_SHOCK);
                pline("A%s electric shock shoots through your body!",
                      (Shock_immunity) ? "n" : " massive");
                losehp(adjust_damage(Shock_immunity ? rnd(6) : rnd(30), (struct monst*)0, &youmonst, AD_ELEC, ADFLAGS_NONE), "electric chair",
                       KILLED_BY_AN);
                exercise(A_CON, FALSE);
                break;
            case 4:
                play_sfx_sound(SFX_HEALING);
                You_feel("much, much better!");
                if (Upolyd) {
                    if (u.mh >= (u.mhmax - 5))
                        u.basemhmax += 4;
                    u.mh = u.mhmax;
                }
                if (u.uhp >= (u.uhpmax - 5))
                    u.ubasehpmax += 4;
                updatemaxhp();
                u.uhp = u.uhpmax;
                u.ucreamed = 0;
                make_blinded(0L, TRUE);
                make_sick(0L, (char *) 0, FALSE);
                make_food_poisoned(0L, (char*)0, FALSE);
                make_mummy_rotted(0L, (char*)0, FALSE);
                heal_legs(0);
                context.botl = context.botlx = 1;
                break;
            case 5:
                take_gold();
                break;
            case 6:
                if (u.uluck + rn2(5) < 0) 
                {
                    //You_feel("your luck is changing.");
                    change_luck(1, TRUE);
                } 
                else
                    makewish(FALSE);
                break;
            case 7:
              {
                int cnt = rnd(10);

                /* Magical voice not affected by deafness */
                play_sfx_sound(SFX_SUMMON_MONSTER);
                pline("A voice echoes:");
                play_sfx_sound(flags.female ? SFX_VOICE_THRONE_ROOM_AUDIENCE_SUMMONED_DAME : SFX_VOICE_THRONE_ROOM_AUDIENCE_SUMMONED_SIRE);
                verbalize("Thy audience hath been summoned, %s!",
                          flags.female ? "Dame" : "Sire");
                context.makemon_spef_idx = 0;
                while (cnt--)
                {
                    struct monst* mtmp = makemon(courtmon(), u.ux, u.uy, MM_PLAY_SUMMON_ANIMATION | MM_SUMMON_IN_SMOKE_ANIMATION | (context.makemon_spef_idx == 0 ? MM_PLAY_SUMMON_SOUND : 0UL));
                    if (mtmp)
                        context.makemon_spef_idx++;

                }
                makemon_animation_wait_until_end();
                break;
              }
            case 8:
                /* Magical voice not affected by deafness */
                pline("A voice echoes:");
                play_sfx_sound(flags.female ? SFX_VOICE_THRONE_ROOM_BY_THINE_IMPERIOUS_ORDER_DAME : SFX_VOICE_THRONE_ROOM_BY_THINE_IMPERIOUS_ORDER_SIRE);
                verbalize("By thine Imperious order, %s...",
                          flags.female ? "Dame" : "Sire");
                do_genocide(5); /* REALLY|ONTHRONE, see do_genocide() */
                break;
            case 9:
                /* Magical voice not affected by deafness */
                pline("A voice echoes:");
                play_sfx_sound(SFX_VOICE_THRONE_ROOM_CURSE_UPON_THEE);
                verbalize(
                 "A curse upon thee for sitting upon this most holy throne!");
                if (Luck > 0) {
                    if(!Blinded)
                        play_sfx_sound(SFX_ACQUIRE_BLINDNESS);
                    make_blinded(Blinded + rn1(100, 250), TRUE);
                    change_luck((Luck > 1) ? -rnd(2) : -1, TRUE);
                } 
                else
                    rndcurse();
                break;
            case 10:
                if (Luck < 0 || (HSee_invisible & INTRINSIC)) 
                {
                    if (level.flags.nommap) {
                        pline("A terrible drone fills your head!");
                        play_sfx_sound(SFX_ACQUIRE_CONFUSION);
                        make_confused(itimeout_incr(HConfusion, rnd(30)), FALSE);
                    } else {
                        pline("An image forms in your mind.");
                        do_mapping();
                    }
                }
                else 
                {
                    Your("vision becomes clear.");
                    HSee_invisible |= FROM_ACQUIRED;
                    newsym(u.ux, u.uy);
                }
                break;
            case 11:
                if (Luck < 0)
                {
                    You_feel("threatened.");
                    play_sfx_sound(SFX_AGGRAVATE_MONSTER);
                    aggravate();
                } 
                else
                {
                    play_sfx_sound(SFX_WRENCHING_SENSATION);
                    You_feel("a wrenching sensation.");
                    tele(); /* teleport him */
                }
                break;
            case 12:
                You("are granted an insight!");
                if (invent)
                {
                    /* rn2(5) agrees w/seffects() */
                    (void)identify_pack(rn2(5), FALSE);
                }
                break;
            case 13:
                play_sfx_sound(SFX_ACQUIRE_CONFUSION);
                Your("mind turns into a pretzel!");
                make_confused(itimeout_incr(HConfusion, rnd(7) + 15),
                              FALSE);
                break;
            default:
                impossible("throne effect");
                break;
            }

        } else {
            if (is_prince(youmonst.data))
                You_feel("very comfortable here.");
            else
                You_feel("somehow out of place...");
        }

        if (!rn2(3) && IS_THRONE(levl[u.ux][u.uy].typ))
        {
            play_special_effect_at(SPECIAL_EFFECT_PUFF_OF_SMOKE, 0, u.ux, u.uy, FALSE);
            play_sfx_sound(SFX_VANISHES_IN_PUFF_OF_SMOKE);
            special_effect_wait_until_action(0);
            /* may have teleported */
            create_current_floor_location(u.ux, u.uy, 0, NO_GLYPH, TRUE);
            pline_The("throne vanishes in a puff of logic.");
            special_effect_wait_until_end(0);
        }
    } 
    else
    {
        pline("Having fun sitting on the %s?", surface(u.ux, u.uy));
    }
    return 1;
}

/* curse a few inventory items at random! */
void
rndcurse()
{
    int nobj = 0;
    int cnt, onum;
    struct obj *otmp;
    static const char mal_aura[] = "feel a malignant aura surround %s.";
    boolean antimagicsuccess = Antimagic_or_resistance;

    if (((uwep && uwep->oartifact && artifact_has_flag(uwep, AF_MAGIC_ABSORBING)) || (uarms && uarms->oartifact && artifact_has_flag(uarms, AF_MAGIC_ABSORBING))) && rn2(20)) 
    {
        play_sfx_sound(SFX_MALIGNANT_AURA_RESISTED);
        You(mal_aura, "the magic-absorbing blade");
        return;
    }
    
    if (Curse_resistance)
    {
        play_sfx_sound(SFX_MALIGNANT_AURA_RESISTED);
        You_feel("a malignant aura around you, but it quickly dissipates.");
        return;
    }

    if (antimagicsuccess)
    {
        play_sfx_sound(SFX_MALIGNANT_AURA_SURROUNDS);
        u_shieldeff();
        You(mal_aura, "you");
    }

    for (otmp = invent; otmp; otmp = otmp->nobj) {
        /* gold isn't subject to being cursed or blessed */
        if (otmp->oclass == COIN_CLASS)
            continue;
        nobj++;
    }
    if (nobj) {
        for (cnt = rnd(6 / ((!!antimagicsuccess) + (!!Half_spell_damage) + 1));
             cnt > 0; cnt--) {
            onum = rnd(nobj);
            for (otmp = invent; otmp; otmp = otmp->nobj) {
                /* as above */
                if (otmp->oclass == COIN_CLASS)
                    continue;
                if (--onum == 0)
                    break; /* found the target */
            }
            /* the !otmp case should never happen; picking an already
               cursed item happens--avoid "resists" message in that case */
            if (!otmp || otmp->cursed)
                continue; /* next target */

            if (otmp->oartifact && artifact_has_flag(otmp, AF_INTEL)
                && rn2(10) < 8) {
                play_sfx_sound(SFX_ITEM_RESISTS_NEGATIVE_EFFECT);
                pline("%s!", Tobjnam(otmp, "resist"));
                continue;
            }

            if (otmp->blessed)
            {
                play_sfx_sound(SFX_UNBLESS_ITEM_SUCCESS);
                unbless(otmp);
            }
            else
            {
                play_sfx_sound(SFX_CURSE_ITEM_SUCCESS);
                curse(otmp);
            }
        }
        update_inventory();
    }

    /* treat steed's saddle as extended part of hero's inventory */
    if (u.usteed && !rn2(4) && (otmp = which_armor(u.usteed, W_SADDLE)) != 0
        && !otmp->cursed) { /* skip if already cursed */
        if (otmp->blessed)
        {
            play_sfx_sound(SFX_UNBLESS_ITEM_SUCCESS);
            unbless(otmp);
        }
        else
        {
            play_sfx_sound(SFX_CURSE_ITEM_SUCCESS);
            curse(otmp);
        }
        if (!Blind) {
            pline("%s %s.", Yobjnam2(otmp, "glow"),
                  hcolor(otmp->cursed ? NH_BLACK : (const char *) "brown"));
            otmp->bknown = TRUE;
        }
    }
}

/* remove a random INTRINSIC ability */
void
attrcurse()
{
    switch (rnd(11)) {
    case 1:
        if (HFire_immunity & INTRINSIC) {
            HFire_immunity &= ~INTRINSIC;
            You_feel("warmer.");
            break;
        }
        /*FALLTHRU*/
    case 2:
        if (HTeleportation & INTRINSIC) {
            HTeleportation &= ~INTRINSIC;
            You_feel("less jumpy.");
            break;
        }
        /*FALLTHRU*/
    case 3:
        if (HPoison_resistance & INTRINSIC) {
            HPoison_resistance &= ~INTRINSIC;
            You_feel("a little sick!");
            break;
        }
        /*FALLTHRU*/
    case 4:
        if (HBlind_telepat & INTRINSIC) {
            HBlind_telepat &= ~INTRINSIC;
            if (Blind && !(Blind_telepat || Unblind_telepat || Detect_monsters))
                see_monsters(); /* Can't sense mons anymore! */
            Your("senses fail!");
            break;
        }
        /*FALLTHRU*/
    case 5:
        if (HTelepat & INTRINSIC) {
            HTelepat &= ~INTRINSIC;
            see_monsters(); /* Can't sense mons anymore! */
            Your("senses fail!");
            break;
        }
        /*FALLTHRU*/
    case 6:
        if (HCold_immunity & INTRINSIC) {
            HCold_immunity &= ~INTRINSIC;
            You_feel("cooler.");
            break;
        }
        /*FALLTHRU*/
    case 7:
        if (HInvis & INTRINSIC) {
            HInvis &= ~INTRINSIC;
            You_feel("paranoid.");
            break;
        }
        /*FALLTHRU*/
    case 8:
        if (HSee_invisible & INTRINSIC) {
            HSee_invisible &= ~INTRINSIC;
            You("%s!", Hallucination ? "tawt you taw a puttie tat"
                                     : "thought you saw something");
            break;
        }
        /*FALLTHRU*/
    case 9:
        if (HFast & INTRINSIC) {
            HFast &= ~INTRINSIC;
            You_feel("slower.");
            break;
        }
        /*FALLTHRU*/
    case 10:
        if (HStealth & INTRINSIC) {
            HStealth &= ~INTRINSIC;
            You_feel("clumsy.");
            break;
        }
        /*FALLTHRU*/
    case 11:
        /* intrinsic protection is just disabled, not set back to 0 */
        if (HMagical_protection & INTRINSIC) {
            HMagical_protection &= ~INTRINSIC;
            You_feel("vulnerable.");
            break;
        }
        /*FALLTHRU*/
    case 12:
        if (HAggravate_monster & INTRINSIC) {
            HAggravate_monster &= ~INTRINSIC;
            You_feel("less attractive.");
            break;
        }
        /*FALLTHRU*/
    default:
        break;
    }
}

/*sit.c*/
