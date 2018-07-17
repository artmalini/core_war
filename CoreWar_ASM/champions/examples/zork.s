.name "zork"
.comment "I'M ALIIIIVE"
		#rf
l2: 	sti r1, %:live, %1 #rerhre
		and r1, %0, r1

live:	live %1
		zjmp %:live
