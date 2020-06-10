using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class SDFileTaskPool 
{
    private List<SDFileTask> _pool = new List<SDFileTask>();

    public SDFileTaskPool()
    {

    }

    public SDFileTask GetNextFreeSDFileTask()
    {
        SDFileTask sdFileTask = _pool.Find(x => !x.InUse);
        if (sdFileTask != null)
        {
            sdFileTask.InUse = true;
        }
        else
        {
            sdFileTask = new SDFileTask();
            sdFileTask.InUse = true;
            _pool.Add(sdFileTask);

            Debug.Log("pool length: " + _pool.Count());
        }

        return sdFileTask;
    }

}
