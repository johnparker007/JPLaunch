using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstallStatusRowGenerateNumberedLoadingScreenFiles : InstallStatusRowBase
{
    protected override string RowText
    {
        get
        {
            return "Generate Numbered Loading Screen Files";
        }
    }

    protected override int Total
    {
        get
        {
            return Installer.InstallInstance.NumberedLoadingScreenFilesTotal;
        }
    }

    protected override int Remaining
    {
        get
        {
            return Installer.InstallInstance.NumberedLoadingScreenFilesRemaining;
        }
    }
}
