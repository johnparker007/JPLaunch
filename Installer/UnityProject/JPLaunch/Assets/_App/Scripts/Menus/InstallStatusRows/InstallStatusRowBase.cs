using System.Collections;
using System.Collections.Generic;
using System.Text;
using UnityEngine;
using UnityEngine.UI;

public abstract class InstallStatusRowBase : MonoBehaviour
{
	public Installer Installer = null;

	public Text StatusString = null;
	public Image CompletedTickImage = null;

	protected abstract string RowText
    {
		get;
    }

	protected abstract int Total
    {
		get;
    }

	protected abstract int Remaining
	{
		get;
	}

	protected float Progress
    {
		get
		{
			if (Installer.InstallInstance == null || Total == 0)
			{
				return 0f;
			}

			return 1f - ((float)Remaining / Total);
		}
	}

	protected int ProgressPercent
    {
		get
        {
			return Mathf.RoundToInt(Progress * 100f);
        }
    }

	protected bool Started
    {
		get
        {
			return Progress > 0f;
		}
	}

	protected bool Completed
	{
		get
		{
			return Progress == 1f;
		}
	}

	protected bool InProgress
    {
        get
        {
			return Started && !Completed;
        }
    }

	protected void OnEnable()
    {
		StatusString.text = "";
		CompletedTickImage.gameObject.SetActive(false);
	}

	protected void Update() 
	{
		UpdateStatusString();
		UpdateStatusFontStyle();
		UpdateStatusIcon();
	}

	private void UpdateStatusString()
    {
		StringBuilder stringBuilder = new StringBuilder();
		stringBuilder.Append(RowText);
		if(InProgress)
		{
			stringBuilder.Append(" (" + ProgressPercent + "%)");
        }

		StatusString.text = stringBuilder.ToString();
	}

	private void UpdateStatusFontStyle()
	{
		if(InProgress)
        {
			StatusString.fontStyle = FontStyle.Bold;
		}
		else
        {
			StatusString.fontStyle = FontStyle.Normal;
		}
	}

	private void UpdateStatusIcon()
	{
		CompletedTickImage.gameObject.SetActive(Completed);
	}
}
