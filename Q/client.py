from urllib import response
import requests

url = "http://127.0.0.1:8000/api/v1/sensors/listCreate/"

response = requests.get(url)

print(response.json())