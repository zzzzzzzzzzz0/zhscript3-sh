+ 式微，式微！胡不归？
+ 不行了，不行了，你怎么还在写程序？

###### zhscript3-sh

未见有中文脚本第三版，何得以有其外壳？第三版本意从 zhscript2-no-std-rust 之 no 之 features 而来，然则……

世事如灼龟，孰能知其裂所向乎

### 开三工鸟

以下三个可共用文件却在另两个项目，全取太费，各单保留一份又悖念，终只得麻烦行编译者按“途”索骥了

```
zhscript/gjke4/rust.h
zhscript2-rust-sh/webkitx/src/Chan.cpp
zhscript2-rust-sh/webkitx/src/Chan.h
```

```bash
$ apt install g++ make libvte-2.91-dev libgtksourceview-3.0-dev # 或 libwebkit2gtk-4.0-dev 
$ make -C gtkBsh/
$ make -C plugin/gtkBsh/webkit/
$ make -C plugin/gtkBsh/vte/
$ make -C plugin/gtkBsh/src/
```

使能运行尚需解释器在在，也便难免悉数一番

```bash
$ cd .. # 至项目上一级
$ git clone "https://github.com/zzzzzzzzzzz0/zhscript2-rust.git"
$ git clone "https://github.com/zzzzzzzzzzz0/zs2-l4-rust.git"
$ git clone "https://github.com/zzzzzzzzzzz0/l4-rust.git"
$ cd l4-rust
$ cargo build
$ cd ../zhscript3-sh
$ ln -s ../../../l4-rust/target/debug/libl4.so target/debug/l4.so
```

始测试

```bash
$ ./target/debug/gtkBsh test/gtkBsh/1.zhscript
```

若出现一个满是编辑区、终端和网页的窗口，果真乃“人生如初见”，否……好在人生非棋局，虽起落无悔但重来大可

另上发布版步骤

```bash
$ make -C gtkBsh/ d=release f=-O3 
$ make -C plugin/gtkBsh/webkit/ d=release f=-O3 
$ make -C plugin/gtkBsh/vte/ d=release f=-O3 
$ make -C plugin/gtkBsh/src/ d=release f=-O3 
```

##### gtkBsh

“乙壳”

把脚本做为界面描述语言的命令参数式的通用 gui 程序

目前支持“终端”、“网页”、“源码”三种视图（插件）

装载的解释器是锈版贰点零再置一套既“平铺直叙”又“矫翩回调”的接口

