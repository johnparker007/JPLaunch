using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using SFB;

[RequireComponent(typeof(Button))]
public class ButtonSelectGamesrootFolder : MonoBehaviour, IPointerDownHandler
{
    public Installer Installer = null;

    public void OnPointerDown(PointerEventData eventData) { }

    private void Awake()
    {
        Button button = GetComponent<Button>();
        button.onClick.AddListener(OnClick);
    }

    void Start()
    {

    }

    private void OnClick()
    {
        var paths = StandaloneFileBrowser.OpenFolderPanel("Select Games Root Folder", "", false);
        if (paths.Length > 0)
        {
            Installer.Configuration.GamesRootPath = paths[0];
            Installer.Configuration.Save();
        }
    }

}