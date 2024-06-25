/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2020-2022 Gregg E. Berman
 *  
 *  https://github.com/HomeSpan/HomeSpan
 *  
 *  特此授予获得此软件和相关文档文件（“软件”）副本的任何人免费许可，以无限制方式处理软件，
 *  包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许
 *  向其提供软件的人员这样做，但须遵守以下条件：
 *  
 *  上述版权声明和本许可声明均应包含在软件的所有副本或重要部分中。
 *  
 *  软件按“原样”提供，不作任何明示或暗示的保证，包括但不限于适销性、特定用途的适用性和不
 *  侵权性的保证。在任何情况下，作者或版权持有者均不对因软件或使用或其他处理软件而引起的
 *  或与之相关的任何索赔、损害或其他责任承担责任，无论是合同行为、侵权行为还是其他行为。
 *  
 ********************************************************************************/
 
////////////////////////////////////////////////////////////
//                                                        //
//              HomeSpan：ESP32 的 HomeKit 实现           //
//    ------------------------------------------------    //
//                                                        //
//       Example 1: 由基本 HomeSpan 组件构建的未起         //
//                  作用的开/关灯控制                      //
//                                                        //
////////////////////////////////////////////////////////////


  // 欢迎来到 HOMESPAN！
  
// 第一个例子介绍了 HomeSpan 库，并演示了如何使用 HomeSpan Accessory、Service 和 Characteristic 对象的组合来实现简单的开/关灯光控制。
// 一旦将此草图上传到您的 HomeSpan 设备并将设备与您的家配对，一个新的“灯泡”图块将出现在您的 iPhone、iPad 或 Mac 的“家庭”应用中。

// 虽然图块将完全可操作（即您可以将灯泡的状态从“开”或“关”更改为“关”），但我们尚未将实际的灯或 LED 连接到 HomeSpan 设备，因此不会有任何实际的
// 东西亮起。相反，在这个和接下来的几个例子中，我们将重点了解可以配置 HomeKit 控件的不同方式。从示例 5 开始，我们将 LED 连接到设备并介绍从 
// “家庭”应用实际打开和关闭 LED 的方法。

// 注意：所有 HomeSpan 示例最好结合 HomeSpan GitHub 页面上提供的文档进行查看。有关详细信息和参考资料，请参阅 https://github.com/HomeSpan/HomeSpan。
// 特别是，在继续操作之前，您可能需要查看 HomeSpan API 概述页面。

// 这些示例还经常引用 Apple 的 HomeKit 附件协议规范（称为 HAP）。您可以直接从 Apple 下载此文件，网址为
// https://developer.apple.com/support/homekit-accessory-protocol。


// 让我们开始吧...

#include "HomeSpan.h"         // HomeSpan 草图总是从包含 HomeSpan 库开始

void setup() {                //您的 HomeSpan 代码应放在标准 Arduino setup() 函数中
  Serial.begin(115200);       // 启动串行连接，以便您可以接收 HomeSpan 诊断并使用 HomeSpan 的命令行界面 (CLI) 控制设备

  // HomeSpan 库创建一个名为 “homeSpan” 的全局对象，该对象封装了所有 HomeSpan 功能。
  // begin() 方法用于初始化 HomeSpan 并启动所有 HomeSpan 进程。
  
  // 前两个参数是 Category 和 Name，HomeKit 使用它们来配置在首次将 HomeSpan 设备与 iPhone 配对时在“家庭”应用中显示的设备图标和名称。
  
  // 此外，您在下面选择的名称将用作所有附件图块的“默认名称”。首次配对设备时，“家庭”应用将显示此默认名称，并允许您在配对完成之前更改它（针对每个附件图块）。
  // 但是，即使在设备配对后，您也可以随时通过任何图块的设置屏幕直接从 “家庭”应用更改任何附件图块的名称。

  // 重要提示：您在下面选择的名称在所有 HomeSpan 设备上必须是唯一的！

  homeSpan.begin(Category::Lighting,"HomeSpan LightBulb");   // 初始化一个名为 “HomeSpan Lightbulb” 的 HomeSpan 设备，并将类别设置为照明

  // 接下来，我们构建一个简单的 HAP 附件数据库，其中单个附件包含 3 个服务，每个服务都有各自所需的特性。
  
  new SpanAccessory();                              // 首先使用 SpanAccessory() 创建一个新的附件，不需要任何参数

    new Service::AccessoryInformation();            // HAP 要求每个配件都实现配件信息服务

  // 配件信息服务唯一需要的特性是特殊的识别特性。它不需要任何参数：
  
      new Characteristic::Identify();               // 创建所需的识别特征
      
  // 配件信息服务还包括以下四个可选特性。它们不执行任何功能，仅供参考——它们的值显示在 HomeKit 的每个配件的设置面板中。
  // 您可以随意取消注释这些行并实现它们的任意组合，或者根本不实现它们。
                                                      
  // new Characteristic::Manufacturer("HomeSpan");  // 配件制造商（任意文本字符串，每个配件可以相同）
  // new Characteristic::SerialNumber("123-ABC");   // 配件序列号（任意文本字符串，每个配件可以相同）
  // new Characteristic::Model("120-Volt Lamp");    // 配件型号（任意文本字符串，每个配件可以相同）
  // new Characteristic::FirmwareRevision("0.9");   // 配件固件（任意文本字符串，每个配件可以相同）

  // *注意* HAP 要求附件信息服务始终在任何其他服务之前实例化，这就是我们首先创建它的原因。

  // 现在已经定义了所需的“信息”服务，我们终于可以创建我们的灯泡服务了

    new Service::LightBulb();                         // 创建灯泡服务
      new Characteristic::On();                       // 此服务需要“开启”特性来打开和关闭灯

  // 这就是从头定义数据库所需的全部内容，包括所有必需的 HAP 元素，用于控制单个灯泡。当然，此草图还不包含任何代码来实现
  // 灯的实际操作 - 没有任何可以打开和关闭的内容。但您仍会看到“家庭”应用中显示一个灯泡图块，并可以将其打开和关闭。

} // setup() 结束

//////////////////////////////////////

void loop(){

  // 上述设置中的代码实现了附件属性数据库，但不执行任何操作。HomeSpan 本身必须不断轮询以查找来自控制器（例如 iPhone 上的“家庭”应用）
  // 的请求。下面的 poll() 方法就是在 loop() 的每次迭代中连续执行此操作所需的全部内容
  
  homeSpan.poll();         // 运行 HomeSpan!
  
} // loop() 结束

// 恭喜！您已创建第一个 HomeSpan 草图，可以将其上传到 ESP32 开发板并与 HomeKit 配对。
//
//
