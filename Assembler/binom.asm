	add $sp, $zero, $zero, $zero, 512			# 0: set $sp = 512
	lw $a0, $zero, $zero, $zero, 0x100			# 1: get n from address 0x100
	lw $a1, $zero, $zero, $zero, 0x101			# 1: get k from address 0x101
	jal $zero, $zero, $zero, $zero, bin			# 2: calc $v0 = bin(n,k)
	sw $v0, $zero, $zero, $zero, 0x102			# 3: store bin(n,k) in 0x102
	halt $zero, $zero, $zero, $zero, 0			# 4: halt
	
bin:
	sub $sp, $sp, $zero, $zero, 4				# 5: adjust stack for 4 items
	sw  $s0, $sp, $zero, $zero, 3				# 6: save $s0
	sw  $ra, $sp, $zero, $zero, 2				# 7: save return address
	sw  $a1, $sp, $zero, $zero, 1				# 8: save argument1
	sw  $a0, $sp, $zero, $zero, 0				# 9: save argument0
	
	branch $zero, $a1, $zero, 0, retm  			# 10: jump to retm if k == 0
	branch $zero, $a0, $a1,   0, retm			# 11: jump to retm if n == k
	sub $a0, $a0, $zero, $zero, 1				# 12: calculate n - 1
	sub $a1, $a1, $zero, $zero, 1				# 13: calculate k - 1
	
	jal $zero, $zero, $zero, $zero, bin			# 14: calc $v0=bin(n-1,k-1)
	add $s0, $v0, $zero, $zero, 0				# 15: $s0 = bin(n-1,k-1)
	add $a1, $a1, $zero, $zero, 1				# 16: calculate k' + 1 = k -1 +1 = k
	jal $zero, $zero, $zero, $zero, bin			# 17: calc bin(n-1,k)
	add $v0, $v0, $s0, $zero, 0		   			# 18: $v0 = fib(n-1,k-1) + bin(n-1,k)
retfinal:
	lw $a0, $sp, $zero, $zero, 0				# 19: restore $a0
	lw $a1, $sp, $zero, $zero, 1				# 20: restore $a1
	lw $ra, $sp, $zero, $zero, 2				# 21: restore $ra
	lw $s0, $sp, $zero, $zero, 3				# 22: restore $s0
	add $sp, $sp, $zero, $zero, 4				# 23: pop 4 items from stack
	sw	$v0, $zero, $zero, $zero, 0x102		    # 24: save return value in memory (address 0x102)
	jr $ra, $zero, $zero, $zero, 0				# 25: and return

retm:
	add $v0, $zero, $zero, $zero, 1		    	# 26: $v0 = 1
	jal $zero, $zero, $zero, $zero, retfinal	# 27: go to retfinal
	
