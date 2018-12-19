# First Matrix 	: 0x100 - 0x10F => 256 - 271
# Second Matrix 	: 0x110 - 0x11F => 272 - 287
# Result Matrix	: 0x120 - 0x12F => 288 - 303
	
.word 0x100 0
.word 0x101 1
.word 0x102 2
.word 0x103 3
.word 0x104 4
.word 0x105 5
.word 0x106 6
.word 0x107 7
.word 0x108 8
.word 0x109 9
.word 0x10A 10
.word 0x10B 11
.word 0x10C 12
.word 0x10D 13
.word 0x10E 14
.word 0x10F 15
.word 0x110 0
.word 0x111 1
.word 0x112 2
.word 0x113 3
.word 0x114 4
.word 0x115 5
.word 0x116 6
.word 0x117 7
.word 0x118 8
.word 0x119 9
.word 0x11A 10
.word 0x11B 11
.word 0x11C 12
.word 0x11D 13
.word 0x11E 14
.word 0x11F 15

	add 	$sp, $zero, $zero, $zero, 512
	sub 	$t0,$zero,$zero,$zero,1				# 0 : set i=-1
	add 	$s0,$zero,$zero,$zero,4				# 1 : set s0=4 (const)
	
for1:
	add		$t0,$t0,$zero,$zero,1			# 3 : first for - i++;
	branch 	$zero,$t0,$s0,0,return		# 2 : jump to return if i==4
	sub 	$t1,$zero,$zero,$zero,1			# 4 : set j=-1

for2:
	add		$t1,$t1,$zero,$zero,1			# 6 : second for - j++
	branch 	$zero,$t1,$s0,0,for1		# 5 : jump to return if j==4
	sub 	$t2,$zero,$zero,$zero,1			# 7 : set k=-1
	add 	$t3,$zero,$zero,$zero,0			# 8 : set result = 0

for3:
	add		$t2,$t2,$zero,$zero,1			# f : third for - k++
	branch	$zero,$t2,$s0,0,setCell		# 9 : jump to setCell if k==4
	mac		$s1,$t0,$s0,$t2,256				# a : get the address of A[i][k] - i*4+k+256
	mac		$s2,$t2,$s0,$t1,272				# b : get the address of B[k][j] - k*4+j+272
	lw		$s1,$s1,$zero,$zero,0			# c : restore $s1 = A[i][k]
	lw		$s2,$s2,$zero,$zero,0			# d : restore $s2 = B[k][j]
	mac		$t3,$s1,$s2,$t3,0				# e : result += A[i][k] * B[k][j]
	branch	$zero,$zero,$zero,$zero,for3	# 10 : jump to for3
	
setCell:
	mac		$s1,$t0,$s0,$t1,288				# 11 :  get the address of C[i][j] - i*4+j+288
	sw		$t3,$s1,$zero,$zero,0			# 12 :	store C[i][j] = result
	branch	$zero,$zero,$zero,$zero,for2	# 13 : 	jump to for2

return:
	halt	$zero,$zero,$zero,$zero,0		# 14 : return - end the programe
	
