# cservice_template

[[Build status](http://bamboo.niias/browse/TOOL-CSERVICEBUILD/latest)]
[[Tests status](http://bamboo.niias/browse/TOOL-CSERVICEBUILD/test)]
[[License](./doc/LICENSE.md)]


Service for ...

**cservice_template** is the software designed for ... It is developed based on C++17 and provides easy-to-use API. With **cservice_template**, users can quickly connect to ..., receive ... data and transmit decision via ....

---

## Table of contents

1.  [ Overview ](#overview)
2.  [ Dependencies ](#dependencies)
3.  [ Installation ](#installation)
4.  [ Run ](#run)
5.  [ Tests ](#tests)
6.  [ Release History ](#release)
7.  [ Contributing ](#contributing)
8.  [ Support ](#support)
9.  [ License ](#license)
10. [ FAQ ](#faq)

---

<a name="overview"></a>
## 1. Overview

A service is a template for proper use by developers within a company. The number of services is constantly growing, however, their base remains unchanged. In the current repository, the author has tried to simplify many routine tasks when creating a new repository, including: automatic code documentation, static analysis, code coverage with Unit-tests, the use of generally accepted company submodules to interact with other services in the system.

---

<a name="dependencies"></a>
## 2. Dependencies

Basic:<br>

- [build-essential](https://packages.debian.org/ru/sid/build-essential)
- [C++17 (GCC-8, G++-8)](https://en.cppreference.com/w/cpp/17)
- [CMake (> 3.10)](https://cmake.org)
- [Make (> 4.2)](https://en.wikipedia.org/wiki/Make_(software))
- [LCov (> 1.14)](http://ltp.sourceforge.net/coverage/lcov.php)
- [GCov (>9.3)](https://linux.die.net/man/1/gcov)
- [CLang-Tidy (> 10.0)](https://clang.llvm.org/extra/clang-tidy/)
- [Ninja (> 1.10)](https://ninja-build.org)

Third-party (for visualization):<br>

- [Doxygen (> 1.8)](https://www.doxygen.nl/index.html)
- [Graphviz](https://graphviz.org)
- [Latex](https://www.latex-project.org/get/)
- [Tree](https://pingvinus.ru/note/tree)
- [PCL (> 1.10)](https://pointclouds.org)

---

<a name="installation"></a>
## 3. [Installation](./doc/INSTALL.md)

The installation procedures in Linux Ubuntu 16.04/14.04 32-bit LTS or Linux Mint 19.* /20. * 64-bit are shown [here](./doc/INSTALL.md) as examples.

---

<a name="run"></a>
## 4. Run

Make changes according to task in [configuration file](./cfg).

```
cd cservice_template
git checkout release
```
Without [visualization](./doc/README.md): ```./scripts/build.sh``` <br>
With [visualization](./doc/README.md): ```./scripts/build-gui.sh```

```
./scripts/run.sh
```

Or using [Qt Creator IDE](https://www.qt.io/download):


Without [visualization](./doc/README.md): **Projects->Run->.*-c ../cservice_template/cfg/cservice_template.cfg -p /tmp/niias/cservice_template<br>

With [visualization](./doc/README.md): <br>
- *Projects->Build->CMake->GUI->ON->Apply Configuration Changes* <br>
- *Projects->Run->* ```-c ../cservice_template/cfg/cservice_template.cfg -p /tmp/niias/cservice_template``` <br>

You can find more scripts in [scripts/](./scripts).

---

<a name="tests"></a>
## 5. [Tests](./tests/README.md)

---

<a name="release"></a>
## 6. [Release History](./doc/HISTORY.md)

---

<a name="contributing"></a>
## 7. Contributing

1. Fork it (<http://bb.niias/projects/TOOL/repos/cservice_template/browse>).
2. Read [Readme](./README.md), [License](./doc/LICENSE.md), [Code of Conduct](./doc/CODE_OF_CONDUCT.md) and [Condributing Guidelines][contributing].
3. Create your fix or feature branch (`git checkout -b feature/name`).
4. Make changes according to [Condributing Guidelines][contributing].
5. Make unit tests.
6. Build repo and tests.
7. Correct Readmes for whole directories.
8. Ensure that it is likely to be merged.
9. Commit your changes (```git add . & git commit -m "Feature. Add wrapper class WrapperClass."```).
10. Push to the branch (```git push origin feature/new-wrapper-class```)
11. Create a new Pull Request to `develop`

---

<a name="support"></a>
## 8. Support

Reach out to me at one of the following places!

- Telegram at - <a href="http://https://telegram.org" target="_blank">`@DLeliuhin`</a>
- Email at - dleliuhin@gmail.com.

---

<a name="license"></a>
## 9. [License](./doc/LICENSE.md)

---

<a name="faq"></a>
## 10. [FAQ](doc/FAQ.md)

---

[contributing]: http://confluence.niias/pages/viewpage.action?pageId=7340222

---

**JSC NIIAS**