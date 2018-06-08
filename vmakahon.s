.name "vMaKaHoN.s \n\nfggd"
.comment "gfdg"

42: 	sti r1, %:live, %666999
		and r1, %0, r1

live:
live %4
zjmp %:live

forks:
add	r2, r3, r2		;increment r2
xor	r2, %15, r4		;if (r4) {carry = 0}

start:
	ld -42, r2
	zjmp %2

first_attack:
	sti r10, r15, r9
	live %42
	zjmp %-410
