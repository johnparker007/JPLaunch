using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using SFB;

[RequireComponent(typeof(Text))]
public class TextGamesRootFolder : MonoBehaviour
{
    public Installer Installer = null;

    private Text _text = null;

    void Start()
    {
        _text = GetComponent<Text>();
    }

    private void Update()
    {
        if(Installer.Configuration.GamesRootPath != null && Installer.Configuration.GamesRootPath.Length > 0)
        {
            _text.text = Installer.Configuration.GamesRootPath;
        }
    }

}