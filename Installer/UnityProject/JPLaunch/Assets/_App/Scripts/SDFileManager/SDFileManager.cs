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

    public static string CreateFlattenedFilepath(
        string rootFolder, 
        string sourceFilenameToCreatePath, 
        string targetFilenameAtPath, 
        string filenameExtension)
    {
        List<string> directoriesToWrite = new List<string>();
        string directoryPath = "";
        for (int characterIndex = 0; characterIndex < sourceFilenameToCreatePath.Length; ++characterIndex)
        {
            string character = sourceFilenameToCreatePath.Substring(characterIndex, 1);

            directoryPath += character;
             
            directoriesToWrite.Add(rootFolder + directoryPath);

            directoryPath += "/";
        }

        string filePath = 
            rootFolder 
            + directoryPath 
            + targetFilenameAtPath
            + filenameExtension;
        if (!FastCRC.Instance.IsFilePathInDatabase(filePath))
        {
            foreach (string writePath in directoriesToWrite)
            {
                Directory.CreateDirectory(writePath);
            }
        }

        return directoryPath;
    }

}
