	ld a, l			 ; 32768 125 4ts
	or h			 ; 32769 180 4ts
	jr nz, l_8008		 ; 32770 32     4	 7/12ts
	scf			 ; 32772 55     4ts
	ld a, 2			 ; 32773 62     2	 7ts
	ret			 ; 32775 201 10ts
l_8008: call 8274		 ; 32776 205 82	 32     17ts
	ld a, 42		 ; 32779 62     42	 7ts
	ld b, 1			 ; 32781 6     1	 7ts
	ld hl, 8297		 ; 32783 33     105 32     10ts
	rst 8			 ; 32786 207 11ts
	sbc a, d		 ; 32787 154 4ts
	ret c			 ; 32788 216 11/5ts
	ld (8296), a		 ; 32789 50     104 32     13ts
	ld hl, 16384		 ; 32792 33     0	 64     10ts
	ld bc, 16384		 ; 32795 1     0	 64     10ts
	rst 8			 ; 32798 207 11ts
	sbc a, l		 ; 32799 157 4ts
	ret c			 ; 32800 216 11/5ts
	push bc			 ; 32801 197 11ts
	ld a, (8296)		 ; 32802 58     104 32     13ts
	rst 8			 ; 32805 207 11ts
	sbc a, e		 ; 32806 155 4ts
	pop bc			 ; 32807 193 10ts
	ret c			 ; 32808 216 11/5ts
	ld a, c			 ; 32809 121 4ts
	ld bc, 48955		 ; 32810 1     59	 191 10ts
	ld e, 64		 ; 32813 30     64	 7ts
	out (c), e		 ; 32815 237 89	 12ts
	ld b, 255		 ; 32817 6     255 7ts
	and a			 ; 32819 167 4ts
	jr nz, l_803a		 ; 32820 32     4	 7/12ts
	out (c), a		 ; 32822 237 121 12ts
	jr l_8050		 ; 32824 24     22	 12ts
l_803a: ld a, 1			 ; 32826 62     1	 7ts
	out (c), a		 ; 32828 237 121 12ts
	ld de, 191		 ; 32830 17     191 0     10ts
	ld hl, 23359		 ; 32833 33     63	 91     10ts
	ld a, 64		 ; 32836 62     64	 7ts
l_8046: dec a			 ; 32838 61     4ts
	ld b, e			 ; 32839 67     4ts
	out (c), a		 ; 32840 237 121 12ts
	ld b, d			 ; 32842 66     4ts
	outd			 ; 32843 237 171 16ts
	and a			 ; 32845 167 4ts
	jr nz, l_8046		 ; 32846 32     246 7/12ts
l_8050: or a			 ; 32848 183 4ts
	ret			 ; 32849 201 10ts
	ld de, 8297		 ; 32850 17     105 32     10ts
l_8055: ld a, (hl)		 ; 32853 126 7ts
	and a			 ; 32854 167 4ts
	jr z, l_8065		 ; 32855 40     12	 12/7ts
	cp 58			 ; 32857 254 58	 7ts
	jr z, l_8065		 ; 32859 40     8	 12/7ts
	cp 13			 ; 32861 254 13	 7ts
	jr z, l_8065		 ; 32863 40     4	 12/7ts
	ldi			 ; 32865 237 160 16ts
	jr l_8055		 ; 32867 24     240 12ts
l_8065: xor a			 ; 32869 175 4ts
	ld (de), a		 ; 32870 18     7ts
	ret			 ; 32871 201 10ts
