using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstallStatusRowGenerateSearchStringsFull : InstallStatusRowBase
{
    protected override string RowText
    {
        get
        {
            return "Generate Search Strings - full";
        }
    }

    protected override int Total
    {
        get
        {
            return Installer.InstallInstance.SearchStringsTotalFull;
        }
    }

    protected override int Remaining
    {
        get
        {
            return Installer.InstallInstance.SearchStringsRemainingFull;
        }
    }
}
