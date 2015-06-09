# lcdapi

## Synopsis

C++ API for lcdproc clients, original project at http://www.c-sait.net/lcdapi/

Now at https://github.com/spdawson/lcdapi

## Requirements

This software requires the following packages:

<ul>
  <li>pthread library</li>
  <li>socket library</li>
  <li>graphviz</li>
  <li>doxygen</li>
</ul>

If doxygen or graphviz are not installed, the documentation will not be generated and building may fail.

## Getting started

Assuming that the latest version is `X.Y`:

```sh
tar xaf lcdapi-X.Y.tar.gz
cd lcdapi-X.Y
libtoolize --force
autoreconf -i
./configure
make
sudo make install
```
