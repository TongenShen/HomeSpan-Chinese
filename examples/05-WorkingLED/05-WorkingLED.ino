////////////////////////////////////////////////////////////
//                                                        //
//              HomeSpan：ESP32 的 HomeKit 实现           //
//    ------------------------------------------------    //
//                                                        //
//     示例 5：基于 LightBulb 服务的两个工作开/关 LED       //
//                                                        //
//                                                        //
////////////////////////////////////////////////////////////


#include "HomeSpan.h" 
#include "DEV_LED.h"          // 新功能！包括这个新文件 DEV_LED.h，下面将对其进行全面解释

void setup() {

  // 第一盏灯！通过 HomeKit 控制 LED！
  // 示例 5 在示例 2 的基础上进行了扩展，添加了实际控制从 HomeKit 连接到 ESP32 的 LED 所需的代码。在示例 2 中，我们构建了所有功能，
  // 以在 HomeKit 内部创建显示开/关灯的“Tile”配件，但这些控制实际上并未对 ESP32 进行任何操作。要操作实际设备，需要对 HomeSpan 进行编程，
  // 使其通过执行某种形式的操作来响应来自 HomeKit 的“更新”请求。

  // 虽然 HomeKit 本身会向各个特性发送“更新”请求，但这并不直观，并且当服务具有多个特性（例如“开”和“亮度”）时，会导致复杂的编码要求。
  // 为了让用户更容易做到这一点，HomeSpan 使用了一个更新服务的框架，而不是更新单个特性。它通过调用每个服务的 update() 方法来实现这一点，
  // 并使用标志指示 HomeKit 请求更新的该服务中的所有特性。用户只需实现代码来执行实际操作，如果更新成功，则返回 true 或 false。
  // HomeSpan 负责所有底层细节。

  // HomeKit 中定义的每项服务，例如 Service:LightBulb 和 Service:Fan（甚至 Service::AccessoryInformation）都实现了 update() 方法，
  // 默认情况下，该方法不执行任何操作，只返回 true 值。要实际操作真实设备，您需要使用自己的代码覆盖此默认 update() 方法。最简单的方法是
  // 基于内置 HomeSpan 服务之一创建 DERIVED 类。在此派生类中，您可以执行初始设置例程（如果需要），使用自己的代码覆盖 update() 方法，
  // 甚至创建完全操作复杂设备所需的任何其他方法或特定于类的变量。最重要的是，派生类可以接受参数，以便您可以使它们更通用，多次重复使用
  // 它们（如下所示），并将它们转换为独立模块（也如下所示）。

  // HomeSpan 实现的所有 HomeKit 服务都可以在 Services.h 文件中找到。任何服务都可以用作派生服务的父级。

  // 我们首先重复与示例 2 几乎相同的代码，但有一些关键更改。为了便于阅读，删除了仅重复示例 2 的行中的所有先前注释，并添加了新注释以明确显示新代码。
  

  Serial.begin(115200);

  homeSpan.begin(Category::Lighting,"HomeSpan LED");
  
  new SpanAccessory(); 
  
    new Service::AccessoryInformation(); 
      new Characteristic::Identify();                

  //  在示例 2 中，我们在此处实例化了 LightBulb 服务及其“开启”特性。我们现在将替换这两行（通过注释掉它们）...

  //  new Service::LightBulb();                   
  //    new Characteristic::On();                 

  // ...使用一行新代码来实例化一个新类，我们将调用 DEV_LED()：

    new DEV_LED(16);        // 这将实例化一个新的 LED 服务。它在哪里定义？Characteristic::On 发生了什么？继续阅读...

  // DEV_LED 的完整定义和代码在名为“DEV_LED.h”的单独文件中实现，该文件使用此程序顶部的 #include 指定。
  // 前缀 DEV_ 不是必需的，但在命名所有设备特定服务时，这是一个有用的惯例。请注意，DEV_LED 将包含服务的所有必需特性，
  // 因此您不必单独实例化 Characteristic::On --- HomeSpan 为 DEV_LED 所需的一切都应该在 DEV_LED 本身中实现（尽管并不是那么多）。
  // 最后，请注意，我们创建 DEV_LED 来接受单个整数参数。如果您猜这是您已连接 LED 的引脚的编号，那么您是对的。
  // 请参阅 DEV_LED.h 以了解其工作原理的完整说明。

  new SpanAccessory(); 
  
    new Service::AccessoryInformation();    
      new Characteristic::Identify();                       

  //  new Service::LightBulb();                       // 同上，删除此行...
  //    new Characteristic::On();                     // 此行也被删除..
  
    new DEV_LED(17);                                  // ...并用一行代码替换，该代码在引脚 17 上实例化第二个 DEV_LED 服务

} // setup() 结束

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();
  
} // loop() 结束
