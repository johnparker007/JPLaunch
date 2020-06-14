using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using UnityEngine;

public class SDFileTask
{
    public bool InUse
    {
        get;
        set;
    }

    private string _filename = null;
    private byte[] _bytes = null;

    public void WriteAllBytesAsync(string filename, byte[] bytes, int overrideLength)
    {
        _filename = (string)filename.Clone();

        if (overrideLength == 0)
        {
            _bytes = (byte[])bytes.Clone();
        }
        else
        {
            _bytes = bytes.Take(overrideLength).ToArray();
        }

        if(!FastCRC.Instance.AddOrUpdateFile(_filename, _bytes))
        {
            WriteAllBytesAsyncTask();
        }
        else
        {
            InUse = false;
        }
    }

    private async void WriteAllBytesAsyncTask()
    {
        await Task.Run(() =>
        {
            try
            {
                File.WriteAllBytes(_filename, _bytes);
            }
            catch (Exception exception)
            {
                Debug.LogError("Exception trying to WriteAllBytes in Async function: " + exception);
            }

            InUse = false;
        });
    }

    public void CopyFileAsync(string sourceFilename, string targetFilename)
    {
        byte[] fileBytes = File.ReadAllBytes(sourceFilename);

        WriteAllBytesAsync(targetFilename, fileBytes, 0);
    }



}
