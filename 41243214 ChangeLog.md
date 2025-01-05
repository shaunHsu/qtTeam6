#
12/20<br>
使用方式: scan->選擇資料夾(直接選，內容檔案不會顯示)->mp3檔匯到Tracks Tab
可以手動選擇(裝mp3檔的)資料夾 (不確定filter有沒有用<br>
前/後按鈕會自動開始播放，暫停跟STOP都有用<br>
左邊留著放更多功能按鈕<br>
今天沒時間放註解了 累死 (12/20 01:33)<br>
![圖片](https://github.com/user-attachments/assets/584e4850-1859-4a0f-ad84-20967120fabd)
##
12/21<br>
新增自動下一首功能，連結signal:mediastatuschanged到函式autoplayNext()判斷如果為EndofMedia就往下一列移動後開始播放
##
12/22<br>
結合play跟pause按鈕，onClicked()會判斷player->playbackState():<br>
事前判斷: 如果當前選擇的列不為記錄列，表示暫停時重新選了一首播放-->重新載入metadata<br>
QMediaPlayer::StoppedState: 目前沒有播放東西，紀錄目前選擇的列並播放<br>
QMediaPlayer::PlayingStateplaying: 目前有在播放東西，暫停<br>
QMediaPlayer::PausedState:  目前暫停中，繼續播放<br>
就算在暫停中移動進度拉條，拉條訊號也會即時更新播放進度，不用擔心繼續播放時player還在舊位置<br>
##
1/3<br>
更改歌曲加入的方式，新歌曲會被加到目前的歌單後面，加入完後會執行一次掃描，路徑重複的檔案會被移除<br>
加入雙擊播放功能<br>
UI改動:<br>
mainlayout延伸<br>
tab物件延伸<br>
IDE中qDebug訊息補充<br>
![圖片](https://github.com/user-attachments/assets/0dd66382-18ed-43be-8072-b1811a151369)
##
1/5<br>
套用歌詞搜尋API，搜尋結果會先儲存至txt/html檔案再由tab2的QtextBrowser設置<br>
目前因為請求回應有延遲所以會讀取舊版本的檔案<br>
![圖片](https://github.com/user-attachments/assets/37b74536-9cc1-4ea1-a36d-546b336b99e5)
##
1/6<br>
加入timer解決API延遲問題，獲取完成後程式會等待10秒再載入HTML檔案<br>
fix: 在自動換首時也會觸發API<br>
![Screenshot 2025-01-06 065744](https://github.com/user-attachments/assets/924a740d-5cfb-4975-accc-c8cbc03542b7)<br>
![Screenshot 2025-01-06 070011](https://github.com/user-attachments/assets/0f9f3059-ccbf-4cb9-95fa-48d9785dc91b)
