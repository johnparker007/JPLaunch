using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstallStatusRowGenerateNumberedGameFiles : InstallStatusRowBase
{
    protected override string RowText
    {
        get
        {
            return "Generate Numbered Game Files";
        }
    }

    protected override int Total
    {
        get
        {
            return Installer.InstallInstance.NumberedGameFilesTotal;
        }
    }

    protected override int Remaining
    {
        get
        {
            return Installer.InstallInstance.NumberedGameFilesRemaining;
        }
    }
}
