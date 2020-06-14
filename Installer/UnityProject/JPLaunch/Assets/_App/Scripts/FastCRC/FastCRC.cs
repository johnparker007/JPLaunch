using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Security.Cryptography;
using Boo.Lang;
using Soft160.Data.Cryptography;
using UnityEngine;


public class FastCRC : CRCServiceProvider
{
	public class Database
    {
		private const int kInitialDictionaryCapacity = 200000;

		public Dictionary<string, int> CRCData;

		private Installer _installer = null;
		private string _databasePath = null;

		public Database(Installer installer)
        {
			_installer = installer;
			_databasePath = _installer.OutputFolder + "/crc_db";

			if (!Load())
            {
				CRCData = new Dictionary<string, int>(kInitialDictionaryCapacity);
			}
		}

		public bool Load()
		{
			try
			{
				byte[] fileBytes = File.ReadAllBytes(_databasePath);
				if(fileBytes != null)
                {
					MemoryStream memoryStream = new MemoryStream();
					BinaryFormatter binaryFormatter = new BinaryFormatter();

					memoryStream.Write(fileBytes, 0, fileBytes.Length);
					memoryStream.Position = 0;

					CRCData = binaryFormatter.Deserialize(memoryStream) as Dictionary<string, int>;

					return true;
				}
			}
			catch (Exception exception)
			{
				// failed, will fall thru and return false;
			}

			return false;
		}

		public void Save()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryFormatter binaryFormatter = new BinaryFormatter();

			binaryFormatter.Serialize(memoryStream, CRCData);

			byte[] crcDataAsByteArray = memoryStream.ToArray();

			try
			{
				File.WriteAllBytes(_databasePath, crcDataAsByteArray);
			}
			catch (Exception exception)
			{
				Debug.LogError("Exception reading file bytes: " + exception);
			}
		}
	}

	public static FastCRC Instance
	{
		get
        {
			if(_instance == null)
            {
				_instance = new FastCRC();
            }

			return _instance;
        }
	}

	private static FastCRC _instance = null;

	private Database _database = null;
	private Installer _installer = null;


	public void Setup(Installer installer)
    {
		_installer = installer;

		_database = new Database(_installer);
	}

	// returns true if filepath already in dictionary with correct hash
	public bool AddOrUpdateFile(string filePath, byte[] fileData)
    {
		Initialize();
		int hashInt = BitConverter.ToInt32(ComputeHash(fileData), 0);

		int foundCRCValue;
		bool foundFilePath = _database.CRCData.TryGetValue(filePath, out foundCRCValue);

		if(foundFilePath && foundCRCValue == hashInt)
        {
			return true;
		}
		else
        {
			if(_database.CRCData.ContainsKey(filePath))
            {
				_database.CRCData[filePath] = hashInt;
			}
			else
            {
				_database.CRCData.Add(filePath, hashInt);
			}
			return false;
		}
	}

	public bool IsFilePathInDatabase(string filePath)
    {
		int foundCRCValue;
		bool foundFilePath = _database.CRCData.TryGetValue(filePath, out foundCRCValue);

		return foundFilePath;
	}

	public void SaveDatabase()
    {
		_database.Save();
    }

}
