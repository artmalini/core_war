.name "zork"
.comment "I'M ALIIIIVE"
		 #jj
l2: 	sti r1,		%:live, %3
		and r1, 		%0, r1

live:	live %1
		zjmp %:live
