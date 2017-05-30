
	addi	$s3,$zero,8192
	addi	$s0,$zero,8220
	lw	$s0,0($s0)
l0c:
	blez	$s0,fim
	move	$s1,$zero
l14:
	slt	$at,$s1,$s0
	beqz	$at,l44
	sll	$t0,$s1,0x2
	add	$t0,$t0,$s3
	lw	$t1,0($t0)
	lw	$t2,4($t0)
	slt	$at,$t2,$t1
	beqz	$at,l3c
	sw	$t1,4($t0)
	sw	$t2,0($t0)

l3c:
	addi	$s1,$s1,1
	j	l14
l44:
	addi	$at,$zero,1
	sub	$s0,$s0,$at
	j	l0c
fim:
