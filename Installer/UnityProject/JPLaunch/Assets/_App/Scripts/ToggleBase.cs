using UnityEngine;
using UnityEngine.UI;

[RequireComponent(typeof(Toggle))]
public abstract class ToggleBase: MonoBehaviour
{
    public Installer Installer = null;

    protected Toggle _toggle = null;

    private void Awake()
    {
        _toggle = GetComponent<Toggle>();
        _toggle.onValueChanged.AddListener(OnValueChanged);
    }

    protected abstract void OnValueChanged(bool value);

}