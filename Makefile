build:
	gcc main.c vibrato.c flanger.c chorus.c allpass.c wahwah.c -o effect.out -lm -lportaudio

run:
	make build
	./effect.out

clean:
	rm effect.out
