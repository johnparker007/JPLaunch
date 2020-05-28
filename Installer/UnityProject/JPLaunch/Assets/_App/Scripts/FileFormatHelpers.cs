using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FileFormatHelpers
{
    public static Installer.FileFormat GetFileFormat(string filename)
    {
        string fileExtension = filename.Substring(filename.Length - 3);
        if (fileExtension.ToUpper() == "TAP")
        {
            return Installer.FileFormat.Tap;
        }
        else if (fileExtension.ToUpper() == "SNA")
        {
            return Installer.FileFormat.Sna;
        }
        else if (fileExtension.ToUpper() == "Z80")
        {
            return Installer.FileFormat.Z80;
        }
        else
        {
            Debug.LogError("Couldn't match extension");
            Debug.Break();
            return Installer.FileFormat.Tap;
        }
    }

}
