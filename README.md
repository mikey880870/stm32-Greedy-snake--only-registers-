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
2.食物生成為隨機生成，透過計算TIM2的ARR值而得。
3.使用 ADC3 的 IN10、IN11 讀取 HW504 的 VRx 及 VRy，且須使用連續轉換及掃瞄模式
4.因為使用的 ADC 模式為一般通道，故須搭配 DMA 讀取 ADC Data
5.使用 IWDG 確保程式可正常行
