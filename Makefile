
build:
	gcc main.c vibrato.c flanger.c chorus.c -o effect.out -lm -lportaudio

run:
	make build
	./effect.out
