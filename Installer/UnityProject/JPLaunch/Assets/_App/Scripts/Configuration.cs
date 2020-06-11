using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Configuration
{
    private const string kKeyGamesRootPath = "GamesRootPath";
    private const string kKeyESXDOSRootPath = "ESXDOSRootPath";
    private const string kKeyAutobootFPLaunch = "AutobootFPLaunch";
    private const string kKeyIncludeTapFiles = "IncludeTapFiles";
    private const string kKeyIncludeSnaFiles = "IncludeSnaFiles";
    private const string kKeyIncludeZ80Files = "IncludeZ80Files";


    public string GamesRootPath
    {
        get;
        set;
    }

    public string ESXDOSRootPath
    {
        get;
        set;
    }

    public bool AutobootFPLaunch
    {
        get;
        set;
    }

    public bool IncludeTapFiles
    {
        get;
        set;
    }

    public bool IncludeSnaFiles
    {
        get;
        set;
    }

    public bool IncludeZ80Files
    {
        get;
        set;
    }

    public void Load()
    {
        GamesRootPath = PlayerPrefs.GetString(kKeyGamesRootPath);
        ESXDOSRootPath = PlayerPrefs.GetString(kKeyESXDOSRootPath);
        AutobootFPLaunch = PlayerPrefs.GetInt(kKeyAutobootFPLaunch) == 1;
        IncludeTapFiles = PlayerPrefs.GetInt(kKeyIncludeTapFiles) == 1;
        IncludeSnaFiles = PlayerPrefs.GetInt(kKeyIncludeSnaFiles) == 1;
        IncludeZ80Files = PlayerPrefs.GetInt(kKeyIncludeZ80Files) == 1;
    }

    public void Save()
    {
        PlayerPrefs.SetString(kKeyGamesRootPath, GamesRootPath);
        PlayerPrefs.SetString(kKeyESXDOSRootPath, ESXDOSRootPath);
        PlayerPrefs.SetInt(kKeyAutobootFPLaunch, AutobootFPLaunch ? 1 : 0);
        PlayerPrefs.SetInt(kKeyIncludeTapFiles, IncludeTapFiles ? 1 : 0);
        PlayerPrefs.SetInt(kKeyIncludeSnaFiles, IncludeSnaFiles ? 1 : 0);
        PlayerPrefs.SetInt(kKeyIncludeZ80Files, IncludeZ80Files ? 1 : 0);

    }

}
