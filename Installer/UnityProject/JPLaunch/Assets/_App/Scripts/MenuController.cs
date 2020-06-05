using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MenuController : MonoBehaviour 
{
	public GameObject MenuMain = null;
	public GameObject MenuInstalling = null;

	public static MenuController Instance
    {
		get;
		private set;
    }

	private GameObject _currentMenu = null;

	private void Awake()
    {
		Instance = this;

		MenuMain.SetActive(false);
		MenuInstalling.SetActive(false);
	}

	public void SetMenu(GameObject menu)
    {
		if(_currentMenu != null)
        {
			_currentMenu.SetActive(false);
        }

		_currentMenu = menu;
		_currentMenu.SetActive(true);
    }
}
