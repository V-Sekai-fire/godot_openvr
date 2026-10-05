# Third-party libraries

Libraries vendored in this directory, with their upstream version and licence.

## openvr

- Upstream: https://github.com/ValveSoftware/openvr
- Version: v2.5.1 (ae46a8dd0172580648c8922658a100439115d3eb)
- License: BSD-3-Clause
- Kept: `LICENSE`, `README.md`, `headers/`, and `bin/` and `lib/` for `win32`, `win64`,
  `linux32` and `linux64`

A squashed git subtree of a single commit holding only the kept paths, each file the tag's
blob unchanged. The rest of the tag is not vendored: `samples/` with its prebuilt
third-party binaries, `src/`, `codegen/`, `controller_callouts/`, `docs/`, the CMake files,
`.gitattributes`, and the `androidarm64`, `linuxarm64` and `osx32` libraries, since the
extension builds for Windows and Linux only.

To move to a new tag, make the same single commit from it and pull that commit:

    git subtree pull --prefix=thirdparty/openvr <trimmed repo> <branch> --squash

Pulling the upstream tag directly vendors the whole tag again.

## openvr_mingw

- Source: `openvr_mingw.hpp`, generated from `openvr/headers/openvr.h` at v2.5.1 by
  `misc/openvr_mingw_gen.py`
- License: BSD-3-Clause (the OpenVR header it rewrites); the generator script is MIT

Regenerate it whenever the openvr subtree moves to a new tag.
