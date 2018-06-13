.name "zork"
.comment "I'M ALIIIIVE"
		 #jj

l2:		sti 	   r1,		%:live, %1 #sdf
		and 	   r1, 		%0, r1

live:	live %1
		zjmp %:live
