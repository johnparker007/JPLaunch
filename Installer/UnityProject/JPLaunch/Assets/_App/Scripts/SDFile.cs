using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;
using System;
using System.Text;
using System.IO;

public class SDFile
{
    public SDFile()
    {

    }

    public static bool WriteAllBytes(String filename, byte[] bytes, int overrideLength = 0)
    {

        try
        {
            if(overrideLength == 0)
            {
                File.WriteAllBytes(filename, bytes);
            }
            else
            {
                // TOIMPROVE probably a more efficient way of doing this
                IEnumerable<byte> bytesToWrite = bytes.Take(overrideLength);
                File.WriteAllBytes(filename, bytesToWrite.ToArray());
            }
        }
        catch (IOException ioException)
        {
            Debug.LogWarning("Caught IOException " + ioException + " writing file " + filename);
            return false;
        }

        return true;
    }

    public static String CreateFlattenedFilepath(String rootFolder, String filename)
    {
        String directoryPath = "";
        for(int characterIndex = 0; characterIndex < filename.Length - 1; ++characterIndex)
        {
            String character = filename.Substring(characterIndex, 1);

            directoryPath += character;

            Directory.CreateDirectory(rootFolder + "/" + directoryPath);

            directoryPath += "/";
        }

        return directoryPath;
    }

    public static String GetFlattenedFilename(String filename)
    {
        // domark
        // want: /d/o/m/a/r/k

        String flattenedFilename = "";



        return flattenedFilename;
    }
}
