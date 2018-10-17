	lw	1	0	a	#1
	lw	2	0	b	#1
	add	3	1	2	$3=2
	add	3	3	2	$3=3
	jalr	4	4	jump down 1
	add	3	3	2	$3 = 4
	add	3	3	2	$3 = 5
	lw	6	0	j	load 11 int $6
	jalr	5	6	jump to pc 11 (line 11 here)
	add	3	3	2	should be skipped
	add	3	3	2	should be skipped
	noop
	noop	
	halt			
a	.fill	1	
b	.fill	1
j	.fill 	11