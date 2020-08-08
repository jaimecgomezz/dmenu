# dmenu

A patch-friendly [dmenu](https://tools.suckless.org/dmenu/) distribution. Lets make `suckless software for everybody`.



## Features

|                                                              |      | Patches                                                      |      |                                                              |      |
| ------------------------------------------------------------ | ---- | ------------------------------------------------------------ | ---- | ------------------------------------------------------------ | ---- |
| [border](https://tools.suckless.org/dmenu/patches/border/)   | ✔️    | [preselect](https://tools.suckless.org/dmenu/patches/preselect/) | ✔️    | [symbols](https://tools.suckless.org/dmenu/patches/symbols/) | ✔️    |
| [case insensitive](https://tools.suckless.org/dmenu/patches/case-insensitive/) | ✔️    | [scroll](https://tools.suckless.org/dmenu/patches/scroll/)   | ✔️    | [vertfull](https://tools.suckless.org/dmenu/patches/vertfull/) | ✔️    |
| [center](https://tools.suckless.org/dmenu/patches/center/)   | ✔️    | [initial-text](https://tools.suckless.org/dmenu/patches/initialtext/) | ✔️    | [navhistory](https://tools.suckless.org/dmenu/patches/navhistory/) | ✔️    |
| [dynamic options](https://tools.suckless.org/dmenu/patches/dynamicoptions/) | ✔️    | [pipe-out](https://tools.suckless.org/dmenu/patches/pipeout/) | ✔️    | [more-color](https://tools.suckless.org/dmenu/patches/morecolor/) | ✔️    |
| [fuzzy-highlight](https://tools.suckless.org/dmenu/patches/fuzzyhighlight/) | ✔️    | [json](https://tools.suckless.org/dmenu/patches/json/)       | ✔️    | [line height](https://tools.suckless.org/dmenu/patches/line-height/) | ✔️    |
| [fuzzy-match](https://tools.suckless.org/dmenu/patches/fuzzymatch/) | ✔️    | [multi selection](https://tools.suckless.org/dmenu/patches/multi-selection/) | ✔️    | [print-input-text](https://tools.suckless.org/dmenu/patches/printinputtext/) | ✔️    |
| [grid](https://tools.suckless.org/dmenu/patches/grid/)       | ✔️    | [managed](https://tools.suckless.org/dmenu/patches/managed/) | ✔️    | [x-resources](https://tools.suckless.org/dmenu/patches/xresources/) | ✔️    |
| [xyw](https://tools.suckless.org/dmenu/patches/xyw/)         | ✔️    | [reject no match](https://tools.suckless.org/dmenu/patches/reject-no-match/) | ✔️    | [high-priority](https://tools.suckless.org/dmenu/patches/highpriority/) | ✔️    |
| [numbers](https://tools.suckless.org/dmenu/patches/numbers/) | ✔️    | [prefix completition](https://tools.suckless.org/dmenu/patches/prefix-completion/) | ✔️    | [highlight](https://tools.suckless.org/dmenu/patches/highlight/) | ✔️    |
| [password](https://tools.suckless.org/dmenu/patches/password/) | ✔️    | [instant](https://tools.suckless.org/dmenu/patches/instant/) | ✔️    | [non blocking stdin](https://tools.suckless.org/dmenu/patches/non_blocking_stdin/) |      |
| [incremental](https://tools.suckless.org/dmenu/patches/incremental/) | ✔️    | [mouse support](https://tools.suckless.org/dmenu/patches/mouse-support/) | ✔️    |                                                              |      |



| Scripts                                                      |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [dbrowse](https://github.com/clamiax/scripts/blob/master/src/dbrowse) | [passmenu](https://git.zx2c4.com/password-store/tree/contrib/dmenu/passmenu) |
| [dmenu-pass](https://efe.kim/files/scripts/dmenu_pass)       | [passmenu2](https://tools.suckless.org/dmenu/scripts/passmenu2) |
| [dmenu-path](https://github.com/ema/dotfiles/blob/master/bin/dmenu_path) | [todo](https://tools.suckless.org/dmenu/scripts/todo)        |
| [dmenu-run](https://tools.suckless.org/dmenu/scripts/dmenu_run_with_command_history/) (command history) | [dbdb](https://tools.suckless.org/dmenu/scripts/dbdb.sh)     |
| [dmenu-websearch](https://efe.kim/files/scripts/dmenu_websearch) | [dmenu-run-i](https://tools.suckless.org/dmenu/scripts/dmenu_run_i) |
| [mpdmenu](https://github.com/cdown/mpdmenu/blob/master/mpdmenu) | [dmenu-launch](https://github.com/fsilveir/dmenu-launch)     |

The scripts shown above are the ones listed on the official [suckless page](https://tools.suckless.org/dmenu/scripts/). They can be founded under the `scripts` folder for convenience.



## Installation

Currently there’s no package available, so a manual installation is needed.

### Requirements

[Xlib header files](https://tronche.com/gui/x/xlib/introduction/header.html), [make](https://www.gnu.org/software/make/), [patch](https://man7.org/linux/man-pages/man1/patch.1.html)

### Steps


1. Download the source code

   ```sh
   git clone https://github.com/jaimecgomezz/dmenu.git && cd dmenu
   ```

2. Use [make](https://www.gnu.org/software/make/) to install `dmenu` on your system, it may be need to be executed with `sudo`

   ```sh
   sudo make clean install
   ```



## Patching

This distribution comes with [handle](https://github.com/jaimecgomezz/dmenu/blob/master/handle), a utility that will take care of patches for you, just run:

```sh
# Usage: ./handle ACTION PATCH [OPTIONS]

# Installing patch A
./handle patch A

# Removing border A
./handle depatch A
```

The rest of ACTIONS, PATCHES and OPTIONS currently available can be found running:

```sh
./handle
```



## Testing patches

For those willing to support the project, here’s a handy utility, [test-patch](https://github.com/jaimecgomezz/dmenu/blob/master/test-patch) script. It will test the integration of a given patch with all the other patches listed under the `patches` folder. Whenever you need know if the patch you’ve been working on its ready, use it!

`````sh
# Usage: ./test-patch PATCH

# Testing the patch A
./test-patch A
...
B			Ok	# Means both patches can be used simultaneously
C			Failed!	# Means that the both patches have conflicts integrating together
...
`````

When the tests are finished, `test-patch` will report the results. If a patch “fails” you should:

- Make the older patch compatible with the new patch. Not on a functional level, but in a code level.
- Warn about the incompatibility of both patches in the `handle-usage` doc.

WARNING: This utility DO NOT test the patch functionality (if it does whats it’s suppose to do), it only makes you aware of any patch that might have troubles integrating with it.



## Notes

The proper documentation is a high priority, unfortunately, it requires a considerable amount of time. It will be delivered soon, of course, your contributions are encouraged!




## Contributing

You can read the `CONTRIBUTING` and make a `PR` whenever you’re ready, they are all welcomed:)



## License

 Code released under the MIT license.
