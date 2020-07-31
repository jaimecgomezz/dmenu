# dmenu

[dmenu](https://tools.suckless.org/dmenu/) is dynamic menu for X. It manages large numbers of user-defined menu items efficiently.

This distribution aims to solve the patches integration problem, as well as the available scripts implementation. Is meant to be driven by the community and well documented, allowing to make `suckless for everybody`.



## Features

|                                                              |      | Patches                                                      |      |                                                              |      |
| ------------------------------------------------------------ | ---- | ------------------------------------------------------------ | ---- | ------------------------------------------------------------ | ---- |
| [border](https://tools.suckless.org/dmenu/patches/border/)   | ✔️    | [preselect](https://tools.suckless.org/dmenu/patches/preselect/) | ✔️    | [symbols](https://tools.suckless.org/dmenu/patches/symbols/) |      |
| [case insensitive](https://tools.suckless.org/dmenu/patches/case-insensitive/) | ✔️    | [scroll](https://tools.suckless.org/dmenu/patches/scroll/)   | ✔️    | [vertfull](https://tools.suckless.org/dmenu/patches/vertfull/) |      |
| [center](https://tools.suckless.org/dmenu/patches/center/)   | ✔️    | [initial-text](https://tools.suckless.org/dmenu/patches/initialtext/) |      | [nav-history](https://tools.suckless.org/dmenu/patches/navhistory/) |      |
| [dynamic options](https://tools.suckless.org/dmenu/patches/dynamicoptions/) | ✔️    | [pipe-out](https://tools.suckless.org/dmenu/patches/pipeout/) |      | [non blocking stdin](https://tools.suckless.org/dmenu/patches/non_blocking_stdin/) |      |
| [fuzzy-highlight](https://tools.suckless.org/dmenu/patches/fuzzyhighlight/) | ✔️    | [json](https://tools.suckless.org/dmenu/patches/json/)       |      | [more-color](https://tools.suckless.org/dmenu/patches/morecolor/) |      |
| [fuzzy-match](https://tools.suckless.org/dmenu/patches/fuzzymatch/) | ✔️    | [multi selection](https://tools.suckless.org/dmenu/patches/multi-selection/) |      | [line height](https://tools.suckless.org/dmenu/patches/line-height/) |      |
| [grid](https://tools.suckless.org/dmenu/patches/grid/)       | ✔️    | [managed](https://tools.suckless.org/dmenu/patches/managed/) |      | [print-input-text](https://tools.suckless.org/dmenu/patches/printinputtext/) |      |
| [xyw](https://tools.suckless.org/dmenu/patches/xyw/)         | ✔️    | [reject no match](https://tools.suckless.org/dmenu/patches/reject-no-match/) |      | [x-resources](https://tools.suckless.org/dmenu/patches/xresources/) |      |
| [numbers](https://tools.suckless.org/dmenu/patches/numbers/) | ✔️    | [prefix completition](https://tools.suckless.org/dmenu/patches/prefix-completion/) |      | [high-priority](https://tools.suckless.org/dmenu/patches/highpriority/) |      |
| [password](https://tools.suckless.org/dmenu/patches/password/) | ✔️    | [instant](https://tools.suckless.org/dmenu/patches/instant/) |      | [highlight](https://tools.suckless.org/dmenu/patches/highlight/) |      |
| [incremental](https://tools.suckless.org/dmenu/patches/incremental/) | ✔️    | [mouse support](https://tools.suckless.org/dmenu/patches/mouse-support/) |      |                                                              |      |

### Coming...

|                                                              | Scripts                                                      |                                                          |
| ------------------------------------------------------------ | ------------------------------------------------------------ | -------------------------------------------------------- |
| [passmenu](https://git.zx2c4.com/password-store/tree/contrib/dmenu/passmenu) | [dbrowse](https://github.com/clamiax/scripts/blob/master/src/dbrowse) | [dbdb](https://tools.suckless.org/dmenu/scripts/dbdb.sh) |
| [passmenu2](https://tools.suckless.org/dmenu/scripts/passmenu2) | [dmenu-pass](https://efe.kim/files/scripts/dmenu_pass)       | [clipmenu](https://github.com/cdown/clipmenu)            |
| [todo](https://tools.suckless.org/dmenu/scripts/todo)        | [dmenu-path](https://github.com/ema/dotfiles/blob/master/bin/dmenu_path) |                                                          |
| [via](https://github.com/xalexalex/via)                      | [dmenu-run](https://tools.suckless.org/dmenu/scripts/dmenu_run_with_command_history/) |                                                          |
| [dmenu-run-i](https://tools.suckless.org/dmenu/scripts/dmenu_run_i) | [dmenu-websearch](https://efe.kim/files/scripts/dmenu_websearch) |                                                          |
| [dmenu-launch](https://github.com/fsilveir/dmenu-launch)     | [mpdmenu](https://github.com/cdown/mpdmenu/blob/master/mpdmenu) |                                                          |



## Installation

Currently there’s no package available, so a manual installation is required.

### Requirements

- [Xlib header files](https://tronche.com/gui/x/xlib/introduction/header.html)

- [make](https://www.gnu.org/software/make/)

  


1. Download the source code

   ```sh
   git clone https://github.com/jaimecgomezz/dmenu.git && cd dmenu
   ```

2. Use [make](https://www.gnu.org/software/make/) to install `dmenu` on your system, it may be need to be executed with `sudo`

   ```sh
   sudo make clean install
   ```



## Patching

This [dmenu](https://tools.suckless.org/dmenu/) distribution comes with [handle](https://github.com/jaimecgomezz/dmenu/blob/master/handle), a utility that will take care of patches for you, just run:

```sh
# Usage: ./handle [ACTION] [PATCH] [OPTION]

# Installing the border patch
./handle patch border

# Uninstalling the border patch
./handle depatch border
```

The rest of ACTIONS, PATCHES and OPTIONS currently available can be found running:

```sh
./handle
```



## Notes

- The proper documentation is a high priority, unfortunately, it requires a considerable amount of time. It will be delivered soon, of course, your contributions are encouraged!




## Contributing

You can read the `CONTRIBUTING` and make a `PR` whenever you’re ready, they are all welcomed:)



## License

 [Jaime Castro](https://github.com/jaimecgomezz), 2020. Code released under the MIT license.
