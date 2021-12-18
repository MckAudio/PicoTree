default:
	make -j4 -C build
	openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program build/pwm.elf verify reset exit"