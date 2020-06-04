using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using SFB;
using System.IO;

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

    private void OnClick()
    {
        string targetDirectory = "";
        if(Installer.Configuration.GamesRootPath != null && Installer.Configuration.GamesRootPath.Length > 0)
        {
            targetDirectory = Installer.Configuration.GamesRootPath;
        }

        string[] paths = StandaloneFileBrowser.OpenFolderPanel("Select Games Root Folder", targetDirectory, false);
        if (paths.Length > 0)
        {
            Installer.Configuration.GamesRootPath = paths[0];
            Installer.Configuration.Save();
        }
    }

}