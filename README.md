# dmenu

A patch-friendly [dmenu](https://tools.suckless.org/dmenu/) distribution. Lets make `suckless software for everybody`.

[![ss-Sun-16-Aug20-00-54.png](https://i.postimg.cc/3xS7jJxq/ss-Sun-16-Aug20-00-54.png)](https://postimg.cc/18qLsS60)

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



## Patching and testing

For the sake of stability across projects, the [handle](https://github.com/jaimecgomezz/suckless-patchers/blob/master/handle) (patching) and [test-patch](https://github.com/jaimecgomezz/suckless-patchers/blob/master/test-patch) (testing) utilities and its usage instructions can be found [here](https://github.com/jaimecgomezz/suckless-patchers). Believe me, they’re worth it!



## Notes

The proper documentation is a high priority, unfortunately, it requires a considerable amount of time. It will be delivered soon, of course, your contributions are encouraged!




## Contributing

You can read the `CONTRIBUTING` and make a `PR` whenever you’re ready, they are all welcomed:)



## License

 Code released under the MIT license.
