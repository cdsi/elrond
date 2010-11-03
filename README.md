Elrond -- helps to integrate Python applications and C libraries
===

Elrond contains a C library that provides a common set of routines
used in other applications. These are mostly wrappers around
[GLib](http://library.gnome.org/devel/glib/), and routines that allow
shared-memory to be accessed by C and Python applications.

Elrond also contains some "generic" Python PyGTK+ widgets that, for
exmaple, allow text output to be displayed in a window via a simple
pipe.

## INSTALLATION

    git clone git@github.com:cdsi/elrond.git elrond/git-repo
    cd elrond
    git-new-workdir git-repo unstable unstable

Please note that "elrond/unstable" is required by the packages that
depend upon elrond. This allows multiple versions of elrond to be
installed into well-known locations using [Semantic
Versioning](http://semver.org) where "unstable", "stable", and
"testing" are links to appropriate tags and/or branches.

## BUILD

    cd elrond/unstable
    yes | ./build.sh

## REQUIREMENTS

 * [Sam v1.0.0](http://github.com/cdsi/sam)

## CONTRIBUTE

[cdsi-lotr@googlegroups.com](mailto:cdsi-lotr@googlegroups.com)

## LICENSE

Elrond is available under the MIT License.
