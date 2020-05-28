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

    public bool WriteAllBytes(String filename, byte[] bytes)
    {
        try
        {
            File.WriteAllBytes(filename, bytes);
        }
        catch (IOException ioException)
        {
            Debug.LogWarning("Caught IOException " + ioException + " writing file " + filename);
            return false;
        }

        return true;
    }

    public String CreateFlattenedFilepath(String rootFolder, String filename)
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

    public String GetFlattenedFilename(String filename)
    {
        // domark
        // want: /d/o/m/a/r/k

        String flattenedFilename = "";



        return flattenedFilename;
    }
}
