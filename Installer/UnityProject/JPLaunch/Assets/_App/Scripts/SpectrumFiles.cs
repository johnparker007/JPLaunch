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
        WriteFile(AppCodeBin, Installer.kOutputFolder + "/" + Installer.kCodeFolder + "/" + "jplaunch");
        WriteFile(App_NIRVANAP_7_ROWSBin, Installer.kOutputFolder + "/" + Installer.kCodeFolder + "/" + "nirvana7");
        WriteFile(App_NIRVANAP_23_ROWSBin, Installer.kOutputFolder + "/" + Installer.kCodeFolder + "/" + "nirvana");
        WriteFile(BSave, Installer.kOutputFolder + "/" + Installer.kCodeFolder + "/" + "BSAVE");
        WriteFile(ChDir, Installer.kOutputFolder + "/" + Installer.kCodeFolder + "/" + "CHDIR");
        WriteFile(Ibm_fontChr, Installer.kOutputFolder + "/" + Installer.kGraphicsFolder + "/" + "8x8font");
        WriteFile(JPLAUNCHTap, Installer.kOutputRoot + "/" + "JPLAUNCH.TAP");
        WriteFile(Ld16384_recompiled, Installer.kOutputFolder + "/" + Installer.kCodeFolder + "/" + "jpl16384");
        WriteFile(MiniFzx, Installer.kOutputFolder + "/" + Installer.kGraphicsFolder + "/" + "propfont");
        WriteFile(LD25000, Installer.kOutputRoot + "/" + Installer.kDotCommandsFolder + "/" + "LD25000");
        WriteFile(LD43000, Installer.kOutputRoot + "/" + Installer.kDotCommandsFolder + "/" + "LD43000");
        WriteFile(SearchWindowScr, Installer.kOutputFolder + "/" + Installer.kGraphicsFolder + "/" + "srch_win");
    }

    private void WriteFile(TextAsset fileBytes, string filename)
    {
        Installer.SDFile.WriteAllBytes(filename, fileBytes.bytes);
    }
}
