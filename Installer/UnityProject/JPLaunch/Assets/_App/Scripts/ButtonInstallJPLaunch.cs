using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using SFB;

[RequireComponent(typeof(Button))]
public class ButtonInstallJPLaunch : MonoBehaviour, IPointerDownHandler
{
    public Installer Installer = null;

    private Button _button = null;

    public void OnPointerDown(PointerEventData eventData) { }

    void Start()
    {
        _button = GetComponent<Button>();
        _button.onClick.AddListener(OnClick);
    }

    private void Update()
    {
        _button.interactable = Installer.Configuration.GamesRootPath != null;
    }

    private void OnClick()
    {
        Installer.Install();
    }
    
}