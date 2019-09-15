/* ho dovuto caricare le lib con -T{build.variant.path}/linker_scripts/gcc/libs.ld */
/* se le chiamo nel "recipe.c.combine.pattern", definito in platform.txt vedo errore (bsp.a not found) */

GROUP (
	/*udooneo.a*/
	bsp.a
	psp.a
	open-amp.a
	libc.a
	libm.a
	libnosys.a
	libsupc++.a 
	libgcc.a
)

