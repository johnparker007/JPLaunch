using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstallStatusRowGenerateGameListPagesMini : InstallStatusRowBase
{
    protected override string RowText
    {
        get
        {
            return "Generate Game List Pages - mini";
        }
    }

    protected override int Total
    {
        get
        {
            return Installer.InstallInstance.GameListPagesTotalMini;
        }
    }

    protected override int Remaining
    {
        get
        {
            return Installer.InstallInstance.GameListPagesRemainingMini;
        }
    }
}
