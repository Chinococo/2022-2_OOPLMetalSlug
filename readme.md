###### tags: `111-2學校上課`
# OOPL 越南大戰
## Git Branch視覺化教學
當你安裝玩Git後，你可以調用以**gitk**
使用步驟:
1. 打開cmd，cd到你專案目錄
2. 打上gitk --all &
3. 你應該會看到以下圖片
![](https://i.imgur.com/MAn7Pei.png)
## Git 指令教學
| 使令目的 | 指令 |
| -------- | -------- | 
| 網路上複製code     | git clone repo.url    |
| 將更新的code加入stash    | git add .    |
| 新增節點    | git commit -am "變更的意義"    |
| 查看目前branch    | git branch    |
| 刪除分ㄖ   | git branch -d  branch-name  |
| 變更自己目前在的branch   | git checkout branch-name    |  變更自己目前在的branch   | git checkout branch-name    | 
|  上傳github(更新master目錄)  | git push    | 
|  上傳github(更新其他目錄，但分支線上存在)  | git push origin branch-name   | 
|  上傳github(更新其他目錄，但分支線上不存在)  | git push --set-upstream origin branch-name  | 
|  合併分支  | git checkout master(母體分支) / git merge 要整併的分支  整併完分支會消失 | 
## 圖表
### 圖片
```mermaid
graph TD
    A(抓取圖片) -->|裁減| B(地圖)
    A(抓取圖片) -->|裁減| C(角色)
    A(抓取圖片) -->|裁減| D(敵人)    
```
### 選單畫面
```mermaid
graph TD
    A(選單) -->|開始遊戲| B(進入遊戲)
    A(選單) -->|多人遊戲| C(2P遊玩)
    A(選單) -->|設定 Game Settings| D(設定畫面)
    D -->|設定| G(設定聲音大小)
    D -->|設定| H(設定按鍵)
    A(選單) -->|選擇關卡| E(進入遊戲)    
    A(選單) -->|結束遊戲| F(關閉遊戲)  
```
### 遊戲運作原理
```mermaid
graph TD
    A(選單) -->|開始遊戲| B(進入遊戲)
    A(選單) -->|遊戲設定 Game Settings| C(聲音)
    A(選單) -->|聲音設定 Game Settings| D(設定聲音大小)
    A(選單) -->|選擇關卡| E(進入遊戲)    
    A(選單) -->|結束遊戲| F(關閉遊戲)  
```
```mermaid
graph TD
    A[載入初始化圖片] --> B[檢查是否有傷害性武器與主角重疊]
    B --> |有| C[讓角色死掉]
    B --> |沒有| D[檢查剩下的傷害性武器]
    D --> E[定時更新敵人動作以及傷害]
    E -->|重新偵測| B
    F[檢查鍵盤是否有接收到訊號] --> |按了上| G[將角色槍口對上]
    F --> |按下| H[將角色蹲下]
    F --> |按右| I[向右移動]
    F --> |按左| J[向左移動 檢查邊界判斷是否可以移動]
    K[地圖控制] --> |可以往前| L[前進]
    K --> |不可回頭| L
```
### 理想開發時間
```mermaid
gantt
    title 遊戲開發工作進度表
    dateFormat  YYYY-MM-DD
    section 選單開發
    選單設定     :active,    des1, 2023-03-20, 3d
    聲音大小控制 :active,    des2,2023-03-20, 3d
    按鍵修改     :active,    des3, after des2, 3d
    關卡選擇畫面 :active, des4,after des2, 3d
    section 重要物件設計
    主角動畫製作 :  active,des5, after des4, 10d
    地圖畫面移動 :  active,des6, after des4, 10d
    section Mission1前半部
    Mission1地圖 :  crit,active,important, after des6, 10d
    基本敵人製作: active,des7, after des6, 3d
    物件(箱子):  active,des8, after des6, 1d
    槍枝(衝鋒槍): active,des9, after des8, 3d
    俘虜製作 :  active,des10, after des9, 3d
    槍枝(火焰槍) : active,des11, after des9, 3d
    敵人(直升機)製作: active,des12, after des11, 3d
    section Mission1後半部
    潛水導彈兵 : active,        des13, after des12, 3d
    物件(石頭) : active,        des14, after des12, 1d
    物件(彈藥箱) :active,       des15, after des14, 1d
    載具(坦克) :  active,       des16, after des13, 3d
    物件(炸藥箱) : active,      des17, after des13, 1d
    BOSS(第一大關) :active,     des18, after des13, 4d
    section Mission2前半部
    Mission2地圖 :  crit,active,important2, after des18, 10d
    士兵(戴盾牌):active,des19,after des18,2d
    士兵(趴下移動):active,des20,after des18,2d
    電擊陷阱:active,des21,after des20,2d
    士兵(傘兵):active,des22,after des20,2d
    載具(敵方坦克):active,des23,after des21,2d
    士兵(傘兵):active,des24,after des21,2d
    槍枝(導彈槍):active,des25,after des24,2d
    載具(船):active,des26,after des24,4d
    section Mission2後半部
    最終BOSS場地:crit,active,des27,after des26,4d
    中BOSS:active,des28,after des26,2d
    最終BOSS:active,des29,after des28,2d
    section Mission3
    Mission3地圖 : crit,active,important3, after des27, 10d
    敵人(艾倫):active,des29,after des27,2d
    士兵(雪球兵):active,des30,after des27,3d
    建築物boss:active,des31,after des30,2d
    特殊機關boss:active,des32,after des30,4d
    槍枝(霰彈槍):active,des33,after des31,2d
    最終boss:active,des34,after des31,5d
    section Mission4
    Mission4地圖 : crit,active,important4, after des34, 10d
    固定式砲台:active,des35,after des34,2d
    大坦克:active,des36,after des35,3d
    最終boss:active,des37,after des36,5d
    section Mission5
    Mission5地圖 : crit,active,important5, after des37, 9d
    敵人(轟炸機):active,des38,after des37,2d
    敵人(牆):active,des39,after des38,2d
    士兵(固定式追蹤飛彈兵):active,des40,after des39,2d
    最終boss:active,des41,after des39,5d
    section final mission
    final mission地圖 : crit,active,important6, after des41, 11d
    敵人(丟鋼筋坦克):active,des42,after des41,2d
    敵人(裝甲坦克):active,des43,after des42,2d
    固定式機槍:active,des44,after des43,2d
    最終boss:active,des45,after des44,5d
```