using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpectrumFiles : MonoBehaviour 
{
    [Header("Files")]
    public TextAsset AppCodeBin = null;
    public TextAsset App_NIRVANAP_7_ROWSBin = null;
    public TextAsset App_NIRVANAP_23_ROWSBin = null;
    public TextAsset BSave = null;
    public TextAsset ChDir = null;
    public TextAsset Ibm_fontChr = null;
    public TextAsset JPLAUNCHTap = null;
    public TextAsset Ld16384_recompiled = null;
    public TextAsset MiniFzx = null;
    public TextAsset LD25000 = null;
    public TextAsset LD43000 = null;
    public TextAsset SearchWindowScr = null;

    public Installer Installer = null;

    public void WriteFiles()
    {
        WriteFile(AppCodeBin, Installer.OutputFolder + "/" + Install.kCodeFolder + "/" + "jplaunch");
        WriteFile(App_NIRVANAP_7_ROWSBin, Installer.OutputFolder + "/" + Install.kCodeFolder + "/" + "nirvana7");
        WriteFile(App_NIRVANAP_23_ROWSBin, Installer.OutputFolder + "/" + Install.kCodeFolder + "/" + "nirvana");
        WriteFile(BSave, Installer.OutputFolder + "/" + Install.kCodeFolder + "/" + "BSAVE");
        WriteFile(ChDir, Installer.OutputFolder + "/" + Install.kCodeFolder + "/" + "CHDIR");
        WriteFile(Ibm_fontChr, Installer.OutputFolder + "/" + Install.kGraphicsFolder + "/" + "8x8font");
        WriteFile(JPLAUNCHTap, Installer.Configuration.ESXDOSRootPath + "/" + "JPLAUNCH.TAP");
        WriteFile(Ld16384_recompiled, Installer.OutputFolder + "/" + Install.kCodeFolder + "/" + "jpl16384");
        WriteFile(MiniFzx, Installer.OutputFolder + "/" + Install.kGraphicsFolder + "/" + "propfont");
        WriteFile(LD25000, Installer.Configuration.ESXDOSRootPath + "/" + Install.kDotCommandsFolder + "/" + "LD25000");
        WriteFile(LD43000, Installer.Configuration.ESXDOSRootPath + "/" + Install.kDotCommandsFolder + "/" + "LD43000");
        WriteFile(SearchWindowScr, Installer.OutputFolder + "/" + Install.kGraphicsFolder + "/" + "srch_win");
    }

    private void WriteFile(TextAsset fileBytes, string filename)
    {
        SDFileManager.WriteAllBytesAsync(filename, fileBytes.bytes);
    }
}
