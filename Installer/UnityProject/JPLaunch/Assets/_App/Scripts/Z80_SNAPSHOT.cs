public class Z80_SNAPSHOT
{
    public int TYPE;                //0 = 48k, 1 = 128k, 2 = +3, 3 = Pentagon 128k
    public byte I;                  //I Register
    public int HL_, DE_, BC_, AF_;  //Alternate registers
    public int HL, DE, BC, IX, IY;  //16 bit main registers
    public byte R;                  //R Register
    public int AF, SP;              //AF and SP register
    public byte IM;                 //Interupt Mode
    public byte BORDER;             //Border colour
    public int PC;                  //PC Register
    public byte PORT_7FFD;          //Current state of port 7ffd
    public byte PORT_FFFD;          //Current state of soundchip AY
    public byte PORT_1FFD;          //Last out to port 1ffd (for +3)
    public byte[] AY_REGS;          //Contents of AY registers
    public bool IFF1;               //Are interrupts enabled?
    public bool IFF2;
    public bool ISSUE2;             //Issue 2 Keyboard?
    public bool AY_FOR_48K;
    public int TSTATES;
    public byte[][] RAM_BANK = new byte[16][];       //Contents of the 8192*16 ram banks

 

}
