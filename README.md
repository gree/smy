# SMY

SMY(StateMachine written inYAML) は YAML から StateMachine の状態遷移図、コードを生成するためのツール。

## 特徴

- GREE内製のゲームで使用されていて実績のあるシステム。
- プログラム内部での動作が状態遷移図として可視化されるので仕様の把握、追加実装などのメンテナンスが容易となる。
- YAML で記述されているため追加実装した際の差分がわかりやすい。
- 対応言語はC++、C#(Unity特化)
 - JavaScript版も対応予定。

## インストールするべきもの
YAMLからコード生成やグラフ生成するために以下のものが必要となる。

- graphviz  
`brew install graphviz`

- ruby-graphviz  
`sudo gem install ruby-graphviz`

## 利用方法
### C++版
YAMLを新規作成してStateを作成。既にある場合は編集する。
下記のように元となるStateとそのStateから遷移するStateを記入する。条件がある場合はその旨も記入。
この例だとWaitStartGameのStateからタップした際はStartGameへ遷移する。
```
WaitStartGame:
  StartGame: {when: "タップ"}
```

YAMLが完成したらコンバートしてコードとグラフが生成される。コンバートは以下のコマンド。  
`ruby tool/state2cpp.rb {ステート名}.yml`


コンバートしたらグラフファイルである以下のファイルができる。

- {ステート名}.png
- {ステート名}.pdf
- {ステート名}.svg

ちなみに図は以下のようになる。([smy-flappy-cocos2dx](https://github.com/gree/smy-flappy-cocos2dx)の例)
![](https://raw.githubusercontent.com/gree/smy-flappy-cocos2dx/master/StateMachine/Main.png)

コードは以下のものが生成される。

- {ステート名}.h
- {ステート名}.cpp
- {ステート名}States.h
- {ステート名}States.cpp

{ステート名}.h内で{ステート名}States.hをincludeしており具体的な処理は{ステート名}States.cppに書くことになる。  
メンバ変数等を定義する際は{ステート名}.h内に書くようにする。

*注意*: Stateを変更した時に再度YAMLをいじってコード、グラフを再生成する必要がある。
差分のみが{ステート名}States.hと{ステート名}States.cppに出力されるようになってるので、その差分に追加した処理を書くことになる。

### C#版
C++版と全く同じようにYAMLに記述してコンバートするとグラフとコードが生成される。コンバートは以下のコマンド。  
`ruby tool/state2unity.rb {ステート名}.yml`

グラフは全く同じものができ、コードは以下のものができる。
- {ステート名}.cs
- {ステート名}States.cs

partialクラスを使っていてC++版と同じように具体的な処理は{ステート名}States.csに書き、メンバ変数等を定義する際は{ステート名}.cs内に書くようにする。

## サンプル
- [smy-flappy-cocos2dx](https://github.com/gree/smy-flappy-cocos2dx)
 - cocos2d版SMY で作ったFlappyBird風のサンプル。
- [smy-flappy-unity](https://github.com/gree/smy-flappy-unity)
 - unity版SMY で作ったFlappyBird風のサンプル。

## ライセンス

Copyright (c) 2016 GREE, Inc.

MIT License
