using UnityEngine;
using UnityEngine.UI;

public class ToggleIncludeZ80Files: ToggleBase
{
    protected void Start()
    {
        _toggle.isOn = Installer.Configuration.IncludeZ80Files;
    }

    protected override void OnValueChanged(bool value)
    {
        Installer.Configuration.IncludeZ80Files = value;
        Installer.Configuration.Save();
    }

}