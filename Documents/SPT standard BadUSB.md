# **Science Projects Terminal Standard BadUSB**
#### _Document Version:Original-Alpha 1.0  Editing date:2023/08/23_
***

>### **IDEA:**
>>* To enable some members to master the ability could collect more information 
in life,it's meaningful to design a convenient and portable mini tool.Therefore,
we are setting about making some BadUSB tools and then our members own much feats could exchange it.Besides,we suggest that the members studying at school exchange this,because we need you try your best to hack class teachers' computer and as far as possible to collect information of others.
>>* [Collect information as more as possible is for building a people contacting net that we can use social engineer to bring more convenience and profits to our 
organization and all the members.]
>### **DESIGN:**
>>1. To make a mini BadUSB tool,we decided to use the _Digispark kickstarter_-**Atinay85*** development board,it is mini and convenient to develop,although it's price is about 15 yuan.(About 2 dollar)
>>2. For the code of all the functions,we chose Arduino Framework to edit and develop it,because it's so suitable for the Atinay85 and language it used is C++,it was used very widely and easy for our members to understand and study.
>>3. First of all,to prepare our edition,we need to add the additional board url to the [ArduinoIDE] -> [Preferences] -> [Additional Boards Manager URLs].
>>4. Besides,h.After we add the describe file to the manager,we can import the sample file into our workspace and then see the core library of our code developing is a Arduino library called DigKeyboard.
* Describe Files' URL http://digistump.com/package_digistump_index.json
* [Digis Drive Release - Github Repository](https://github.com/digistump/DigistumpArduino/releases)

```C++
#include <DigKeyBoard.h> 
```

>### **END:**
>>* After we referring the sample file,it is easy to know there are a lot of class packages about the key macro,we just need to import the definitions in need.All in all,what function do we want decided how the code we write.
>>* Additionally,to make the BadUSB's performance develop to max, we can add the **ESP12-F** chip into our plan or use ESP Board directly to enable the BadUSB be controlled by ourself via phone or other SPT smart device such as Smart glove based on using _ESP-NOw_ protocol. 

### _Expected Every Version's function Referring Table_

|FUNCTIONS|FORMAL|PRO|PLUS|
|  :----:  | :----:  |:----:|:----:|
| Price| 2$|4$|6$|
|Mini|√|√|×|
|BadUSB|√|√|√|
| HID Hack*| √|√|√|
|Remote Control|× |√ |√|
|Attack Log|×|√|√|
|Station Link|×|×|√|
|BlueTooth|×|×|√|
|Password Bomb|×|×|√|
|Battery|×|×|√|
|Hall Start|×|×|√|

##### Completed time:2023/08/23-22:23 Version Alpha 1.0