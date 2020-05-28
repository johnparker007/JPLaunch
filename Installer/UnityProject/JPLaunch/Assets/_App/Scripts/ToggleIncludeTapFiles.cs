using UnityEngine;
using UnityEngine.UI;

public class ToggleIncludeTapFiles: ToggleBase
{
    protected void Start()
    {
        _toggle.isOn = Installer.Configuration.IncludeTapFiles;
    }

    protected override void OnValueChanged(bool value)
    {
        Installer.Configuration.IncludeTapFiles = value;
        Installer.Configuration.Save();
    }

}