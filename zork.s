.name "zork"
.comment "I'M ALIIIIVE"
		 #jj
<<<<<<< HEAD
l2: 
	sti r1,%:live,%1
=======
l2: 	sti r1,%:live,%1
>>>>>>> 11c0534a28409ff614c50ba05381b57ff7a505e5
		and r1,%0,r1

live:	live %1
		zjmp %:live
