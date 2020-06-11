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

            Directory.CreateDirectory(rootFolder + "/" + directoryPath);

            directoryPath += "/";
        }

        return directoryPath;
    }

    public static string GetFlattenedFilename(string filename)
    {
        // domark
        // want: /d/o/m/a/r/k

        string flattenedFilename = "";

        return flattenedFilename;
    }


}
