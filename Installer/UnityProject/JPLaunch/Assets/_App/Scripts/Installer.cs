
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
    

    public const string kOutputRoot= "C:/Users/John/Desktop/ZEsarUX_win-8.1/_SD_CARD_ROOT_087";
    public const string kOutputFolder = kOutputRoot + "/JPLAUNCH";


    public SpectrumFiles SpectrumFiles = null;

    public Install InstallPrefab = null;

    private Install _install = null;

    public MasterStateType MasterState
    {
        get;
        set;
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
            if(_install == null)
            {
                return 0;
            }

            return _install.SearchStringsTotal;
        }
    }

    public int GameListPagesTotal
    {
        get
        {
            if (_install == null)
            {
                return 0;
            }

            return _install.GameListPagesTotal;
        }
    }

    public int SearchStringsRemaining
    {
        get
        {
            if (_install == null)
            {
                return 0;
            }

            return _install.SearchStringsRemaining;
        }
    }

    public int GameListPagesRemaining
    {
        get
        {
            if (_install == null)
            {
                return 0;
            }

            return _install.GameListPagesRemaining;
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

    public void Install()
    {
        if(_install != null)
        {
            Destroy(_install.gameObject);
        }

        _install = Instantiate(InstallPrefab, transform);
        _install.StartInstall(this);
    }


}
