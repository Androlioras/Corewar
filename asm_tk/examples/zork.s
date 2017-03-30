l2:		sti r1, %4, r9
		xor r1, %4, r9
		or 	r1, %4, r9
		ldi r1, %4, r9
live:	live %1
		zjmp %:live
