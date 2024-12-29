# Chronograph
这个软件是模仿[105软件工作室](www.105soft.com)的365倒计时写的。因为恰好需要在大屏上显示短时间的倒计时，这类软件在线版挺多，而且在线版本界面也做得更好看，但是在线版始终没有离线版靠谱。再说界面问题，365倒计时采用透明模式的办法，配合其他软件，什么样的背景做不出来？所以本人觉得365倒计时其实很实用，但是却缺少了实时钟功能，因为有时也只需要显示实际时间就够了。所以就模仿重写了一个。
程序是用MFC写的，本来这种简单的用Win32 API也够了，因为网上都说MFC就是一个封装，逻辑、原理没咋变，试用下来确实如此，但在很多细节上还是方便了不少，结构也更清楚了一些。但该趟的坑还是得趟，这里记录一下：
1.文档/视图模式，这里只要框架窗口设透明，视图窗口不用设也能透明，但是返过来一点用都没有，这里没有弄明白。从结果来看也可以达到想要的效果，但是，需要消息在框架和视图之间传来传去，比较麻烦，所以最终完全没用文档/视图结构。如果不是要实现透明效果，其实文档/视图模式结构更清楚一些；
2.使用了几个MFC的控件，书上都没有的，应该是新版本才提供的吧，字体那个，从RC文件内容来看，其列表应该是静态的（没有换电脑测试），关键是item还不是CString然后又不能直接用，不知道设计这么复杂是为什么，还有颜色那个，明明是combo命名却偏偏要叫button，看来要用好还得自己弄。
3.是窗口样式，网上看到很多人照搬照抄弄不出透明效果，原因是有的是基于控件，有的是基于对话框，创建的时候基础样式不同，附带的样式也不同，也即是说，不管是创建什么类型的窗口，结果得到的样式（包括扩展样式）并不仅仅只是创建时写明了的那些样式，原因可能是有些样式是冲突的或者关联的，要有这种样式就必须有（或都没有）另一种样式，所以改变样式的时候少（或多）去掉（或添加）一种都可能没有效果，并且基础样式和扩展样式之间也存在关联。关键是样式设冲突了程序并不会报错，很不容易发现问题。不过读取样式出来分析还是容易找出正确的设置方法的。
