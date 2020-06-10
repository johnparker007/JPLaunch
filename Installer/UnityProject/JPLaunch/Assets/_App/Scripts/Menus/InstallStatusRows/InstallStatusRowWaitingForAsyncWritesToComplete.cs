using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstallStatusRowWaitingForAsyncWritesToComplete : InstallStatusRowBase
{
    protected override string RowText
    {
        get
        {
            return "Waiting for async writes to complete";
        }
    }

    protected override int Total
    {
        get
        {
            return Installer.InstallInstance.AsyncWritesTotal;
        }
    }

    protected override int Remaining
    {
        get
        {
            return Installer.InstallInstance.AsyncWritesRemaining;
        }
    }
}
