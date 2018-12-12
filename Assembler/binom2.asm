	add $sp, $zero, $zero, $zero, 512		# 0: set $sp = 512
	lw $a0, $zero, $zero, $zero, 0x100		# 1: get n from address 0x100
	lw $a1, $zero, $zero, $zero, 0x101		# 1: get k from address 0x101
	jal $zero, $zero, $zero, $zero, bin2	# 2: calc $v0 = bin(n,k)
	sw $v0, $zero, $zero, $zero, 0x102		# 3: store bin(n,k) in 0x102
	halt $zero, $zero, $zero, $zero, 0		# 4: halt

bin2:
	sub $sp, $sp, $zero, $zero, 4			# 5: adjust stack for 4 items
	sw $s0, $sp, $zero, $zero, 3			# 6: save $s0
	sw $ra, $sp, $zero, $zero, 2			# 7: save return address
	sw $a1, $sp, $zero, $zero, 1			# 8: save argument1
	sw $a0, $sp, $zero, $zero, 0			# 8: save argument0
	
	add $t0, $zero, $zero, $zero, 0			# 10: $t0[=i] = 0
	add $t1, $zero, $zero, $zero, 0			# 10: $t1[=j] = 0
fori:
	branch $zero, $t0, $a0, 2, return		# a: jump to return if i > n
	branch $zero, $t0, $a1, 2, ibig			# a: i is bigger than k, therefore jump to ibig ($t2 = min(i,k))
	add $t2, $t0, $zero, $zero, 0			# 10: we didn't jump, so k is bigger than i, therefore $t2 = k
forj:
	branch $zero, $t1, $t2, 2, endfori		# a: jump to fori if j > min(i,k)
	branch $zero, $a1, $zero, 0, base  		# a: jump to base if j == 0
	branch $zero, $a0, $a1, 0, base	    	# a: jump to base if j == i
	
else:
	sub $t0, $t0, $zero, $zero, 1			# 10: i--
	sub $t1, $t1, $zero, $zero, 1			# 10: j--
	mac $s0, $t0, $a0, $t1,  258 			# $s0 = 258+(j-1)+n*(i-1) (address of c[i-1][j-1])
	lw $t3, $s0, $zero, $zero, 1			# 16: $t3 = c[i-1][j-1]
	add $t1, $t1, $zero, $zero, 1			# 10: j++ (now j is as it should be)
	mac $s0, $t0, $a0, $t1,  258 			# $s0 = 258+(j)+n*(i-1) (address of c[i-1][j])
	lw $s2, $s0, $zero, $zero, 0			# 16: $s2 = c[i-1][j]
	add $t2, $t3, $s2, $zero, 0				# 10: $t2 = c[i-1][j-1] + c[i-1][j]
	add $t0, $t0, $zero, $zero, 1			# 10: i++ (now i is as it should be)
	mac $s0, $t0, $a0, $t1,  258 			# $s0 = 258+j+n*i (address of c[i][j])
	sw $t2, $s0, $zero, $zero, 0			# c[i][j] = c[i-1][j-1] + c[i-1][j]
	branch $zero, $zero, $zero, $zero, endforj	    # a: jump to forj
	
base:
	mac $s0, $t0, $a0, $t1,  258 			# $s0 = 258+j+n*i (address of c[i][j])
	add $t3, $zero, $zero, $zero, 1			# 10: $t3=1
	sw $t3, $s0, $zero, $zero, 0			# c[i][j]=1
	branch $zero, $zero, $zero, $zero, forj	    # a: jump to forj

endforj:
	add $t1, $t1, $zero, $zero, 1			# 10: j++
	branch $zero, $zero, $zero, $zero, forj	    # a: jump to forj
endfori:
	add $t0, $t0, $zero, $zero, 1			# 10: i++
	add $t1, $zero, $zero, $zero, 0			# 10: $t1[=j] = 0
	branch $zero, $zero, $zero, $zero, fori	    # a: jump to fori
	
return:
	mac $s0, $a0, $a0, $a1,  258 			# $s0 = 258+k+n*n (address of c[n][k])
	lw $v0, $s0, $zero, $zero, 0			# 16: $v0 = c[n][k]
	lw $a0, $sp, $zero, $zero, 0			# 15: restore $a0
	lw $a1, $sp, $zero, $zero, 1			# 16: restore $a1
	lw $ra, $sp, $zero, $zero, 2			# 17: restore $ra
	lw $s0, $sp, $zero, $zero, 3			# 17: restore $s0
	add $sp, $sp, $zero, $zero, 4			# 18: pop 4 items from stack
	sw	$v0,   $zero, $zero, $zero, 0x102	# save return value in memory
	jr $ra, $zero, $zero, $zero, 0			# 19: and return

ibig:
	add $t2, $t0, $zero, $zero, 0			# 10: $t2 = i
    branch $zero, $zero, $zero, forj		# 13: jump to forj