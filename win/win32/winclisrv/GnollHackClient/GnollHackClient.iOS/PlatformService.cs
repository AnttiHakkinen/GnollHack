﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Xamarin.Forms;
using System.Runtime.InteropServices;
using GnollHackClient;

using Foundation;
using UIKit;

[assembly: Dependency(typeof(GnollHackClient.iOS.PlatformService))]
namespace GnollHackClient.iOS
{
    public class PlatformService : IPlatformService
    {
        public string GetVersionString()
        {
            NSObject ver = NSBundle.MainBundle.InfoDictionary["CFBundleShortVersionString"];
            return ver.ToString();
        }

        public ulong GetDeviceMemoryInBytes()
        {
            try
            {
                NSProcessInfo info = NSProcessInfo.ProcessInfo;
                ulong memory = info.PhysicalMemory;
                return memory;
            }
            catch
            {
                return 0;
            }
        }

        public ulong GetDeviceFreeDiskSpaceInBytes()
        {
            try
            {
                ulong freesize = NSFileManager.DefaultManager.GetFileSystemAttributes(Environment.GetFolderPath(Environment.SpecialFolder.Personal)).FreeSize;
                return freesize;
            }
            catch
            {
                return 0;
            }
        }

        public ulong GetDeviceTotalDiskSpaceInBytes()
        {
            try
            {
                ulong totalsize = NSFileManager.DefaultManager.GetFileSystemAttributes(Environment.GetFolderPath(Environment.SpecialFolder.Personal)).Size;
                return totalsize;
            }
            catch
            {
                return 0;
            }
        }

        public void CloseApplication()
        {
            RevertAnimationDuration(true);
            //MainActivity.CurrentMainActivity.Finish();
        }

        public void SetStatusBarHidden(bool ishidden)
        {
            UIApplication.SharedApplication.StatusBarHidden = ishidden;
        }

        public bool GetStatusBarHidden()
        {
            return UIApplication.SharedApplication.StatusBarHidden;
        }

        //public void SaveFileToDownloads(byte[] data, string name)
        //{
            //if (MainActivity.CurrentMainActivity?.CheckSelfPermission(Manifest.Permission.WriteExternalStorage) != Android.Content.PM.Permission.Granted)
            //{
            //    MainActivity.CurrentMainActivity?.RequestPermissions(new string[] { Manifest.Permission.WriteExternalStorage }, 0);
            //}

            //if (MainActivity.CurrentMainActivity?.CheckSelfPermission(Manifest.Permission.WriteExternalStorage) == Android.Content.PM.Permission.Granted)
            //{
            //    string path = Android.OS.Environment.GetExternalStoragePublicDirectory(Android.OS.Environment.DirectoryDownloads).AbsolutePath;
            //    string filePath = System.IO.Path.Combine(path, name);

            //    if (System.IO.File.Exists(filePath))
            //    {
            //        System.IO.FileInfo file = new System.IO.FileInfo(filePath);
            //        file.Delete();
            //    }
            //    FileOutputStream fileOutputStream = new FileOutputStream(new Java.IO.File(filePath));
            //    fileOutputStream.Write(data);
            //    fileOutputStream.Close();
            //}
        //}

        public void OverrideAnimationDuration()
        {

        }
        public void RevertAnimationDuration(bool isfinal)
        {

        }
    }
}