# Third-party libraries

Libraries vendored in this directory, with their upstream version and licence.

## openvr

- Upstream: https://github.com/ValveSoftware/openvr
- Version: v2.5.1 (ae46a8dd0172580648c8922658a100439115d3eb)
- License: BSD-3-Clause

A squashed git subtree of the tag, kept as upstream ships it. Update it with:

    git subtree pull --prefix=thirdparty/openvr https://github.com/ValveSoftware/openvr <tag> --squash

Upstream's `samples/` carries prebuilt third-party binaries under their own licences; the
extension builds only against `headers/`, `lib/` and `bin/`.

## openvr_mingw

- Source: `openvr_mingw.hpp`, generated from `openvr/headers/openvr.h` at v2.5.1 by
  `misc/openvr_mingw_gen.py`
- License: BSD-3-Clause (the OpenVR header it rewrites); the generator script is MIT

Regenerate it whenever the openvr subtree moves to a new tag.
