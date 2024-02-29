# Lempel-Ziv Decomposition, `lzd`

## Description
The program `lzd` demonstrates the [Lempel-Ziv decomposition](https://ieeexplore.ieee.org/document/1055714) and the
match factor decomposition used in
[`macle`](http://github.com/evolbioinf/macle). It is based on a [modern
algorithm](https://ieeexplore.ieee.org/document/4483326) for
calculating the Lempel-Ziv decomposition and shows the internal data
structures used by the algorithm, including the suffix array.

## Author
[Bernhard Haubold](http://guanine.evolbio.mpg.de/), `haubold@evolbio.mpg.de`

## Make the Program
Make sure you've installed the package `libdivsufsort-dev`. Then execute

`$ make`

The directory `bin` now contains the program `lzd`.
## Make the Documentation
Make sure you have a working TeX installation, for example by
installing the package `texlive`. Then execute

`$ make doc`

The documentation is now in `doc/lzdDoc.pdf`.
## License
[GNU General Public License](https://www.gnu.org/licenses/gpl.html)
