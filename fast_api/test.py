import requests

print(requests.get("http://localhost:5555").json())
print(requests.get("http://localhost:5555/items/100").json())
print(requests.get("http://localhost:5555/items/item100").json())
print(requests.get("http://localhost:5555/items/").json())
