using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;
using System;
using System.Text;
using System.IO;
using System.Threading.Tasks;

public class SDFile
{
    public SDFile()
    {

    }

    public static async Task<bool> WriteAllBytesAsync(String filename, byte[] bytes, int overrideLength = 0)
    {
        if(overrideLength == 0)
        {
            return await WriteAllBytesAsyncTask(filename, bytes);
        }
        else
        {
            // TOIMPROVE probably a more efficient way of doing this
            IEnumerable<byte> bytesToWrite = bytes.Take(overrideLength);
            return await WriteAllBytesAsyncTask(filename, bytesToWrite.ToArray());
        }
    }

    private static async Task<bool> WriteAllBytesAsyncTask(String filename, byte[] bytes)
    {
        bool writtenWithoutException = true;
        await Task.Run(() =>
        {
            try
            {
                File.WriteAllBytes(filename, bytes);
            }
            catch(Exception exception)
            {
                Debug.LogError("Exception trying to WriteAllBytes in Async function: " + exception);
                writtenWithoutException = false;
            }
        });

        return writtenWithoutException;
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
