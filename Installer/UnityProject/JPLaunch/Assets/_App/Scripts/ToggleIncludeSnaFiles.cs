using UnityEngine;
using UnityEngine.UI;

public class ToggleIncludeSnaFiles: ToggleBase
{
    protected void Start()
    {
        _toggle.isOn = Installer.Configuration.IncludeSnaFiles;
    }

    protected override void OnValueChanged(bool value)
    {
        Installer.Configuration.IncludeSnaFiles = value;
        Installer.Configuration.Save();
    }

}