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
                return Install.kUDGTapIconString;
            case Installer.FileFormat.Sna:
                return Install.kUDGSnaIconString;
            case Installer.FileFormat.Z80:
                return Install.kUDGZ80IconString;
            default:
                Debug.LogError("Couldn't match format");
                Debug.Break();
                return Install.kUDGTapIconString;
        }
    }

}
