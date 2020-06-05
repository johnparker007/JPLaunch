﻿using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using UnityEngine;
using UnityEngine.UI;

public class Install : MonoBehaviour 
{
    public const int kSpectrumCharacterColumnPageCountHighByte = 31;
    public const int kSpectrumPixelRowPageCountHighByte = 0;
    public const int kSpectrumCharacterColumnPageCountLowByte = 31;
    public const int kSpectrumPixelRowPageCountLowByte = 1;

    public const int kSpectrumCharacterColumnRowCount = 31;
    public const int kSpectrumPixelRowRowCount = 2;

    public const int kGamenameMaximumLength = 64;

    public const int kRowsPerPageFull = 23;
    public const int kRowsPerPageMini = 7;

    public const int kPlusThreeDOSFileDataStartOffset = 128;

    public const string kAssetsCompletePath = "C:/Users/John/Dropbox/ZX_Coding/projects/TapLauncher/assets";
    public const string kAppCodeBinaryFilename = "app_CODE.bin";
    public const string kAppNirvanaBinaryFilename = "app_NIRVANAP.bin";
    public const string kAppLd16384RecompiledBinaryFilename = "ld16384_recompiled";

    public const string kSearchWindowFilename = "SearchWindow.scr";

    public const string kDotCommandsFolder = "BIN";

    public const string kLibraryFolder = "library";
    public const string kCodeFolder = "code";
    public const string kGraphicsFolder = "graphics";

    public const string kFilesFolder = "files";
    public const string kDatabaseFolder = "database";

    public const string kGameListFullFolder = "gamefull";
    public const string kGameListMiniFolder = "gamemini";

    public const string kSearchListFullFolder = "srchfull";
    public const string kSearchListMiniFolder = "srchmini";

    public const string kFullLoadingScreenScrFolder = "load_scr";
    public const string kPartialLoadingScreenScrFolder = "part_scr";

    // REMEMBER: keep in same order as sprite sheet, so clearer to cross-reference with ASCII table
    public const string kUDGSpectrumRainbowStripeString = "&";
    public const string kUDGSnaIconString = "'";
    public const string kUDGZ80IconString = "(";
    public const string kUDGTapIconString = ")";
    public const string kUDGScrollbarOuterTop = "*";
    public const string kUDGScrollbarOuterBottom = "+";
    public const string kUDGScrollbarOuterMiddle = ",";
    public const string kUDGScrollbarInnerTop = "-";
    public const string kUDGScrollbarInnerMiddle = ".";
    public const string kUDGScrollbarInnerBottom = "/";


    public const int kSpectrumScreenWidth = 256;
    public const int kSpectrumScreenHeight = 192;

    public const int kSpectrumCharSize = 8;

    public const int kScreenAddressPageCount = 31;

    public const int kBitsPerByte = 8;

    public Texture2D FontTexture2D = null;
    public Texture2D UDGFontTexture2D = null;
    public Texture2D SpectrumScreenTexture2D = null;

    private Installer _installer = null;

    private int[] _characterWidths =
    {
        2, // 32 (space)
        2, // 33 !
        4, // 34 "
        6, // 35 #
        4, // 36 $
        4, // 37 %
        5, // 38 &
        3, // 39 '
        3, // 40 (
        3, // 41 )
        6, // 42 *
        6, // 43 +
        3, // 44 ,
        5, // 45 -
        2, // 46 .
        4, // 47 /
        5, // 48 0
        3, // 49 1
        5, // 50 2
        5, // 51 3
        5, // 52 4
        5, // 53 5
        5, // 54 6
        5, // 55 7
        5, // 56 8
        5, // 57 9
        2, // 58 :
        3, // 59 ;
        4, // 60 <
        4, // 61 =
        4, // 62 >
        4, // 63 ?
        5, // 64 @
        5, // 65 A
        5, // 66 B
        5, // 67 C
        5, // 68 D
        4, // 69 E
        4, // 70 F
        5, // 71 G
        5, // 72 H
        2, // 73 I
        5, // 74 J
        5, // 75 K
        4, // 76 L
        6, // 77 M
        5, // 78 N
        5, // 79 O
        5, // 80 P
        5, // 81 Q
        5, // 82 R
        5, // 83 S
        6, // 84 T
        5, // 85 U
        6, // 86 V
        6, // 87 W
        6, // 88 X
        6, // 89 Y
        5, // 90 Z
        3, // 91 [
        4, // 92 \
        3, // 93 ]
        4, // 94 ^
        5, // 95 _
        5, // 96 £ --------------- here
        4, // 97 a
        4, // 98 b
        4, // 99 c
        4, // 100 d
        4, // 101 e
        3, // 102 f
        4, // 103 g
        4, // 104 h
        2, // 105 i
        3, // 106 j
        4, // 107 k
        3, // 108 l
        6, // 109 m
        4, // 110 n
        4, // 111 o
        4, // 112 p
        4, // 113 q
        4, // 114 r
        4, // 115 s
        3, // 116 t
        4, // 117 u
        4, // 118 v
        6, // 119 w
        4, // 120 x
        4, // 121 y
        4, // 122 z
        4, // 123 {
        2, // 124 |
        4, // 125 }
        5, // 126 ~
        5, // 127 (c)
    };

    private int[] _characterXPositions;


    public int SearchStringsTotal
    {
        get;
        private set;
    }

    public int GameListPagesTotal
    {
        get;
        private set;
    }

    public int SearchStringsRemaining
    {
        get;
        private set;
    }

    public int GameListPagesRemaining
    {
        get;
        private set;
    }

    public int TotalObjects
    {
        get
        {
            return SearchStringsTotal + GameListPagesTotal;
        }
    }

    public int TotalObjectsRemaining
    {
        get
        {
            return SearchStringsRemaining + GameListPagesRemaining;
        }
    }


    private List<String> _allFilenames = null;
    private List<String> _allFilenamesWithoutPathOrExtension = null;
    private List<String> _allFilenamesWithoutPathOrExtensionUppercase = null;



    private byte[] _database = null;

    private SearchGenerator _searchGenerator = new SearchGenerator();

    private Font _font = new Font();
    private LoadingScreenExtractor _loadingScreenExtractor = new LoadingScreenExtractor();


    private Color[] _blankScreen = null;
    byte[] _screenMemory = new byte[kSpectrumScreenWidth * kSpectrumScreenHeight / 8];

    private List<int> _fileIndices = new List<int>();

    private long _nextYieldtime = 0L;

    private bool _coroutineTaskRunning = false;

    private List<String[]> _splitStrings = new List<string[]>();



    private void GenerateCharacterXPositions()
    {
        _characterXPositions = new int[_characterWidths.Length];

        int currentXPosition = 0;
        for (int characterIndex = 0; characterIndex < _characterWidths.Length; ++characterIndex)
        {
            _characterXPositions[characterIndex] = currentXPosition;
            currentXPosition += _characterWidths[characterIndex];
        }
    }

    private void GenerateBlankScreenColorArray()
    {
        _blankScreen = new Color[SpectrumScreenTexture2D.width * SpectrumScreenTexture2D.height];
        for (int blankScreenPixelIndex = 0; blankScreenPixelIndex < _blankScreen.Length; ++blankScreenPixelIndex)
        {
            _blankScreen[blankScreenPixelIndex] = Color.white;
        }
    }

    public void StartInstall(Installer installer)
    {
        _installer = installer;

        Initialise();

        StartCoroutine(InstallCoroutine());
    }

    private void Initialise()
    {
        GenerateCharacterXPositions();
        GenerateBlankScreenColorArray();
    }

    public IEnumerator InstallCoroutine()
    {
        _installer.MasterState = Installer.MasterStateType.Running;

        yield return null; // initial yield to let GUI catch up

        while (!DeleteOutputFolderIfPresent())
        {
            Debug.LogWarning("Failed to delete output folder... retrying in 1 second");

            yield return new WaitForSeconds(1f);
        }

        Debug.Log("Deleted output folder successfully");

        // let deletes catch up
        yield return new WaitForSeconds(1f);

        InitialiseOutputFolder();

        _installer.SpectrumFiles.WriteFiles();

        _allFilenames = GetAllFilenames(_installer.Configuration.GamesRootPath);

        _allFilenamesWithoutPathOrExtension = GetAllFilenamesWithoutPathOrExtension();
        _allFilenamesWithoutPathOrExtensionUppercase = _allFilenamesWithoutPathOrExtension.ConvertAll(x => x.ToUpper());

        CreateDatabase(); // TOIMPROVE may not want to use this later

        _searchGenerator.Initialise(_allFilenamesWithoutPathOrExtensionUppercase);



        char[] separators = { ' ', ',', '(', ')', '{', '}', '[', ']' }; // TODO add more, don't know what kind of filenames other people will have, ? £ $ etc
        for (int stringIndex = 0; stringIndex < _allFilenamesWithoutPathOrExtension.Count; ++stringIndex)
        {
            _splitStrings.Add(_allFilenamesWithoutPathOrExtensionUppercase[stringIndex].Split(separators));
        }

        //GenerateDatabasePageFiles();
        GenerateNumberedGameFiles();
        GenerateNumberedLoadingScreenFiles();

        GenerateSystemMenus();

        Debug.Log("GenerateGameListPages (full)...");
        StartCoroutine(GenerateGameListPages(kRowsPerPageFull));
        while (_coroutineTaskRunning)
        {
            yield return null;
        }

        Debug.Log("GenerateGameListPages (mini)...");
        StartCoroutine(GenerateGameListPages(kRowsPerPageMini));
        while (_coroutineTaskRunning)
        {
            yield return null;
        }

        Debug.Log("GenerateSearchResultPages (full)...");
        StartCoroutine(GenerateSearchResultPages(_searchGenerator.UniqueWordsFiltered, kRowsPerPageFull));
        while (_coroutineTaskRunning)
        {
            yield return null;
        }

        Debug.Log("GenerateSearchResultPages (mini)...");
        StartCoroutine(GenerateSearchResultPages(_searchGenerator.UniqueWordsFiltered, kRowsPerPageMini));
        while (_coroutineTaskRunning)
        {
            yield return null;
        }

        _installer.MasterState = Installer.MasterStateType.CompletedSuccessfully; // TODO this isn't necessarily true!
        MenuController.Instance.SetMenu(MenuController.Instance.MenuMain);
    }

    private bool DeleteOutputFolderIfPresent()
    {
        if (Directory.Exists(Installer.kOutputFolder))
        {
            DeleteDirectory(Installer.kOutputFolder);
        }

        return !Directory.Exists(Installer.kOutputFolder);
    }

    private void InitialiseOutputFolder()
    {
        Directory.CreateDirectory(Installer.kOutputFolder);

        Directory.CreateDirectory(Installer.kOutputFolder + "/" + kCodeFolder);
        Directory.CreateDirectory(Installer.kOutputFolder + "/" + kGraphicsFolder);

        Directory.CreateDirectory(Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kDatabaseFolder);
        Directory.CreateDirectory(Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kGameListFullFolder);
        Directory.CreateDirectory(Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kGameListMiniFolder);
        Directory.CreateDirectory(Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kSearchListFullFolder);
        Directory.CreateDirectory(Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kSearchListMiniFolder);
        Directory.CreateDirectory(Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kFilesFolder);
        Directory.CreateDirectory(Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kFullLoadingScreenScrFolder);
        Directory.CreateDirectory(Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kPartialLoadingScreenScrFolder);
    }

    /// <summary>
    /// Depth-first recursive delete, with handling for descendant 
    /// directories open in Windows Explorer.
    /// </summary>
    public static void DeleteDirectory(string path)
    {
        foreach (string directory in Directory.GetDirectories(path))
        {
            DeleteDirectory(directory);
        }

        try
        {
            Directory.Delete(path, true);
        }
        catch (Exception)
        {
            Debug.LogWarning("Exception attempting to delete: " + path + "... retrying shortly");
            // do nothing, but this should catch all exceptions
        }

        //catch (IOException)
        //{
        //    Directory.Delete(path, true);
        //}
        //catch (UnauthorizedAccessException)
        //{
        //    Directory.Delete(path, true);
        //}
    }


    private void CreateDatabase()
    {
        _database = new byte[_allFilenames.Count * kGamenameMaximumLength];

        for (int index = 0; index < _allFilenames.Count; ++index)
        {
            byte[] gamenameASCII = Encoding.ASCII.GetBytes(GetFilenameWithoutPathOrExtension(index));

            for (int characterIndex = 0; characterIndex < kGamenameMaximumLength; ++characterIndex)
            {
                byte writeByte;
                if (characterIndex == kGamenameMaximumLength - 1)
                {
                    writeByte = 0; // force final char to be zero for the proportional font routine that expects a null terminate string
                }
                else if (gamenameASCII.Length > characterIndex)
                {
                    writeByte = gamenameASCII[characterIndex];
                }
                else
                {
                    writeByte = 0;
                }
                _database[(index * kGamenameMaximumLength) + characterIndex] = writeByte;
            }
        }
    }

    //private void GenerateDatabasePageFiles(int rowsPerPage)
    //{
    //    //byte[] sourcePlusThreeDatabasePageFileBytes = File.ReadAllBytes("Assets\\_App\\SpectrumFiles\\32x23DatabasePage44000");
    //    byte[] sourcePlusThreeDatabasePageFileBytes = File.ReadAllBytes("Assets\\_App\\SpectrumFiles\\64x23DatabasePage44000");

    //    byte[] plusThreeDatabasePageBuffer = new byte[sourcePlusThreeDatabasePageFileBytes.Length];

    //    Buffer.BlockCopy(sourcePlusThreeDatabasePageFileBytes, 0, plusThreeDatabasePageBuffer, 0, sourcePlusThreeDatabasePageFileBytes.Length);

    //    int pageCount = _allFilenames.Count / rowsPerPage; // TODO this is one more, will need to handle part pages to implement
    //    for(int pageIndex = 0; pageIndex < pageCount; ++pageIndex)
    //    {
    //        int sourceOffset = pageIndex * rowsPerPage * kGamenameMaximumLength;
    //        int destinationOffset = kPlusThreeDOSFileDataStartOffset;

    //        Buffer.BlockCopy(_database, sourceOffset, plusThreeDatabasePageBuffer, destinationOffset, rowsPerPage * kGamenameMaximumLength);

    //        string filename = kOutputFolder + "/" + kLibraryFolder + "/" + kDatabaseFolder + "/" + String.Format("{0:000000}", pageIndex);
    //        File.WriteAllBytes(filename, plusThreeDatabasePageBuffer);
    //    }

    //}

    private void GenerateSystemMenus()
    {
        GenerateSystemMenuExit();
        GenerateSystemMenuConfiguration();
    }

    private void GenerateSystemMenuExit()
    {
        SpectrumScreenTexture2D.SetPixels(_blankScreen);

        FontDrawCharacters("Exit", 1, 0);
        FontDrawRainbowStripesUDGs();

        FontDrawCharactersCentred("Run NMI.SYS", 3 * kSpectrumCharSize);
        FontDrawCharactersCentred("Reset to BASIC", 5 * kSpectrumCharSize);
        FontDrawCharactersCentred("Back", 7 * kSpectrumCharSize);

        SpectrumScreenTexture2D.Apply(false);

        byte[] screenMemory = GetByteArrayFromScreenTexture();

        string filename =
            Installer.kOutputFolder + "/"
            + kGraphicsFolder + "/"
            + "exit";

        SDFile.WriteAllBytes(filename, screenMemory);
    }

    private void GenerateSystemMenuConfiguration()
    {
        SpectrumScreenTexture2D.SetPixels(_blankScreen);

        FontDrawCharacters("Configuration", 1, 0);
        FontDrawRainbowStripesUDGs();

        FontDrawCharactersRightAligned("Default view mode:", kSpectrumScreenWidth / 2, 3 * kSpectrumCharSize);
        FontDrawCharactersRightAligned("NMI.SYS startup path:", kSpectrumScreenWidth / 2, 5 * kSpectrumCharSize);
        FontDrawCharactersRightAligned("Input acceleration:", kSpectrumScreenWidth / 2, 7 * kSpectrumCharSize);
        FontDrawCharactersRightAligned("Keyboard type:", kSpectrumScreenWidth / 2, 9 * kSpectrumCharSize);
        FontDrawCharactersRightAligned("Joystick type:", kSpectrumScreenWidth / 2, 11 * kSpectrumCharSize);

        FontDrawCharactersCentred("Back", 13 * kSpectrumCharSize);

        byte[] screenMemory = GetByteArrayFromScreenTexture();

        string filename =
            Installer.kOutputFolder + "/"
            + kGraphicsFolder + "/"
            + "config";

        SDFile.WriteAllBytes(filename, screenMemory);
    }

    private IEnumerator GenerateGameListPages(int rowsPerPage)
    {
        _coroutineTaskRunning = true;

        for (int fileIndex = 0; fileIndex < _allFilenames.Count; ++fileIndex)
        {
            _fileIndices.Add(fileIndex);
        }

        //        int pageCount = _allFilenames.Count / rowsPerPage; // TODO this is one more, will need to handle part pages to implement
        int pageCount = GetPageCountIncludingAnyPartialEndPage(_allFilenames.Count, rowsPerPage);
        GameListPagesTotal = pageCount;
        for (int pageIndex = 0; pageIndex < pageCount; ++pageIndex)
        {
            GameListPagesRemaining = pageCount - pageIndex;
            if (System.DateTime.Now.Ticks > _nextYieldtime)
            {
                const long kTicksPerSecond = 10000000;
                _nextYieldtime = System.DateTime.Now.Ticks + kTicksPerSecond;
                yield return null;
            }

            GenerateDatabaseScreenFile(pageIndex, rowsPerPage);
        }

        _coroutineTaskRunning = false;
    }

    private void GenerateDatabaseScreenFile(int pageIndex, int rowsPerPage)
    {
        SpectrumScreenTexture2D.SetPixels(_blankScreen);

        //int pageCount = _allFilenames.Count / rowsPerPage; // TODO this will usually be 1 more (except if 23 rows on final page, make a GetDatabasePageCount function)
        int pageCount = GetPageCountIncludingAnyPartialEndPage(_allFilenames.Count, rowsPerPage);
        FontDrawCharacters("All titles (page " + (pageIndex + 1) + "/" + pageCount + ")", 1, 0);
        FontDrawRainbowStripesUDGs();

        int thisPageRowCount = GetPageRowCount(_allFilenames.Count, pageIndex, rowsPerPage);
        byte[] gameNameBytes = new byte[kGamenameMaximumLength];
        for (int rowIndex = 0; rowIndex < thisPageRowCount; ++rowIndex)
        {
            Array.Copy(_database, (pageIndex * kGamenameMaximumLength * rowsPerPage) + (rowIndex * kGamenameMaximumLength), gameNameBytes, 0, kGamenameMaximumLength);

            string gameNameString = Encoding.ASCII.GetString(gameNameBytes); //.Trim();

            FontDrawCharacters(gameNameString, 8 + 3, kSpectrumCharSize + (rowIndex * kSpectrumCharSize));

            string filename = _allFilenames[(pageIndex * rowsPerPage) + rowIndex];
            Installer.FileFormat fileFormat = FileFormatHelpers.GetFileFormat(filename);
            FontDrawUDGCharacter(fileFormat.UDGIconString(), 0 * kSpectrumCharSize, kSpectrumCharSize + (rowIndex * kSpectrumCharSize));

            WriteFileFormatToScreenTexture(fileFormat, rowIndex);
        }

        DrawScrollBarToTexture(pageIndex, pageCount, rowsPerPage);

        WritePageAndRowCountToScreenTexture(pageCount, thisPageRowCount); // TODO rowCount for final page
        WriteIndicesToScreenTexture(_fileIndices, pageIndex * rowsPerPage, rowsPerPage);

        SpectrumScreenTexture2D.Apply(false);

        SaveScreenTextureAsSpectrumScreenData(pageIndex, rowsPerPage);
    }

    private void SaveScreenTextureAsSpectrumScreenData(int pageIndex, int rowsPerPage)
    {
        //byte[] screenMemory = GetByteArrayFromScreenTexture();

        //string filename = kOutputFolder + "/" + kLibraryFolder + "/" + kPageScrFolder + "/" + String.Format("{0:000000}", pageIndex) + ".SCR";
        //File.WriteAllBytes(filename, screenMemory);

        //**************************************************************************************
        String pageNumberString = String.Format("{0:000000}", pageIndex);

        String pageFolder;
        if (rowsPerPage == kRowsPerPageFull)
        {
            pageFolder = kGameListFullFolder;
        }
        else
        {
            pageFolder = kGameListMiniFolder;
        }

        String rootFolder = Installer.kOutputFolder + "/" + kLibraryFolder + "/" + pageFolder + "/";
        String flattenedFilePath = SDFile.CreateFlattenedFilepath(rootFolder, pageNumberString);

        byte[] screenMemory = GetByteArrayFromScreenTexture();

        string filename =
            Installer.kOutputFolder + "/"
            + kLibraryFolder + "/"
            + pageFolder + "/"
            + flattenedFilePath
            + pageNumberString.Substring(pageNumberString.Length - 1)
            + ".scr";

        SDFile.WriteAllBytes(filename, screenMemory);
    }

    private byte[] GetByteArrayFromScreenTexture()
    {
        for (int spectrumScreenTextureY = 0; spectrumScreenTextureY < kSpectrumScreenHeight; ++spectrumScreenTextureY)
        {
            for (int spectrumScreenTextureX = 0; spectrumScreenTextureX < kSpectrumScreenWidth; /* don't need to increment spectrumScreenTextureX */ )
            {
                byte screenByte = 0;

                for (int bitNumber = 0; bitNumber < 8; ++bitNumber)
                {
                    if (GetBitFromSpectrumScreenTexture(spectrumScreenTextureX, spectrumScreenTextureY) == 1)
                    {
                        screenByte |= (byte)(1 << (7 - bitNumber));
                    }
                    ++spectrumScreenTextureX;
                }

                // deal with Y (from this BASIC example: https://oldmachinery.blogspot.com/2014/04/zx-sprites.html)
                int block = (int)(spectrumScreenTextureY / 64);
                int characterRow = (int)(spectrumScreenTextureY / 8);
                int yr = spectrumScreenTextureY - (characterRow * 8);
                characterRow = characterRow - (block * 8);
                int address = /* 16384+ */ block * 2048 + characterRow * 32 + yr * 256;

                // increase by x as bytes
                address += (spectrumScreenTextureX - 1) / 8;

                _screenMemory[address] = screenByte;
            }
        }

        return _screenMemory;
    }

    private int GetBitFromSpectrumScreenTexture(int x, int y)
    {
        Color pixelColor = SpectrumScreenTexture2D.GetPixel(x, kSpectrumScreenHeight - y - 1);

        return pixelColor == Color.black ? 1 : 0;
    }

    private void GenerateNumberedGameFiles()
    {
        for (int fileIndex = 0; fileIndex < _allFilenames.Count; ++fileIndex)
        {
            try
            {
                Installer.FileFormat fileFormat = FileFormatHelpers.GetFileFormat(GetFilenameWithPath(fileIndex));

                String fileIndexAsPaddedString = String.Format("{0:000000}", fileIndex);

                String rootFolder = Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kFilesFolder + "/";
                String flattenedFilePath = SDFile.CreateFlattenedFilepath(rootFolder, fileIndexAsPaddedString);

                String flattenedFilenameAndPath = Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kFilesFolder + "/" + flattenedFilePath + fileIndexAsPaddedString.Substring(fileIndexAsPaddedString.Length - 1) + "." + fileFormat.ToString();

                File.Copy(GetFilenameWithPath(fileIndex), flattenedFilenameAndPath);
            }
            catch (Exception exception)
            {
                Debug.LogError("Exception "
                    + exception.ToString()
                    + " while trying to generate a numbered game file from: "
                    + GetFilenameWithPath(fileIndex));
            }
        }
    }

    private void GenerateNumberedLoadingScreenFiles()
    {
        byte[] partialScreenBytes = new byte[2048 + 2048 + 768];
        for (int attributeByteIndex = 0; attributeByteIndex < 256; ++attributeByteIndex)
        {
            if (attributeByteIndex < 19)
            {
                partialScreenBytes[2048 + 2048 + attributeByteIndex] = (byte)(ZXConstants.PAPER_BLUE | ZXConstants.INK_WHITE | ZXConstants.BRIGHT);
            }
            else if (attributeByteIndex < 32)
            {
                partialScreenBytes[2048 + 2048 + attributeByteIndex] = (byte)(ZXConstants.PAPER_BLUE | ZXConstants.INK_BLUE | ZXConstants.BRIGHT);
            }
            else
            {
                partialScreenBytes[2048 + 2048 + attributeByteIndex] = (byte)(ZXConstants.PAPER_BLACK | ZXConstants.INK_RED | ZXConstants.BRIGHT);
            }
        }

        partialScreenBytes[2048 + 2048 + 26] = (byte)(ZXConstants.PAPER_BLUE | ZXConstants.INK_RED | ZXConstants.BRIGHT);
        partialScreenBytes[2048 + 2048 + 27] = (byte)(ZXConstants.PAPER_RED | ZXConstants.INK_YELLOW | ZXConstants.BRIGHT);
        partialScreenBytes[2048 + 2048 + 28] = (byte)(ZXConstants.PAPER_YELLOW | ZXConstants.INK_GREEN | ZXConstants.BRIGHT);
        partialScreenBytes[2048 + 2048 + 29] = (byte)(ZXConstants.PAPER_GREEN | ZXConstants.INK_CYAN | ZXConstants.BRIGHT);
        partialScreenBytes[2048 + 2048 + 30] = (byte)(ZXConstants.PAPER_CYAN | ZXConstants.INK_BLUE | ZXConstants.BRIGHT);


        for (int fileIndex = 0; fileIndex < _allFilenames.Count; ++fileIndex)
        {
            try
            {
                byte[] fileBytes = File.ReadAllBytes(GetFilenameWithPath(fileIndex));

                Installer.FileFormat fileFormat = FileFormatHelpers.GetFileFormat(GetFilenameWithPath(fileIndex));
                byte[] screenBytes = _loadingScreenExtractor.Extract(fileBytes, fileFormat, GetFilenameWithPath(fileIndex));

                String fileIndexAsPaddedString = String.Format("{0:000000}", fileIndex);

                String rootFolderFull = Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kFullLoadingScreenScrFolder + "/";
                String flattenedFilePathFull = SDFile.CreateFlattenedFilepath(rootFolderFull, fileIndexAsPaddedString);

                String rootFolderPartial = Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kPartialLoadingScreenScrFolder + "/";
                String flattenedFilePathPartial = SDFile.CreateFlattenedFilepath(rootFolderPartial, fileIndexAsPaddedString);

                String flattenedFilenameAndPathFullScreen = Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kFullLoadingScreenScrFolder + "/" + flattenedFilePathFull + fileIndexAsPaddedString.Substring(fileIndexAsPaddedString.Length - 1) + ".scr";
                String flattenedFilenameAndPathPartialScreen = Installer.kOutputFolder + "/" + kLibraryFolder + "/" + kPartialLoadingScreenScrFolder + "/" + flattenedFilePathPartial + fileIndexAsPaddedString.Substring(fileIndexAsPaddedString.Length - 1) + ".scr";

                // write full screen
                FileStream outputFileStream = new FileStream(flattenedFilenameAndPathFullScreen, FileMode.Create, FileAccess.Write);
                outputFileStream.Write(screenBytes, 0, LoadingScreenExtractor.kLoadingScreenLength);
                outputFileStream.Close();

                // write partial screen
                Array.Copy(screenBytes, partialScreenBytes, 2048 + 2048);
                Array.Copy(screenBytes, 2048 + 2048 + 2048, partialScreenBytes, 2048 + 2048 + 256, 256 + 256);

                outputFileStream = new FileStream(flattenedFilenameAndPathPartialScreen, FileMode.Create, FileAccess.Write);
                outputFileStream.Write(partialScreenBytes, 0, LoadingScreenExtractor.kLoadingScreenLength - 2048);
                outputFileStream.Close();
            }
            catch (Exception exception)
            {
                Debug.LogError("Exception "
                    + exception.ToString()
                    + " while trying to generate a loading screen file from: "
                    + GetFilenameWithPath(fileIndex));
            }
        }
    }

    private List<String> GetAllFilenames(String directory)
    {
        var allFullPathAndFilenames = Directory.GetFiles(directory, "*.*", SearchOption.AllDirectories).
            Where(s =>
                (_installer.Configuration.IncludeTapFiles && s.EndsWith(".tap", StringComparison.OrdinalIgnoreCase))
                || (_installer.Configuration.IncludeSnaFiles && s.EndsWith(".sna", StringComparison.OrdinalIgnoreCase))
                || (_installer.Configuration.IncludeZ80Files && s.EndsWith(".z80", StringComparison.OrdinalIgnoreCase))
                );

        Array.Sort(allFullPathAndFilenames.ToArray(), StringComparer.Ordinal);
        return allFullPathAndFilenames.ToList();
    }

    private List<String> GetAllFilenamesWithoutPathOrExtension()
    {
        List<String> allFilenamesWithoutPathOrExtension = new List<String>();
        for (int filenameIndex = 0; filenameIndex < _allFilenames.Count; ++filenameIndex)
        {
            allFilenamesWithoutPathOrExtension.Add(GetFilenameWithoutPathOrExtension(filenameIndex));
        }

        return allFilenamesWithoutPathOrExtension;
    }

    private String GetFilenameWithPath(int index)
    {
        return _allFilenames[index];
    }

    private String GetFilenameWithoutPath(int index)
    {
        return Path.GetFileName(_allFilenames[index]);
    }

    private String GetFilenameWithoutPathOrExtension(int index)
    {
        return Path.GetFileNameWithoutExtension(_allFilenames[index]);
    }

    private void GenerateSearchStringScreenFiles(String searchTerm, List<int> searchResultIndices, int rowsPerPage)
    {
        int pageCount = SearchGetPageCount(searchResultIndices, rowsPerPage);
        byte[] gameNameBytes = new byte[kGamenameMaximumLength];
        for (int pageIndex = 0; pageIndex < pageCount; ++pageIndex)
        {
            SpectrumScreenTexture2D.SetPixels(_blankScreen);

            FontDrawCharacters("Search results for " + searchTerm, 1, 0);
            FontDrawRainbowStripesUDGs();

            int currentPageRowCount = SearchGetPageRowCount(searchResultIndices, pageIndex, rowsPerPage);
            int currentPageSearchResultIndicesStartIndex = pageIndex * rowsPerPage;
            for (int rowIndex = 0; rowIndex < currentPageRowCount; ++rowIndex)
            {
                Array.Copy(_database, searchResultIndices[currentPageSearchResultIndicesStartIndex + rowIndex] * kGamenameMaximumLength, gameNameBytes, 0, kGamenameMaximumLength);

                string gameNameString = Encoding.ASCII.GetString(gameNameBytes); //.Trim();

                FontDrawCharacters(gameNameString, 8 + 3, kSpectrumCharSize + (rowIndex * kSpectrumCharSize));

                string filename = _allFilenames[searchResultIndices[currentPageSearchResultIndicesStartIndex + rowIndex]];
                Installer.FileFormat fileFormat = FileFormatHelpers.GetFileFormat(filename);
                FontDrawUDGCharacter(fileFormat.UDGIconString(), 0 * kSpectrumCharSize, kSpectrumCharSize + (rowIndex * kSpectrumCharSize));

                WriteFileFormatToScreenTexture(fileFormat, rowIndex);
            }

            DrawScrollBarToTexture(pageIndex, pageCount, rowsPerPage);

            WritePageAndRowCountToScreenTexture(pageCount, currentPageRowCount);
            WriteIndicesToScreenTexture(searchResultIndices, currentPageSearchResultIndicesStartIndex, rowsPerPage);

            SpectrumScreenTexture2D.Apply(false);

            //SaveSearchPageDatFile(searchTerm, searchResultIndices);
            SaveScreenTextureAsSpectrumSearchScreenData(searchTerm, pageIndex, rowsPerPage);
        }
    }

    private int SearchGetPageCount(List<int> searchResultIndices, int rowsPerPage)
    {
        return GetPageCountIncludingAnyPartialEndPage(searchResultIndices.Count, rowsPerPage);
    }

    private int GetPageCountIncludingAnyPartialEndPage(int totalRows, int rowsPerPage)
    {
        int completePageCount = totalRows / rowsPerPage;
        bool hasIncompleteEndPage = totalRows % rowsPerPage != 0;
        int pageCount = completePageCount;
        if (hasIncompleteEndPage)
        {
            ++pageCount;
        }

        return pageCount;
    }

    private int SearchGetPageRowCount(List<int> searchResultIndices, int pageIndex, int rowsPerPage)
    {
        return GetPageRowCount(searchResultIndices.Count, pageIndex, rowsPerPage);
    }

    private int GetPageRowCount(int totalRows, int pageIndex, int rowsPerPage)
    {
        int fullPagesCount = totalRows / rowsPerPage;
        int fullPagesTotalRowCount = fullPagesCount * rowsPerPage;

        int pageIndexRowCount;
        if (pageIndex == fullPagesCount)
        {
            pageIndexRowCount = totalRows - fullPagesTotalRowCount;
        }
        else
        {
            pageIndexRowCount = rowsPerPage;
        }

        return pageIndexRowCount;
    }

    private void SaveScreenTextureAsSpectrumSearchScreenData(String searchTerm, int pageIndex, int rowsPerPage)
    {
        String searchListFolder;
        if (rowsPerPage == kRowsPerPageFull)
        {
            searchListFolder = kSearchListFullFolder;
        }
        else
        {
            searchListFolder = kSearchListMiniFolder;
        }

        String rootFolder = Installer.kOutputFolder + "/" + kLibraryFolder + "/" + searchListFolder + "/";
        String flattenedFilePath = SDFile.CreateFlattenedFilepath(rootFolder, searchTerm);

        byte[] screenMemory = GetByteArrayFromScreenTexture();

        String pageNumberString = String.Format("{0:000000}", pageIndex);

        string filename =
            Installer.kOutputFolder + "/"
            + kLibraryFolder + "/"
            + searchListFolder + "/"
            + flattenedFilePath
             + searchTerm.Substring(searchTerm.Length - 1) + "_"
            + pageNumberString + ".scr";

        SDFile.WriteAllBytes(filename, screenMemory);
    }

    private void DebugPrintDatabaseBytes()
    {
        //StringBuilder databaseStringBuilder = new StringBuilder();
        //for(int databaseByteIndex = 0; databaseByteIndex < _database.Length; ++databaseByteIndex)
        //{
        //    databaseStringBuilder.Append(_database[databaseByteIndex].ToString());
        //}

        for (int filenameIndex = 0; filenameIndex < _allFilenames.Count; ++filenameIndex)
        {
            Debug.Log(_allFilenames[filenameIndex]);
        }


        Debug.Log("*** DATABASE BYTES AS ASCII ***");
        Debug.Log(ASCIIEncoding.ASCII.GetString(_database));
    }

    private void FontDrawCharactersCentred(string characters, int spectrumScreenY)
    {
        int stringWidth = FontGetStringWidth(characters);
        int x = (int)((kSpectrumScreenWidth - stringWidth) * 0.5f);

        FontDrawCharacters(characters, x, spectrumScreenY);
    }

    private void FontDrawCharactersRightAligned(string characters, int rightBorderX, int spectrumScreenY)
    {
        int stringWidth = FontGetStringWidth(characters);
        int x = rightBorderX - stringWidth;

        FontDrawCharacters(characters, x, spectrumScreenY);
    }

    private void FontDrawCharacters(string characters, int spectrumScreenX, int spectrumScreenY)
    {
        int x = spectrumScreenX;
        int characterWidth;
        for (int characterIndex = 0; characterIndex < characters.Length; ++characterIndex)
        {
            string character = characters.Substring(characterIndex, 1);

            // kerning for lower case j (if more letters come up that need it, will need to clean this code up:
            if (characterIndex > 0 && character == "j")
            {
                x -= 1;
            }

            characterWidth = FontDrawCharacter(character, x, spectrumScreenY);
            x += characterWidth;
        }
    }

    private int FontDrawCharacter(string character, int spectrumScreenX, int spectrumScreenY)
    {
        byte[] charByte = Encoding.ASCII.GetBytes(character);

        if (charByte[0] == 0)
        {
            return 0; // end of string
        }

        int characterIndex = charByte[0] - 32; // - 32 for ASCII space character

        int x = _characterXPositions[characterIndex];
        int y = 0;
        int width = _characterWidths[characterIndex];

        if (spectrumScreenX + width >= SpectrumScreenTexture2D.width)
        {
            return 0; // char goes out of screen (TOIMPROVE could render partial chars at screen edge)
        }

        Color[] sourcePixels = FontTexture2D.GetPixels(x, y, width, kSpectrumCharSize);

        //        SpectrumScreenTexture2D.SetPixels(spectrumScreenX, SpectrumScreenTexture2D.height - spectrumScreenY - kSSpectrumCharSize + 1, width, kSSpectrumCharSize, sourcePixels);
        SpectrumScreenTexture2D.SetPixels(spectrumScreenX, SpectrumScreenTexture2D.height - spectrumScreenY - kSpectrumCharSize, width, kSpectrumCharSize, sourcePixels);

        return width;
    }

    private int FontGetStringWidth(string characters)
    {
        byte[] charactersBytes = Encoding.ASCII.GetBytes(characters);

        int stringWidth = 0;
        for (int characterIndex = 0; characterIndex < characters.Length; ++characterIndex)
        {
            int fontCharacterIndex = charactersBytes[characterIndex] - 32; // - 32 for ASCII space character

            stringWidth += _characterWidths[fontCharacterIndex];
        }

        return stringWidth;
    }

    private void FontDrawUDGCharacter(string character, int spectrumScreenX, int spectrumScreenY)
    {
        byte[] charByte = Encoding.ASCII.GetBytes(character);

        int characterIndex = charByte[0] - 32; // - 32 for ASCII space character

        int x = characterIndex * kSpectrumCharSize;
        int y = 0;

        Color[] sourcePixels = UDGFontTexture2D.GetPixels(x, y, kSpectrumCharSize, kSpectrumCharSize);

        SpectrumScreenTexture2D.SetPixels(spectrumScreenX, SpectrumScreenTexture2D.height - spectrumScreenY - kSpectrumCharSize, kSpectrumCharSize, kSpectrumCharSize, sourcePixels);
    }

    private void FontDrawRainbowStripesUDGs()
    {
        FontDrawUDGCharacter(kUDGSpectrumRainbowStripeString, 26 * kSpectrumCharSize, 0);
        FontDrawUDGCharacter(kUDGSpectrumRainbowStripeString, 27 * kSpectrumCharSize, 0);
        FontDrawUDGCharacter(kUDGSpectrumRainbowStripeString, 28 * kSpectrumCharSize, 0);
        FontDrawUDGCharacter(kUDGSpectrumRainbowStripeString, 29 * kSpectrumCharSize, 0);
        FontDrawUDGCharacter(kUDGSpectrumRainbowStripeString, 30 * kSpectrumCharSize, 0);
    }

    private IEnumerator GenerateSearchResultPages(List<String> searchStrings, int rowsPerPage)
    {
        _coroutineTaskRunning = true;

        SearchStringsTotal = searchStrings.Count;
        for (int searchStringIndex = 0; searchStringIndex < searchStrings.Count; ++searchStringIndex)
        {
            SearchStringsRemaining = searchStrings.Count - searchStringIndex;
            if (System.DateTime.Now.Ticks > _nextYieldtime)
            {
                const long kTicksPerSecond = 10000000;
                _nextYieldtime = System.DateTime.Now.Ticks + kTicksPerSecond;
                yield return null;
            }

            String searchString = searchStrings[searchStringIndex];
            if (searchString.Length == 1 || searchString.Length > SearchGenerator.kMaximumSearchTermLength)
            {
                continue;
            }
            GenerateSearchResultPage(searchStrings[searchStringIndex], _allFilenamesWithoutPathOrExtension, rowsPerPage);
        }

        _coroutineTaskRunning = false;
    }

    private void GenerateSearchResultPage(String searchString, List<String> strings, int rowsPerPage)
    {
        List<int> searchResultIndices = GetSearchResultIndices(searchString, strings);

        GenerateSearchStringScreenFiles(searchString, searchResultIndices, rowsPerPage);
    }

    private List<int> GetSearchResultIndices(String searchString, List<String> strings)
    {
        List<int> searchResultIndices = new List<int>();
        for (int stringIndex = 0; stringIndex < strings.Count; ++stringIndex)
        {
            // doesn't make it much/any faster



            //char[] separators = { '\n', ',', '.', ' ' };    // add your own
            //            str.Split(separators).Contains(word);

            //if (!strings[stringIndex].Contains(searchString))
            //{
            //    continue;
            //}




            //String searchPattern = @"\b" + searchString + @"\b";
            //if (IsMatch(strings[stringIndex], searchPattern))

            //if(strings[stringIndex].Split().Contains(searchString))
            if (_splitStrings[stringIndex].Contains(searchString))
            {
                searchResultIndices.Add(stringIndex);
            }
        }

        return searchResultIndices;
    }

    public static bool IsMatch(string input, string pattern)
    {
        return new Regex(pattern, RegexOptions.None /*, true*/).IsMatch(input);

        //Regex testRegex = new Regex("", RegexOptions.None);
    }

    private void WriteByteToScreenTexture(byte writeByte, int spectrumCharacterColumn, int spectrumPixelRow)
    {
        Color[] bytePixels = GetBytePixels(writeByte);

        int x = GetScreenTextureX(spectrumCharacterColumn);
        int y = GetScreenTextureY(spectrumPixelRow);

        SpectrumScreenTexture2D.SetPixels(x, y, kBitsPerByte, 1, bytePixels);
    }

    private Color[] GetBytePixels(byte writeByte)
    {
        BitArray bitArray = new BitArray(new byte[] { writeByte });

        Color[] sourcePixels = new Color[kBitsPerByte];

        for (int bitIndex = 0; bitIndex < kBitsPerByte; ++bitIndex)
        {
            sourcePixels[kBitsPerByte - bitIndex - 1] = bitArray.Get(bitIndex) ? Color.black : Color.white;
        }

        return sourcePixels;
    }

    private int GetScreenTextureX(int spectrumCharacterColumn)
    {
        return spectrumCharacterColumn * kSpectrumCharSize;
    }

    private int GetScreenTextureY(int spectrumPixelRow)
    {
        return SpectrumScreenTexture2D.height - 1 - spectrumPixelRow;
    }

    private void WriteBitToScreenTexture(bool writeBit, int spectrumCharacterColumn, int spectrumPixelRow, int bitNumber)
    {
        if (!writeBit)
        {
            return;
        }

        Color[] bitPixel = { Color.black };

        int x = GetScreenTextureX(spectrumCharacterColumn) + bitNumber;
        int y = GetScreenTextureY(spectrumPixelRow);

        SpectrumScreenTexture2D.SetPixels(x, y, 1, 1, bitPixel);
    }

    private void WritePageAndRowCountToScreenTexture(int pageCount, int rowCount)
    {
        byte pageCountHighByte = (byte)(pageCount / 256);
        byte pageCountLowByte = (byte)(pageCount & 255);
        WriteByteToScreenTexture(pageCountHighByte, kSpectrumCharacterColumnPageCountHighByte, kSpectrumPixelRowPageCountHighByte);
        WriteByteToScreenTexture(pageCountLowByte, kSpectrumCharacterColumnPageCountLowByte, kSpectrumPixelRowPageCountLowByte);

        byte rowCountByte = (byte)rowCount;
        WriteByteToScreenTexture(rowCountByte, kSpectrumCharacterColumnRowCount, kSpectrumPixelRowRowCount);
    }

    private void WriteIndicesToScreenTexture(List<int> searchResultIndices, int currentPageSearchResultIndicesStartIndex, int rowsPerPage)
    {
        int remainingIndicesOnThisPageCount = Mathf.Min(searchResultIndices.Count - currentPageSearchResultIndicesStartIndex, rowsPerPage);

        const int kIndicesStartColumn = 19;
        int writePixelRow = 0;
        int writeCharacterColumn = kIndicesStartColumn;
        for (int indicesIndex = 0; indicesIndex < remainingIndicesOnThisPageCount; ++indicesIndex)
        {
            int searchResultIndex = searchResultIndices[currentPageSearchResultIndicesStartIndex + indicesIndex];
            byte searchResultIndexHighByte = (byte)(searchResultIndex / 256);
            byte searchResultIndexLowByte = (byte)(searchResultIndex & 255);

            WriteByteToScreenTexture(searchResultIndexHighByte, writeCharacterColumn, writePixelRow);
            AdvanceCharacterColumnPixelRow(ref writeCharacterColumn, ref writePixelRow);

            WriteByteToScreenTexture(searchResultIndexLowByte, writeCharacterColumn, writePixelRow);
            AdvanceCharacterColumnPixelRow(ref writeCharacterColumn, ref writePixelRow);
        }
    }

    private void WriteFileFormatToScreenTexture(Installer.FileFormat fileFormat, int listRowIndex)
    {
        const int kFileFormatStartColumn = 25;
        int writePixelRow = 0;
        int writeBitNumber = 0;
        int writeCharacterColumn = kFileFormatStartColumn;
        for (int i = 0; i < listRowIndex; ++i)
        {
            AdvanceCharacterColumnPixelRowBitNumber(ref writeCharacterColumn, ref writePixelRow, ref writeBitNumber);
            AdvanceCharacterColumnPixelRowBitNumber(ref writeCharacterColumn, ref writePixelRow, ref writeBitNumber);
        }

        switch (fileFormat)
        {
            case Installer.FileFormat.Tap: // 00
                WriteBitToScreenTexture(false, writeCharacterColumn, writePixelRow, writeBitNumber);
                AdvanceCharacterColumnPixelRowBitNumber(ref writeCharacterColumn, ref writePixelRow, ref writeBitNumber);
                WriteBitToScreenTexture(false, writeCharacterColumn, writePixelRow, writeBitNumber);
                AdvanceCharacterColumnPixelRowBitNumber(ref writeCharacterColumn, ref writePixelRow, ref writeBitNumber);
                break;
            case Installer.FileFormat.Sna: // 01
                WriteBitToScreenTexture(false, writeCharacterColumn, writePixelRow, writeBitNumber);
                AdvanceCharacterColumnPixelRowBitNumber(ref writeCharacterColumn, ref writePixelRow, ref writeBitNumber);
                WriteBitToScreenTexture(true, writeCharacterColumn, writePixelRow, writeBitNumber);
                AdvanceCharacterColumnPixelRowBitNumber(ref writeCharacterColumn, ref writePixelRow, ref writeBitNumber);
                break;
            case Installer.FileFormat.Z80: // 10
                WriteBitToScreenTexture(true, writeCharacterColumn, writePixelRow, writeBitNumber);
                AdvanceCharacterColumnPixelRowBitNumber(ref writeCharacterColumn, ref writePixelRow, ref writeBitNumber);
                WriteBitToScreenTexture(false, writeCharacterColumn, writePixelRow, writeBitNumber);
                AdvanceCharacterColumnPixelRowBitNumber(ref writeCharacterColumn, ref writePixelRow, ref writeBitNumber);
                break;
            default:
                Debug.LogError("Couldn't match file format");
                Debug.Break();
                break;
        }
    }

    private void AdvanceCharacterColumnPixelRowBitNumber(ref int characterColumn, ref int pixelRow, ref int bitNumber)
    {
        ++bitNumber;
        if (bitNumber == kBitsPerByte)
        {
            bitNumber = 0;
            AdvanceCharacterColumnPixelRow(ref characterColumn, ref pixelRow);
        }
    }

    private void AdvanceCharacterColumnPixelRow(ref int characterColumn, ref int pixelRow)
    {
        ++pixelRow;
        if (pixelRow == kSpectrumCharSize)
        {
            pixelRow = 0;
            ++characterColumn;
        }

        //if(characterColumn == 32)
        //{
        //    Debug.LogError("Have gone off right side of speccy screen");
        //}
    }



    private void DrawScrollBarToTexture(int pageIndex, int pageCount, int rowsPerPage)
    {
        DrawOuterScrollBar(pageCount, rowsPerPage);
        DrawInnerScrollBar(pageIndex, pageCount, rowsPerPage);
    }

    public void DrawOuterScrollBar(int pageCount, int rowsPerPage)
    {
        const int kScrollBarPixelX = 31 * kSpectrumCharSize;

        const int kOuterScrollBarTopCharRow = 1;
        int outerScrollBarBottomCharRow = rowsPerPage;

        FontDrawUDGCharacter(kUDGScrollbarOuterTop, kScrollBarPixelX, kOuterScrollBarTopCharRow * kSpectrumCharSize);
        FontDrawUDGCharacter(kUDGScrollbarOuterBottom, kScrollBarPixelX, outerScrollBarBottomCharRow * kSpectrumCharSize);

        for (int middleCharRow = kOuterScrollBarTopCharRow + 1; middleCharRow < outerScrollBarBottomCharRow; ++middleCharRow)
        {
            FontDrawUDGCharacter(kUDGScrollbarOuterMiddle, kScrollBarPixelX, middleCharRow * kSpectrumCharSize);
        }
    }

    public void DrawInnerScrollBar(int pageIndex, int pageCount, int rowsPerPage)
    {
        float progressNormalised = Mathf.InverseLerp(1f, (float)pageCount, (float)(pageIndex + 1));

        const int kBarPixelXStart = (31 * kSpectrumCharSize) + 3;

        const int kEdgeBorderHeight = 3;
        const int kTopEdgeY = (1 * kSpectrumCharSize) + kEdgeBorderHeight;
        int bottomEdgeY = ((rowsPerPage + 1) * kSpectrumCharSize) - kEdgeBorderHeight + 2; // +2 fixes height ( 2x 1 pixel border of top/bottom of outer bar?)

        int maximumBarHeight = bottomEdgeY - kTopEdgeY;
        const int kMinimumBarHeight = 3;

        float heightNormalised = 1.0f / pageCount;
        int rawHeightPixels = (int)((float)maximumBarHeight * heightNormalised);

        if (rawHeightPixels < kMinimumBarHeight)
        {
            rawHeightPixels = kMinimumBarHeight;
        }

        int gapHeightPixels = maximumBarHeight - rawHeightPixels;

        Color[] sourceTopBottomPixels = { Color.white, Color.black, Color.white };
        Color[] sourceMiddlePixels = { Color.black, Color.black, Color.black };

        int startPixelRow = kTopEdgeY + (int)((float)gapHeightPixels * progressNormalised);

        for (int pixelRow = 0; pixelRow < rawHeightPixels; ++pixelRow)
        {
            int drawPixelY = startPixelRow + pixelRow;
            Color[] pixels;
            if (pixelRow == 0 || pixelRow == rawHeightPixels - 1)
            {
                pixels = sourceTopBottomPixels;
            }
            else
            {
                pixels = sourceMiddlePixels;
            }
            SpectrumScreenTexture2D.SetPixels(
                kBarPixelXStart,
                SpectrumScreenTexture2D.height - drawPixelY,
                3,
                1,
                pixels);
        }

    }




}