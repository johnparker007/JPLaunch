using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstallStatusRowInitialInstallTasks : InstallStatusRowBase
{
    protected override string RowText
    {
        get
        {
            return "Initial Install Tasks";
        }
    }

    protected override int Total
    {
        get
        {
            return Installer.InstallInstance.InitialInstallTasksTotal;
        }
    }

    protected override int Remaining
    {
        get
        {
            return Installer.InstallInstance.InitialInstallTasksRemaining;
        }
    }
}
