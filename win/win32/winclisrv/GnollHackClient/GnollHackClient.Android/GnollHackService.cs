﻿using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.IO;
using Xamarin.Forms;
using System.Runtime.InteropServices;
using Android.Content.Res;
using GnollHackClient;
using GnollHackCommon;

[assembly: Dependency(typeof(GnollHackClient.Droid.GnollHackService))]
namespace GnollHackClient.Droid
{
    class GnollHackService : IGnollHackService
    {
        private string _gnollhackfilesdir;

        [DllImport(@"libgnollhackdroid.so")]
        public static extern int RunGnollHack(
            [MarshalAs(UnmanagedType.LPStr)] string gnhdir,
            [MarshalAs(UnmanagedType.LPStr)] string cmdlineargs,
            UInt32 runflags,
            UInt32 wincaps1,
            UInt32 wincaps2,
            VoidVoidCallback callback_init_nhwindows,
            IntVoidCallback callback_player_selection,
            CharVoidCallback callback_askname,
            VoidVoidCallback callback_get_nh_event,
            VoidConstCharCallback callback_exit_nhwindows,
            VoidConstCharCallback callback_suspend_nhwindows,
            VoidVoidCallback callback_resume_nhwindows,
            IntIntCallback callback_create_nhwindow,
            VoidIntCallback callback_clear_nhwindow,
            VoidIntBooleanCallback callback_display_nhwindow,
            VoidIntCallback callback_destroy_nhwindow,
            VoidIntIntIntCallback callback_curs,
            PutStrExColorCallback callback_putstr_ex,
            VoidIntIntConstCharCallback callback_putmixed,
            VoidConstCharBooleanCallback callback_display_file,
            VoidIntCallback callback_start_menu,
            AddMenuCallback callback_add_menu,
            AddExtendedMenuCallback callback_add_extended_menu,
            VoidIntConstCharCallback callback_end_menu,
            IntIntIntOutIntCallback callback_select_menu,
            VoidIntCallback callback_message_menu, /* no need for X-specific handling */
            VoidVoidCallback callback_update_inventory,
            VoidVoidCallback callback_mark_synch,
            VoidVoidCallback callback_wait_synch,
            /* If clipping is on */
            VoidIntIntBooleanCallback callback_cliparound,
            /* If positionbar is on */
            VoidCharCallback callback_update_positionbar,
            VoidIntIntIntIntIntLongIntUlongCallback callback_print_glyph,
            VoidIntCallback callback_init_print_glyph,
            VoidConstCharCallback callback_raw_print,
            VoidConstCharCallback callback_raw_print_bold,
            IntVoidCallback callback_nhgetch,
            NhPosKeyCallback callback_nh_poskey,
            VoidVoidCallback callback_nhbell,
            IntVoidCallback callback_doprev_message,
            IntConstCharPtrConstCharPtrCharPtrCallback callback_yn_function,
            GetLineCallback callback_getlin,
            IntVoidCallback callback_get_ext_cmd,
            VoidIntCallback callback_number_pad,
            VoidVoidCallback callback_delay_output,
            VoidIntCallback callback_delay_output_milliseconds,
            VoidIntCallback callback_delay_output_intervals,

            VoidVoidCallback callback_change_color,
            VoidIntCallback callback_change_background,
            VoidIntCallback callback_set_font_name,
            CharVoidCallback callback_get_color_string,

            VoidVoidCallback callback_start_screen,
            VoidVoidCallback callback_end_screen,
            VoidIntCallback callback_outrip,
            VoidConstCharCallback callback_preference_update,
            CharPtrBooleanCallback callback_getmsghistory,
            VoidConstCharBooleanCallback callback_putmsghistory,
            VoidVoidCallback callback_status_init,
            VoidVoidCallback callback_status_finish,
            VoidIntConstCharPtrConstCharPtrBooleanCallback callback_status_enablefield,
            StatusUpdateCallback callback_status_update,
            BooleanVoidCallback callback_can_suspend_yes,
            VoidVoidCallback callback_stretch_window,
            VoidUlongCallback callback_set_animation_timer,
            VoidIntCallback callback_open_special_view,
            BooleanVoidCallback callback_stop_all_sounds,
            BooleanIntDoubleCallback callback_play_immediate_ghsound,
            BooleanIntDoubleCallback callback_play_ghsound_occupation_ambient,
            BooleanIntDoubleCallback callback_play_ghsound_effect_ambient,
            BooleanDoubleCallback callback_set_effect_ambient_volume,
            BooleanDoubleCallback callback_play_ghsound_music,
            BooleanDoubleCallback callback_play_ghsound_level_ambient,
            BooleanDoubleCallback callback_play_ghsound_environment_ambient,
            BooleanDoubleDoubleDoubleDoubleDoubleCallback callback_adjust_ghsound_general_volumes,
            BooleanIntDoubleVoidPtrCallback callback_add_ambient_ghsound,
            BooleanVoidPtrCallback callback_delete_ambient_ghsound,
            BooleanDoubleVoidPtrCallback callback_set_ambient_ghsound_volume,
            VoidIntCallback callback_exit_hack,
            CharVoidCallback callback_getcwd,
            IntCharCharUintCallback callback_messagebox,
            VoidIntCallback callback_outrip_begin,
            VoidIntCallback callback_outrip_end,

            FreeMemoryCallback callback_free_memory
        );

        [DllImport(@"libgnollhackdroid.so")]
        public static extern int GetGlyph2Tile(out IntPtr gl2ti_ptr, out int size);
        [DllImport(@"libgnollhackdroid.so")]
        public static extern int CountTotalTiles();
        [DllImport(@"libgnollhackdroid.so")]
        public static extern int LibGetUnexploredGlyph();
        [DllImport(@"libgnollhackdroid.so")]
        public static extern int LibGetNoGlyph();

        [DllImport(@"libgnollhackdroid.so")]
        public static extern int DoSomeCalcDroid();
        [DllImport(@"libgnollhackdroid.so")]
        public static extern int DoSomeHackDroid();
        [DllImport(@"libgnollhackdroid.so")]
        public static extern int RunGnollHackTest([MarshalAs(UnmanagedType.LPStr)] string gnhdir);

        private void LoadNativeLibrary(string libName)
        {
            Java.Lang.JavaSystem.LoadLibrary(libName);
        }
        private void UnloadNativeLibrary(string libName)
        {
            Java.Lang.JavaSystem.Gc();
        }

        public void LoadLibrary()
        {
            LoadNativeLibrary("gnollhackdroid");
        }
        public void UnloadLibrary()
        {
            UnloadNativeLibrary("gnollhackdroid");
        }
        public void InitializeGnollHack()
        {
            /* Unpack GnollHack files */
            /* Add a check whether to unpack if there are existing files or not */

            string filesdir = Android.App.Application.Context.FilesDir.Path;
            _gnollhackfilesdir = filesdir;

            /* For debugging purposes now, delete all existing files in filesdir first */
            //System.IO.DirectoryInfo di = new DirectoryInfo(_gnollhackfilesdir);

            //foreach (FileInfo file in di.GetFiles())
            //{
            //    file.Delete();
            //}

            /* Make relevant directories */
            string[] ghdirlist = { "save" };
            foreach (string ghdir in ghdirlist)
            {
                string fulldirepath = Path.Combine(_gnollhackfilesdir, ghdir);
                if (!Directory.Exists(fulldirepath))
                {
                    Directory.CreateDirectory(fulldirepath);
                }
            }


            /* Copy missing files from resources */
            string content;
            AssetManager assets = MainActivity.StaticAssets;

            string assetsourcedir = "gnh";
            string[] txtfileslist = { "credits", "license", "logfile", "perm", "record", "recover", "symbols", "sysconf", "xlogfile", "defaults.gnh" };

            foreach (string txtfile in txtfileslist)
            {
                string fullsourcepath = Path.Combine(assetsourcedir, txtfile);
                using (StreamReader sr = new StreamReader(assets.Open(fullsourcepath)))
                {
                    content = sr.ReadToEnd();
                }
                string fulltargetpath = Path.Combine(filesdir, txtfile);
                if (File.Exists(fulltargetpath))
                {
                    /* Should check whether the current one is an up-to-date version; assume for now that it is not */
                    File.Delete(fulltargetpath);
                    //continue;
                }

                using (StreamWriter sw = new StreamWriter(fulltargetpath))
                {
                    sw.Write(content);
                }
            }

            string[] binfileslist = { "nhdat" };
            byte[] data;
            int maxsize = 2048 * 1024;
            foreach (string binfile in binfileslist)
            {
                string fullsourcepath = Path.Combine(assetsourcedir, binfile);

                using (BinaryReader br = new BinaryReader(assets.Open(fullsourcepath)))
                {
                    data = br.ReadBytes(maxsize);
                }

                string fulltargetpath = Path.Combine(filesdir, binfile);
                if (File.Exists(fulltargetpath))
                {
                    /* Should check whether the current one is an up-to-date version; assume for now that it is not */
                    File.Delete(fulltargetpath);
                    //continue;
                }

                using (BinaryWriter sw = new BinaryWriter(File.Open(fulltargetpath, FileMode.Create)))
                {
                    sw.Write(data);
                }
            }
        }

        public void GetTileArrays(out IntPtr gl2ti, out int size)
        {
            GetGlyph2Tile(out gl2ti, out size);
        }
        public int GetTotalTiles()
        {
            return CountTotalTiles();
        }
        public int GetUnexploredGlyph()
        {
            return LibGetUnexploredGlyph();
        }
        public int GetNoGlyph()
        {
            return LibGetNoGlyph();
        }

        public int Test1()
        {
            return DoSomeCalcDroid();
        }
        public int Test2()
        {
            return DoSomeHackDroid();
        }
        public int TestRunGnollHack()
        {
            return RunGnollHackTest(_gnollhackfilesdir);
        }
        public int StartGnollHack(ClientGame clientGame)
        {
            return RunGnollHack(
                _gnollhackfilesdir,
                "",
                (UInt32)(clientGame.WizardMode ? RunGnollHackFlags.WizardMode : 0),
                0,
                0,
                clientGame.ClientCallback_InitWindows,
                clientGame.ClientCallback_PlayerSelection,
                clientGame.ClientCallback_AskName,
                clientGame.ClientCallback_get_nh_event,
                clientGame.ClientCallback_ExitWindows,
                clientGame.ClientCallback_VoidConstCharDummy,
                clientGame.ClientCallback_VoidVoidDummy,
                clientGame.ClientCallback_CreateGHWindow,
                clientGame.ClientCallback_ClearGHWindow,
                clientGame.ClientCallback_DisplayGHWindow,
                clientGame.ClientCallback_DestroyGHWindow,
                clientGame.ClientCallback_Curs,
                clientGame.ClientCallback_PutStrEx,
                clientGame.ClientCallback_VoidIntIntConstCharDummy,
                clientGame.ClientCallback_VoidConstCharBooleanDummy,
                clientGame.ClientCallback_StartMenu,
                clientGame.ClientCallback_AddMenu,
                clientGame.ClientCallback_AddExtendedMenu,
                clientGame.ClientCallback_EndMenu,
                clientGame.ClientCallback_SelectMenu,
                clientGame.ClientCallback_VoidIntDummy, /* no need for X-specific handling */
                clientGame.ClientCallback_VoidVoidDummy,
                clientGame.ClientCallback_VoidVoidDummy,
                clientGame.ClientCallback_VoidVoidDummy,
                /* If clipping is on */
                clientGame.ClientCallback_Cliparound,
                /* If positionbar is on */
                clientGame.ClientCallback_VoidCharDummy,
                clientGame.ClientCallback_PrintGlyph,
                clientGame.ClientCallback_VoidIntDummy,
                clientGame.ClientCallback_RawPrint,
                clientGame.ClientCallback_RawPrintBold,
                clientGame.ClientCallback_nhgetch,
                clientGame.ClientCallback_nh_poskey,
                clientGame.ClientCallback_VoidVoidDummy,
                clientGame.ClientCallback_IntVoidDummy,
                clientGame.ClientCallback_yn_question,
                clientGame.ClientCallback_getlin,
                clientGame.ClientCallback_IntVoidDummy,
                clientGame.ClientCallback_VoidIntDummy,
                clientGame.ClientCallback_DelayOutput,
                clientGame.ClientCallback_DelayOutputMilliseconds,
                clientGame.ClientCallback_DelayOutputIntervals,

                clientGame.ClientCallback_VoidVoidDummy,
                clientGame.ClientCallback_VoidIntDummy,
                clientGame.ClientCallback_VoidIntDummy,
                clientGame.ClientCallback_CharVoidDummy,

                clientGame.ClientCallback_VoidVoidDummy,
                clientGame.ClientCallback_VoidVoidDummy,
                clientGame.ClientCallback_VoidIntDummy,
                clientGame.ClientCallback_PreferenceUpdate,
                clientGame.ClientCallback_GetMsgHistory,
                clientGame.ClientCallback_PutMsgHistory,
                clientGame.ClientCallback_StatusInit,
                clientGame.ClientCallback_StatusFinish,
                clientGame.ClientCallback_StatusEnable,
                clientGame.ClientCallback_StatusUpdate,
                clientGame.ClientCallback_BooleanVoidDummy,
                clientGame.ClientCallback_VoidVoidDummy,
                clientGame.ClientCallback_VoidUlongDummy,
                clientGame.ClientCallback_VoidIntDummy,
                clientGame.ClientCallback_BooleanVoidDummy,
                clientGame.ClientCallback_BooleanIntDoubleDummy,
                clientGame.ClientCallback_BooleanIntDoubleDummy,
                clientGame.ClientCallback_BooleanIntDoubleDummy,
                clientGame.ClientCallback_BooleanDoubleDummy,
                clientGame.ClientCallback_BooleanDoubleDummy,
                clientGame.ClientCallback_BooleanDoubleDummy,
                clientGame.ClientCallback_BooleanDoubleDummy,
                clientGame.ClientCallback_BooleanDoubleDoubleDoubleDoubleDoubleDummy,
                clientGame.ClientCallback_BooleanIntDoubleVoidPtrDummy,
                clientGame.ClientCallback_BooleanVoidPtrDummy,
                clientGame.ClientCallback_BooleanDoubleVoidPtrDummy,
                clientGame.ClientCallback_ExitHack,
                clientGame.ClientCallback_GetCwd,
                clientGame.ClientCallback_MessageBox,
                clientGame.ClientCallback_VoidIntDummy,
                clientGame.ClientCallback_VoidIntDummy,

                clientGame.ClientCallback_FreeMemory
                );

        }
    }
}