## FdF features

- The entire program has been constructed with 32-bit integer variables! There isn't a single `long`, `float`, or `double` in the code. Both the zoom and the displacement are agile and the response is immediate. This, I found, was the only way to get my Raspberry Pi to draw 500 × 500 point maps. Color gradients are a bit more resource intensive, but they too are built with `int` variables \[see image D\].

- Images are buffered to prevent screen-tearing as the pixels are plotted.

- Information is not lost as one manipulates the image. For example, one could zoom in (`Z` key) until reaching *overflow* levels, spoiling the plot, and still undo the movements without data degradation. Likewise, flattening a map to zero with the vertical distortion `J` key is also reversible.

- Out of view lines are not processed, to further improve performance. Segments that do show in the image are still rendered even when the endpoints fall outside the image. *Only the plotted portions are actually calculated*.

## FdF operation

This project responds correctly to the typical window operations, such as the *minimize* and *close* buttons, but the user is meant to interact via the keyboard:

	'ESC'      : quit program
	'R' or 'r' : reload isometric projection
	'W' or 'w' : move up
	'A' or 'a' : move left
	'S' or 's' : move down
	'D' or 'd' : move right
	'Z' or 'z' : zoom in
	'X' or 'x' : zoom out
	'J' or 'j' : scale z down
	'K' or 'k' : scale z up
	'C' or 'c' : toggle color gradation

The default color treatment is to split the segments evenly between the endpoint colors. A more interesting—and quite stunning—effect is accomplished with the color gradiient option (`C` key).

## Simple MiniLibX installation guide, as performed with my Raspberry Pi 2

- Download and install the X11 development package

		sudo apt-get libxext-dev

- Extract the compress file `minilibx-linux.tgz` that contains, among other things, the **MiniLibX** library

		tar -xvf minilibx-linux.tgz -C /target/directory

- Navigate into the folder just created, `minilibx-linux`, and execute its **Makefile**

		make all

- Copy the newly created library (`libmlx.a`) and its header (`mlx.h`) into desired locations of the system. For example,

		sudo cp libmlx.a /usr/local/lib/
		sudo cp mlx.h /usr/local/include/

  NOTE: The alternative `libmlx_Linux.a` library or the *same* `libmlx.a` library compiled from the `sources.tgz` folder, will both make the project crash when the close button of the window is clicked.

- Adapt the **FdF** project's **Makefile** to include the new header and link the appropriate libraries. The compilation and linker options should incorporate the following flags

		CFLAGS = -I/usr/local/include/
		LDFLAGS = -L/usr/local/lib/
		LDLIBS = -lmlx -lXext -lX11

  Notice that the actual libraries are stored in a specialized variable, `LDLIBS`, implicitly used by the linker

#### NOTE: The Makefile present in this project extracts, compiles, and archives the desired library into a folder next to the source code.
