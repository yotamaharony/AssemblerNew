	add $sp, $zero, $zero, $zero, 512		# 0:  set $sp = 512
	lw $a0, $zero, $zero, $zero, 0x100		# 1:  get n from address 0x100
	lw $a1, $zero, $zero, $zero, 0x101		# 1:  get k from address 0x101
	jal $zero, $zero, $zero, $zero, bin2	# 2:  calc $v0 = bin(n,k)
	sw $v0, $zero, $zero, $zero, 0x102		# 3:  store bin2(n,k) in 0x102
	halt $zero, $zero, $zero, $zero, 0		# 4:  halt

bin2:
	sub $sp, $sp, $zero, $zero, 6			# 5:  adjust stack for 6 items
	sw $s2, $sp, $zero, $zero, 5			# 6:  save $s2
	sw $s1, $sp, $zero, $zero, 4			# 7:  save $s1
	sw $s0, $sp, $zero, $zero, 3			# 8:  save $s0
	sw $ra, $sp, $zero, $zero, 2			# 9:  save return address
	sw $a1, $sp, $zero, $zero, 1			# 10: save argument1
	sw $a0, $sp, $zero, $zero, 0			# 11: save argument0
	
	branch $zero, $a1, $zero, 0, edge_case1 # 12: jump to edge_case1 if k = 0
	branch $zero, $a0, $zero, 0, edge_case0 # 13: jump to edge_case0 if n = 0
	
	jal $zero, $zero, $zero, $zero, fact	# 14: calc n! ($a0 = n)
	add  $s0, $v0, $zero, $zero, 0		    # 15: $s0 = n!
	sub  $a0, $a0, $a1, $zero, 0		    # 16: $a0 = (n-k)
	jal $zero, $zero, $zero, $zero, fact	# 17: calc (n-k)! ($a0 = n-k)
	add  $s1, $v0, $zero, $zero, 0		    # 18: $s1 = (n-k)!
	add  $a0, $a1, $zero, $zero, 0		    # 19: $a0 = k
	jal $zero, $zero, $zero, $zero, fact	# 20: calc k! ($a0 = k)
	add  $s2, $v0, $zero, $zero, 0			# 21: $s2 = k!
	mac $s2, $s1, $s2, $zero, 0				# 22: $s2 = k!*(n-k)!
	add $a0, $s0, $zero, $zero, 0			# 23: $a0 = n!
	add $a1, $s2, $zero, $zero, 0			# 24: $a1 = (n-k)!*k!
	jal $zero, $zero, $zero, $zero, divide  # 25: calculate n choose k (n!/(k!(n-k)!))
	
	lw $a0, $sp, $zero, $zero, 0			# 26: restore $a0
	lw $a1, $sp, $zero, $zero, 1			# 27: restore $a1
	lw $ra, $sp, $zero, $zero, 2			# 28: restore $ra
	lw $s0, $sp, $zero, $zero, 3			# 29: restore $s0
	lw $s1, $sp, $zero, $zero, 4			# 30: restore $s1
	lw $s2, $sp, $zero, $zero, 5			# 31: restore $s2
	add $sp, $sp, $zero, $zero, 6			# 32: pop 6 items from stack
	jr $ra, $zero, $zero, $zero, 0			# 33: and return

		
fact:
	add $t0, $zero, $zero, $zero, 1			# 34: $t0[=fact] = 1
	add $t1, $a0, $zero, $zero, 0			# 35: $t1 = $a0
fact_loop:
	mac $t0, $t1, $t0, $zero,  0			# 36: fact = fact * $a0
	sub $t1, $t1, $zero, $zero, 1			# 37: $a0--
	branch $zero, $t1, $zero, 2, fact_loop  # 38: jump to fact_loop if $t1 > 0
	add	$v0, $t0, $zero, $zero, 0     	    # 39: save return value in memory
	jr $ra, $zero, $zero, $zero, 0			# 40: and return

divide:
	add $t0, $zero, $zero, $zero, $zero	 	# 41: $t0[=diff] = 0
	add $t1, $a0, $zero, $zero, $zero		# 42: $t1 = $a0
divide_loop:
	sub $t1, $t1, $a1, $zero,  0			# 43: $t1 = $t1 - $a1
	add $t0, $t0, $zero, $zero, 1			# 44: diff++
	branch $zero, $t1, $zero, 2, divide_loop # 45: jump to divide_loop if $t1 > 0
	add $v0, $t0, $zero, $zero, 0     	  	    # 46: save return value in memory ***TODO: maybe change to zero***
	jr $ra, $zero, $zero, $zero, 0			# 47: and return
	
edge_case0:
	add	$v0, $zero, $zero, $zero, 0     	# 48: save return value in memory
	add $sp, $sp, $zero, $zero, 6			# 49: pop 6 items from stack
	jr $ra, $zero, $zero, $zero, 0			# 50: and return
	
edge_case1:
	add	$v0, $zero, $zero, $zero, 1     	# 51: save return value in memory
	add $sp, $sp, $zero, $zero, 6			# 52: pop 6 items from stack
	jr $ra, $zero, $zero, $zero, 0			# 53: and return
