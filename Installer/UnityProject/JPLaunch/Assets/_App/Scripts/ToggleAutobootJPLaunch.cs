using UnityEngine;
using UnityEngine.UI;

public class ToggleAutobootJPLaunch: ToggleBase
{
    protected void Start()
    {
        _toggle.isOn = Installer.Configuration.AutobootFPLaunch;
    }

    protected override void OnValueChanged(bool value)
    {
        Installer.Configuration.AutobootFPLaunch = value;
        Installer.Configuration.Save();
    }

}