pwm:
	make -j4 -C build pwm
	openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program build/pwm.elf verify reset exit"

blink:
	make -j4 -C build blink
	openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program build/blink.elf verify reset exit"

encoder:
	make -j4 -C build encoder
	openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program build/encoder.elf verify reset exit"