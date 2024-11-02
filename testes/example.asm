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
