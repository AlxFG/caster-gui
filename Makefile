CC = zig cc -target x86_64-windows-gnu

LDFLAGS = -L3rdparty/raylib/windows/lib -lraylib -lopengl32 -lgdi32 -lwinmm
CFLAGS = -I3rdparty/raylib/windows/include

build:
	${CC} src/main.c -o caster-gui.exe ${CFLAGS} ${LDFLAGS}
