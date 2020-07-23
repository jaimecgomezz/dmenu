# dmenu

[dmenu](https://tools.suckless.org/dmenu/) is dynamic menu for X. It manages large numbers of user-defined menu items efficiently.

This distribution aims to solve the patches integration problem, as well as the available scripts implementation. Is meant to be driven by the community and well documented, allowing to make `suckless for everybody`.



## Features

### Patches

| [border](https://tools.suckless.org/dmenu/patches/border/)   | ✔️    | [instant](https://tools.suckless.org/dmenu/patches/instant/) |      | [pipe-out](https://tools.suckless.org/dmenu/patches/pipeout/) |      |
| ------------------------------------------------------------ | ---- | ------------------------------------------------------------ | ---- | ------------------------------------------------------------ | ---- |
| [case insensitive](https://tools.suckless.org/dmenu/patches/case-insensitive/) | ✔️    | [json](https://tools.suckless.org/dmenu/patches/json/)       |      | [prefix completition](https://tools.suckless.org/dmenu/patches/prefix-completion/) |      |
| [center](https://tools.suckless.org/dmenu/patches/center/)   | ✔️    | [line height](https://tools.suckless.org/dmenu/patches/line-height/) |      | [preselect](https://tools.suckless.org/dmenu/patches/preselect/) |      |
| [dynamic options](https://tools.suckless.org/dmenu/patches/dynamicoptions/) | ✔️    | [managed](https://tools.suckless.org/dmenu/patches/managed/) |      | [print-input-text](https://tools.suckless.org/dmenu/patches/printinputtext/) |      |
| [fuzzy-highlight](https://tools.suckless.org/dmenu/patches/fuzzyhighlight/) | ✔️    | [more-color](https://tools.suckless.org/dmenu/patches/morecolor/) |      | [reject no match](https://tools.suckless.org/dmenu/patches/reject-no-match/) |      |
| [fuzzy-match](https://tools.suckless.org/dmenu/patches/fuzzymatch/) | ✔️    | [mouse support](https://tools.suckless.org/dmenu/patches/mouse-support/) |      | [scroll](https://tools.suckless.org/dmenu/patches/scroll/)   |      |
| [grid](https://tools.suckless.org/dmenu/patches/grid/)       | ✔️    | [multi selection](https://tools.suckless.org/dmenu/patches/multi-selection/) |      | [symbols](https://tools.suckless.org/dmenu/patches/symbols/) |      |
| [xyw](https://tools.suckless.org/dmenu/patches/xyw/)         |      | [nav-history](https://tools.suckless.org/dmenu/patches/navhistory/) |      | [vertfull](https://tools.suckless.org/dmenu/patches/vertfull/) |      |
| [high-priority](https://tools.suckless.org/dmenu/patches/highpriority/) |      | [non blocking stdin](https://tools.suckless.org/dmenu/patches/non_blocking_stdin/) |      | [x-resources](https://tools.suckless.org/dmenu/patches/xresources/) |      |
| [incremental](https://tools.suckless.org/dmenu/patches/incremental/) |      | [numbers](https://tools.suckless.org/dmenu/patches/numbers/) |      | [highlight](https://tools.suckless.org/dmenu/patches/highlight/) |      |
| [initial-text](https://tools.suckless.org/dmenu/patches/initialtext/) |      | [password](https://tools.suckless.org/dmenu/patches/password/) |      |                                                              |      |



### Scripts

| [dbrowse](https://github.com/clamiax/scripts/blob/master/src/dbrowse) | [passmenu](https://git.zx2c4.com/password-store/tree/contrib/dmenu/passmenu) | [dbdb](https://tools.suckless.org/dmenu/scripts/dbdb.sh) |
| ------------------------------------------------------------ | ------------------------------------------------------------ | -------------------------------------------------------- |
| [dmenu-pass](https://efe.kim/files/scripts/dmenu_pass)       | [passmenu2](https://tools.suckless.org/dmenu/scripts/passmenu2) | [clipmenu](https://github.com/cdown/clipmenu)            |
| [dmenu-path](https://github.com/ema/dotfiles/blob/master/bin/dmenu_path) | [todo](https://tools.suckless.org/dmenu/scripts/todo)        |                                                          |
| [dmenu-run](https://tools.suckless.org/dmenu/scripts/dmenu_run_with_command_history/) (command history) | [via](https://github.com/xalexalex/via)                      |                                                          |
| [dmenu-websearch](https://efe.kim/files/scripts/dmenu_websearch) | [dmenu-run-i](https://tools.suckless.org/dmenu/scripts/dmenu_run_i) |                                                          |
| [mpdmenu](https://github.com/cdown/mpdmenu/blob/master/mpdmenu) | [dmenu-launch](https://github.com/fsilveir/dmenu-launch)     |                                                          |




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

