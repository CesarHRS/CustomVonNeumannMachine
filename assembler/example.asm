.data

value:	 12
Z:	 0
#vetor: 0,1,2,3

.text 		

main:
	li $t2, 25		# Load immediate value (25) 
	lw $t3, value		# Load the word stored in value (see bottom)
	add $t4, $t2, $t3	# Add
	sub $t5, $t2, $t3	# Subtract
	sw $t5, Z		#Store the answer in Z (declared at the bottom)  

comparacao:
	li $t1 10
	li $t2 5
	beq $t1 $t1 .igual
	bne $t1 $t2 .diferente
	# Sub is necessary due to the limits of the instruction size
	sub $t2 $t1 $t3
	bgtz $t3 .maior
	bltz $t3 .menor
