using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstallStatusRowGenerateSearchStringsMini : InstallStatusRowBase
{
    protected override string RowText
    {
        get
        {
            return "Generate Search Strings - mini";
        }
    }

    protected override int Total
    {
        get
        {
            return Installer.InstallInstance.SearchStringsTotalMini;
        }
    }

    protected override int Remaining
    {
        get
        {
            return Installer.InstallInstance.SearchStringsRemainingMini;
        }
    }
}
