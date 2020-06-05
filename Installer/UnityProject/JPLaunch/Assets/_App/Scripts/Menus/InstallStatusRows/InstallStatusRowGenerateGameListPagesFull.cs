using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstallStatusRowGenerateGameListPagesFull : InstallStatusRowBase
{
    protected override string RowText
    {
        get
        {
            return "Generate Game List Pages - full";
        }
    }

    protected override int Total
    {
        get
        {
            return Installer.InstallInstance.GameListPagesTotalFull;
        }
    }

    protected override int Remaining
    {
        get
        {
            return Installer.InstallInstance.GameListPagesRemainingFull;
        }
    }
}
