## MiniLibX installation guide, as performed with a Raspberry Pi 2:

- Download and install the X11 development package

		sudo apt-get libxext-dev

- Extract the compress file `sources.tgz` that contains, among other things, the **MiniLibX** library

		tar -xvf sources.tgz -C /target/directory

- Navigate into the folder just created, `minilibx`, and execute its Makefile

		make all

- Copy the newly created library (`mlx.a`) and its header (`mlx.h`) into desired locations of the system. For example,

		cp libmlx.a /usr/local/lib/
		cp mlx.h /usr/local/include/

- Adapt the **FdF** project's Makefile to include the new header and link the appropriate libraries. The compilation and linker options should incorporate the following flags

		CFLAGS = -I/usr/local/include/
		LDFLAGS = -L/usr/local/lib/
		LDLIBS = -lmlx -lXext -lX11

  Notice that the actual libraries are stored in a specialized variable, `LDLIBS`, implicitly used by the linker
