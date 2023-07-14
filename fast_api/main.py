from fastapi import FastAPI
import uvicorn

# 创建app
app = FastAPI()

# 绑定路由和视图函数


@app.get("/")
async def index():
    return {"FastAPI": "Hello world!"}


@app.get("/items/{item_id}")
async def get_item(item_id: int):
    return {"item_id": item_id}

# 在 Windows 中必须加上 if __name__ == "__main__"
# 否则会抛出 RuntimeError: This event loop is already running
if __name__ == "__main__":
    # 启动服务，因为我们这个文件叫做 main.py
    # 所以需要启动 main.py 里面的 app
    # 第一个参数 "main:app" 就表示这个含义
    # 然后是 host 和 port 表示监听的 ip 和 端口
    uvicorn.run("main:app", host="0.0.0.0", port=5555)
