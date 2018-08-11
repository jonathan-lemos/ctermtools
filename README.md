# ctermtools
Lightweight set of terminal UI functions.

Includes colors, underlining, getch(), disabling/enabling echo, hiding/showing the cursor, and more.

## Installation
To install the library:

```shell
make
sudo make install
```

To uninstall the library:

```shell
sudo make uninstall
```

To clean the project folder:

```shell
make clean
```

To build and run the test executable:

```shell
make test
./test
```
This must be done after installing the library.

## Documentation
Type the following to build the documentation:

```shell
make docs
firefox docs/html/globals.html #substitute "firefox" with your web browser of choice
```
This will only work if doxygen is installed on the system.

## License
This project is licensed under the MIT License. See [LICENSE.txt](LICENSE.txt) for details.
