set -e

HERE="$(dirname "$(realpath "$0")")"
pushd $HERE

DIR=".testdir"
meson setup "$DIR" -Db_coverage=true -Dtests=enabled --reconfigure
meson compile -C "$DIR" --clean
meson test -C "$DIR" || true #--wrapper 'valgrind --leak-check=full'
ninja coverage -C "$DIR"

