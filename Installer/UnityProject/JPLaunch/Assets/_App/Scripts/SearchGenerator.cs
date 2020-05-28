using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;
using System;
using System.Text;

public class SearchGenerator
{
    public const int kMaximumSearchTermLength = 16;

    public List<String> UniqueWords;
    public List<String> UniqueWordsFiltered;

    public SearchGenerator()
    {

    }

    public void Initialise(List<String> allFilenamesUppercase)
    {
        CleanFilenames(allFilenamesUppercase);
    }

    private void CleanFilenames(List<String> allFilenames)
    {
        List<String> allFilenamesCopy = allFilenames.ToArray().ToList();

        // TOIMPROVE should strip "'s" to just "s", so can search for TIGERS if it was TIGER'S
        allFilenamesCopy = ReplaceCharRange(allFilenamesCopy, '!', '/');
        allFilenamesCopy = ReplaceCharRange(allFilenamesCopy, ':', '@');
        allFilenamesCopy = ReplaceCharRange(allFilenamesCopy, '[', '`');
        allFilenamesCopy = ReplaceCharRange(allFilenamesCopy, '{', '~');

        allFilenamesCopy = RemoveExtraSpaceChars(allFilenamesCopy);

        //allFilenamesCopy = ConvertToUpperCase(allFilenamesCopy);

        String allFilenamesConcatenated = GetAllStringsConcatenated(allFilenamesCopy);

        UniqueWords = GetUniqueWords(allFilenamesConcatenated);

        UniqueWordsFiltered = GetUniqueWordsFiltered(UniqueWords);
    }

    private List<String> ReplaceCharRange(List<String> strings, char startChar, char endCharInclusive)
    {
        for (int stringIndex = 0; stringIndex < strings.Count; ++stringIndex)
        {
            for (int charInt = startChar; charInt <= endCharInclusive; ++charInt)
            {
                strings[stringIndex] = strings[stringIndex].Replace(((char)charInt).ToString(), " ");
            }
        }

        return strings;
    }

    private List<String> RemoveExtraSpaceChars(List<String> strings)
    {
        for (int stringIndex = 0; stringIndex < strings.Count; ++stringIndex)
        {
            // TOIMPROVE write this better!
            strings[stringIndex] = strings[stringIndex].Replace("  ", " ");
            strings[stringIndex] = strings[stringIndex].Replace("  ", " ");
            strings[stringIndex] = strings[stringIndex].Replace("  ", " ");
            strings[stringIndex] = strings[stringIndex].Replace("  ", " ");
            strings[stringIndex] = strings[stringIndex].Replace("  ", " ");
            strings[stringIndex] = strings[stringIndex].Replace("  ", " ");
            strings[stringIndex] = strings[stringIndex].Replace("  ", " ");
            strings[stringIndex] = strings[stringIndex].Replace("  ", " ");
            strings[stringIndex] = strings[stringIndex].Replace("  ", " ");
        }

        return strings;
    }

    private List<String> ConvertToUpperCase(List<String> strings)
    {
        for (int stringIndex = 0; stringIndex < strings.Count; ++stringIndex)
        {
            strings[stringIndex] = strings[stringIndex].ToUpper();
        }

        return strings;
    }

    private String GetAllStringsConcatenated(List<String> strings)
    {
        StringBuilder allStringsConcatenated = new StringBuilder();
        for (int stringIndex = 0; stringIndex < strings.Count; ++stringIndex)
        {
            allStringsConcatenated.Append(strings[stringIndex]);
        }

        return allStringsConcatenated.ToString();
    }


    private List<String> GetUniqueWords(String allFilenamesConcatenated)
    {
        //String source = "I have a car I had bought it two years ago I like it very much.";
   
        //Char[] separators = new Char[] { ' ', '\r', '\n', '\t', ',', '.', ';', '!', '?' };
        Char[] separators = new Char[] { ' ' };

        HashSet<String> uniqueWords =
          new HashSet<String>(allFilenamesConcatenated.Split(separators, StringSplitOptions.RemoveEmptyEntries));

        return uniqueWords.ToList();
    }

    private List<String> GetUniqueWordsFiltered(List<String> uniqueWords)
    {
        List<String> uniqueWordsFiltered = uniqueWords.ToArray().ToList();
        uniqueWordsFiltered.RemoveAll(x => x.Length > kMaximumSearchTermLength || x.Length == 1);

        return uniqueWordsFiltered;
    }

}
