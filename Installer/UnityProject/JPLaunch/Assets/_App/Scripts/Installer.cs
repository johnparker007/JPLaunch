
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using UnityEngine;
using UnityEngine.UI;

public class Installer : MonoBehaviour
{
    public enum MasterStateType
    {
        Idle,
        Running,
        CompletedSuccessfully,
        Failed
    }

    public enum FileFormat
    {
        Tap,
        Sna,
        Z80
    }
    
    public SpectrumFiles SpectrumFiles = null;

    public Install InstallPrefab = null;

    public string OutputFolder
    {
        get
        {
            return Configuration.ESXDOSRootPath + "/JPLAUNCH";
        }
    }

    public MasterStateType MasterState
    {
        get;
        set;
    }

    public Install InstallInstance
    {
        get;
        private set;
    }


    public Configuration Configuration
    {
        get;
        private set;
    }

    public int SearchStringsTotal
    {
        get
        {
            if(InstallInstance == null)
            {
                return 0;
            }

            return InstallInstance.SearchStringsTotalFull;
        }
    }

    public int GameListPagesTotal
    {
        get
        {
            if (InstallInstance == null)
            {
                return 0;
            }

            return InstallInstance.GameListPagesTotalFull;
        }
    }

    public int SearchStringsRemaining
    {
        get
        {
            if (InstallInstance == null)
            {
                return 0;
            }

            return InstallInstance.SearchStringsRemainingFull;
        }
    }

    public int GameListPagesRemaining
    {
        get
        {
            if (InstallInstance == null)
            {
                return 0;
            }

            return InstallInstance.GameListPagesRemainingFull;
        }
    }

    public int TotalObjects
    {
        get
        {
            return SearchStringsTotal + GameListPagesTotal;
        }
    }

    public int TotalObjectsRemaining
    {
        get
        {
            return SearchStringsRemaining + GameListPagesRemaining;
        }
    }

    private void Awake()
    {
        Configuration = new Configuration();
        Configuration.Load();

        MasterState = MasterStateType.Idle;
    }

    private void Start()
    {
        MenuController.Instance.SetMenu(MenuController.Instance.MenuMain);
    }

    public void Install()
    {
        MenuController.Instance.SetMenu(MenuController.Instance.MenuInstalling);

        if (InstallInstance != null)
        {
            Destroy(InstallInstance.gameObject);
        }

        InstallInstance = Instantiate(InstallPrefab, transform);
        InstallInstance.StartInstall(this);
    }


}
