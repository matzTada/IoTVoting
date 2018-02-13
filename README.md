# IoTVoting

IoT教育向け投票システム  
ボタンを押した回数に対応してフルカラーLEDの色が変わる．複数ノードから無線通信で色情報を一か所に収集し，視覚化する．色のコントロールを遠隔で行うことも可能．

<a><img src="https://github.com/matzTada/IoTVoting/blob/master/image/working_client.jpg" alt="working_client" width=40%></a>
<a><img src="https://github.com/matzTada/IoTVoting/blob/master/image/working_server.jpg" alt="working_server" width=40%></a>

[IoTLiteracyEdu](https://github.com/matzTada/IoTLiteracyEdu)プロジェクトの後継版  
技術面での変更点

* データベースの廃止→プログラム間のソケット通信に変更
* XBee通信のちょっとした改良(WandWoFulも参考に)
* プログラムの簡略化

## やっていること，できること

* クライアント側
	* R,G,Bに対応して一つずつボタンがある
	* ボタンを押した回数に対応してフルカラーLEDの色が変わる
	* LEDの状態（色）を定期的にサーバに送信
* サーバ側
	* クライアント側からのデータを視覚化
	* クライアント側に色情報を一斉送信（コントロールできる）


## 考えられる遊び方

* 一番多い色を集計し，すべてのノードをその色に塗り替える
* 表現できる色それぞれに選択肢を対応付けて投票する
	* 例えば，「お題：好きな果物，選択肢：赤＝リンゴ，緑＝メロン，青＝それ以外」　など
	* 「好きな教科」「好きなスポーツ」「好きな言語」等なんでもできる．
* まわりの人と色を合わせるには
	* プロトコルの考えにもつながる
	* 相談あり，相談なし，事前にルールを決める，隣の人の色しかわからない等の応用が利く
* てかまあ，情報教育としてじゃなくて，単になんかしらの投票するときとか面白いかもね．

## 主要登場人物とつながり

* クライアント側
	* Arduino
	* XBee (ZigBee)
	* Full Color LED (3色LED)
	* Tact switch
* サーバー側
	* Raspberry Pi (別にラズパイじゃなくても可)
	* XBee (ZigBee)
	* Processing
	* Python

<a><img src="https://github.com/matzTada/IoTVoting/blob/master/image/system.png" alt="system" width=100%></a>

## クライアントノード配線

<a><img src="https://github.com/matzTada/IoTVoting/blob/master/fritzing/wiring.png" alt="wiring" width=50%></a>


## 授業に入る前の準備手順

1. Arduinoのノードを配線する
2. ```arduino/mode```以下のプログラムを理解する
3. クライアント側ノードをテストする
	3. ```arduino/mode/mote.inoと同じディレクトリのファイル```をArduino IDEで開き，これをArduinoに焼く
	1. LEDが光るか
	2. ボタンを押してカウントができているか
	3. ボタンを押したらLEDの色が変わるか
2. XBeeの設定
	1. XBeeにテプラなどでIDを貼り、アドレスとの対応をメモっておく
	2. X-CTUのインストール
	3. X-CTUでFirmwareの設定
		1. Coordinatorはネットワークに一つ，他は全部Router
		2. PAN IDをそろえる（そろってないと当たり前のように通信できない）
		3. API enable = 2にする．ライブラリの都合上結構な大事
4. XBeeの通信テスト
	1. 送信はArduinoプログラム（送信先アドレスをCoordinatorに合わせる）
	2. 受信（CoordinatorをPCなりRasPiなりに接続）
		1. X-CTUの端末でみてみる
		3. Pythonで受けてみる（Serialライブラリを使う）
3. ソケット通信テスト
	1. PythonでUDP通信してみる
	2. ProcessingでUDP通信してみる
	3. PythonとProcessingの間でUDP通信してみる
3. サーバ側Controllerのテスト
	1. ```/python/controller.py```を試す
	1. クライアント側からデータを受信できているか
	2. 受信したデータをUDPで送信できているか
3. サーバ側Visualizerのテスト
	1. ```/processing/visualizer/visualizer.pdeと同じディレクトリのファイル```をProcessing IDEで開く
	2. UDPで受信できているか
	3. 視覚化できているか
4. クライアント側をコントロールできているか試す
