# stm32 Greedy snake (only registers)
程式功能:使用STM32控制Joystick及8*8點矩陣實現貪食蛇遊戲
硬體方面:

1.Joystick (HW504):

輸入電壓:5V
VRx及VRy為ADC接腳，可以透過STM32 ADC功能讀取數值。以判斷上下左右。
![下載](https://github.com/mikey880870/stm32-Greedy-snake--only-registers-/assets/127172104/964ced73-16e8-4005-825b-2e5f071e363e)

2.Max7219 8*8 點矩陣

輸入電壓:3~5V
控制腳位:DIN（數據輸入），CS，和 CLK（時鐘）
![下載 (1)](https://github.com/mikey880870/stm32-Greedy-snake--only-registers-/assets/127172104/4e72ea5b-124c-439b-b8b4-77c69fb8747f)

3.UART(FT232):

透過STM32 TX RX 控制用於及時查看數據及除錯用。

程式方面:

1.貪食蛇主體及食物:透過 struct food_s 及 struct snake_s，判斷食物及貪食蛇狀態，詳細程式於"snake_helperFunc"

2.食物生成為隨機生成，透過計算TIM2的ARR值而得

3.使用 ADC3 的 IN10、IN11 讀取 HW504 的 VRx 及 VRy，且須使用連續轉換及掃瞄模式

4.因為使用的 ADC 模式為一般通道，故須搭配 DMA 讀取 ADC Data

5.使用 IWDG 確保程式可正常行

/  程式流程  /
貪食蛇遊戲主要流程：

1.系統初始化：
初始化硬體設備，包括 Joystick、8x8 點矩陣顯示器（Max7219）和 UART 通訊。
配置 ADC3 以讀取 Joystick 的 VRx 和 VRy 值，並啟用 DMA 進行數據傳輸。
啟動獨立看門狗（IWDG）以確保系統穩定運行。

2.遊戲開始：
在點矩陣上顯示初始的貪食蛇和食物位置。
設置初始遊戲參數，如蛇的長度、方向和速度。

3.遊戲主循環：
讀取輸入： 通過 ADC 和 DMA 讀取 Joystick 的位置，判斷玩家的操作方向。
更新蛇的位置： 根據玩家的操作更新蛇的方向和位置。
檢查碰撞：
如果蛇撞到牆壁或自身，遊戲結束。
如果蛇吃到食物，增加蛇的長度，並隨機生成新的食物。
更新顯示： 在點矩陣上刷新蛇和食物的位置。
餵狗： 重置看門狗計時器以防止系統復位。

4.遊戲結束：
在點矩陣上顯示遊戲結束的提示信息。
等待玩家的重新啟動操作。
