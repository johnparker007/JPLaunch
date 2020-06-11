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
public class ButtonSelectESXDOSRootFolder : MonoBehaviour, IPointerDownHandler
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
        if(Installer.Configuration.ESXDOSRootPath != null 
            && Installer.Configuration.ESXDOSRootPath.Length > 0
            && Directory.Exists(Installer.Configuration.ESXDOSRootPath))
        {
            targetDirectory = Installer.Configuration.ESXDOSRootPath;
        }

        string[] paths = StandaloneFileBrowser.OpenFolderPanel("Select ESXDOS Root Folder", targetDirectory, false);
        if (paths.Length > 0)
        {
            Installer.Configuration.ESXDOSRootPath = paths[0];
            Installer.Configuration.Save();
        }
    }

}