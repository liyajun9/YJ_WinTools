此项目包含本人编写的Windows C++常用工具，如有错误，欢迎指出.
目录结构：
├─exceptions	异常类，继承自std::exception，添加了详细异常描述
├─libs			外部库，jsoncpp, libcurl, openssl, sqlite
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
├─log			日志
├─macros		常用宏定义
├─security  	编码加解密工具，包含MD5, Base64, DES, AES, RSA, Signature		
└─utils
    ├─database		数据库api封装，支持sqlite3
    ├─encodings		字符编码转换工具, 支持unicode,ansi,utf8之间的相互转换
    ├─synchronize   同步类，event, locker
    ├─thread        线程类，线程监听者类
    ├─time         	时间常用工具
    └─trace			trace
