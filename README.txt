此项目包含本人编写的Windows C++常用工具，如有错误，欢迎指出.

目录结构：
\					headers.h 引入常用头文件
macros\				宏定义
libs\				外部库文件
					jsoncpp\
					libcurl\
					sqlite\
utils\				工具类
  					encodings\charEncodings		字符编码，支持unicode,ansi,utf8之间的相互转换
					time\timeUtils	时间工具
					synchronize\CSLocker,Event 封装同步对象
					trace\trace	调试trace
					FileUtils	文件工具
					StringUtils string工具
					SystemUtils	系统工具
					database	数据库
						sqlite	sqlite数据库访问
exceptions\			异常类
					Exception		基本异常，做为自定义异常基类，继承自std::exception，添加了详细异常描述
					SystemException windows系统异常，自动获取LastError做为描述
					WSAException	windows WSA异常，自动获取WSALastError做为描述
					SQLiteException SQLite异常
log\				日志
security\			安全
					Base64
					MD5
					Crypto_DES
					Crypto_AES
					Crypto_RSA
					Crypto_Sign
socketserver\		threadpool\ 线程池	IOCPThreadPool基本的IOCP线程池模板，可绑定设备，可手动dispatch派发任务，可手动增加或减少活动线程数
								\IOCP   完成端口
								\workerThread 工作线程
								

├─exceptions
├─libs
│  ├─jsoncpp
│  │  └─json
│  ├─libcurl
│  │  ├─bin
│  │  ├─include
│  │  │  └─curl
│  │  └─lib
│  ├─openssl
│  │  ├─bin
│  │  ├─include
│  │  │  └─openssl
│  │  └─lib
│  └─sqlite
│      ├─bin
│      ├─include
│      └─lib
├─log
├─macros
├─server
├─socketserver
│  ├─buffer
│  ├─connection
│  ├─protocol
│  └─threadPool
│      ├─IOCP
│      └─workerThread
├─templates
└─utils
    ├─database
    ├─encodings
    ├─synchronize
    ├─thread
    ├─time
    └─trace
