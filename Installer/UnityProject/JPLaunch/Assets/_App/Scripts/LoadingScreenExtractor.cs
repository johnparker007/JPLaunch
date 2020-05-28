using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;
using System;
using System.Text;
using System.IO;


public class LoadingScreenExtractor
{
    public const int kLoadingScreenLength = 6912;


    public LoadingScreenExtractor()
    {

    }

    private byte[] _buffer = new byte[kLoadingScreenLength];

    private byte[] _noImageAvailableBuffer = new byte[kLoadingScreenLength];

    public byte[] Extract(byte[] sourceFileBytes, Installer.FileFormat fileFormat, string filename)
    {
        switch(fileFormat)
        {
            case Installer.FileFormat.Tap:
                return ExtractTap(sourceFileBytes);
            case Installer.FileFormat.Sna:
                return ExtractSna(sourceFileBytes);
            case Installer.FileFormat.Z80:
                return ExtractZ80(filename);
            default:
                Debug.LogError("Format not found");
                return _noImageAvailableBuffer;
        }
    }

    // TODO Still more to do - example file: 'Sai Combat (1996)(Mirrorsoft).tap' : has screen that ZX Block Editor can see
    // there is something special with the length (6912 + 256 as 2 seperate blocks, not getting detected
    
    // TOIMPROVE - perhaps also get blocks where the previous block was a pilot, and the start address was 16384 (and the length of next block is >6912)
    private byte[] ExtractTap(byte[] sourceFileBytes)
    {
        const int kLengthByteCount = 2;
        const int kChecksumAndFlagsByteCount = 2;

        const int kLoadingScreenBlockLength = kLoadingScreenLength + kChecksumAndFlagsByteCount;

        int offset = 0;

        do
        {
            int blockLength = Get16BitWord(sourceFileBytes, offset);
            if (blockLength == kLoadingScreenBlockLength)
            {
                Array.Copy(sourceFileBytes, offset + kLengthByteCount + 1, _buffer, 0, kLoadingScreenLength); // + 1 as I think flags byte is at start?
                return _buffer;
            }

            offset += kLengthByteCount + blockLength;
        }
        while (offset < sourceFileBytes.Length);

        return _noImageAvailableBuffer;
    }

    // LSB first
    private int Get16BitWord(byte[] sourceBytes, int offset)
    {
        return sourceBytes[offset] + (sourceBytes[offset + 1] * 256);
    }

    private byte[] ExtractSna(byte[] sourceFileBytes)
    {
        const int kSpectrumRAMStartOffset = 27;

        Array.Copy(sourceFileBytes, kSpectrumRAMStartOffset, _buffer, 0, kLoadingScreenLength);

        return _buffer;
    }

    private byte[] ExtractZ80(string filename)
    {
        Z80_SNAPSHOT z80Snapshot = Z80File.LoadZ80(filename);

        //Array.Copy(z80Snapshot.RAM_BANK[8], 0, _buffer, 0, kLoadingScreenLength);
        Array.Copy(z80Snapshot.RAM_BANK[10], 0, _buffer, 0, kLoadingScreenLength);

        return _buffer;
        //Debug.Log(z80Snapshot.)

        //// info from: http://www.worldofspectrum.org/faq/reference/z80format.htm

        //const int kProgramCounterOffset = 6;

        //bool z80Version2or3 = sourceFileBytes[kProgramCounterOffset] == 0 && sourceFileBytes[kProgramCounterOffset + 1] == 0;

        //const int kVersion1HeaderByteLength = 30;
        //const int kVersion2And3AdditionalHeaderLengthOffset = 30;
        
        //int headerLength = kVersion1HeaderByteLength;
        //if(z80Version2or3)
        //{
        //    int additionalHeaderLength = Get16BitWord(sourceFileBytes, kVersion2And3AdditionalHeaderLengthOffset);
        //    headerLength += additionalHeaderLength;
        //}

        //int offset = headerLength + 1; // not sure why it's +1 from reading the doc at WoS, but this is correct
        ////int offset = headerLength; // not sure why it's +1 from reading the doc at WoS, but this is correct

        //int compressedBlockLength = Get16BitWord(sourceFileBytes, offset);
        //int blockPageNumber = sourceFileBytes[offset + 2];



        //Debug.Log("ExtractZ80 - headerLength == " + headerLength + "  compressedBlockLength: " + compressedBlockLength + "   blockPageNumber: " + blockPageNumber);

        //return null;
    }



}
