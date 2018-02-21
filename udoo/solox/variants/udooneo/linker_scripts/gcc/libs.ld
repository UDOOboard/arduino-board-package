
/* lib are loaded with -T{build.variant.path}/linker_scripts/gcc/libs.ld */
/* loading libs in "recipe.c.combine.pattern" (defined in platform.txt) a "bsp.a not found" error is triggered */

GROUP (
	bsp.a
	psp.a
	mcc.a
	libc.a
	libm.a
	libnosys.a
	libsupc++.a 
	libgcc.a
)

