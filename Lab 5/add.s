	# Compute (a + b + carry_in) and store the result in the address
	# of sum, the value 0 is stored at the address of carry_out unless
        # the expression above produces a carry in which case the
	# value 1 is written.
	# %rdi: a
        # %rsi: b
        # %rdx: carry_in (either 0 or 1)
        # %rcx: address of sum
        # %r8:  address of carry_out
        .globl add
add:
        add %rdi, (%rcx)        # sum += a
        add %rsi, (%rcx)        # sum += b
        jnc .skip_carry_out_1   # if carry, do not jump

        add $1, (%r8)           # carry_out = 1

        ret

.skip_carry_out_1:      # 1st carry trigger, so add carry_in and check
        add %rdx, (%rcx)        # sum += carry_in
        jnc .skip_carry_out_2   # 2nd carry check

        add $1, (%r8)           # carry_out = 1

        ret

.skip_carry_out_2:      # no carry so write 0 to carry_out
        xor %r8, %r8    # carry_out = 0

        ret
