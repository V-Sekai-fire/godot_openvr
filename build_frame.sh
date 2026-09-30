#!/bin/bash
# Build godot_openvr for a Godot double-precision engine (e.g. the Steam Frame's
# Windows build run under Proton). Windows x86_64, llvm-mingw. godot-cpp is built
# against the engine's own dumped extension_api.json so the bindings match, and
# openvr_mingw.hpp (tunabrain's ABI patch) is generated if absent.
set -euo pipefail
HERE=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
export PATH="${LLVM_MINGW_BIN:-/c/Users/ernest.lee/scoop/apps/mingw-mstorsjo-llvm-ucrt/current/bin}:$PATH"
GODOT_ENGINE=${GODOT_ENGINE:-/c/b/godot-dbl/bin/godot.windows.editor.double.x86_64.llvm.console.exe}
w() { command -v cygpath >/dev/null 2>&1 && cygpath -w "$1" || echo "$1"; }

mkdir -p "$HERE/build"
( cd "$HERE/build" && "$GODOT_ENGINE" --headless --dump-extension-api )
[ -f "$HERE/openvr/headers/openvr_mingw.hpp" ] || ( cd "$HERE/openvr/headers" && python "$HERE/misc/openvr_mingw_gen.py" )
( cd "$HERE/godot-cpp" && scons platform=windows target=template_debug arch=x86_64 precision=double \
    use_mingw=yes custom_api_file="$(w "$HERE/build/extension_api.json")" -j"${JOBS:-6}" )
( cd "$HERE" && scons platform=windows target=debug bits=64 precision=double use_mingw=yes -j"${JOBS:-6}" )
echo "built: demo/addons/godot-openvr/bin/win64/libgodot_openvr_debug.dll"
