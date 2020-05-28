using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using SFB;

[RequireComponent(typeof(Slider))]
public class SliderTotalProgress : MonoBehaviour
{
    public Installer Installer = null;

    private Slider _slider = null;

    void Start()
    {
        _slider = GetComponent<Slider>();
    }

    private void Update()
    {
        if(Installer.Configuration.GamesRootPath != null && Installer.Configuration.GamesRootPath.Length > 0)
        {
            int totalObjectsProcessed = Installer.TotalObjects - Installer.TotalObjectsRemaining;
            if(Installer.TotalObjects == 0)
            {
                _slider.value = 0;
            }
            else
            {
                _slider.value = (float)totalObjectsProcessed / Installer.TotalObjects;
            }
        }
    }

}