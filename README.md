# Intel Yocto Test

build with kas
$ kas build ./build-aa1.yml

alternatively
$ source ./openembedded-core/oe-init-build-env
[NB: this only works, if the build was already setup once by kas, since this
init file is just general initfile to source bitbake environment]

manually, build with bitbake (see .yml files)
$ bitbake image-minimal-hwtest
or
$ bitbake enclustra-image-minimal

