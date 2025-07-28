set -e

cleanup() {
    if [ -n "$dir" ]; then
        popd || true
    fi
}
trap cleanup EXIT

dir=$(dirname $0)
pushd $dir

meson setup build -Db_coverage=true --reconfigure
meson compile -C build --clean
meson test -C build #--wrapper 'valgrind --leak-check=full'
ninja coverage -C build

