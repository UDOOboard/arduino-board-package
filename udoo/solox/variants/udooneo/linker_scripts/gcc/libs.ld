
/* ho dovuto caricare le lib con -T{build.variant.path}/linker_scripts/gcc/libs.ld */
/* se le chiamo nel "recipe.c.combine.pattern", definito in platform.txt vedo errore (bsp.a not found) */

GROUP (
/*
	/home/francesco/.arduino15/packages/arduino/hardware/sam/1.6.4/variants/arduino_due_x/mqx/release/bsp/bsp.a
	/home/francesco/.arduino15/packages/arduino/hardware/sam/1.6.4/variants/arduino_due_x/mqx/release/psp/psp.a
	/home/francesco/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/arm-none-eabi/lib/armv7e-m/fpu/libc.a
	/home/francesco/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/arm-none-eabi/lib/armv7e-m/fpu/libm.a
	/home/francesco/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/arm-none-eabi/lib/armv7e-m/fpu/libnosys.a
	/home/francesco/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/arm-none-eabi/lib/armv7e-m/fpu/libsupc++.a 
	/home/francesco/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/lib/gcc/arm-none-eabi/4.8.3/armv7e-m/fpu/libgcc.a
*/
	/*core.a*/

	bsp.a
	psp.a
	open-amp.a
	libc.a
	libm.a
	libnosys.a
	libsupc++.a 
	libgcc.a
)

