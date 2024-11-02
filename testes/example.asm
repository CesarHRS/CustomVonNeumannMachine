.data

value:	 10
Z:	 0
vetor: 0,1,2,3

.text 		

main:
	li $t0, 25		# Load immediate value (25) 
	print $t0
	lw $t1, value		# Load the word stored in value (see bottom)
	print $t1
	add $t3, $t1, $t0	# Add
	print $t3
	sub $t4, $t1, $t0	# Subtract
	print $t4
	sw $t4, Z		# Store the answer in Z (declared at the bottom)  

	la $t0, vetor
	li $t2, 0
	li $t3, 3
	j print_vec
print_vec:
	print $t0
	li $t1, 1
	add $t0, $t1, $t0
	add $t2, $t1 $t2
	blt $t2 $t3 print_vec

comparacao:
	li $t1 10
	li $t2 5
	#beq $t1 $t1 igual
	#bne $t1 $t2 diferente
	#bgt $t1 $t2 maior
	#blt $t2 $t1 menor
