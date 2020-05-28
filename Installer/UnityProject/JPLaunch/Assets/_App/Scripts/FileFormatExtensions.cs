using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class FileFormatExtensions
{
    public static string UDGIconString(this Installer.FileFormat fileFormat)
    {
        switch (fileFormat)
        {
            case Installer.FileFormat.Tap:
                return Installer.kUDGTapIconString;
            case Installer.FileFormat.Sna:
                return Installer.kUDGSnaIconString;
            case Installer.FileFormat.Z80:
                return Installer.kUDGZ80IconString;
            default:
                Debug.LogError("Couldn't match format");
                Debug.Break();
                return Installer.kUDGTapIconString;
        }
    }

}
