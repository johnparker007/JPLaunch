using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using SFB;

[RequireComponent(typeof(Button))]
public class ButtonOK : MonoBehaviour, IPointerDownHandler
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
        _button.interactable = Installer.MasterState == Installer.MasterStateType.CompletedSuccessfully;
    }

    private void OnClick()
    {
        MenuController.Instance.SetMenu(MenuController.Instance.MenuMain);
    }
    
}