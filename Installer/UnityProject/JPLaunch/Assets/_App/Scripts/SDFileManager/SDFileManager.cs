using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

public class SDFileManager : MonoBehaviour 
{
    private static SDFileTaskPool _sdFileTaskPool = new SDFileTaskPool();

    public static int WritesInUse
    {
        get
        {
            return _sdFileTaskPool.WritesInUse;
        }
    }

    public static bool WritesComplete
    {
        get
        {
            return !_sdFileTaskPool.IsAnyTaskInUse;
        }
    }

    public static int PoolCount
    {
        get
        {
            return _sdFileTaskPool.PoolCount;
        }
    }

    public static void WriteAllBytesAsync(string filename, byte[] bytes, int overrideLength = 0)
    {
        SDFileTask sdFileTask = _sdFileTaskPool.GetNextFreeSDFileTask();

        sdFileTask.WriteAllBytesAsync(filename, bytes, overrideLength);
    }

    public static void CopyFileAsync(string sourceFilename, string targetFilename)
    {
        SDFileTask sdFileTask = _sdFileTaskPool.GetNextFreeSDFileTask();

        sdFileTask.CopyFileAsync(sourceFilename, targetFilename);
    }

    public static string CreateFlattenedFilepath(string rootFolder, string filename)
    {
        string directoryPath = "";
        for (int characterIndex = 0; characterIndex < filename.Length - 1; ++characterIndex)
        {
            string character = filename.Substring(characterIndex, 1);

            directoryPath += character;

            // TODO don't try to create dir if already there according to the saved dictionary
            // small time saving writing to SD from testing (maybe save 10%-20% overall time)
            Directory.CreateDirectory(rootFolder + "/" + directoryPath);

            directoryPath += "/";
        }

        return directoryPath;
    }

}
