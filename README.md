<h1 style="text-align:center"><strong>CustomSDK</strong></h1>

1. ## 简单介绍
   本项目建立初衷:
   * 建立一个用于帮助C++初学者(学过语法,能独立写一些小型的程序)向工业化(**配置文件**|**日志**|**软件架构**|**开源框架**|**源码管理**等多方面结合)过渡的示例框架项目(**不包含具体业务,追求尽可能通用**),减少此阶段无人引路造成的迷茫感
   * 不断整理一些通用但不常用的代码示例写法,绝大多数程序员是做不到把写过/见过的代码完全永久地记在脑子里的,也没必要,只需要做到:**遇到类似需求->能够想起自己做过->能快速找到在哪->能将旧代码改写以适配新需求**,就已经很好了

   **关键词**:**boost**、**qt**、**跨平台**、**插件化**、**跨语言调用(swig)**、**cmake**、**shell**、**git**

   **适用对象**:热爱编程、有一定归纳能力、敢于折腾但无具体方向的初学者

   **声明:此项目基于兴趣建立,仅用于参考,需辩证性使用,作者不保证内容绝对通用**

2. ## 目录结构说明
   | 文件(夹)   | 内容描述                                                 | 备注 |
   | :--------- | :------------------------------------------------------- | :--: |
   | bin        | SDK核心动态库、工具、服务等                              |      |
   | etc        | 自带工具初始化配置文件                                   |      |
   | include    | 二次开发必需头文件                                       |      |
   | lib        | 二次开发必需链接库                                       |      |
   | plugins    | 插件(按目录区分不同用途)                                 |      |
   | tools      | 二次开发用辅助工具                                       |      |
   | thirdparty | 第三方库支持                                             |      |
   | examples   | 示例程序(源代码、配置文件、构建脚本等)                   |      |
   | test       | 测试用程序、配置文件、运行脚本等                         |      |
   | src        | 源码、构建脚本等(**若提供则应该尽量做到拿来即用**)       |      |
   | doc        | 使用说明、开发手册(**应做到尽可能详尽且随版本同步更新**) |      |
   | README.md  | SDK目录结构说明、产品介绍、版本更新日志等                |      |
3. ## 源码构建说明
   1. 编译环境准备
      本项目主要用到的构建工具以及第三方库如下(版本不做要求,默认按最新版本,若出现问题,请锻炼一下自己的折腾能力):
      * **必需(核心框架库所需)**:**cmake**、**boost**、**qt**、**pugixml**、**spdlog**
      * 可选(一些简单使用示例插件所需):**nlohmann-json**、**qrencode**、**cmark-gfm**、**openssl**、**opencv**
      * 可选(跨语言调用支持):swig、python、jdk
      
      本项目的构建基于CMake构建工具并且编写了一份CMake模块("src/CustomSDK/module.cmake")以便于快速构建不同类型子项,需要使用者遵守一定的规则(此处仅简单说明,进一步请自学CMake语法做到能够完全读懂甚至优化所提供的模块文件):
      1. 项目所需第三方库,应置于统一目录进行管理,并配置环境变量(ThirdParty)指定为对应目录:

         例:
         * /path/to/thirdparty
            * pugixml
               * include
               * lib
            * boost
               * include
               * lib
            * qt
               * include
               * lib
         
         **注:qt 和 boost 需单独使用"QT_DIR"、"BOOST_DIR"环境变量指定路径**

         建议使用**vcpkg**(Windows)/**homebrew**(Mac)管理用到的三方库

      2. 一般地,对于每个具体的子项(CMakeTarget),其目录结构也尽量保持一致

         例:
         * /path/to/target
            * include
               * target
            * src
            * resource
            * CMakeLists.txt
         * CMakeLists.txt
      
   2. 源码编译&安装
      对于初学者而言,建议使用IDE而非直接在linux命令行之类直接命令编译,建议使用的IDE为:**VisualStudio**/**CLion**:
      1. **VisualStudio**:
         "src/scripts"目录下预备了一些简单的构建脚本,按文件名选择适合自己开发环境的执行,即可在"src/build"对应目录下生成构建目录,VisualStudio打开构建目录中的解决方案文件(*.sln)
      2. **CLion**:
         使用CLion指定项目文件"src/CustomSDK/CMakeLists.txt"打开工作区
      
      按上述操作即可以直观地看到项目的目录结构,按IDE默认操作编译即可

      **注:执行编译安装(“Install”),默认将生成的文件部署到"src"同级目录下,即生成上面的目录结构**

4. ## 具体模块界面/功能展示与介绍

   ![示例图片](https://github.com/Icy-Joker/CustomSDK/wiki/resource/gifs/StyleSheetViewer.gif "样式表编辑工具")

   ![示例图片](https://github.com/Icy-Joker/CustomSDK/wiki/resource/gifs/GraphicsViewDemo.gif "2D场景绘制")

   ![示例图片](https://github.com/Icy-Joker/CustomSDK/wiki/resource/gifs/DatabaseVisualizationTool.gif "数据库可视化工具")

   ![示例图片](https://github.com/Icy-Joker/CustomSDK/wiki/resource/gifs/QRCodeGenerator.gif "二维码编码工具")

   ![示例图片](https://github.com/Icy-Joker/CustomSDK/wiki/resource/gifs/MediaPlayer.gif "媒体播放器")

   ![示例图片](https://github.com/Icy-Joker/CustomSDK/wiki/resource/gifs/NetworkTool.gif "网络测试工具")

   ![示例图片](https://github.com/Icy-Joker/CustomSDK/wiki/resource/gifs/ChartDemo.gif "图表示例")

   ![示例图片](https://github.com/Icy-Joker/CustomSDK/wiki/resource/gifs/RegularExpressionValidator.gif "正则验证工具")

5. ## 其他
   源码学习:项目中的项目均按照其角色分类依次提交,可通过Git日志查看每次提交的变更,更容易梳理出各子项扮演的角色
