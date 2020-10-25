include Makefile.inc

SAMPLE_DATA=0001-sampleDataModule.bin

all: sampleCodeModule sampleDataModule chess

sampleCodeModule:
	cd SampleCodeModule; make

sampleDataModule:
	printf "This is sample data." >> $(SAMPLE_DATA) && dd if=/dev/zero bs=1 count=1 >> $(SAMPLE_DATA)

chess:
	cd Chess; make

clean:
	cd SampleCodeModule; make clean
	cd Chess; make clean
	rm -rf *.bin


.PHONY: sampleCodeModule chess all clean
