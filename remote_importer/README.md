远程导入模块:

1）启动远端服务器：
使用python自带的 http.server 模块，用一条命令实现一个http服务：
$ python3 -m http.server 12800
Serving HTTP on 0.0.0.0 port 12800 (http://0.0.0.0:12800/) ...
...

2）在命令行输入：
>>> from remote_importer import install_meta
>>> install_meta('http://localhost:12800/') # 往 sys.meta_path 注册 finder 
>>> import my_info  # 打印ok，说明导入成功
hello world!
>>> my_info.name  # 验证可以取得到变量
'hahahaha!'

<img width="" src="/uploads/873FDE1B944B492BA8B988F2EC005042/image.png" alt="image.png" />

在笔者的机器上：
<img width="" src="/uploads/7D7B9AD793574D6AAD31D6E95BE63E2A/image.png" alt="image.png" />
