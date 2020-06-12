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

    private string _sourceFilename = null;
    private string _targetFilename = null;

    public void WriteAllBytesAsync(string filename, byte[] bytes, int overrideLength)
    {
        _filename = (string)filename.Clone();

        if (overrideLength == 0)
        {
            _bytes = (byte[])bytes.Clone();

            WriteAllBytesAsyncTask();
        }
        else
        {
            _bytes = bytes.Take(overrideLength).ToArray();

            WriteAllBytesAsyncTask();
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
        _sourceFilename = (string)sourceFilename.Clone();
        _targetFilename = (string)targetFilename.Clone();

        CopyFileAsyncTask();
    }

    private async void CopyFileAsyncTask()
    {
        await Task.Run(() =>
        {
            try
            {
                File.Copy(_sourceFilename, _targetFilename, true);
            }
            catch (Exception exception)
            {
                Debug.LogError("Exception trying to copy file in Async function: " + exception);
            }

            InUse = false;
        });
    }


}
