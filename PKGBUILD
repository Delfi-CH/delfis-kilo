# Maintainer: delfi-ch <delfi@delfi.dev>
pkgname=delfis-kilo-git
pkgver=0           # initial placeholder
pkgrel=1
pkgdesc="Clone of kilo with some additional features"
arch=('x86_64')
url="https://github.com/Delfi-CH/delfis-kilo"
license=('BSD-2-Clause')
depends=('glibc')
makedepends=('git')
provides=('delfis-kilo')
conflicts=('delfis-kilo')

source=("git+https://github.com/delfi-ch/delfis-kilo.git#branch=main")
sha256sums=('SKIP')

pkgver() {
    cd "$srcdir/delfis-kilo" || return 1
    echo "r$(git rev-list --count HEAD).$(git rev-parse --short HEAD)"
}

build() {
    cd "$srcdir/delfis-kilo" || return 1
    make
}

package() {
    cd "$srcdir/delfis-kilo" || return 1
    make DESTDIR="$pkgdir" install

    [[ -f LICENSE ]] && install -Dm644 LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}
