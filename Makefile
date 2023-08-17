FQBN := arduino:samd:mkrwifi1010
PORT := /dev/ttyACM0
BUILD := ./build

$(info	BOARD: $(FQBN))
$(info	PORT: $(PORT))
$(info	build directory: $(BUILD))

.PHONY: default upload install clean

default:
	arduino-cli compile -b $(FQBN) --build-path $(BUILD)

upload:
	arduino-cli upload -b $(FQBN) -p $(PORT) -v --input-dir $(BUILD)

install: | default upload

clean:
	rm -rf $(BUILD)
